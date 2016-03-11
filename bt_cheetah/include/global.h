/*
 * global.h
 *
 *  Created on: Aug 20, 2012
 *      Author: guillaume
 */

#ifndef GLOBAL_H_
#define GLOBAL_H_


#include <boost/circular_buffer.hpp>
#include <boost/array.hpp>

#define NB_FRAMES					5	// 5 frames per batch
#define NB_E					    19
#define NB_PAC						22

enum Fingers {FINGER_1=0,FINGER_2=1,FINGER_3=2};


typedef boost::array<uint16_t,NB_E> Impedance;
typedef boost::array<uint16_t,NB_PAC> Pac;

typedef struct {
	Impedance E;
	Pac pac;
	uint16_t Pdc;
	uint16_t Tac;
	uint16_t Tdc;
} Frame;

typedef boost::array<Frame,3> Finger_frames;
typedef boost::circular_buffer<Finger_frames> Buffer;

#endif /* GLOBAL_H_ */
