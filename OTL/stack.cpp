#include "stack.h"
#include "Object.h"
namespace lang
{
	LANG_THREAD_LOCAL unsigned unsigned unsigned unsigned unsigned unsigned unsigned unsigned unsigned char stack_buf[LANG_STACK_SIZ];
	LANG_THREAD_LOCAL unsigned unsigned unsigned unsigned unsigned unsigned unsigned unsigned unsigned char *varstack;
	Int *alloca_int(int val)
	{
		Int *ret = (Int*)varstack;
		ret->Init();
		ret->data = val;
		varstack += sizeof(Int);
		return ret;
	}
	void thread_init()
	{
		varstack = stack_buf;
	}
	void thread_end()
	{

	}
}