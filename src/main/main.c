/*
 * This file is part of Cleanflight and Betaflight.
 *
 * Cleanflight and Betaflight are free software. You can redistribute
 * this software and/or modify this software under the terms of the
 * GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * Cleanflight and Betaflight are distributed in the hope that they
 * will be useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software.
 *
 * If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdbool.h>
#include <stdint.h>

#include "platform.h"

#include "fc/init.h"

#include "scheduler/scheduler.h"

// crteensy
#include "drivers/io.h"
#include "stm32h7xx_hal_gpio.h"
// /crteensy

void run(void);

int main(int argc, char * argv[])
{
#ifdef SIMULATOR_BUILD
    targetParseArgs(argc, argv);
#else
    UNUSED(argc);
    UNUSED(argv);
#endif
    init();

    // crteensy
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    /*Configure GPIO pin : PA10 */
    GPIO_InitStruct.Pin = GPIO_PIN_8;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    // /crteensy

//
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);
  while(1)
  {
    HAL_Delay(500);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_RESET);
    HAL_Delay(500);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_SET);

  }
//*/
    run();

    return 0;
}

void FAST_CODE run(void)
{
    while (true) {
        scheduler();
#ifdef SIMULATOR_BUILD
        delayMicroseconds_real(50); // max rate 20kHz
#endif
    }
}
