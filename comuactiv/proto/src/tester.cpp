/*
 * main.cpp
 *
 *  Created on: 4 May 2015
 *      Author: Jan Kumor
 */

#include <cstdint>
#include <fstream>
#include <iostream>

#include "messages/AssociationSetupMsg.hpp"
#include "messages/Message.hpp"

using namespace std;
using namespace comuactiv::proto::messages;

int main() {
	AssociationSetupMsg msg("6666");

	std::ofstream out;
	out.open("test.txt", std::ios::binary);
	pRawMessage raw = msg.getRaw();
	for(int i = 0; i < raw->length; i++)
	{
		std::cout << raw->array[i];
		out.put(raw->array[i]);
	}
	std::cout << std::endl;

	AssociationSetupMsg msg2(raw);
	pRawMessage raw2 = msg2.getRaw();
	for(int i = 0; i < raw->length; i++)
	{
		std::cout << raw2->array[i];
		out.put(raw2->array[i]);
	}
	std::cout << std::endl;


	out.close();
}



