# In order to compile yout C++ files using Moonfit, two ways:
# Option 1: design a .pro file containing your files and add the following command inside : include(Moonfit/moonfit.pri).
# Option 2: add all C++ and h files from moonfit folder and subfolders into your .pro (together with your own files including moonfit).
#			in that case, please make sure to use the following commands inside your .pro 

# A - Options that you can put inside your .pro file (just uncomment there)

#name of the executable file generated
#TARGET = MoonfitProject

#put += console to run in a separate terminal
#CONFIG += console

#bundles might be required for MAC OS 
#CONFIG -= app_bundle

#TEMPLATE = app

# this function allows to do include(Moonfit.pri) from another project
INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD
#message("Moonfit Library included from folder :")
#message($$PWD)

# B - options for including Moonfit.

# note: the options widgets and core gui are necessary for the production of the ui_....h automatically from interface files (.ui).
QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport


# ======================== BOOST PART ==================================
# boost is not required anymore for the code.
win32: INCLUDEPATH += C:\Qt\Boost\boost_1_62_0\boost_1_62_0
#in windows, boosts raises the following error : "boost unable to find numeric literal operator operator Q" => need to add the following option
win32: QMAKE_CXXFLAGS += -fext-numeric-literals
# to avoid lots of useless warnings from boost library files (wtf !)
QMAKE_CXXFLAGS += -Wno-unused-local-typedefs -Wreorder -Wno-unused-parameter


# Necessary only for boost - would also be necessary for the syntax vector<int> bla = {1, 2, 3};
QMAKE_CXXFLAGS += -std=c++11

HEADERS += \
    $$PWD/common.h \
    $$PWD/moonfit.h \
    $$PWD/Framework/evaluator.h \
    $$PWD/Framework/generate.h \
    $$PWD/Framework/modele.h \
    $$PWD/Framework/overrider.h \
    $$PWD/Framework/spline.h \
    $$PWD/Framework/tableCourse.h \
    $$PWD/Framework/parameterSets.h \
    $$PWD/Extreminator/common/myFiles.h \
    $$PWD/Extreminator/common/myRandom.h \
    $$PWD/Extreminator/common/myTimes.h \
    $$PWD/Extreminator/common/statistiques.h \
    $$PWD/Extreminator/baseProblem.h \
    $$PWD/Extreminator/include/multimedia/AudioDefs.hpp \
    $$PWD/Extreminator/include/multimedia/VideoDefs.hpp \
    $$PWD/Extreminator/include/blas.h \
    $$PWD/Extreminator/include/blascompat32.h \
    $$PWD/Extreminator/include/covrt.h \
    $$PWD/Extreminator/include/emlrt.h \
    $$PWD/Extreminator/include/engine.h \
    $$PWD/Extreminator/include/fintrf.h \
    $$PWD/Extreminator/include/io64.h \
    $$PWD/Extreminator/include/lapack.h \
    $$PWD/Extreminator/include/mat.h \
    $$PWD/Extreminator/include/matrix.h \
    $$PWD/Extreminator/include/mex.h \
    $$PWD/Extreminator/include/mwmathutil.h \
    $$PWD/Extreminator/include/tmwtypes.h \
    $$PWD/Extreminator/optimizers/SRES/ESES.h \
    $$PWD/Extreminator/optimizers/SRES/ESSRSort.h \
    $$PWD/Extreminator/optimizers/SRES/sharefunc.h \
    $$PWD/Extreminator/optimizers/baseOptimizer.h \
    $$PWD/Extreminator/optimizers/CMAES.h \
    $$PWD/Extreminator/optimizers/Config.h \
    $$PWD/Extreminator/optimizers/Genetic.h \
    $$PWD/Extreminator/optimizers/GeneticGeneral.h \
    $$PWD/Extreminator/optimizers/GradientDescent.h \
    $$PWD/Extreminator/optimizers/individual.h \
    $$PWD/Extreminator/optimizers/MultipleGradientDescent.h \
    $$PWD/Extreminator/optimizers/Orthogonalise.h \
    $$PWD/Extreminator/optimizers/population.h \
    $$PWD/Extreminator/optimizers/scalingFunctions.h \
    $$PWD/Extreminator/optimizers/simulatedAnnealing.h \
    $$PWD/Extreminator/optimizers/SRES.h \
    $$PWD/Extreminator/fitteInterface.h \
    $$PWD/Interface/optselect.h \
    $$PWD/Interface/grapheCustom.h \
    $$PWD/Interface/QCustomPlot/qcustomplot.h \
    $$PWD/Interface/starter.h \
    $$PWD/Interface/simuwin.h \
    $$PWD/Framework/experiment.h
   
SOURCES += \
    $$PWD/Framework/evaluator.cpp \
    $$PWD/Framework/experiment.cpp \
    $$PWD/Framework/generate.cpp \
    $$PWD/Framework/modele.cpp \
    $$PWD/Framework/overrider.cpp \
    $$PWD/Framework/spline.cpp \
    $$PWD/Framework/tableCourse.cpp \
    $$PWD/Framework/parameterSets.cpp \
    $$PWD/Interface/simuwin.cpp \
    $$PWD/Interface/optselect.cpp \
    $$PWD/Interface/grapheCustom.cpp \
    $$PWD/Interface/QCustomPlot/qcustomplot.cpp \
    $$PWD/Interface/starter.cpp \
    $$PWD/Extreminator/common/myFiles.cc \
    $$PWD/Extreminator/common/myRandom.cc \
    $$PWD/Extreminator/common/myTimes.cc \
    $$PWD/Extreminator/optimizers/SRES/ESES.cc \
    $$PWD/Extreminator/optimizers/SRES/ESSRSort.cc \
    $$PWD/Extreminator/optimizers/SRES/sharefunc.cc \
    $$PWD/Extreminator/optimizers/baseOptimizer.cc \
    $$PWD/Extreminator/optimizers/CMAES.cc \
    $$PWD/Extreminator/optimizers/Config.cc \
    $$PWD/Extreminator/optimizers/Genetic.cc \
    $$PWD/Extreminator/optimizers/GeneticGeneral.cc \
    $$PWD/Extreminator/optimizers/GradientDescent.cc \
    $$PWD/Extreminator/optimizers/individual.cc \
    $$PWD/Extreminator/optimizers/Orthogonalise.cc \
    $$PWD/Extreminator/optimizers/population.cc \
    $$PWD/Extreminator/optimizers/scalingFunctions.cc \
    $$PWD/Extreminator/optimizers/simulatedAnnealing.cc \
    $$PWD/Extreminator/optimizers/SRES.cc \
    $$PWD/Extreminator/fitteInterface.cpp \
    $$PWD/Interface/minimumInterface.cpp \
    $$PWD/common.cpp

FORMS += \
    $$PWD/Interface/simuwin.ui \
    $$PWD/Interface/optselect.ui \
    $$PWD/Interface/starter.ui
	
#In case you want to use the QWT library instead of QCustomPlot
#QT += printsupport
#QT += opengl
#QT += svg
