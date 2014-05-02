#include "scope.h"
#include "stack.h"

namespace lang
{
	scope::scope(TreeNode *node) :context(node)
	{
		this->refcount++;
	}


	scope::~scope()
	{
	}
	void scope::RefInc(){ this->refcount++; }
	void scope::RefDec(){ this->refcount--; if (this->refcount <= 0)delete this; }
	ObjectBase* scope::Run()
	{
		auto EBP = varstack;
		auto E = this->Run(this->context);
		varstack = EBP;
		return E;
	}
	ObjectBase* scope::Run(TreeNode *context)
	{
		ObjectBase* ret = nullptr;//void
		switch (context->Type)
		{
			case NODE_ROOT:
				context = ((RootNode*)context)->Child;
				ret = Run(context);
				break;
			case NODE_EVAL:
				context = ((EvalNode*)context)->Child;
				ret = Eval(context);
				break;
		}
		return ret;
	}
	ObjectBase* scope::Eval(TreeNode *context, int op)
	{
		ObjectBase* ret = nullptr;//void
		TreeNode *op1, *op2;
		ObjectBase *opr1, *opr2;
		int thisop = 17;
		switch (context->Type)
		{
			case NODE_OP:
				op1 = ((BinOPNode*)context)->Child[0];
				op2 = ((BinOPNode*)context)->Child[1];
				opr1 = Eval(op1, thisop);
				opr2 = Eval(op2, thisop);
				ret = *opr1 + opr2;
				break;
			case NODE_CONSTANT:
				ret = ((ConstNode<ObjectBase*>*)context)->constant;
				break;
		}
		return ret;
	}
}
