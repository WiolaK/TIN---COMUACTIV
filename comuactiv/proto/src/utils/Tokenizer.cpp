/*
 * Tokenizer.cpp
 *
 *  Created on: 25 May 2015
 *      Author: Jan Kumor
 */

#include "Tokenizer.hpp"

#include <stddef.h>
#include <iostream>

namespace comuactiv {
namespace proto {
namespace utils {

Tokenizer::Tokenizer(const char sep)
: sep_(sep) {
	//Do nothing
}

Tokenizer::~Tokenizer() {
	//Do nothing
}

std::vector<std::string> Tokenizer::operator()(std::string str) {
	std::vector<std::string> tokens;
	for(size_t p=0, q=0; p != str.npos; p=q) {
		std::string subString = str.substr(p+(p!=0), (q=str.find(sep_, p+1))-p-(p!=0));
		std::cout << subString << std::endl;
		tokens.push_back(subString);
	}
	return tokens;
}

} /* namespace utils */
} /* namespace proto */
} /* namespace comuactiv */
