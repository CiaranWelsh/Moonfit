include("../Moonfit/moonfit.pri")

#name of the executable file generated
TARGET = YassinSplThym3.9

#put += console to run in a separate terminal
#CONFIG += console

#bundles might be required for MAC OS ??
#CONFIG -= app_bundle

TEMPLATE = app

HEADERS += \
    expThymus.h \
    namesThymus.h \
    Model1ThymusOnly/modele1ThymusOnly.h \
    Model2ThymusSpleen/modele1ThymusSpleen.h \
    Model0ManessoOnly/modele0ManessoOnly.h \
    Model0TVaslin2007Only/modeleTVaslin2007.h \
    Model3TSManesso/modele3MultiDiv.h \
    Model4MegaThymus/modele4MegaThymus.h \
    Model0OneCompartment/modele0OneCompartment.h \
    Model5SuperDN/modele5SuperDN.h \
    Model6GenericTVaslin/modele6GenericTVaslin.h 

SOURCES += \
    expThymus.cpp \
    namesThymus.cpp \
    scriptsThymus.cpp \
    Model1ThymusOnly/modele1ThymusOnly.cpp \
    Model2ThymusSpleen/modele1ThymusSpleen.cpp \
    Model0ManessoOnly/modele0ManessoOnly.cpp \
    Model0TVaslin2007Only/modeleTVaslin2007.cpp \
    Model3TSManesso/modele3MultiDiv.cpp \
    Model4MegaThymus/modele4MegaThymus.cpp \
    Model0OneCompartment/modele0OneCompartment.cpp \
    Model5SuperDN/modele5SuperDN.cpp \
    Model6GenericTVaslin/modele6GenericTVaslin.cpp 