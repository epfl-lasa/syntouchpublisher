/*
 * plot.cpp
 *
 *  Created on: Jun 24, 2012
 *      Author: guillaume
 */

#include "plot.h"

	Plot::Plot(const std::string& plot_name,int cb_size):
	plot_name(plot_name),
	cb_e(19)
	{


		tmp = new std::ofstream("file.dat",std::ios_base::trunc);
		if(!(tmp->is_open())){
			std::cout<< "failed to open file.dat" << std::endl;
		}

		 h1 = gnuplot_init();
		 gnuplot_setstyle(h1,"lines");
		 gnuplot_cmd(h1,"set yrange [0:4000]");


		for(unsigned int i = 0; i < cb_e.size();i++){
			cb_e[i] = boost::circular_buffer<uint16_t>(100);
			for(unsigned int j = 0; j < 100;j++){
				(cb_e[i])[j] = 0;
			}
		}


	}

	void Plot::plot(const boost::array<uint16_t,44>& data){

		plot_E(data);

	}

	void Plot::write_data_to_file(){

		tmp->close();
		tmp->open("file.dat",std::ios_base::trunc);

		for(unsigned int j = 0; j < 100;j++){
					for(unsigned int i = 0; i < cb_e.size();i++){

					(*tmp) << (cb_e[i])[j] << " ";

				}
					(*tmp) << std::endl;
		}

		tmp->flush();


	}


	void Plot::plot_E(const boost::array<uint16_t,44>& data){


	 /*   gnuplot_resetplot(h1);



		int index = 0;*/
		int index = 0;
		for(unsigned int i = 0; i < cb_e.size();i++){
			cb_e[i].push_back(data[index]);
			index = index + 1;

		}

		write_data_to_file();
	//	gnuplot_cmd(h1,"plot \"file.dat\"  using 1 title \"E0\" with lines");

		gnuplot_cmd(h1,"plot \"file.dat\"  using 1 title \"E0\" with lines,\
						             \"file.dat\"  using 2 title \"E1\" with lines,\
						             \"file.dat\"  using 3 title \"E2\" with lines");

		/*gnuplot_cmd(h1,"plot \"file.dat\"  using 1 title \"E0\" with lines,\
				             \"file.dat\"  using 2 title \"E1\" with lines,\
				             \"file.dat\"  using 3 title \"E2\" with lines,\
							 \"file.dat\"  using 4 title \"E3\" with lines,\
				 			 \"file.dat\"  using 5 title \"E4\" with lines,\
							 \"file.dat\"  using 6 title \"E5\" with lines,\
				             \"file.dat\"  using 7 title \"E6\" with lines,\
							 \"file.dat\"  using 8 title \"E7\" with lines,\
				 			 \"file.dat\"  using 9 title \"E8\" with lines");*/

	}

	void Plot::plot_Pac(const boost::array<uint16_t,44>& data){

	}
