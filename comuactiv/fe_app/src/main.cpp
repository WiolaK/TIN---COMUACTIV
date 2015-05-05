/*
 * main.cpp
 *
 *  Created on: 3 May 2015
 *      Author: john
 */

#include <iostream>

#include "ForwardEntity.hpp"

using namespace comuactiv::fe_app;

int main(int argc, char* argv[])
{

	if(argc == 3)
	{
		ForwardEntity::getInstance().start(argv[1], argv[2]);
	}
	else
	{
		std::cout << "Usage: fe_app <server> <port> " << std::endl;
	}

	return 0;
}




