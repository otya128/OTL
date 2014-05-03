#include "VM.h"
#include "Object.h"

namespace lang
{
	VM::VM() : bytecode(0)
	{
	}


	VM::~VM()
	{
		delete bytecode;
	}
	ObjectBase* VM::Run()
	{
		return Run(this->bytecode,true);
	}
	ObjectBase* VM::Run(OPCODE*& bytecode, bool whiledo)
	{
		ObjectBase* op1 = { 0 }, *op2 = { 0 }, *ret = { 0 };
		do
		{
			switch (*bytecode)
			{
				case OP_ADD:
					bytecode++;
					switch (*bytecode)
					{
						case OP_CONST_CONST:
							bytecode++;
							op1 = *(ObjectBase**)bytecode;
							bytecode += sizeof(ObjectBase*);
							op2 = *(ObjectBase**)bytecode;
							bytecode += sizeof(ObjectBase*);
							break;
						case OP_CONST_OP:
							bytecode++;
							op1 = *(ObjectBase**)bytecode;
							bytecode += sizeof(ObjectBase*);
							op2 = Run(bytecode, false);
							bytecode--;
							break;
						case OP_OP_CONST:
							bytecode++;
							op1 = Run(bytecode, false);
							op2 = *(ObjectBase**)bytecode;
							bytecode += sizeof(ObjectBase*);
							bytecode--;
							break;
						case OP_OP_OP:
							op1 = Run(bytecode, false);
							op2 = Run(bytecode, false);
							break;
					}
					ret = *op1 + op2;
					break;
				case OP_END:
					return ret;
			}
			if (whiledo)bytecode++;
		} while (whiledo);
		return ret;
	}
	void VM::Compile(TreeNode* tree)
	{
		_Compile(tree);
		bytecodelist.push_back(OP_END);
		bytecode = bytecodelist.data();
	}
	void VM::_Compile(TreeNode* tree)
	{
		switch (tree->Type)
		{
			case NODE_ROOT:
				tree = ((RootNode*)tree)->Child;
				_Compile(tree);
				break;
			case NODE_EVAL:
				tree = ((EvalNode*)tree)->Child;
				Eval(tree);
				break;
		}
	}
	void VM::Eval(TreeNode* tree)
	{
		TreeNode *op1, *op2;
		size_t addr = 0;
		unsigned char select = OP_NOP;
		switch (tree->Type)
		{
			case NODE_OP:
				op1 = ((BinOPNode*)tree)->Child[0];
				op2 = ((BinOPNode*)tree)->Child[1];
				bytecodelist.push_back(OP_ADD);
				if (op1->Type != NODE_CONSTANT)
				{
					select |= 0x02;
				}
				if (op2->Type != NODE_CONSTANT)
				{
					select |= 0x01;
				}
				bytecodelist.push_back((OPCODE)select);
				Eval(op1);
				Eval(op2);
				break;
			case NODE_CONSTANT:
				addr = (size_t)((ConstNode<ObjectBase*>*)tree)->constant;
				for (int i = 0, j = 0; i < sizeof(int); i++, j += 8)
				{
					bytecodelist.push_back((OPCODE)(addr >> j));
				}
				break;
		}
	}
}
