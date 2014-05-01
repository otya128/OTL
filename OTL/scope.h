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
		ObjectBase* Run();
		ObjectBase* Eval(TreeNode *&context, int op = 17);
	};
}
#endif
