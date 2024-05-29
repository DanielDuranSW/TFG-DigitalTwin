// ClassifierModel.cpp
#include "ClassifierModel.h"

ClassifierModel::ClassifierModel() {}

ClassifierModel::~ClassifierModel() {}

std::string runInference(const std::vector<int> &inputData)
{
    // Inicializar el entorno de ONNX Runtime
    Ort::Env env(ORT_LOGGING_LEVEL_WARNING, "example");
    Ort::SessionOptions session_options;
    session_options.SetIntraOpNumThreads(1);
    session_options.SetGraphOptimizationLevel(GraphOptimizationLevel::ORT_ENABLE_EXTENDED);

    // Ruta al modelo ONNX
    const char *model_path = "/home/daniduran/ws/TFG-DigitalTwin/resources/model.onnx";

    // Crear una sesión para el modelo
    Ort::Session session(env, model_path, session_options);

    // Obtener nombres de las entradas y salidas del modelo
    Ort::AllocatorWithDefaultOptions allocator;
    auto input_name = session.GetInputName(0, allocator);
    auto output_name = session.GetOutputName(0, allocator);

    // Definir la forma de la entrada
    std::vector<int64_t> input_shape = {1, static_cast<int64_t>(inputData.size())}; // {batch_size, num_features}

    // Crear tensor de entrada
    size_t input_tensor_size = inputData.size();
    std::vector<float> input_tensor_values(input_tensor_size);
    std::copy(inputData.begin(), inputData.end(), input_tensor_values.begin());

    // Crear el tensor de entrada
    Ort::MemoryInfo memory_info = Ort::MemoryInfo::CreateCpu(OrtDeviceAllocator, OrtMemTypeCPU);
    Ort::Value input_tensor = Ort::Value::CreateTensor<float>(memory_info, input_tensor_values.data(), input_tensor_size, input_shape.data(), input_shape.size());

    // Ejecutar la inferencia
    std::vector<const char *> input_names = {input_name};
    std::vector<const char *> output_names = {output_name};
    auto output_tensors = session.Run(Ort::RunOptions{nullptr}, input_names.data(), &input_tensor, 1, output_names.data(), 1);

    // Obtener la salida
    float *output = output_tensors.front().GetTensorMutableData<float>();

    // Suponiendo que la salida es una cadena de texto o un índice de clase que mapeas a una cadena
    std::string result = "Predicted class: " + std::to_string(output[0]);

    // Liberar la memoria de los nombres de entrada y salida
    allocator.Free(input_name);
    allocator.Free(output_name);

    return result;
}