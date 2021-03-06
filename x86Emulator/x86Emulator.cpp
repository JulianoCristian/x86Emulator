// x86Emulator.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include "Emulator.hpp"
#include <iostream>
#include <fstream>


struct OptData {
	bool quiet = false;
	std::string filename = "";
	bool error = false;
};

OptData errorOptData() {
	OptData optData;
	optData.error = true;
	return optData;
}

OptData optGet(int argc, char* argv[]) {
	OptData optData;
	for (size_t i = 1; i < argc; i++) {
		if (argv[i][0] == '-') {
			if (argv[i][2] != '\0')
			{
				return errorOptData();
			}
			switch (argv[i][1])
			{
			case 'q':
				optData.quiet = true;
				break;
			default:
				return errorOptData();
				break;
			}
		}
		else {
			if(optData.filename=="")
				optData.filename = argv[i];
			else
				return errorOptData();
		}
	}
	return optData;
}

/* メモリは1MB */
static constexpr size_t MEMORY_SIZE = (1024 * 1024);

int main(int argc,char* argv[])
{
	//Emulatorを生成
	x86::Emulator emu(MEMORY_SIZE, 0x7c00, 0x7c00);

	auto optData = optGet(argc, argv);

	if (optData.error) {
		std::cerr << "error option";
		return 1;
	}

	if (optData.filename=="") {
		std::cerr << "no filename error"<<std::endl;
		return 1;
	}

	std::ifstream ifs(optData.filename,std::ios_base::in|std::ios_base::binary );

	if (!ifs) {
		std::cerr << optData.filename << "ファイルが開けません" << std::endl;
		return 1;
	}
	emu.Read(ifs);

	emu.Execute(
		[]() {std::wcout << "end of program..."<<std::endl; },
		[]() {std::wcout << "error" << std::endl; }, 
		[optData](std::wstring str) { if(optData.quiet==false)std::wcout << str << std::endl; }
	);
	if (optData.quiet==false)
		std::wcout<<emu.Dump_registers();
    return 0;
}

