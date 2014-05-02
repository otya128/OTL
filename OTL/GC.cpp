#include "GC.h"
#include <iostream>
#include "Object.h"

namespace lang
{
	GC *gc;
	GC::GC()
	{
	}


	GC::~GC()
	{
	}
	void GC::collect()
	{
		Object *target = this->latest;
		count++;
		while (target)
		{
			std::wcout << target->ToString() << target << std::endl;
			target->gcinfo.count = count;
			target = target->gcinfo.prev;
		}
	}
}
