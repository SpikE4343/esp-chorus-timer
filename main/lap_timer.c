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

static PilotLapData_t allPilotLapData[MAX_RX_COUNT];

void lapTimerTask(void *arg);

void lapTimerInit(LapTimerConfig_t *info)
{
    config = info;

    // init sub modules
    rssiInit(&config->rssiReader);
    rxInit(&config->rxController);

    xTaskCreate(lapTimerTask, "lapTimerTask", 1024 * 3, NULL, 10, NULL);
}

void lapTimerSetupPilotRx()
{
    for(int p=0;p<config->pilotCount;++p)
    {
        PilotConfig_t* pilot = &config->pilots[p];
        rxSetState(
            pilot->id, 
            pilot->band, 
            pilot->channel);
    }
}

void lapTimerSetup()
{
    assert(config->pilotCount == config->rssiReader.channelCount);
    memset(&allPilotLapData, 0, sizeof(allPilotLapData));

    lapTimerSetupPilotRx();
}

inline uint32_t millis()
{
    return xTaskGetTickCount() * (1000 / configTICK_RATE_HZ);
}

void lapTimerUpdatePilot(PilotConfig_t *pilot, PilotLapData_t* lapData, float rssi, uint32_t now)
{
    // potential passing
    uint32_t last = lapData->timesCount ? lapData->times[lapData->timesCount - 1] : 0;
    uint32_t lapTime = now - last;

    // not passed threshold rssi value to count as a passing
    if (rssi < (float)pilot->threshold)
        return;

    if (lapData->timesCount > 0)
    {
        float seconds = (float)lapTime / 1000;
        printf("pilot: %u, lap: %f, rssi:%f\n", pilot->id, seconds, rssi);
    }

    // not long enough since the last to register a new time (cool down period)
    if (lapTime < config->minLapTime)
        return;

    lapData->times[lapData->timesCount++] = now;

    // not enough data to count a lap
    if (lapData->timesCount < 2)
        return;

    // A lap occurred
    float seconds = (float)lapTime / 1000;
    printf("Pilot: %u, lap: %f\n", pilot->id, seconds);
}

void lapTimerTask(void *arg)
{
    lapTimerSetup();

    while (1)
    {
        assert(config->pilotCount == config->rssiReader.channelCount);

        float *rssi_readings = rssiReadings();
        uint32_t now = millis();
        for (int i = 0; i < config->pilotCount; ++i)
        {
            PilotConfig_t *pilot = &config->pilots[i];
            float rssi = rssi_readings[i];

            lapTimerUpdatePilot(pilot, &allPilotLapData[i], rssi, now);
        }

        // TODO: queue readings
        vTaskDelay(config->updateDelay / portTICK_PERIOD_MS);
    }
}
