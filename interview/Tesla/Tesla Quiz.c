#include <stdbool.h>

//////////////////////////////////////////////////////////////////////////////
// 1) Celestial Body Struct
////////////////////////////////////////////////////////////////////////////////
// celestialBody_s is a data structure that represents celestial bodies in the
// solar system. However, the data structure is taking up too much space on
// an x86 system (32-bit aligned). How can the celestialBody_s structure be
// changed so that it needs 8 or fewer bytes for storage without losing fidelity
// in any of the members while optimizing for speed? Solutions that do not meet
// this requirement in coderpad will be considered incorrect.
#pragma pack(1)
struct celestialBody_s
{
    float mass;     // 4 bytes
    float diameter; // 4 bytes
} __attribute__((packed));
#pragma pack

// 2) Function-like macro
////////////////////////////////////////////////////////////////////////////////
// Suppose the compiler you are using does not support inline functions
// Write a function-like macro INCREMENT to increment a variable by an
// arbitrary amount. Both the variable to increment and the increment
// amount should be passed in as parameters.
#define INCREMENT(var, amount) ((var) += (amount))

#define MAX_VAL 1000UL

////////////////////////////////////////////////////////////////////////////////
// 3) Array pointer math
////////////////////////////////////////////////////////////////////////////////
//
// Write some code in the arrayMath() function to print out the values located at:
// row 0, column 0
// row 1, column 2
// row 2, column 2
// You are not allowed to use [] to reference the elements of the array.
// You are only allowed to use pointers.
// There should be no compiler warnings or errors.
//
#include <stdio.h>

int myArray[3][4] =
    {
        {0, 3, 6, 9},
        {1, 4, 7, 10},
        {2, 5, 8, 11}};

void arrayMath()
{
    // Here, ptr is declared as a pointer to an array of 4 integers.
    // It is initialized to point to myArray.
    int(*ptr)[4] = myArray;

    // ptr + 0 points to the first row of myArray.
    //*(ptr + 0) dereferences this pointer to get the address of the first element of the first row.
    //*(ptr + 0) + 0 points to the first element of the first row.
    //*(*(ptr + 0) + 0) dereferences this pointer to get the value at row 0, column 0.
    printf("Value at row 0, column 0: %d\n", *(*(ptr + 0) + 0));

    printf("Value at row 1, column 2: %d\n", *(*(ptr + 1) + 2));
    printf("Value at row 2, column 2: %d\n", *(*(ptr + 2) + 2));
}

int main()
{
    arrayMath();
    return 0;
}

////////////////////////////////////////////////////////////////////////////////
// 4) Periodic Tasks
////////////////////////////////////////////////////////////////////////////////
//
// Assume there are two periodic tasks in the system. They run every 10ms and
// 100ms. The system starts up in main, which then creates the two tasks. Main
// is not shown here.
// Assume that the 100ms task is running at lower priority than the 10ms task.
// When the 10ms task needs to run, it interrupts the 100ms task, executes,
// and then returns control to the 100ms task.
// Please explain what is wrong with this code.
//

// race condition, componentValue can get modified by 10ms task when 100ms task is using it
// To solve this, you need to use synchronization mechanisms to protect the shared variable componentValue.
// One common approach is to use a mutex to ensure that only one task can access componentValue at a time.

// +1, also the task should be a while loop

volatile int componentValue = 1;
int finalValue = 1;
pthread_mutex_t lock;

// updates finalValue
void task_100ms()
{
    pthread_mutex_lock(&lock);
    finalValue = componentValue * 2;
    pthread_mutex_unlock(&lock);
    sleep(50);

    pthread_mutex_lock(&lock);
    if (finalValue == (componentValue * 2))
    {
        printf("finalValue is: %d", finalValue);
        printf("componentValue is : %d", componentValue);
    }
    pthread_mutex_unlock(&lock);
}

// updates componentvalue
void task_10ms()
{
    pthread_mutex_lock(&lock);
    componentValue += 1;
    if (componentValue > 20)
    {
        componentValue = 0;
    }
    pthread_mutex_unlock(&lock);
}

