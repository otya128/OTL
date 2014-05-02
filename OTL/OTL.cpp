// OTL.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//
#include <iostream>
#include "stdafx.h"
#include "Object.h"
//class Test{ public:Test(); };
#include "Test.h"
#include "parser.h"
#include "scope.h"
using namespace lang;
int main(int argc, char* argv[])
{
	Init();
	Test test;
	parser pars;
	std::wstring text(L"1+1+1+1");
	pars.Parse(text);
	scope scop(&pars.root);
	auto ret = scop.Run();
	std::wcout << ret->ToString();
	return 0;
}

