#ifndef ADASYNTH_MULTISYNTH_H
#define ADASYNTH_MULTISYNTH_H
#include <string>
#include <fstream>
#include <iostream>
#include <Stk.h>
#include <SineWave.h>
#include <BlitSaw.h>
#include <BlitSquare.h>
#include <RtAudio.h>
#include <FileWrite.h>
#include <FileWvOut.h>
#include "Oscillator.hpp"

#define SAMPLE_RATE 44100.0

class MultiSynth
{
public:
	//! Default constructor
	MultiSynth( void );
	//! Reads from csv file in the format: "frequency_i, amplitude_i \n"
	//! Creates n sine waves of imported frequency and amplitude
	MultiSynth(std::string filename);
	//! Default destructor
	~MultiSynth( void );
	//! Adds oscillator of frequency freq to oscillators
	void addOscillator(oscType type,stk::StkFloat freq);
	//! Adds oscillator of frequency freq to oscillators
	void addOscillator(oscType type,stk::StkFloat freq, stk::StkFloat amp); //TEMPORARY FUNCTION. WILL BE REMOVED
	//! Prints out all oscillator and other info about the object
	void print() const;
	//! Ticks all oscillators and sums results to one value
	stk::StkFloat tick();

private:
	std::vector<Oscillator*> oscillators;
	unsigned int t;
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