////////////////////////////////////////////////////////////////////////////////
// 5) Struct pointer math
////////////////////////////////////////////////////////////////////////////////
//
// Write some code in the structMath() function to print out the values for
// keyValue and alternateKeyValue from the Tesla laptop definition without using
// the '.' or '->' operators to directly reference the qwerty struct or its
// members.
// There should be no compiler warnings or errors.
//
typedef enum
{
    MOUSE_NONE,
    MOUSE_UP,
    MOUSE_DOWN,
    MOUSE_LEFT,
    MOUSE_RIGHT,
} mouse_direction_E;

typedef struct
{
    bool leftButton;
    bool rightButton;
    bool middleButton;
    bool mouseOn;
    mouse_direction_E direction;
} mouse_S;

typedef struct
{
    char keyValue;
    char alternateKeyValue;
} keyboard_S;

typedef struct
{
    mouse_S simpleMouse;
    keyboard_S qwerty;
} laptop_S;

laptop_S tesla =
    {
        .simpleMouse =
            {
                .leftButton = false,
                .rightButton = false,
                .middleButton = false,
                .mouseOn = false,
                .direction = MOUSE_NONE,
            },
        .qwerty =
            {
                .keyValue = '5',
                .alternateKeyValue = '%'},
};

void structMath()
{
    laptop_S *laptopPtr = &tesla;
    char *keyValeuPtr = (char *)laptopPtr + sizeof(mouse_S);
    char *alternateKeyValuePtr = keyValeuPtr + sizeof(char);
}

#include <stddef.h>
#define offsetof(type, member) ((size_t)&((type *)0)->member)
void structMath()
{
    laptop_S *laptopPtr = &tesla;
    char *keyValuePtr = (char *)laptopPtr + offsetof(laptop_S, qwerty) + offsetof(keyboard_S, keyValue);
    char *alternateKeyValuePtr = (char *)laptopPtr + offsetof(laptop_S, qwerty) + offsetof(keyboard_S, alternateKeyValue);

    printf("keyValue: %c\n", *keyValuePtr);
    printf("alternateKeyValue: %c\n", *alternateKeyValuePtr);
}

////////////////////////////////////////////////////////////////////////////////
// 6) Hysteresis
////////////////////////////////////////////////////////////////////////////////
//
// heatingRequired
//
//  This function indicates whether heating is required to maintain a set
//  temperature, based on the current heater request state (initially off),
//  specified set temperature and the current temperature.  The implementation
//  should have 1 degree of hysteresis around the set temperature to prevent
//  excessive toggling of the heater.  I.e., If the heater is already on, it
//  shall stay on within the range of [setTemp - 1 degC, setTemp + 1 degC].
//
//  arguments:
//   setTempHalfDeg - The set temperature in half-degree increments
//   curTempHalfDeg - The current temperature in half-degree increments
//
//  returns:
//   boolean indicating whether or not the heater should be active
//
bool heatingRequired(int setTempHalfDeg, int curTempHalfDeg, bool heaterOn)
{
    int setTemp = setTempHalfDeg / 2;
    int curTemp = curTempHalfDeg / 2;

    if (heaterOn)
    {
        // Heater stays on within the range [setTemp - 1, setTemp + 1]
        if (curTemp >= setTemp - 1 && curTemp <= setTemp + 1)
        {
            return true;
        }
    }
    else
    {
        // Heater turns on if current temperature is below setTemp - 1
        if (curTemp < setTemp - 1)
        {
            return true;
        }
    }

    return false;
}

////////////////////////////////////////////////////////////////////////////////
// 7) Nibble Swap
////////////////////////////////////////////////////////////////////////////////
// The messaging protocol used by certain vehicle controllers requires that all
// nibbles in data payloads be swapped (e.g. 0x1234 -> 0x2143). Write a function
// that takes an unsigned 64-bit integer and swaps the nibbles like so:
// 0x0123456789ABCDEF to 0x1032547698BADCFE. The function should be independent
// of machine endianness.

#include <stdint.h>
#include <stdio.h>

