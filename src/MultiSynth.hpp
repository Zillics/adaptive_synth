#ifndef ADASYNTH_MULTISYNTH_H
#define ADASYNTH_MULTISYNTH_H
#include <string>
#include <fstream>
#include <iostream>
#include <Stk.h>
#include <SineWave.h>
#include <BlitSaw.h>
#include <BlitSquare.h>
#include <Noise.h>
#include <RtAudio.h>
#include <FileWrite.h>
#include <FileWvOut.h>

#define SAMPLE_RATE 44100.0

#include "Oscillator.hpp"



class MultiSynth
{
public:
	//! Default constructor
	MultiSynth( void );
	//! Reads from csv file in the format: "frequency_i, amplitude_i \n"
	//! Creates n sine waves of imported frequency and amplitude
	MultiSynth(std::string filename);
	MultiSynth(std::string sinename,std::string noisename);
	//! Default destructor
	~MultiSynth( void );
	//! Adds oscillators based on a csv file
	void read_file(std::string filename,oscType osc_type);
	//! Adds oscillator of frequency freq to oscillators
	void addOscillator(oscType type,stk::StkFloat freq);
	//! Adds oscillator of frequency freq to oscillators
	void addOscillator(oscType type,stk::StkFloat freq, stk::StkFloat amp); //TEMPORARY FUNCTION. WILL BE REMOVED
	//! Prints out all oscillator and other info about the object
	void print() const;
	//! Ticks all oscillators and sums results to one value
	stk::StkFloat tick();
	//! Sets sample rate
	void set_sampleRate(stk::StkFloat sr) { sampleRate = sr; }
	//! Sets amp to value so no distortion will occur (lower bound)
	void updateAmp() { amp = maxAmp/n_osc; std::cout << "Synth amp set to " << amp << std::endl; }
	//! Sets amp to custom value (distortion might happen)
	void setAmp(stk::StkFloat _amp) { amp = _amp; }
private:
	std::vector<Oscillator*> oscillators;
	unsigned int n_osc = 0;
	stk::StkFloat maxAmp = 0;
	stk::StkFloat amp; //The amplitude (0-1) that is applied to the resulting wave in tick
	unsigned int t;
	stk::StkFloat sampleRate = SAMPLE_RATE;
};
// Player for testing out different MultiSynth objects
class Player
{
public:
	//! Default constructor
	Player( void );
	//! Default destructor
	~Player( void );
	//! Play MultiSynth object
	void play(MultiSynth* synth);
	//! Record MultiSynth object for _ seconds to wav file
	void record(MultiSynth* synth, unsigned int seconds, std::string filepath);
private:
	RtAudio dac;
};

#endif