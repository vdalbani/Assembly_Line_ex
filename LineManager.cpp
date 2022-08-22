//Author Name:				Victor A.

#include <iostream>
#include <fstream>
#include <vector>
#include "Task.h"
#include "LineManager.h"
#include "Utilities.h"

namespace std
{
	LineManager::LineManager(const std::string& str, std::vector<Task*>& v_tasks, std::vector<CustomerOrder>& customerOrd) :
		m_cntCustomerOrder(0)
	{
		Utilities utl;
		size_t nextPos = 0;
		auto more = true;
		auto taskOne = true;

		std::string token;
		std::string next;
		std::ifstream file(str);

		while (!file.eof())
		{
			std::getline(file, token);

			auto tempTask = utl.extractToken(token, nextPos, more);

			if (more)
				next = utl.extractToken(token, nextPos, more);


			for (size_t i = 0; i < v_tasks.size(); ++i)
			{
				if (v_tasks[i]->getName() == tempTask)
				{
					if (taskOne)
					{
						first_task = i;
						taskOne = !taskOne;
					}

					if (next.empty())
					{
						last_task = i;
					}
					else
					{
						for (size_t j = 0; j < v_tasks.size(); ++j)
							if (v_tasks[j]->getName() == next)
							{
								v_tasks[i]->setNextTask(*v_tasks[j]);
								break;
							}
					}

					break;
				}
			}

			nextPos = 0;
			more = true;
			tempTask.clear();
			next.clear();
		}

		for (auto& co : customerOrd)
			ToBeFilled.push_front(std::move(co));

		customerOrd.erase(customerOrd.begin(), customerOrd.end());
		AssemblyLine = v_tasks;
	}

	bool LineManager::run(std::ostream& out)
	{
		auto isRun = true;

		if (!ToBeFilled.empty())
		{
			*AssemblyLine[first_task] += std::move(ToBeFilled.back());
			ToBeFilled.pop_back();

		}

		for (auto& i : AssemblyLine)
			i->runProcess(out);

		CustomerOrder buffer;

		if (AssemblyLine[last_task]->getCompleted(buffer))
			Completed.push_back(std::move(buffer));

		for (auto& i : AssemblyLine)
			if (i->moveTask())
				isRun = false;

		return isRun;
	}

	void LineManager::displayCompleted(std::ostream& out) const
	{
		if (!Completed.empty())
			for (const auto& i : Completed)
				i.display(out);
	}

	void LineManager::validateTasks() const
	{
		if (!AssemblyLine.empty())
			for (auto i : AssemblyLine)
				i->validate(std::cout);
	}
}
