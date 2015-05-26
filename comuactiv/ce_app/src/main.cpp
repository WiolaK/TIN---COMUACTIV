/*
 * main.cpp
 *
 *  Created on: 3 May 2015
 *      Author: john
 */

#include <iostream>

#include "ControlEntity.hpp"

using namespace comuactiv::ce_app;

int main(int argc, char* argv[])
{
	if(argc == 2)
	{
		ControlEntity::getInstance().start(argv[1]);
	}
	else
	{
		std::cout << "Usage: ce_app <port> " << std::endl;
	}

	return 0;
}




