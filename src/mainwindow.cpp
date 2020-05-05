/**
 * @copyright Copyright (c) 2020 Rico Luedeke
 * @author Rico Luedeke
 * @brief  This file is part of qt-port-synth (A baisc synthesizer using PortAudio and Qt5)
 * @date 2020-05-04
 * @see https://github.com/rluedek/qt-port-synth
 */

#include "mainwindow.h"

#include <QGuiApplication>
#include <QScreen>

#include "audio/filter/FilterTypes.h"
#include "audio/DefaultParameters.h"


#include "ui_mainwindow.h"
#include "qdebug.h"

MainWindow::MainWindow(QWidget *parent, AudioHal* hal, VoiceManager* pVoiceManager)
    : QMainWindow(parent)
    , m_hal(hal)
    , m_manager(pVoiceManager)
    , ui(new Ui::MainWindow)
    , m_dOctaveOsc(0.0)
{
    ui->setupUi(this);

    ui->VolumeAttackKnob->setValue(ENV_ATTACK_TIME_DEFAULT);
    ui->VolumeAttackKnob->setMaximum(ENV_ATTACK_TIME_MAX);
    ui->VolumeAttackKnob->setMinimum(ENV_ATTACK_TIME_MIN);
    ui->VolumeAttackKnob->setSingleStep(KNOB_STEP);
    connect(ui->VolumeAttackKnob, &QDial::valueChanged,
        m_manager, &VoiceManager::setEnvelopeAttackTime);

    ui->VolumeDecayKnob->setValue(ENV_DECAY_TIME_DEFAULT);
    ui->VolumeDecayKnob->setMaximum(ENV_DECAY_TIME_MAX);
    ui->VolumeDecayKnob->setMinimum(ENV_DECAY_TIME_MIN);
    ui->VolumeDecayKnob->setSingleStep(KNOB_STEP);
    connect(ui->VolumeDecayKnob, &QDial::valueChanged,
        m_manager, &VoiceManager::setEnvelopeDecayTime);

    
    ui->VolumeSustsainKnob->setMaximum(ENV_SUSTAIN_AMPL_MAX);
    ui->VolumeSustsainKnob->setMinimum(ENV_SUSTAIN_AMPL_MIN);
    ui->VolumeSustsainKnob->setSingleStep(KNOB_STEP);
    ui->VolumeSustsainKnob->setValue(ENV_SUSTAIN_AMPL_DEFAULT);
    connect(ui->VolumeSustsainKnob, &QDial::valueChanged,
        m_manager, &VoiceManager::setEnvelopeSustainAmplitude);

    ui->VolumeReleaseKnob->setMaximum(ENV_RELEASE_TIME_MAX);
    ui->VolumeReleaseKnob->setMinimum(ENV_RELEASE_TIME_MIN);
    ui->VolumeReleaseKnob->setSingleStep(KNOB_STEP);
    ui->VolumeReleaseKnob->setValue(ENV_RELEASE_TIME_DEFAULT);
    connect(ui->VolumeReleaseKnob, &QDial::valueChanged,
        m_manager, &VoiceManager::setEnvelopeReleaseTime);

    ui->FilterEnvelopeAttackKnob->setMaximum(FILTER_ENV_ATTACK_TIME_MAX);
    ui->FilterEnvelopeAttackKnob->setMinimum(FILTER_ENV_ATTACK_TIME_MIN);
    ui->FilterEnvelopeAttackKnob->setSingleStep(KNOB_STEP);
    ui->FilterEnvelopeAttackKnob->setValue(FILTER_ENV_ATTACK_TIME_DEFAULT);
    connect(ui->FilterEnvelopeAttackKnob, &QDial::valueChanged,
        m_manager, &VoiceManager::setGlobalEnvelopeAttackTime);

    ui->FilterDecayKnob->setMaximum(FILTER_ENV_DECAY_TIME_MAX);
    ui->FilterDecayKnob->setMinimum(FILTER_ENV_DECAY_TIME_MIN);
    ui->FilterDecayKnob->setSingleStep(KNOB_STEP);
    ui->FilterDecayKnob->setValue(FILTER_ENV_DECAY_TIME_DEFAULT);
    connect(ui->FilterDecayKnob, &QDial::valueChanged,
        m_manager, &VoiceManager::setGlobalEnvelopeDecayTime);

    ui->FilterSustainKnob->setMaximum(FILTER_ENV_SUSTAIN_AMPL_MAX);
    ui->FilterSustainKnob->setMinimum(FILTER_ENV_SUSTAIN_AMPL_MIN);
    ui->FilterSustainKnob->setSingleStep(KNOB_STEP);
    ui->FilterSustainKnob->setValue(FILTER_ENV_SUSTAIN_AMPL_DEFAULT);
    connect(ui->FilterSustainKnob, &QDial::valueChanged,
        m_manager, &VoiceManager::setGlobalEnvelopeSustainAmplitude);

    ui->FilterReleaseKnob->setMaximum(FILTER_ENV_RELEASE_TIME_MAX);
    ui->FilterReleaseKnob->setMinimum(FILTER_ENV_RELEASE_TIME_MIN);
    ui->FilterReleaseKnob->setSingleStep(KNOB_STEP);
    ui->FilterReleaseKnob->setValue(FILTER_ENV_RELEASE_TIME_DEFAULT);
    connect(ui->FilterReleaseKnob, &QDial::valueChanged,
        m_manager, &VoiceManager::setGlobalEnvelopeReleaseTime);

    ui->CutOffKnob->setMaximum(FILTER_CUTOFF_MAX);
    ui->CutOffKnob->setMinimum(FILTER_CUTOFF_MIN);
    ui->CutOffKnob->setSingleStep(KNOB_STEP);
    ui->CutOffKnob->setValue(FILTER_CUTOFF_DEFAULT);
    connect(ui->CutOffKnob, &QDial::valueChanged,
        m_manager, &VoiceManager::setCutOffFrequency);

    ui->ResonanceKnob->setMaximum(FILTER_RESONANCE_MAX);
    ui->ResonanceKnob->setMinimum(FILTER_RESONANCE_MIN);
    ui->ResonanceKnob->setSingleStep(KNOB_STEP);
    ui->ResonanceKnob->setValue(FILTER_RESONANCE_DEFAULT);
    connect(ui->ResonanceKnob, &QDial::valueChanged,
        m_manager, &VoiceManager::setResonance);

    ui->FilterLFOAmountKnob->setMaximum(LFO_AMOUNT_MAX);
    ui->FilterLFOAmountKnob->setMinimum(LFO_AMOUNT_MIN);
    ui->FilterLFOAmountKnob->setSingleStep(KNOB_STEP);
    ui->FilterLFOAmountKnob->setValue(LFO_AMOUNT_DEFAULT);
    connect(ui->FilterLFOAmountKnob, &QDial::valueChanged,
        m_manager, &VoiceManager::setLfoAmount);

    ui->FilterLFORateKnob->setMaximum(LFO_FREQUENCY_MAX);
    ui->FilterLFORateKnob->setMinimum(LFO_FREQUENCY_MIN);
    ui->FilterLFORateKnob->setSingleStep(KNOB_STEP);
    ui->FilterLFORateKnob->setValue(LFO_FREQUENCY_DEFAULT);
    connect(ui->FilterLFORateKnob, &QDial::valueChanged,
        m_manager, &VoiceManager::setLfoFrequency);

    ui->MixSlider->setMinimum(OSCILLATOR_MIX_MIN);
    ui->MixSlider->setMaximum(OSCILLATOR_MIX_MAX);
    ui->MixSlider->setSingleStep(KNOB_STEP);
    ui->MixSlider->setValue(OSCILLATOR_MIX_DEFAULT);
    connect(ui->MixSlider, &QSlider::valueChanged,
        m_manager, &VoiceManager::setOscillatorMix);

    ui->VolumeGainKnob->setMaximum(GAIN_MAX);
    ui->VolumeGainKnob->setMinimum(GAIN_MIN);
    ui->VolumeGainKnob->setSingleStep(KNOB_STEP);
    ui->VolumeGainKnob->setValue(GAIN_DEFAULT);
    connect(ui->VolumeGainKnob, &QDial::valueChanged,
        m_manager, &VoiceManager::setGain);


    connect(ui->RadioButton_Osc1_Sinus, &QRadioButton::clicked,
            this, &MainWindow::radioButton_Osc1_Sinus);
    
    
    connect(ui->RadioButton_Osc1_Square, &QRadioButton::clicked,
            this, &MainWindow::radioButton_Osc1_Square);


    connect(ui->RadioButton_Osc1_Triangle, &QRadioButton::clicked,
            this, &MainWindow::radioButton_Osc1_Triangle);


    connect(ui->RadioButton_Osc1_Saw, &QRadioButton::clicked,
            this, &MainWindow::radioButton_Osc1_Saw);


    connect(ui->RadioButton_Osc2_Sinus, &QRadioButton::clicked,
            this, &MainWindow::radioButton_Osc2_Sinus);
    
    
    connect(ui->RadioButton_Osc2_Square, &QRadioButton::clicked,
            this, &MainWindow::radioButton_Osc2_Square);


    connect(ui->RadioButton_Osc2_Triangle, &QRadioButton::clicked,
            this, &MainWindow::radioButton_Osc2_Triangle);


    connect(ui->RadioButton_Osc2_Saw, &QRadioButton::clicked,
            this, &MainWindow::radioButton_Osc2_Saw);

    
    connect(ui->FilterLFOSinButton, &QRadioButton::clicked,
            this, &MainWindow::radioButton_Lfo_Sinus);
    
    
    connect(ui->FilterLFOSqrButton, &QRadioButton::clicked,
            this, &MainWindow::radioButton_Lfo_Square);


    connect(ui->FilterLFOTriButton, &QRadioButton::clicked,
            this, &MainWindow::radioButton_Lfo_Triangle);


    connect(ui->FilterLFOSawButton, &QRadioButton::clicked,
            this, &MainWindow::radioButton_Lfo_Saw);


    connect(ui->Button_Octave_Down, &QAbstractButton::pressed,
            this, &MainWindow::octaveDown);


    connect(ui->Button_Octave_UP, &QAbstractButton::pressed,
            this, &MainWindow::octaveUp);


    connect(ui->BpButton, &QAbstractButton::pressed,
            this, &MainWindow::setFilterBP);


    connect(ui->HpButton, &QAbstractButton::pressed,
            this, &MainWindow::setFilterHP);


    connect(ui->LpButton, &QAbstractButton::pressed,
            this, &MainWindow::setFilterLP);

    // get screen resolution and set window to maximum screen size
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = screen->geometry();
    int height = screenGeometry.height();
    int width = screenGeometry.width();
    
    // resize to fullscreen
    //resize(width, height);
    }

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    if (event->isAutoRepeat())
    {
        event->ignore();
    }
    else
    {
        double frequency = keyNumberToFrequency(m_pianoKeys[event->key()]);
        m_hal->play(frequency);
    }
    
}

