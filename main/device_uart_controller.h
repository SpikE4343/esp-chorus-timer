//

#ifndef _device_uart_INCLUDED_
#define _device_uart_INCLUDED_



typedef struct
{
  uint8_t txPin;
  uint8_t rxPin;
  uint32_t baud;
} DeviceUartConfig_t;

void deviceUartInit(DeviceUartConfig_t* config);

#endif