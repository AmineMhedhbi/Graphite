#include "topology_builder.h"
#include <iostream>

void setConnectivityNodes(std::vector < std::vector<ReceivingCluster*> >& receiving_clusters,
                         std::vector< std::vector<int> > connectivity_matrix,
                         int num_clusters,
                         int num_clusters_per_layer)
{
    for (int i = 0; i < num_clusters; ++i)
    {
        std::vector<ReceivingCluster*> receiving_clusters_row;
        receiving_clusters_row.resize(num_clusters);
        for (int j = 0; j < num_clusters; ++j)
        {
            if (connectivity_matrix[i][j] != 0)
            {
                ReceivingCluster* receiving_cluster = new ReceivingCluster();
                receiving_cluster -> _layer = j / num_clusters_per_layer;
                receiving_cluster -> _wavelength = connectivity_matrix[i][j] % 100;
                receiving_cluster -> _waveguide = connectivity_matrix[i][j] / 100;
                if (receiving_cluster -> _waveguide % 2 == 0)
                {
                    receiving_cluster -> _direction = CW;
                }
                else
                {
                    receiving_cluster -> _direction = CCW;
                }
                receiving_clusters_row[j] = receiving_cluster;
            }
            else
            {
                receiving_clusters_row[j] = NULL;
            }
        }
        receiving_clusters[i] = receiving_clusters_row;
    }
}

