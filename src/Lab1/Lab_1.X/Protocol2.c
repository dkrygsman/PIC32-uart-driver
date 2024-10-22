/*
 * File:   Protocol2.c
 * Author: danie
 *
 * Created on March 11, 2023, 2:44 PM
 */

#include <xc.h>
#include "Uart.h"
#include <BOARD.h>
#include <stdio.h>
#include <stdlib.h>
#include <proc/p32mx340f512h.h>
#include <sys/attribs.h>
#include "buffer.h"
#include "Protocol2.h"
#include "MessageIDs.h"
#include <string.h>

#define PROT_1
#define HEAD 0xCC
#define TAIL 0xB9
#define SET_ID 0x81
#define GET_ID 0x83
#define STATE_ID 0x82
#define PING_ID 0x84
#define PONG_ID 0x85

static int state;

static rxpADT failedbuffer;
static rxpADT testbuffer;
static rxpADT printbuffer;
static rxpADT rxPacket;
static rxpADT endianbuffer;
static packet_buffer pkt_buff_1;
static circular_buffer tx_buffer;
static circular_buffer rx_buffer;
static int tx_busy;
static int rx_busy;
static int tx_collision;
static int counter;
static int special_case;
static int packet_ready;



/*------------------------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------Protocol Functions------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------------------------------*/


int Protocol_Init(){
    BOARD_Init();
    Uart_Init();
    Buff_Init(&tx_buffer);
    Buff_Init(&rx_buffer);
    LEDS_INIT();
    TRISE = 0x00;
    pkt_Buff_Init(&pkt_buff_1);
    state = 1;
    packet_ready = 0;
}



int Protocol_SendDebugMessage(char *Message)
{
    unsigned char temp[MAXPAYLOADLENGTH];
    
    for (int j =1; j <= (strlen(Message)); j ++){
        temp[j] = Message[j-1];
    }
    
    unsigned char debug_len;
    debug_len = strlen(Message)+1;
    
    Protocol_SendPacket(debug_len, 0x80, temp);
    return 1;
}

uint8_t Protocol_QueuePacket (){
    
    if(!is_buff_empty(&rx_buffer))
    {
        unsigned char k;
        k = GetChar();
        return BuildRxPacket(&rxPacket, k);
    }
}


int Protocol_SendPacket(unsigned char len, unsigned char ID, void *Payload){  
    int checker = 0;
    if(len <= 0x80){
        PutChar(HEAD);
        PutChar(len);
        PutChar(ID);
        unsigned char current_cksum;
        current_cksum = Protocol_CalcIterativeChecksum(ID, 0x00);
        int i;
        unsigned char* payload_number = Payload;
    
        payload_number++;
        for (i =1; i < len; i ++)
        {
            PutChar(*payload_number);
            current_cksum = Protocol_CalcIterativeChecksum(*payload_number, current_cksum);
            payload_number++;
        }
    
        PutChar(TAIL);
        PutChar(current_cksum);
        PutChar('\r');
        PutChar('\n');
        return 1;
    }
    else{
        return 0;
    }
}


uint8_t BuildRxPacket (rxpADT *y, unsigned char input)
{
    //LATE = 0x10000000;
    //  assign static variable state = 1;   in main
    
    //states
    //1-head
    //2-len
    //3-ID
    //4-payload
    //5-tail
    //6-cksum
    //7-\r
    //8-\n 
    
    switch(state)
    {
        case 1:
        {
            if(input == 0xCC){
                state = 2;
                //PutChar(input);
            }
            
        }
        break;
        case 2:
        {
            y->len = input;
            //PutChar(input);
            if(y->len == 1)
            {
                special_case = 1;
            }
            state = 3;
        }
        break;
        case 3:
        {
            y->ID = input;
            //PutChar(input);
            counter = 1;
            state = 4;
            if(special_case == 1)
            {
                state = 5;
            }
            
        }
        break;
        case 4:
        {
            if(counter < y->len)
            {
                y->payLoad[counter] = input;
                //PutChar(input);
                counter = counter + 1;
                if(counter == y->len)
                {
                    state = 5;
                }
            }
            
        }
        break;
        case 5:
        {
            if(input == 0xB9){
                state = 6;
                //PutChar(input);
            }
            else{
                state = 1;
            }
        }
        break;
        case 6:
        {
            y->checkSum = input;
            //PutChar(input);
            state = 7;
        }
        break;
        case 7:
        {
            state = 8;
        }
        break;
        case 8:
        {
            state = 1;

            packet_ready = 1;
            if(y->ID == SET_ID){                  //LED SET case 
//                set = 1;
                LEDS_SET(y->payLoad[1]);
            }
            if(y->ID == GET_ID){                  //LED GET case 
//                get = 1;
                y->payLoad[1] = LEDS_GET();
                y->len = 0x02;
                y->ID = STATE_ID;
            }
            if(y->ID == PING_ID)                   //LED PING case 
            {
                y->ID = PONG_ID;
            }
            
            add_to_pkt_buff(&pkt_buff_1, rxPacket);
        }
        break;
    }
}

