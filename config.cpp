// config.cpp
#include "config.h"

// 0.5 segundos (500,000 microsegundos) -> usleep(500000);
// 1 segundos -> usleep(1000000);
// 50 Hz -> 20000   HIGH_FREQ
// 5 Hz -> 200000   LOW_FREQ

// 85.54 de adquisicion de datos
// 200mA en 24 horas
// 8.33mAh
// 0.0023148148 mAs
// 0.00000231148 mAms
// 0.00000000231148 mAmicros
// 50 Hz -> 20000*0.00000000231148 = 0.0000462296 mA po 50Hz

int INITIAL_WAIT = 3000000;
int HIGH_FREQ_WAIT = 20000;
int LOW_FREQ_WAIT = HIGH_FREQ_WAIT * COEFFICIENT_RTC;

int COEFFICIENT_RTC = 1; // COEFFICIENT_RTC (1 desasctivado)
int STATE_GENERAL_DURATION = HIGH_FREQ_WAIT;

int STATE_FSR_DURATION = HIGH_FREQ_WAIT;
int STATE_IMU_DURATION = HIGH_FREQ_WAIT;
int STATE_RAM_DURATION = HIGH_FREQ_WAIT;
int STATE_BLE_DURATION = HIGH_FREQ_WAIT;
int STATE_ENERGY_DURATION = HIGH_FREQ_WAIT;
int STATE_CUSTOM_DURATION = HIGH_FREQ_WAIT;

int RESOURCE_RTC_DURATION = STATE_GENERAL_DURATION;
// µA/ms
float INTENSITY_CONSUMED = 0;
float STATE_GENERAL_INTENSITY = 0.008464846;
float STATE_IMU_INTENSITY = 0.0118507844; // STATE_GENERAL_INTENSITY*1.4
float STATE_ENERGY_INTENSITY = 0.000462296;
float CYCLE_INTENSITY = STATE_GENERAL_INTENSITY * 4 + STATE_IMU_INTENSITY + STATE_ENERGY_INTENSITY;

bool terminateFlag = false;
bool classifierWorking = true;
bool realSimulation = true;

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
