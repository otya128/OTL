#ifndef __PARSER__H__
#define __PARSER__H__
#include <string>

namespace lang
{
	enum tokenenum
	{
		identifier,//���ʎq
		num,//���l
		doublequote,//
		str,//������
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
		//equal�n greaterequal~xorequal�܂�
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
		//�ǉ����Z�q
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
		//�萔
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
		token();
		token(std::wstring& n, tokenenum t, int s, int l, int L);
		token(wchar_t* n, tokenenum t, int s, int l, int L);
		token(wchar_t n, tokenenum t, int s, int l, int L);
		std::wstring name;
		tokenenum type;
		int start;
		int length;
		int line;
		struct token* prev;
		struct token* next;
	};
	enum NodeType
	{
		EVAL = 1,
		OP,
	};
	class TreeNode
	{
	public:
		NodeType Type;
		token* Token;
		TreeNode() = delete;
		tokenenum GetTokenType();
	};
	class OPNode : public TreeNode
	{
	public:
		OPNode();

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
