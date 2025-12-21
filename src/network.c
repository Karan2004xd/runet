#include "../include/layer.h"
#include "../include/network.h"
#include "../include/status_codes.h"
#include "../include/matrix.h"

#include <stdio.h>
#include <stdlib.h>

static const char *get_activation_name(RunetActivation act)
{
  switch (act) {
    case RUNET_ACT_RELU: return "ReLU";
    case RUNET_ACT_SOFTMAX: return "Softmax";
    case RUNET_ACT_NONE: return "None";
    default: return "Unknown";
  }
}

static const char *get_layer_name(RunetLayerType type)
{
  switch (type) {
    case RUNET_LAYER_DENSE: return "Dense";
    default: return "Unknown";
  }
}

static RunetNetwork *network_create_base(int capacity)
{
  RunetNetwork *n = malloc(sizeof(RunetNetwork));
  if (!n) {
    return NULL;
  }

  n->capacity = capacity;
  n->curr_size = 0;
  n->layers = malloc(capacity * sizeof(RunetLayer *));

  if (!n->layers) {
    free(n);
    return NULL;
  }
  return n;
}

RunetNetwork *runet_network_create(int capacity)
{
  return network_create_base(capacity);
}

RunetNetwork *runet_network_from_file(const char *path, int *status_code)
{
  FILE *file = fopen(path, "rb");
  if (!file) {
    *status_code = FILE_OPEN_ERROR;
    return NULL;
  }

  unsigned int magic;
  fread(&magic, sizeof(unsigned int), 1, file);

  if (magic != MAGIC_NUMBER) {
    fclose(file);
    *status_code = INVALID_FILE_FORMAT;
    return NULL;
  }

  int layer_count;
  fread(&layer_count, sizeof(int), 1, file);

  RunetNetwork *net = network_create_base(layer_count);

  for (int i = 0; i < layer_count; i++) {
    int type, act_fn, rows, cols;
    fread(&type, sizeof(int), 1, file);
    fread(&act_fn, sizeof(int), 1, file);
    fread(&rows, sizeof(int), 1, file);
    fread(&cols, sizeof(int), 1, file);

    RunetLayer *l = runet_layer_create_dense(rows, cols, (RunetActivation) act_fn);

    fread(l->weights->data, sizeof(float), rows * cols, file);
    fread(l->bias->data, sizeof(float), cols, file);

    runet_network_add(net, l);
  }

  fclose(file);
  *status_code = SUCCESS_CODE;
  return net;
}

int runet_network_add(RunetNetwork *net, RunetLayer *layer)
{
  if (!net || !layer) {
    return NULL_PARAMETER;
  }

  if (net->curr_size >= net->capacity) {
    return NETWORK_AT_CAPACITY;
  }

  if (net->curr_size > 0) {
    RunetLayer *prev_layer = net->layers[net->curr_size - 1];

    // prev_layer->weights->cols = output size of last layer
    // layer->weights->rows = input size of new layer
    if (prev_layer->weights->cols != layer->weights->rows) {
      return SHAPE_MISMATCH;
    }
  }

  net->layers[net->curr_size] = layer;
  net->curr_size++;
  return SUCCESS_CODE;
}

int runet_network_predict(RunetNetwork *net,
                          const RunetMatrix *input,
                          RunetMatrix **output)
{
  if (!net || net->curr_size == 0 || !net->layers) {
    return NULL_PARAMETER;
  }
  int status_code;

  if ((status_code = runet_layer_forward(net->layers[0], input)) < 0) {
    return status_code;
  }

  for (int i = 1; i < net->curr_size; i++) {
    RunetMatrix *prev_output = net->layers[i - 1]->output;

    if ((status_code = runet_layer_forward(net->layers[i], prev_output)) < 0) {
      return status_code;
    }
  }

  if (output) {
    *output = net->layers[net->curr_size - 1]->output;
  }
  return SUCCESS_CODE;
}

void runet_network_summary(const RunetNetwork *net)
{
  if (!net) {
    printf("Network is empty\n");
    return;
  }

  printf("\n================ Runet Model Summary ================\n");
  printf("%-5s | %-10s | %-15s | %-10s\n", "Idx", "Type", "Shape (In x Out)", "Activation");
  printf("-----------------------------------------------------\n");

  for (int i = 0; i < net->curr_size; i++) {
    RunetLayer *l = net->layers[i];
    printf("%-5d | %-10s | %d x %-12d | %-10s\n", 
           i, 
           get_layer_name(l->type),
           l->in_features, 
           l->out_features, 
           get_activation_name(l->activation));
  }
  printf("=====================================================\n\n");
}

void runet_network_free(RunetNetwork *net)
{
  if (!net) {
    return ;
  }

  for (int i = 0; i < net->curr_size; i++) {
    runet_layer_free(net->layers[i]);
  }
  free(net->layers);
  free(net);
}
