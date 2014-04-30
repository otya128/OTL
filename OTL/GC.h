#ifndef __GC__H__
#include "stdafx.h"
#define __GC__H__
namespace lang
{
	class GC
	{
	public:
		Object *latest;
		int count;
		GC();
		~GC();
		void collect();
	};
	extern GC *gc;
}
#endif
