#include "MultiSynth.hpp"

int main()
{
	std::cout << "STK WORKS!" << std::endl;
	MultiSynth* ms = new MultiSynth();
	ms->addOscillator(SINE);
	ms->addOscillator(SAW);
	ms->addOscillator(SQUARE);
	ms->addOscillator(SINE);
	ms->addOscillator(SQUARE);
	ms->print();
	return 0;
}