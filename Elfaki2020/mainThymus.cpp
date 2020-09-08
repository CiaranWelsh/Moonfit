// -------------- Script that uses Moonfit to perform thymic atrophy simulations / optimizations -------------
//
// Author:      Philippe A. Robert (philippe [dot] robert [at] ens-lyon.org, 8th Feb. 2020
// Source:      gitlab.com/Moonfit/Balthyse
// References   [1] Robert, P., Jönsson, E and Meyer-Hermann, M MoonFit, a minimal interface for fitting ODE
//                  dynamical models, bridging simulation by experimentalists and customization by C++ programmers,
//                  BioRxiV 2018, https://doi.org/10.1101/281188
//              [2] Elfaki, Y. et al. Influenza A virus-induced thymic atrophy differentially affects conventional
//                  and regulatory T cell developmental dynamics. EJI 2020

#include <vector>
#include <string>
#include <iostream>
using namespace std;



// ------------- Step 1: Give the location to the data files, and a folder to export results

static string folder = "C:/Users/pprobert/Desktop/NewArchaeropteryx/Sources/Balthyse/DATA/";
static string folderBaseResults = "C:/Users/pprobert/Desktop/NewArchaeropteryx/Sources/Balthyse/Results";




// ------------- Step 2: Include Moonfit. "moonfit.h" is enough to use the full library
#include "../Moonfit/moonfit.h"

// Note: TO personnalize the configuration of Moonfit, you might want to have a look at Moonfit/common.h
//  -> it creates #define WINDOWS/UNIX/MAC and #define QT4/QT5 automatically if you need to use.
//  -> You can choose to compile without graphical interface nor Qt, then define WITHOUT_QT in common.h
//  -> It also defines useful functions (all platforms) like:
//  -> It gives predefined options for optimizers (for doing optimizations without GUI)
//            enum typeOptimizer {GeneticFast, SRESFast, Genetic25k,  ... SRES100k, ...
//            string optFileHeader(typeOptimizer toUse)




// ------------- Step 3: Now including all your models for the project, and the experiments defining what to do with them

// The model file defines the equations for thymic dynamics
// Note:    1/ to decide the type of model structure, manually use #define ModelStructureA or B or C inside modelsStructABC.h
//          2/ by default, the hypothesis of increased export has a different strength for each different population
//              -> to apply the hypothesis: "Equal modulation of export between Tregs and Tcongs, use #define equalExportTregs
//              -> to apply the hypothesis: "Equal modulation of export between all SP cells, use #define equalExportAll
#include "modelsStructABC.h"

// The experiment file defines different ways to simulate the model (equations), according to different hypotheses
#include "expThymus.h"







