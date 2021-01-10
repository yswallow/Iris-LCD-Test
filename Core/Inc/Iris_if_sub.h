/*
 * Iris_if_sub.h
 *
 *  Created on: Jan 8, 2021
 *      Author: Keshikan
 *    Modified: yswallow
 */

#ifndef INC_IRIS_IF_SUB_H_
#define INC_IRIS_IF_SUB_H_

#include <stdint.h>
#include "stm32f4xx_hal.h"
#include "Iris_if_conf.h"
#include "Iris_if.h"

#define IRIS_SUB_SIZ_X (130)
#define IRIS_SUB_SIZ_Y (132)
#define IRIS_SUB_VRAM_SIZ (IRIS_SUB_SIZ_X * IRIS_SUB_SIZ_Y)

extern void sendCmdSub(uint8_t dat);
extern void sendDatSub(uint8_t dat);

extern void initIrisSub();
extern void irisDrawDotSub(uint16_t x, uint16_t y, uint16_t color);
extern void irisClearDispSub();
extern void irisUpdateSub();
//extern void irisSubMain();

#endif /* INC_IRIS_IF_SUB_H_ */
