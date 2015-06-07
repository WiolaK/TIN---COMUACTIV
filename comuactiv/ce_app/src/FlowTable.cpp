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

std::map<std::string, std::string> FlowTable::getFTMap(){
	return ftmap;
}

int FlowTable::checkTable() {
	XMLText* textNode;
	XMLElement *element, *e;
	element = table.FirstChildElement("FLOWTABLE");

	for(e = element->FirstChildElement("ENTRY"); e != 0; e = e->NextSiblingElement("ENTRY")){

		textNode = e->FirstChildElement("FROM")->FirstChild()->ToText();
		from = textNode->Value();
		textNode = e->FirstChildElement("TO")->FirstChild()->ToText();
		to = textNode->Value();

		printf("%s \n", from);
		printf("%s \n", to);
		ftmap.insert(std::pair<std::string,std::string>(from, to));
	}
	std::cout << "ftmap size " << ftmap.size() << std::endl;
	return 0;
}



} /* namespace flowtable */
