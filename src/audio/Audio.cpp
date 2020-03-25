#include "Audio.h"

#include <cmath>

/*static*/
int AudioHal::m_sDefaultDeviceNumber = -1;


//ctor
AudioHal::AudioHal()
: m_priorFreq(0.0)
, m_frequency(0.0)
, stream(0)
, left_phase(0)
, right_phase(0)
, m_Playing(false)
, m_globalTime(0)
{

}

void AudioHal::initialize()
{
    printf("AudioHal: Initializing audio interface.\n");
    
    PaError err;

    err = Pa_Initialize();

    if (err != paNoError)
    {
        printf("AudioHal: Error while initialiazing.\n");
    }
    
    const PaDeviceInfo *deviceInfo;

    printf("AudioHal: Setting audio to default device.\n");
    m_sDefaultDeviceNumber = Pa_GetDefaultOutputDevice();

    printf( "Default Output: [ " );

    deviceInfo = Pa_GetDeviceInfo( m_sDefaultDeviceNumber );

    if( m_sDefaultDeviceNumber == Pa_GetHostApiInfo( deviceInfo->hostApi )->defaultOutputDevice )
    {
        const PaHostApiInfo *hostInfo = Pa_GetHostApiInfo( deviceInfo->hostApi );
    }

    printf( " ]\n" );
}

void AudioHal::terminate()
{
    Pa_Terminate();
}

void AudioHal::open()
{
    PaStreamParameters outputParameters;
    PaError err;
    
    outputParameters.device = Pa_GetDefaultOutputDevice(); /* default output device */
    if (outputParameters.device == paNoDevice) {
      fprintf(stderr,"Error: No default output device.\n");
      terminate();
    }
    outputParameters.channelCount = 2;       /* stereo output */
    outputParameters.sampleFormat = paFloat32; /* 32 bit floating point output */
    outputParameters.suggestedLatency = Pa_GetDeviceInfo( outputParameters.device )->defaultLowOutputLatency;
    outputParameters.hostApiSpecificStreamInfo = NULL;


    printf("AudioHal:: Opening stream...\n");
    err = Pa_OpenStream(
              &stream,
              NULL, /* no input */
              &outputParameters,
              SAMPLE_RATE,
              FRAMES_PER_BUFFER,
              paClipOff,      /* we won't output out of range samples so don't bother clipping them */
              &AudioHal::paCallback,
              this );


    if (err != paNoError)
    {
        terminate();
        return;
    }

    err = Pa_StartStream( stream );
    
    if (err != paNoError)
    {
        return;
    }
}

void AudioHal::play(double frequency)
{
    m_frequency = frequency;
    
    if (m_pVoiceManager != nullptr)
    {   
        printf("AudioHal::play\n");
        m_pVoiceManager->noteOn(frequency, getGlobalTime());
    }
 }

void AudioHal::stop(double frequency)
{
    if (m_pVoiceManager)
    {
        printf("AudioHal::stop\n");
        m_pVoiceManager->noteOff(frequency, getGlobalTime());
    }
}

int AudioHal::paUserCallback(    const void *inputBuffer, void *outputBuffer,
                        unsigned long framesPerBuffer,
                        const PaStreamCallbackTimeInfo* timeInfo,
                        PaStreamCallbackFlags statusFlags)
{
    float *out = (float*)outputBuffer;
    unsigned long i;

    (void) timeInfo; /* Prevent unused variable warnings. */
    (void) statusFlags;
    (void) inputBuffer;

    //create signal
    for( int j=0; j<TABLE_SIZE; j++ )
    {
        float value = m_pVoiceManager->getSample(m_globalTime);

        *out++ = 0.2 * value;  /* left */
        *out++ = 0.2 * value;  /* right */

        m_globalTime += TIME_STEP;
        if (m_globalTime >= SAMPLE_RATE)
        {    
            m_globalTime = 0;
        }
    }

    return paContinue;
}

/*
SETTER AND GETTER
*/

double AudioHal::getGlobalTime()
{
    return m_globalTime;
}

void AudioHal::setVoiceManager(VoiceManager* pVoicemanager)
{
    m_pVoiceManager = pVoicemanager;
}