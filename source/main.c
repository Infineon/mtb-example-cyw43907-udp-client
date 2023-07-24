/******************************************************************************
* File Name:   main.c
*
* Description: This is the source code for UDP Client Example in ModusToolbox.
*              The example establishes a connection with a remote UDP server
*              and based on the command received from the UDP server, turns
*              the user LED ON or OFF.
*
* Related Document: See README.md
*
*******************************************************************************
* $ Copyright 2021-2023 Cypress Semiconductor $
*******************************************************************************/

/* Header file includes. */
#include "cyhal.h"
#include "cybsp.h"
#include "cy_retarget_io.h"

/* FreeRTOS header file. */
#include <FreeRTOS.h>
#include <task.h>

/* UDP client task header file. */
#include "udp_client.h"

/*******************************************************************************
* Macros
********************************************************************************/
/* RTOS related macros. */
#define UDP_CLIENT_TASK_STACK_SIZE        (5 * 1024)
#define UDP_CLIENT_TASK_PRIORITY          (1)

/*******************************************************************************
* Global Variables
********************************************************************************/

/* UDP server task handle. */
TaskHandle_t client_task_handle;

/*******************************************************************************
* Function Name: main
********************************************************************************
* Summary:
*  System entrance point. This function sets up user tasks and then starts
*  the RTOS scheduler.
*
* Parameters:
*  void
*
* Return:
*  int
*
*******************************************************************************/
int main(void)
{
    cy_rslt_t result;

    /* Initialize the device and board peripherals */
    result = cybsp_init();
    if (result != CY_RSLT_SUCCESS)
    {
        CY_ASSERT(0);
    }

    /* Enable global interrupts */
    __enable_irq();

    /* Initialize retarget-io to use the debug UART port */
    cy_retarget_io_init(CYBSP_DEBUG_UART_TX, CYBSP_DEBUG_UART_RX, CY_RETARGET_IO_BAUDRATE);

    /* Initialize the User LED */
    cyhal_gpio_init(CYBSP_USER_LED2, CYHAL_GPIO_DIR_OUTPUT, CYHAL_GPIO_DRIVE_STRONG, CYBSP_LED_STATE_OFF);

    /* \x1b[2J\x1b[;H - ANSI ESC sequence to clear screen. */
    printf("\x1b[2J\x1b[;H");
    printf("============================================================\n");
    printf("CYW43907 - UDP Client\n");
    printf("============================================================\n\n");

    /* Create the task for making a UDP Client communicate with a remote
     * UDP Server.
     */
    xTaskCreate(udp_client_task, "Network task", UDP_CLIENT_TASK_STACK_SIZE, NULL,
                UDP_CLIENT_TASK_PRIORITY, &client_task_handle);
    /* Start the FreeRTOS scheduler. */
    vTaskStartScheduler();

    /* Should never get here. */
    CY_ASSERT(0);
}

/* [] END OF FILE */
