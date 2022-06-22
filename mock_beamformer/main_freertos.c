/*
 *  ======== main_freertos.c ========
 */
#include <stdint.h>

#ifdef __ICCARM__
#include <DLib_Threads.h>
#endif


/* RTOS header files */
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>

/* Driver configuration */
#include <ti/drivers/Board.h>


#include "data_acquisition.h"
#include "beamformer.h"
//extern void *dataAcquisitionTask(void *arg0);

/* Stack size in bytes */
#define THREADSTACKSIZE    768 / sizeof(portSTACK_TYPE)

/*
 *  ======== main ========
 */
int main(void)
{
    TaskHandle_t dataAcqHandle,beamformerHandle;
    int retc;

    /* initialize the system locks */
#ifdef __ICCARM__
    __iar_Initlocks();
#endif

    /* Call driver init functions */
    Board_init();

    xQueueDataMic1 = xQueueCreate(16,sizeof(int32_t)); //16 is arbitrary
    xQueueDataMic2 = xQueueCreate(16,sizeof(int32_t)); //16 is arbitrary
    xQueueDataMic3 = xQueueCreate(16,sizeof(int32_t)); //16 is arbitrary
    xQueueDataMic4 = xQueueCreate(16,sizeof(int32_t)); //16 is arbitrary

    if (xQueueDataMic1 == 0 | xQueueDataMic2 == 0| xQueueDataMic3 == 0 | xQueueDataMic4 == 0) {
        // failed to created queues
        while(1){};
    }

    retc = xTaskCreate((TaskFunction_t)dataAcquisitionTask,
                                "data acquisition",
                                THREADSTACKSIZE,
                                NULL,
                                1,
                                &dataAcqHandle);
    if (retc != pdPASS) {
        /* xTaskCreate failed */
        while (1) {}
    }


    retc = xTaskCreate((TaskFunction_t)beamformerTask,
                                "beamformer",
                                THREADSTACKSIZE,
                                NULL,
                                1,
                                &beamformerHandle);
    if (retc != pdPASS) {
        /* xTaskCreate failed */
        while (1) {}
    }

    /* Start the FreeRTOS scheduler */
    vTaskStartScheduler();

    return (0);
}

//*****************************************************************************
//
//! \brief Application defined malloc failed hook
//!
//! \param  none
//!
//! \return none
//!
//*****************************************************************************
void vApplicationMallocFailedHook()
{
    /* Handle Memory Allocation Errors */
    while(1)
    {
    }
}

//*****************************************************************************
//
//! \brief Application defined stack overflow hook
//!
//! \param  none
//!
//! \return none
//!
//*****************************************************************************
void vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName)
{
    //Handle FreeRTOS Stack Overflow
    while(1)
    {
    }
}
