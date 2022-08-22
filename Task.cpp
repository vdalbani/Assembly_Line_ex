//Author Name:				Victor A.

#include "Task.h"
#include <queue>

namespace std
{
	Task::Task(const std::string& str) : Item(str)
	{
		m_pNextTask = nullptr;
	}

	void Task::runProcess(std::ostream& os)
	{
		if (!m_orders.empty() && !m_orders.back().getOrderFillState())
		{
			m_orders.back().fillItem(*this, os);
		}
	}


	bool Task::moveTask()
	{
		if (m_orders.empty())
		{
			return false;
		}
		else if (m_pNextTask && m_orders.back().getItemFillState(getName()))
		{
			*m_pNextTask += std::move(m_orders.back());
			m_orders.pop_back();
		}

		return true;
	}

	void Task::setNextTask(Task& task)
	{
		m_pNextTask = &task;
	}

	bool Task::getCompleted(CustomerOrder& cust_order)
	{

		if (m_orders.front().getOrderFillState() && !m_orders.empty())
		//if (!m_orders.empty())
		{
			cust_order = std::move(m_orders.back());
			m_orders.pop_back();
			return true;
		}
		return false;

	}

	void Task::validate(std::ostream& os) const
	{
		os << getName() << " --> "
			<< (m_pNextTask ? m_pNextTask->getName() : "END OF LINE") << std::endl;
	}

	Task& Task::operator+=(CustomerOrder&& cust_order)
	{
		m_orders.push_front(std::move(cust_order));
		return *this;
	}
}
