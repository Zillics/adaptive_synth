#include "Oscillator.hpp"

SineOsc::SineOsc()
{
	type = SINE;
	oscillator = *(new stk::SineWave()); 
}

SawOsc::SawOsc()
{
	type = SAW;
	oscillator = *(new stk::BlitSaw()); 
}

SquareOsc::SquareOsc()
{
	type = SQUARE;
	oscillator = *(new stk::BlitSquare()); 
}