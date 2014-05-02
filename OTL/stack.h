#ifndef __LANG__STACK__H__
#include "stdafx.h"
#define __LANG__STACK__H__
namespace lang
{
#ifdef _MSC_VER
#define LANG_THREAD_LOCAL __declspec(thread)
#else
#define LANG_THREAD_LOCAL __thread
#endif
#define LANG_STACK_SIZ 1024*1024
	extern LANG_THREAD_LOCAL unsigned unsigned unsigned unsigned unsigned unsigned unsigned unsigned unsigned char *varstack;
	void thread_init();
	void thread_end();
	Int *alloca_int(int val);
}
#endif