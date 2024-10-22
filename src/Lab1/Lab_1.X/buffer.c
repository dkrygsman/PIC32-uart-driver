///*
// * File:   buffer.c
// * Author: daniel krygsman
// *
// * Created on February 2, 2023, 2:45 PM
// */
//
//#include <xc.h>
//#include "BOARD.h"
//#include <stdio.h>
//#include <stdlib.h>
//#include "buffer.h"
////#define BUFF_PART_1
//
//#define BUFFER_SIZE 32
//
//
//
//static circular_buffer tx_buffer;
//static circular_buffer rx_buffer;
//
//int Buff_Init(circular_buffer *w)
//{
//    w->head = 0;                          //set all static variables to zero
//    w->tail = 0;
//    w->full_flag = 0;
//    return 1;
//}
//
//int is_buff_empty(circular_buffer *w)
//{         
//    if(w->tail==w->head && w->full_flag ==0)
//    {
//        return 1;
//    }
//    else
//    {
//        return 0;
//    }
//        
//}
//
//int is_buff_full(circular_buffer *w){
//    
//    if(w->head== w->tail && w->full_flag == 1)
//    {
//        return 1;
//    }    
//    else
//    {
//        return 0;
//    }
//        
//}
//
//unsigned char take_from_buff(circular_buffer *w){
//    
//    char val;
//        if(is_buff_empty(w)== 1)
//        {
//            return 0;
//        }
//        else 
//        {
//        val = w->data[w->head];
//        w->head = (w->head+1)%BUFFER_SIZE;
//        w->full_flag = 0;
//        }
//            
//    return val;
//}
//
//int add_to_buff(circular_buffer *w, char ch)
//{    
//    if(is_buff_full(w) == 1)
//    {
//        return 0;
//    }
//    else
//    {
//        w->data[w->tail] = ch;
//        w->tail= (w->tail+1)%BUFFER_SIZE;
//        if(w->tail==w->head)
//        {
//            w->full_flag = 1;
//        }
//        return 1;
//    }
//}
//
//#ifdef BUFF_PART_1
//void main(void) 
//{
//    BOARD_Init();
//    Buff_Init(&tx_buffer);
//    char h = 'h';
//    char e = 'e';
//    char l = 'l';
//    
//    
//    char s = ' ';
//    char w = 'w';
//    char o = 'o';
//    char letter_r = 'r';
//    
//    char d = 'd';
//    
//    add_to_buff(&tx_buffer, h); //1
//    add_to_buff(&tx_buffer, e);
//    add_to_buff(&tx_buffer, l);
//    add_to_buff(&tx_buffer, l);
//    add_to_buff(&tx_buffer, o);
//    add_to_buff(&tx_buffer, s);
//    add_to_buff(&tx_buffer, w);
//    add_to_buff(&tx_buffer, o);
//    add_to_buff(&tx_buffer, letter_r);
//    add_to_buff(&tx_buffer, l);
//    add_to_buff(&tx_buffer, d);
//    add_to_buff(&tx_buffer, s);
//    add_to_buff(&tx_buffer, d);
//    add_to_buff(&tx_buffer, s);
//    add_to_buff(&tx_buffer, d);
//    add_to_buff(&tx_buffer, d); //16
//    add_to_buff(&tx_buffer, d); //17
//    
//    unsigned char values;
//    values = take_from_buff(&tx_buffer);
//    values = take_from_buff(&tx_buffer);
//    values = take_from_buff(&tx_buffer);
//    values = take_from_buff(&tx_buffer);
//    values = take_from_buff(&tx_buffer);
//    
//    add_to_buff(&tx_buffer, d);
//    add_to_buff(&tx_buffer, s);
//    add_to_buff(&tx_buffer, d);
//    add_to_buff(&tx_buffer, s);
//    add_to_buff(&tx_buffer, d);
//    add_to_buff(&tx_buffer, d);
//    
//    while(1)
//    {
//    };
//    return;
//}
//#endif
//
//
//
//
//
//
//
//
//static circular_buffer tx_buffer;
//static circular_buffer rx_buffer;
//
////
/////**
//// * @Function Buff_Init(void)
//// * @param none
//// * @return none
//// * @brief  Initializes buff, sets head to 0 and tail to 0
//// * @author Daniel Krygsman ece121 W2023 */
////
////int Buff_Init(circular_buffer *w)
////{
////    w->head = 0;                         //set all static variables to zero
////    w->tail = 0;
////    w->diff = 0;
////    return;
////}
/////**
//// * @Function if_buff_full(circular_buffer whichBuff)
//// * @param circular_buffer whichBuff
//// * @return int
//// * @brief  checks if buff is full returns 1 if so 0 if not
//// * @author Daniel Kyrgsman ece121 W2023 */
////int is_buff_full(circular_buffer *w)
////{
////    
////        w->diff = w->tail - w->head;
////        if(w->diff == 15)           //3 different options for difference
////        {
////            return 1;
////        }
////        else if(w->diff == 1)
////        {
////            return 1;
////        }
////        else
////        {
////            return 0;
////        }
////    
////}
/////**
//// * @Function is_buff_empty(circular_buffer whichBuff)
//// * @param circular_buffer whichBuff
//// * @return int
//// * @brief  checks if buff is empty, if so return 1, not return0
//// * @author Daniel Kyrgsman ece121 W2023 */
////int is_buff_empty(circular_buffer *w)
////{
////   
////        w->diff = w->tail - w->head;
////        if(w->tail == w->head)
////        {
////            return 1;
////        }
////        else
////        {
////            return 0;
////        }
////        
////}
/////**
//// * @Function take_from_buff(circular_buffer whichBuff)
//// * @param circular_buffer whichBuff
//// * @return char 
//// * @brief  takes from buff, null if empty
//// * @author Daniel Kyrgsman ece121 W2023 */
////
////unsigned char take_from_buff(circular_buffer *w)
////{
////    
////        if(is_buff_empty(w) == 1)                           //check if buff is empty
////        {
////            return 0;                                            //if empty return null
////        }
////        else                                                        
////        {
////            unsigned char r;
////            r = w->data[w->head];                     //else assign data from head to r
////            w->head = (w->head + 1) % BUFFER_SIZE; //increment head, with roll over
////            return r;                                               //return value in r
////        }
////        
////}
/////**
//// * @Function add_to_buff(char ch);
//// * @param circular_buffer whichBuff, char ch
//// * @return int 
//// * @brief  adds a char to buffer if has room, return 1 if success, 0 if not
//// * @author Daniel Krygsman ece121 W2023 */
////    
////int add_to_buff(circular_buffer *w, char ch)
////{
////  
////        if(is_buff_full(w) == 1)                        //check if buffer is full
////        {
////            return 0;                                       //if so return 0, fail
////        }
////        else                                                        
////        {
////            w->data[w->tail] = ch;                    //else update buffer tail with peram
////            w->tail = (w->tail + 1 ) % BUFFER_SIZE;  //increment tail and watch overflow
////            return 1;                                               //return 1, success
////        }
////        
////    
////}