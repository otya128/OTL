#ifndef __GC__H__
#include "stdafx.h"
#define __GC__H__
namespace lang
{
	extern Object *latest;
	class GC
	{
	public:
		GC();
		~GC();
		void collect();
	};
}
#endif
