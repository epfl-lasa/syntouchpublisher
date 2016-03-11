/*
 * subscriber.cpp
 *
 *  Created on: Jun 22, 2012
 *      Author: guillaume
 */

#include "gnuplot/subscriber.h"


void Subscriber::callbackFinger1(const syntouchpublisher::biotac_message::ConstPtr& msg){
	data[0] = 	msg->E[0];
	data[1] = 	msg->Pac[0];

	data[2] = 	msg->E[1];
	data[3] = 	msg->Pac[1];

	data[4] = 	msg->E[2];
	data[5] = 	msg->Pac[2];
	plot_finger1.plot(data);
}



int main(int argc, char **argv)
{
	ros::init(argc, argv, "listener");
	ros::NodeHandle n;
	ros::Subscriber sub_finger1 = n.subscribe("finger1", 1, Subscriber::callbackFinger1);

	ros::Rate r(100);

	/*ros::Subscriber sub_finger2 = n.subscribe("finger2", 1000, chatterCallbackFinger2);
	ros::Subscriber sub_finger3 = n.subscribe("finger3", 1000, chatterCallbackFinger3);*/


	  while (ros::ok())
	  {
		 ros::spinOnce();
	     r.sleep();
	  }
}
