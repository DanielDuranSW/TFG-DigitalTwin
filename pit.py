import onnx

# Cargar el modelo ONNX
model_path = '/home/daniduran/ws/TFG-DigitalTwin/resources/model.onnx'  # Actualiza esto con la ruta correcta
model = onnx.load(model_path)

# Obtener el grafo del modelo
graph = model.graph

# Información sobre las entradas del modelo
input_info = [(input.name, [dim.dim_value for dim in input.type.tensor_type.shape.dim]) for input in graph.input]

# Información sobre las salidas del modelo
output_info = [(output.name, [dim.dim_value for dim in output.type.tensor_type.shape.dim]) for output in graph.output]

print("Entradas del modelo:")
for name, shape in input_info:
    print(f"  Nombre: {name}, Dimensiones: {shape}")

print("\nSalidas del modelo:")
for name, shape in output_info:
    print(f"  Nombre: {name}, Dimensiones: {shape}")
