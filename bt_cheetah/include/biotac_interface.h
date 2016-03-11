/*
 * bt_cheeta_interface.h
 *
 *  Created on: Jun 19, 2012
 *      Author: guillaume
 */

#ifndef BT_CHEETA_INTERFACE_H_
#define BT_CHEETA_INTERFACE_H_

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <queue>
#include <boost/circular_buffer.hpp>

#include "cheetah.h"
#include "biotac.h"

#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/array.hpp>
#include "global.h"

class Biotac_interface{



public:

	Biotac_interface(Buffer &buffer);

	void init();

	void startThread();

	void jointThread();

	void printBioTacInfo();

	static void ctrlcHandler(int action);

private:

	void collectData();

	inline void split_frames();

	inline void set_frame(Frame& frame,bt_data* data,int index, Fingers finger);

	void printFrame(const Frame& frame);

	void print();

private:

	bt_info biotac;
    bt_property biotac_property[MAX_BIOTACS_PER_CHEETAH];
	bt_data *data;
	BioTac bt_err_code;
	Cheetah ch_handle;
	std::queue<bt_data> data_queue;

	Impedance E;
	Pac pac;
	double pdc, tac, tdc;

	int index_E;
	int index_pac;
	int index_data;
	Finger_frames finger_frame;
	boost::shared_ptr<boost::thread> mThread;

	Buffer& buffer;

	int i;
	double length_of_data_in_second;
	int number_of_samples;
	int number_of_loops;
	int number_data_per_loop;

	static const int frame_size = 44;


};

static bool RUN = true;

#endif /* BT_CHEETA_INTERFACE_H_ */
