#include "../network_topology.h"

#define CONFIG_FILE_PATH "../../../../ornoc_topology.cfg"

int main()
{
    NetworkTopology ornoc_topology;
    ornoc_topology.init(CONFIG_FILE_PATH, 32);
    ornoc_topology.print_conncetivity_receivers_info();

    return 0;
}
