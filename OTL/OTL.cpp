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
void TreeView(TreeNode *tree, int sp)
{
	for (int i = 0; i < sp; i++)
	{
		std::cout << ((i == sp - 1) ? /*''*/(char)0x19 : (char)0x05/*''*/);
	}
	switch (tree->Type)
	{
		case NODE_ROOT:
			std::cout << "ROOT" << std::endl;
			TreeView(((RootNode*)tree)->Child, sp + 1);
			break;
		case NODE_EVAL:
			std::cout << "EVAL" << std::endl;
			TreeView(((EvalNode*)tree)->Child, sp + 1);
			break;
		case NODE_CONSTANT:
			std::wcout << L"CONSTANT " << ((ConstNode<ObjectBase*>*)tree)->constant->ToString() << std::endl;
			break;
		case NODE_OP:
			std::wcout << L"OP " << tree->Token->name << std::endl;
			TreeView(((BinOPNode*)tree)->Child[0], sp + 1);
			TreeView(((BinOPNode*)tree)->Child[1], sp + 1);
			break;
	}
}
int main(int argc, char* argv[])
{
	Init();
	Test test;
	parser pars;
	std::wstring text(L"1+1+1+1");
	pars.Parse(text);
	TreeView(&pars.root, 0);
	scope scop(&pars.root);
	auto ret = scop.Run();
	std::wcout << ret->ToString();
	return 0;
}