unsigned char Protocol_CalcIterativeChecksum(unsigned char charIn, unsigned char 
curChecksum)
{
    unsigned char cksum;
    cksum = 0;
    cksum = curChecksum;
    cksum = (cksum >> 1) + (cksum << 7);
    cksum += charIn;
    return cksum;
}


/*------------------------------------------------------------------------------------------------------------------------------------------*/
/*-------------------------------------------------------Packet Buffer Functions------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------------------------------*/


int add_to_pkt_buff(packet_buffer *x, rxpADT y)            //packet buffer is the packet buffer instance 
{                                                           //rxpADT is the struct that im enqeueing to that buffer ^
    if(is_pkt_buff_full(x) == 1)
    {
        return 0;
    }
    else
    {
        x->data[x->tail] = y;
        x->tail= (x->tail+1)%BUFFER_SIZE;
        if(x->tail==x->head)
        {
            x->full_flag = 1;
        }
        return 1;
    }
}



rxpADT take_from_pkt_buff(packet_buffer *x){
    
    rxpADT val;
        if(is_pkt_buff_empty(x)== 1)
        {
        
            return failedbuffer;
        }
        else 
        {
        val = x->data[x->head];
        x->head = (x->head+1)%BUFFER_SIZE;
        x->full_flag = 0;
        }
            
    return val;
}

int pkt_Buff_Init(packet_buffer *x)
{
    x->head = 0;                          //set all static variables to zero
    x->tail = 0;
    x->full_flag = 0;
    return 1;
}

