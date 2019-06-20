#ifndef Moonfit_H
#define Moonfit_H

// To include the Moonfit library from a project, just include this file,
// have a look at .pri to see how to compile your project

#include "common.h"

#include "Framework/modele.h"
#include "Framework/experiment.h"
#include "Framework/tableCourse.h"
#include "Framework/evaluator.h"
#include "Framework/overrider.h"
 
#include "Interface/simuwin.h"


// include for the main() that will launch Moonfit.
#ifndef WITHOUT_QT
#ifdef QT5
#include <QMainWindow>
#include <QApplication>
#endif
#ifdef QT4
#include <QtGui/QMainWindow>
#include <QtGui/QApplication>
#endif
#endif

#endif // COMMON_H
