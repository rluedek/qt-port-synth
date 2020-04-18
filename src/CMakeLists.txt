cmake_minimum_required(VERSION 3.5)

project(yuna-synth LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(Qt5 COMPONENTS Widgets REQUIRED)


add_subdirectory("third_party/portaudio")

add_executable(yuna-synth
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

target_link_libraries(qt-port-synth PRIVATE Qt5::Widgets "libportaudio.so")
