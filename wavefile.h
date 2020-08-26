/*
 * wavefile.h
 *
 *  Created on: Aug 25, 2020
 *      Author: kylej
 */

#ifndef WAVEFILE_H_
#define WAVEFILE_H_

#include <string>
using std::string;
#include <vector>
using std::vector;
#include <fstream>
using std::ofstream;

void write_wav_data (
	ofstream& s,
	vector<double> &buf,
	int sample_rate,
	short channels
);

#endif /* WAVEFILE_H_ */
