/*
 * Program.cpp
 *
 *  Created on: Aug 27, 2016
 *      Author: iryna
 */

#include "Program.h"

Program::Program(std::queue<std::string> instruct, unsigned id) {
	instructions = instruct;
	last_statement_execution = 0;
	programID = id;
}

std::string Program::GetNextStatement() {
	if (!instructions.empty()) {
		return instructions.front();
	} else {
		return "";
	}
}

void Program::RemoveExecuted() {
	if (!instructions.empty()) {
		instructions.pop();
	}
}

void Program::PrintStatements(void) {
	std::queue<std::string> instrQueue(instructions);
	std::cout << "ProgramID = " << programID << std::endl;
	while (!instrQueue.empty()) {
		std::cout << "instructions: " << instrQueue.front() << std::endl;
		instrQueue.pop();
	}
}

unsigned Program::GetExecutedTime(void) {
	return last_statement_execution;
}

void Program::SetExecutedTime(unsigned time) {
	last_statement_execution = time;
}

unsigned Program::GetProgramID(void) {
	return programID;
}

Program::~Program() {
	while(!instructions.empty()) {
		instructions.pop();
	}
}

