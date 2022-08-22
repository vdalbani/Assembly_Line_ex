//Author Name:				Victor A.

#include <iostream>
#include <algorithm>
#include <iomanip>
#include <string>
#include "CustomerOrder.h"

namespace std
{

	size_t CustomerOrder::m_widthField = 1;

	CustomerOrder::CustomerOrder(std::string& record)
	{
		Utilities m_utility;
		bool more = false;
		char delimiter = m_utility.getDelimiter();

		size_t recordStart = 0;
		size_t recordEnd = record.find(delimiter);

		m_name = record.substr(recordStart, recordEnd);

		recordStart = recordEnd + 1;
		recordEnd = record.find(delimiter, recordStart);
		m_product = m_utility.extractToken(record, recordStart, more);
		m_cntItem = std::count(record.begin(), record.end(), m_utility.getDelimiter()) - 1;

		if (m_cntItem > 0)
		{
			m_lstItem = new ItemInfo*[m_cntItem];

			for (size_t i = 0;i < m_cntItem;i++)
			{
				recordStart = recordEnd + 1;

				if (record.find(delimiter, recordEnd + 1) != std::string::npos)
					recordEnd = record.find(delimiter, recordStart);
				else
					recordEnd = record.length();
				
				m_lstItem[i] = new ItemInfo(m_utility.extractToken(record, recordStart, more));
			}
		}

		if (m_widthField < m_utility.getFieldWidth())
		{
			m_widthField = m_utility.getFieldWidth();
		}
	}


	CustomerOrder::CustomerOrder(CustomerOrder&& obj) noexcept
	{
		*this = std::move(obj);
	}

	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& obj) {
		if (this != &obj) {
			delete[] m_lstItem;
			m_lstItem = obj.m_lstItem;
			m_name = obj.m_name;
			m_product = obj.m_product;
			m_cntItem = obj.m_cntItem;
			obj.m_lstItem = nullptr;
		}
		return *this;
	}

	CustomerOrder::~CustomerOrder()
	{
		delete[] m_lstItem;
		m_lstItem = nullptr;
	}

	bool CustomerOrder::getItemFillState(std::string str) const
	{
		for (size_t i = 0;i < m_cntItem;i++)
			if (m_lstItem[i]->m_itemName == str)
			{
				if (m_lstItem[i]->m_fillState == false)
				{
					return false;
				}
			}
		return true;
	}

	bool CustomerOrder::getOrderFillState() const
	{
		for (size_t i = 0; i < m_cntItem; i++)
			if (m_lstItem[i]->m_fillState == false)
			{
				return false;
			}
		return true;
	}


	void CustomerOrder::fillItem(Item& item, std::ostream& os)
	{
		for (size_t i = 0;i < m_cntItem;i++)
		{
			if (item.getName() == m_lstItem[i]->m_itemName)
			{
				if (item.getQuantity() == 0)
				{
					os << "Unable to fill " << m_name << ", " << m_product << "[" << item.getName() << "]" << std::endl;
				}
				else
					item.updateQuantity();
				m_lstItem[i]->m_serialNumber = item.getSerialNumber();
				m_lstItem[i]->m_fillState = true;
				os << "Filled " << m_name << ", " << m_product << "[" << item.getName() << "]" << std::endl;
			}
		}
	}


	void CustomerOrder::display(std::ostream& os) const
	{
		os << m_name << " - " << m_product << std::endl;

		for (size_t i = 0;i < m_cntItem;i++)
		{
			//Line 1
			os << "[" << std::setw(6) << std::setfill('0') << m_lstItem[i]->m_serialNumber << "] ";
			//Line 2
			os << std::setw(m_widthField) << std::setfill(' ') << m_lstItem[i]->m_itemName << " - ";

			os << (m_lstItem[i]->m_fillState == true ? "FILLED" : "MISSING") << std::endl;

		}
	}
}
