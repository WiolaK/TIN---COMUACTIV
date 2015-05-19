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
	AssociationSetupMsg msg;

	std::ofstream out;
	out.open("test.txt", std::ios::binary);

	uint8_t buffer[1024];
	msg.writeMessage(buffer);
	for(int i = 0; i < msg.getLength(); i++)
	{
		std::cout << buffer[i];
		out.put(buffer[i]);
	}
	std::cout << std::endl;
	Message msg2;
	msg2.readMessage(buffer);

	out.close();
	/*std::ofstream out;
	out.open("test.txt", std::ios::binary);
	{
		cereal::BinaryOutputArchive oArchive(out); // Create an output archive
		oArchive(*m1);
		oArchive(*m2);
		oArchive(*m3);
	}
	out.close();

	std::ifstream in;
	in.open("test.txt");
	{
		cereal::BinaryInputArchive iArchive(in); // Create an output archive

		iArchive(*m2); // Write the data to the archive
	}
	in.close();
*/
}



