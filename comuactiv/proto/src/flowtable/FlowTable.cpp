/*
 * FlowTable.cpp
 *
 *  Created on: 25 May 2015
 *      Author: Barbara Kulas
 */

#include "../../include/comuactiv/FlowTable.hpp"

#include <iostream>
#include <utility>

#include "../utils/Printer.hpp"

using namespace tinyxml2;
using namespace comuactiv::proto::utils;

namespace comuactiv {
namespace proto {
namespace flowtable {

FlowTable::FlowTable() :
	table_(true, COLLAPSE_WHITESPACE){
	//Do nothing
}

FlowTable::~FlowTable() {
	//Do nothing
}

void FlowTable::loadTable(std::string path) {
	std::lock_guard<std::mutex> lock(mtx_);
	table_.LoadFile(path.c_str());
}

void FlowTable::parseTable(std::string str) {
	std::lock_guard<std::mutex> lock(mtx_);
	table_.Parse(str.c_str());
}

int FlowTable::checkTable() {
	std::lock_guard<std::mutex> lock(mtx_);
	Printer printer("FlowTableParser");
	XMLText* textNode;
	XMLElement *element, *e;
	element = table_.FirstChildElement("FLOWTABLE");

	for(e = element->FirstChildElement("ENTRY"); e != 0; e = e->NextSiblingElement("ENTRY")){

		textNode = e->FirstChildElement("FROM")->FirstChild()->ToText();
		from_ = textNode->Value();
		textNode = e->FirstChildElement("TO")->FirstChild()->ToText();
		to_ = textNode->Value();

		printer(from_);
		printer(to_);
		ftmap_.insert(std::pair<std::string,std::string>(from_, to_));
	}
	printer("ftmap size " + std::to_string(ftmap_.size()));
	return 0;
}

std::string FlowTable::find(std::string key) {
	std::lock_guard<std::mutex> lock(mtx_);
	auto it = ftmap_.find(key);
	if( it == ftmap_.end()) {
		return "drop";
	} else {
		return it->second;
	}
}

std::string FlowTable::toString() {
	std::lock_guard<std::mutex> lock(mtx_);
	XMLPrinter printer(0, true);
	table_.Accept(&printer);
	return std::string(printer.CStr());
}

} /* namespace flowtable */
} /* namespace proto */
} /* namespace comuactiv */
