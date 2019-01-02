#include "MultiSynth.hpp"
#define CSV_DIR "synth_files/"

int main(int argc, char** argv)
{
	std::cout << "STK WORKS!" << std::endl;
	std::string csv_filename = (std::string)CSV_DIR + (std::string)argv[1];
	std::string csv_noisename = (std::string)CSV_DIR + (std::string)argv[2];
	std::cout << csv_filename << std::endl;
	std::cout << csv_noisename << std::endl;
	MultiSynth* ms = new MultiSynth(csv_filename,csv_noisename);
	//MultiSynth* ms = new MultiSynth();
	//ms->addOscillator(SINE,440);
	//stk::StkFloat test = 0.01;
	//std::cout << test << std::endl;
	ms->print();
	Player* player = new Player();
	player->play(ms);
	//player->record(ms, 4, "sound_files/flugelhorn.wav_resynthesized.csv");
	return 0;
}