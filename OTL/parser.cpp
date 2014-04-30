#include "parser.h"


namespace lang
{
	parser::parser()
	{
	}
	parser::~parser()
	{
	}
	void parser::Parse(std::string& text)
	{
		Lexical(text);
	}
	token* parser::Lexical(std::string& text)
	{

	}
}
