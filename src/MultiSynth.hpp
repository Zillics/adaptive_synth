#ifndef ADASYNTH_MULTISYNTH_H
#define ADASYNTH_MULTISYNTH_H
#include <iostream>
#include <Stk.h>
#include <SineWave.h>
#include <BlitSaw.h>
#include <BlitSquare.h>
#include <RtAudio.h>
#include "Oscillator.hpp"



class MultiSynth
{
public:
	//! Default constructor
	MultiSynth( void );
	//! Default destructor
	~MultiSynth( void );
	//! Adds oscillator to oscillators
	void addOscillator(oscType type);
	//! Prints out all oscillator and other info about the object
	void print() const;
	//! Ticks all oscillators and sums results to one value
	stk::StkFloat tick();

private:
	std::vector<Oscillator*> oscillators;
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
	//!
	//int tick( void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames, double streamTime, RtAudioStreamStatus status, void *dataPointer );
private:
	RtAudio dac;
};

#endif