import os
import glob

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
BASE_DIR = os.path.dirname(SCRIPT_DIR)

pkg_so = glob.glob(os.path.join(SCRIPT_DIR, "librunet*.so"))
dev_so = os.path.abspath(os.path.join(SCRIPT_DIR, "libs", "librunet.so"))

if pkg_so:
    LIB_PATH = pkg_so[0]
elif os.path.exists(dev_so):
    LIB_PATH = dev_so
else:
    LIB_PATH = "librunet.so"

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
