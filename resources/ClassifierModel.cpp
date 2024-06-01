// ClassifierModel.cpp
#include "ClassifierModel.h"
#include <iostream>

ClassifierModel::ClassifierModel(const std::string &model_path)
    : env(ORT_LOGGING_LEVEL_WARNING, "test"),
      session(env, model_path.c_str(), session_options)
{
    session_options.SetIntraOpNumThreads(1);
}

ClassifierModel::~ClassifierModel() {}

std::string ClassifierModel::runInference(std::vector<float> &inputData)
{
    try
    {
        Ort::AllocatorWithDefaultOptions allocator;

        // Define input dimensions
        std::vector<int64_t> input_node_dims = {1, static_cast<int64_t>(inputData.size())};
        auto memory_info = Ort::MemoryInfo::CreateCpu(OrtArenaAllocator, OrtMemTypeDefault);
        auto input_tensor = Ort::Value::CreateTensor<float>(memory_info, inputData.data(), inputData.size(), input_node_dims.data(), input_node_dims.size());

        const char *input_node_names[] = {"float_input"};
        const char *output_node_names[] = {"output_label"};

        // Ejecutar el modelo y obtener la salida
        auto output_tensors = session.Run(Ort::RunOptions{nullptr}, input_node_names, &input_tensor, 1, output_node_names, 1);

        // Obtener los valores del tensor de salida
        Ort::Value &output_tensor = output_tensors.front();
        Ort::TypeInfo type_info = output_tensor.GetTypeInfo();
        auto tensor_info = type_info.GetTensorTypeAndShapeInfo();
        ONNXTensorElementDataType output_type = tensor_info.GetElementType();

        if (output_type == ONNX_TENSOR_ELEMENT_DATA_TYPE_STRING)
        {
            size_t total_length;
            // Asignar el valor de retorno a una variable, aunque no se use
            OrtStatus *status_length = Ort::GetApi().GetStringTensorDataLength(output_tensor, &total_length);

            std::vector<char> buffer(total_length);
            std::vector<size_t> offsets(tensor_info.GetElementCount());
            // Asignar el valor de retorno a una variable, aunque no se use
            OrtStatus *status_content = Ort::GetApi().GetStringTensorContent(output_tensor, buffer.data(), buffer.size(), offsets.data(), offsets.size());

            std::vector<std::string> output_strings;
            for (size_t i = 0; i < offsets.size(); ++i)
            {
                size_t end_offset = (i == offsets.size() - 1) ? total_length : offsets[i + 1];
                output_strings.emplace_back(buffer.data() + offsets[i], end_offset - offsets[i]);
            }

            std::string result;
            for (size_t i = 0; i < output_strings.size(); ++i)
            {
                result += output_strings[i];
            }

            return result;
        }
        else
        {
            return "Unexpected output type.";
        }
    }
    catch (const Ort::Exception &e)
    {
        return std::string("Ort::Exception: ") + e.what();
    }
}
