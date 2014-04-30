#include "stdafx.h"
#include <exception>
#include <iostream>
#include "Object.h"
#include "Test.h"
#include "GC.h"
using namespace lang;
class TestFail : std::exception
{
public:
	TestFail(){}
	TestFail(const char* what) : std::exception(what)
	{}
};
#define TESTASSERT(expr) std::cout<<"Test:"<<#expr<<std::endl;_ASSERT_EXPR(expr,#expr)

Test::Test()
	{
		try
		{
			Object object;
			TESTASSERT(object.GetType() == _Object);
			Int intobject;
			TESTASSERT(intobject.GetType() == _VarInt);
			VarObject varobject;
			TESTASSERT(varobject.GetType() == _VarObject);
			Object *one = new Object, *two = new Object, *three = new Object;
			delete two;
			TESTASSERT(one->gcinfo.next == three);
			TESTASSERT(three->gcinfo.prev == one);
			std::cout << "GC Collect..." << std::endl;
			gc->collect();
			std::cout << "OK!" << std::endl;
		}
		catch (TestFail)
		{
			throw;
		}
		catch (...)
		{
			throw TestFail("throw exception");
		}
	}