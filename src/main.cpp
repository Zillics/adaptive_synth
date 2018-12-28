#include "MultiSynth.hpp"

int main()
{
	std::cout << "STK WORKS!" << std::endl;
	MultiSynth* ms = new MultiSynth("synth_files/guitar_synth.csv");
	//MultiSynth* ms = new MultiSynth();
	//ms->addOscillator(SINE,440);
	//stk::StkFloat test = 0.01;
	//std::cout << test << std::endl;
	ms->print();
	Player* player = new Player();
	player->play(ms);
	player->record(ms, 4, "sound_files/guitar_synth.wav");
	return 0;
}