void MainWindow::keyReleaseEvent(QKeyEvent* event)
{
    if (event->isAutoRepeat())
    {
        event->ignore();
    }
    else
    {
        double frequency = keyNumberToFrequency(m_pianoKeys[event->key()]);
        qDebug() << "Frequency: " << frequency;
        m_hal->stop(frequency);
    }
}

void MainWindow::radioButton_Osc1_Sinus()
{
    Sine temp;
    m_manager->setOscillator1(std::make_shared<Sine>(temp));
}

void MainWindow::radioButton_Osc1_Square()
{
    Square temp;
    m_manager->setOscillator1(std::make_shared<Square>(temp));
}

void MainWindow::radioButton_Osc1_Triangle()
{
    Triangle temp;
    m_manager->setOscillator1(std::make_shared<Triangle>(temp));
}

void MainWindow::radioButton_Osc1_Saw()
{
    Saw temp;
    m_manager->setOscillator1(std::make_shared<Saw>(temp));
}

void MainWindow::radioButton_Osc2_Sinus()
{
    Sine temp;
    m_manager->setOscillator2(std::make_shared<Sine>(temp));
}

void MainWindow::radioButton_Osc2_Square()
{
    Square temp;
    m_manager->setOscillator2(std::make_shared<Square>(temp));
}

