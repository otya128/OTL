#ifndef __LANG__STACK__H__
#include "stdafx.h"
#define __LANG__STACK__H__
namespace lang
{
	void thread_init();
	void thread_end();
	Int *allocate_stack_int(int val);
}
#endif