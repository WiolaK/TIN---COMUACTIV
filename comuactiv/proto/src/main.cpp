/*
 * main.cpp
 *
 *  Created on: 4 May 2015
 *      Author: Jan Kumor
 */

#include <cereal/archives/binary.hpp>
#include <cereal/cereal.hpp>
#include <fstream>
#include <iostream>
#include <string>

#include "messages/AssociationSetupResponseMsg.hpp"

using namespace comuactiv::proto::messages;
using namespace std;

int main() {
	AssociationSetupResponseMsg m1;
	std::ofstream out;
	out.open("test.txt", std::ios::binary);
	{
		cereal::BinaryOutputArchive oArchive(out); // Create an output archive

		oArchive(m1); // Write the data to the archive
	}
	out.close();
	std::cout << "M1: " << m1.prefix_ << m1.code_ << m1.length_ << m1.id_ << m1.data_ << std::endl;

	Message m2;
	std::ifstream in;
	in.open("test.txt");
	{
		cereal::BinaryInputArchive iArchive(in); // Create an output archive

		iArchive(m2); // Write the data to the archive
	}
	in.close();
	std::cout << "M2: " << m2.prefix_ << m2.code_ << m2.length_ << m2.id_ << m2.data_ << std::endl;

}



