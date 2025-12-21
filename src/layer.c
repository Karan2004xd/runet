#include "../include/layer.h"
#include "../include/matrix.h"
#include "../include/matrix_operations.h"
#include "../include/status_codes.h"

#include <stdlib.h>

static int dense_forward(RunetLayer *layer,
                         const RunetMatrix *input)
{
  if (!layer || !input) {
    return NULL_PARAMETER;
  }

  int batch_size = input->rows;
  int out_features = layer->out_features;

  if (layer->output->rows != batch_size || layer->output->cols != out_features) {
    runet_matrix_init(layer->output, batch_size, out_features, NULL);
  }
  int status_code;

  // Z = X * W
  if ((status_code = runet_matrix_mul(layer->output, input, layer->weights)) < 0) {
    return status_code;
  }

  // Z = Z + B
  if ((status_code = runet_matrix_add_bias(layer->output, layer->bias)) < 0) {
    return status_code;
  }

  // Apply activation function
  switch (layer->activation) {
    case RUNET_ACT_RELU:
      if ((status_code = runet_apply_relu(layer->output, layer->output)) < 0) {
        return status_code;
      }
      break;

    case RUNET_ACT_SOFTMAX:
      if ((status_code = runet_apply_softmax(layer->output, layer->output)) < 0) {
        return status_code;
      }
      break;

    default:
      break;
  }
  return SUCCESS_CODE;
}

RunetLayer *runet_layer_create_dense(
  int input_size, int output_size, RunetActivation activation)
{
  RunetLayer *layer = malloc(sizeof(RunetLayer));
  if (!layer) {
    return NULL;
  }

  layer->type = RUNET_LAYER_DENSE;
  layer->activation = activation;
  layer->forward = dense_forward;

  // W = input x output
  layer->weights = runet_matrix_create(input_size, output_size, NULL);

  // B = 1 x output
  layer->bias = runet_matrix_create(1, output_size, NULL);

  // Z = 1 x output
  layer->output = runet_matrix_create(1, output_size, NULL);

  layer->in_features = input_size;
  layer->out_features = output_size;

  return layer;
}

int runet_layer_forward(RunetLayer *layer, const RunetMatrix *input)
{
  return layer->forward(layer, input);
}

void runet_layer_free(RunetLayer *layer)
{
  if (!layer) {
    return ;
  }

  runet_matrix_free(layer->weights);
  runet_matrix_free(layer->bias);
  runet_matrix_free(layer->output);
  free(layer);
}
