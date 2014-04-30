#ifndef __PARSER__H__
#define __PARSER__H__
#include <string>

namespace lang
{
	enum tokenenum
	{
		identifier,//識別子
		num,//数値
		doublequote,//
		str,//文字列
		leftparent,//(
		rightparent,//)
		comma,//,
		plus,//+
		minus,//-
		multiply,//*
		equalequal,//==
		semicolon,//;
		blockstart,//{
		blockend,//}
		plusplus,//++
		minusminus,//--
		greater,//>
		less,//<
		//equal系 greaterequal~xorequalまで
		greaterequal,//>=
		lessequal,//<=
		modulo,//%
		equal,//=
		plusequal,//+=
		minusequal,//-=
		multiplyequal,//*=
		divisionequal,// /=
		moduloequal,//%=
		leftshiftequal,//<<=
		rightshiftequal,//>>=
		andequal,//&=
		orequal,//|=
		xorequal,//^=
		dot,//.
		division,///
		leftbracket,//[
		rightbracket,//]
		debbug_stop,//$
		//追加演算子
		_or,//|
		oror,//||
		_and,//&
		andand,//&&
		_xor,//^
		notequal,//!
		_not,//~
		notnot,//!LogicalNot
		leftshift,//<<
		rightshift,//>>
		chr,//single str
		none,
		_class,
		_new,
		_this,
		_namespace,
		_using,
		_static,
		//定数
		_true,
		_false,
		_null,
		_break,
		_continue,
		_else,
		_while,
		_for,
		_if,
		_return,
		base,
		colon,
		_foreach,
		_in,
		_is,
		_as,
		_lambda,
		conditional,//?
		_catch,
		_throw,
		_public,
		_private,
		_protected,
		_const,
		pow,
		_get,
		_set,
	};
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
		void Parse(std::wstring&);
		token* Lexical(std::wstring&);
		~parser();
	};
}
#endif
