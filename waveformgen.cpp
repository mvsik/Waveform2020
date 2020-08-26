/*
 * waveformgen.cpp
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


/*
 * This Program takes a collection of waveforms and combines them then outputs a wav file
 *
 * Sin Function:
 * General Form ~ y = a * sin(2pi*f*k+p)
 * a - amplitude
 * f - frequency in Hz
 * p - phase
 * k - position on x axis
 *
 * waveforms can be added,subtracted,and multiplied
 */



void Waveform::generate_sine()
{
	double sample = 0;
	for (long k = 0; k < _sample_persec*_dur; k++)
	{
		sample = _a * sin(TwoPi*(_f*k/_sample_persec)+_p);
		_v.push_back(sample);
	}
}

Waveform::Waveform (long sample_persec, double dur, long a, double f, double p)
{
	_sample_persec = sample_persec;
	_dur = dur;
	_a = a;
	_f = f;
	_p = p;
	generate_sine();
}

Waveform_S::Waveform_S(string infile_name,string outfile_name)
{
	//_ifs.open(infile_name);
	//_ofs.open(outfile_name);
	_ifs_s = infile_name;
	_ofs_s = outfile_name;
}

vector<double> Waveform_S::add_waves(const vector<double>& v1,const vector<double>& v2)
{
	vector<double> v3;
	if(v1.size() <= v2.size()){
		for(long i=0; i<v1.size(); i++){
			v3.push_back(v1.at(i)+v2.at(i));
		}
	}
	else{
		for(long i=0; i<v2.size(); i++){
			v3.push_back(v1.at(i)+v2.at(i));
		}
	}
	return v3;
}

vector<double> Waveform_S::mul_waves(const vector<double>& v1,const vector<double>& v2)
{
	vector<double> v3;
	if(v1.size() <= v2.size()){
		for(long i=0; i<v1.size(); i++){
			v3.push_back(v1.at(i)*v2.at(i));
		}
	}
	else{
		for(long i=0; i<v2.size(); i++){
			v3.push_back(v1.at(i)*v2.at(i));
		}
	}
	return v3;
}

vector<double> Waveform_S::sub_waves(const vector<double>& v1,const vector<double>& v2)
{
	vector<double> v3;
	if(v1.size() <= v2.size()){
		for(long i=0; i<v1.size(); i++){
			v3.push_back(v1.at(i)-v2.at(i));
		}
	}
	else{
		for(long i=0; i<v2.size(); i++){
			v3.push_back(v1.at(i)-v2.at(i));
		}
	}
	return v3;
}

void Waveform_S::pushback_waveform (Waveform& w)
//adds a waveform to private _waves_v vector
{
	_waves_v.push_back(w);
}

vector<double>& Waveform::get_v ()
{
	return _v;
}


void Waveform_S::print_waves()
{
	for(int i = 0; i < _waves_v.size(); i++){
		cout << "Waveform " + std::to_string(i+1) + ": ";
		for(int j = 0; j < _waves_v[i].Waveform::get_v().size(); j++){
			cout << std::to_string(_waves_v[i].Waveform::get_v()[j]) << std::to_string(j) << ",";
			if(j % 10 == 0){
				cout << "\n";
			}
		}
		cout << "end" <<endl;
	}
}


void Waveform::set_v(vector<double>& v)
{
	_v = v;
}

Waveform& Waveform_S::get_waveform (int i){
	return _waves_v[i] ;
}

long Waveform::get_sample_persec () {
	return _sample_persec;
}



void Waveform_S::output_waveforms()
{
	ofstream ofs;
	//ifstream ifs;
	//ifs.open(_ifs_s);
	//ofs.open(_ofs_s);

	for (int i = 0; i < _waves_v.size(); i++){
		ofs.open(_ofs_s + std::to_string(i)+".wav");
		write_wav_data(ofs,_waves_v[i].Waveform::get_v(),_waves_v[i].get_sample_persec(),1);
		ofs.close();
	}


	//ifs.close();
	//ofs.close();
}

void Waveform_S::normalize_waveform (Waveform w)
{
	double d_max = *std::max_element(w.get_v().begin(),w.get_v().end());
	vector<double> v ;
	for (int i = 0; i < w.get_v().size();i++){
		v.push_back(w.get_v()[i]/d_max);

	}
	w.set_v(v);
}

