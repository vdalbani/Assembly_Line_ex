//Author Name:				Victor A.

#ifndef STD_ITEM_H
#define STD_ITEM_H

#include <iostream>
#include <string>
#include <iomanip>
#include "Utilities.h"

namespace std
{
	class Item
	{
		std::string m_name;
		std::string m_description;
		size_t m_serialNumber;
		int m_quantity = 0;
		static size_t m_widthField;
		bool more = false;

	public:

		Item(const std::string line);
		const std::string& getName() const;
		const unsigned int getSerialNumber();
		const unsigned int getQuantity();
		void updateQuantity();
		void display(std::ostream& os, bool full) const;
	};
}
#endif //!STD_ITEM_H
