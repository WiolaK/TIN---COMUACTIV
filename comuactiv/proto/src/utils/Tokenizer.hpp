/*
 * Tokenizer.hpp
 *
 *  Created on: 25 May 2015
 *      Author: Jan Kumor
 */

#ifndef PROTO_SRC_UTILS_TOKENIZER_HPP_
#define PROTO_SRC_UTILS_TOKENIZER_HPP_

#include <string>
#include <vector>

namespace comuactiv {
namespace proto {
namespace utils {

class Tokenizer {
public:
	Tokenizer(const char sep);
	virtual ~Tokenizer();

	std::vector<std::string> operator()(std::string str);

private:
	char sep_;
};

} /* namespace utils */
} /* namespace proto */
} /* namespace comuactiv */

#endif /* PROTO_SRC_UTILS_TOKENIZER_HPP_ */
