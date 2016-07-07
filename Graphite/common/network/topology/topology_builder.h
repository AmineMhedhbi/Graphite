#ifndef TOPOLOGY_BUILDER_H
#define TOPOLOGY_BUILDER_H

#include "cluster_node.h"
#include <vector>

void setConnectivityNodes(std::vector < std::vector<ReceivingCluster*> >& receiving_clusters,
                         std::vector< std::vector<int> > connectivity_matrix,
                         int num_clusters,
                         int num_clusters_per_layer);

#endif // TOPOLOGY_BUILDER_H
