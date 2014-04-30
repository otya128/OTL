#ifndef __LANG__OBJECT__H__
#include <string>
#define __LANG__OBJECT__H__
namespace lang
{
#ifdef _MSC_VER
#define GETVFPTRCAST(ptr, type) ((type)(void*)(ptr))
#define GETVFPTR(ptr) ((void*)(ptr))
#define SETVFPTR(ptr, value) ((*(size_t*)((void*)(ptr))) = (size_t)(value))
#else
#error NO DEFINED GETVFPTR AND SETVFPTR
#endif
#define ObjectGetType(ptr) (ObjectType)(**GETVFPTRCAST(ptr, size_t**))
	const int ObjectTypeLength = 3;
	extern char* ObjectTypeString[ObjectTypeLength];
	enum ObjectType
	{
		_Object,
		_VarObject,
		_VarInt,
	};
	void Init();
	class Object;
	struct GCInfo
	{
		GCInfo()
		{
			this->count = 0;
			this->next = 0;
			this->prev = 0;
		}
		int count;
		Object *prev;
		Object *next;
	};
	extern void* Object_vfptr[ObjectTypeLength][16];
	//�Q�ƌ^
	class Object
	{
	public:
		inline Object(bool){}
		static const ObjectType objecttype = _Object;
		GCInfo gcinfo;
		virtual void vfptr_dmmy();
		Object();
		virtual ~Object();
		virtual std::string ToString();
		inline ObjectType GetType()
		{
			return ObjectGetType(this);
		}
	};
	//�l�^
	class VarObject
	{
	public:
		inline VarObject(bool){}
		static const ObjectType objecttype = _VarObject;
		virtual void vfptr_dmmy();
		VarObject();
		virtual ~VarObject();
		virtual std::string ToString();
		inline ObjectType GetType()
		{
			return ObjectGetType(this);
		}
	};
	class VarRefObject
	{
	public:
		VarObject hoge;
	};
	class Int : public VarObject
	{
	public:
		inline Int(bool){}
		static const ObjectType objecttype = _VarInt;
		int data;
		Int();
		virtual ~Int();
	};
}
#endif