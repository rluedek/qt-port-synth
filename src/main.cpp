/**
 * @copyright Copyright (c) 2020 Rico Luedeke
 * @author Rico Luedeke
 * @brief  This file is part of qt-port-synth (A baisc synthesizer using PortAudio and Qt5)
 * @date 2020-05-04
 * @see https://github.com/rluedek/qt-port-synth
 */

#include "mainwindow.h"

#include <QApplication>

#include "audio/Audio.h"

#include "audio/IOscillatorFunction.h"

#include "audio/envelope/Envelope.h"

#include "audio/filter/LowpassFilter.h"

#include "audio/voice/Voice.h"

#include "audio/voicemanager/VoiceManager.h"

#include "audio/oscillator/Lfo.h"

int main(int argc, char *argv[])
{
    //create audio interface
    AudioHal audio;

    //create a voice manager
    VoiceManager manager;

    audio.setVoiceManager(&manager);
    audio.initialize();
    audio.open();

    QApplication a(argc, argv);
    MainWindow w(nullptr, &audio, &manager);
    w.show();
    return a.exec();
}
