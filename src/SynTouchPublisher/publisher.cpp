#include "publisher.h"


Publisher::Publisher(Buffer &buffer,int broadcast_Hz):
buffer(buffer)
{
	this->broadcast_Hz = broadcast_Hz;
	this->biotac_interface = biotac_interface;

}

void Publisher::init(int argc, char **argv){
	 ros::init(argc, argv, "biotac_Node");
}


void Publisher::startThread(){
	mThread = boost::shared_ptr<boost::thread>(new boost::thread(&Publisher::broadCast, this));
}


void Publisher::joinThread(){
	mThread->join();
}

void Publisher::broadCast(){


	 ros::NodeHandle n;
	 ros::Publisher pub_finger1 = n.advertise<SynTouchPublisher::biotac_message>("finger1",100);
	 ros::Publisher pub_finger2 = n.advertise<SynTouchPublisher::biotac_message>("finger2",100);
	 ros::Publisher pub_finger3 = n.advertise<SynTouchPublisher::biotac_message>("finger3",100);
	 ros::Rate loop_rate(broadcast_Hz);


	  while (ros::ok())
	  {

		//   std::cout<< "IN BROADCAST LOOP" << std::endl;

		 if(!(buffer.empty())){


		//	 printFrame((buffer.back())[FINGER_1]);

			 std::cout<< "circular_buffer size: " << buffer.size() << std::endl;
			 //std::cout<< "publisher"<<std::endl;
			 //printFrame((buffer.back())[0]);

			 writeToMessage(msg_finger1,buffer[0][FINGER_1]);
			 writeToMessage(msg_finger2,buffer[0][FINGER_2]);
			 writeToMessage(msg_finger3,buffer[0][FINGER_3]);

			  buffer.pop_front();

			  pub_finger1.publish(msg_finger1);
			  pub_finger2.publish(msg_finger2);
			  pub_finger3.publish(msg_finger3);


			  ros::spinOnce();
			  loop_rate.sleep();
		 }

	  }
}


inline void Publisher::writeToMessage(SynTouchPublisher::biotac_message& msg,const Frame& frame){
	for(unsigned int i=0; i < 19; i++){
		msg.E[i] = frame.E[i];
		msg.Pac[i] = frame.pac[i];
	}
	msg.Pac[19]=frame.pac[19];
	msg.Pac[20]=frame.pac[20];
	msg.Pac[21]=frame.pac[21];
	msg.Pdc = frame.Pdc;
	msg.Tac = frame.Tac;
	msg.Tdc = frame.Tdc;
}

void Publisher::printFrame(const Frame& frame){

	for(unsigned int i=0; i < 19;i++){
		std::cout<< frame.E[i] << " " << frame.pac[i] << " ";
	}
	std::cout<< frame.pac[19] << " " << frame.Pdc << " " << frame.pac[20] << " " << frame.Tac << " " << frame.pac[21] << " " << frame.Tdc << std::endl;
}




