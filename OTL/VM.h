#ifndef __LANG__VM__H__
#define __LANG__VM__H__
#include <list>
#include <vector>
#include "parser.h"
namespace lang
{
	//1+1
	//ADD 0xxxxxx, 0xxxxxxxx
	//0x01 0xXX 0xXX 0xXX 0xXX , 0xXX 0xXX 0xXX 0xXX
	//1+1+1+1
	//ADD 1,ADD 1,ADD 1,1
	//0x01 1 0x01
	enum OPCODE : unsigned char
	{
		OP_NOP,
		OP_ADD,
		OP_CONST_CONST = 0x00,
		OP_CONST_OP = 0x01,
		OP_OP_CONST = 0x02,
		OP_OP_OP = 0x03,
		OP_END = 0xFF,
	};
	class VM
	{
	public:
		VM();
		~VM();
		std::vector<OPCODE> bytecodelist;
		OPCODE* bytecode;
		void Compile(TreeNode* tree);
		void _Compile(TreeNode* tree);
		void Eval(TreeNode* tree);
		ObjectBase* Run();
		ObjectBase* Run(OPCODE*& bytecode,bool);
	};
}
#endif
