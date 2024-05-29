#include "ClassifierModel.h"

ClassifierModel::ClassifierModel()
    : env(ORT_LOGGING_LEVEL_WARNING, "example"),
      session_options(),
      session(env, "/home/daniduran/ws/TFG-DigitalTwin/resources/model.onnx", session_options)
{
    session_options.SetIntraOpNumThreads(1);
    session_options.SetGraphOptimizationLevel(GraphOptimizationLevel::ORT_ENABLE_EXTENDED);
}
ClassifierModel::~ClassifierModel() {}

std::string ClassifierModel::runInference(const std::vector<int> &inputData)
{
    Ort::Env env(ORT_LOGGING_LEVEL_WARNING, "ONNXRuntime");

    // Cargar el modelo desde el archivo .onnx
    Ort::SessionOptions session_options;
    Ort::Session session(env, "/home/daniduran/ws/TFG-DigitalTwin/resources/model.onnx", session_options);

    // Preparar los datos de entrada
    std::vector<float> input_data_float(inputData.begin(), inputData.end()); // Convertir datos de entrada a float

    // Definir la forma de la entrada
    std::vector<int64_t> input_dims = {1, static_cast<int64_t>(inputData.size())};

    // Crear el tensor de entrada
    Ort::Value input_tensor = Ort::Value::CreateTensor<float>(Ort::MemoryInfo::CreateCpu(OrtArenaAllocator, OrtMemTypeDefault), input_data_float.data(), inputData.size(), input_dims.data(), 2);

    // Nombres de las entradas del modelo
    const char *input_names[] = {
        "mean_1", "mean_2", "mean_3", "mean_4", "mean_5",
        "mean_acc_x", "mean_acc_y", "mean_acc_z",
        "mean_gyro_x", "mean_gyro_y", "mean_gyro_z",
        "mag_1", "mag_2", "mag_3", "mag_4", "mag_5",
        "mag_acc_x", "mag_acc_y", "mag_acc_z",
        "mag_gyro_x", "mag_gyro_y", "mag_gyro_z"};

    // Nombre de la salida definido en el modelo
    const char *output_names[] = {"output_string"};

    // Realizar la inferencia
    Ort::RunOptions run_options;
    std::vector<Ort::Value> output_tensors = session.Run(run_options, input_names, &input_tensor, 1, output_names, 1);

    // Obtener la salida
    std::string result = *output_tensors.front().GetTensorMutableData<std::string>();

    return result;
}