void MainWindow::radioButton_Osc2_Saw()
{
    Saw temp;
    m_manager->setOscillator2(std::make_shared<Saw>(temp));
}

void MainWindow::radioButton_Osc2_Triangle()
{
    Triangle temp;
    m_manager->setOscillator2(std::make_shared<Triangle>(temp));
}

void MainWindow::radioButton_Lfo_Sinus()
{
    Sine temp;
    m_manager->setLfoOscillator(std::make_shared<Sine>(temp));
}

void MainWindow::radioButton_Lfo_Square()
{
    Square temp;
    m_manager->setLfoOscillator(std::make_shared<Square>(temp));
}

void MainWindow::radioButton_Lfo_Triangle()
{
    Triangle temp;
    m_manager->setLfoOscillator(std::make_shared<Triangle>(temp));
}

void MainWindow::radioButton_Lfo_Saw()
{
    Saw temp;
    m_manager->setLfoOscillator(std::make_shared<Saw>(temp));
}

void MainWindow::octaveUp()
{
    if (m_dOctaveOsc < 4)
        m_dOctaveOsc++;
}

void MainWindow::octaveDown()
{
    if (m_dOctaveOsc > -4)
        m_dOctaveOsc--;
}

void MainWindow::setFilterBP()
{
    m_manager->setFilter(FilterType::BANDPASS);
}

void MainWindow::setFilterHP()
{
    m_manager->setFilter(FilterType::HIGHPASS);
}

void MainWindow::setFilterLP()
{
    m_manager->setFilter(FilterType::LOWPASS);
}

double MainWindow::keyNumberToFrequency(unsigned keynumber)
{
    keynumber += (12 * m_dOctaveOsc);
    qDebug() << keynumber << endl; 
    return 440.0 * pow(2.0, (keynumber - 69.0) / 12.0);
}