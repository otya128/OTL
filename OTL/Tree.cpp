#include "stdafx.h"
#include "parser.h"
#include "Object.h"
namespace lang
{
	template<int count>
	OPNode<count>::OPNode(token *tkn)
	{
		this->Type = NODE_OP;
		this->Token = tkn;
	}
	template<typename object>
	ConstNode<object>::ConstNode(object val)
	{
		this->Type = NODE_CONSTANT;
		this->constant = val;
	}
	RootNode::RootNode()
	{
		this->Type = NODE_ROOT;
	}
	RootNode parser::Tree(token *tkn)
	{
		RootNode root;
		while (tkn)
		{
			switch (tkn->type)
			{
				case num:
					root.Child = TreeEval(tkn);
					return root;
					break;
			}
			tkn = tkn->next;
		}
		return root;
	}
	TreeNode* parser::TreeEval(token *&tkn)
	{
		token *constoken = nullptr;
		ConstNode<ObjectBase*> *val = nullptr;
		switch (tkn->type)
		{
			case num:
				constoken = tkn;
				val = new ConstNode<ObjectBase*>(tkn->object);
				break;
		}
		token *op = tkn->next;
		if (!op)return val;
		BinOPNode *opnode = nullptr;
		tkn = op;
		switch (op->type)
		{
			case plus:
				opnode = new BinOPNode(tkn);
				opnode->Child[0] = val;
				tkn = tkn->next;
				opnode->Child[1] = TreeEval(tkn);
				return opnode;
		}
	}
}
