/// config.h
#ifndef CONFIG_H
#define CONFIG_H
// 0.5 segundos (500,000 microsegundos) -> usleep(500000);
// 1 segundos -> usleep(1000000);

#define BUFFER_SIZE 16

extern int TLB;
extern int PCK;
extern int INITIAL_WAIT;
extern int STATE_GENERAL_DURATION;
extern int STATE_FSR_DURATION;
extern int STATE_IMU_DURATION;
extern int STATE_RAM_DURATION;
extern int STATE_BLE_DURATION;
extern int STATE_ENERGY_DURATION;
extern int STATE_CUSTOM_DURATION;
extern int RESOURCE_RTC_DURATION;
extern int RAM_BUFFER_RATIO_REFRESH;

#endif // CONFIG_H
