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
	void scope::RefInc(){ this->refcount++; }
	void scope::RefDec(){ this->refcount--; if (this->refcount <= 0)delete this; }
	ObjectBase* scope::Run()
	{
		ObjectBase* ret = nullptr;//void
		return ret;
	}
}
