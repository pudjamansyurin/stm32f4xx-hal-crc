/*
 * crc.c
 *
 *  Created on: May 10, 2022
 *      Author: pujak
 */
#include "crc.h"
#include "string.h"

extern CRC_HandleTypeDef hcrc;

/* Public function definitions */
uint32_t crc_calculate(uint8_t *u8p_buffer, uint16_t u16_size)
{
  uint8_t u8_arrRemaining[4];
  uint16_t u16_count;
  uint32_t u32_value;

  memset(u8_arrRemaining, 0, sizeof(u8_arrRemaining));

  /* Calculate number of 32-bit blocks */
  u16_count = u16_size >> 2;
  u32_value = HAL_CRC_Calculate(&hcrc, (uint32_t*) u8p_buffer, u16_count);

  /* Calculate the rest */
  u16_count = u16_size % 4;

  /* Calculate remaining as 8-bit */
  if (u16_count)
  {
    /* Pack data to 32-bit */
    for (uint8_t u8_i = 0; u8_i < u16_count; u8_i++)
      u8_arrRemaining[u8_i] = *u8p_buffer++;

    /* Accumulate with last value */
    u32_value = HAL_CRC_Accumulate(&hcrc, (uint32_t*) u8_arrRemaining, 1);
  }

  return (u32_value);
}

HAL_StatusTypeDef crc_suspend(FunctionalState suspend)
{
  HAL_StatusTypeDef status;

  if (ENABLE == suspend)
    status = HAL_CRC_DeInit(&hcrc);
  else
    status = HAL_CRC_Init(&hcrc);

  return (status);
}
