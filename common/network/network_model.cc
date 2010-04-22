#include <cassert>
using namespace std;

#include "network.h"
#include "network_types.h"

#include "network_model_magic.h"
#include "network_model_emesh_hop_counter.h"
#include "network_model_analytical.h"
#include "network_model_emesh_hop_by_hop_basic.h"
#include "network_model_emesh_hop_by_hop_broadcast_tree.h"
#include "log.h"

NetworkModel::NetworkModel(Network *network) : 
   _network(network) 
{}

NetworkModel*
NetworkModel::createModel(Network *net, UInt32 model_type, EStaticNetwork net_type)
{
   switch (model_type)
   {
   case NETWORK_MAGIC:
      return new NetworkModelMagic(net);

   case NETWORK_EMESH_HOP_COUNTER:
      return new NetworkModelEMeshHopCounter(net);

   case NETWORK_ANALYTICAL_MESH:
      return new NetworkModelAnalytical(net, net_type);

   case NETWORK_EMESH_HOP_BY_HOP_BASIC:
      return new NetworkModelEMeshHopByHopBasic(net);

   case NETWORK_EMESH_HOP_BY_HOP_BROADCAST_TREE:
      return new NetworkModelEMeshHopByHopBroadcastTree(net);

   default:
      assert(false);
      return NULL;
   }
}

UInt32 
NetworkModel::parseNetworkType(string str)
{
   if (str == "magic")
      return NETWORK_MAGIC;
   else if (str == "emesh_hop_counter")
      return NETWORK_EMESH_HOP_COUNTER;
   else if (str == "analytical")
      return NETWORK_ANALYTICAL_MESH;
   else if (str == "emesh_hop_by_hop_basic")
      return NETWORK_EMESH_HOP_BY_HOP_BASIC;
   else if (str == "emesh_hop_by_hop_broadcast_tree")
      return NETWORK_EMESH_HOP_BY_HOP_BROADCAST_TREE;
   else
      return (UInt32)-1;
}

pair<bool,SInt32> 
NetworkModel::computeCoreCountConstraints(UInt32 network_type, SInt32 core_count)
{
   switch (network_type)
   {
      case NETWORK_MAGIC:
      case NETWORK_EMESH_HOP_COUNTER:
      case NETWORK_ANALYTICAL_MESH:
         return make_pair(false,core_count);

      case NETWORK_EMESH_HOP_BY_HOP_BASIC:
      case NETWORK_EMESH_HOP_BY_HOP_BROADCAST_TREE:
         return NetworkModelEMeshHopByHopGeneric::computeCoreCountConstraints(core_count);

      default:
         LOG_PRINT_ERROR("Unrecognized network type(%u)", network_type);
         return make_pair(false,-1);
   }
}

pair<bool, vector<core_id_t> > 
NetworkModel::computeMemoryControllerPositions(UInt32 network_type, SInt32 num_memory_controllers, SInt32 core_count)
{
   switch (network_type)
   {
      case NETWORK_MAGIC:
      case NETWORK_EMESH_HOP_COUNTER:
      case NETWORK_ANALYTICAL_MESH:
         {
            SInt32 spacing_between_memory_controllers = core_count / num_memory_controllers;
            vector<core_id_t> core_list_with_memory_controllers;
            for (core_id_t i = 0; i < num_memory_controllers; i++)
            {
               assert((i*spacing_between_memory_controllers) < core_count);
               core_list_with_memory_controllers.push_back(i * spacing_between_memory_controllers);
            }
            
            return make_pair(false, core_list_with_memory_controllers);
         }

      case NETWORK_EMESH_HOP_BY_HOP_BASIC:
      case NETWORK_EMESH_HOP_BY_HOP_BROADCAST_TREE:
         return NetworkModelEMeshHopByHopGeneric::computeMemoryControllerPositions(num_memory_controllers, core_count);

      default:
         LOG_PRINT_ERROR("Unrecognized network type(%u)", network_type);
         return make_pair(false, vector<core_id_t>());
   }
}
