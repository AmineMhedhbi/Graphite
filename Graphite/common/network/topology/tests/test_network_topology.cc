include "../network_topology.h"

#define CONFIG_FILE_PATH "../../../../ornoc_topology.cfg"

int main()
{
    NetworkTopoloty ornoc_topology(CONFIG_FILE_PATH);
    ornoc_topology.print_conncetivity_receivers_info();

    return 0;
}
