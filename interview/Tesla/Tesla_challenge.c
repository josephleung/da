#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
 
 
////////////////////////////////////////////////////////////////////////////////
/* TESLA MOTORS FIRMWARE TEST
 * You have 120 minutes to complete the test.  Going over time is penalized at
 * 1% per minute. There are 8 total questions, some with multiple parts.
 *
 * Do not use outside aid or share the content of this test
 *
 * All solutions should compile in Coderpad.io without error
 *
 * A main() function is provided at the bottom for your use
 */
////////////////////////////////////////////////////////////////////////////////
 
////////////////////////////////////////////////////////////////////////////////
// 1) Create a macro (named C_TO_F) to convert from degrees Celsius to Fahrenheit
//    Note: degF = degC * (9/5) + 32
// Answer: TODO
#define C_TO_F(degC) (degC * (9/5) + 32)
 
 
////////////////////////////////////////////////////////////////////////////////
// 2) Bit Manipulation
//    Write a function that inverts (0 -> 1 or 1 -> 0) the most significant and
//    least significant bits of the data value pointed to by b.
 
void flip_hi_lo(uint8_t* b)
{
    uint8_t temp = *b;
    temp ^= 0x81;
    *b = temp;  // here I assume the value pointed to by b is a 8-bit one
}
 
////////////////////////////////////////////////////////////////////////////////
// 3) Debugging
//    The function computeSquareADC() has not been producing correct
//    output consistently. Please describe all issues with the function.
// Answer: TODO
 
volatile uint8_t ADC_RESULT;
uint8_t computeSquareADC(void)
{
    uint16_t retval = ADC_RESULT * ADC_RESULT;  // since this is not a atomic opeation
                                                // the value could change half the way
                                                // causing old_data * new_data problem
    return retval;
}

// fix1 (recommended, save the volatile value before calculation): 
uint8_t computeSquareADC(void)
{
    uint8_t adc_now = ADC_RESULT;
    uint16_t retval = adc_now * adc_now;
    return retval;
}

// fix2 (not recommended for most use case, disable interrupt before calculation):
uint8_t computeSquareADC(void)
{
    // disable interrupt
    uint16_t retval = ADC_RESULT * ADC_RESULT;
    // enable interrupt
    return retval;
}
 
////////////////////////////////////////////////////////////////////////////////
// 4) Memory dump
//    The following memory dump was taken while debugging an issue.
//
// Memory Dump:
// Address:  Byte:
// 0x1000    0xA0
// 0x1001    0x0A
// 0x1002    0xBA
// 0x1003    0x48
// 0x1004    0x2C
// 0x1005    0xB7
// 0x1006    0x3B
// 0x1007    0x82
// 0x1008    0x9C
// 0x1009    0xE5
// 0x100A    0x17
// 0x100B    0x40
// 0x100C    0xEF
// 0x100D    0x47
// 0x100E    0x0F
// 0x100F    0x98
// 0x1010    0x6F
// 0x1011    0xD5
// 0x1012    0x70
// 0x1013    0x9E
// 0x1014    0x94
// 0x1015    0x99
// 0x1016    0x4A
// 0x1017    0xBA
// 0x1018    0xCA
// 0x1019    0xB2
// 0x101A    0x32
// 0x101B    0xE6
// 0x101C    0x8E
// 0x101D    0xB9
// 0x101E    0xC5
// 0x101F    0x2E
// 0x1020    0xC3
//
// System is 32-bit, little-endian.
// A variable called myPacket is of type packet_S (typedef below).
// (Default compiler options; unpacked, naturally aligned.)
// The address of myPacket is 0x1010.
//
typedef struct
{
    uint8_t count;
    uint16_t data[2];
    uint32_t timestamp;
} packet_S;
 
// a) What are the values of each member of myPacket?
// count = 0x6F
// data[0] = 0xD570
// timestamp = 0x9E94994A
 
// b) If the system was big-endian, what would the values of each member of
//    myPacket be?
// count = 0x4A
// data[0] = 0x9994
// timestamp = 0x9E70D56F
 
////////////////////////////////////////////////////////////////////////////////
// 5) State Machine
//
//    Complete the function below to implement the state machine shown in the
//    diagram below for an electronic gumball vending machine.
//     * The initial state of the state machine should be IDLE
//     * The function should output the current state of the state machine
//     * Unexpected input should not cause a state transition
//     * GENERIC_FAULT may be received in any state and should put the machine
//       into the FAULT state
//
//
//          COIN      +---------+
//   +--------------->|         |   BUTTON
//   |                |  READY  | ---------+       
//   |    COIN_RETURN |         |          |
//   |   +----------- +---------+          |
//   |   |                                 |
//   |   V                                 V
// +---------+                        +---------+
// |         |     VEND_COMPLETE      |         |
// |  IDLE   |<-----------------------| VENDING |
// |         |                        |         |
// +---------+                        +---------+
//
//                                 +---------+
//                                 |         |
//                GENERIC_FAULT    |  FAULT  |
//             +------------------>|         |
//                                 +---------+
//
 
typedef enum
{
    IDLE,
    READY,
    VENDING,
    FAULT
} state_E;
 
typedef enum
{
    COIN,
    COIN_RETURN,
    BUTTON,
    VEND_COMPLETE,
    GENERIC_FAULT
} input_E;
 
state_E stateMachine(input_E input)
{
    static unsigned int current_state = IDLE;  // this variable keeps track of the current state
    
    if((current_state == IDLE) && (input == COIN))
    {
        current_state = READY;
        return READY;
    }
 
    else if((current_state == READY) && (input == COIN_RETURN))
    {
        current_state = IDLE;
        return IDLE;    
    }
  
    else if((current_state == READY) && (input == BUTTON))
    {
        current_state = VENDING;
        return VENDING;    
    }
      
    else if((current_state == VENDING) && (input == VEND_COMPLETE))
    {
        current_state = IDLE;
        return IDLE;    
    }
  
    else
      return FAULT;
}
 
 
////////////////////////////////////////////////////////////////////////////////
// 6) Write a unit test for validatePointerAndData that exercises all code paths
//    and branch conditions
 
