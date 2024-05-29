/// config.h
#ifndef CONFIG_H
#define CONFIG_H

#include <vector>

#define BUFFER_SIZE 16
#define BUFFER_LLAC_SIZE 10
#define FLASH_SIZE 32

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
