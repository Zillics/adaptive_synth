#ifndef ADASYNTH_OSCILLATOR_H
#define ADASYNTH_OSCILLATOR_H
#include <iostream>
#include <Stk.h>
#include <SineWave.h>
#include <BlitSaw.h>
#include <BlitSquare.h>
#define TICK_INTERVAL 0.001

enum oscType
{
	SINE,
	SAW,
	SQUARE
};

class Oscillator
{
public:
	//! Default constructor
	Oscillator( void ) {};
	//! Default destructor
	virtual ~Oscillator( void ) = 0;
	//! Prints shorts description of this
	virtual void print() const = 0;
	//! Returns type of oscillator
	oscType getType() const { return type; }
	//! Calls tick() of oscillator
	virtual stk::StkFloat tick() = 0;
	//! Sets frequency of oscillator
	virtual void setFrequency(stk::StkFloat freq) = 0;
	//! Gets frequency of oscillator
	stk::StkFloat getFrequency() const { return frequency; }
	// TODO:
	// 1. Extra effects?
	void setAmplitude(stk::StkFloat amp) { amplitude = amp; } //TEMPORARY FUNCTION. WILL BE REMOVED
protected:
	oscType type;
	stk::StkFloat frequency;
	stk::StkFloat amplitude; //TEMPORARY VARIABLE. WILL BE REMOVED
	stk::StkFloat t;
};

class SineOsc : public Oscillator
{
public:
	//! Default constructor
	SineOsc(stk::StkFloat freq);
	//! Default destructor
	~SineOsc();
	//! Prints shorts dvpn.aalto.fiescription of this	
	void print() const { std::cout << frequency << "Hz-------SineWave-------" << amplitude <<"\n"; }
	//! Calls tick() of oscillator
	stk::StkFloat tick();
	//! Sets frequency of oscillator
	void setFrequency(stk::StkFloat freq) { frequency = freq; oscillator.setFrequency(freq); }
	stk::StkFloat getAmplitude() const;
private:
	stk::SineWave oscillator;
};

class SawOsc : public Oscillator
{
public:
	//! Default constructor
	SawOsc(stk::StkFloat freq);
	//! Default destructor
	~SawOsc();
	//! Prints shorts description of this	
	void print() const { std::cout <<  frequency << "Hz-------SawWave-------" << amplitude << "\n"; }
	//! Calls tick() of oscillator
	stk::StkFloat tick();
	//! Sets frequency of oscillator
	void setFrequency(stk::StkFloat freq) { frequency = freq; oscillator.setFrequency(freq); }
	stk::StkFloat getAmplitude() const;
private:
	stk::BlitSaw oscillator;
};

class SquareOsc : public Oscillator
{
public:
	//! Default constructor
	SquareOsc(stk::StkFloat freq);
	//! Default destructor
	~SquareOsc();
	//! Prints shorts description of this	
	void print() const { std::cout <<  frequency << "Hz-------SquareWave-------" << amplitude <<"\n"; }
	//! Calls tick() of oscillator
	stk::StkFloat tick();
	//! Sets frequency of oscillator
	void setFrequency(stk::StkFloat freq) { frequency = freq; oscillator.setFrequency(freq); }
	stk::StkFloat getAmplitude() const;
private:
	stk::BlitSquare oscillator;
};


#endif