//
#include "lap_timer.h"


#define COUNT 1

static LapTimerConfig_t config;
void app_main()
{
    config.updateDelayMs = 100;
    lapTimerInit(&config);
}