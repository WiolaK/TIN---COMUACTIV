/*
 * FlowTable.hpp
 *
 *  Created on: 25 May 2015
 *      Author: Barbara Kulas
 */

#ifndef COMUACTIV_CE_APP_FLOWTABLE_HPP_
#define COMUACTIV_CE_APP_FLOWTABLE_HPP_

#include <map>
#include <memory>
#include <mutex>
#include <string>

#include "../../src/flowtable/tinyxml2.h"

namespace comuactiv{
namespace proto{
namespace flowtable {

class FlowTable {
public:
	FlowTable();
	~FlowTable();

	void loadTable(std::string path);
	void parseTable(std::string str);
	int checkTable();

	std::string toString();
	std::string find(std::string);

private:
	const char *from_;
	const char *to_;
	const char *priority_;
	tinyxml2::XMLDocument table_;
	std::map<std::string, std::string> ftmap_;
	std::mutex mtx_;
};

typedef std::shared_ptr<FlowTable> pFlowTable;

} /* namespace flowtable */
} /* namespace proto */
} /* namespace comuactiv */


#endif /* COMUACTIV_CE_APP_FLOWTABLE_HPP_ */
