/// config.h
#ifndef CONFIG_H
#define CONFIG_H
// 0.5 segundos (500,000 microsegundos) -> usleep(500000);
// 1 segundos -> usleep(1000000);

// #define STATE_GENERAL_DURATION 100000
#define TLB 4
#define PCK 2
#define BUFFER_SIZE 16

#define INITIAL_WAIT 1000000

#define STATE_GENERAL_DURATION 500000
#define STATE_FSR_DURATION 0
#define STATE_IMU_DURATION 0
#define STATE_RAM_DURATION 0
#define STATE_BLE_DURATION 0
#define STATE_ENERGY_DURATION 0
#define STATE_CUSTOM_DURATION 0

#define RESOURCE_RTC_DURATION 100000

#define RAM_BUFFER_RATIO_REFRESH 100000

#endif // CONFIG_H
