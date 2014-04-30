#include "Object.h"
#include <memory.h>

namespace lang
{
	char* ObjectTypeString[ObjectTypeLength] = 
	{
		"Object",
		"VarObject",
		"VarInt",
	};
	void* Object_vfptr[ObjectTypeLength][16];
	Object* vfptrs[ObjectTypeLength] = {};
	void Init()
	{
		Object object;
		//void(*vfptr)() = (void(*)())**(void***)&object;
		//auto dmmy = &Object::dmmy;
		size_t* vfptr = (size_t*)*(void**)GETVFPTR(&object);
		for (int i = 0; i < ObjectTypeLength; i++)
		{
			memcpy(Object_vfptr[i], vfptr, sizeof(Object_vfptr[i]));
			Object_vfptr[i][0] = (void*)i;
			((size_t*)&object)[0] = (size_t)(Object_vfptr[i]);
		}
		//0xC0000005
		//*vfptr = 1;
		/*(*(size_t*)(size_t*)*(void**)&object) = 1;*/
	}
	void Object::vfptr_dmmy(){}
	void VarObject::vfptr_dmmy(){}
	Object::Object()
	{
		SETVFPTR(this, Object_vfptr[objecttype]);
	}

	Object::~Object()
	{
		//•t‚¯‘Ö‚¦‚é
		this->gcinfo.prev->gcinfo.next = this->gcinfo.next;
		this->gcinfo.next->gcinfo.prev = this->gcinfo.prev;
	}
	std::string Object::ToString()
	{
		return ObjectTypeString[ObjectGetType(this)];
	}
	VarObject::VarObject()
	{
		SETVFPTR(this, Object_vfptr[objecttype]);
	}
	VarObject::~VarObject()
	{
	}
	Int::Int()
	{
		SETVFPTR(this, Object_vfptr[objecttype]);
	}
	Int::~Int()
	{
	}
}
