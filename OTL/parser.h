#ifndef __PARSER__H__
#define __PARSER__H__
#include <string>
#include "Object.h"

namespace lang
{
	enum tokenenum
	{
		identifier,//éØï éq
		num,//êîíl
		doublequote,//
		str,//ï∂éöóÒ
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
		//equalån greaterequal~xorequalÇ‹Ç≈
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
		//í«â¡ââéZéq
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
		//íËêî
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
		ObjectBase *object;
		struct token* prev;
		struct token* next;
	};
	enum NodeType
	{
		NODE_ROOT = 1,
		NODE_EVAL,
		NODE_OP,
		NODE_CONSTANT
	};
	class TreeNode
	{
	protected:
		inline TreeNode(){}
	public:
		NodeType Type;
		token* Token;
		tokenenum GetTokenType();
	};
	template<int count>
	class OPNode : public TreeNode
	{
	public:
		TreeNode *Child[count];
		OPNode(token *tkn);
	};
	class RootNode : public TreeNode
	{
	public:
		TreeNode *Child;
		RootNode();
	};
	template<typename object>
	class ConstNode : public TreeNode
	{
	public:
		object constant;
		ConstNode(object val);
	};
	typedef OPNode<2> BinOPNode;
	typedef OPNode<1> UnaOPNode;
	class parser
	{
	public:
		RootNode root;
		token *firsttoken;
		parser();
		void Parse(std::wstring&);
		token* Lexical(std::wstring&);
		TreeNode* TreeEval(token *&tkn);
		RootNode Tree(token *tkn);
		~parser();
	};
}
#endif
