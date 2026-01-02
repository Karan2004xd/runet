# Runet Inference Engine

**Runet** is a high-performance, lightweight C-based inference engine for Deep Learning models. By bypassing the overhead of heavy frameworks, Runet achieves **6.0x faster execution** than TensorFlow on standard benchmarks (MNIST) with identical accuracy.

## Features
- **Pure C Backend**: Optimized matrix operations with zero memory leaks (Valgrind-verified).
- **Fast Inference**: Specialized for Feed-Forward Neural Networks (Dense layers).
- **Python Integration**: Seamlessly export TensorFlow/Keras models to `.bin` files and run them via a Python wrapper.
- **Lightweight**: Minimal dependencies, perfect for resource-constrained environments.

## Performance Benchmark
| Framework | Task | Accuracy | Inference Speed (Relative) |
| :--- | :--- | :--- | :--- |
| TensorFlow | MNIST | 98% | 1.0x |
| **Runet Engine** | **MNIST** | **98%** | **6.0x** |

## Project Structure
- `src/`: C Source code for matrix math, layers, and network orchestration.
- `include/`: Header files and internal API definitions.
- `scripts/`: Python API (`runet.py`, `c_wrapper.py`).
- `tests/`: Extensive C unit test suite.
- `libs/`: Compiled shared library (`librunet.so`) and model binaries.

## Quick Start (Google Colab/Linux)

1. **Clone & Setup**:
   ```bash
   git clone https://github.com/Karan2004xd/runet.git
   cd runet
   make clean && make librunet.so

2. **Usage**:
    ```bash
    from scripts.runet import RunetEngine

    engine = RunetEngine()

    # Load Pre-trained tensorflow model
    # The engine automatically exports it to .bin format
    engine.load_model(your_tf_model)

    # Predict
    result = engine.predict(input_data)
    ```

## Limitations
- Training **is not supported** (only inference).
- CNNs, RNNs, Transformers are not supported.
- Models must be exported using Runet's exporter.
- Batch inference support is limited to feed-forward execution.

## Supported Model Components
### Models
- Sequential

### Layers
- Dense (Fully Connected)

### Activation Functions
- ReLU
- Softmax

## Educational Purpose
This project was developed as a part of college coursework to explore,

- Neural network inference internals
- Systems-level performance optimization
- C and Python interoperability
- Custom binary formats
- Deterministic execution and memory management
