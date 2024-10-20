/* 
 * File:   Protocol.h
 * Author: Petersen
 * rewritten for Uart.c ECE121 W2023
 */
#ifndef PROTOCOL_H
#define PROTOCOL_H
/*******************************************************************************
 * PUBLIC #DEFINES                                                            *
 ******************************************************************************/
#define PACKETBUFFERSIZE 16
#define MAXPAYLOADLENGTH 128 
#define DEBUG 0 
/*******************************************************************************
 * PUBLIC DATATYPES
 ******************************************************************************/


typedef struct rxpT {
    uint8_t ID;      
    uint8_t len;
    uint8_t checkSum; 
    unsigned char payLoad[MAXPAYLOADLENGTH];
 }rxpADT; 
 
 
typedef struct{
    int head;
    int tail;
    rxpADT data[PACKETBUFFERSIZE];
    int full_flag;
}packet_buffer;

/*******************************************************************************
 * PUBLIC FUNCTIONS                                                           *
 ******************************************************************************/
/**
 * @Function Protocol_Init(baudrate)
 * @param Legal Uart baudrate
 * @return SUCCESS (true) or ERROR (false)
 * @brief Initializes Uart1 for stream I/O to the lab PC via a USB 
 *        virtual comm port. Baudrate must be a legal value. 
 * @author instructor W2022 */
int Protocol_Init(void);
/**
 * @Function unsigned char Protocol_QueuePacket()
 * @param none
 * @return the buffer full flag: 1 if full
 * @brief Place in the main event loop (or in a timer) to continually check 
 *        for completed incoming packets and then queue them into 
 *        the RX circular buffer. The buffer's size is set by constant
 *        PACKETBUFFERSIZE.
 * @author instructor W2023 */
uint8_t Protocol_QueuePacket ();
/**
 * @Function int Protocol_SendDebugMessage(char *Message)
 * @param Message, Proper C string to send out
 * @return SUCCESS (true) or ERROR (false)
 * @brief Takes in a proper C-formatted string and sends it out using ID_DEBUG
 * @warning this takes an array, do <b>NOT</b> call sprintf as an argument.
 * @author mdunne */
int Protocol_SendDebugMessage(char *Message);               
/**
 * @Function int Protocol_SendPacket(unsigned char len, void *Payload)
 * @param len, length of full <b>Payload</b> variable
 * @param Payload, pointer to data
 * @return SUCCESS (true) or ERROR (false)
 * @brief composes and sends a full packet
 * @author instructor W2022 */
int Protocol_SendPacket(unsigned char len, unsigned char ID, void *Payload);      
/*******************************************************************************
 * PRIVATE FUNCTIONS
 * Generally these functions would not be exposed but due to the learning nature 
 * of the class some are are noted to help you organize the code internal 
 * to the module. 
 ******************************************************************************/
/* BuildRxPacket() should implement a state machine to build an incoming
 * packet incrementally and return it completed in the called argument packet
 * structure (rxPacket is a pointer to a packet struct). The state machine should
 * progress through discrete states as each incoming byte is processed.
 * 
 * To help you get started, the following ADT is an example of a structure 
 * intended to contain a single rx packet. 
 */
 /* Now consider how to create another structure for use as a circular buffer
 * containing a PACKETBUFFERSIZE number of these rxpT packet structures.
 ******************************************************************************/
uint8_t BuildRxPacket (rxpADT *y, unsigned char input);
/**
 * @Function char Protocol_CalcIterativeChecksum(unsigned char charIn, unsigned 
char curChecksum)
 * @param charIn, new char to add to the checksum
 * @param curChecksum, current checksum, most likely the last return of this 
function, can use 0 to reset
 * @return the new checksum value
 * @brief Returns the BSD checksum of the char stream given the curChecksum and the
new char
 * @author mdunne */
unsigned char Protocol_CalcIterativeChecksum(unsigned char charIn, unsigned char 
curChecksum);
/**
 * This macro initializes all LEDs for use. It enables the proper pins as outputs 
and also turns all
 * LEDs off.
 */
#define LEDS_INIT() do {LATECLR = 0xFF; TRISECLR = 0xFF;} while (0)
/**
 * Provides a way to quickly get the status of all 8 LEDs into a uint8, where a bit
is 1 if the LED
 * is on and 0 if it's not. The LEDs are ordered such that bit 7 is LED8 and bit 0 
is LED0.
 */
#define LEDS_GET() (LATE & 0xFF)
/**
 * This macro sets the LEDs on according to which bits are high in the argument. 
Bit 0 corresponds
 * to LED0.
 * @param leds Set the LEDs to this value where 1 means on and 0 means off.
 */
#define LEDS_SET(leds) do { LATE = (leds); } while (0)
#endif /* PROTOCOL_H */

int add_to_pkt_buff(packet_buffer *x, rxpADT y);

rxpADT take_from_pkt_buff(packet_buffer *x);

int pkt_Buff_Init(packet_buffer *x);

int is_pkt_buff_empty(packet_buffer *x);

int is_pkt_buff_full(packet_buffer *x);