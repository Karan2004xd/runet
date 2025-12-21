#ifndef __LAYER_H__
#define __LAYER_H__

typedef struct runet_matrix RunetMatrix;
typedef struct runet_layer RunetLayer;

typedef int (*RunetLayerForwardFn)(
  RunetLayer *layer,
  const RunetMatrix *input
);

typedef enum {
  RUNET_LAYER_DENSE
} RunetLayerType;

typedef enum {
  RUNET_ACT_NONE,
  RUNET_ACT_RELU,
  RUNET_ACT_SOFTMAX
} RunetActivation;

struct runet_layer {
  RunetLayerType type; /** < The layer type */
  RunetActivation activation; /** < The activation function */

  RunetMatrix *weights; /** < Weights of the layer */
  RunetMatrix *bias; /** < Bias of the layer */
  RunetMatrix *output; /** < Output of the layer */

  int in_features;
  int out_features;

  RunetLayerForwardFn forward; /** < Function pointer to the specific forwarding function */
};

/**
  * @brief Creates a new Dense Layer
  * * This function based on the parameters specified,
  * creates a complete Dense Layer.
  *
  * @param input_size The size of the input data.
  * @param output_size The size of the output data.
  * @param activation The activation function to apply.
  *
  * @return RunetLayer* A pointer to the newly created Dense Layer
  */
RunetLayer *runet_layer_create_dense(int input_size,
                                     int output_size,
                                     RunetActivation activation);

/**
  * @brief Executes the layer
  * * This function executes the layer based on its parameters
  * and generates an output.
  *
  * @param layer A pointer to the actual layer.
  * @param input A pointer to the input data Matrix.
  *
  * @return int A status code specifying operation success or failure.
  * (refer to RUNET_STATUS_CODE for more information)
  */
int runet_layer_forward(RunetLayer *layer, const RunetMatrix *input);

/**
  * @brief Frees the layer memory.
  * * This function destroys or frees the provided Layer object.
  *
  * @param layer A pointer to the layer to free.
  */
void runet_layer_free(RunetLayer *layer);

#endif // __LAYER_H__
