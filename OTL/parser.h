#ifndef __PARSER__H__
#define __PARSER__H__
#include <string>

namespace lang
{
	enum tokenenum
	{};
	struct token
	{
		std::string name;
		tokenenum type;
		struct token* prev;
		struct token* next;
	};
	class parser
	{
	public:
		parser();
		void Parse(std::string&);
		token* Lexical(std::string&);
		~parser();
	};
}
#endif
