#ifndef NETWORK_TOPOLOGY_H
#define NETWORK_TOPOLOGY_H

#include "cluster_node.h"
#include <string>
#include <vector>

class NetworkTopology
{
    public:
        void init(std::string const& configFile, int num_clusters);
        std::vector < std::vector<ReceivingCluster*> > _receiving_clusters;
        void print_conncetivity_receivers_info();

    private:
        int _num_layers;
        int _num_clusters;
        int _num_clusters_per_layer;
        int _num_wavelengths;
};

#endif // NETWORK_TOPOLOGY_H
