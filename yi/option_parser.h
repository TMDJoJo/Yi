/*
 * option_parser.h
 *
 *  Created on: Sep 11, 2015
 *      Author: tmdjojo
 */

#ifndef OPTION_PARSER_H_
#define OPTION_PARSER_H_

#include <string>

namespace Yi {

class OptionObject{
public:
	OptionObject();
	~OptionObject();
};

template<class T>
class Option: public OptionObject{
public:
	Option();
	~Option();
	const T& get_value();
	bool check_value();
private:
	std::string short_option_;
	std::string option_;
	std::string dest_;
	std::string help_;
	T value_;
};

class OptionParser {
public:
	OptionParser();
	virtual ~OptionParser();

	bool add_option_bool();
	bool add_option_int();
	bool add_option_string(const std::string& short_option, const std::string& option,
			const std::string& dest, const std::string& help);
	void parse_args(int argc, char* argv[]);
};

} /* namespace Yi */
#endif /* OPTION_PARSER_H_ */
