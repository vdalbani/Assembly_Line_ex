//Author Name:				Victor A.

#ifndef STD_LINEMANAGER_H
#define STD_LINEMANAGER_H

#include <iostream>
#include <vector>
#include <deque>
#include "Task.h"
#include "CustomerOrder.h"

namespace std {

	class LineManager
	{
		std::vector<Task*> AssemblyLine;
		std::deque<CustomerOrder> ToBeFilled;
		std::deque<CustomerOrder> Completed;
		unsigned int m_cntCustomerOrder;

		size_t first_task;
		size_t last_task;

	public:
		LineManager(const std::string&, std::vector<Task*>&, std::vector<CustomerOrder>&);
		bool run(std::ostream&);
		void displayCompleted(std::ostream&) const;
		void validateTasks() const;
	};
}
#endif // STD_LINEMANAGER_H
