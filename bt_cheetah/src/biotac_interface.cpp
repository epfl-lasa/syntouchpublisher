/*
 * Bt_cheeta_interface.cpp
 *
 *  Created on: Jun 19, 2012
 *      Author: guillaume
 */
#include "biotac_interface.h"
#include <stdio.h>
#include <stdlib.h>
#include <fstream>


Biotac_interface::Biotac_interface(Buffer &buffer):
buffer(buffer)
{
}


void Biotac_interface::init(){

    /**************************************************************************/
	/* --- Initialize BioTac settings (only default values are supported) --- */
    /**************************************************************************/
	biotac.spi_clock_speed = BT_SPI_BITRATE_KHZ_DEFAULT;
	biotac.number_of_biotacs = 0;
	biotac.sample_rate_Hz = BT_SAMPLE_RATE_HZ_DEFAULT;
	biotac.frame.frame_type = 0;
	biotac.batch.batch_frame_count = BT_FRAMES_IN_BATCH_DEFAULT;
	biotac.batch.batch_ms = BT_BATCH_MS_DEFAULT;
	 // number of data points from the finger


	// Set the duration of the run time
	length_of_data_in_second = 3;
	number_of_samples = 220;//(int)(BT_SAMPLE_RATE_HZ_DEFAULT * length_of_data_in_second);

	std::cout<< "number_of_samples: " << number_of_samples << std::endl;

	// Check if any initial settings are wrong
	if (MAX_BIOTACS_PER_CHEETAH != 3 && MAX_BIOTACS_PER_CHEETAH != 5)
	{
		bt_err_code = BT_WRONG_MAX_BIOTAC_NUMBER;
		bt_display_errors(bt_err_code);
		exit(1);
	}

    /******************************************/
	/* --- Initialize the Cheetah devices --- */
    /******************************************/
	ch_handle = bt_cheetah_initialize(&biotac);

	std::cout<< "ch_handle: " << ch_handle << std::endl;

    /*************************************/
	/* --- Configure the save buffer --- */
	/*************************************/
	data  = bt_configure_save_buffer(number_of_samples);

	/*******************************/
	/* --- Configure the batch --- */
	/*******************************/
	bt_err_code = bt_cheetah_configure_batch(ch_handle, &biotac, number_of_samples);
	if (bt_err_code < 0)
	{
		bt_display_errors(bt_err_code);
		exit(1);
	}
	else
	{
		printf("\nConfigured the batch\n");
	}

}


void Biotac_interface::startThread(){
	mThread = boost::shared_ptr<boost::thread>(new boost::thread(&Biotac_interface::collectData, this));
}

void Biotac_interface::jointThread(){
	mThread->join();
}


void Biotac_interface::ctrlcHandler(int action){
	std::cout<< "run is false" << std::endl;
	RUN = false;
}

void Biotac_interface::printBioTacInfo(){
	/*********************************************************/
	/* --- Get and print out properties of the BioTac(s) --- */
	/*********************************************************/
	for (i = 0; i < MAX_BIOTACS_PER_CHEETAH; i++)
	{
		bt_err_code = bt_cheetah_get_properties(ch_handle, i+1, &(biotac_property[i]));

		if (biotac_property[i].bt_connected == YES)
		{
			(biotac.number_of_biotacs)++;
		}

		if (bt_err_code)
		{
			bt_display_errors(bt_err_code);
			exit(1);
		}
	}

	// Check if any BioTacs are detected
	if (biotac.number_of_biotacs == 0)
	{
		bt_err_code = BT_NO_BIOTAC_DETECTED;
		bt_display_errors(bt_err_code);
	}
	else
	{
		printf("\n%d BioTac(s) detected.\n\n", biotac.number_of_biotacs);
	}
}

void Biotac_interface::collectData(){




		/***************************************************************/
		/* --- Collect the batch and display the data (if desired) --- */
		/***************************************************************/

		std::cout<< "Start collecting BioTac data for " << length_of_data_in_second << " second(s)... " << std::endl;
		number_of_loops = (int)(number_of_samples / ((double)(biotac.frame.frame_size * biotac.batch.batch_frame_count)));
	//	number_of_loops = 20;

		number_data_per_loop = biotac.frame.frame_size *  biotac.batch.batch_frame_count;

		std::cout<< "number_of_samples: "    << number_of_samples              << std::endl;
		std::cout<< "number_of_loops: "   	 << number_of_loops                << std::endl;
		std::cout<< "frame_size: "           << biotac.frame.frame_size        << std::endl;
		std::cout<< "batch_frame_count: "    << biotac.batch.batch_frame_count << std::endl;
		std::cout<< "number_data_per_loop: " << number_data_per_loop           << std::endl;



		while(RUN){	// 1 loop 5 frames collected
			bt_cheetah_collect_batch(ch_handle, &biotac, data, NO);
			bt_reset_count();
		//	print();
			split_frames();
		//	usleep(1000);
		}

		free(data);

}



inline void Biotac_interface::split_frames(){

	int index = 0;
	for(int frame = 0; frame < NB_FRAMES;frame++){
		set_frame(finger_frame[FINGER_1],data,index,FINGER_1);
		set_frame(finger_frame[FINGER_2],data,index,FINGER_2);
		set_frame(finger_frame[FINGER_3],data,index,FINGER_3);
 		index=index+44;
 		buffer.push_back(finger_frame);
	}
}

inline void Biotac_interface::set_frame(Frame& frame,bt_data* data,int index, Fingers finger){
	index_E = 0;
	index_pac = 0;
	index_data = index;


	for(int j = 0; j < 38; j++){
		if(j % 2 == 0 && j < 38){
			frame.E[index_E] 	   = data[index_data].d[finger].word;
			index_E++;
		}else{
			frame.pac[index_pac] = data[index_data].d[finger].word;
			index_pac++;
		}
		index_data++;
	}

	frame.Pdc =  data[index_data].d[finger].word;
	index_data++;

	frame.pac[index_pac] = data[index_data].d[finger].word;
	index_pac++;
	index_data++;

	frame.Tac = data[index_data].d[finger].word;
	index_data++;

	frame.pac[index_pac] = data[index_data].d[finger].word;
	index_pac++;
	index_data++;

	frame.Tdc = data[index_data].d[finger].word;
	index_data++;

	frame.pac[index_pac] = data[index_data].d[finger].word;


}

void Biotac_interface::print(){
	std::cout<< "new batch direct from Source" << std::endl;
	for(unsigned int i=44;i < 88;i++){
		std::cout<< data[i].d[0].word << " ";
		if(i == 43){
			std::cout<< std::endl;
			std::cout<< std::endl;
		}else if(i == 87){
			std::cout<< std::endl;
			std::cout<< std::endl;
		}else if(i == 131){
			std::cout<< std::endl;
			std::cout<< std::endl;
		}else if(i == 175){
			std::cout<< std::endl;
			std::cout<< std::endl;
		}
	}
	std::cout<< "End of bactch direct from Source " << std::endl;


}

void Biotac_interface::printFrame(const Frame& frame){
	for(unsigned int i=0; i < 19;i++){
		std::cout<< frame.E[i] << " " << frame.pac[i] << " ";
	}
	std::cout<< frame.pac[19] << " " << frame.Pdc << " " << frame.pac[20] << " " << frame.Tac << " " << frame.pac[21] << " " << frame.Tdc << std::endl;



}
