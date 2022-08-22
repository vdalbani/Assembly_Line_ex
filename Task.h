//Author Name:				Victor A.

#ifndef STD_TASK_H
#define STD_TASK_H

#include <iostream>
#include <string>
#include <deque>
#include "CustomerOrder.h"
#include "Item.h"

namespace std
{

	class Task : public Item
	{
		std::deque<CustomerOrder> m_orders;
		Task* m_pNextTask = nullptr;

	public:
		Task(const std::string& str);
		Task(const Task&) = delete;
		Task& operator=(const Task&) = delete;
		Task(Task&&) = delete;
		Task& operator=(Task&&) = delete;

		void runProcess(std::ostream&);
		bool moveTask();
		void setNextTask(Task&);
		bool getCompleted(CustomerOrder&);
		void validate(std::ostream&) const;
		Task& operator+=(CustomerOrder&&);
	};
}
#endif // STD_TASK_H
