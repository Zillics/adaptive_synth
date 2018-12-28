#include "Oscillator.hpp"

SineOsc::SineOsc(stk::StkFloat freq)
{
	type = SINE;
	oscillator = *(new stk::SineWave());
	this->setFrequency(freq);
	t = 0.0;
	amplitude = 1;
}

stk::StkFloat SineOsc::getAmplitude() const
{
	return amplitude;
}

stk::StkFloat SineOsc::tick() 
{
	stk::StkFloat ret = getAmplitude()*oscillator.tick();
	t += tickInterval;
	return ret;
}

SawOsc::SawOsc(stk::StkFloat freq)
{
	type = SAW;
	oscillator = *(new stk::BlitSaw()); 
	this->setFrequency(freq);
	t = 0.0;
	amplitude = 1;
}

stk::StkFloat SawOsc::getAmplitude() const
{
	return amplitude;//0.01*t;
}


stk::StkFloat SawOsc::tick() 
{
	stk::StkFloat ret = getAmplitude()*oscillator.tick();
	t += tickInterval;
	return ret;
}


SquareOsc::SquareOsc(stk::StkFloat freq)
{
	type = SQUARE;
	oscillator = *(new stk::BlitSquare()); 
	this->setFrequency(freq);
	t = 0.0;
	amplitude = 1;
}

stk::StkFloat SquareOsc::getAmplitude() const
{
	return amplitude;//0.01*t;
}

stk::StkFloat SquareOsc::tick() 
{
	stk::StkFloat ret = getAmplitude()*oscillator.tick();
	t += tickInterval;
	return ret;
}


Oscillator::~Oscillator() {}

SineOsc::~SineOsc()
{
	delete &oscillator;
}

SawOsc::~SawOsc()
{
	delete &oscillator;
}

SquareOsc::~SquareOsc()
{
	delete &oscillator;
}