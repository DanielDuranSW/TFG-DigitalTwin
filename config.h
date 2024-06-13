/// config.h
#ifndef CONFIG_H
#define CONFIG_H

#include <vector>

#define BUFFER_SIZE 16
#define BUFFER_LLAC_SIZE 128
#define FLASH_SIZE 32
#define linesToRead 1

extern int INITIAL_WAIT;
extern int HIGH_FREQ_WAIT;
extern int LOW_FREQ_WAIT;

extern int COEFFICIENT_RTC;
extern int STATE_GENERAL_DURATION;

extern int STATE_FSR_DURATION;
extern int STATE_IMU_DURATION;
extern int STATE_RAM_DURATION;
extern int STATE_BLE_DURATION;
extern int STATE_ENERGY_DURATION;
extern int STATE_CUSTOM_DURATION;

extern int RESOURCE_RTC_DURATION;

extern float INTENSITY_CONSUMED;
extern float STATE_GENERAL_INTENSITY;
extern float STATE_IMU_INTENSITY;
extern float STATE_ENERGY_INTENSITY;
extern float CYCLE_INTENSITY;

extern bool terminateFlag;
extern bool classifierWorking;
extern bool realSimulation;

extern std::vector<int> fsr_in_distal_phalanges;
extern std::vector<int> fsr_in_mid_proximal_phalanges;
extern std::vector<int> fsr_in_metatarsals;
extern std::vector<int> fsr_in_tarsometatarsals;
extern std::vector<int> fsr_in_calcaneus_talus;

extern std::vector<int> imu_acc_x;
extern std::vector<int> imu_acc_y;
extern std::vector<int> imu_acc_z;

extern std::vector<int> imu_gyro_x;
extern std::vector<int> imu_gyro_y;
extern std::vector<int> imu_gyro_z;

#endif // CONFIG_H
