//Author Name:				Victor A.

#ifndef STD_UTILITIES_H
#define STD_UTILITIES_H

#include <string>

namespace std
{
	class Utilities
	{
		size_t m_widthField = 1;
		static char m_delimiter;

	public:
		void setFieldWidth(size_t);

		size_t getFieldWidth() const { return m_widthField; };

		const std::string extractToken(const std::string& str, size_t& next_pos, bool& more);

		static void setDelimiter(const char u_delimiter);
		
		const char getDelimiter() const { return m_delimiter; };
	};

}
#endif // !STD_UTILITIES_H
