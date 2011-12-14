#pragma once

#include <string>
using std::string;

#include "network_link_model.h"
#include "fixed_types.h"
#include "contrib/orion/orion.h"

class ElectricalNetworkLinkModel : public NetworkLinkModel
{
public:
   ElectricalNetworkLinkModel(string link_type, float link_frequency, double link_length, UInt32 link_width);
   ~ElectricalNetworkLinkModel();

   volatile double getStaticPower();
   void updateDynamicEnergy(UInt32 num_bit_flips, UInt32 num_flits = 1);
   volatile double getDynamicEnergy() { return _total_dynamic_energy; }

private:
   OrionLink* _orion_link;
   volatile double _total_dynamic_energy;
};
