#include <string.h>
using namespace std;

#include "dram_cntlr.h"
#include "memory_manager.h"
#include "core.h"
#include "log.h"

namespace PrL1PrL2DramDirectory
{

DramCntlr::DramCntlr(MemoryManager* memory_manager,
      float dram_access_cost,
      float dram_bandwidth,
      float core_frequency,
      bool dram_queue_model_enabled,
      bool dram_queue_model_moving_avg_enabled,
      UInt32 dram_queue_model_moving_avg_window_size,
      string dram_queue_model_moving_avg_type, 
      UInt32 cache_block_size,
      ShmemPerfModel* shmem_perf_model):
   m_memory_manager(memory_manager),
   m_cache_block_size(cache_block_size),
   m_shmem_perf_model(shmem_perf_model)
{
   m_dram_perf_model = new DramPerfModel(dram_access_cost, 
         dram_bandwidth,
         core_frequency, 
         dram_queue_model_enabled, 
         dram_queue_model_moving_avg_enabled,
         dram_queue_model_moving_avg_window_size, 
         dram_queue_model_moving_avg_type);

   m_dram_access_count = new AccessCountMap[NUM_ACCESS_TYPES];
}

DramCntlr::~DramCntlr()
{
   printDramAccessCount();
   delete [] m_dram_access_count;

   delete m_dram_perf_model;
}

void
DramCntlr::getDataFromDram(IntPtr address, core_id_t requester, Byte* data_buf)
{
   if (m_data_map[address] == NULL)
   {
      m_data_map[address] = new Byte[getCacheBlockSize()];
      memset((void*) m_data_map[address], 0x00, getCacheBlockSize());
   }
   memcpy((void*) data_buf, (void*) m_data_map[address], getCacheBlockSize());

   UInt64 dram_access_latency = runDramPerfModel(requester);
   getShmemPerfModel()->incrCycleCount(dram_access_latency);

   addToDramAccessCount(address, READ);
}

void
DramCntlr::putDataToDram(IntPtr address, core_id_t requester, Byte* data_buf)
{
   if (m_data_map[address] == NULL)
   {
      LOG_PRINT_ERROR("Data Buffer does not exist");
   }
   memcpy((void*) m_data_map[address], (void*) data_buf, getCacheBlockSize());

   runDramPerfModel(requester);
   
   addToDramAccessCount(address, WRITE);
}

UInt64
DramCntlr::runDramPerfModel(core_id_t requester)
{
   UInt64 pkt_time = getShmemPerfModel()->getCycleCount();
   UInt64 pkt_size = (UInt64) getCacheBlockSize();
   UInt64 dram_access_latency = m_dram_perf_model->getAccessLatency(pkt_time, pkt_size, requester);
   return dram_access_latency;
}

void
DramCntlr::addToDramAccessCount(IntPtr address, access_t access_type)
{
   m_dram_access_count[access_type][address] = m_dram_access_count[access_type][address] + 1;
}

void
DramCntlr::printDramAccessCount()
{
   for (UInt32 k = 0; k < NUM_ACCESS_TYPES; k++)
   {
      for (AccessCountMap::iterator i = m_dram_access_count[k].begin(); i != m_dram_access_count[k].end(); i++)
      {
         if ((*i).second > 100)
         {
            LOG_PRINT("Dram Cntlr(%i), Address(0x%x), Access Count(%llu), Access Type(%s)", 
                  m_memory_manager->getCore()->getId(), (*i).first, (*i).second,
                  (k == READ)? "READ" : "WRITE");
         }
      }
   }
}

}