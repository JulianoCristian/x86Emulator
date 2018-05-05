#pragma once
#include "Registers.hpp"
#include "Memory.hpp"
#include "CodeFetch.hpp"
#include "Eflags.hpp"

namespace x86 {

	class Container {

		//Eflags
		Eflags eflags;

		//�ėp���W�X�^
		Registers registers;

		//������
		Memory memory;

		//�������ǂݏo���Ɏg�p
		CodeFetch codeFetch;



	public:
		Container(size_t size, uint32_t eip, uint32_t esp)
			:memory(size),
			codeFetch(eip, memory)
		{}

		Registers& GetRegisters() { return registers; }
		Memory& GetMemory() { return memory; }
		CodeFetch& GetCodeFetch() { return codeFetch; }
		Eflags& GetEflags() { return eflags; }

		const Registers& GetRegisters()const { return registers; }
		const Memory& GetMemory()const { return memory; }
		const CodeFetch& GetCodeFetch()const { return codeFetch; }
		const Eflags& GetEflags()const { return eflags; }

	};
}