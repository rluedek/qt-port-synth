#include "mainwindow.h"

#include <QGuiApplication>
#include <QScreen>

#include "ui_mainwindow.h"
#include "qdebug.h"

MainWindow::MainWindow(QWidget *parent, AudioHal* hal, VoiceManager* pVoiceManager)
    : QMainWindow(parent)
    , m_hal(hal)
    , m_manager(pVoiceManager)
    , ui(new Ui::MainWindow)
    , m_dOctaveOsc1(0.0)
    , m_dOctaveOsc2(0.0)
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
    //this->grabKeyboard();

    if (event->isAutoRepeat())
    {
        event->ignore();
    }
    else
    {
        double frequency = keyNumberToFrequency(m_pianoKeys[event->key()]);
        qDebug() << "Frequency: " << frequency;
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
    if (m_dOctaveOsc1 < 4)
        m_dOctaveOsc1++;
}

void MainWindow::octaveDown()
{
    if (m_dOctaveOsc1 > -4)
        m_dOctaveOsc1--;
}

double MainWindow::keyNumberToFrequency(unsigned keynumber)
{
    keynumber += (12 * m_dOctaveOsc1);
    qDebug() << keynumber << endl; 
    return 440.0 * pow(2.0, (keynumber - 69.0) / 12.0);
}