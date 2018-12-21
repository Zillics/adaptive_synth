#include "MultiSynth.hpp"

int main()
{
	std::cout << "STK WORKS!" << std::endl;
	MultiSynth* ms = new MultiSynth("synth_files/violin.csv");
	//stk::StkFloat test = 0.01;
	//std::cout << test << std::endl;
	ms->print();
	Player* player = new Player();
	player->play(ms);
	return 0;
}