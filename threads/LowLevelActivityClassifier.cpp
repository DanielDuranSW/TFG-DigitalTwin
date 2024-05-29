#include "LowLevelActivityClassifier.h"

// Definiciones de las variables de buffer
std::vector<int> buffer_fsr_in_distal_phalanges(BUFFER_LLAC_SIZE);
std::vector<int> buffer_fsr_in_mid_proximal_phalanges(BUFFER_LLAC_SIZE);
std::vector<int> buffer_fsr_in_metatarsals(BUFFER_LLAC_SIZE);
std::vector<int> buffer_fsr_in_tarsometatarsals(BUFFER_LLAC_SIZE);
std::vector<int> buffer_fsr_in_calcaneus_talus(BUFFER_LLAC_SIZE);

std::vector<int> buffer_imu_acc_x(BUFFER_LLAC_SIZE);
std::vector<int> buffer_imu_acc_y(BUFFER_LLAC_SIZE);
std::vector<int> buffer_imu_acc_z(BUFFER_LLAC_SIZE);

std::vector<int> buffer_imu_gyro_x(BUFFER_LLAC_SIZE);
std::vector<int> buffer_imu_gyro_y(BUFFER_LLAC_SIZE);
std::vector<int> buffer_imu_gyro_z(BUFFER_LLAC_SIZE);

int bufferIndexFSR = 0;
int bufferIndexIMU = 0;

bool bo = false;

void addToBuffer(std::vector<int> &buffer, int value)
{
    // Mover todos los elementos una posición a la derecha
    for (int i = BUFFER_LLAC_SIZE - 1; i > 0; --i)
    {
        buffer[i] = buffer[i - 1];
    }
    // Insertar el nuevo valor en la primera posición
    buffer[0] = value;
}

