#include "stdafx.h"
#include "parser.h"
#include "Object.h"
namespace lang
{
	template<int count>
	OPNode<count>::OPNode(token *tkn, TreeNode *r) : opcount(count)
	{
		this->Root = r;
		this->Type = NODE_OP;
		this->Token = tkn;
	}
	template<typename object>
	ConstNode<object>::ConstNode(object val, TreeNode *r)
	{
		this->Type = NODE_CONSTANT;
		this->constant = val;
		this->Root = r;
	}
	RootNode::RootNode(TreeNode *r)
	{
		this->Root = r;
		this->Type = NODE_ROOT;
	}
	EvalNode::EvalNode(TreeNode *r)
	{
		this->Type = NODE_EVAL;
		this->Root = r;
	}
	int Operator(tokenenum op)
	{
		switch (op)
		{
			case dot:
				return 1;
			case leftparent://return 17;
			case leftbracket:
				return 2;
			case plusplus:
			case minusminus:
				return 2;
			case _is:
			case _as:
				return 7;
			case pow:
				return 4;
			case modulo:
			case multiply:
			case division:
				return 5;
			case minus:
			case plus:
				return 6;
			case leftshift://<<
			case rightshift://>>
				return 7;
			case greater:
			case greaterequal:
			case less:
			case lessequal:
				return 8;
			case equalequal:
			case notequal:
				return 9;
			case _and:
				return 10;
			case _xor:
				return 11;
			case _or:
				return 12;
			case andand:
				return 13;
			case oror:
				return 14;
			case conditional:
				return 15;
			case equal://=    Å_
			case plusequal://+= Å_
			case minusequal://-   Å_
			case divisionequal:// /=Å_
			case leftshiftequal://<<= Å_
			case rightshiftequal://>>= /
			case multiplyequal: //*=  /
			case moduloequal:  //%=  /
			case andequal:    //&=  /
			case xorequal:   //^=  /
			case orequal:   //|=  /
				return 16;
			default:
				return 0;
		}
	}
	RootNode parser::Tree(token *tkn)
	{
		RootNode root(nullptr);
		while (tkn)
		{
			switch (tkn->type)
			{
				case num:
					root.Child = new EvalNode(&root);
					//((EvalNode*)root.Child)->Child = 
						TreeEval(((EvalNode*)root.Child), tkn);
					return root;
					break;
			}
			tkn = tkn->next;
		}
		return root;
	}
	void TreeNode::SetChild(TreeNode *child)
	{
	}
	void EvalNode::SetChild(TreeNode *child)
	{
		this->Child = child;
	}
	void RootNode::SetChild(TreeNode *child)
	{
		this->Child = child;
	}
	TreeNode* parser::TreeEval(TreeNode *parent, token *&tkn, int opera)
	{
		token *constoken = nullptr;
		ConstNode<ObjectBase*> *val = nullptr;
		switch (tkn->type)
		{
			case num:
				constoken = tkn;
				val = new ConstNode<ObjectBase*>(tkn->object, parent);
				break;
		}
		token *op = tkn->next;
		if (!op)return val;
		BinOPNode *opnode = nullptr;
		tkn = op;
		int thisbinop = Operator(tkn->type);
		switch (op->type)
		{
			case plus:
				if (thisbinop >= opera)
				{
					opnode = new BinOPNode(tkn, parent->Root);
					opnode->Child[0] = parent;
					tkn = tkn->next;
					opnode->Child[1] = TreeEval(opnode, tkn, thisbinop);
					parent->Root->SetChild(opnode);
					return val;
				}
				opnode = new BinOPNode(tkn, parent);
				if (parent->Type == NODE_EVAL)parent->SetChild(opnode);
				opnode->Child[0] = val;
				tkn = tkn->next;
				opnode->Child[1] = TreeEval(opnode, tkn, thisbinop);
				break;
		}
		return opnode;
	}
}
