#include "network_topology.h"
#include "topology_builder.h"
#include "helpers/configfile/config_file.h"
#include <assert.h>
#include <iostream>

void NetworkTopology::init(std::string const& configFile,
                           int num_clusters)
{
    ConfigFile confFile(configFile, num_clusters);

    _num_layers = confFile.Value("general", "num_layers");
    _num_clusters = num_clusters;
    switch(_num_clusters)
    {
        case 2:  _num_wavelengths = confFile.Value("num_wavelengths", "two_clusters_wavelengths");
                 break;
        case 4:  _num_wavelengths = confFile.Value("num_wavelengths", "four_clusters_wavelengths");
                 break;
        case 8:  _num_wavelengths = confFile.Value("num_wavelengths", "eight_clusters_wavelengths");
                 break;
        case 16: _num_wavelengths = confFile.Value("num_wavelengths", "sixteen_clusters_wavelengths");
                 break;
        case 32: _num_wavelengths = confFile.Value("num_wavelengths", "thirtytwo_clusters_wavelengths");
                 break;
        case 64: _num_wavelengths = confFile.Value("num_wavelengths", "sixtyfour_clusters_wavelengths;");
                 break;
        default: _num_wavelengths = confFile.Value("num_wavelengths", "eight_clusters_wavelengths;");
                 break;
    }
    std::vector< std::vector<int> > connectivity_matrix =
            confFile.get_connectivity_matrix();
 
    assert((int)connectivity_matrix.size() == _num_clusters);
    _num_clusters_per_layer = _num_clusters/_num_layers;

    _receiving_clusters.resize(_num_clusters);

    setConnectivityNodes(_receiving_clusters,
                         connectivity_matrix,
                         _num_clusters,
                         _num_clusters_per_layer);
}

void NetworkTopology::print_conncetivity_receivers_info()
{
    std::cout << std::endl << "number of wavelengths: " << _num_wavelengths << std::endl;
    for (int i = 0; i < _num_clusters; ++i)
    {
        std::cout << std::endl <<  "======================================" << std::endl;
        std::cout << "Cluster " << i << " is connected to:" << std::endl;
        for (int j = 0; j < _num_clusters; ++j)
        {
            if (_receiving_clusters[i][j] != NULL)
            {
                std::cout << "Cluster " << j  << " on layer "
                          << _receiving_clusters[i][j] -> _layer + 1
                          << ", sends on wavelength "
                          << _receiving_clusters[i][j] -> _wavelength
                          << ", of waveguide "
                          << _receiving_clusters[i][j] -> _waveguide + 1;
                if (_receiving_clusters[i][j] -> _direction == CW)
                {
                    std::cout << " in the CW direction." << std::endl;
                }
                else if (_receiving_clusters[i][j] -> _direction == CCW)
                {
                    std::cout << " in the CCW direction." << std::endl;
                }
            }
        }
    }
}

