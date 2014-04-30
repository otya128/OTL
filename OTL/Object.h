#ifndef __LANG__OBJECT__H__
#define __LANG__OBJECT__H__
namespace lang
{
	class Object;
	struct GCInfo
	{
		GCInfo()
		{
			this->count = 0;
			this->next = 0;
		}
		int count;
		Object *next;
	};
	//éQè∆å^
	class Object
	{
	public:
		GCInfo gcinfo;
		virtual void dmmy();
		Object();
		virtual ~Object();
	};
	//ílå^
	class VarObject
	{
	public:
		virtual void dmmy();
		VarObject();
		virtual ~VarObject();
	};
	class VarRefObject
	{
		VarObject hoge;
	};
	class Int : public VarObject
	{
		int data;
	};
}
#endif
