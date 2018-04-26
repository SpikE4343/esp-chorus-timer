
#include "driver/gpio.h"

#define MAX_LAP_COUNT 64 
#define MAX_PILOT_NAME_LEN 32

#define MAX_PILOT_COUNT 32

#define MAX_RACE_PILOT_COUNT 8
#define MAX_RACE_COUNT 64

typedef enum
{
    LAP_TIMER_STATE_STARTUP = 0,
    LAP_TIMER_STATE_ACTIVE
} LapTimerState_t;

typedef enum
{   
    RACE_STATE_INIT = 0,
    RACE_STATE_STARTING_WAIT,
    RACE_STATE_RUNNING,
    RACE_STATE_TIME_UP,
    RACE_STATE_COMPLETE
} RaceState_t;

typedef struct 
{
    uint8_t id;
    uint8_t band;
    uint8_t channel;
    uint16_t threshold;
} DeviceConfig_t;

typedef struct
{
    DeviceConfig_t* config;
    uint8_t status;
} Device_t;

typedef struct
{
    uint8_t race;
    float time;
} Lap_t;

typedef struct
{
    uint8_t id;
    uint8_t lapCount;
    uint8_t bestLap;
    uint8_t raceStartLap;

    DeviceConfig_t device;

    char name[MAX_NAME_LEN];
    Lap_t laps[MAX_LAP_COUNT];
    
    
} Pilot_t;

typedef struct
{
    uint8_t type;
    uint8_t status;
    
    uint8_t maxLaps;
    uint8_t pilotCount;    

    uint8_t pilots[MAX_RACE_PILOT_COUNT];
    uint8_t rank[MAX_RACE_PILOT_COUNT];
    uint8_t rankCount;
    
    uint16_t minRaceTime;
} Race_t;

typedef struct 
{
    uint16_t        minLapTime;
    uint8_t         pilotCount;
    uint8_t         raceCount;
    uint8_t         deviceCount;

    Pilot_t         pilots[MAX_PILOT_COUNT];    
    Race_t          races[MAX_RACE_COUNT];
    Device_t        devices[MAX_DEVICE_COUNT];

} LapTimer_t;


void lapTimerInit(LapTimerConfig_t* info);
void lapTimerUpdatePilotConfig(PilotConfig_t* pilot);
