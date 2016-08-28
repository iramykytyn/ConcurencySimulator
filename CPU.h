/*
 * CPU.h
 *
 *  Created on: Aug 27, 2016
 *      Author: iryna
 */

#ifndef CPU_H_
#define CPU_H_

#include <queue>
#include <map>
#include <string>
#include <list>
#include <regex>
#include <iostream>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/regex.hpp>
#include "Program.h"

enum Statement {VARIABLE, PRINT, LOCK, UNLOCK, END, UNDEFINED};

class CPU {
public:
	static CPU *GetInstance() {
		if(!instance)
			instance = new CPU();
		return instance;
	}

	~CPU();
	void 	InitializePrograms( std::queue<std::string>,
								unsigned	variableTU,
								unsigned	printTU,
								unsigned	lockTU,
								unsigned	unlockTU,
								unsigned	endTU,
								unsigned	_quantum);
	void	Run();

private:
	static CPU *instance;
	CPU();

	int 		exec(Program* program, unsigned time);
	unsigned 	GetRequiredTime(std::string);
	void 		executeStatement(std::string);
	bool		checkValueIsLess100(int);
	bool 		LockUnlockCheck(std::queue<std::string> instructions);

	std::map<Statement, unsigned>	timeUnitsMap;
	std::queue<Program*> 			readyQueue;
	std::queue<Program*> 			blockedQueue;
	std::map<char, int> 			variables;
	unsigned 	quantum;
	bool 		hasLock;
};

#endif /* CPU_H_ */
