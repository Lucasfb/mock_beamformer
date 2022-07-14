/*
 * beamformer.h
 *
 *  Created on: 22 de jun de 2022
 *      Author: lucas
 */

#ifndef BEAMFORMER_H_
#define BEAMFORMER_H_

#include <FreeRTOS.h>
#include <queue.h>

#include "data_acquisition.h"


extern void *beamformerTask(void *arg0);




#endif /* BEAMFORMER_H_ */
