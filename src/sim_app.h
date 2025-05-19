

#ifndef _SIM_APP_H
#define _SIM_APP_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>


// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Type Definitions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Application states

  Summary:
    Application states enumeration

  Description:
    This enumeration defines the valid application states.  These states
    determine the behavior of the application at various times.
*/

typedef enum
{
    /* Application's state machine's initial state. */
    SIM_APP_STATE_INIT=0,
    SIM_APP_STATE_SERVICE_TASKS,
    /* TODO: Define states used by the application state machine. */

} SIM_APP_STATES;

// Simulated Socket Struct
typedef struct
{
    /* The application's current state */
    int      sock;
    int      csock;
    bool     connected;

} SIM_SOCKET_DATA;

// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    Application strings and buffers are be defined outside this structure.
 */

typedef struct
{
    /* The application's current state */
    SIM_APP_STATES state;

    /* TODO: Define any additional data used by the application. */

} SIM_APP_DATA;

int REGISTER_SOCK(char* SERVERNAME, int PORT);

void SIM_APP_Initialize ( void );


void SIM_APP_Tasks( void );
void ATTEMPT_CONNECTION(SIM_SOCKET_DATA* U);


size_t UART2_Write(uint8_t* pWrBuffer, const size_t size);
size_t UART2_Read(uint8_t* pRdBuffer, const size_t size);

size_t UART3_Write(uint8_t* pWrBuffer, const size_t size);
size_t UART3_Read(uint8_t* pRdBuffer, const size_t size);



//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif /* _SIM_APP_H */

/*******************************************************************************
 End of File
 */

