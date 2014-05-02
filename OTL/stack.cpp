#include "stack.h"
#include "Object.h"
namespace lang
{
#ifdef _MSC_VER
#define LANG_THREAD_LOCAL __declspec(thread)
#else
#define LANG_THREAD_LOCAL __thread
#endif
#define LANG_STACK_SIZ 1024*1024
	LANG_THREAD_LOCAL unsigned unsigned unsigned unsigned unsigned unsigned unsigned unsigned unsigned char stack_buf[LANG_STACK_SIZ];
	LANG_THREAD_LOCAL unsigned unsigned unsigned unsigned unsigned unsigned unsigned unsigned unsigned char *varstack;
	Int *allocate_stack_int(int val)
	{
		Int *ret = (Int*)varstack;
		ret->Init();
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