void *low_level_activity_classifier_run(void *arg)
{
    Instances *args = static_cast<Instances *>(arg);
    State *state = &(args->state);
    ClassifierFeatures *classifierFeatures = args->classifierFeatures;

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

                // // Comprobaciones prints
                // printf("Empieza la MATRACAAAAAAAAAAAAA(FSR)\n");
                // printVector(fsrData, "fsrData");
                // printVector(block, "block");

                // printVector(fsr_in_distal_phalanges, "VECTORDEDISTAL");
                // printVectorFromPositions(block, fsr_in_distal_phalanges, "Values for distal phalanges");
                // printf("Mean distal phalanges: %d\n", mean_distal_phalanges);

                // printVector(fsr_in_mid_proximal_phalanges, "VECTORDEMID");
                // printVectorFromPositions(block, fsr_in_mid_proximal_phalanges, "Values for mid proximal phalanges");
                // printf("Mean mid proximal phalanges: %d\n", mean_mid_proximal_phalanges);

                // printVector(fsr_in_metatarsals, "VECTORDEMETATAR");
                // printVectorFromPositions(block, fsr_in_metatarsals, "Values for metatarsals");
                // printf("Mean metatarsals: %d\n", mean_metatarsals);

                // printVector(fsr_in_tarsometatarsals, "VECTORDETARSO");
                // printVectorFromPositions(block, fsr_in_tarsometatarsals, "Values for tarsometatarsals");
                // printf("Mean tarsometatarsals: %d\n", mean_tarsometatarsals);

                // printVector(fsr_in_calcaneus_talus, "VECTORDECALCANEO");
                // printVectorFromPositions(block, fsr_in_calcaneus_talus, "Values for calcaneus talus");
                // printf("Mean calcaneus talus: %d\n", mean_calcaneus_talus);

                // addToBuffer(buffer_fsr_in_distal_phalanges, mean_distal_phalanges);
                // printVector(buffer_fsr_in_distal_phalanges, "Buffer Distal Phalanges");

                // addToBuffer(buffer_fsr_in_mid_proximal_phalanges, mean_mid_proximal_phalanges);
                // printVector(buffer_fsr_in_mid_proximal_phalanges, "Buffer Mid Proximal Phalanges");

                // addToBuffer(buffer_fsr_in_metatarsals, mean_metatarsals);
                // printVector(buffer_fsr_in_metatarsals, "Buffer Metatarsals");

                // addToBuffer(buffer_fsr_in_tarsometatarsals, mean_tarsometatarsals);
                // printVector(buffer_fsr_in_tarsometatarsals, "Buffer Tarsometatarsals");

                // addToBuffer(buffer_fsr_in_calcaneus_talus, mean_calcaneus_talus);
                // printVector(buffer_fsr_in_calcaneus_talus, "Buffer Calcaneus Talus");
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
                int mean_imu_acc_x = calculateMean(block, imu_acc_x);
                int mean_imu_acc_y = calculateMean(block, imu_acc_y);
                int mean_imu_acc_z = calculateMean(block, imu_acc_z);

                int mean_imu_gyro_x = calculateMean(block, imu_gyro_x);
                int mean_imu_gyro_y = calculateMean(block, imu_gyro_y);
                int mean_imu_gyro_z = calculateMean(block, imu_gyro_z);

                // printf("Empieza la MATRACAAAAAAAAAAAAA(IMU)\n");
                // printVector(imuData, "imuData");
                // printVector(block, "imuBlock");

                // printVector(imu_acc_x, "VECTORIMUX");
                // printVectorFromPositions(block, imu_acc_x, "Values for IMU X");
                // printf("Mean IMU X: %d\n", mean_imu_acc_x);

                // printVector(imu_acc_y, "VECTORIMUY");
                // printVectorFromPositions(block, imu_acc_y, "Values for IMU Y");
                // printf("Mean IMU Y: %d\n", mean_imu_acc_y);

                // printVector(imu_acc_z, "VECTORIMUZ");
                // printVectorFromPositions(block, imu_acc_z, "Values for IMU Z");
                // printf("Mean IMU Z: %d\n", mean_imu_acc_z);

                // printVector(imu_gyro_x, "VECTORIMUGYROX");
                // printVectorFromPositions(block, imu_gyro_x, "Values for IMU Gyro X");
                // printf("Mean IMU Gyro X: %d\n", mean_imu_gyro_x);

                // printVector(imu_gyro_y, "VECTORIMUGYROY");
                // printVectorFromPositions(block, imu_gyro_y, "Values for IMU Gyro Y");
                // printf("Mean IMU Gyro Y: %d\n", mean_imu_gyro_y);

                // printVector(imu_gyro_z, "VECTORIMUGYROZ");
                // printVectorFromPositions(block, imu_gyro_z, "Values for IMU Gyro Z");
                // printf("Mean IMU Gyro Z: %d\n", mean_imu_gyro_z);

                addToBuffer(buffer_imu_acc_x, mean_imu_acc_x);
                printVector(buffer_imu_acc_x, "Buffer IMU Acc X");

                addToBuffer(buffer_imu_acc_y, mean_imu_acc_y);
                printVector(buffer_imu_acc_y, "Buffer IMU Acc Y");

                addToBuffer(buffer_imu_acc_z, mean_imu_acc_z);
                printVector(buffer_imu_acc_z, "Buffer IMU Acc Z");

                addToBuffer(buffer_imu_gyro_x, mean_imu_gyro_x);
                printVector(buffer_imu_gyro_x, "Buffer IMU Gyro X");

                addToBuffer(buffer_imu_gyro_y, mean_imu_gyro_y);
                printVector(buffer_imu_gyro_y, "Buffer IMU Gyro Y");

                addToBuffer(buffer_imu_gyro_z, mean_imu_gyro_z);
                printVector(buffer_imu_gyro_z, "Buffer IMU Gyro Z");
            }
            bufferIndexIMU++;
        }

        bool buffersFull =
            std::all_of(buffer_imu_gyro_z.begin(), buffer_imu_gyro_z.end(), [](int i)
                        { return i != 0; });

        if (buffersFull || bo)
        {

            classifierFeatures->Feature2and3(buffer_fsr_in_distal_phalanges);
            classifierFeatures->Feature4(buffer_fsr_in_distal_phalanges, buffer_fsr_in_calcaneus_talus);

            int mean_1 = classifierFeatures->Feature1(buffer_fsr_in_distal_phalanges);
            int mean_2 = classifierFeatures->Feature1(buffer_fsr_in_mid_proximal_phalanges);
            int mean_3 = classifierFeatures->Feature1(buffer_fsr_in_metatarsals);
            int mean_4 = classifierFeatures->Feature1(buffer_fsr_in_tarsometatarsals);
            int mean_5 = classifierFeatures->Feature1(buffer_fsr_in_calcaneus_talus);

            // std::vector<int> inputData = {
            //     mean_1, mean_2, mean_3, mean_4, mean_5,
            //     mean_acc_x, mean_acc_y, mean_acc_z,
            //     mean_gyro_x, mean_gyro_y, mean_gyro_z,
            //     mag_1, mag_2, mag_3, mag_4, mag_5,
            //     mag_acc_x, mag_acc_y, mag_acc_z,
            //     mag_gyro_x, mag_gyro_y, mag_gyro_z};
            std::vector<int> inputData = {};
            bo = true;
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