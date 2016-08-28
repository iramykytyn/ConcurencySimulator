/*
 * Parser.cpp
 *
 *  Created on: Aug 28, 2016
 *      Author: iryna
 */
#include "Parser.h"

/* Function std::vector<std::string> GetFirstLineDataVector(std::ofstream &inputFile)
 * return vector with info about number of programs, time units for every statement and quantum
 */
std::vector<std::string> GetFirstLineDataVector(std::ifstream &inputFile) {
	std::string firstLineStr;
	std::vector<std::string > firstLineVector;

	if (inputFile.is_open() && std::getline(inputFile, firstLineStr)) {
		// Check file for consisting seven integers separated by spaces
		if (!std::regex_match (firstLineStr, std::regex("(\\d+\\s*){7}") )) {
			std::cout << "Error: Check input parameters.\n";
		}
		boost::split(firstLineVector, firstLineStr, boost::is_any_of(" "));
	} else {
		std::cout << "Unable to open input file."<< std::endl;
	}
	return firstLineVector;
}



/* Function std::queue<std::string> ParseInputFile(std::ifstream &inputFile)
 * return queue of all instructions from input file
 * GetFirstLineDataVector should always be invoked before this function
 */
std::queue<std::string> ParseInputFile(std::ifstream &inputFile){
	std::string instructionLineStr;
	std::queue<std::string> instructions;
	if (inputFile.is_open()) {
		while(std::getline(inputFile, instructionLineStr)) {
			boost::trim(instructionLineStr);
			instructions.push(instructionLineStr);
		}
	} else {
		std::cout << "Unable to open input file." << std::endl;
	}
	return instructions;
}





