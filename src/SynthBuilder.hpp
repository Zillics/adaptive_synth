#ifndef ADASYNTH_SYNTHBUILDER_H
#define ADASYNTH_SYNTHBUILDER_H
#include "MultiSynth.hpp"

class SynthBuilder
{
public:
	SynthBuilder( void ) { }
	~SynthBuilder( void ) { }
	//! Reads from csv file in the format: "frequency_i, amplitude_i \n"
	//! Creates n sine waves of imported frequency and amplitude
	MultiSynth* Build_MultiSynth(std::string filename) const;
private:
};


#endif