/*
 * waveformgen.h
 *
 *  Created on: Aug 25, 2020
 *      Author: kylej
 */

#ifndef WAVECLASS
#define WAVECLASS

#include <vector>
using std::vector;
#include <string>
using std::string;
#include <fstream>
using std::ifstream; using std::ofstream;


/*
 * Waveform Class
 *
 * generate_sine is called in constructor
 *
 * includes getters and setters for _v
 */

class Waveform
{
private:
	vector<double> _v; //contains samples of the waveform
	long _sample_persec; //samples per second of waveform
	long _dur; //duration of waveform in seconds
	long _a; //amplitude
	double _f;//frequency
	double _p;//phase
	const double TwoPi = 2 * acos(0.0);

public:
	Waveform(long sample_persec = 44100, double dur = 1, long a = 1, double f = 200, double p = 0);

	void generate_sine();

	vector<double>& get_v();

	long get_sample_persec ();

	void set_v(vector<double>& v);


};


/*
 * Waveform_S Class
 *
 * Contains several Waveform objects in _waves_v vector
 *
 * These can be manipluated with following functions:
 * add_waves - adds two waveforms together
 * sub_waves - subtracts two waveforms
 * mul_waves - multiplies two waveforms
 *
 * print_waves feeds each waveform inside _waves_v to cout
 *
 * get_waveform returns a waveform object from _waves_v
 *
 */
class Waveform_S
{
private:
	vector<Waveform> _waves_v;
	//ofstream _ofs;
	//ifstream _ifs;
	string _ofs_s;
	string _ifs_s;

public:
	Waveform_S(string infile_name,string outfile_name);

	void pushback_waveform (Waveform& w);
	vector<double> add_waves(const vector<double>& v1,const vector<double>& v2);
	vector<double> sub_waves(const vector<double>& v1,const vector<double>& v2);
	vector<double> mul_waves(const vector<double>& v1,const vector<double>& v2);
	void print_waves();

	Waveform& get_waveform (int i = 0);

	void output_waveforms();

	void normalize_waveform (Waveform w);


};

#endif /* WAVECLASS */
