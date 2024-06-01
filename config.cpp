// config.cpp
#include "config.h"

// 0.5 segundos (500,000 microsegundos) -> usleep(500000);
// 1 segundos -> usleep(1000000);
// 50 Hz -> 20000   HIGH_FREQ
// 5 Hz -> 200000   LOW_FREQ

int INITIAL_WAIT = 3000000;
int HIGH_FREQ_WAIT = 200000;
int LOW_FREQ_WAIT = 2000000;
int SKIP_FACTOR = LOW_FREQ_WAIT / HIGH_FREQ_WAIT;
int STATE_GENERAL_DURATION = LOW_FREQ_WAIT;

int STATE_FSR_DURATION = 0;
int STATE_IMU_DURATION = 0;
int STATE_RAM_DURATION = 0;
int STATE_BLE_DURATION = 0;
int STATE_ENERGY_DURATION = 0;
int STATE_CUSTOM_DURATION = 0;
int RESOURCE_RTC_DURATION = 100000;
int RAM_BUFFER_RATIO_REFRESH = STATE_GENERAL_DURATION / 4;

float INTENSITY_CONSUMED = 0;

// Definiciones de las posiciones de los grupos FSR
std::vector<int> fsr_in_distal_phalanges = {20, 4, 23, 7, 6};
std::vector<int> fsr_in_mid_proximal_phalanges = {21, 16, 22, 19, 3, 5, 15};
std::vector<int> fsr_in_metatarsals = {0, 1, 2, 13, 14, 17, 18};
std::vector<int> fsr_in_tarsometatarsals = {10, 11, 12};
std::vector<int> fsr_in_calcaneus_talus = {8, 9, 31, 28, 25, 24, 27, 26, 29, 30};

std::vector<int> imu_acc_x = {0};
std::vector<int> imu_acc_y = {1};
std::vector<int> imu_acc_z = {2};

std::vector<int> imu_gyro_x = {3};
std::vector<int> imu_gyro_y = {4};
std::vector<int> imu_gyro_z = {5};
