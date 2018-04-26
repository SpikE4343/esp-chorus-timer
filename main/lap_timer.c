/* SPI Slave example, sender (uses SPI master driver)

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "lap_timer.h"

static LapTimerConfig_t *config;

static LapTimer_t* timer;

void lapTimerTask(void *arg);


void lapTimerInit(LapTimerConfig_t *info)
{
    config = info;

    xTaskCreate(lapTimerTask, "lapTimerTask", 1024 * 3, NULL, 10, NULL);
}


void lapTimerSetup()
{
    memset(&timer, 0, sizeof(LapTimer_t));
}


inline uint32_t millis()
{
    return xTaskGetTickCount() * (1000 / configTICK_RATE_HZ);
}

void lapTimerUpdate()
{

}

void lapTimerTask(void *arg)
{
    lapTimerSetup();

    while (1)
    {
        lapTimerUpdate();
        vTaskDelay(config->updateDelayMs / portTICK_PERIOD_MS);
    }
}
