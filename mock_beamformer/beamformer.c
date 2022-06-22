

#include <unistd.h>
#include <stdint.h>
#include <stddef.h>

#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>

#include <ti/drivers/UART.h>
#include <ti/display/Display.h>

#include "beamformer.h"
#include "data_acquisition.h"


void *beamformerTask(void *arg0)
{

    Display_Handle    handle;
    Display_Params    params;
    Display_Params_init(&params);
    handle = Display_open(Display_Type_UART, &params);


    // Variables that will receive the data from the data acquisition task
    int32_t newDataMic1, newDataMic2, newDataMic3, newDataMic4;

    while(1) {
        if( xQueueReceive( xQueueDataMic1, &newDataMic1,( TickType_t ) 10 ) == pdPASS ){
            Display_printf(handle, 0, 0, "Mic1 = %d", newDataMic1);
        }
        if( xQueueReceive( xQueueDataMic2, &newDataMic2,( TickType_t ) 10 ) == pdPASS ){
            Display_printf(handle, 0, 0, "Mic2 = %d", newDataMic2);
        }
        if( xQueueReceive( xQueueDataMic3,&newDataMic3,( TickType_t ) 10 ) == pdPASS ){
            Display_printf(handle, 0, 0, "Mic3 = %d", newDataMic3);
        }
        if( xQueueReceive( xQueueDataMic4, &newDataMic4,( TickType_t ) 10 ) == pdPASS ){
            Display_printf(handle, 0, 0, "Mic4 = %d", newDataMic4);
        }
    }

    Display_close(handle);

}
