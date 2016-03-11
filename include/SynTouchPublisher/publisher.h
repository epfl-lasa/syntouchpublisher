/*
 * talker.h
 *
 *  Created on: Jun 19, 2012
 *      Author: guillaume
 */


#ifndef PUBLISHER_H_
#define PUBLISHER_H_

//		ROS

#include "ros/ros.h"
#include "biotac_message.h"

// my code

#include "biotac_interface.h"
#include "biotac.h"
#include "global.h"


class Publisher{


public:


	Publisher(Buffer &buffer,int broadcast_Hz);

	void init(int argc, char **argv);

	void startThread();

	void joinThread();

	void broadCast();

private:

	void printFrame(const Frame& frame);

	inline void writeToMessage(SynTouchPublisher::biotac_message& msg,const Frame& frame);


private:

	SynTouchPublisher::biotac_message msg_finger1;
	SynTouchPublisher::biotac_message msg_finger2;
	SynTouchPublisher::biotac_message msg_finger3;


	Biotac_interface* biotac_interface;

	boost::shared_ptr<boost::thread> mThread;

	Buffer& buffer;

	int broadcast_Hz;

};

static const char *command_name[] = \
		{ "PAC", "PDC", "TAC", "TDC", "   ", "   ", "   ", "   ", "   ", "   ", \
		  "   ", "   ", "   ", "   ", "   ", "HAL", "REV", "E01", "E02", "E03", \
		  "E04", "E05", "E06", "E07", "E08", "E09", "E10", "E11", "E12", "E13", \
		  "E14", "E15", "E16", "E17", "E18", "E19", "   ", "   ", "   ", "   ", \
		  "   ", "   ", "   ", "   ", "   ", "   ", "   ", "   ", "   ", "   ", \
		  "   ", "   ", "   ", "   ", "   ", "   ", "   ", "   ", "   ", "   ", \
		  "   ", "   ", "   ", "   "};


#endif /* PUBLISHER_H_ */
