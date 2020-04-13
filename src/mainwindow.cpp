#include "mainwindow.h"

#include <QGuiApplication>
#include <QScreen>

#include "audio/filter/FilterTypes.h"

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

    ui->VolumeAttackKnob->setValue(0);
    ui->VolumeAttackKnob->setMaximum(990);
    ui->VolumeAttackKnob->setMinimum(1);
    ui->VolumeAttackKnob->setSingleStep(10);
    connect(ui->VolumeAttackKnob, &QDial::valueChanged,
        m_manager, &VoiceManager::setEnvelopeAttackTime);

    ui->VolumeDecayKnob->setValue(0);
    ui->VolumeDecayKnob->setMaximum(990);
    ui->VolumeDecayKnob->setMinimum(1);
    ui->VolumeDecayKnob->setSingleStep(10);
    connect(ui->VolumeDecayKnob, &QDial::valueChanged,
        m_manager, &VoiceManager::setEnvelopeDecayTime);

    ui->VolumeSustsainKnob->setValue(0);
    ui->VolumeSustsainKnob->setMaximum(990);
    ui->VolumeSustsainKnob->setMinimum(1);
    ui->VolumeSustsainKnob->setSingleStep(10);
    connect(ui->VolumeSustsainKnob, &QDial::valueChanged,
        m_manager, &VoiceManager::setEnvelopeSustainAmplitude);

    ui->VolumeReleaseKnob->setValue(0);
    ui->VolumeReleaseKnob->setMaximum(2000);
    ui->VolumeReleaseKnob->setMinimum(0);
    ui->VolumeReleaseKnob->setSingleStep(10);
    connect(ui->VolumeReleaseKnob, &QDial::valueChanged,
        m_manager, &VoiceManager::setEnvelopeReleaseTime);

    ui->FilterEnvelopeAttackKnob->setValue(0);
    ui->FilterEnvelopeAttackKnob->setMaximum(990);
    ui->FilterEnvelopeAttackKnob->setMinimum(1);
    ui->FilterEnvelopeAttackKnob->setSingleStep(10);
    connect(ui->FilterEnvelopeAttackKnob, &QDial::valueChanged,
        m_manager, &VoiceManager::setGlobalEnvelopeAttackTime);

    ui->FilterDecayKnob->setValue(0);
    ui->FilterDecayKnob->setMaximum(990);
    ui->FilterDecayKnob->setMinimum(1);
    ui->FilterDecayKnob->setSingleStep(10);
    connect(ui->FilterDecayKnob, &QDial::valueChanged,
        m_manager, &VoiceManager::setGlobalEnvelopeDecayTime);

    ui->FilterSustainKnob->setValue(0);
    ui->FilterSustainKnob->setMaximum(990);
    ui->FilterSustainKnob->setMinimum(1);
    ui->FilterSustainKnob->setSingleStep(10);
    connect(ui->FilterSustainKnob, &QDial::valueChanged,
        m_manager, &VoiceManager::setGlobalEnvelopeSustainAmplitude);

    ui->FilterReleaseKnob->setValue(0);
    ui->FilterReleaseKnob->setMaximum(2000);
    ui->FilterReleaseKnob->setMinimum(0);
    ui->FilterReleaseKnob->setSingleStep(10);
    connect(ui->FilterReleaseKnob, &QDial::valueChanged,
        m_manager, &VoiceManager::setGlobalEnvelopeReleaseTime);

    ui->CutOffKnob->setValue(1);
    ui->CutOffKnob->setMaximum(990);
    ui->CutOffKnob->setMinimum(1);
    ui->CutOffKnob->setSingleStep(10);
    connect(ui->CutOffKnob, &QDial::valueChanged,
        m_manager, &VoiceManager::setCutOffFrequency);

    ui->ResonanceKnob->setValue(1);
    ui->ResonanceKnob->setMaximum(990);
    ui->ResonanceKnob->setMinimum(1);
    ui->ResonanceKnob->setSingleStep(10);
    connect(ui->ResonanceKnob, &QDial::valueChanged,
        m_manager, &VoiceManager::setResonance);

    ui->FilterLFOAmountKnob->setValue(0);
    ui->FilterLFOAmountKnob->setMaximum(1000);
    ui->FilterLFOAmountKnob->setMinimum(0);
    ui->FilterLFOAmountKnob->setSingleStep(10);
    connect(ui->FilterLFOAmountKnob, &QDial::valueChanged,
        m_manager, &VoiceManager::setLfoAmount);

    ui->FilterLFORateKnob->setValue(0);
    ui->FilterLFORateKnob->setMaximum(20000);
    ui->FilterLFORateKnob->setMinimum(0);
    ui->FilterLFORateKnob->setSingleStep(10);
    connect(ui->FilterLFORateKnob, &QDial::valueChanged,
        m_manager, &VoiceManager::setLfoFrequency);

    ui->MixSlider->setValue(500);
    ui->MixSlider->setMinimum(0);
    ui->MixSlider->setMaximum(1000);
    ui->MixSlider->setSingleStep(10);
    connect(ui->MixSlider, &QSlider::valueChanged,
        m_manager, &VoiceManager::setOscillatorMix);

    ui->VolumeGainKnob->setValue(0);
    ui->VolumeGainKnob->setMaximum(1000);
    ui->VolumeGainKnob->setMinimum(0);
    ui->VolumeGainKnob->setSingleStep(1);


    connect(ui->VolumeGainKnob, &QDial::valueChanged,
        m_hal, &AudioHal::setVolume);


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