uint64_t payload_nibble_swap(uint64_t p)
{
    uint64_t nibbleSwappedVal = 0;

    for (int i = 0; i < 16; i++)
    {
        // Extract the nibble at position i
        uint64_t nibble = (p >> (i * 4)) & 0xF;
        // Place the nibble in the swapped position
        nibbleSwappedVal |= nibble << ((i ^ 1) * 4);
    }

    return nibbleSwappedVal;
}

uint64_t payload_nibble_swap(uint64_t p)
{
    // Create masks for odd and even nibbles
    uint64_t odd_mask = 0xF0F0F0F0F0F0F0F0ULL;  // Bits 4-7, 12-15, etc
    uint64_t even_mask = 0x0F0F0F0F0F0F0F0FULL; // Bits 0-3, 8-11, etc

    // Extract and shift odd/even nibbles
    uint64_t odd_nibbles = (p & odd_mask) >> 4;   // Shift right
    uint64_t even_nibbles = (p & even_mask) << 4; // Shift left

    // Combine the results
    return odd_nibbles | even_nibbles;
}

int main()
{
    uint64_t p = 0x0123456789ABCDEF;
    uint64_t swapped = payload_nibble_swap(p);
    printf("Original: 0x%016llX\n", p);
    printf("Swapped: 0x%016llX\n", swapped);
    return 0;
}

////////////////////////////////////////////////////////////////////////////////
// 8a) Braking Check
////////////////////////////////////////////////////////////////////////////////
// Design an input checker for a function that is used in an extremely safety
// critical braking system. This function takes two arguments, a pointer
// to a memory location that contains the distance to an obstacle in meters and
// a signed integer that is the closure rate in m/s.
//
// Implement the functions brakes_checkPointerAddr() and
// brakes_checkPointerData() so that the data used by the emergency braking
// calculation is guaranteed to be safe.
//

/*
 * @param distancePtr - int32_t pointer to data to be used
 *
 * returns true if pointer is non-NULL, 4 byte aligned
 * and in the range 0x1000 to 0xF000, false otherwise
 */
bool brakes_checkPointerAddr(int32_t *distancePtr)
{
    // Check if the pointer is non-NULL
    if (distancePtr == NULL)
    {
        return false;
    }

    // Check if the pointer is 4-byte aligned
    if (((uintptr_t)distancePtr % 4) != 0)
    {
        return false;
    }

    // Check if the pointer is within the range 0x1000 to 0xF000
    if ((uintptr_t)distancePtr < 0x1000 || (uintptr_t)distancePtr > 0xF000)
    {
        return false;
    }

    return true;
}

/*
 * @param distancePtr - int32_t pointer to data to be used (guaranteed to be non-NULL)
 *
 * returns true if data value is positive, non-zero and not
 * equal to the sentinel value 0x7FFFFFFF, false otherwise
 */
bool brakes_checkPointerData(int32_t *distancePtr)
{
    // Check if the data value is positive, non-zero, and not equal to 0x7FFFFFFF
    if (*distancePtr > 0 && *distancePtr != 0x7FFFFFFF)
    {
        return true;
    }
    return false;
}

#define CLOSURE_RATE_THRESH 20U
#define DISTANCE_THRESH 100

/*
 * @param distancePtr - int32_t pointer to data to be used
 * @param closureRate - int32_t variable with the current closure rate in m/s
 *
 * returns TRUE if input data is valid and less than the
 * DISTANCE_THRESH constant and the closureRate is greater than the
 * CLOSURE_RATE_THRESH, FALSE otherwise
 */
bool brakes_activateEmergencyBraking(int32_t *distancePtr, int32_t closureRate)
{
    bool activateBrakes = false;
    if (brakes_checkPointerAddr(distancePtr))
    {
        if (brakes_checkPointerData(distancePtr))
        {
            if ((*distancePtr < DISTANCE_THRESH) && (closureRate > CLOSURE_RATE_THRESH))
            {
                activateBrakes = true;
            }
        }
    }
    return activateBrakes;
}

