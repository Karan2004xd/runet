import struct
from tensorflow.keras.models import Sequential


def export_to_runet_bin(model: Sequential, filename: str):
    """
    Exports a Keras/TF Sequential model to the Runet .bin format.
    Assumes only Dense layers are used.
    """
    dense_layers = []

    for layer in model.layers:
        if 'dense' in layer.name:
            dense_layers.append(layer)

    with open(filename, 'wb') as f:
        f.write(struct.pack('I', 0x52554E45))
        f.write(struct.pack('i', len(dense_layers)))

        for layer in dense_layers:
            weights, biases = layer.get_weights()
            rows, cols = weights.shape

            act_type = 0
            if layer.activation.__name__ == 'relu':
                act_type = 1
            elif layer.activation.__name__ == 'softmax':
                act_type = 2

            f.write(struct.pack('iiii', 0, act_type, rows, cols))

            weights.astype('float32').tofile(f)
            biases.astype('float32').tofile(f)

    print(f"Model successfully exported to {filename}")
