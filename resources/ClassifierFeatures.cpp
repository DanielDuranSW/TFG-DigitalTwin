// ClasifierFeatures.cpp
#include "ClassifierFeatures.h"

ClassifierFeatures::ClassifierFeatures() {}

ClassifierFeatures::~ClassifierFeatures() {}

void ClassifierFeatures::Feature1(std::vector<int> buffer_fsr_in_distal_phalanges, std::vector<int> buffer_fsr_in_mid_proximal_phalanges, std::vector<int> buffer_fsr_in_metatarsals, std::vector<int> buffer_fsr_in_tarsometatarsals, std::vector<int> buffer_fsr_in_calcaneus_talus, std::vector<int> buffer_imu_in_x, std::vector<int> buffer_imu_in_y, std::vector<int> buffer_imu_in_z)
{
    // Calcular la media de cada buffer
    int mean_distal_phalanges = calculateMean(buffer_fsr_in_distal_phalanges);
    int mean_mid_proximal_phalanges = calculateMean(buffer_fsr_in_mid_proximal_phalanges);
    int mean_metatarsals = calculateMean(buffer_fsr_in_metatarsals);
    int mean_tarsometatarsals = calculateMean(buffer_fsr_in_tarsometatarsals);
    int mean_calcaneus_talus = calculateMean(buffer_fsr_in_calcaneus_talus);
    int mean_imu_x = calculateMean(buffer_imu_in_x);
    int mean_imu_y = calculateMean(buffer_imu_in_y);
    int mean_imu_z = calculateMean(buffer_imu_in_z);

    // Utilizar los valores de media como sea necesario en el resto del método
    // Por ejemplo:
    printf("FEATUREEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE\n");
    printf("Mean distal phalanges: %d\n", mean_distal_phalanges);
    printf("Mean mid proximal phalanges: %d\n", mean_mid_proximal_phalanges);
    printf("Mean metatarsals: %d\n", mean_metatarsals);
    printf("Mean tarsometatarsals: %d\n", mean_tarsometatarsals);
    printf("Mean calcaneus talus: %d\n", mean_calcaneus_talus);
    printf("Mean IMU X: %d\n", mean_imu_x);
    printf("Mean IMU Y: %d\n", mean_imu_y);
    printf("Mean IMU Z: %d\n", mean_imu_z);
}

int ClassifierFeatures::calculateMean(const std::vector<int> &buffer)
{

    long long sum = 0;
    for (int value : buffer)
    {
        sum += value;
    }

    return static_cast<int>(sum / static_cast<long long>(buffer.size()));
}
