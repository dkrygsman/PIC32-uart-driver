///*******************************************************************************
// * Author: daniel krygsman
// * Date:    1/27/2023
// *
// *
// * Program: Flashes LED
// * Info: pickit3 PIC32MX340F512H xc32 compiler
// ******************************************************************************/
//
//
//#include <xc.h>
//#include "Uart.h"
//#include <BOARD.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <proc/p32mx340f512h.h>
//#include <sys/attribs.h>
//#include "buffer.h"
//
//
////#define PART1
////#define PART2
////#define BUFFER_SIZE 16
//
//
//
//static circular_buffer tx_buffer;
//static circular_buffer rx_buffer;
//static int tx_busy;
//static int rx_busy;
//static int tx_collision;
//
//
//void Uart_Init(void){
//    IEC0bits.U1RXIE = 0;
//    IEC0bits.U1TXIE = 0;    
//    U1MODE = 0;                     //clears control registers
//    U1BRG = 21;                     //sets baud rate to generate 115200
//    U1MODEbits.PDSEL = 00;          //sets no parity       
//    U1MODEbits.STSEL = 0;           //sets 1 bit stop             //uart enable
//            //receiver enable
//    IPC6bits.U1IP = 6;
//    IPC6bits.U1IS = 0;
//    U1STAbits.URXISEL = 0;              //rx flag raised when character is received
//    U1STAbits.UTXISEL = 0;              //tx flag raised when tx contains space
//    IFS0bits.U1TXIF = 0;
//    IFS0bits.U1RXIF = 0;
//    U1MODEbits.ON = 1; 
//    IEC0bits.U1RXIE = 1;
//    IEC0bits.U1TXIE = 1; 
//    U1STAbits.UTXEN = 1;            //transmitter enable
//    U1STAbits.URXEN = 1;
//    return;
//}   
//
//
//
//int PutChar(char ch)
//{
//    if(is_buff_full(&tx_buffer))            //do nothing if buff is full
//    {
//        return 0;
//    }
//    else
//    {
//        tx_busy = 1;                        //while adding raise busy flag
//        add_to_buff(&tx_buffer, ch);
//        //tx_busy = 0;
//        //TRMT is 1 when tx reg and buff are empty
//        
//        //if(U1STAbits.TRMT == 1 && tx_collision == 0)
//        if (U1STAbits.TRMT==1 && !is_buff_empty(&tx_buffer))        //tx is empty and but has data
//        {
//            tx_busy = 0;                                        //lower busy and raise interupt, best case
//            IFS0bits.U1TXIF = 1;
//        }
//        //else if(U1STAbits.TRMT == 1 && tx_collision == 1)
//        else 
//        {
//            tx_busy = 0;
//            //IFS0bits.U1TXIF = 1;
//            //tx_collision = 0;
//        }
//        return 1;
//    }
//}
//
//unsigned char GetChar(void)
//{
//        unsigned char value_getchar;
//        value_getchar = take_from_buff(&rx_buffer);         //simple just take from rx and return 
//        return value_getchar;
//        IFS0bits.U1RXIF = 1;
//}
//
//void __ISR(_UART_1_VECTOR)IntUart1Handler(void)
//{
//    int checker = 0;
//    if(IFS0bits.U1RXIF)                                     //RX block
//    {
//        IFS0bits.U1RXIF = 0;                //URXDA is rx buffer sweet stop
//        while(U1STAbits.URXDA && !is_buff_full(&rx_buffer))     //has room and data and buffer has room
//        {
//            add_to_buff(&rx_buffer, U1RXREG);               //add rxREG contents to rx_buff
//            LATE = 0b00000001;
//        }
//       
//    }
//    if(IFS0bits.U1TXIF)                         //TX block
//    {
//        IFS0bits.U1TXIF = 0;
//        if(tx_busy)                             //if busy do nothing
//        {
//            //tx_collision = 1;
//            //LATE = 0b00000010;
//            //tx_busy = 0;
//        }
//        else                                                            
//        {
//            while (!is_buff_empty(&tx_buffer) && !U1STAbits.UTXBF)      //if not busy check if tx_buff has data and TX is not full
//            {                   //UTXBF is 1 when TX is full
//            
//                unsigned char val;
//                val = take_from_buff(&tx_buffer);           //print next char from tx_buffer
//                U1TXREG = val;
//                LATE = 0b00000100;
//                //tx_busy = 0;
//            } 
//            
//          
//        }
//    
//    }
//    //tx_busy = 0;
//    IFS0bits.U1TXIF = 0;                            //lower flag for special cases such as first flag raise
//}
//
//
//
//#ifdef PART2
//void main(void) {
//    BOARD_Init();
//    Uart_Init();
//    Buff_Init(&tx_buffer);
//    Buff_Init(&rx_buffer);
//    TRISE = 0x00;
//    LATE = 0b00000000;
//    
//    
//    
//   
//    
//    
//    
//    while(1)
//    {
//        LATE = 0b10000000;
//        
//        if(!is_buff_empty(&rx_buffer))
//        {
//            unsigned char k;
//            k = GetChar();
//            LATE = 0b00000000;
//            PutChar(k); 
//        }
//        
//    }
//    
//    return;
//}
//#endif
//
//#ifdef PART1
//void main(void) {
//    BOARD_Init();
//    UART_Init();
//    while(1)
//    {
//        if (U1STAbits.URXDA != 0)
//        {
//            U1TXREG = U1RXREG;
//        }
//    U1RXREG = 0;
//    };
//    return;
//}
//#endif 
//
//