////////////////////////////////////////////////////////////////////////////////
// 8b) Braking Check Part 2
////////////////////////////////////////////////////////////////////////////////
//
// While testing the implementation for brakes_activateEmergencyBraking() above,
// an engineer discovered that there were cases where the closureRate was below
// the threshold, but an event was triggered.  Please explain what could have
// gone wrong and why.
//
/*
To address the issue where the brakes_activateEmergencyBraking() function triggers an event even when the closureRate is below the threshold, we need to consider potential causes. Here are some possible explanations:

Incorrect Comparison Logic:

The function might have a bug in the logic that compares the closureRate to the threshold. For example, using <= instead of < could cause the function to trigger an event at the threshold value.
Data Type Overflow/Underflow:

If the closureRate is stored in a data type that cannot handle the range of values correctly, it might cause overflow or underflow, leading to incorrect comparisons.
Precision Issues:

If the closureRate is a floating-point number, precision issues might cause unexpected behavior. For example, small inaccuracies in floating-point arithmetic could result in a value being slightly above the threshold when it should be below.
Race Conditions:

If the closureRate is updated by another thread or interrupt, a race condition might cause the value to be read incorrectly, leading to an incorrect event trigger.
Incorrect Initialization or Update:

The closureRate might not be initialized or updated correctly, leading to incorrect values being used in the comparison.
External Factors:

External factors such as sensor noise or glitches might cause the closureRate to temporarily spike above the threshold, triggering an event.
To diagnose and fix the issue, the engineer should:

Review the comparison logic in the brakes_activateEmergencyBraking() function.
Ensure that the closureRate is stored in an appropriate data type.
Check for precision issues if using floating-point arithmetic.
Ensure proper synchronization if closureRate is accessed by multiple threads.
Verify the initialization and update logic for closureRate.
Consider filtering or debouncing the closureRate to handle sensor noise or glitches.
By addressing these potential issues, the engineer can ensure that the brakes_activateEmergencyBraking() function behaves as expected and only triggers an event when the closureRate is truly above the threshold.
*/

////////////////////////////////////////////////////////////////////////////////
// 9) State Machine
////////////////////////////////////////////////////////////////////////////////
//
// Write a function to implement the state machine shown in the diagram below.
//  * The initial state of the state machine should be A
//  * State machine input is provided as an argument to the function
//  * The function should output the current state of the state machine
//
//
//     Input = 1   +---------+   Input = 4
//   +------------>|         |<------------+
//   |             | State A |             |
//   |  Input = 2  |         |  Input = 3  |
//   |   +-------- +---------+ --------+   |
//   |   |                             |   |
//   |   V                             V   |
// +---------+      Input = 6      +---------+
// |         |<--------------------|         |
// | State C |                     | State B |
// |         |-------------------->|         |
// +---------+      Input = 5      +---------+
//
//                                 +---------+
//              Input =            |         |
//              Unexpected Value   |  FAULT  |
//             +------------------>|         |
//                                 +---------+
//

#include <stdio.h>

typedef enum
{
    STATE_A,
    STATE_B,
    STATE_C,
    STATE_FAULT
} State;

State stateMachine(int input)
{
    static State currentState = STATE_A;

    switch (currentState)
    {
    case STATE_A:
        if (input == 2)
        {
            currentState = STATE_C;
        }
        else if (input == 3)
        {
            currentState = STATE_B;
        }
        else
        {
            currentState = STATE_FAULT;
        }
        break;

    case STATE_B:
        if (input == 4)
        {
            currentState = STATE_A;
        }
        else if (input == 6)
        {
            currentState = STATE_C;
        }
        else
        {
            currentState = STATE_FAULT;
        }
        break;

    case STATE_C:
        if (input == 1)
        {
            currentState = STATE_A;
        }
        else if (input == 5)
        {
            currentState = STATE_B;
        }
        else
        {
            currentState = STATE_FAULT;
        }
        break;
    case STATE_FAULT:
        // Remain in FAULT state for any input
        break;

    default:
        currentState = STATE_FAULT;
        break;
    }

    return currentState;
}

int main()
{
    int inputs[] = {1, 5, 6, 2, 6, 3, 4, 7}; // Example inputs
    int numInputs = sizeof(inputs) / sizeof(inputs[0]);

    for (int i = 0; i < numInputs; i++)
    {
        State currentState = stateMachine(inputs[i]);
        printf("Input: %d, Current State: %d\n", inputs[i], currentState);
    }

    return 0;
}