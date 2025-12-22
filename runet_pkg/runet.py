import constants as constant
from c_wrapper import CWrapper
from tensorflow.keras import models
import struct
import numpy as np


class RunetEngine:
    """
    The main interface for the Runet Inferance Engine.
    Handles model exportation from Tensorflow and C-based inferance
    """

    def __init__(self):
        """Initializes the engine and loads the C wrapper"""
        self._wrapper = CWrapper()

    def export_to_runet_bin(self, model: models, path: str) -> str:
        """
        Creates a .bin file for the provided Tensorflow based model
        and creates a .bin file at the provided path.

        Args:
            model (tensorflow.keras.models): A Tensorflow model.
            path (str): The path to where the .bin file is to be exported. 

        Returns:
            str: The path where the .bin file got exported.
        """
        return self._export_to_runet_bin_base(model, path)

    def load_model(self, model: models) -> None:
        """
        Loads the data of the model inside the engine to create
        the network.

        Args:
            model (tensorflow.keras.models): A Tensorflow model.
        """

        name = model.name.split("_", 1)[0] # split the model name out.
        if name not in constant.SUPPORTED_MODELS:
            raise ValueError(f"{name} is not supported by runet.")

        path = self._export_to_runet_bin_base(model, constant.DEFAULT_BIN_PATH)
        status = self._wrapper.runet_network_from_file(path)

        if status < 0: 
            raise ValueError(f"Failed to load model.\nError Code: {status}\
                             \nMessage: {constant.STATUS_CODE_MESSAGES[status]}")

    def summary(self):
        """Prints the summary of the network of the engine."""
        self._wrapper.runet_network_summary()

    def predict(self, input_data: np.ndarray):
        """
        Runs inference on the provided input data using the C backend.

        Args:
            input_data (np.array): The input data to predict upon.

        Returns:
            np.array: The output result of the model.
        """
        c_input = self._wrapper.runet_matrix_create(input_data)
        return self._wrapper.runet_network_predict(c_input)

    def _export_to_runet_bin_base(self, model: models, path: str):
        layers = []

        for layer in model.layers:
            name = layer.name.split("_", 1)[0] # split out the layer name
            if name in constant.SUPPORTED_LAYERS:
                layers.append(layer)
            else:
                print(f"WARNING: {name} is not supported and it won't be applied to model")

        with open(path, 'wb') as f:
            f.write(struct.pack('I', constant.MAGIC_NUMBER))
            f.write(struct.pack('i', len(layers)))

            for layer in layers:
                weights, biases = layer.get_weights()
                rows, cols = weights.shape

                act_type = 0
                act_name = layer.activation.__name__

                if act_name in constant.SUPPORTED_ACTIVATION_FNS:
                    # get the exact activation number
                    act_type = constant.SUPPORTED_ACTIVATION_FNS.index(act_name) + 1
                else:
                    print(f"WARNING: {act_name} is not supported and it won't be applied to the layer")

                f.write(struct.pack('iiii', 0, act_type, rows, cols))

                weights.astype('float32').tofile(f)
                biases.astype('float32').tofile(f)

        print(f"Model successfully exported to {path}")
        return path
