/*
 * main_waveform.cpp
 *
 *  Created on: Aug 25, 2020
 *      Author: kylej
 */

#include <iostream>
using std::cout; using std::endl;
#include <string>
using std::string; using std::getline; using std::stol;
#include <vector>
using std::vector;
#include <utility>
using std::pair;
#include <fstream>
using std::ifstream; using std::ofstream;
#include <cmath>
using std::pow;
#include <sstream>
using std::ostringstream;

#include "waveformgen.h"
#include "wavefile.h"

int main ()
{
	Waveform_S f ("input","output"); //input will be input.txt output will be output.wav
	Waveform w1(44100,1,1,440,0);
	Waveform w2(44100,1,1,600,0);
	Waveform w3(44100,1,1,700,0);
	//w1.generate_sine();
	//w2.generate_sine();

	f.pushback_waveform(w1);
	f.pushback_waveform(w2);
	f.pushback_waveform(w3);

	//f.print_waves();

	vector<double> a = f.mul_waves(f.get_waveform(0).get_v(),f.get_waveform(1).get_v());

	f.get_waveform(1).set_v(a);

	//f.print_waves();

	a = f.add_waves(f.get_waveform(2).get_v(),f.get_waveform(0).get_v());

	f.get_waveform(2).set_v(a);

	f.print_waves();

	f.normalize_waveform(f.get_waveform(2));

	f.print_waves();

	f.output_waveforms();

	return 0;

}

