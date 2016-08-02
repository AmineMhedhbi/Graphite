#include "../helpers/configfile/config_file.h"

#include <iostream>
#define CONFIG_FILE_PATH "../../../../ornoc_topology.cfg"

int main()
{
    // power of 2, number of clusters chosen to read proper config
    int num_clusters = 2;
    ConfigFile cf(CONFIG_FILE_PATH, num_clusters);

    int num_waveguides, num_layers;
    num_waveguides = cf.Value("general" ,"num_waveguides");
    num_layers = cf.Value("general", "num_layers");
    std::cout << std::endl;
    std::cout << "#waveguides = " << num_waveguides << ", "
              << "#layers = " << num_layers
              << std::endl << std::endl;
     
    cf.print_connectivity_matrix();
    std::cout << std::endl;
    return 0;
}
