/*
 * Parser.h
 *
 *  Created on: Aug 28, 2016
 *      Author: iryna
 */

#ifndef PARSER_H_
#define PARSER_H_
#include <queue>
#include <fstream>
#include <iostream>
#include <regex>
#include <boost/algorithm/string.hpp>


std::vector<std::string> GetFirstLineDataVector(std::ifstream &inputFile);
std::queue<std::string> ParseInputFile(std::ifstream &inputFile);


#endif /* PARSER_H_ */
