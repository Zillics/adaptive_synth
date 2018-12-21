#include "MultiSynth.hpp"

MultiSynth::MultiSynth( void )
{
	t = 0;
}

MultiSynth::MultiSynth(std::string filename)
{
	t = 0;
	std::ifstream istr_row;
	std::string line;
	std::string word;
	istr_row.open(filename,std::ifstream::in);
	if(istr_row.fail())
	{
		throw std::invalid_argument("MultiSynth: File does not exist!");
	}
	stk::StkFloat frequency;
	stk::StkFloat amplitude;
	while(std::getline(istr_row,line))
	{
		std::stringstream istr_col(line);
		if(!std::getline(istr_col,word,',')){throw std::invalid_argument("Wrong file format!");}
		frequency = std::stof(word);
		if(!std::getline(istr_col,word,',')){throw std::invalid_argument("Wrong file format!");}
		amplitude = std::stof(word);
		if(std::getline(istr_col,word,',')) {throw std::invalid_argument("Wrong file format!");}
		// Add oscillator
		addOscillator(SINE,frequency,amplitude);
	}
}

MultiSynth::~MultiSynth()
{
	for(auto osc : oscillators)
	{
		delete osc;
	}
	oscillators.clear();
}

void MultiSynth::addOscillator(oscType type, stk::StkFloat freq)
{
	Oscillator* osc;
	switch(type)
	{
		case SINE :
			osc = new SineOsc(freq);
			break;
		case SAW :
			osc = new SawOsc(freq);
			break;
		case SQUARE :
			osc = new SquareOsc(freq);
			break;
		default:
			throw std::invalid_argument("MultiSynth::addOscillator : no oscillator of that type!");
	}
	oscillators.push_back(osc);
}
//TEMPORARY FUNCTION. WILL BE REMOVED
void MultiSynth::addOscillator(oscType type,stk::StkFloat freq, stk::StkFloat amp)
{
	Oscillator* osc;
	switch(type)
	{
		case SINE :
			osc = new SineOsc(freq);
			osc->setAmplitude(amp);
			break;
		case SAW :
			osc = new SawOsc(freq);
			osc->setAmplitude(amp);			
			break;
		case SQUARE :
			osc = new SquareOsc(freq);
			osc->setAmplitude(amp);
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

stk::StkFloat MultiSynth::tick()
{
	stk::StkFloat result = 0.0;
	for(auto osc : oscillators)
	{
		result += osc->tick();
	}
	return result;
}


Player::Player( void )
{
	stk::Stk::setSampleRate( 44100.0 );
	stk::Stk::showWarnings( true );
}
//! The tick() function handles sample computation and scheduling of control updates.
//! It will be called automatically when the system needs a new buffer of audio samples.
int tick( void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames, double streamTime, RtAudioStreamStatus status, void *dataPointer )
{
	MultiSynth* synth = (MultiSynth*) dataPointer;
	//stk::SineWave* sine = (stk::SineWave*) dataPointer;
	register stk::StkFloat sample, *samples = (stk::StkFloat *) outputBuffer;
	for(unsigned int i = 0; i < nBufferFrames; i++)
	{
		sample = synth->tick();
		// Apply value to both stereo channels
		for ( int k=0; k<2; k++ ) *samples++ = sample;
	}
	return 0;
}

void Player::play(MultiSynth* synth)
{
    RtAudioFormat format = ( sizeof(stk::StkFloat) == 8 ) ? RTAUDIO_FLOAT64 : RTAUDIO_FLOAT32;
    RtAudio::StreamParameters parameters;
    parameters.deviceId = 6;
    parameters.nChannels = 2;
    unsigned int bufferFrames = stk::RT_BUFFER_SIZE;
    try 
    {
    	dac.openStream( &parameters, NULL, format, (unsigned int)stk::Stk::sampleRate(), &bufferFrames, &tick, (void *)synth );
    	dac.startStream();
    }
    catch ( RtAudioError& error ) 
    {
    	error.printMessage();
    }
  char input;
  std::cout << "\nPlaying ... press <enter> to quit.\n";
  std::cin.get( input );
  try 
  {
  	// Stop the stream
  	dac.stopStream();
  }
  catch (RtAudioError& e) {
  	e.printMessage();
  }
  if ( dac.isStreamOpen() ) dac.closeStream();
}
	
