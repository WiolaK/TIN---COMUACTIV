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
	XMLElement *element;
//	element = table.FirstChildElement("FLOWTABLE");
//	element = element->FirstChildElement("ENTRY");
//	element = element->FirstChildElement("FROM");
//	textNode = element->FirstChild()->ToText();
	for(int i=1; i<2; i++){

//		textNode = table.FirstChildElement("FLOWTABLE")->FirstChildElement("ENTRY")->FirstChildElement("FROM")->FirstChild()->ToText();
//		from = textNode->Value();
	}

//	printf("%s \n", from);

	return 0;
}

} /* namespace flowtable */
