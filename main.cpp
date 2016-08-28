#include <queue>
#include <fstream>
#include <iostream>
#include "Program.h"
#include "CPU.h"
#include "Parser.h"

#define PROGRAM_FILE_PATH "program.txt"

CPU *CPU::instance = 0;

int main(void) {

	CPU *cpu = CPU::GetInstance();

	std::ifstream inputFile;
	inputFile.open(PROGRAM_FILE_PATH);
	std::vector<std::string > firstLineVector = GetFirstLineDataVector(inputFile);
	std::queue<std::string> instructionsQueue = ParseInputFile(inputFile);

	inputFile.close();

	// initialize all needed parameters for CPU construction
	unsigned variableTU = std::stoi(firstLineVector[1]);
	unsigned printTU = std::stoi(firstLineVector[2]);
	unsigned lockTU = std::stoi(firstLineVector[3]);
	unsigned unlockTU = std::stoi(firstLineVector[4]);
	unsigned endTU = std::stoi(firstLineVector[5]);
	unsigned quantum = std::stoi(firstLineVector[6]);

	// create objects of Program and initialize them by instructions from instructionsQueue
	cpu->InitializePrograms(instructionsQueue, variableTU, printTU, lockTU, unlockTU, endTU, quantum);

	// execute instructions of all added programs
	cpu->Run();

	delete cpu;

	return 0;
}
