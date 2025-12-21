#ifndef __NETWORK_H__
#define __NETWORK_H__

typedef struct runet_layer RunetLayer;
typedef struct runet_matrix RunetMatrix;

struct runet_network {
  RunetLayer **layers;
  int curr_size;
  int capacity;
};

typedef struct runet_network RunetNetwork;

RunetNetwork *runet_network_create(int capacity);

void runet_network_free(RunetNetwork *net);

int runet_network_add(RunetNetwork *net, RunetLayer *layer);

int runet_network_predict(RunetNetwork *net,
                          const RunetMatrix *input,
                          RunetMatrix **output);

void runet_network_summary(const RunetNetwork *net);

int runet_network_from_file(RunetNetwork *net, const char *path);

#endif // __NETWORK_H__
