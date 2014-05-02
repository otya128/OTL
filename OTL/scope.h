#ifndef __SCOPE__H__
#define __SCOPE__H__
#include "stdafx.h"
#include "parser.h"
namespace lang
{
	class scope
	{
	protected:
		int refcount;
	public:
		TreeNode *context;
		scope(TreeNode *node);
		~scope();
		void RefInc();
		void RefDec();
		ObjectBase* Run();
		ObjectBase* Run(TreeNode *context);
		ObjectBase* Eval(TreeNode *context, int op = 17);
	};
}
#endif
