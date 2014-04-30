#include "stdafx.h"
#include "Object.h"
#include <exception>
using namespace lang;
class TestFail : std::exception
{
public:
	TestFail(){}
	TestFail(const char* what) : std::exception(what)
	{}
};
class Test
{
public:
	Test()
	{
		try
		{
			Object object;
		}
		catch (...)
		{
			throw TestFail();
		}
	}
};