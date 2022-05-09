/*
 * crc.h
 *
 *  Created on: May 10, 2022
 *      Author: pujak
 */

#ifndef STM32F4XX_HAL_CRC_H_
#define STM32F4XX_HAL_CRC_H_

#include "stm32f4xx_hal.h"

/* Public function declarations */
uint32_t crc_calculate(uint8_t *u8p_buffer, uint16_t u16_size);
HAL_StatusTypeDef crc_suspend(FunctionalState suspend);

#endif /* STM32F4XX_HAL_CRC_H_ */