/// @brief Main : to get help, launch without any argument. Graphical window will open, and after quitting, all options will be displayed.
int main(int argc, char *argv[]){

    cout << "Thymic atrophy simulations, initializing: \n   -> Data files will be searched in " << folder << "\n   -> Results will be put in " << folderBaseResults << endl;
    #ifdef ModelStructureA
    cout << " ************ Simulations with MODEL STRUCTURE A ************* " << endl;
    #else
        #ifdef ModelStructureB
        cout << " ************ Simulations with MODEL STRUCTURE B ************* " << endl;
        #else
            #ifdef ModelStructureB
            cout << " ************ Simulations with MODEL STRUCTURE C ************* " << endl;
            #else
            cout << " Problem: No Model structure defined! Please use #define ModelStructureA or B or C inside modelsStructABC.h" << endl;
            return 0;
            #endif
        #endif
    #endif
    if(!dirExists(folder)) cerr << "! Problem: Could not find the fodler (does not exist?): " << folder << "\n => Please change inside scriptsThymus.cpp" << endl;
    if(!dirExists(folderBaseResults.c_str())) createFolder(folderBaseResults);

    // ---------- Step 4: Initializing Qt if necessary
    #ifndef WITHOUT_QT
    QApplication b(argc, argv);             // Starts the Qt application
    #endif


    // ----------- Step 5: Create a model and create an experiment with this model. Good to give a config file as well.

    Model* currentModel = new modele6GenericTVaslin();
    Experiment* currentExperiment = new expCombinedHyp(currentModel);
    string configFile = folder + string("ConfigAllHypStructuresABC.txt");
    cout << "   -> Using model : " << currentModel->name << " with experiment " << currentExperiment->Identification << "\n   -> Will use config file " << configFile << endl;

    // ----------- Step 6: Give experimental data to the experiment.

    cout << " -> The loaded data is:" << endl;
    TableCourse* Data_all = new TableCourse(folder + string("CellNrMillions.txt"));
    cout << Data_all->print() << endl;
    TableCourse* Data_all_Std = new TableCourse(folder + string("CellNrMillionsStd.txt"));
    cout << Data_all_Std->print() << endl;

    currentExperiment->giveData(Data_all, 0, Data_all_Std);

    // creates the list of data points/variables to be used for the cost function.
    // giving data after will not be included in the cost.
    currentExperiment->loadEvaluators();

    // creates interpolated curves (linear=false, spline=false) when want to replace a variable by the data.
    overrider* OverData_new = new overrider(Data_all, false);
    currentExperiment->setOverrider(0, OverData_new);

//  it is also possible to define overriders manually for separate variables:,
//  overrider* OverData_new = new overrider();
//  for(int i = 0; i < Data_all->nbVar; ++i){
//      string extVarName = Data_all->headers[i+1];
//      OverData_new->learnSpl(extVarName,Data_all->getTimePoints(i), Data_all->getTimeCourse(i), useSplines);
//  }



    #ifndef WITHOUT_QT
    cout << "Launching Graphical Interface ..." << endl;

    // Step 7a: Launch the graphical interface from an experiment (containing the model inside)
    simuWin* p = new simuWin(currentExperiment);

    // Step 7b: optionally give a config file
    p->loadConfig(configFile);

    // Step 7c: show the graphical interface!
    p->show();

    // Step 7d: leave the control to Qt instead of finishing the program
    b.exec();

    // That's it !

    #else
    cout << "WITHOUT_QT was defined => Continue without graphical interface.\n";

    #define TESTINGMODE false

    /* Pieces of code to perform optimizations manually */

    // =============== Create new result subfolder ================

    string folderRes = folderBaseResults + string("script") + codeTime() + string("/");           // Define working directory (name = "sim" + date)
    createFolder(folderRes);
    vector<string> listGeneratedFilesSets;                      // will store the files with parameter sets that to re-load them later


    // =============== Optimization options ... ================

    // deciding between different optimizer options, will be stored in the following stringstream
    stringstream headerOptimizer;
    // for testing, will just perform a few steps of optimization to check everything is working.
    if(TESTINGMODE) headerOptimizer << optFileHeader(GeneticFast);
    else headerOptimizer << optFileHeader(Genetic50k);

    // ========== The class manageSims is used to perform simulations / optimizations, without the graphical interface (instead of simuWin) ===========

    manageSims* msi = new manageSims(currentExperiment);        // manageSims is the class to perform optimizations/other things without graphical interface. simuWin is the extension with graphical interface.
    msi->loadConfig(configFile);                                // Now, loads a list of configurations (parameters + variables) to optimize, and optimizes them one by one


    // ----------------- Part 1 : for each combination (parameters-variables in the config file), do a fitting -----------------------

    for(int i = 0; i < msi->nbCombs; ++i){
        stringstream codeSimu;      codeSimu << "CombNr" << i << "-" << codeTime();               // generates a text code for this particular optimization, in case parallel optimizations are running
        stringstream folderComb;    folderComb << folderRes << codeSimu.str() << "/";        // creates a folder for this particular optimization, to create figures etc ...
        createFolder(folderComb.str());

        cout << "   -> Optimizing combination (" << i << ") with ID: " << codeSimu.str() << "\n";

        // re-takes the initial parameter set because parameters were probably changed by previous optimization for parameters that will not necessarily be optimized/modified in the next combinations
        msi->resetParamSetFromConfig(folder + configFile);

        // set options of simulation : dt initial = 10 sec, and no recording of regular kinetics (just recording of evaluators). Need to be done each time because simuWin->makeReports, etc will change the dt and will generate kinetics with its own dt in order to make plots
        currentExperiment->m->setPrintMode(false, 1);
        //currentExperiment->m->dt = 0.001;

        // creates the optimizer file for the combination of parameters to optimize, using boundaries from the configuration file, and the header from headeroptimizer
        string optOptions = msi->motherCreateOptimizerFile(i, headerOptimizer.str());       // for each combination, will need to re-create an optimizer file
        ofstream f1((folderComb.str() + string("Optimizer.txt")).c_str(), ios::out); if(f1) {f1 << optOptions << "\n"; f1.close();}

        // chose the variables to simulate and the ones to be replaced by data interpolated according to this combination
        msi->motherOverrideUsingComb(i);

        // DOES THE OPTIMIZATION !!!, and records the 1000 best sets
        msi->motherOptimize(folderComb.str() + string("Optimizer.txt"), 1000);

        // Exports all the best parameter sets.
        msi->saveHistory(folderComb.str() + string("History.txt"));

        listGeneratedFilesSets.push_back(folderComb.str() + string("History.txt"));

        // Generates report files.
        #ifndef WITHOUT_QT
        // if QT allowed, generates the plots for this best set
        simuWin tempWindow(currentExperiment);   // funny, if in non pointer with simuWin tw = simuWin(currentExperiment), get a compiling error 'use of deleted function' ...
        tempWindow.loadHistory(QString((folderComb.str() + string("History.txt")).c_str()));
        tempWindow.useParamSetFromHistory(0);                                                     // takes the first set of parameters (the best), also possible to use msi->useParamSetFromHistory(0, i); for overriding only parameters from this combination,
        tempWindow.simulate();
        tempWindow.makeFigReportParamSet(folderComb.str());
        ofstream f2((folderComb.str() + string("FitnessBestSetOf") + codeSimu.str() + string(".txt")).c_str(), ios::out); if(f2) {f2 << currentExperiment->costReport() << "\n"; f2.close();}
        ofstream f3((folderComb.str() + string("CostEvolutionDuringOptimization") + codeSimu.str() + string(".txt")).c_str(), ios::out); if(f3) {f3 << tempWindow.costRecords.print() << "\n"; f3.close();}
        #else
        msi->useParamSetFromHistory(0);                                                     // takes the first set of parameters (the best), also possible to use msi->useParamSetFromHistory(0, i); for overriding only parameters from this combination,
        msi->simulate();
        ofstream f2((folderComb.str() + string("FitnessBestSetOf") + codeSimu.str() + string(".txt")).c_str(), ios::out); if(f2) {f2 << currentExperiment->costReport() << "\n"; f2.close();}
        ofstream f3((folderComb.str() + string("CostEvolutionDuringOptimization.txt") + codeSimu.str()).c_str(), ios::out); if(f3) {f3 << msi->costRecords.print() << "\n"; f3.close();}
        #endif
    }
    #endif

    return 0;
}









