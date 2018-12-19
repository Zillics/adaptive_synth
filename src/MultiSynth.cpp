#include "MultiSynth.hpp"

MultiSynth::MultiSynth( void )
{

}

MultiSynth::~MultiSynth()
{
	for(auto osc : oscillators)
	{
		delete osc;
	}
	oscillators.clear();
}

void MultiSynth::addOscillator(oscType type)
{
	Oscillator* osc;
	switch(type)
	{
		case SINE :
			osc = new SineOsc();
			break;
		case SAW :
			osc = new SawOsc();
			break;
		case SQUARE :
			osc = new SquareOsc();
			break;
		default:
			throw std::invalid_argument("MultiSynth::addOscillator : no oscillator of that type!");
	}
	oscillators.push_back(osc);
}

void MultiSynth::print() const
{
	for(auto osc : oscillators)
	{
		osc->print();
	}
}