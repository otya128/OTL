// OTL.cpp : �R���\�[�� �A�v���P�[�V�����̃G���g�� �|�C���g���`���܂��B
//

#include "stdafx.h"
#include "Object.h"
//class Test{ public:Test(); };
#include "Test.h"
#include "parser.h"
using namespace lang;
int main(int argc, char* argv[])
{
	Init();
	Test test;
	parser pars;
	std::wstring text(L"1+1");
	pars.Parse(text);
	return 0;
}

