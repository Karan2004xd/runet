import os
from pathlib import Path

try:
    import google.colab
    IN_COLAB = True
except ImportError:
    IN_COLAB = False

if IN_COLAB:
    BASE_DIR = Path(os.getcwd())
else:
    BASE_DIR = Path(__file__).resolve().parent.parent

LIB_PATH = os.path.join(BASE_DIR, "libs", "librunet.so")
DEFAULT_BIN_PATH = os.path.join(BASE_DIR, "libs", "runet_model.bin")

MAGIC_NUMBER = 0x52554E45

SUPPORTED_MODELS = [
    "sequential"
]

SUPPORTED_LAYERS = [
    "dense"
]

SUPPORTED_ACTIVATION_FNS = [
    "relu", "softmax"
]

STATUS_CODE_MESSAGES = {
    -101: "Invalid Matrix Index Access",

    -201: "Matrix Shape Mismatch",
    -202: "Null/Empty Parameter",
    -203: "Matrix Memory Allocation Failure",

    -301: "Layer wise shape mismatch in network",
    -302: "Network storage at capacity, cannot fit in more layers",
    -303: "Unable to open the file",
    -304: "Invalid File Format",
}
