// LowLevelActivityClassifier.cpp

#include "LowLevelActivityClassifier.h"

void *low_level_activity_classifier_run(void *arg)
{
    Instances *args = static_cast<Instances *>(arg);
    State *state = &(args->state);

    // Buffer para almacenar las medias calculadas
    std::vector<double> buffer_fsr_in_distal_phalanges;
    std::vector<double> buffer_fsr_in_mid_proximal_phalanges;
    std::vector<double> buffer_fsr_in_metatarsals;
    std::vector<double> buffer_fsr_in_tarsometatarsals;
    std::vector<double> buffer_fsr_in_calcaneus_talus;

    while (true)
    {
        state->lockMutex();
        state->waitConditionLLAC();

        // Recibe los datos de fsr e imu:
        std::vector<int> fsrData = args->fsrData;
        std::vector<int> imuData = args->imuData;

        // Procesar los datos de fsr en bloques de 32
        size_t dataSize = fsrData.size();
        for (size_t i = 0; i < dataSize; i += 32)
        {
            std::vector<int> block(fsrData.begin() + i, fsrData.begin() + std::min(i + 32, dataSize));

            if (block.size() == 32)
            {
                double mean_distal_phalanges = calculateMean(block, fsr_in_distal_phalanges);
                double mean_mid_proximal_phalanges = calculateMean(block, fsr_in_mid_proximal_phalanges);
                double mean_metatarsals = calculateMean(block, fsr_in_metatarsals);
                double mean_tarsometatarsals = calculateMean(block, fsr_in_tarsometatarsals);
                double mean_calcaneus_talus = calculateMean(block, fsr_in_calcaneus_talus);
                printf("Empieza la MATRACAAAAAAAAAAAAAa\n");
                printVector(fsrData, "fsrData");
                printVector(block, "block");
                printVector(fsr_in_distal_phalanges, "VECTORDEDISTAL");
                printf("Mean distal phalanges: %f\n", mean_distal_phalanges);
                buffer_fsr_in_distal_phalanges.push_back(mean_distal_phalanges);
                buffer_fsr_in_mid_proximal_phalanges.push_back(mean_mid_proximal_phalanges);
                buffer_fsr_in_metatarsals.push_back(mean_metatarsals);
                buffer_fsr_in_tarsometatarsals.push_back(mean_tarsometatarsals);
                buffer_fsr_in_calcaneus_talus.push_back(mean_calcaneus_talus);
            }
        }

        state->unlockMutex();
    }
    pthread_exit(NULL);
}

double calculateMean(const std::vector<int> &data, const std::vector<int> &positions)
{
    double sum = 0.0;
    for (int pos : positions)
    {
        if (pos < data.size())
        {
            sum += data[pos];
        }
    }
    return sum / positions.size();
}

void printVector(const std::vector<int> &vec, const char *vecName)
{
    printf("%s: [", vecName);
    for (size_t i = 0; i < vec.size(); ++i)
    {
        printf("%d", vec[i]);
        if (i < vec.size() - 1)
        {
            printf(", ");
        }
    }
    printf("]\n");
}