#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <Qt>
#include <QMainWindow>
#include <QKeyEvent>

#include <QBoxLayout>
#include <QDial>
#include <QSlider>

#include "audio/Audio.h"
#include "audio/voicemanager/VoiceManager.h"
#include "audio/IOscillatorFunction.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr, AudioHal* hal = nullptr, VoiceManager* pVoiceManager = nullptr);
    ~MainWindow();

private:
    
    AudioHal *m_hal;
    VoiceManager *m_manager;
    Ui::MainWindow *ui;

    double m_dBaseFrequencyOsc1;
    double m_dBaseFrequencyOsc2;
    double m_dOctaveOsc1;
    double m_dOctaveOsc2;

    Square m_square;
    Sine m_sine;
    Triangle m_triangle;

    // YSXCFVGBNJMK
    std::map<int, int> m_pianoKeys = {    {Qt::Key_Y, 69}
                                        , {Qt::Key_S, 70}
                                        , {Qt::Key_X, 71}
                                        , {Qt::Key_C, 72}
                                        , {Qt::Key_F, 73}
                                        , {Qt::Key_V, 74}
                                        , {Qt::Key_G, 75}
                                        , {Qt::Key_B, 76}
                                        , {Qt::Key_N, 77}
                                        , {Qt::Key_J, 78}
                                        , {Qt::Key_M, 79}
                                        , {Qt::Key_K, 80}
                                    };

    void radioButton_Osc1_Sinus();
    void radioButton_Osc1_Square();
    void radioButton_Osc1_Triangle();
    void radioButton_Osc1_Saw();

    void radioButton_Osc2_Sinus();
    void radioButton_Osc2_Square();
    void radioButton_Osc2_Triangle();
    void radioButton_Osc2_Saw();

    void radioButton_Lfo_Sinus();
    void radioButton_Lfo_Square();
    void radioButton_Lfo_Triangle();
    void radioButton_Lfo_Saw();

    inline double keyNumberToFrequency(unsigned keynumber);

    void octaveUp();
    void octaveDown();
    
protected:
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);
};
#endif // MAINWINDOW_H
