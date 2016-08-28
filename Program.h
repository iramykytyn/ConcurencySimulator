/*
 * Program.h
 *
 *  Created on: Aug 27, 2016
 *      Author: iryna
 */

#ifndef PROGRAM_H_
#define PROGRAM_H_

#include <queue>
#include <string>
#include <iostream>

class Program {
	friend class CPU;
public:

	Program(std::queue<std::string> instruct, unsigned id);
	~Program(void);

	void 		PrintStatements(void);

private:
	std::string GetNextStatement(void);
	unsigned 	GetExecutedTime(void);
	void 		SetExecutedTime(unsigned time);
	unsigned	GetProgramID(void);
	void 		RemoveExecuted(void);

	std::queue<std::string> instructions;
	unsigned 				programID;
	unsigned 				last_statement_execution;
};

#endif /* PROGRAM_H_ */
