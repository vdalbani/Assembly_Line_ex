//Author Name:				Victor A.

#include <iostream>
#include <string>
#include "Utilities.h"

namespace std
{
	char Utilities::m_delimiter = '\0';

	void Utilities::setFieldWidth(size_t fieldWidth)
	{
		m_widthField = fieldWidth;

	}

	const std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more)
	{
		const auto tempPos = str.find(getDelimiter(), next_pos);

		auto token = str.substr(next_pos, tempPos - next_pos);

		more = tempPos != std::string::npos;

		if (tempPos == next_pos)
		{
			std::string err = "ERROR - two delimiters with no token between them";
			throw err;
		}

		if (token.length() > getFieldWidth())
		{
			this->setFieldWidth(token.length());
		}

		next_pos = tempPos + 1u;

		return token;
	}

	void Utilities::setDelimiter(const char u_delimiter) {
		m_delimiter = u_delimiter;
	}

}
