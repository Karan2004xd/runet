#ifndef __NETWORK_H__
#define __NETWORK_H__

#define MAGIC_NUMBER 0x52554E45

typedef struct runet_layer RunetLayer;
typedef struct runet_matrix RunetMatrix;

struct runet_network {
  RunetLayer **layers;
  int curr_size;
  int capacity;
};

typedef struct runet_network RunetNetwork;

/**
  * @brief Creates a new network.
  * * This function creates a new network with a certain capacity.
  *
  * @param capacity The maximum numbers of layers it can hold.
  * @return RunetNetwork* A pointer to the new network (can be NULL).
  */
RunetNetwork *runet_network_create(int capacity);

/**
  * @brief Frees the network memory.
  * * This function frees or destroys the provided network.
  *
  * @param net A pointer to the network to free.
  */
void runet_network_free(RunetNetwork *net);

/**
  * @brief Adds a layer to the network.
  * * This function simply adds the provided layer to the network.
  *
  * @param net A pointer to the desitination network.
  * @param layer A pointer to the layer to add.
  *
  * @return int A status code specifying operation success or failure.
  * (refer to RUNET_STATUS_CODE for more information)
  */
int runet_network_add(RunetNetwork *net, RunetLayer *layer);

/**
  * @brief Executes the network to make prediction.
  * * This function executes each layer (using their underlying
  * forwarding logic) and generates output prediction with every layer.
  *
  * @param net A pointer to the desitination network.
  * @param input The input data matrix.
  * @param output The output data matrix (result matrix).
  *
  * @return int A status code specifying operation success or failure.
  * (refer to RUNET_STATUS_CODE for more information)
  */
int runet_network_predict(RunetNetwork *net,
                          const RunetMatrix *input,
                          RunetMatrix **output);

/**
  * @brief Prints out the summary of the network.
  *
  * @param net A const pointer to the network.
  */
void runet_network_summary(const RunetNetwork *net);

/**
  * @brief Creates a new network.
  * * This function creates a new network by reading the
  * binary file of data.
  *
  * @param path A const pointer specifying the path of file.
  * @param status_code A pointer specifying the status_code.
  *
  * @return RunetNetwork* A pointer to the new network (can be NULL).
  */
RunetNetwork *runet_network_from_file(const char *path, int *status_code);

#endif // __NETWORK_H__
