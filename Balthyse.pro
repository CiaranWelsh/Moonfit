include("../Moonfit/moonfit.pri")

#name of the executable file generated
TARGET = Balthyse

#put += console to run in a separate terminal
#CONFIG += console

#bundles might be required for MAC OS 
#CONFIG -= app_bundle

TEMPLATE = app

HEADERS += \
    modelsStructABC.h \
    expThymus.h

SOURCES += \
    mainThymus.cpp \
    modelsStructABC.cpp \
    expThymus.cpp
