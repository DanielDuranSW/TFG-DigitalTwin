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

    // printf("FEATUREEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE\n");
    // printf("Mean distal phalanges: %d\n", mean_distal_phalanges);
    // printf("Mean mid proximal phalanges: %d\n", mean_mid_proximal_phalanges);
    // printf("Mean metatarsals: %d\n", mean_metatarsals);
    // printf("Mean tarsometatarsals: %d\n", mean_tarsometatarsals);
    // printf("Mean calcaneus talus: %d\n", mean_calcaneus_talus);
    // printf("Mean IMU X: %d\n", mean_imu_x);
    // printf("Mean IMU Y: %d\n", mean_imu_y);
    // printf("Mean IMU Z: %d\n", mean_imu_z);
}

int ClassifierFeatures::calculateMean(const std::vector<int> &buffer)
{
    // Es long por los negativos
    long long sum = 0;
    for (int value : buffer)
    {
        sum += value;
    }

    return static_cast<int>(sum / static_cast<long long>(buffer.size()));
}

void ClassifierFeatures::Feature2and3(const std::vector<int> &buffer)
{
    // Tamaño del búfer para la FFT
    int N = buffer.size();

    // Punteros para los numero complejos de entrada y salida
    fftw_complex *in = (fftw_complex *)fftw_malloc(sizeof(fftw_complex) * N);
    fftw_complex *out = (fftw_complex *)fftw_malloc(sizeof(fftw_complex) * N);

    // Crear un plan FFTW para la transformada directa
    fftw_plan plan = fftw_plan_dft_1d(N, in, out, FFTW_FORWARD, FFTW_ESTIMATE);

    // Copiar datos de entrada al formato requerido por FFTW
    for (int i = 0; i < N; ++i)
    {
        in[i][0] = buffer[i]; // Parte real
        in[i][1] = 0;         // Parte imaginaria (no se usa)
    }

    // Ejecutar la transformada
    fftw_execute(plan);

    // Encontrar el índice de la magnitud máxima
    int maxMagnitude = 0;
    int maxIndex = 0;
    for (int i = 0; i < N; ++i)
    {
        int magnitude = sqrt(out[i][0] * out[i][0] + out[i][1] * out[i][1]);
        if (magnitude > maxMagnitude)
        {
            maxMagnitude = magnitude;
            maxIndex = i;
        }
    }

    // La frecuencia asociada al mayor valor se calcula como la frecuencia normalizada por el tamaño de la señal
    int frequency = maxIndex / N;

    // Es la magnitud máxima encontrada en el espectro de frecuencia después de aplicar la transformada de Fourier
    int feature2 = maxMagnitude;
    // Es la frecuencia asociada al mayor valor en el espectro de frecuencia, normalizada por el tamaño de la señal.
    int feature3 = frequency;

    printf("FEATUREEEEEEEEEEEEEEE22222222222222222222 %i\n", feature2);
    printf("FEATUREEEEEEEEEEEEEEE33333333333333333333 %i\n", feature3);

    // Liberar memoria y plan de FFTW
    fftw_destroy_plan(plan);
    fftw_free(in);
    fftw_free(out);
}
