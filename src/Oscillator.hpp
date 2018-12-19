#ifndef ADASYNTH_OSCILLATOR_H
#define ADASYNTH_OSCILLATOR_H
#include <iostream>
#include <Stk.h>
#include <SineWave.h>
#include <BlitSaw.h>
#include <BlitSquare.h>

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
	Oscillator( void ) {}
	//! Default destructor
	~Oscillator( void ) {}
	//! Prints shorts description of this
	virtual void print() const = 0;
	//! Returns type of oscillator
	oscType getType() const { return type; }
	//! Calls tick() of oscillator
	virtual stk::StkFloat tick() = 0;
	// TODO:
	// 1. Extra effects?
protected:
	oscType type;
};

class SineOsc : public Oscillator
{
public:
	//! Default constructor
	SineOsc( void );
	//! Default destructor
	~SineOsc();
	//! Prints shorts description of this	
	void print() const { std::cout << "-------SineWave-------\n"; }
	//! Calls tick() of oscillator
	stk::StkFloat tick() { return oscillator.tick(); }
private:
	stk::SineWave oscillator;
};

class SawOsc : public Oscillator
{
public:
	//! Default constructor
	SawOsc( void );
	//! Default destructor
	~SawOsc();
	//! Prints shorts description of this	
	void print() const { std::cout << "-------SawWave-------\n"; }
	//! Calls tick() of oscillator
	stk::StkFloat tick() { return oscillator.tick(); }
private:
	stk::BlitSaw oscillator;
};

class SquareOsc : public Oscillator
{
public:
	//! Default constructor
	SquareOsc( void );
	//! Default destructor
	~SquareOsc();
	//! Prints shorts description of this	
	void print() const { std::cout << "-------SquareWave-------\n"; }
	//! Calls tick() of oscillator
	stk::StkFloat tick() { return oscillator.tick(); }
private:
	stk::BlitSquare oscillator;
};


#endif