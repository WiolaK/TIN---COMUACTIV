/*
 * FlowTable.cpp
 *
 *  Created on: 25 May 2015
 *      Author: Barbara Kulas
 */

#include "FlowTable.h"

#include <iostream>

using namespace tinyxml2;

namespace flowtable {
FlowTable::FlowTable() {
	loadTable();
}

FlowTable::~FlowTable() {

}

void FlowTable::loadTable() {
	table.LoadFile("../flowtable.xml");
}

int FlowTable::checkTable() {
	XMLText* textNode;
	for(int i=1; i<2; i++){
		textNode = table.FirstChildElement("FROM")->FirstChild()->ToText();
		from = textNode->Value();
	}

	std::cout << from << std::endl;

	return 0;
}

} /* namespace flowtable */
