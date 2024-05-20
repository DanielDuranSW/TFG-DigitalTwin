// config.cpp
#include "config.h"

// 0.5 segundos (500,000 microsegundos) -> usleep(500000);
// 1 segundos -> usleep(1000000);

int INITIAL_WAIT = 3000000;
int STATE_GENERAL_DURATION = 500000;
int STATE_FSR_DURATION = 0;
int STATE_IMU_DURATION = 0;
int STATE_RAM_DURATION = 0;
int STATE_BLE_DURATION = 0;
int STATE_ENERGY_DURATION = 0;
int STATE_CUSTOM_DURATION = 0;
int RESOURCE_RTC_DURATION = 1000000;
int RAM_BUFFER_RATIO_REFRESH = STATE_GENERAL_DURATION / 4; // No se usa

// Definiciones de las posiciones de los grupos FSR
std::vector<int> fsr_in_distal_phalanges = {0, 1, 2, 4};
std::vector<int> fsr_in_mid_proximal_phalanges = {29, 30, 31};
std::vector<int> fsr_in_metatarsals = {9, 10, 11, 12};
std::vector<int> fsr_in_tarsometatarsals = {5, 6, 7, 8};
std::vector<int> fsr_in_calcaneus_talus = {13, 14, 15, 16};

std::vector<int> imu_in_x = {0, 3};
std::vector<int> imu_in_y = {1, 4};
std::vector<int> imu_in_z = {2, 5};
