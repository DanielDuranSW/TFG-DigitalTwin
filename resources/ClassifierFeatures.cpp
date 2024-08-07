// ClasifierFeatures.cpp
#include "ClassifierFeatures.h"

ClassifierFeatures::ClassifierFeatures() {}

ClassifierFeatures::~ClassifierFeatures() {}

int ClassifierFeatures::Feature1(std::vector<int> buffer)
{
    // Calcular la media de cada buffer
    return calculateMean(buffer);
    printf("FEATUREEEEEEEEEEEEEEE11111111111111111111 %i\n", calculateMean(buffer));
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

int ClassifierFeatures::Feature2and3(const std::vector<int> &buffer)
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
    // int feature3 = frequency;

    // printf("FEATUREEEEEEEEEEEEEEE22222222222222222222 %i\n", feature2);
    // printf("FEATUREEEEEEEEEEEEEEE33333333333333333333 %i\n", feature3);

    // Liberar memoria y plan de FFTW
    fftw_destroy_plan(plan);
    fftw_free(in);
    fftw_free(out);

    return feature2;
}

void ClassifierFeatures::Feature4(const std::vector<int> &buffer_fsr_in_distal_phalanges, const std::vector<int> &buffer_fsr_in_calcaneus_talus)
{
    // Comprobar que los buffers tienen el mismo tamaño
    if (buffer_fsr_in_distal_phalanges.size() != buffer_fsr_in_calcaneus_talus.size())
    {
        std::cerr << "Error: Buffers must have the same size." << std::endl;
        return;
    }

    int n = buffer_fsr_in_distal_phalanges.size();
    double mean1 = calculateMean(buffer_fsr_in_distal_phalanges);
    double mean2 = calculateMean(buffer_fsr_in_calcaneus_talus);

    double numerator = 0;
    double denominator1 = 0;
    double denominator2 = 0;

    for (int i = 0; i < n; ++i)
    {
        double diff1 = buffer_fsr_in_distal_phalanges[i] - mean1;
        double diff2 = buffer_fsr_in_calcaneus_talus[i] - mean2;

        numerator += diff1 * diff2;
        denominator1 += diff1 * diff1;
        denominator2 += diff2 * diff2;
    }

    double denominator = sqrt(denominator1) * sqrt(denominator2);

    double correlation = (denominator == 0) ? 0 : numerator / denominator;

    printf("FEATUREEEEEEEEEEEEEEE44444444444444444444 %f\n", correlation);
}