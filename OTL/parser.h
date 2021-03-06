#ifndef __PARSER__H__
#define __PARSER__H__
#include <string>
#include "Object.h"

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
		TreeNode *Root;
		virtual void SetChild(TreeNode *child);
	};
	template<int count>
	class OPNode : public TreeNode
	{
	public:
		TreeNode *Child[count];
		OPNode(token *tkn, TreeNode *r);
		int opcount;
	};
	class EvalNode : public TreeNode
	{
	public:
		TreeNode *Child;
		EvalNode(TreeNode *r);
		virtual void SetChild(TreeNode *child);
	};
	class RootNode : public TreeNode
	{
	public:
		TreeNode *Child;
		RootNode(TreeNode *r);
		virtual void SetChild(TreeNode *child);
	};
	template<typename object>
	class ConstNode : public TreeNode
	{
	public:
		object constant;
		ConstNode(object val, TreeNode *r);
	};
	typedef OPNode<2> BinOPNode;
	typedef OPNode<1> UnaOPNode;
	const int DEFAULT_OP = 17;
	class parser
	{
	public:
		RootNode root;
		token *firsttoken;
		parser();
		void Parse(std::wstring&);
		token* Lexical(std::wstring&);
		TreeNode* TreeEval(TreeNode *parent, token *&tkn, int opera = DEFAULT_OP);
		RootNode Tree(token *tkn);
		~parser();
	};
}
#endif
