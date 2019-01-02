#include "MultiSynth.hpp"

MultiSynth::MultiSynth( void )
{
	t = 0;
}

MultiSynth::MultiSynth(std::string filename)
{
	read_file(filename,SINE);
}

MultiSynth::MultiSynth(std::string sine_file,std::string noise_file)
{
	read_file(sine_file,SINE);
	read_file(noise_file,NOISE);
}

void MultiSynth::read_file(std::string filename,oscType osc_type)
{
	t = 0;
	std::ifstream istr_row;
	std::string line;
	std::string word;
	istr_row.open(filename,std::ifstream::in);
	if(istr_row.fail())
	{
		throw std::invalid_argument("MultiSynth: File " + filename + "does not exist!");
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
		addOscillator(osc_type,frequency,amplitude);
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
	osc->set_tickInterval(1/sampleRate);
	oscillators.push_back(osc);
	n_osc += 1;
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
		case NOISE : 
			osc = new Noise(freq,amp);
			break;
		default:
			throw std::invalid_argument("MultiSynth::addOscillator : no oscillator of that type!");
	}
	osc->set_tickInterval(1/sampleRate);
	oscillators.push_back(osc);
	if(amp > maxAmp) { maxAmp = amp; }
	n_osc += 1;
}


void MultiSynth::print() const
{
	std::cout << "*****MultiSynth**object*****" << std::endl;
	std::cout << "Sample rate: " << sampleRate << "Hz" << std::endl;
	std::cout << "Number of oscillators: " << n_osc << std::endl;
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
	result = amp*result;
	if(result > 1.0 || result < -1.0) { std::cout << "Upper/Lower bound reached! " << result << std::endl; }
	return result;
}


Player::Player( void )
{
	std::cout << "Initializing player of sampling rate " << SAMPLE_RATE << std::endl;
	stk::Stk::setSampleRate( SAMPLE_RATE );
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
	synth->updateAmp();
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
	
//! Record MultiSynth object for _ seconds to wav file
void Player::record(MultiSynth* synth, unsigned int seconds, std::string filepath)
{
	stk::FileWvOut output;
	// Open a 16-bit, two-channel WAV formatted output file
	output.openFile(filepath, 1, stk::FileWrite::FILE_WAV, stk::Stk::STK_SINT16 );
	unsigned int n_samples = seconds*SAMPLE_RATE; //TODO: fetch sample rate from internal variable of object instead
	// Run the oscillator for n_sampes samples, writing to the output file
	for ( unsigned int i=0; i<n_samples; i++ )
    	output.tick( synth->tick() );

}