//Author Name:				Victor A.

#ifndef STD_CUSTOMER_ORDER_H
#define STD_CUSTOMER_ORDER_H

#include <string>
#include <utility>
#include "Item.h"

namespace std
{
	//Struct added 
	struct ItemInfo
	{
		std::string m_itemName;
		unsigned int m_serialNumber = 0;
		bool m_fillState = false;

		ItemInfo(std::string src) : m_itemName(src) {};
	};

	class CustomerOrder
	{
		std::string m_name;
		std::string m_product;
		unsigned int m_cntItem = 0;
		ItemInfo** m_lstItem = nullptr;
		static size_t m_widthField;

	public:

		CustomerOrder() {}
		CustomerOrder(std::string&);
		CustomerOrder(const CustomerOrder&) { throw "Error"; };

		CustomerOrder& operator=(const CustomerOrder&) = delete;
		CustomerOrder(CustomerOrder&& custObj) noexcept;
		CustomerOrder& operator=(CustomerOrder&& custObj);

		~CustomerOrder();

		bool getItemFillState(std::string) const;
		bool getOrderFillState() const;
		void fillItem(Item&, std::ostream&);
		void display(std::ostream&) const;
	};
}

#endif //!STD_CUSTOMER_ORDER_H
