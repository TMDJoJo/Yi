/*
 * option_parser.cpp
 *
 *  Created on: Sep 11, 2015
 *      Author: tmdjojo
 */

#include "option_parser.h"
#include <iostream>

namespace Yi {

OptionParser::OptionParser() {
	// TODO Auto-generated constructor stub

}

OptionParser::~OptionParser() {
	// TODO Auto-generated destructor stub
}

bool OptionParser::add_option_string(const std::string& short_option, const std::string& option,
		const std::string& dest, const std::string& help){

	std::cout<< short_option << std::endl;
	std::cout<< option << std::endl;
	std::cout<< dest << std::endl;
	std::cout<< help << std::endl;


	return true;
}

} /* namespace Yi */


int main(int argc, char *argv[])
{
	std::cout<< "hello" << std::endl;

	Yi::OptionParser op = Yi::OptionParser();
	op.add_option_string("-f", "--file", "file", "ff");

    return 0;
}
