//
#include "lap_timer.h"

static LapTimerConfig_t config;

#define COUNT 1

void app_main()
{
    config.rxController.rxCount = COUNT;
    config.rxController.spiOutputPin = 25;
    config.rxController.spiClockPin = 26;
    config.rxController.spiSelectPin[0] = 27;
    config.rxController.spiSelectPin[1] = 21;
    config.rxController.spiSelectPin[2] = 33;
    config.rxController.spiSelectPin[3] = 32;
    config.rxController.spiClockSpeed = 5000000;

    config.rssiReader.lpfCutoffHz = 100;
    config.rssiReader.updateDelay = 1;
    config.rssiReader.channelCount = COUNT;
    config.rssiReader.bitWidth = ADC_WIDTH_12Bit;
    config.rssiReader.attenuation = ADC_ATTEN_6db;
    config.rssiReader.channels[0] = 0;
    config.rssiReader.channels[1] = 1;
    config.rssiReader.channels[2] = 2;
    config.rssiReader.channels[3] = 3;

    config.pilotCount = COUNT;
    config.minLapTime = 5000;
    config.pilots[0].id = 0;
    config.pilots[0].band = 0;
    config.pilots[0].channel = 8;
    config.pilots[0].threshold = 800;
    config.pilots[1].id = 1;
    config.pilots[1].threshold = 512;
    config.pilots[2].id = 2;
    config.pilots[2].threshold = 512;
    config.pilots[3].id = 3;
    config.pilots[3].threshold = 512;
    config.updateDelay = 5;
    
    lapTimerInit(&config);
}