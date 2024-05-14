#include "LowLevelActivityClassifier.h"

// Definiciones de las variables de buffer
std::vector<int> buffer_fsr_in_distal_phalanges(BUFFER_LLAC_SIZE);
std::vector<int> buffer_fsr_in_mid_proximal_phalanges(BUFFER_LLAC_SIZE);
std::vector<int> buffer_fsr_in_metatarsals(BUFFER_LLAC_SIZE);
std::vector<int> buffer_fsr_in_tarsometatarsals(BUFFER_LLAC_SIZE);
std::vector<int> buffer_fsr_in_calcaneus_talus(BUFFER_LLAC_SIZE);

std::vector<int> buffer_imu_in_x(BUFFER_LLAC_SIZE);
std::vector<int> buffer_imu_in_y(BUFFER_LLAC_SIZE);
std::vector<int> buffer_imu_in_z(BUFFER_LLAC_SIZE);

int bufferIndexFSR = 0;
int bufferIndexIMU = 0;

void addToBuffer(std::vector<int> &buffer, int value, int index)
{
    buffer[index % BUFFER_SIZE] = value;
}

void *low_level_activity_classifier_run(void *arg)
{
    Instances *args = static_cast<Instances *>(arg);
    State *state = &(args->state);

    while (true)
    {
        state->lockMutex();
        state->waitConditionLLAC();

        std::vector<int> fsrData = args->fsrData;
        std::vector<int> imuData = args->imuData;

        // Procesar los datos de fsr en bloques de 32
        size_t fsrDataSize = fsrData.size();
        for (size_t i = 0; i < fsrDataSize; i += 32)
        {
            std::vector<int> block(fsrData.begin() + i, fsrData.begin() + std::min(i + 32, fsrDataSize));

            if (block.size() == 32)
            {
                int mean_distal_phalanges = calculateMean(block, fsr_in_distal_phalanges);
                int mean_mid_proximal_phalanges = calculateMean(block, fsr_in_mid_proximal_phalanges);
                int mean_metatarsals = calculateMean(block, fsr_in_metatarsals);
                int mean_tarsometatarsals = calculateMean(block, fsr_in_tarsometatarsals);
                int mean_calcaneus_talus = calculateMean(block, fsr_in_calcaneus_talus);

                // Comprobaciones prints
                printf("Empieza la MATRACAAAAAAAAAAAAA(FSR)\n");
                printVector(fsrData, "fsrData");
                printVector(block, "block");

                printVector(fsr_in_distal_phalanges, "VECTORDEDISTAL");
                printVectorFromPositions(block, fsr_in_distal_phalanges, "Values for distal phalanges");
                printf("Mean distal phalanges: %d\n", mean_distal_phalanges);

                printVector(fsr_in_mid_proximal_phalanges, "VECTORDEMID");
                printVectorFromPositions(block, fsr_in_mid_proximal_phalanges, "Values for mid proximal phalanges");
                printf("Mean mid proximal phalanges: %d\n", mean_mid_proximal_phalanges);

                printVector(fsr_in_metatarsals, "VECTORDEMETATAR");
                printVectorFromPositions(block, fsr_in_metatarsals, "Values for metatarsals");
                printf("Mean metatarsals: %d\n", mean_metatarsals);

                printVector(fsr_in_tarsometatarsals, "VECTORDETARSO");
                printVectorFromPositions(block, fsr_in_tarsometatarsals, "Values for tarsometatarsals");
                printf("Mean tarsometatarsals: %d\n", mean_tarsometatarsals);

                printVector(fsr_in_calcaneus_talus, "VECTORDECALCANEO");
                printVectorFromPositions(block, fsr_in_calcaneus_talus, "Values for calcaneus talus");
                printf("Mean calcaneus talus: %d\n", mean_calcaneus_talus);

                addToBuffer(buffer_fsr_in_distal_phalanges, mean_distal_phalanges, bufferIndexFSR);
                printVector(buffer_fsr_in_distal_phalanges, "Buffer Distal Phalanges");

                addToBuffer(buffer_fsr_in_mid_proximal_phalanges, mean_mid_proximal_phalanges, bufferIndexFSR);
                printVector(buffer_fsr_in_mid_proximal_phalanges, "Buffer Mid Proximal Phalanges");

                addToBuffer(buffer_fsr_in_metatarsals, mean_metatarsals, bufferIndexFSR);
                printVector(buffer_fsr_in_metatarsals, "Buffer Metatarsals");

                addToBuffer(buffer_fsr_in_tarsometatarsals, mean_tarsometatarsals, bufferIndexFSR);
                printVector(buffer_fsr_in_tarsometatarsals, "Buffer Tarsometatarsals");

                addToBuffer(buffer_fsr_in_calcaneus_talus, mean_calcaneus_talus, bufferIndexFSR);
                printVector(buffer_fsr_in_calcaneus_talus, "Buffer Calcaneus Talus");
            }
            bufferIndexFSR++;
        }

        // Procesar los datos de imu en bloques de 6
        size_t imuDataSize = imuData.size();
        for (size_t i = 0; i < imuDataSize; i += 6)
        {
            std::vector<int> block(imuData.begin() + i, imuData.begin() + std::min(i + 6, imuDataSize));

            if (block.size() == 6)
            {
                int mean_imu_x = calculateMean(block, imu_in_x);
                int mean_imu_y = calculateMean(block, imu_in_y);
                int mean_imu_z = calculateMean(block, imu_in_z);

                printf("Empieza la MATRACAAAAAAAAAAAAA(IMU)\n");
                printVector(imuData, "imuData");
                printVector(block, "imuBlock");

                printVector(imu_in_x, "VECTORIMUX");
                printVectorFromPositions(block, imu_in_x, "Values for IMU X");
                printf("Mean IMU X: %d\n", mean_imu_x);

                printVector(imu_in_y, "VECTORIMUY");
                printVectorFromPositions(block, imu_in_y, "Values for IMU Y");
                printf("Mean IMU Y: %d\n", mean_imu_y);

                printVector(imu_in_z, "VECTORIMUZ");
                printVectorFromPositions(block, imu_in_z, "Values for IMU Z");
                printf("Mean IMU Z: %d\n", mean_imu_z);

                addToBuffer(buffer_imu_in_x, mean_imu_x, bufferIndexIMU);
                printVector(buffer_imu_in_x, "Buffer IMU X");

                addToBuffer(buffer_imu_in_y, mean_imu_y, bufferIndexIMU);
                printVector(buffer_imu_in_y, "Buffer IMU Y");

                addToBuffer(buffer_imu_in_z, mean_imu_z, bufferIndexIMU);
                printVector(buffer_imu_in_z, "Buffer IMU Z");
            }
            bufferIndexIMU++;
        }

        state->unlockMutex();
    }
    pthread_exit(NULL);
}

int calculateMean(const std::vector<int> &data, const std::vector<int> &positions)
{
    int sum = 0;
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

void printVectorFromPositions(const std::vector<int> &data, const std::vector<int> &positions, const char *vecName)
{
    printf("%s: [", vecName);
    for (size_t i = 0; i < positions.size(); ++i)
    {
        if (positions[i] < data.size())
        {
            printf("%d", data[positions[i]]);
            if (i < positions.size() - 1)
            {
                printf(", ");
            }
        }
    }
    printf("]\n");
}