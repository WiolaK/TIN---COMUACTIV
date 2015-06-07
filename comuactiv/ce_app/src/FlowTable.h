/*
 * FlowTable.h
 *
 *  Created on: 25 May 2015
 *      Author: Barbara Kulas
 */

#ifndef COMUACTIV_CE_APP_FLOWTABLE_H_
#define COMUACTIV_CE_APP_FLOWTABLE_H_

#include <iostream>
#include <map>
#include <string>
#include "tinyxml2.h"

using namespace tinyxml2;

namespace flowtable {
class FlowTable {
private:
	const char *from;
	const char *to;
	const char *priority;
	XMLDocument table;
	std::map<std::string, std::string> ftmap;

public:
	FlowTable();
	~FlowTable();

	void loadTable();
	int checkTable();
	std::map<std::string, std::string> getFTMap();

};
}


#endif /* COMUACTIV_CE_APP_FLOWTABLE_H_ */
