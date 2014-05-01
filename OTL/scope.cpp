#include "scope.h"
namespace lang
{
	scope::scope(TreeNode *node) :context(node)
	{
		this->refcount++;
	}


	scope::~scope()
	{
	}
	ObjectBase* scope::Run(){}
}
