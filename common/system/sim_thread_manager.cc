#include "sim_thread_manager.h"

#include "lock.h"
#include "log.h"
#include "config.h"
#include "simulator.h"
#include "mcp.h"

SimThreadManager::SimThreadManager()
   : m_active_threads(0)
{
}

SimThreadManager::~SimThreadManager()
{
   LOG_ASSERT_WARNING(m_active_threads == 0,
                      "Threads still active when SimThreadManager exits.");
}

void SimThreadManager::spawnSimThreads()
{
   UInt32 num_sim_threads = Config::getSingleton()->getNumLocalCores();

   LOG_PRINT("Starting %d threads on proc: %d\n.", num_sim_threads, Config::getSingleton()->getCurrentProcessNum());

   m_sim_threads = new SimThread [num_sim_threads];

   for (UInt32 i = 0; i < num_sim_threads; i++)
   {
      LOG_PRINT("Starting thread %i", i);
      m_sim_threads[i].spawn();
   }

   while (m_active_threads < num_sim_threads)
      sched_yield();

   LOG_PRINT("Threads started: %d.", m_active_threads);
}

void SimThreadManager::quitSimThreads()
{
   LOG_PRINT("Sending quit messages.");

   Transport::Node *global_node = Transport::getSingleton()->getGlobalNode();
   UInt32 num_local_cores = Config::getSingleton()->getNumLocalCores();

   // This is something of a hard-wired emulation of Network::netSend
   // ... not the greatest thing to do, but whatever.
   NetPacket pkt(0, SIM_THREAD_TERMINATE_THREADS, 0, 0, 0, NULL);
   const Config::CoreList &core_list = Config::getSingleton()->getCoreListForProcess(Config::getSingleton()->getCurrentProcessNum());

   for (UInt32 i = 0; i < num_local_cores; i++)
   {
      core_id_t core_id = core_list[i];
      pkt.receiver = core_id;
      global_node->send(core_id, &pkt, pkt.bufferSize());
   }

   LOG_PRINT("Waiting for local sim threads to exit.");

   while (m_active_threads > 0)
      sched_yield();

   Transport::getSingleton()->barrier();

   LOG_PRINT("All threads have exited.");
}

void SimThreadManager::simThreadStartCallback()
{
   m_active_threads_lock.acquire();
   ++m_active_threads;
   m_active_threads_lock.release();
}

void SimThreadManager::simThreadExitCallback()
{
   m_active_threads_lock.acquire();
   --m_active_threads;
   m_active_threads_lock.release();
}
