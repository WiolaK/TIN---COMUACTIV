/*
 * Printer.hpp
 *
 *  Created on: 25 May 2015
 *      Author: Jan Kumor
 */

#ifndef PROTO_SRC_UTILS_PRINTER_HPP_
#define PROTO_SRC_UTILS_PRINTER_HPP_

#include <ctime>
#include <iostream>
#include <mutex>
#include <string>

namespace comuactiv {
namespace proto {
namespace utils {

class Printer {
public:
	Printer() : name_(std::string("NoName")) {};
	Printer(std::string name) : name_(name) {};
	virtual ~Printer() {};

	void operator()(std::string log) const {
		//Full ISO 8601 timestamp
		std::time_t t = std::time(nullptr);
		char timestamp[28];
		std::strftime(timestamp, sizeof(timestamp), "%FT%T%z: ", std::localtime(&t));
		std::lock_guard<std::mutex> lock(mtx_);
		std::cout << timestamp << name_ << ": " << log << std::endl;
	}

	template<typename T>
	Printer& operator<<(T t ) {
		std::lock_guard<std::mutex> lock(mtx_);
		std::cout << t;
		return *this;
	}

protected:
	std::string name_;
	static std::mutex mtx_;
};

} /* namespace utils */
} /* namespace proto */
} /* namespace comuactiv */

#endif /* PROTO_SRC_UTILS_PRINTER_HPP_ */
