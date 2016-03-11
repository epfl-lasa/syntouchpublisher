/*
 * main.cpp
 *
 *  Created on: Jun 19, 2012
 *      Author: guillaume
 */


#include <boost/circular_buffer.hpp>
#include "biotac_interface.h"
#include "publisher.h"
#include "global.h"
#include <iostream>
#include <boost/thread.hpp>




int main(int argc, char **argv){


	Buffer buffer(220);


	Biotac_interface biotac_interface(buffer);
	Publisher publisher(buffer,120);

	biotac_interface.init();
	publisher.init(argc,argv);


	biotac_interface.startThread();
	publisher.startThread();


	biotac_interface.jointThread();
	publisher.joinThread();


	return 1;
}

