// OTL.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//
#include <iostream>
#include "stdafx.h"
#include "Object.h"
//class Test{ public:Test(); };
#include "Test.h"
#include "parser.h"
#include "scope.h"
#include "VM.h"
using namespace lang;
//using namespace lang::VM;
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
void VMView(OPCODE*& op, bool whiledo, bool lisp = false)
{
	do
	{
		ObjectBase* op1 = { 0 }, *op2 = { 0 }, *ret = { 0 };
		switch (*op)
		{
			case OP_ADD:
				std::cout << (lisp ? "( + " : "ADD ");
				op++;
				switch (*op)
				{
					case OP_CONST_CONST:
						if (!lisp)std::cout << "CONST_CONST:";
						op++;
						op1 = *(ObjectBase**)op;
						std::wcout << op1->ToString() << (lisp ? ' ' : ',');
						op += sizeof(ObjectBase*);
						op2 = *(ObjectBase**)op;
						op += sizeof(ObjectBase*);
						std::wcout << op2->ToString();
						break;
					case OP_CONST_OP:
						if (!lisp)std::cout << "CONST_OP:";
						op++;
						op1 = *(ObjectBase**)op;
						std::wcout << op1->ToString() << (lisp ? ' ' : ',');
						op += sizeof(ObjectBase*);
						VMView(op, false, lisp);
						if (whiledo)op--;
						break;
					case OP_OP_CONST:
						if (!lisp)std::cout << "OP_CONST:";
						op++;
						VMView(op, false, lisp);
						op2 = *(ObjectBase**)op;
						std::wcout << (lisp ? ' ' : ',') << op2->ToString();
						op += sizeof(ObjectBase*);
						if (whiledo)op--;
						break;
					case OP_OP_OP:
						if (!lisp)std::cout << "OP_OP:";
						op++;
						VMView(op, false, lisp);
						VMView(op, false, lisp);
						break;
				}
				if (lisp)std::cout << ')';
				if (whiledo)std::wcout << std::endl;
				break;
			case OP_END:
				return;
		}
		if (whiledo)op++;
	} while (whiledo);
}
int main(int argc, char* argv[])
{
	Init();
	Test test;
	parser pars;
	std::wstring text(L"1+1+52+3+4");
	pars.Parse(text);
	TreeView(&pars.root, 0);
	scope scop(&pars.root);
	auto ret = scop.Run();
	std::wcout << "interpreter:" << ret->ToString() << std::endl;
	VM vm;
	vm.Compile(&pars.root);
	VMView(vm.bytecode, true, true);
	vm.bytecode = vm.bytecodelist.data();
	ret = vm.Run();
	std::wcout << "VM:" << ret->ToString() << std::endl;
	std::getc(stdin);
	return 0;
}

