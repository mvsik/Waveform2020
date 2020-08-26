/*
 * wavefile.cpp
 *
 *  Created on: Aug 25, 2020
 *      Author: someone else??
 */

#include <string>
using std::string;
#include <vector>
using std::vector;
#include <fstream>
using std::ofstream;

void write_wav_data (ofstream& out_stream,vector<double> &buf,int sample_rate,short channels)
{
	//setup all the WAV variables
	int buf_size = buf.size() * sizeof(double);
	int  chunk_size = 36 * buf_size;
	int sub_chunk_size = 16;
	short audio_format = 3;
	int byte_rate = sample_rate * channels * sizeof(double);
	short block_align = channels * sizeof(double);
	short bits_per_sample = 8 * sizeof(double);

	//write the RIFF part
	out_stream.write("RIFF",4);
	out_stream.write(reinterpret_cast<const char *>(&chunk_size),4);
	out_stream.write("WAVE",4);

	//write the format subchunk
	out_stream.write("fmt ",4);
	out_stream.write(reinterpret_cast<const char*>(&sub_chunk_size),4);
	out_stream.write(reinterpret_cast<const char*>(&audio_format),2);
	out_stream.write(reinterpret_cast<const char*>(&channels),2);
	out_stream.write(reinterpret_cast<const char*>(&sample_rate),4);
	out_stream.write(reinterpret_cast<const char*>(&byte_rate),4);
	out_stream.write(reinterpret_cast<const char*>(&block_align),2);
	out_stream.write(reinterpret_cast<const char*>(&bits_per_sample),2);

	//write data chunk
	out_stream.write("data",4);
	out_stream.write(reinterpret_cast<const char*>(&buf_size),4);
	out_stream.write(reinterpret_cast<const char*>(buf.data()),buf_size);

}


