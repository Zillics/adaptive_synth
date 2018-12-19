#ifndef ADASYNTH_MULTISYNTH_H
#define ADASYNTH_MULTISYNTH_H
#include <iostream>
#include <Stk.h>
#include <SineWave.h>
#include <BlitSaw.h>
#include <BlitSquare.h>
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
	//! Plays note in defined frequency
	void play(stk::StkFloat frequency) const;
	//! Ticks all oscillators and sums results to one value
	stk::StkFloat tick();

private:
	std::vector<Oscillator*> oscillators;
};


#endif