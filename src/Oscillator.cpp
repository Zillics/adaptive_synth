#include "Oscillator.hpp"

SineOsc::SineOsc()
{
	type = SINE;
	oscillator = *(new stk::SineWave());
	oscillator.setFrequency(440);
}

SawOsc::SawOsc()
{
	type = SAW;
	oscillator = *(new stk::BlitSaw()); 
	oscillator.setFrequency(440);
}

SquareOsc::SquareOsc()
{
	type = SQUARE;
	oscillator = *(new stk::BlitSquare()); 
	oscillator.setFrequency(440);
}