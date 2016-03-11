/*
 * plot.h
 *
 *  Created on: Jun 23, 2012
 *      Author: guillaume
 */

#ifndef PLOT_H_
#define PLOT_H_


extern "C" {
	#include "gnuplot_i.h"
}

#include "cheetah.h"
#include <string>
#include <boost/circular_buffer.hpp>
#include <boost/array.hpp>
#include <iostream>
#include <vector>
#include <iostream>
#include <fstream>



class Plot{

	typedef std::vector<boost::circular_buffer<uint16_t> > vector_of_circular_buffers;

public:

	Plot(const std::string& plot_name,int cb_size);

	void plot(const boost::array<uint16_t,44>& data);

private:

	void write_data_to_file();

	void plot_E(const boost::array<uint16_t,44>& data);

	void plot_Pac(const boost::array<uint16_t,44>& data);
private:

	const std::string plot_name;

	vector_of_circular_buffers cb_e;

	std::vector<uint16_t> e;
	gnuplot_ctrl    	  *h1;
	double          	  x[100];
	std::ofstream *tmp;



};

static char *E_names[] = \
		{ "E01", "E02", "E03", "E04", "E05", "E06", "E07", "E08", "E09", "E10",
	      "E11", "E12", "E13", "E14", "E15", "E16", "E17", "E18", "E19"};



#endif /* PLOT_H_ */
