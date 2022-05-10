# STM32F4 HAL Cyclic Redundancy Check (CRC)

## How to use the module

#### **`main.c`**

```c
#include "stm32f4xx-hal-crc/crc.h"

#define BUF_SZ  123

uint8_t u8_arrBuffer[BUF_SZ];

int main(void)
{
  uint32_t u32_crcValue;

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_CRC_Init();

  /* Generate random data */
  for(uint8_t u8_i = 0; u8_i < BUF_SZ; u8_i++)
    u8_arrBuffer[u8_i] = u8_i;

  /* Calculate CRC data */
  u32_crcValue = crc_calculate(&u8_arrBuffer[0], BUF_SZ);

  /* Super loop */
  while(1) {
    
  }

  /* DeInit the CRC */
  crc_suspend(ENABLE);
}
```
