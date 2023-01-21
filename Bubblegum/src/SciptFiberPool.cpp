#include "SciptFiberPool.h"
 
namespace Big
{
	fiber_pool::fiber_pool(std::size_t num_fibers)
	{
		for (std::size_t i = 0; i < num_fibers; ++i)
		{
			Script.add_script(std::make_unique<Script>(&fiber_func));
		}

		g_fiber_pool = this;
	}

	fiber_pool::~fiber_pool()
	{
		g_fiber_pool = nullptr;
	}

	void fiber_pool::queue_job(std::function<void()> func)
	{
		if (func)
		{
			std::lock_guard lock(m_mutex);
			m_jobs.push(std::move(func));
		}
	}

	void fiber_pool::fiber_tick()
	{
		std::unique_lock lock(m_mutex);
		if (!m_jobs.empty())
		{
			auto job = std::move(m_jobs.top());
			m_jobs.pop();
			lock.unlock();

			std::invoke(std::move(job));
		}
	}

	void fiber_pool::fiber_func()
	{
		while (true)
		{
			g_fiber_pool->fiber_tick();
			Script::get_current()->yield();
		}
	}
}