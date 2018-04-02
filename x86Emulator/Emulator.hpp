#pragma once
#include <cstdint>
#include <memory>
#include <cstring>
#include <fstream>

namespace x86 {


	struct Register
	{
		static constexpr unsigned EAX = 0;
		static constexpr unsigned ECX = 1;
		static constexpr unsigned EDX = 2;
		static constexpr unsigned EBX = 3;
		static constexpr unsigned ESP = 4;
		static constexpr unsigned EBP = 5;
		static constexpr unsigned ESI = 6;
		static constexpr unsigned EDI = 7;
		static constexpr unsigned REGISTERS_COUNT = 8;
	};


	class Emulator {
	private:
		//�ėp���W�X�^
		uint32_t registers[Register::REGISTERS_COUNT];

		//EFLAGS���W�X�^
		uint32_t eflags;

		//������(�o�C�g��)
		std::unique_ptr<uint8_t[]> memory;

		//�v���O�����J�E���^
		uint32_t eip;

	public:

		Emulator(size_t size, uint32_t eip, uint32_t esp)
			:memory(std::make_unique<uint8_t[]>(size)),
			//���W�X�^�̏����l���w�肳�ꂽ���̂ɂ���
			eip(eip)
		{
			//�ėp���W�X�^�̏����l��S��0�ɂ���
			std::memset(registers, 0, sizeof(registers));
			this->registers[Register::ESP] = esp;
		}
		template<class CharT,class Traits = std::char_traits<CharT>>
		void Read(std::basic_istream<CharT,Traits>& ifs) {
			ifs.read(reinterpret_cast<char*>(memory.get()), 512);
		}
	};
}