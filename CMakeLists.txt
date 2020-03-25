cmake_minimum_required(VERSION 3.5)

project(qtsynth LANGUAGES CXX)

#SET( CMAKE_CXX_COMPILER "/usr/bin/x86_64-w64-mingw32-g++" )

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

#set (CMAKE_PREFIX_PATH "/home/rluedek/Qt5.7.0/5.7/")

find_package(Qt5 COMPONENTS Widgets REQUIRED)

#LINK_DIRECTORIES(/usr/lib/x86_64-linux-gnu/)

if(ANDROID)
  add_library(qtsynth SHARED
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
  )
else()
  add_executable(qtsynth
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    audio/Audio.cpp
    audio/Sine.cpp
    audio/Square.cpp
    audio/Triangle.cpp
    audio/oscillator/Lfo.cpp
    audio/envelope/Envelope.cpp
    audio/envelope/NoEnvelope.h
    audio/filter/LowpassFilter.cpp
    audio/filter/NoFilter.h
    audio/voice/Voice.cpp
    audio/voicemanager/VoiceManager.cpp
    audio/modulation/ModulationValue.cpp
  )
endif()

target_link_libraries(qtsynth PRIVATE Qt5::Widgets portaudio)
