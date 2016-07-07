#include "../helpers/configfile/config_file.h"

#include <iostream>
#define CONFIG_FILE_PATH "../../../../ornoc_topology.cfg"

int main()
{
    ConfigFile cf(CONFIG_FILE_PATH);

    int num_waveguides = cf.Value("general" ,"num_waveguides");
    std::cout << std::endl;
    std::cout << "num waveguides = " << num_waveguides << std::endl;
    std::cout << std::endl;
    
    cf.print_connectivity_matrix();
    std::cout << std::endl;
    return 0;
}
