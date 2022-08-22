//Author Name:				Victor A.

#include <iostream>
#include <string>
#include "Item.h"

namespace std
{

	size_t Item::m_widthField = 0;

	Item::Item(const std::string line)
	{

		Utilities utilities;
		bool more = true;
		size_t next = 0u;


		m_name = utilities.extractToken(line, next, more);
		m_serialNumber = std::stoi(utilities.extractToken(line, next, more));
		m_quantity = std::stoi(utilities.extractToken(line, next, more));
		m_widthField = utilities.getFieldWidth();
		m_description = utilities.extractToken(line, next, more);
	}

	const std::string& Item::getName() const
	{
		return m_name;
	}


	const unsigned int Item::getSerialNumber()
	{
		return m_serialNumber++;
	}

	const unsigned int Item::getQuantity()
	{
		return m_quantity;
	}

	void Item::updateQuantity() {
		if (m_quantity >= 0) {
			m_quantity--;
		}
	}

	void Item::display(std::ostream& os, bool full) const {
		os << std::setfill(' ') << std::setw(m_widthField) << std::left << m_name << " [";
		os << std::setfill('0') << std::setw(6) << std::left << m_serialNumber << "] ";

		if (full == true)
		{
			os << std::setfill(' ') << "Quantity: " << std::setw(m_widthField) << std::left << m_quantity;
			os << " Description: " << m_description;
		}
		os << std::endl;

	}
}
