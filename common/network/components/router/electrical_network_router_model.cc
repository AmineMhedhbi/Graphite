#include "electrical_network_router_model.h"
#include "log.h"

ElectricalNetworkRouterModel::ElectricalNetworkRouterModel(float frequency, UInt32 num_input_ports, UInt32 num_output_ports, UInt32 num_flits_per_buffer, UInt32 flit_width)
{
   _orion_router = new OrionRouter(frequency, num_input_ports, num_output_ports, 1, 1, num_flits_per_buffer, flit_width, OrionConfig::getSingleton());
   initializeCounters();
}

ElectricalNetworkRouterModel::~ElectricalNetworkRouterModel()
{
   delete _orion_router;
}

void
ElectricalNetworkRouterModel::initializeCounters()
{
   _total_dynamic_energy_buffer = 0;
   _total_dynamic_energy_crossbar = 0;
   _total_dynamic_energy_switch_allocator = 0;
   _total_dynamic_energy_clock = 0;
}