int is_pkt_buff_empty(packet_buffer *x)
{         
    if(x->tail==x->head && x->full_flag ==0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
        
}

int is_pkt_buff_full(packet_buffer *x){
    
    if(x->head== x->tail && x->full_flag == 1)
    {
        return 1;
    }    
    else
    {
        return 0;
    }
        
}

/*------------------------------------------------------------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------MAIN-------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------------------------------*/


#ifdef PROT_1
void main(void) 
{
    Protocol_Init();
    
  
/*                                                  //testing send packet 
*    unsigned char test[MAXPAYLOADLENGTH];
*    test[0] = 0x85;
*    test[1] = 0x00;
*    test[2] = 0x43;
*    test[3] = 0xcd;
*    test[4] = 0x28;
*    Protocol_SendPacket(0x05, 0x84, test);      //payload (test) is entire payload including ID
*    int check = 0;
*/

    
/*                                           //testing build rx packet state machine 
*    state = 1;
*    special_case = 0;
*    BuildRxPacket (&rxPacket, HEAD);          //for this one i load in head, len, id, payload[1]...payload[len-1], tail, cksum, \r, \n 
*    unsigned char one = 0x02;
*    BuildRxPacket (&rxPacket, one);
*    unsigned char eight_o = 0x81;
*    BuildRxPacket (&rxPacket, eight_o);
*    unsigned char leds = 0x01;
*    BuildRxPacket (&rxPacket, leds);
*    BuildRxPacket (&rxPacket, TAIL);
*    unsigned char check_S = 0xE6;
*    BuildRxPacket (&rxPacket, check_S);
*    unsigned char zero_d = 0x0D;
*    BuildRxPacket (&rxPacket, zero_d);
*    unsigned char zero_A = 0x0A;
*    BuildRxPacket (&rxPacket, zero_A);
*    int r = 0;
*/    
    
/*                                                  //code for testing out my enqueue and dequeue packets
*    rxPacket.ID = 0x81;
*    rxPacket.checkSum = 0xf6;
*    rxPacket.len = 0x02;
*    rxPacket.payLoad[1] = 0x65;
*    add_to_pkt_buff(&pkt_buff_1, rxPacket);
*    
*    //Protocol_SendPacket(testbuffer.len, testbuffer.ID, testbuffer.payLoad);
*    testbuffer = take_from_pkt_buff(&pkt_buff_1);
*    Protocol_SendPacket(testbuffer.len, 0x80, testbuffer.payLoad);
*    PutChar(HEAD);
*    PutChar('a');
*    LEDS_SET(0x02);
*/
    
    
/*                                          //testing for build packet then return 
*    int check = 0;
*    while(1)
*    {
*        LATE = 0b11000000;
*        
*        if(!is_buff_empty(&rx_buffer))
*        {
*            unsigned char k;
*            k = GetChar();
*            //PutChar(k);
*            //BuildRxPacket (&rxPacket, k);
*            
*        }
*        
*    Protocol_SendPacket(0x02, 0x81, &rxPacket->payLoad);
*/       
    
    
    unsigned char debug_message[MAXPAYLOADLENGTH] = "This is the debug message!!!";
    
    
    Protocol_SendDebugMessage(debug_message);
    //Protocol_SendPacket(0x01, 0x80, 0x00);
    //int does = PutChar('a');
    while(1)
    {
        
        k = GetChar();
        return BuildRxPacket(&rxPacket, k);
        
        //Protocol_QueuePacket();
        
            if(packet_ready == 1){
                //add_to_pkt_buff(&pkt_buff_1, rxPacket);
                packet_ready = 0;
                printbuffer = take_from_pkt_buff(&pkt_buff_1);
                
               //Protocol_SendPacket(printbuffer.len, printbuffer.ID, printbuffer.payLoad);
                
                if(printbuffer.ID == SET_ID)
                {
                    Protocol_SendPacket(printbuffer.len, printbuffer.ID, printbuffer.payLoad);
                }
                if(printbuffer.ID == STATE_ID)
                {
                    Protocol_SendPacket(printbuffer.len, printbuffer.ID, printbuffer.payLoad);
                }
                special_case = 0;
                
                if(printbuffer.ID == PONG_ID)
                {
                    uint32_t e;
                    e = (printbuffer.payLoad[1]<<24)|(printbuffer.payLoad[2]<<16)|(printbuffer.payLoad[3]<<8)|(printbuffer.payLoad[4]);
                    e = e/2;
                
                    printbuffer.payLoad[1] = (e>>24)&0xFF;
                    printbuffer.payLoad[2] = (e>>16)&0xFF;
                    printbuffer.payLoad[3] = (e>>8)&0xFF;
                    printbuffer.payLoad[4] = (e)&0xFF;
                    Protocol_SendPacket(printbuffer.len, printbuffer.ID, printbuffer.payLoad);
                }
                
                
            }
        
    };
    return;
}
#endif



/*------------------------------------------------------------------------------------------------------------------------------------------*/
/*-------------------------------------------------------Interrupt Functions ---------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------------------------------*/


void Uart_Init(void){
    IEC0bits.U1RXIE = 0;
    IEC0bits.U1TXIE = 0;    
    U1MODE = 0;                     //clears control registers
    U1BRG = 21;                     //sets baud rate to generate 115200
    U1MODEbits.PDSEL = 00;          //sets no parity       
    U1MODEbits.STSEL = 0;           //sets 1 bit stop             //uart enable
            //receiver enable
    IPC6bits.U1IP = 6;
    IPC6bits.U1IS = 0;
    U1STAbits.URXISEL = 0;              //rx flag raised when character is received
    U1STAbits.UTXISEL = 0;              //tx flag raised when tx contains space
    IFS0bits.U1TXIF = 0;
    IFS0bits.U1RXIF = 0;
    U1MODEbits.ON = 1; 
    IEC0bits.U1RXIE = 1;
    IEC0bits.U1TXIE = 1; 
    U1STAbits.UTXEN = 1;            //transmitter enable
    U1STAbits.URXEN = 1;
    return;
}   



int PutChar(char ch)
{
    if(is_buff_full(&tx_buffer))            //do nothing if buff is full
    {
        return 0;
    }
    else
    {
        tx_busy = 1;                        //while adding raise busy flag
        add_to_buff(&tx_buffer, ch);
        //tx_busy = 0;
        //TRMT is 1 when tx reg and buff are empty
        
        //if(U1STAbits.TRMT == 1 && tx_collision == 0)
        if (U1STAbits.TRMT==1 && !is_buff_empty(&tx_buffer))        //tx is empty and but has data
        {
            tx_busy = 0;                                        //lower busy and raise interupt, best case
            IFS0bits.U1TXIF = 1;
        }
        //else if(U1STAbits.TRMT == 1 && tx_collision == 1)
        else 
        {
            tx_busy = 0;
            //IFS0bits.U1TXIF = 1;
            //tx_collision = 0;
        }
        return 1;
    }
}

unsigned char GetChar(void)
{
        unsigned char value_getchar;
        value_getchar = take_from_buff(&rx_buffer);         //simple just take from rx and return 
        return value_getchar;
        //IFS0bits.U1RXIF = 1;
}

void __ISR(_UART_1_VECTOR)IntUart1Handler(void)
{
    int checker = 0;
    if(IFS0bits.U1RXIF)                                     //RX block
    {
        IFS0bits.U1RXIF = 0;                //URXDA is rx buffer sweet stop
        while(U1STAbits.URXDA && !is_buff_full(&rx_buffer))     //has room and data and buffer has room
        {
            add_to_buff(&rx_buffer, U1RXREG);               //add rxREG contents to rx_buff
            //LATE = 0b00000001;
        }
       
    }
    if(IFS0bits.U1TXIF)                         //TX block
    {
        IFS0bits.U1TXIF = 0;
        if(tx_busy)                             //if busy do nothing
        {
            //tx_collision = 1;
            //LATE = 0b00000010;
            //tx_busy = 0;
        }
        else                                                            
        {
            while (!is_buff_empty(&tx_buffer) && !U1STAbits.UTXBF)      //if not busy check if tx_buff has data and TX is not full
            {                   //UTXBF is 1 when TX is full
            
                unsigned char val;
                val = take_from_buff(&tx_buffer);           //print next char from tx_buffer
                U1TXREG = val;
                //LATE = 0b00000100;
                //tx_busy = 0;
            } 
            
          
        }
    
    }
    //tx_busy = 0;
    IFS0bits.U1TXIF = 0;                            //lower flag for special cases such as first flag raise
}

/*------------------------------------------------------------------------------------------------------------------------------------------*/
/*-------------------------------------------------------Circular Buffer Functions----------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------------------------------*/

int Buff_Init(circular_buffer *w)
{
    w->head = 0;                          //set all static variables to zero
    w->tail = 0;
    w->full_flag = 0;
    return 1;
}

int is_buff_empty(circular_buffer *w)
{         
    if(w->tail==w->head && w->full_flag ==0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
        
}

int is_buff_full(circular_buffer *w){
    
    if(w->head== w->tail && w->full_flag == 1)
    {
        return 1;
    }    
    else
    {
        return 0;
    }
        
}

unsigned char take_from_buff(circular_buffer *w){
    
    char val;
        if(is_buff_empty(w)== 1)
        {
            return 0;
        }
        else 
        {
        val = w->data[w->head];
        w->head = (w->head+1)%BUFFER_SIZE;
        w->full_flag = 0;
        }
            
    return val;
}

int add_to_buff(circular_buffer *w, char ch)
{    
    if(is_buff_full(w) == 1)
    {
        return 0;
    }
    else
    {
        w->data[w->tail] = ch;
        w->tail= (w->tail+1)%BUFFER_SIZE;
        if(w->tail==w->head)
        {
            w->full_flag = 1;
        }
        return 1;
    }
}


/*------------------------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------------------------------*/