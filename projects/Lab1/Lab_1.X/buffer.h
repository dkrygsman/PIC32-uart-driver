/***
 * File:    buffer.h
 * Author:  Daniel Krygsman
 * Created: ECE121 W2023 rev 1
 * This library implements a true UART device driver that enforces 
 * I/O stream abstraction between the physical and application layers.
 * All stream accesses are on a per-character or byte basis. 
 */
#include <xc.h>
#include <BOARD.h>
#define BUFFER_SIZE 32
/*******************************************************************************
 
STRUCTURES     
 */

typedef struct{
    int head;
    int tail;
    unsigned char data[BUFFER_SIZE];
    int full_flag;
}circular_buffer;
// ******************************************************************************/


/*******************************************************************************
 * PUBLIC FUNCTION PROTOTYPES                                                  *
 ******************************************************************************/
/**
 * @Function Buff_Init(void)
 * @param circular_buffer whichBuff
 * @return none
 * @brief  Initializes buff, sets head to 0 and tail to 0, and data to 0
 * @author Daniel Krygsman ece121 W2023 */
int Buff_Init(circular_buffer *w);


/**
 * @Function add_to_buff(char ch);
 * @param circular_buffer whichBuff, char ch
 * @return int 
 * @brief  adds a char to buffer if has room, return 1 if success, 0 if not
 * @author Daniel Krygsman ece121 W2023 */
int add_to_buff(circular_buffer *w, char ch);

/**
 * @Function take_from_buff(circular_buffer whichBuff)
 * @param circular_buffer whichBuff
 * @return char 
 * @brief  takes from buff, null if empty
 * @author Daniel Kyrgsman ece121 W2023 */
unsigned char take_from_buff(circular_buffer *w);

/**
 * @Function if_buff_full(circular_buffer whichBuff)
 * @param circular_buffer whichBuff
 * @return int
 * @brief  checks if buff is full returns 1 if so 0 if not
 * @author Daniel Kyrgsman ece121 W2023 */
int is_buff_full(circular_buffer *w);

/**
 * @Function is_buff_empty(circular_buffer whichBuff)
 * @param circular_buffer whichBuff
 * @return int
 * @brief  checks if buff is empty, if so return 1, not return0
 * @author Daniel Kyrgsman ece121 W2023 */
int is_buff_empty(circular_buffer *w);



