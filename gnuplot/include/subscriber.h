/*
 * subscriber.h
 *
 *  Created on: Jun 22, 2012
 *      Author: guillaume
 */

#ifndef SUBSCRIBER_H_
#define SUBSCRIBER_H_

#include "ros/ros.h"
#include "syntouchpublisher/biotac_message.h"
#include <string>
#include "plot.h"

class Subscriber{


public:


    static void callbackFinger1(const syntouchpublisher::biotac_message::ConstPtr& msg);



public:
	static Plot plot_finger1;
	static Plot plot_finger2;
	static Plot plot_finger3;


};

Plot Subscriber::plot_finger1 = Plot("finger1",100);
Plot Subscriber::plot_finger2 = Plot("finger2",100);
Plot Subscriber::plot_finger3 = Plot("finger3",100);
static boost::array<uint16_t,44> data;



#endif /* SUBSCRIBER_H_ */
