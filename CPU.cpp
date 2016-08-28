/*
 * CPU.cpp
 *
 *  Created on: Aug 27, 2016
 *      Author: iryna
 */

#include "CPU.h"

CPU::CPU()
{
	timeUnitsMap[VARIABLE] = 0;
	timeUnitsMap[PRINT] = 0;
	timeUnitsMap[LOCK] = 0;
	timeUnitsMap[UNLOCK] = 0;
	timeUnitsMap[END] = 0;
	quantum = 0;
	for(char var = 97; var != 123; ++var ) {
		variables[var] = 0;
	}
	hasLock = false;
}


void CPU::InitializePrograms( 	std::queue<std::string> parsedInstructionsVector,
		unsigned	variableTU,
		unsigned	printTU,
		unsigned	lockTU,
		unsigned	unlockTU,
		unsigned	endTU,
		unsigned	_quantum)
{
	timeUnitsMap[VARIABLE] = variableTU;
	timeUnitsMap[PRINT] = printTU;
	timeUnitsMap[LOCK] = lockTU;
	timeUnitsMap[UNLOCK] = unlockTU;
	timeUnitsMap[END] = endTU;
	quantum = _quantum;
	for(char var = 97; var != 123; ++var ) {
		variables[var] = 0;
	}
	hasLock = false;

	for(unsigned id = 1; id <= parsedInstructionsVector.size(); ++id) {
		std::string instr;
		std::queue<std::string> oneProgramInstructions;
		unsigned numberOfStatementsForOneProgram = 0;
		do{
			numberOfStatementsForOneProgram++;
			instr = parsedInstructionsVector.front();
			boost::trim(instr);
			parsedInstructionsVector.pop();
			oneProgramInstructions.push(instr);
		} while(instr != "end");
		if(numberOfStatementsForOneProgram <= 25 && LockUnlockCheck(oneProgramInstructions)) {
			Program *program =  new Program(oneProgramInstructions, id);
			readyQueue.push(program);
		} else if (numberOfStatementsForOneProgram > 25) {
			std::cout << "Program " << id << " was not added to queue " \
					"because of consisting more then 25 statements."<<std::endl;
		}
	}
}

void CPU::Run(){
	while(!readyQueue.empty()){
		exec(readyQueue.front(), quantum);
	}
}

int CPU::exec(Program * program, unsigned quant) {

	std::string statement = program->GetNextStatement();
	unsigned requiredTime = GetRequiredTime(statement);
	unsigned executedTime = program->GetExecutedTime();  //time command was executed previous time
	unsigned totalAvailableTime = quant + executedTime;

	while (totalAvailableTime >=  requiredTime && requiredTime != 0) {
		if(std::regex_match(statement, std::regex("[a-z]\\s+=\\s+\\d+")))
		{
			statement = std::regex_replace(statement, std::regex("\\s+"), "");
			std::vector< std::string > tokens;
			boost::split(tokens, statement, boost::is_any_of("="));
			unsigned variableValue = std::stoi(tokens[1]);
			checkValueIsLess100(variableValue);
			variables[*(tokens[0].c_str())] = variableValue;

		} else if(std::regex_match(statement, std::regex("print\\s+[a-z]")))
		{
			statement = std::regex_replace(statement, std::regex("\\s+"), " ");
			std::vector< std::string > tokens;
			boost::split(tokens, statement, boost::is_any_of(" "));
			unsigned programId = readyQueue.front()->GetProgramID();
			std::cout << programId << ": "<< variables[*(tokens[1].c_str())] << std::endl;

		} else if(statement == "lock")
		{
			if(hasLock) {
				blockedQueue.push(readyQueue.front());
				readyQueue.pop();
				return 0;
			} else {
				hasLock = true;
			}

		} else if(statement == "unlock")
		{
			if (!blockedQueue.empty()) {
				readyQueue.push(blockedQueue.front());
				blockedQueue.pop();
			}
			hasLock = false;

		} else if(statement == "end")
		{
			program->RemoveExecuted();
			delete readyQueue.front();
			readyQueue.pop();
			return 0;
		} else {
			std::cout<<"Error: Undefined statement: "<<statement<< \
					". Check if all instructions in input file match all rules." << std::endl;
		}

		program->RemoveExecuted();
		totalAvailableTime -= requiredTime;
		statement = program->GetNextStatement();
		requiredTime = GetRequiredTime(statement);
	}

	program->SetExecutedTime(totalAvailableTime > 0 ? totalAvailableTime : 0);

	// moving program to the end of the readyQueue if it was not mover already to blockedQueue
	if (!readyQueue.empty()) {
		readyQueue.push(readyQueue.front());
		readyQueue.pop();
	}
	return 0;
}


unsigned CPU::GetRequiredTime(std::string statement)
{
	if(std::regex_match(statement, std::regex("\\w\\s+=\\s+\\d+"))) {
		return timeUnitsMap[VARIABLE];
	} else if(std::regex_match(statement, std::regex("print\\s+[a-z]"))) {
		return timeUnitsMap[PRINT];
	} else if(statement == "lock") {
		return timeUnitsMap[LOCK];
	} else if(statement == "unlock") {
		return timeUnitsMap[UNLOCK];
	} else if(statement == "end") {
		return timeUnitsMap[END];
	} else {
		std::cout<<"Error: Undefined statement;"<<statement<<std::endl;
		return 0;
	}
}

bool CPU::checkValueIsLess100(int value) {
	if (value <= 100 && value >= 0) {
		return true;
	} else {
		std::cout << "Found incorrect value of variable. Check input file." << std::endl;
		return false;
	}
}

bool CPU::LockUnlockCheck(std::queue<std::string> instructions) {
	std::queue<std::string> instr(instructions);
	bool isLock = false;
	bool isUnlock = false;

	if(!instr.empty()) {
		std::string statement;
		do {
			statement = instr.front();
			if (statement == "lock") {
				if (isLock == true && isUnlock == false) {
					std::cout<<"Error: Not allowed nested lock/unlock. Program removed from queue."<<std::endl;
					return false;
				}
				isLock = true;
			}
			else if (statement == "unlock") {
				isUnlock = true;
			}
			instr.pop();
		} while (statement != "end");
	}

	if (isLock != isUnlock) {
		std::cout<<"Error: Lock/unlock do not occur in pair. Program removed from queue."<<std::endl;
	}

	return isLock == isUnlock;
}

CPU::~CPU() {
	while(!readyQueue.empty()) {
		delete readyQueue.front();
		readyQueue.pop();
	}
	while(!blockedQueue.empty()) {
		delete blockedQueue.front();
		blockedQueue.pop();
	}

	delete instance;
}

