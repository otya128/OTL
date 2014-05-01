#include "parser.h"
#include <iostream>

namespace lang
{
	bool isIden(wchar_t c)
	{
		return (c >= L'A'&&c <= L'Z') || (c >= L'a'&&c <= L'z') || (c >= L'0'&&c <= L'9') || (c == L'_');
	}
	bool isNum(wchar_t c)
	{
		return c >= L'0'&&c <= L'9';
	}
	parser::parser()
	{
	}
	parser::~parser()
	{
	}
	void parser::Parse(std::wstring& text)
	{
		Lexical(text);
	}
	bool util_matchw(std::wstring& text, wchar_t* match, int index = 0)
	{
		int i = index;
		int j = 0;
		while (true)
		{
			if (!match[i])return true;
			if (text[i] != match[i]) return false;
			i++;
			j++;
		}
	}
	token::token(){}
	token::token(std::wstring& n, tokenenum t, int s, int l, int L) : name(n), type(t), start(s), length(l), line(L), next(0){}
	token::token(wchar_t* n, tokenenum t, int s, int l, int L) : name(n), type(t), start(s), length(l), line(L), next(0){}
	token::token(wchar_t n, tokenenum t, int s, int l, int L) : type(t), start(s), length(l), line(L), next(0){ name = n; }
	void TokenAdd(token*& tkn, token* add)
	{
		tkn->next = add;
		add->prev = tkn;
		tkn = add;
	}
#define DEFTOKENOP(type, op,opequ) if(nextchr == L'='){TokenAdd(tkn, new token(opequ     , type, index, 1, __line__));break;}TokenAdd(tkn, new token(op, type, index, 1, __line__))
#define DEFTOKENCHR(type) TokenAdd(tkn, new token(chr, type, index, 1, __line__))
#define DEFTOKENSTR(chr, type, len) TokenAdd(tkn, new token(chr, type, index, len, __line__));index += len - 1;
	token* parser::Lexical(std::wstring& text)
	{
		token *tkn = new token, *firsttkn = tkn;
		enum state
		{
			None,
			Num,
			Str,
			Iden,
		} stat = None;
		size_t index = 0;
		int __line__ = 0;
		std::wstring name;
		while (true)
		{
			wchar_t chr = text[index];
			wchar_t nextchr = 0;
			if (index + 1 < text.length())nextchr = text[index + 1];
			wchar_t prevchr = 0;
			if (index)prevchr = text[index - 1];
			switch (stat)
			{
				case None:
					switch (chr)
					{
						case L'+':
							DEFTOKENOP(plus, L'+', L"+=");
							break;
						case L'-':
							DEFTOKENCHR(minus);
							break;
						case L'*':
							DEFTOKENCHR(multiply);
							break;
						case L'/':
							DEFTOKENCHR(division);
							break;
						case L'%':
							DEFTOKENCHR(modulo);
							break;
						case L'"':
							stat = Str; index--;
							continue;
						default:
							if (isNum(chr))
							{
								stat = Num;
								continue;
							}
							if (isIden(chr))
							{
								stat = Iden;
								continue;
							}
							break;
					}
					break;
				case Num:
					if (isNum(chr))
					{
						name += chr;
					}
					else
					{
						TokenAdd(tkn, new token(name, num, index, name.length(), __line__)); name.clear();
						stat = None;
						continue;
					}
					break;
				case Str:
					if (chr!=L'"')
					{
						name += chr;
					}
					else
					{
						TokenAdd(tkn, new token(name, str, index, name.length(), __line__)); name.clear();
						stat = None;
						continue;
					}
					break;
				case Iden:
					if (isIden(chr))
					{
						name += chr;
					}
					else
					{
						TokenAdd(tkn, new token(name, identifier, index, name.length(), __line__)); name.clear();
						stat = None;
						continue;
					}
					break;
				default:
					break;
			}
			if (!chr) break;
			index++;
		}
		token* tkk = firsttkn->next;
		while (tkk)
		{
			std::wcout << tkk->name << std::endl;
			tkk = tkk->next;
		}
		return firsttkn;
	}
}