// @param dataPtr - int32_t pointer to data to be used
//
// @return TRUE if pointer is non-NULL, data value is positive, non-zero and not
//         equal to the sentinel value 0x7FFFFFFF, FALSE otherwise
//
bool validatePointerAndData(int32_t* dataPtr)
{
    bool status = false;
    if ((dataPtr != NULL) &&
        (*dataPtr > 0)    &&
        (*dataPtr != 0x7FFFFFFF))
    {
        status = true;
    }
    return status;
}
 
//
// @return TRUE if all tests pass, FALSE otherwise
//
bool test_validatePointerAndData(void)
{ 
    int32_t test_data = 0;
    int32_t *pointer = NULL;
    bool test_pass = false;
  
    if(validatePointerAndData(pointer) == false)  // passed the NULL pointer test
    {
        test_pass = true;
        *pointer = &test_data;  // now the pointer pointed to is test_data, which is 0
    }
    else
    {
        test_pass = false;
    }

    if (test_pass = true && validatePointerAndData(pointer) == false)  // if passed NULL pointer test, do non-zero test
    {
        test_pass = true;
        *pointer = 0x7FFFFFFF;  // modify the value of test_data to 0x7FFFFFFF
    }
    else 
    {
        test_pass = false;
        
    }
  
    if (test_pass = true && validatePointerAndData(pointer) == false)  // if passed non-zero test, do sentinel value test
    {
        test_pass = true;
    }
    else 
    {
        test_pass = false;  
    }
  
  
    if(test_pass == true)
      return true;
    else
    return false;
}
 
 
////////////////////////////////////////////////////////////////////////////////
// 7) Low Pass Filter
//    Implement a function that will run at 10hz and returns an exponentially
//    weighted average. The latest sample is given 1/10 weighting and previous
//    filtered value a weighting of 9/10. The function should initialize the filter
//    to the first sample value recieved if it is the first time the function has run.
 
float lowPassSamples_10hz(float sample)
{
    static float previous_filtered_value = 0;  // this variable keeps track of revious
//    filtered value
    static bool first_time_run = true;
  
    float output_value = 0;
    
    if(!first_time_run)
    {
      output_value = (previous_filtered_value * 0.9) + (sample * 0.1);
    }
  
    else
    {
      output_value = sample;      
    }
    
    previous_filtered_value = output_value;  // save the value
  
    return output_value;
}
 
////////////////////////////////////////////////////////////////////////////////
// 8a) Create a function to push a byte into a FIFO. The FIFO should be implemented
//     as a circular buffer of length 20. The FIFO will be used to cache the most
//     recent data from a data stream, therefore, drop the oldest value if the
//     buffer is full.
 
#define BUFFER_SIZE 20U
uint8_t fifoBuffer[BUFFER_SIZE];
void bufferPush_ISR(uint8_t data)
{
    static volatile unsigned int population = 0;  // how many active elements in our FIFO
    static volatile unsigned int write_ptr = 0;  // keep track of the write_ptr

    fifoBuffer[write_ptr] = data;  // save the data
  
    if(write_ptr == (BUFFER_SIZE - 1))  // the write_ptr just hits the end of the memory space, go to the head
    {
      write_ptr = 0;
    }
    else  // increment the write pointer
    {
      write_ptr++;
    }

    population = (population < BUFFER_SIZE) ? population++ : BUFFER_SIZE;
}
 
////////////////////////////////////////////////////////////////////////////////
// 8b) Create a function to print out and empty the data buffer.
//     Data should be printed in order from oldest to newest, active elements only.
 
void printAndEmptyBuffer(void)
{
    disableInterrupts();// we do not want any modification to the FIFO in this readout period
    unsigned int read_ptr = 0;
    if(population < BUFFER_SIZE)
    {
      for(int i = 0; i < population; i++)
      {
        printf("%d", fifoBuffer[i]);
      }
      write_ptr = 0;
      population = 0;
    }
    else  // if the FIFO has rewritten happened, we got the oldest data at write_ptr + 1
    {
      read_ptr = write_ptr + 1;
      for(int i = 0; i < population; i++)
      {
        printf("%d", fifoBuffer[read_ptr]);
        
        if(read_ptr == (BUFFER_SIZE - 1))  // the write_ptr just hits the end of the memory space, go to the head
        {
          write_ptr = 0;
        }
        else  // increment the write pointer
        {
          read_ptr++;
        }
        
      }
      write_ptr = 0;
      population = 0;
    }
  
  enableInterrupts();
}
 
////////////////////////////////////////////////////////////////////////////////
// 8c) The function bufferPush_ISR() will be called from an interrupt service
//     routine whenever new data is available to be buffered.
//     The function printAndEmptyBuffer() will be called from a periodic task.
//     The functions disableInterrupts() and enableInterrupts() are available
//     for disabling and enabling interrupts, respectively.
//
//     In your implementations of bufferPush_ISR() and printAndEmptyBuffer(),
//     determine whether or not it is necessary to disable/enable interrupts.
//     If so, add comments where the calls are necessary. If not required,
//     briefly comment why not.
//
// Answer:
// here I disable interrupts in the printAndEmptyBuffer() only since we don't want get the odd result when we printing out data when an element in the FIFO get refreshed.
// of course, if there's possible that the ISR can be trigered insanlely frequent, we may need to disable interrupts when save the data in case we continue refreshing the last element
 
int main()
{
     
    return 0;
}