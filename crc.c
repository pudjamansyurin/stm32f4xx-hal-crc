/*
 * crc.c
 *
 *  Created on: May 10, 2022
 *      Author: pujak
 */
#include "crc.h"
#include "string.h"

extern CRC_HandleTypeDef hcrc;

/* Private function declarations */
static uint32_t pack(uint8_t *u8p_buffer, uint8_t u8_count);

/* Public function definitions */
uint32_t crc_calculate(uint8_t *u8p_buffer, uint16_t u16_size)
{
  uint16_t u16_count, u16_rest;
  uint32_t u32_value = 0;

  /* Calculate number of 32-bit blocks */
  u16_count = u16_size >> 2;
  if (u16_count > 0)
  {
    u32_value = HAL_CRC_Calculate(&hcrc, (uint32_t*) u8p_buffer, u16_count);
    u8p_buffer += u16_count << 2;
  }

  /* Calculate remaining as 8-bit block*/
  u16_rest = u16_size % 4;
  if (u16_rest > 0)
  {
    /* Pack data to 32-bit */
    u32_value = pack(u8p_buffer, u16_rest);

    /* Calculate last value */
    if (u16_count == 0)
      u32_value = HAL_CRC_Calculate(&hcrc, &u32_value, 1);
    else
      u32_value = HAL_CRC_Accumulate(&hcrc, &u32_value, 1);
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

/* Private function definitions */
static uint32_t pack(uint8_t *u8p_buffer, uint8_t u8_count)
{
  uint8_t u8_arrRemaining[4];

  memset(u8_arrRemaining, 0, sizeof(u8_arrRemaining));

  for (uint8_t u8_i = 0; u8_i < u8_count; u8_i++)
    u8_arrRemaining[u8_i] = *u8p_buffer++;

  return (*(uint32_t*) u8_arrRemaining);
}
