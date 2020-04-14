cmake_minimum_required(VERSION 3.5)

project(qtsynth LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

# this would be needed if qt would be on another place, but then portaudio wouldn't be found
#set (CMAKE_PREFIX_PATH "/home/rluedek/Qt5.7.0/5.7/") 

find_package(Qt5 COMPONENTS Widgets REQUIRED)

#LINK_DIRECTORIES(/usr/lib/x86_64-linux-gnu/)

add_executable(qt-port-synth
  main.cpp
  mainwindow.cpp
  mainwindow.h
  mainwindow.ui
  audio/Audio.cpp
  audio/Sine.cpp
  audio/Square.cpp
  audio/Saw.cpp
  audio/Triangle.cpp
  audio/oscillator/Lfo.cpp
  audio/envelope/Envelope.cpp
  audio/envelope/NoEnvelope.h
  audio/filter/LowpassFilter.cpp
  audio/filter/HighpassFilter.cpp
  audio/filter/BandpassFilter.cpp
  audio/filter/NoFilter.h
  audio/voice/Voice.cpp
  audio/voicemanager/VoiceManager.cpp
  audio/modulation/ModulationValue.cpp
)

target_link_libraries(qt-port-synth PRIVATE Qt5::Widgets portaudio)
