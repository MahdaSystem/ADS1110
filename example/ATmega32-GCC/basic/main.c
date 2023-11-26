/**
 **********************************************************************************
 * @file   main.c
 * @author Hossein.M (https://github.com/Hossein-M98)
 * @brief  example code for ADS1110 Driver (for ATmega32)
 **********************************************************************************
 *
 * Copyright (c) 2023 Mahda Embedded System (MIT License)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 **********************************************************************************
 */

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include "Retarget.h"
#include "ADS1110.h"
#include "ADS1110_platform.h"


int main(void)
{
  ADS1110_Handler_t Handler = {0};
  ADS1110_Sample_t  Sample = {0};

  Retarget_Init(F_CPU, 9600);
  printf("ADS1110 Driver Example\r\n\r\n");

  ADS1110_Platform_Init(&Handler);
  ADS1110_Init(&Handler, ADS1110_ADDRESS_A0);
  ADS1110_SetMode(&Handler, ADS1110_MODE_SINGLESHOT);
  ADS1110_SetGain(&Handler, ADS1110_GAIN_1);
  ADS1110_SetRate(&Handler, ADS1110_RATE_15MPS);

  while (1)
  {
    ADS1110_StartConversion(&Handler);
    while (ADS1110_CheckDataReady(&Handler) == ADS1110_DATA_NOT_READY)
      _delay_ms(1);

    ADS1110_ReadSample(&Handler, &Sample);
    printf("Voltage: %fV\r\n", Sample.Voltage);

    _delay_ms(1000);
  }

  ADS1110_DeInit(&Handler);
  return 0;
}
