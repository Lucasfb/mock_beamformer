/*
 * data_acquisition.h
 *
 *  Created on: 20 de jun de 2022
 *      Author: lucas
 */

#ifndef DATA_ACQUISITION_H_
#define DATA_ACQUISITION_H_

#include <FreeRTOS.h>
#include <queue.h>

QueueHandle_t xQueueDataMic1,xQueueDataMic2,xQueueDataMic3,xQueueDataMic4;

extern void *dataAcquisitionTask(void *arg0);



#endif /* DATA_ACQUISITION_H_ */
