#include "MultiSynth.hpp"

int main()
{
	std::cout << "STK WORKS!" << std::endl;
	MultiSynth* ms = new MultiSynth();
	ms->addOscillator(SINE);
	ms->addOscillator(SAW);
	ms->addOscillator(SQUARE);
	Player* player = new Player();
	player->play(ms);
	return 0;
}