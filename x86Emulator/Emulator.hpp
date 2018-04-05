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

		uint32_t getCode8(const int index)const {
			return memory[eip + index];
		}

		int32_t getSignCode8(const int index)const {
			return static_cast<int8_t>(getCode8(index));
		}

		uint32_t getCode32(const int index)const {
			uint32_t ret = 0;

			/* ���g���G���f�B�A���Ń������̒l���擾���� */
			for (int i = 0; i < 4; i++) {
				ret |= getCode8(index + i) << (i * 8);
			}

			return ret;
		}

		void mov_r32_imm32() {
			const uint8_t reg = getCode8(0) - 0xB8;
			const uint32_t value = getCode32(1);
			registers[reg] = value;
			eip += 5;
		}

		void short_jump() {
			const int8_t diff = getSignCode8(0);
			eip += (diff + 2);
		}
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