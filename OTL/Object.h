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
	extern wchar_t* ObjectTypeString[ObjectTypeLength];
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
	class ObjectBase{
	public:
		virtual void vfptr_dmmy() = 0;
		virtual ObjectBase* operator +(ObjectBase*) = 0;
		inline ObjectType GetType()
		{
			return ObjectGetType(this);
		}
		virtual std::wstring ToString() = 0;
	};
	//ŽQÆŒ^
	class Object : public ObjectBase
	{
	public:
		inline Object(bool){}
		static const ObjectType objecttype = _Object;
		GCInfo gcinfo;
		virtual void vfptr_dmmy();
		Object();
		virtual ~Object();
		virtual std::wstring ToString();
		inline ObjectType GetType()
		{
			return ObjectGetType(this);
		}
		virtual ObjectBase* operator +(ObjectBase*);
	};
	//’lŒ^
	class VarObject : public ObjectBase
	{
	public:
		inline VarObject(bool){}
		void Init();
		static const ObjectType objecttype = _VarObject;
		virtual void vfptr_dmmy();
		VarObject();
		virtual ~VarObject();
		virtual std::wstring ToString();
		inline ObjectType GetType()
		{
			return ObjectGetType(this);
		}
		virtual ObjectBase* operator +(ObjectBase*);
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
		///////////////
		//////////////w
		/////////////ew
		////////////new
		/////////// new
		//////////t new
		/////////nt new
		////////ent new
		///////ment new
		//////ement new
		/////cement new
		////acement new
		///lacement new
		//placement new
		void Init();
		static const ObjectType objecttype = _VarInt;
		int data;
		Int();
		virtual ~Int();
		virtual std::wstring ToString();
		virtual ObjectBase* operator +(ObjectBase*);
		static inline int ToInt(ObjectBase* i)
		{
			if (i->GetType() == _VarInt)
				return ((Int*)i)->data;
		}
	};
}
#endif
