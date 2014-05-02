#include <memory.h>
#include "Object.h"
#include "GC.h"
#include "stack.h"

namespace lang
{
	char* ObjectTypeString[ObjectTypeLength] = 
	{
		"Object",
		"VarObject",
		"VarInt",
	};
	void* Object_vfptr[ObjectTypeLength][16];
	void* vfptrs[ObjectTypeLength];
	void Init()
	{
		gc = new GC();
		vfptrs[0] = new Object(true);
		vfptrs[1] = new VarObject(true);
		vfptrs[2] = new Int(true);
		//void(*vfptr)() = (void(*)())**(void***)&object;
		//auto dmmy = &Object::dmmy;
		for (int i = 0; i < ObjectTypeLength; i++)
		{
			void* vfptr = (size_t*)*(void**)GETVFPTR(vfptrs[i]);
			memcpy(Object_vfptr[i], vfptr, (16));
			Object_vfptr[i][0] = (void*)i;
			//((size_t*)&object)[0] = (size_t)(Object_vfptr[i]);
		}
		//0xC0000005
		//*vfptr = 1;
		/*(*(size_t*)(size_t*)*(void**)&object) = 1;*/
	}
	void Object::vfptr_dmmy(){}
	void VarObject::vfptr_dmmy(){}
	Object::Object()
	{
		if (gc->latest)
		{
			this->gcinfo.prev = gc->latest;
			this->gcinfo.prev->gcinfo.next = this;
		}
		gc->latest = this;
		SETVFPTR(this, Object_vfptr[objecttype]);
	}

	Object::~Object()
	{
		//•t‚¯‘Ö‚¦‚é
		if (this->gcinfo.prev)this->gcinfo.prev->gcinfo.next = this->gcinfo.next;
		if(this->gcinfo.next)this->gcinfo.next->gcinfo.prev = this->gcinfo.prev;
		if (gc->latest == this)gc->latest = this->gcinfo.prev;
	}
	std::string Object::ToString()
	{
		return ObjectTypeString[ObjectGetType(this)];
	}
	std::string VarObject::ToString()
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
	void VarObject::Init()
	{
		SETVFPTR(this, Object_vfptr[objecttype]);
	}
	Int::Int()
	{
		SETVFPTR(this, Object_vfptr[objecttype]);
	}
	Int::~Int()
	{
	}
	void Int::Init()
	{
		SETVFPTR(this, Object_vfptr[objecttype]);
	}
	ObjectBase* Object::operator +(ObjectBase*)
	{
		//error!
		return nullptr;
	}
	ObjectBase* VarObject::operator +(ObjectBase*)
	{
		//error!
		return nullptr;
	}
	ObjectBase* Int::operator +(ObjectBase* op1)
	{
		return allocate_stack_int(ToInt(op1) + this->data);
	}
}
