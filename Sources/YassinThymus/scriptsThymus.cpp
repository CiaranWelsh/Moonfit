// The file common.h checks the system and defines WINDOWS/UNIX and QT4/QT5.
#include "../common.h"
#include "Extreminator/common/myRandom.h"

#ifdef WINDOWS
#include <windows.h>
#endif

#ifdef UNIX
#include <sys/stat.h>
#endif

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

#include <vector>
#include <ctime>
using namespace std;

#include "../Interface/simuwin.h"
#include "../Interface/starter.h"

#include "namesThymus.h"
#include "expThymus.h"
#include "Model0ManessoOnly/modele0ManessoOnly.h"
#include "Model0TVaslin2007Only/modeleTVaslin2007.h"
#include "Model1ThymusOnly/modele1ThymusOnly.h"
#include "Model2ThymusSpleen/modele1ThymusSpleen.h"
#include "Model3TSManesso/modele3MultiDiv.h"


/// @brief tool functions implemented below
string codeTime();                                              /// @brief a function to give a different name each time called (based on the time)
string textFileForFolder(string explanations);                  /// @brief generates the .tex to analyze a folder with results (pictures)
void compileLatex(string folderRes, string texFile);            /// @brief ask the system to compile a tex file and put the result in folderRes
void mergePDFs(vector<string> & listFiles, string outputFile);  /// @brief merges PDF files into one with a new name
string removeFolderFromFile(string file);                       /// @brief keeps only the file name (and not folder)

/// @brief MAIN SCRIPTS (called by the main or can be called manually)
void scriptsWithMainExp(int nb, string newConfigFile = string(""), string newParameterSet = string(""));        // mentioning the script that the main will call (one argument)
//string scriptsWithPerturbations(int nb, double parameter, string analysisName = string(""), string outputFolder = string(""), string chosenConfig = string(""), string chosenSet = string(""));                                                        // mentioning the script that the main will call (two arguments)
//void scriptsWith20HoursExp(int nb,string chosenConfig = string(""), string newParameterSet = string(""));
//void MultiObjective(int nb = 0,string chosenConfig = string(""), string newParameterSet = string(""));

enum{ ANA_CANO = 1, ANA_PERTURB = 2, ANA_DENS = 4, ANA_TITR = 8, ANA_PARAM_AROUND = 16, ANA_PARAM_SCAN = 32, ANA_CYCLO = 64, ANA_BACKGR = 128, ANA_PERTURB20 = 256, ANA_ALL = ANA_CANO | ANA_PERTURB | ANA_DENS | ANA_TITR | ANA_PARAM_AROUND | ANA_PARAM_SCAN | ANA_CYCLO | ANA_BACKGR | ANA_PERTURB20};
//void TotalAnalysis(int ChosenAnalysis = -1, string exportFolder = string(""), string chosenSet = string(""));
//void reAnalyzeFolder(int ChosenAnalysis, string _folder, bool includingSubFolders);

/// @brief Define here the working folder to open/write files, where The project file is is.
//#define folder string("C:/Users/Philippe/Desktop/Work/RestartV2016/Sources/TasosLMajor/")
//#define defaultfolder string("/home/phr13/Archeopteryx/2016-11-23/Sources/TasosLMajor/")
//#define defaultfolderBaseResults string("/home/phr13/Archeopteryx/2016-11-23/Results/")
string folder;
string folderBaseResults;


/// @brief standardization of the possible options for optimizing.
enum typeOptimizer {GeneticFast, SRESFast, Genetic25k, Genetic50k, Genetic100k, Genetic250k, Genetic500k, Genetic1M, SRES25k, SRES50k, SRES100k, SRES250k, SRES500k, SRES1M, GeneticAllCombs25k, GeneticAllCombs50k, GeneticAllCombs100k, GeneticAllCombs250k};
string optName(typeOptimizer toUse);
string optFileHeader(typeOptimizer toUse);
// To switch the optimizers in fast mode (just a few simulations).
#define TESTINGMODE 0




/// @brief Main : to get help, launch without any argument. Graphical window will open, and when quitted, all options will be displayed.
int main(int argc, char *argv[]){

    // ==================================== Initializing Qt ========================================
    #ifndef WITHOUT_QT
    QApplication b(argc, argv);     // Starts the Qt application
    #endif

    // ====================== Setting up the working folders automatically =========================
    // Note : the structure of the project should be : a "Sources" master directory, with all things inside, including the .pro file"
    folder = locateProjectDirectory(string("YassinODEs.pro")) + string("YassinThymus/");
    if (folder.size() == 0) { cout << "ERR: Working folders could not be auto-detected \n"; return 0; } // folder = defaultfolder;  folderBaseResults = defaultfolderBaseResults;  cout << " : \n -> " << folder << endl << " -> " << folderBaseResults << endl;
    else {folderBaseResults = getParentFolder(getParentFolder(folder)) + string("Results/");}
    createFolder(folderBaseResults); // in case it does not exist,
    cout << "Working folders were auto-detected to be : \n -> " << folder << endl << " -> " << folderBaseResults << endl;

    // ======================================= Manual commands =====================================
    if(false){
        {

            /*Modele* ML = new modeleLeishmania();
            ML->dt = 0.00001;
            Experiment* Exp = new expLMajor(ML);
            Exp->init();
            Exp->simulate(Small_Dose);*/


            scriptsWithMainExp(0);
            #ifndef WITHOUT_QT
            return b.exec();                // to leave the control to Qt instead of finishing the program
            #endif
        }
        return 0;
    }

    // =============== Launcher (from command line options or launch GUI) ==========================
    switch(argc){
        case 0: case 1: {       // ================= No arguments : launch the graphical interface -> manual choice ===================

            string exeName = removeFolderFromFile(string(argv[0]));
            cout << "\n   Welcome !\n" << endl;
            cout << "   -> No option chosen from command line ..." << endl;
            cout << "   -> For information, here are command line options to use the program :\n" << endl;

            cout << "\n\n ---------------------------- Canonical Differentiation -----------------------------------\n" << endl;
            cout << "Syntax 1 (2/4/6 args): "  << exeName << " NumScript " << endl;
            //cout << "variants : "  << exeName << " NumScript    -set       parameterSetFile.txt" << endl;
            //cout << "or       : "  << exeName << " NumScript    -config    configFile.txt" << endl;
            //cout << "or both" << endl;
            scriptsWithMainExp(-1);             // to print all options

            /*cout << "\n\n ---------------------Predictions from all kinds of experimlents --------------------------\n" << endl;
            cout << "Syntax 2 (3/5/7 args): "  << argv[0] << " NumScript   parameter" << endl;
            cout << "variants : "  << exeName << " NumScript    parameter    -set       parameterSetFile.txt" << endl;
            cout << "or       : "  << exeName << " NumScript    parameter    -config    configFile.txt" << endl;
            cout << "or both" << endl;
            scriptsWithPerturbations(-1, 0);    // to print all options

            cout << "\n\n --------------------Making a PDF report with all the predictions--------------------------\n" << endl;
            cout << "Syntax 3 (2 args): " << exeName << " total" << endl;

            cout << "\n\n --------------------Fittings all data together from changing cytokines at 20 hours--------------------------\n" << endl;
            cout << "Syntax 4 (2 args): " << exeName << " 20hours" << endl;

            cout << "\n\n --------------------Multiobjective Fittings from changing cytokines at 20 hours--------------------------\n" << endl;
            cout << "Syntax 6 (3 args): " << exeName << " multi    NumScript" << endl;
            MultiObjective(-1);                 // to print all options

            cout << "\n\n\n\n";

            #ifndef WITHOUT_QT      // If graphical interface is allowed in compiling -> launch a starter GUI
            cout << "   -> launching starting GUI to chose manually what to do ..." << endl;
            Starter* st = new Starter(folder);
            string configFileM0 = string("M3a-SimpleNoIL10/configForModeleSimpleNoIL10.txt");
            Modele* currentModelM0 = new modeleSimpleNoIL10();
            string configFileM1 = string("M3c-MinNoIL10/configForModeleMinNoIL10.txt");
            Modele* currentModelM1 = new modeleMinNoIL10();
            string configFileM2 = string("M4-MinLatent/configForModeleMinLatent.txt");
            Modele* currentModelM2 = new modeleMinLatent();
            string configFileM3 = string("M5-MinLatentTbet/configForModeleLatentTbet.txt");
            Modele* currentModelM3 = new modeleLatentTbet();
            string configFileM4 = string("M6a-LatentTbet2/BestConfigSoFar.txt"); //configLatentTbet2NonOverlap.txt"); //UnBonSetTotalConfig.txt");                 //configFile = string("GoodCombManualTbetGata3ForLatent2NoIL250pourcents.txt");
            Modele* currentModelM4 = new modeleLatentTbet2();
            st->addModel(currentModelM0->name, currentModelM0, configFileM0);
            st->addModel(currentModelM1->name, currentModelM1, configFileM1);
            st->addModel(currentModelM2->name, currentModelM2, configFileM2);
            st->addModel(currentModelM3->name, currentModelM3, configFileM3);
            st->addModel(currentModelM4->name, currentModelM4, configFileM4);
            st->setDefaultModel(currentModelM4->name);
            st->exec();
            cout << "   -> Leaving GUI\n" << endl;
            cout << " ==================================================================================================== \n" << endl << endl;

            pair<int,float> choice = st->getFinalChoice();
            if(choice.first >= 0){
                if(choice.second < 0) {
                    scriptsWithMainExp(choice.first);
                    cout << "Line Command for this :\n" << argv[0] << " " << choice.first << endl;
                } else {
                    scriptsWithPerturbations(choice.first, choice.second);
                    cout << "Line Command for this :\n" << argv[0] << " " << choice.first << " " << choice.second << endl;
                }
            }
            if(choice.first == -2){
                MultiObjective(-1);
            }*/

            #ifndef WITHOUT_QT
            scriptsWithMainExp(0);
            return b.exec();                // to leave the control to Qt instead of finishing the program
            #endif
            break;}

        case 2: {
            /*if(!string(argv[1]).compare(string("total"))) {TotalAnalysis(); return 0;}
            if(!string(argv[1]).compare(string("20hours"))) {scriptsWith20HoursExp(-1);
                #ifndef WITHOUT_QT
                return b.exec();                // to leave the control to Qt instead of finishing the program
                #endif
            }*/
            scriptsWithMainExp(atoi(argv[1]));
            if(atoi(argv[1]) <= 9){
                #ifndef WITHOUT_QT
                return b.exec();                // to leave the control to Qt instead of finishing the program
                #endif
            }
            break;}
       /* case 3: {
            if(!string(argv[1]).compare(string("multi"))) {MultiObjective(atoi(argv[2])); return 0;}
            scriptsWithPerturbations(atoi(argv[1]), (double) atof(argv[2])); break;}
        case 4: case 6:{
            string chosenConfig;
            string chosenSet;
            if(!string(argv[2]).compare(string("-set"))) chosenSet = string(argv[3]);
            if(!string(argv[2]).compare(string("-config"))) chosenConfig = string(argv[3]);
            if(argc == 6){
                if(!string(argv[4]).compare(string("-set"))) chosenSet = string(argv[5]);
                if(!string(argv[4]).compare(string("-config"))) chosenConfig = string(argv[5]);
            }
            if(chosenSet.find("/")!=string::npos) chosenSet = folder + chosenSet;
            if(chosenConfig.find("/")!=string::npos) chosenConfig = folder + chosenConfig;
            cout << "   => Chosen Options :\n";
            if(chosenSet.size() > 0) cout << "-set=" << chosenSet << endl;
            if(chosenConfig.size() > 0) cout << "-config=" << chosenConfig << endl;
            scriptsWithMainExp(atoi(argv[1]), chosenConfig, chosenSet);
            break;
        }
        case 5: case 7:{
        string chosenConfig;
            string chosenSet;
            if(!string(argv[3]).compare(string("-set"))) chosenSet = string(argv[4]);
            if(!string(argv[3]).compare(string("-config"))) chosenConfig = string(argv[4]);
            if(argc == 7){
                if(!string(argv[5]).compare(string("-set"))) chosenSet = string(argv[6]);
                if(!string(argv[5]).compare(string("-config"))) chosenConfig = string(argv[6]);
            }
            if(chosenSet.find("/")!=string::npos) chosenSet = folder + chosenSet;
            if(chosenConfig.find("/")!=string::npos) chosenConfig = folder + chosenConfig;
            cout << "   => Chosen Options :\n";
            if(chosenSet.size() > 0) cout << "-set=" << chosenSet << endl;
            if(chosenConfig.size() > 0) cout << "-config=" << chosenConfig << endl;
            scriptsWithPerturbations(atoi(argv[1]), (double) atof(argv[2]), string("CmdLineAnalysisPert") + string(argv[1]), string(""), chosenConfig, chosenSet);
            break;
        }*/
    default:{}
    }

    return 0;
}





















/*

enum politicalMethod {ST_ONLYONE, ST_SUM, ST_RANDOM_EQUAL, ST_RANDOM_UNEQUAL, ST_EVOL_WEAK, ST_EVOL_STRONG, ST_OSCILL, ST_MAX, ST_MAX_EVOL, ST_CUSTOM, NBSTRATS};
string politicalName(politicalMethod p);
*/

/* Note : fields inherited from MultiExperiment
    int NbBigExps;
    vector<Experiment*> ListBigExperiments;
        void AddExperiment(Experiment* Ex);
        Experiment* getExperiment(int BigExpID);

    vector<double> coefficients;
    int cptNbSimus;

    // function called by the cost functions, need to be re-implemented, and can change the coefficients whenever.
    virtual void politics(){}
    virtual void postPolitics(){}
*/
/*

struct MultiExpThs : public MultiExperiments {
    vector<int> subExpsToConsider;
    politicalMethod pol;
    bool changePoliticsEveryTime;
    int lastNumber;
    bool testMode;
    vector<double> fakeCostsForTests;

    MultiExpThs(Modele* currentModel);
    void setPolitics(politicalMethod p);
    void considerExp(int BigExpID);
    void politics();
    void postPolitics();
    void testPolitics();
    string print();
};

*/







//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
///
///
///         1 - Scripts for canonical differentiation. Can do all fittings and identifiability/sensitivity
///
///
///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void scriptsWithMainExp(int nb,string newConfigFile, string newParameterSet){

    if(nb < 0){      // displays help
        cout << "\nAvailable scripts :" << endl;
        cout << "A).   Scripts for loading a model, data and launching the graphical interface to play with them. " << endl;
        cout << "      The default parameter set is not particularly good." << endl;
        cout << "" << endl;
        cout << "- 0 :        Graphical interface, Model 1                                         " << endl;
        cout << "- 1 :        Graphical interface, Model 2                                         " << endl;
        cout << "- 2 :        Graphical interface, Model 3                                         " << endl;
        cout << "- 3 :        Graphical interface, Model 4                                         " << endl;
        cout << "- 4 :        Graphical interface, Model 5                                         " << endl;
        cout << "- 5 :        Graphical interface, Model 6                                         " << endl;
        cout << "" << endl;
        cout << "B).   Scripts with fitting" << endl;
        cout << "- 10:  Fitting with modeleLeishmaniaMajor, for all combinations of Model 1" << endl;
        cout << "- 11:  Fitting with modeleLeishmaniaMajor, for all combinations of Model 2" << endl;
        cout << "- 12:  Fitting with modeleLeishmaniaMajor, for all combinations of Model 3" << endl;
        cout << "- 13:  Fitting with modeleLeishmaniaMajor, for all combinations of Model 4" << endl;
        cout << "- 14:  Fitting with modeleLeishmaniaMajor, for all combinations of Model 5" << endl;
        cout << "- 15:  Fitting with modeleLeishmaniaMajor, for all combinations of Model 6" << endl;

       //cout << "- 20:  Fitting with modeleLatentTbet2, different percents around the parameter set" << endl;
        cout << "- 30:  identifiablilty, modeleLeishmaniaMajor, for all combinations separately" << endl;
        cout << "- 31:  identifiablilty, modeleLeishmaniaMajor, for all combinations separately" << endl;
        cout << "- 32:  identifiablilty, modeleLeishmaniaMajor, for all combinations separately" << endl;
        cout << "- 33:  identifiablilty, modeleLeishmaniaMajor, for all combinations separately" << endl;
        cout << "- 34:  identifiablilty, modeleLeishmaniaMajor, for all combinations separately" << endl;
        cout << "- 35:  identifiablilty, modeleLeishmaniaMajor, for all combinations separately" << endl;

        /*cout << "- 40:  identifiablilty, modeleLeishmaniaMajor, 50 percents around the parameter set" << endl;
        cout << "" << endl;
        cout << "C).   Sensitivity" << endl;
        cout << "- 50:  sensitivity, modeleLatentTbet2,     around the parameter set" << endl;*/
        return;
    }

    cout << " -> Launching scriptsWithMainExp(" << nb << ")" << endl;
    if(newConfigFile.size() > 0)   cout << "      forcing configuration : " << newConfigFile << endl;
    if(newParameterSet.size() > 0) cout << "      forcing parameter set : " << newParameterSet << endl;

    // ======= Loading data for canonical differentiations into TableCourses and overriders ========

    /*TableCourse* lm   = new TableCourse(folder + string("DATA/lm.txt"));
    vector<TableCourse*> kinetics = {lm};   // note : this syntax requires -std=c++11 in the compiler options
    int nbDataSets = kinetics.size();

    bool useSplines = false;                // false = linear interpolation, true = cubic splines
    overrider* Overlm = new overrider();    // Note : never create overrider as a non pointer, to be used by the graphical interface because they will be erased when function closes and gives control to the interface --> use a pointer and new ...
    vector<overrider*> overs = {Overlm};    // saves the overriders and kinetics in a vector so it is easy to get them in a loop by kinetics[i]...
    //*/


//    TableCourse* Data_all = new TableCourse(folder + string("DATA/AllMillionsNew.txt"));
    TableCourse* Data_all = new TableCourse(folder + string("DATA/AllMillionsNoRecircul.txt")); // DiscardGFPNeg
    TableCourse* Data_Potritt = new TableCourse(folder + string("DATA/DNsPotritt.txt"));

    //TableCourse* Data_pc = new TableCourse(folder + string("DATA/Percents.txt"));
    //vector<TableCourse*> kinetics = {Data_abs, Data_pc};   // note : this syntax requires -std=c++11 in the compiler options
    //int nbDataSets = kinetics.size();

    //TableCourse* DataStd_new = new TableCourse(folder + string("DATA/DataStd_new.txt"));
    //vector<TableCourse*> kineticsStd = {DataStd_new};   // note : this syntax requires -std=c++11 in the compiler options
    //int nbDataSets = kineticsStd.size();

/*
    bool useSplines = false;                // false = linear interpolation, true = cubic splines
    overrider* OverData_new = new overrider();    // Note : never create overrider as a non pointer, to be used by the graphical interface because they will be erased when function closes and gives control to the interface --> use a pointer and new ...
    vector<overrider*> overs = {OverData_new};    // saves the overriders and kinetics in a vector so it is easy to get them in a loop by kinetics[i]...


    // ======= Reading the data and interpolating curves into the overriders =====================

    vector<string> GlobalNamesVariables = getGlobalNames();                             // vector saying how to read the names of variables in the kinetics files (v[N::IL2] = 'gIL2', ...)
    for(int ne = 0; ne < nbDataSets; ++ne){                                             //  converts the name of variables (ex : 'gIL2') into their global index (ex: N::IL2)
        for(int i = 0; i < kinetics[ne]->nbVar; ++i){
            string ss = kinetics[ne]->headers[i+1];     // header of this variable

            // converting 'name in kinetics file ("gIL2", ...) --> index of variable (index = N::IL2 in the enum)' ======
            int GlobName = -1;
            for(int j = 0; j < (int) GlobalNamesVariables.size(); ++j){
                if(!GlobalNamesVariables[j].compare(ss)) GlobName = j;
            }

            // giving the data to overriders for interpolation (splines or linear) ======
            if(GlobName > -1){
                overs[ne]->learnSpl(GlobName,kinetics[ne]->getTimePoints(i), kinetics[ne]->getTimeCourse(i), useSplines);
            } else cout << "Variable " << ss << " not found in the kinetics\n";
        }
    }
      //overrider* OverData_new;
     //OverData_new->setOver(0, true);
    //cerr << "Heeee";
    //cerr << OverData_new->print();
    //return;

    */

   // ======= Creating the model depending on the options ========

    string configFile = string("configLMajor.txt");
    if(newConfigFile.length() > 0) configFile = newConfigFile;

    Modele* currentModel = NULL;
    switch(nb){
        //case 0: case 10: { currentModel = new modele1ThymusOnly();
        //case 0: case 10: { currentModel = new modele1ThymusSpleen();
        //configFile=string("Model1ThymusOnly/BestConfigModel1.txt");
        case 0: case 10: {
            currentModel = new modele0ManessoOnly();
            configFile=string("Model0ManessoOnly/BasicConfManesso.txt");
            break; }
        case 1: case 11: {
            currentModel = new ModeleTVaslin2007();
            break; }
        case 2: case 12: { currentModel = new modele3MultiDiv();
            #ifdef ReducedParams
            configFile = string("Model3TSManesso/BasicConfMultiDivMoreVar.txt");
            #else
            configFile = string("Model3TSManesso/BasicConfMultiDiv.txt");
            #endif
            break;}
        }
    // just printing
    cout << "   -> Using model : " << currentModel->name << " for canonical differentiation\n   -> performing script nr(" << nb << ")\n";
    if(newConfigFile.length() > 0)   cout << "      ... with configuration (" << newConfigFile << ")" << endl;
    if(newParameterSet.length() > 0) cout << "      ... with parameter set (" << newParameterSet << ")" << endl;

    //expThymus* currentExperiment = new expThymus(currentModel);
    //expCombinedHyp* currentExperiment = new expCombinedHyp(currentModel);


    expDNPotritt* currentExperiment = new expDNPotritt(currentModel);
    //expThymus* currentExperiment = new expThymus(currentModel);
    //expCombinedHypLog* currentExperiment = new expCombinedHypLog(currentModel);
    currentExperiment->giveData(Data_all, 0);

    // ERR: can not give two experiments ???
    //currentExperiment->giveData(Data_Potritt, 1);

    // ======= Giving data to the evaluators of the experiment class (for getting a cost later & knowing what to record) ========


    //currentExperiment->giveData(Data_all, Infection); // apparently, should be done only once

    //currentExperiment->giveData(Data_all, ReducedInflow);
    //currentExperiment->giveData(Data_all, MoreDeath);

    //currentExperiment->giveData(Data_all, MoreOutputThymus);

    //currentExperiment->giveData(Data_all, FasterDifferentiation);

    //currentExperiment->giveData(Data_all, SpaceDependentOutput);



    //currentExperiment->giveStdDevs(DataStd_new, Small_Dose);
    vector<string> GlobalNamesVariables = getGlobalNames();
    currentExperiment->giveHowToReadNamesInKinetics(GlobalNamesVariables); // very important to do it... segfault if not
    currentExperiment->loadEvaluators();


    // ======= and giving the overriders to the experiment class to replace wanted curves by data ========

    //currentExperiment->setOverrider(Small_Dose, OverData_new);


    // =============== Scripts 0, 1, 2, 3 & 4 : no optimization, only launches the GUI ================

    if(nb < 10 ){
        #ifndef WITHOUT_QT
        simuWin* p = new simuWin(currentExperiment);
        cout << "Launching Graphical Interface ..." << endl;
        p->loadConfig(folder + configFile);
        if(newParameterSet.length() > 0) currentModel->loadParameters(newParameterSet);
        p->show();
        #else
        cout << "Script finished (without qt, because WITHOUT_QT was defined)\n";
        #endif
        return;
    }




    /*

    // =============== Create folder for scripts requiring optimization or more ================

    string folderRes = folderBaseResults + string("script") + codeTime() + string("/");           // Define working directory (name = "sim" + date)
    createFolder(folderRes);


    // =============== Optimization options ... ================


    stringstream headerOptimizer;                                                   // each further script might use different optimizer options, will be stored in the following stringstream
    if(TESTINGMODE) headerOptimizer << optFileHeader(GeneticFast);
    else headerOptimizer << optFileHeader(Genetic50k);


    cerr << configFile << endl;
    // ========== Main Scripts !! (It uses the class manageSims to perform simulations / optimizations, without the graphical interface) ===========

    switch(nb){ // fitting
    case 10: case 11: case 12: case 13: case 14: case 15:  {

        manageSims* msi = new manageSims(currentExperiment);        // manageSims is the class to perform optimizations/other things without graphical interface. simuWin is the extension with graphical interface.
        msi->loadConfig(folder + configFile);                       // Now, loads a list of configurations (parameters + variables) to optimize, and optimizes them one by one
        //cerr << "test" << endl;
        vector<string> listGeneratedFilesSets;                      // will store the files with parameter sets that to re-load them later




        // ----------------- Part 1 : for each combination (parameters-variables), do a fitting -----------------------

        for(int i = 0; i < msi->nbCombs; ++i){
            cerr << "Optimize combination" << i << endl;
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

            // Optimize (using the data stated by this combination) !
            msi->motherOverrideUsingComb(i);                                                    // chose the variables to simulate and to replace by data according to this combination
            msi->motherOptimize(folderComb.str() + string("Optimizer.txt"), 1000);              // DOES THE OPTIMIZATION !!!, and records the 1000 best sets

            // saves the best sets of parameters
            msi->saveHistory(folderComb.str() + string("History.txt"));                         // SAVES all the best parameter sets. by default, 10 000, can be modified by             msi->history.resize(max_nb_sets_to_record);
            listGeneratedFilesSets.push_back(folderComb.str() + string("History.txt"));         // list[i] = historyFile for comb i

            // if QT allowed, generates the plots for this best set
            #ifndef WITHOUT_QT
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












*/
/*

        // ----------------- Part 2 : take the best parameters obtained for each combination into a single (combined) parameter set -----------------------

        vector< vector<double> > parametersPerComb;
        msi->resetParamSetFromConfig(folder + configFile);                     // starting from the initial parameter set again
        for(int i = 0; i < msi->nbCombs; ++i){
            msi->loadHistory(listGeneratedFilesSets[i]);
            parametersPerComb.push_back(msi->history.getSetNumber(0)->v);      // to record the parameters fitted by each combinations, because two combinations might want to optimize the same parameters ..., note that when two combinations optimize the same parameter, the last combination will erase the previous one ...
            msi->useParamSetFromHistory(0, i);                                 // takes the best, copying only parameters optimized by this combination, and keeping the other ones
        }
        vector<double> best = currentModel->getParameters();

        // saves the best set of parameters for each combination, syntax : NB_parameters\tNB_combinations\nIDComb0\tParam1Comb0\tParam2Comb0\t... (1 combination = 1 line)
        ofstream fsum(folderRes + string("ParameterSetsPerCombination.txt"), ios::out);
        if(fsum){
            fsum << parametersPerComb.size() << "\t" << msi->nbCombs << "\n";
            for(int i = 0; i < (int) parametersPerComb.size(); ++i){
                fsum << i;
                for(int j = 0; j < (int) parametersPerComb[i].size(); ++j){
                    fsum << "\t" << parametersPerComb[i][j];}
                fsum << "\n";}
            fsum.close();
        }

        // saves the combined best set in a file, syntax : NB_parameters\nParam1\tparam2\tParam3 ...
        cout << "   -> Best (combined) parameter set :";
        int NP = best.size();
        ofstream fbest(folderRes + string("ReconstitutedBestSet.txt"), ios::out);
        if(fbest) fbest << NP << endl;
        for(int i = 0; i < NP; ++i){
            if(fbest) fbest << best[i] << "\t";     cout << "\t" << best[i];}
        if(fbest) fbest.close();                    cout << endl;

        // if qt allowed, generates the plots for this set
        cout << "Fig ..." << endl;
        #ifndef WITHOUT_QT
        createFolder(folderRes + string("BestCombinedSet"));
        simuWin tempWindow2(currentExperiment);
        tempWindow2.motherOverrideUsingComb(-1);    // to allow simulation of all variables free in all combinations
        tempWindow2.simulate();
        tempWindow2.makeFigReportParamSet(folderRes + string("BestCombinedSet/"));
        ofstream f2((folderRes + string("BestCombinedSet/") + string("FitnessBestCombinedSet.txt")).c_str(), ios::out); if(f2) {f2 << currentExperiment->costReport() << "\n"; f2.close();}
        #else
        msi->motherOverrideUsingComb(-1);
        msi.simulate();
        ofstream f2((folderRes + string("BestCombinedSet/") + string("FitnessBestSetOf") + codeSimu.str() + string(".txt")).c_str(), ios::out); if(f2) {f2 << currentExperiment->costReport() << "\n"; f2.close();}
        #endif

        cout << "   -> Script " << nb << " finished ! --> Script " << nb + 10 << " starting ...\n   _____________________________________________________________\n";
        cout << "\n\n\n\n\n\n";
        nb += 10;
    }*/



    /*
    }   // end switch









*/
/*


    // ----------------- Part 3 : does a global fitting around the parameter set, simulating all the variables -----------------------

    switch(nb){     // need to redo a switch here because wants the scripts 1x to be followed by 2x
    case 20: case 21: case 22: case 23: case 24: {

        manageSims* msi = new manageSims(currentExperiment);        // manageSims is the class to perform optimizations/other things without graphical interface. simuWin is the extension with graphical interface.
        msi->loadConfig(folder + configFile);                       // Now, loads a list of configurations (parameters + variables) to optimize, and optimizes them one by one
        vector<string> listGeneratedFilesSets;                      // will store the files with parameter sets that to re-load them later

        // 'around' the parameter set, means allowing the parameters to vary +/- a certain percent of the value of the parameter set. Will optimize with different percents :
        vector<double> best = currentModel->getParameters();
        vector<double> percents = {90.0, 50.0, 25.0, 10.0, 5.0, 2.0, 1.0};

        for(int k = 0; k < (int) percents.size(); ++k){

            stringstream codeSimu; codeSimu << "Percents(" << percents[k] << ")-" << codeTime();             // generates a text code for this particular optimization, in case parallel optimizations are running
            stringstream folderComb; folderComb << folderRes << codeSimu.str() << "/";                           // creates a folder for this particular optimization, to create figures etc ...
            createFolder(folderComb.str());
            cout << "   -> Optimizing " << percents[k] << " % around the best parameter set, with ID: " << codeSimu.str() << "\n";

            // set the boundaries for each parameter to best set +/- percent around. Note that here, should not start from the parameter set in the configuration, but rather the best one
            int NP = currentModel->getNbParams();
            currentModel->setParameters(best);
            for(int i = 0; i < NP; ++i){
                if(std::isnan(best[i]) || std::isinf(best[i])) best[i] = 1e12;
                double newLow  = best[i] * (1.0 - (percents[k] / 100.0));
                double newHigh = best[i] * (1.0 + (percents[k] / 100.0));
                //if(newLow > currentModel->getUpperBound(i)) newLow = currentModel->getLowerBound(i);
                //if(newHigh < currentModel->getLowerBound(i)) newHigh = currentModel->getUpperBound(i);
                //currentModel->setBounds(i, max(currentModel->getLowerBound(i), newLow) , min(currentModel->getUpperBound(i), newHigh));
                currentModel->setBounds(i, newLow ,newHigh);
            }
            msi->updateConfigParamsFromModel();

            // set options of simulation : dt initial = 10 sec, and no recording of regular kinetics (just recording of evaluators). Need to be done each time because simuWin->makeReports, etc will change the dt and will generate kinetics with its own dt in order to make plots
            currentExperiment->m->setPrintMode(false, 5000);
            currentExperiment->m->dt = 10;

            // creates the optimizer file for the combination of parameters to optimize, using boundaries from the configuration file, and the header from headeroptimizer
            string optOptions = msi->motherCreateOptimizerFile(-1, headerOptimizer.str());      // for each combination, will need to re-create an optimizer file. Note : this function uses the boundaries in the configuration, not from the model ...
            ofstream f1((folderComb.str() + string("Optimizer.txt")).c_str(), ios::out); if(f1) {f1 << optOptions << "\n"; f1.close();}

            // Optimize (all the parameters from all the configurations) !
            msi->motherOverrideUsingComb(-1);                                                   // chose the variables to simulate and to replace by data according to this combination
            msi->motherOptimize(folderComb.str() + string("Optimizer.txt"), 1000);              // DOES THE OPTIMIZATION !!!, and records the 1000 best sets

            // saves the best sets of parameters
            msi->saveHistory(folderComb.str() + string("History.txt"));                         // SAVES all the best parameter sets. by default, 10 000, can be modified by             msi->history.resize(max_nb_sets_to_record);
            listGeneratedFilesSets.push_back(folderComb.str() + string("History.txt"));         // list[i] = historyFile for comb i

            // if QT allowed, generates the plots for this set
            #ifndef WITHOUT_QT
            simuWin tempWindow2(currentExperiment);   // funny, if in non pointer with simuWin tw = simuWin(currentExperiment), get a compiling error 'use of deleted function' ...
            tempWindow2.loadHistory(QString((folderComb.str() + string("History.txt")).c_str()));
            tempWindow2.useParamSetFromHistory(0);                                                     // takes the first set of parameters (the best), also possible to use msi->useParamSetFromHistory(0, i); for overriding only parameters from this combination,
            tempWindow2.simulate();
            tempWindow2.makeFigReportParamSet(folderComb.str());
            ofstream f2((folderComb.str() + string("FitnessBestSetOf") + codeSimu.str() + string(".txt")).c_str(), ios::out); if(f2) {f2 << currentExperiment->costReport() << "\n"; f2.close();}
            ofstream f3((folderComb.str() + string("CostEvolutionDuringOptimization") + codeSimu.str() + string(".txt")).c_str(), ios::out); if(f3) {f3 << tempWindow2.costRecords.print() << "\n"; f3.close();}
            #else
            // selects the best set of parameters, runs a simulation and saves simulation versus data
            msi->useParamSetFromHistory(0);                                                     // takes the first set of parameters (the best), also possible to use msi->useParamSetFromHistory(0, i); for overriding only parameters from this combination,
            msi->simulate();
            ofstream f2((folderComb.str() + string("FitnessBestSetOf") + codeSimu.str() + string(".txt")).c_str(), ios::out); if(f2) {f2 << currentExperiment->costReport() << "\n"; f2.close();}
            ofstream f3((folderComb.str() + string("CostEvolutionDuringOptimization.txt") + codeSimu.str()).c_str(), ios::out); if(f3) {f3 << msi->costRecords.print() << "\n"; f3.close();}
            #endif

        }
        break;
    }



*/


    /*



    // ----------------- Part 4 : Identifiability -----------------------

    case 30: case 31: case 32: case 33: case 34: case 35:{

        manageSims* msi = new manageSims(currentExperiment);        // manageSims is the class to perform optimizations/other things without graphical interface. simuWin is the extension with graphical interface.
        msi->loadConfig(folder + configFile);                       // Now, loads a list of configurations (parameters + variables) to optimize, and optimizes them one by one
        //vector<string> listGeneratedFilesSets;                      // will store the files with parameter sets that to re-load them later




        // ----------------- Part 1 : for each combination (parameters-variables), do a fitting -----------------------

        for(int i = 0; i < msi->nbCombs; ++i){

            stringstream codeSimu;      codeSimu << "IdentCombNr" << i << "-" << codeTime();               // generates a text code for this particular optimization, in case parallel optimizations are running
            stringstream folderComb;    folderComb << folderRes << codeSimu.str() << "/";                        // creates a folder for this particular optimization, to create figures etc ...
            createFolder(folderComb.str());

            cout << "Identifiability for combination (" << i << ") with ID: " << codeSimu.str() << "\n";

            // re-takes the initial parameter set because parameters were probably changed by previous optimization for parameters that will not necessarily be optimized/modified in the next combinations
            msi->resetParamSetFromConfig(folder + configFile);
            vector<double> initialSet = currentModel->getParameters();

            // set options of simulation : dt initial = 10 sec, and no recording of regular kinetics (just recording of evaluators). Need to be done each time because simuWin->makeReports, etc will change the dt and will generate kinetics with its own dt in order to make plots
            currentExperiment->m->setPrintMode(false, 5000);
            //currentExperiment->m->dt = 0.002;

            msi->motherOverrideUsingComb(i);
            vector<int> paramsInConfig = msi->parametersInConfig(i);
            for(int j = 0; j < (int) paramsInConfig.size(); ++j){
                int p = paramsInConfig[j];

                msi->prepareOptFilesForIdentifibiality(folderRes, p, i, headerOptimizer.str());
                msi->motherIdentifiability(initialSet, p);  // the parameters will be applied inside this function

                oneParameterAnalysis* opa = msi->identifiabilities[p];
                string res = opa->print();
                stringstream fname; fname << folderComb.str() << "resIdentifiabilityForParam" << p << ".txt";
                fstream fp(fname.str(), ios::out); if(fp) {fp << res; fp.close();}
                msi->makeIdentifibialityReport(p, folderComb.str(), i);
                cout << "      ... Details saved in " << fname.str() << endl;
                */
                /*
                // saves the best sets of parameters
                msi->saveHistory(folderComb.str() + string("History.txt"));                         // SAVES all the best parameter sets. by default, 10 000, can be modified by             msi->history.resize(max_nb_sets_to_record);
                listGeneratedFilesSets.push_back(folderComb.str() + string("History.txt"));         // list[i] = historyFile for comb i

                // if QT allowed, generates the plots for this best set
                #ifndef WITHOUT_QT
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
            */

    /*
            }
        }
        break;
    }

    } // end switch

    */

    cout << "   -> Script " << nb << " finished !\n   _____________________________________________________________\n";
}



















/*



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
///
///
///         2 - Scripts to simulate all the other experiments, with data to compare no fitting here (only manual)
///
///
///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



// Note : if exportName is not "", then do not use the graphical interface
// returns the name of the created folder
string scriptsWithPerturbations(int nb, double parameter, string analysisName, string outputFolder, string chosenConfig, string chosenSet){
    if(outputFolder.empty()) outputFolder = folderBaseResults;
    replace( analysisName.begin(), analysisName.end(), '_', '-');
    if(nb < 0){
        cout << "Scripts with perturbations (with parameter p) :" << endl;
        cout << "" << endl;
        cout << "- 0 :         No perturbation, normal differentiations   " << endl;
        cout << "- 18 :         -- same -- (but data from J4)   " << endl;
        cout << "- 19 :         -- same -- (with blocking antibodies combinations)   " << endl;
        cout << "" << endl;
        cout << "A).   Changing differentiation condition in the middle (default p = 20 hrs) : " << endl;
        cout << "- 1 :         From Th1,   change to other ones at t = p hrs   " << endl;
        cout << "- 2 :         From Th2,   change to other ones at t = p hrs   " << endl;
        cout << "- 3 :         From iTreg, change to other ones at t = p hrs   " << endl;
        cout << "- 4 :         From Th17,  change to other ones at t = p hrs   " << endl;
        cout << "- 5 :         From Th0,   change to other ones at t = p hrs   " << endl;
        cout << "- 6 :         To Th1,   change to other ones at t = p hrs   " << endl;
        cout << "- 7 :         To Th2,   change to other ones at t = p hrs   " << endl;
        cout << "- 8 :         To iTreg, change to other ones at t = p hrs   " << endl;
        cout << "- 9 :         To Th17,  change to other ones at t = p hrs   " << endl;
        cout << "- 10 :        To Th0,   change to other ones at t = p hrs   " << endl;
        cout << "" << endl;
        cout << "B).   Titrations of cell density in the well : " << endl;
        cout << "- 11 :        Th1   diff, Different Densities of cells               " << endl;
        cout << "- 12 :        Th2   diff, Different Densities of cells               " << endl;
        cout << "- 13 :        iTreg diff, Different Densities of cells               " << endl;
        cout << "- 14 :        Th17  diff, Different Densities of cells               " << endl;
        cout << "- 15 :        Th10  diff, Different Densities of cells               " << endl;
        cout << "" << endl;
        cout << "C).   Titrations of cytokines : " << endl;
        cout << "- 20 :        Th1,  Doses of IL2                         " << endl;
        cout << "- 21 :        Th1,  Doses of IL4                         " << endl;
        cout << "- 22 :        Th1,  Doses of IL6                         " << endl;
        cout << "- 23 :        Th1,  Doses of IL12                        " << endl;
        cout << "- 24 :        Th1,  Doses of IL17                        " << endl;
        cout << "- 25 :        Th1,  Doses of IL21                        " << endl;
        cout << "- 26 :        Th1,  Doses of IFNG                        " << endl;
        cout << "" << endl;
        cout << "- 30 :        Th2,  Doses of IL2                         " << endl;
        cout << "- 31 :        Th2,  Doses of IL4                         " << endl;
        cout << "- 32 :        Th2,  Doses of IL6                         " << endl;
        cout << "- 33 :        Th2,  Doses of IL12                        " << endl;
        cout << "- 34 :        Th2,  Doses of IL17                        " << endl;
        cout << "- 35 :        Th2,  Doses of IL21                        " << endl;
        cout << "- 36 :        Th2,  Doses of IFNG                        " << endl;
        cout << "" << endl;
        cout << "- 40 :        iTreg,  Doses of IL2                         " << endl;
        cout << "- 41 :        iTreg,  Doses of IL4                         " << endl;
        cout << "- 42 :        iTreg,  Doses of IL6                         " << endl;
        cout << "- 43 :        iTreg,  Doses of IL12                        " << endl;
        cout << "- 44 :        iTreg,  Doses of IL17                        " << endl;
        cout << "- 45 :        iTreg,  Doses of IL21                        " << endl;
        cout << "- 46 :        iTreg,  Doses of IFNG                        " << endl;
        cout << "" << endl;
        cout << "- 50 :        Th17,  Doses of IL2                         " << endl;
        cout << "- 51 :        Th17,  Doses of IL4                         " << endl;
        cout << "- 52 :        Th17,  Doses of IL6                         " << endl;
        cout << "- 53 :        Th17,  Doses of IL12                        " << endl;
        cout << "- 54 :        Th17,  Doses of IL17                        " << endl;
        cout << "- 55 :        Th17,  Doses of IL21                        " << endl;
        cout << "- 56 :        Th17,  Doses of IFNG                        " << endl;
        cout << "" << endl;
        cout << "- 60 :        Th0,  Doses of IL2                         " << endl;
        cout << "- 61 :        Th0,  Doses of IL4                         " << endl;
        cout << "- 62 :        Th0,  Doses of IL6                         " << endl;
        cout << "- 63 :        Th0,  Doses of IL12                        " << endl;
        cout << "- 64 :        Th0,  Doses of IL17                        " << endl;
        cout << "- 65 :        Th0,  Doses of IL21                        " << endl;
        cout << "- 66 :        Th0,  Doses of IFNG                        " << endl;
        cout << "" << endl;
        cout << "D).   Sensitivity to parameters : " << endl;
        cout << "- 70 :        Th1,  Variations of the given parameter    " << endl;
        cout << "- 71 :        Th2,  Variations of the given parameter    " << endl;
        cout << "- 72 :        iTreg,Variations of the given parameter    " << endl;
        cout << "- 73 :        Th17, Variations of the given parameter    " << endl;
        cout << "- 74 :        Th0,  Variations of the given parameter    " << endl;
        cout << "- 75 :        Th1,  Scanning the given parameter         " << endl;
        cout << "- 76 :        Th2,  Scanning the given parameter         " << endl;
        cout << "- 77 :        iTreg,Scanning the given parameter         " << endl;
        cout << "- 78 :        Th17, Scanning the given parameter         " << endl;
        cout << "- 79 :        Th0,  Scanning the given parameter         " << endl;
        cout << "" << endl;
        cout << "E).   Stopping translation (cycloheximidine): " << endl;
        cout << "- 80 :        All conditions, treatment with cycloheximidine at the given time   " << endl;
        cout << "" << endl;
        cout << "F).   Simulations under a deficient background: " << endl;
        cout << "- 90 :        All conditions for a single background of given index (0=WT, 1, ...)   " << endl;
        cout << "\n";
        cout << "- 100 :       Perform all with various parameters and saves all simulations       " << endl;
        return string("No Choice Given (help mode)");
    }
    cout << "\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    cout << "launching Perturbation script nr " << nb << " with parameter " << parameter << endl;


    if((nb == 100) && (analysisName.size() > 0)) cerr << "ERR : scriptWithPerturbations, you can not do all the scripts (nr 100), and give a name. " << endl;

    for(int i = (nb == 100 ? 0 : nb); i < (nb == 100 ? 66 : nb+1); ++i){
// ======= Define working directory (name = "sim" + date) FolderRes will be created if required ========

string folderRes = outputFolder + analysisName + string("simPert") + codeTime() + string("/");


// ======= Creating the model depending on the options ========

    string configFile;
    Modele* currentModel = new modeleLatentTbet2();
    Experiment* currentExperiment = NULL;
    configFile = folder + string("BestConfigSoFar.txt");
    if(chosenConfig.size() > 0) configFile = chosenConfig;
    //configFile = string("C:/Users/Philippe/Desktop/Work/2015/Sim2 (2015-11-17) for LyonSysBio/UnBonSetTotalConfig.txt");
    switch(nb){
        case 0: { currentExperiment = new expThs        (currentModel);                                  break;}
        case 1: { currentExperiment = new expFromTh1    (currentModel, parameter < 0 ? 20 : parameter);  break;}
        case 2: { currentExperiment = new expFromTh2    (currentModel, parameter < 0 ? 20 : parameter);  break;}
        case 3: { currentExperiment = new expFromTreg   (currentModel, parameter < 0 ? 20 : parameter);  break;}
        case 4: { currentExperiment = new expFromTh17   (currentModel, parameter < 0 ? 20 : parameter);  break;}
        case 5: { currentExperiment = new expFromTh0    (currentModel, parameter < 0 ? 20 : parameter);  break;}
        case 6: { currentExperiment = new expToTh1    (currentModel, parameter < 0 ? 20 : parameter);  break;}
        case 7: { currentExperiment = new expToTh2    (currentModel, parameter < 0 ? 20 : parameter);  break;}
        case 8: { currentExperiment = new expToTreg   (currentModel, parameter < 0 ? 20 : parameter);  break;}
        case 9: { currentExperiment = new expToTh17   (currentModel, parameter < 0 ? 20 : parameter);  break;}
        case 10: { currentExperiment = new expToTh0    (currentModel, parameter < 0 ? 20 : parameter);  break;}
        case 18: { currentExperiment = new expThs        (currentModel);                                  break;}
        case 19: { currentExperiment = new expCanoExtended(currentModel);                                 break;}
        case 11: { currentExperiment = new expDensityTh1(currentModel);                                  break;}
        case 12: { currentExperiment = new expDensityTh2(currentModel);                                  break;}
        case 13: { currentExperiment = new expDensityTreg(currentModel);                                 break;}
        case 14: { currentExperiment = new expDensityTh17(currentModel);                                 break;}
        case 15: { currentExperiment = new expDensityTh0(currentModel);                                  break;}

        case 20: { currentExperiment = new expDosesTH1(currentModel, N::IL2);  break;}
        case 21: { currentExperiment = new expDosesTH1(currentModel, N::IL4);  break;}
        case 22: { currentExperiment = new expDosesTH1(currentModel, N::IL6);  break;}
        case 23: { currentExperiment = new expDosesTH1(currentModel, N::IL12); break;}
        case 24: { currentExperiment = new expDosesTH1(currentModel, N::IL17); break;}
        case 25: { currentExperiment = new expDosesTH1(currentModel, N::IL21); break;}
        case 26: { currentExperiment = new expDosesTH1(currentModel, N::IFNG); break;}

        case 30: { currentExperiment = new expDosesTH2(currentModel, N::IL2);  break;}
        case 31: { currentExperiment = new expDosesTH2(currentModel, N::IL4);  break;}
        case 32: { currentExperiment = new expDosesTH2(currentModel, N::IL6);  break;}
        case 33: { currentExperiment = new expDosesTH2(currentModel, N::IL12); break;}
        case 34: { currentExperiment = new expDosesTH2(currentModel, N::IL17); break;}
        case 35: { currentExperiment = new expDosesTH2(currentModel, N::IL21); break;}
        case 36: { currentExperiment = new expDosesTH2(currentModel, N::IFNG); break;}

        case 40: { currentExperiment = new expDosesTreg(currentModel, N::IL2);  break;}
        case 41: { currentExperiment = new expDosesTreg(currentModel, N::IL4);  break;}
        case 42: { currentExperiment = new expDosesTreg(currentModel, N::IL6);  break;}
        case 43: { currentExperiment = new expDosesTreg(currentModel, N::IL12); break;}
        case 44: { currentExperiment = new expDosesTreg(currentModel, N::IL17); break;}
        case 45: { currentExperiment = new expDosesTreg(currentModel, N::IL21); break;}
        case 46: { currentExperiment = new expDosesTreg(currentModel, N::IFNG); break;}

        case 50: { currentExperiment = new expDosesTH17(currentModel, N::IL2);  break;}
        case 51: { currentExperiment = new expDosesTH17(currentModel, N::IL4);  break;}
        case 52: { currentExperiment = new expDosesTH17(currentModel, N::IL6);  break;}
        case 53: { currentExperiment = new expDosesTH17(currentModel, N::IL12); break;}
        case 54: { currentExperiment = new expDosesTH17(currentModel, N::IL17); break;}
        case 55: { currentExperiment = new expDosesTH17(currentModel, N::IL21); break;}
        case 56: { currentExperiment = new expDosesTH17(currentModel, N::IFNG); break;}

        case 60: { currentExperiment = new expDosesTH0(currentModel, N::IL2);  break;}
        case 61: { currentExperiment = new expDosesTH0(currentModel, N::IL4);  break;}
        case 62: { currentExperiment = new expDosesTH0(currentModel, N::IL6);  break;}
        case 63: { currentExperiment = new expDosesTH0(currentModel, N::IL12); break;}
        case 64: { currentExperiment = new expDosesTH0(currentModel, N::IL17); break;}
        case 65: { currentExperiment = new expDosesTH0(currentModel, N::IL21); break;}
        case 66: { currentExperiment = new expDosesTH0(currentModel, N::IFNG); break;}

        case 70: { currentExperiment = new expParametersTh1  (currentModel, (int) parameter, true); break;}
        case 71: { currentExperiment = new expParametersTh2  (currentModel, (int) parameter, true); break;}
        case 72: { currentExperiment = new expParametersiTreg(currentModel, (int) parameter, true); break;}
        case 73: { currentExperiment = new expParametersTh17 (currentModel, (int) parameter, true); break;}
        case 74: { currentExperiment = new expParametersTh0  (currentModel, (int) parameter, true); break;}
        case 75: { currentExperiment = new expParametersTh1  (currentModel, (int) parameter, false); break;}
        case 76: { currentExperiment = new expParametersTh2  (currentModel, (int) parameter, false); break;}
        case 77: { currentExperiment = new expParametersiTreg(currentModel, (int) parameter, false); break;}
        case 78: { currentExperiment = new expParametersTh17 (currentModel, (int) parameter, false); break;}
        case 79: { currentExperiment = new expParametersTh0  (currentModel, (int) parameter, false); break;}

        case 80: { currentExperiment = new expCycloheximidine(currentModel, parameter); break;}

        case 90: { currentExperiment = new expDeficientAllCond(currentModel, getBackgroundNr((int) parameter)); break;}


        default: {cerr << "ERR: script nr " << nb << " is not defined\n"; return string("Undefined Script");}
    }

    vector<string> GlobalNamesVariables = getGlobalNames();
    //currentExperiment->giveHowToReadNamesInKinetics(GlobalNamesVariables);
    //Nooo currentExperiment->loadEvaluators();
    if(chosenSet.size() > 0) currentModel->loadParameters(chosenSet);

    switch(nb){
        case 0: case 19: case 18: { //currentExperiment = new expThs        (currentModel);
            // ======= Loading data into kinetics (TableCourse) and overriders ========
            TableCourse* TTh1   = new TableCourse(folder + string("DATA/KinTh1-J5.txt"));
            TableCourse* TTh2   = new TableCourse(folder + string("DATA/KinTh2-J5.txt"));
            TableCourse* TiTreg = new TableCourse(folder + string("DATA/KinTreg-J5.txt"));
            TableCourse* TTh17  = new TableCourse(folder + string("DATA/KinTh17-J5.txt"));
            TableCourse* TTh0   = new TableCourse(folder + string("DATA/KinTh0-J5.txt"));
            if(nb == 18){
                TTh1   = new TableCourse(folder + string("DATA/KinTh1-J4.txt"));
                TTh2   = new TableCourse(folder + string("DATA/KinTh2-J4.txt"));
                TiTreg = new TableCourse(folder + string("DATA/KinTreg-J4.txt"));
                TTh17  = new TableCourse(folder + string("DATA/KinTh17-J4.txt"));
                TTh0   = new TableCourse(folder + string("DATA/KinTh0-J4.txt"));
            }
            // ======= Giving data to the evaluators (for getting a cost & knowing what to record) ========
            currentExperiment->giveData(TTh1, TH1);
            currentExperiment->giveData(TTh2, TH2);
            currentExperiment->giveData(TiTreg, TREG);
            currentExperiment->giveData(TTh17, TH17);
            currentExperiment->giveData(TTh0, TH0);
            currentExperiment->giveHowToReadNamesInKinetics(GlobalNamesVariables);
            currentExperiment->loadEvaluators();

            // ======= Now, preparing the data for Overriders :
            int nbDataSets = 5;
            vector<TableCourse*> kinetics;
            kinetics.push_back(TTh1);
            kinetics.push_back(TTh2);
            kinetics.push_back(TiTreg);
            kinetics.push_back(TTh17);
            kinetics.push_back(TTh0);
            bool useSplines = false;                        // false = linear interpolation, true = cubic splines
            overrider* OverTh1 = new overrider();           // DO NOT CREATE overrider (not pointer) because they will be erased when function closes and gives control to the GUI ...
            overrider* OverTh2 = new overrider();
            overrider* OveriTreg = new overrider();
            overrider* OverTh17 = new overrider();
            overrider* OverTh0 = new overrider();
            vector<overrider*> overs;                       // saves the overriders and kinetics in a vector so it is easy to get them in a loop by kinetics[i] ...
            overs.push_back(OverTh1);
            overs.push_back(OverTh2);
            overs.push_back(OveriTreg);
            overs.push_back(OverTh17);
            overs.push_back(OverTh0);

            // vector saying how to read the names of variables in the kinetics files (v[N::IL2] = 'gIL2', ...)
            for(int ne = 0; ne < nbDataSets; ++ne){
                for(int i = 0; i < kinetics[ne]->nbVar; ++i){
                    string ss = kinetics[ne]->headers[i+1];
                    // ======= converting 'name in kinetics file ("gIL2", ...) --> index of variable (index = N::IL2 in the enum)' ======
                    int GlobName = -1;
                    for(int j = 0; j < (int) GlobalNamesVariables.size(); ++j){
                        if(!GlobalNamesVariables[j].compare(ss)) GlobName = j;
                    }
                    // ======= giving the data to overriders for interpolation (splines or linear) ======
                    if(GlobName > -1){
                        overs[ne]->learnSpl(GlobName,kinetics[ne]->getTimePoints(), kinetics[ne]->getTimeCourse(i), useSplines);
                    } else cout << "Variable " << ss << " not found in the kinetics\n";
                }
            }
            // ======= and giving data to overriders to replace wanted curves by data ========
            currentExperiment->setOverrider(TH1,    OverTh1);
            currentExperiment->setOverrider(TH2,    OverTh2);
            currentExperiment->setOverrider(TREG,   OveriTreg);
            currentExperiment->setOverrider(TH17,   OverTh17);
            currentExperiment->setOverrider(TH0,    OverTh0);
            break;
        }
        case 1: { //currentExperiment = new expFromTh1    (currentModel, parameter < 0 ? 20 : parameter);
            TableCourse* ToTh1   = new TableCourse(folder + string("DATA/Th1ToTh1.txt"));
            TableCourse* ToTh2   = new TableCourse(folder + string("DATA/Th1ToTh2.txt"));
            TableCourse* ToiTreg = new TableCourse(folder + string("DATA/Th1ToTreg.txt"));
            TableCourse* ToTh17  = new TableCourse(folder + string("DATA/Th1ToTh17.txt"));
            TableCourse* ToTh0   = new TableCourse(folder + string("DATA/Th1ToTh0.txt"));
            TableCourse* Untouched   = new TableCourse(folder + string("DATA/Th1Untouched.txt"));
            currentExperiment->giveData(ToTh1,      TH1_TO_TH1);
            currentExperiment->giveData(ToTh2,      TH1_TO_TH2);
            currentExperiment->giveData(ToiTreg,    TH1_TO_ITREG);
            currentExperiment->giveData(ToTh17,     TH1_TO_TH17);
            currentExperiment->giveData(ToTh0,      TH1_TO_TH0);
            currentExperiment->giveData(Untouched,  TH1_UNTOUCHED);
            currentExperiment->giveHowToReadNamesInKinetics(GlobalNamesVariables);
            currentExperiment->loadEvaluators();
            break;
        }
        case 2: { //currentExperiment = new expFromTh2    (currentModel, parameter < 0 ? 20 : parameter);
            TableCourse* ToTh1   = new TableCourse(folder + string("DATA/Th2ToTh1.txt"));
            TableCourse* ToTh2   = new TableCourse(folder + string("DATA/Th2ToTh2.txt"));
            TableCourse* ToiTreg = new TableCourse(folder + string("DATA/Th2ToTreg.txt"));
            TableCourse* ToTh17  = new TableCourse(folder + string("DATA/Th2ToTh17.txt"));
            TableCourse* ToTh0   = new TableCourse(folder + string("DATA/Th2ToTh0.txt"));
            TableCourse* Untouched   = new TableCourse(folder + string("DATA/Th2Untouched.txt"));
            currentExperiment->giveData(ToTh1,      TH2_TO_TH1);
            currentExperiment->giveData(ToTh2,      TH2_TO_TH2);
            currentExperiment->giveData(ToiTreg,    TH2_TO_ITREG);
            currentExperiment->giveData(ToTh17,     TH2_TO_TH17);
            currentExperiment->giveData(ToTh0,      TH2_TO_TH0);
            currentExperiment->giveData(Untouched,  TH2_UNTOUCHED);
            currentExperiment->giveHowToReadNamesInKinetics(GlobalNamesVariables);
            currentExperiment->loadEvaluators();
            break;
        }
        case 3: { //currentExperiment = new expFromTreg   (currentModel, parameter < 0 ? 20 : parameter);
            TableCourse* ToTh1   = new TableCourse(folder + string("DATA/TregToTh1.txt"));
            TableCourse* ToTh2   = new TableCourse(folder + string("DATA/TregToTh2.txt"));
            TableCourse* ToiTreg = new TableCourse(folder + string("DATA/TregToTreg.txt"));
            TableCourse* ToTh17  = new TableCourse(folder + string("DATA/TregToTh17.txt"));
            TableCourse* ToTh0   = new TableCourse(folder + string("DATA/TregToTh0.txt"));
            TableCourse* Untouched   = new TableCourse(folder + string("DATA/TregUntouched.txt"));
            currentExperiment->giveData(ToTh1,      ITREG_TO_TH1);
            currentExperiment->giveData(ToTh2,      ITREG_TO_TH2);
            currentExperiment->giveData(ToiTreg,    ITREG_TO_ITREG);
            currentExperiment->giveData(ToTh17,     ITREG_TO_TH17);
            currentExperiment->giveData(ToTh0,      ITREG_TO_TH0);
            currentExperiment->giveData(Untouched,  ITREG_UNTOUCHED);
            currentExperiment->giveHowToReadNamesInKinetics(GlobalNamesVariables);
            currentExperiment->loadEvaluators();
            break;
        }
        case 4: { //currentExperiment = new expFromTh17   (currentModel, parameter < 0 ? 20 : parameter);
            TableCourse* ToTh1   = new TableCourse(folder + string("DATA/Th17ToTh1.txt"));
            TableCourse* ToTh2   = new TableCourse(folder + string("DATA/Th17ToTh2.txt"));
            TableCourse* ToiTreg = new TableCourse(folder + string("DATA/Th17ToTreg.txt"));
            TableCourse* ToTh17  = new TableCourse(folder + string("DATA/Th17ToTh17.txt"));
            TableCourse* ToTh0   = new TableCourse(folder + string("DATA/Th17ToTh0.txt"));
            TableCourse* Untouched   = new TableCourse(folder + string("DATA/Th17Untouched.txt"));
            currentExperiment->giveData(ToTh1,      TH17_TO_TH1);
            currentExperiment->giveData(ToTh2,      TH17_TO_TH2);
            currentExperiment->giveData(ToiTreg,    TH17_TO_ITREG);
            currentExperiment->giveData(ToTh17,     TH17_TO_TH17);
            currentExperiment->giveData(ToTh0,      TH17_TO_TH0);
            currentExperiment->giveData(Untouched,  TH17_UNTOUCHED);
            currentExperiment->giveHowToReadNamesInKinetics(GlobalNamesVariables);
            currentExperiment->loadEvaluators();
            break;
        }
        case 5:  { //currentExperiment = new expFromTh0    (currentModel, parameter < 0 ? 20 : parameter);
            TableCourse* ToTh1   = new TableCourse(folder + string("DATA/Th0ToTh1.txt"));
            TableCourse* ToTh2   = new TableCourse(folder + string("DATA/Th0ToTh2.txt"));
            TableCourse* ToiTreg = new TableCourse(folder + string("DATA/Th0ToTreg.txt"));
            TableCourse* ToTh17  = new TableCourse(folder + string("DATA/Th0ToTh17.txt"));
            //TableCourse* ToTh0   = new TableCourse(folder + string("DATA/Th0ToTh0.txt")); // no data for it
            TableCourse* Untouched   = new TableCourse(folder + string("DATA/Th0Untouched.txt"));
            currentExperiment->giveData(ToTh1,      TH0_TO_TH1);
            currentExperiment->giveData(ToTh2,      TH0_TO_TH2);
            currentExperiment->giveData(ToiTreg,    TH0_TO_ITREG);
            currentExperiment->giveData(ToTh17,     TH0_TO_TH17);
            //currentExperiment->giveData(ToTh0,      TH0_TO_TH0);
            currentExperiment->giveData(Untouched,  TH0_UNTOUCHED);
            currentExperiment->giveHowToReadNamesInKinetics(GlobalNamesVariables);
            currentExperiment->loadEvaluators();
            break;
        }
        case 6: { //currentExperiment = new expFromTh1    (currentModel, parameter < 0 ? 20 : parameter);
            TableCourse* FromTh1   = new TableCourse(folder + string("DATA/Th1ToTh1.txt"));
            TableCourse* FromTh2   = new TableCourse(folder + string("DATA/Th2ToTh1.txt"));
            TableCourse* FromiTreg = new TableCourse(folder + string("DATA/TregToTh1.txt"));
            TableCourse* FromTh17  = new TableCourse(folder + string("DATA/Th17ToTh1.txt"));
            TableCourse* FromTh0   = new TableCourse(folder + string("DATA/Th0ToTh1.txt"));
            TableCourse* Untouched   = new TableCourse(folder + string("DATA/Th1Untouched.txt"));
            currentExperiment->giveData(FromTh1,      TH1_FROM_TH1);
            currentExperiment->giveData(FromTh2,      TH1_FROM_TH2);
            currentExperiment->giveData(FromiTreg,    TH1_FROM_ITREG);
            currentExperiment->giveData(FromTh17,     TH1_FROM_TH17);
            currentExperiment->giveData(FromTh0,      TH1_FROM_TH0);
            currentExperiment->giveData(Untouched,  TH1_UNTOUCHED_BIS);
            currentExperiment->giveHowToReadNamesInKinetics(GlobalNamesVariables);
            currentExperiment->loadEvaluators();
            break;
        }
        case 7: { //currentExperiment = new expFromTh2    (currentModel, parameter < 0 ? 20 : parameter);
            TableCourse* FromTh1   = new TableCourse(folder + string("DATA/Th1ToTh2.txt"));
            TableCourse* FromTh2   = new TableCourse(folder + string("DATA/Th2ToTh2.txt"));
            TableCourse* FromiTreg = new TableCourse(folder + string("DATA/TregToTh2.txt"));
            TableCourse* FromTh17  = new TableCourse(folder + string("DATA/Th17ToTh2.txt"));
            TableCourse* FromTh0   = new TableCourse(folder + string("DATA/Th0ToTh2.txt"));
            TableCourse* Untouched   = new TableCourse(folder + string("DATA/Th2Untouched.txt"));
            currentExperiment->giveData(FromTh1,      TH2_FROM_TH1);
            currentExperiment->giveData(FromTh2,      TH2_FROM_TH2);
            currentExperiment->giveData(FromiTreg,    TH2_FROM_ITREG);
            currentExperiment->giveData(FromTh17,     TH2_FROM_TH17);
            currentExperiment->giveData(FromTh0,      TH2_FROM_TH0);
            currentExperiment->giveData(Untouched,  TH2_UNTOUCHED_BIS);
            currentExperiment->giveHowToReadNamesInKinetics(GlobalNamesVariables);
            currentExperiment->loadEvaluators();
            break;
        }
        case 8: { //currentExperiment = new expFromTreg   (currentModel, parameter < 0 ? 20 : parameter);
            TableCourse* FromTh1   = new TableCourse(folder + string("DATA/Th1ToTreg.txt"));
            TableCourse* FromTh2   = new TableCourse(folder + string("DATA/Th2ToTreg.txt"));
            TableCourse* FromiTreg = new TableCourse(folder + string("DATA/TregToTreg.txt"));
            TableCourse* FromTh17  = new TableCourse(folder + string("DATA/Th17ToTreg.txt"));
            TableCourse* FromTh0   = new TableCourse(folder + string("DATA/Th0ToTreg.txt"));
            TableCourse* Untouched   = new TableCourse(folder + string("DATA/TregUntouched.txt"));
            currentExperiment->giveData(FromTh1,      ITREG_FROM_TH1);
            currentExperiment->giveData(FromTh2,      ITREG_FROM_TH2);
            currentExperiment->giveData(FromiTreg,    ITREG_FROM_ITREG);
            currentExperiment->giveData(FromTh17,     ITREG_FROM_TH17);
            currentExperiment->giveData(FromTh0,      ITREG_FROM_TH0);
            currentExperiment->giveData(Untouched,  ITREG_UNTOUCHED_BIS);
            currentExperiment->giveHowToReadNamesInKinetics(GlobalNamesVariables);
            currentExperiment->loadEvaluators();
            break;
        }
        case 9: { //currentExperiment = new expFromTh17   (currentModel, parameter < 0 ? 20 : parameter);
            TableCourse* FromTh1   = new TableCourse(folder + string("DATA/Th1ToTh17.txt"));
            TableCourse* FromTh2   = new TableCourse(folder + string("DATA/Th2ToTh17.txt"));
            TableCourse* FromiTreg = new TableCourse(folder + string("DATA/TregToTh17.txt"));
            TableCourse* FromTh17  = new TableCourse(folder + string("DATA/Th17ToTh17.txt"));
            TableCourse* FromTh0   = new TableCourse(folder + string("DATA/Th0ToTh17.txt"));
            TableCourse* Untouched   = new TableCourse(folder + string("DATA/Th17Untouched.txt"));
            currentExperiment->giveData(FromTh1,      TH17_FROM_TH1);
            currentExperiment->giveData(FromTh2,      TH17_FROM_TH2);
            currentExperiment->giveData(FromiTreg,    TH17_FROM_ITREG);
            currentExperiment->giveData(FromTh17,     TH17_FROM_TH17);
            currentExperiment->giveData(FromTh0,      TH17_FROM_TH0);
            currentExperiment->giveData(Untouched,  TH17_UNTOUCHED_BIS);
            currentExperiment->giveHowToReadNamesInKinetics(GlobalNamesVariables);
            currentExperiment->loadEvaluators();
            break;
        }
        case 10:  { //currentExperiment = new expFromTh0    (currentModel, parameter < 0 ? 20 : parameter);
            TableCourse* FromTh1   = new TableCourse(folder + string("DATA/Th1ToTh0.txt"));
            TableCourse* FromTh2   = new TableCourse(folder + string("DATA/Th2ToTh0.txt"));
            TableCourse* FromiTreg = new TableCourse(folder + string("DATA/TregToTh0.txt"));
            TableCourse* FromTh17  = new TableCourse(folder + string("DATA/Th17ToTh0.txt"));
            //TableCourse* FromTh0   = new TableCourse(folder + string("DATA/Th0ToTh0.txt"));
            TableCourse* Untouched   = new TableCourse(folder + string("DATA/Th0Untouched.txt"));
            currentExperiment->giveData(FromTh1,      TH0_FROM_TH1);
            currentExperiment->giveData(FromTh2,      TH0_FROM_TH2);
            currentExperiment->giveData(FromiTreg,    TH0_FROM_ITREG);
            currentExperiment->giveData(FromTh17,     TH0_FROM_TH17);
            //currentExperiment->giveData(FromTh0,      TH0_FROM_TH0);
            currentExperiment->giveData(Untouched,  TH0_UNTOUCHED_BIS);
            currentExperiment->giveHowToReadNamesInKinetics(GlobalNamesVariables);
            currentExperiment->loadEvaluators();
            break;
        }
        case 11: { //currentExperiment = new expDensityTh1(currentModel);
            TableCourse* Dens10   = new TableCourse(folder + string("DATA/Th1Dens10.txt"));
            TableCourse* Dens40   = new TableCourse(folder + string("DATA/Th1Dens40.txt"));
            TableCourse* Dens100   = new TableCourse(folder + string("DATA/Th1Dens100.txt"));
            TableCourse* Dens200   = new TableCourse(folder + string("DATA/Th1Dens200.txt"));
            TableCourse* Dens400   = new TableCourse(folder + string("DATA/Th1Dens400.txt"));
            TableCourse* Dens700   = new TableCourse(folder + string("DATA/Th1Dens700.txt"));
            TableCourse* Dens1000   = new TableCourse(folder + string("DATA/Th1Dens1000.txt"));
            TableCourse* Dens1800   = new TableCourse(folder + string("DATA/Th1Dens1800.txt"));
            currentExperiment->giveData(Dens10,         DENS10k);
            currentExperiment->giveData(Dens40,         DENS40k);
            currentExperiment->giveData(Dens100,        DENS100k);
            currentExperiment->giveData(Dens200,        DENS200k);
            currentExperiment->giveData(Dens400,        DENS400k);
            currentExperiment->giveData(Dens700,        DENS700k);
            currentExperiment->giveData(Dens1000,       DENS1000k);
            currentExperiment->giveData(Dens1800,       DENS1800k);
            currentExperiment->giveHowToReadNamesInKinetics(GlobalNamesVariables);
            currentExperiment->loadEvaluators();
            break;
        }
        case 12: { //currentExperiment = new expDensityTh2(currentModel);
            TableCourse* Dens10   = new TableCourse(folder + string("DATA/Th2Dens10.txt"));
            TableCourse* Dens40   = new TableCourse(folder + string("DATA/Th2Dens40.txt"));
            TableCourse* Dens100   = new TableCourse(folder + string("DATA/Th2Dens100.txt"));
            TableCourse* Dens200   = new TableCourse(folder + string("DATA/Th2Dens200.txt"));
            TableCourse* Dens400   = new TableCourse(folder + string("DATA/Th2Dens400.txt"));
            TableCourse* Dens700   = new TableCourse(folder + string("DATA/Th2Dens700.txt"));
            TableCourse* Dens1000   = new TableCourse(folder + string("DATA/Th2Dens1000.txt"));
            TableCourse* Dens1800   = new TableCourse(folder + string("DATA/Th2Dens1800.txt"));
            currentExperiment->giveData(Dens10,         DENS10k);
            currentExperiment->giveData(Dens40,         DENS40k);
            currentExperiment->giveData(Dens100,        DENS100k);
            currentExperiment->giveData(Dens200,        DENS200k);
            currentExperiment->giveData(Dens400,        DENS400k);
            currentExperiment->giveData(Dens700,        DENS700k);
            currentExperiment->giveData(Dens1000,       DENS1000k);
            currentExperiment->giveData(Dens1800,       DENS1800k);
            currentExperiment->giveHowToReadNamesInKinetics(GlobalNamesVariables);
            currentExperiment->loadEvaluators();
            break;
        }
        case 13: { //currentExperiment = new expDensityTreg(currentModel);
            TableCourse* Dens10   = new TableCourse(folder + string("DATA/TregDens10.txt"));
            TableCourse* Dens40   = new TableCourse(folder + string("DATA/TregDens40.txt"));
            TableCourse* Dens100   = new TableCourse(folder + string("DATA/TregDens100.txt"));
            TableCourse* Dens200   = new TableCourse(folder + string("DATA/TregDens200.txt"));
            TableCourse* Dens400   = new TableCourse(folder + string("DATA/TregDens400.txt"));
            TableCourse* Dens700   = new TableCourse(folder + string("DATA/TregDens700.txt"));
            TableCourse* Dens1000   = new TableCourse(folder + string("DATA/TregDens1000.txt"));
            TableCourse* Dens1800   = new TableCourse(folder + string("DATA/TregDens1800.txt"));
            currentExperiment->giveData(Dens10,         DENS10k);
            currentExperiment->giveData(Dens40,         DENS40k);
            currentExperiment->giveData(Dens100,        DENS100k);
            currentExperiment->giveData(Dens200,        DENS200k);
            currentExperiment->giveData(Dens400,        DENS400k);
            currentExperiment->giveData(Dens700,        DENS700k);
            currentExperiment->giveData(Dens1000,       DENS1000k);
            currentExperiment->giveData(Dens1800,       DENS1800k);
            currentExperiment->giveHowToReadNamesInKinetics(GlobalNamesVariables);
            currentExperiment->loadEvaluators();
            break;
        }
        case 14: { //currentExperiment = new expDensityTh17(currentModel);
            TableCourse* Dens10   = new TableCourse(folder + string("DATA/Th17Dens10.txt"));
            TableCourse* Dens40   = new TableCourse(folder + string("DATA/Th17Dens40.txt"));
            TableCourse* Dens100   = new TableCourse(folder + string("DATA/Th17Dens100.txt"));
            TableCourse* Dens200   = new TableCourse(folder + string("DATA/Th17Dens200.txt"));
            TableCourse* Dens400   = new TableCourse(folder + string("DATA/Th17Dens400.txt"));
            TableCourse* Dens700   = new TableCourse(folder + string("DATA/Th17Dens700.txt"));
            TableCourse* Dens1000   = new TableCourse(folder + string("DATA/Th17Dens1000.txt"));
            TableCourse* Dens1800   = new TableCourse(folder + string("DATA/Th17Dens1800.txt"));
            currentExperiment->giveData(Dens10,         DENS10k);
            currentExperiment->giveData(Dens40,         DENS40k);
            currentExperiment->giveData(Dens100,        DENS100k);
            currentExperiment->giveData(Dens200,        DENS200k);
            currentExperiment->giveData(Dens400,        DENS400k);
            currentExperiment->giveData(Dens700,        DENS700k);
            currentExperiment->giveData(Dens1000,       DENS1000k);
            currentExperiment->giveData(Dens1800,       DENS1800k);
            currentExperiment->giveHowToReadNamesInKinetics(GlobalNamesVariables);
            currentExperiment->loadEvaluators();
            break;
        }
        case 15: { //currentExperiment = new expDensityTh0(currentModel);
            TableCourse* Dens10   = new TableCourse(folder + string("DATA/Th0Dens10.txt"));
            TableCourse* Dens40   = new TableCourse(folder + string("DATA/Th0Dens40.txt"));
            TableCourse* Dens100   = new TableCourse(folder + string("DATA/Th0Dens100.txt"));
            TableCourse* Dens200   = new TableCourse(folder + string("DATA/Th0Dens200.txt"));
            TableCourse* Dens400   = new TableCourse(folder + string("DATA/Th0Dens400.txt"));
            TableCourse* Dens700   = new TableCourse(folder + string("DATA/Th0Dens700.txt"));
            TableCourse* Dens1000   = new TableCourse(folder + string("DATA/Th0Dens1000.txt"));
            TableCourse* Dens1800   = new TableCourse(folder + string("DATA/Th0Dens1800.txt"));
            currentExperiment->giveData(Dens10,         DENS10k);
            currentExperiment->giveData(Dens40,         DENS40k);
            currentExperiment->giveData(Dens100,        DENS100k);
            currentExperiment->giveData(Dens200,        DENS200k);
            currentExperiment->giveData(Dens400,        DENS400k);
            currentExperiment->giveData(Dens700,        DENS700k);
            currentExperiment->giveData(Dens1000,       DENS1000k);
            currentExperiment->giveData(Dens1800,       DENS1800k);
            currentExperiment->giveHowToReadNamesInKinetics(GlobalNamesVariables);
            currentExperiment->loadEvaluators();
            break;
        }
    default:{}
    }



// =============== Scripts 1, 2 & 3 : no optimization, only launches the GUI ================

    if((nb != 100) && (analysisName.size() == 0)){
        #ifndef WITHOUT_QT
        simuWin* p = new simuWin(currentExperiment);
        cout << "Launch GUI ..." << endl;
        p->loadConfig(configFile);
        p->show();
        #else
        cout << "Script finished (without qt, because WITHOUR_QT was defined)\n";
        #endif
    } else {
        createFolder(folderRes);
        // if QT allowed, generates the plots for this set
        #ifndef WITHOUT_QT
        simuWin tempWindow(currentExperiment);   // funny, if in non pointer with simuWin tw = simuWin(currentExperiment), get a compiling error 'use of deleted function' ...
        //tempWindow.loadHistory(QString((folderComb.str() + string("History.txt")).c_str()));
        //tempWindow.useParamSetFromHistory(0);                                                     // takes the first set of parameters (the best), also possible to use msi->useParamSetFromHistory(0, i); for overriding only parameters from this combination,
        tempWindow.loadConfig(configFile);

        // load again the good set.
        if(chosenSet.size() > 0) currentModel->loadParameters(chosenSet);

        if((nb >= 70) && (nb < 80)) tempWindow.setColorScale(GREEN_BLUE_RED);
        else tempWindow.setColorScale(MULTICOL);

        // ======================== experiment / model loaded => here is the analysis performed =================================


        tempWindow.simulate();

        tempWindow.saveSet(folderRes + string("currentSet.txt"));

        // makes the plots and does a PDF for this simulation.
        vector<string> foldersWithPlots = tempWindow.makeFigReportParamSet(folderRes);

        for(int i = 0; i < (int) foldersWithPlots.size(); ++i){
            ofstream tex(foldersWithPlots[i] + string("together.tex"), ios::out);
            tex << textFileForFolder(analysisName);
            tex.close();
            compileLatex(foldersWithPlots[i], string("together.tex"));
        }

        #else
        cerr << "You asked to do perturbation stripts for exporting results, but the graphical mode is disables (WITHOUT_QT)" << endl;
        #endif

        if(nb != 100) return folderRes;
    }

    } // end of the for loop
    return string("");
}




*/
























/*


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
///
///
///         3 - Script to print the simulation of all experiments in all conditions
///
///
///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void reAnalyzeFolder(int ChosenAnalysis, string _folder, bool includingSubFolders){
    vector<string> foldersToParse;
    foldersToParse.push_back(_folder);
    if(includingSubFolders) foldersToParse = findAllResultFolders(_folder); // this should include the current folder (if it has history)

    for(int i = 0; i < (int) foldersToParse.size(); ++i){
        string currentFolder = foldersToParse[i];
        pSets bestSet = readHistory(currentFolder + string("History.txt"));
        bestSet.saveBestSet(currentFolder + string("currentBestSet.txt"));
        TotalAnalysis(ChosenAnalysis, currentFolder, currentFolder + string("currentBestSet.txt"));
    }
}

void sumUpSubFolders(string _folder, bool includingSubFolders){
    vector<string> foldersToParse;
    foldersToParse.push_back(_folder);
    if(includingSubFolders) foldersToParse = findAllResultFolders(_folder); // this should include the current folder (if it has history)

    // qu'est-ce qu'on veut sur une reanaluze ...
    Modele* currentModel = new modeleLatentTbet2();
    MultiExpThs* ME = new MultiExpThs(currentModel);

    for(int i = 0; i < (int) foldersToParse.size(); ++i){
        string currentFolder = foldersToParse[i];
        pSets setsInHistory = readHistory(currentFolder + string("History.txt"));
        oneSet bestSet = setsInHistory.bestOneSet();
        currentModel->setParameters(bestSet.v);
        ME->simulateAll();


        ofstream sumFile(_folder + "/SumSubFolders.txt");
        sumFile << currentFolder << "\n" << bestSet.print() << "/t";
        //bestSet.saveBestSet(currentFolder + string("currentBestSet.txt"));
        //TotalAnalysis(ChosenAnalysis, currentFolder, currentFolder + string("currentBestSet.txt"));
    }
}

void TotalAnalysis(int ChosenAnalysis, string exportFolder, string chosenSet){
    vector<string> listFolders;
    string nextTexFile;
    string chosenConfig = string("");

    //enum{ ANA_CANO = 1, ANA_PERTURB = 2, ANA_DENS = 4, ANA_TITR = 8, ANA_PARAM_AROUND = 16, ANA_PARAM_SCAN = 32, ANA_CYCLO = 64, ANA_BACKGR = 128, ANA_PERTURB20 = 256, ANA_ALL = ANA_CANO | ANA_PERTURB | ANA_DENS | ANA_TITR | ANA_PARAM_AROUND | ANA_PARAM_SCAN | ANA_CYCLO | ANA_BACKGR | ANA_PERTURB20};
    int ANA_SELECTED = ANA_PARAM_AROUND | ANA_PARAM_SCAN;
    if(ChosenAnalysis > 0) ANA_SELECTED = ChosenAnalysis;

    if(ANA_SELECTED & ANA_CANO){
        cout << "- 0 :         No perturbation, normal differentiations   " << endl;
        listFolders.push_back(scriptsWithPerturbations(0, -1, string("A001NormalDiffJ5"), exportFolder, chosenConfig, chosenSet));
        listFolders.push_back(scriptsWithPerturbations(8, -1, string("A002NormalDiffJ4"), exportFolder, chosenConfig, chosenSet));
        listFolders.push_back(scriptsWithPerturbations(9, -1, string("A003NormalDiffJ5Ext"), exportFolder, chosenConfig, chosenSet));

        nextTexFile = exportFolder + string("SumUp1-NormalDiff") + codeTime() + string(".tex");
        for(int i = 0; i < (int) listFolders.size(); ++i){listFolders[i] += string("together.pdf");}
        mergePDFs(listFolders, nextTexFile);
        listFolders.clear();
    }

    if(ANA_SELECTED & ANA_PERTURB){
        cout << "      Changing differentiation condition in the middle (default p = 20 hrs) : " << endl;
        cout << "- 1 :         From Th1,   change to other ones at t = ... hrs   " << endl;
        cout << "- 2 :         From Th2,   change to other ones at t = ... hrs   " << endl;
        cout << "- 3 :         From iTreg, change to other ones at t = ... hrs   " << endl;
        cout << "- 4 :         From Th17,  change to other ones at t = ... hrs   " << endl;
        cout << "- 5 :         From Th0,   change to other ones at t = ... hrs   " << endl;
        listFolders.push_back(scriptsWithPerturbations(1, 5,  string("A010-FromTh1At5hrs"), exportFolder, chosenConfig, chosenSet));
        listFolders.push_back(scriptsWithPerturbations(1, 10, string("A011-FromTh1At10hrs"), exportFolder, chosenConfig, chosenSet));
        listFolders.push_back(scriptsWithPerturbations(1, 20, string("A012-FromTh1At20hrs"), exportFolder, chosenConfig, chosenSet));
        listFolders.push_back(scriptsWithPerturbations(1, 30, string("A013-FromTh1At30hrs"), exportFolder, chosenConfig, chosenSet));
        listFolders.push_back(scriptsWithPerturbations(1, 48, string("A014-FromTh1At48hrs"), exportFolder, chosenConfig, chosenSet));
        listFolders.push_back(scriptsWithPerturbations(1, 60, string("A015-FromTh1At60hrs"), exportFolder, chosenConfig, chosenSet));
        listFolders.push_back(scriptsWithPerturbations(1, 72, string("A016-FromTh1At72hrs"), exportFolder, chosenConfig, chosenSet));

        listFolders.push_back(scriptsWithPerturbations(2, 5,  string("A020-FromTh2At5hrs"), exportFolder, chosenConfig, chosenSet));
        listFolders.push_back(scriptsWithPerturbations(2, 10, string("A021-FromTh2At10hrs"), exportFolder, chosenConfig, chosenSet));
        listFolders.push_back(scriptsWithPerturbations(2, 20, string("A022-FromTh2At20hrs"), exportFolder, chosenConfig, chosenSet));
        listFolders.push_back(scriptsWithPerturbations(2, 30, string("A023-FromTh2At30hrs"), exportFolder, chosenConfig, chosenSet));
        listFolders.push_back(scriptsWithPerturbations(2, 48, string("A024-FromTh2At48hrs"), exportFolder, chosenConfig, chosenSet));
        listFolders.push_back(scriptsWithPerturbations(2, 60, string("A025-FromTh2At60hrs"), exportFolder, chosenConfig, chosenSet));
        listFolders.push_back(scriptsWithPerturbations(2, 72, string("A026-FromTh2At72hrs"), exportFolder, chosenConfig, chosenSet));

        listFolders.push_back(scriptsWithPerturbations(3, 5,  string("A030-FromiTregAt5hrs"), exportFolder, chosenConfig, chosenSet));
        listFolders.push_back(scriptsWithPerturbations(3, 10, string("A031-FromiTregAt10hrs"), exportFolder, chosenConfig, chosenSet));
        listFolders.push_back(scriptsWithPerturbations(3, 20, string("A032-FromiTregAt20hrs"), exportFolder, chosenConfig, chosenSet));
        listFolders.push_back(scriptsWithPerturbations(3, 30, string("A033-FromiTregAt30hrs"), exportFolder, chosenConfig, chosenSet));
        listFolders.push_back(scriptsWithPerturbations(3, 48, string("A034-FromiTregAt48hrs"), exportFolder, chosenConfig, chosenSet));
        listFolders.push_back(scriptsWithPerturbations(3, 60, string("A035-FromiTregAt60hrs"), exportFolder, chosenConfig, chosenSet));
        listFolders.push_back(scriptsWithPerturbations(3, 72, string("A036-FromiTregAt72hrs"), exportFolder, chosenConfig, chosenSet));

        listFolders.push_back(scriptsWithPerturbations(4, 5,  string("A040-FromTh17At5hrs"), exportFolder, chosenConfig, chosenSet));
        listFolders.push_back(scriptsWithPerturbations(4, 10, string("A041-FromTh17At10hrs"), exportFolder, chosenConfig, chosenSet));
        listFolders.push_back(scriptsWithPerturbations(4, 20, string("A042-FromTh17At20hrs"), exportFolder, chosenConfig, chosenSet));
        listFolders.push_back(scriptsWithPerturbations(4, 30, string("A043-FromTh17At30hrs"), exportFolder, chosenConfig, chosenSet));
        listFolders.push_back(scriptsWithPerturbations(4, 48, string("A044-FromTh17At48hrs"), exportFolder, chosenConfig, chosenSet));
        listFolders.push_back(scriptsWithPerturbations(4, 60, string("A045-FromTh17At60hrs"), exportFolder, chosenConfig, chosenSet));
        listFolders.push_back(scriptsWithPerturbations(4, 72, string("A046-FromTh17At72hrs"), exportFolder, chosenConfig, chosenSet));

        listFolders.push_back(scriptsWithPerturbations(5, 5,  string("A050-FromTh0At5hrs"), exportFolder, chosenConfig, chosenSet));
        listFolders.push_back(scriptsWithPerturbations(5, 10, string("A051-FromTh0At10hrs"), exportFolder, chosenConfig, chosenSet));
        listFolders.push_back(scriptsWithPerturbations(5, 20, string("A052-FromTh0At20hrs"), exportFolder, chosenConfig, chosenSet));
        listFolders.push_back(scriptsWithPerturbations(5, 30, string("A053-FromTh0At30hrs"), exportFolder, chosenConfig, chosenSet));
        listFolders.push_back(scriptsWithPerturbations(5, 48, string("A054-FromTh0At48hrs"), exportFolder, chosenConfig, chosenSet));
        listFolders.push_back(scriptsWithPerturbations(5, 60, string("A055-FromTh0At60hrs"), exportFolder, chosenConfig, chosenSet));
        listFolders.push_back(scriptsWithPerturbations(5, 72, string("A056-FromTh0At72hrs"), exportFolder, chosenConfig, chosenSet));

        nextTexFile = folder + string("SumUp2-ChangeMedium") + codeTime() + string(".tex");
        for(int i = 0; i < (int) listFolders.size(); ++i){listFolders[i] += string("together.pdf");}
        mergePDFs(listFolders, nextTexFile);
        listFolders.clear();
    }
    cerr << "========================= Not stuck =======================" << endl;
    if(ANA_SELECTED & ANA_PERTURB20){
        cerr << "========================= Yahooooo =======================" << endl;
        cout << "      Changing differentiation condition in the middle (default p = 20 hrs) : " << endl;
        cout << "- 1 :         From Th1,   change to other ones at t = 20 hrs   " << endl;
        cout << "- 2 :         From Th2,   change to other ones at t = 20 hrs   " << endl;
        cout << "- 3 :         From iTreg, change to other ones at t = 20 hrs   " << endl;
        cout << "- 4 :         From Th17,  change to other ones at t = 20 hrs   " << endl;
        cout << "- 5 :         From Th0,   change to other ones at t = 20 hrs   " << endl;
        listFolders.push_back(scriptsWithPerturbations(1, 20, string("A012-FromTh1At20hrs"), exportFolder, chosenConfig, chosenSet));
        listFolders.push_back(scriptsWithPerturbations(2, 20, string("A022-FromTh2At20hrs"), exportFolder, chosenConfig, chosenSet));
        listFolders.push_back(scriptsWithPerturbations(3, 20, string("A032-FromiTregAt20hrs"), exportFolder, chosenConfig, chosenSet));
        listFolders.push_back(scriptsWithPerturbations(4, 20, string("A042-FromTh17At20hrs"), exportFolder, chosenConfig, chosenSet));
        listFolders.push_back(scriptsWithPerturbations(5, 20, string("A052-FromTh0At20hrs"), exportFolder, chosenConfig, chosenSet));

        nextTexFile = exportFolder + string("SumUp2-ChangeMedium") + codeTime() + string(".tex");
        for(int i = 0; i < (int) listFolders.size(); ++i){listFolders[i] += string("together.pdf");}
        mergePDFs(listFolders, nextTexFile);
        listFolders.clear();
    }

    if(ANA_SELECTED & ANA_DENS){
        cout << "      Titrations of cell density in the well : " << endl;
        cout << "- 10 :        Th1   diff, Different Densities of cells               " << endl;
        cout << "- 11 :        Th2   diff, Different Densities of cells               " << endl;
        cout << "- 12 :        iTreg diff, Different Densities of cells               " << endl;
        cout << "- 13 :        Th17  diff, Different Densities of cells               " << endl;
        cout << "- 14 :        Th10  diff, Different Densities of cells               " << endl;
        listFolders.push_back(scriptsWithPerturbations(10, -1, string("A080-DensitiesTh1"), exportFolder, chosenConfig, chosenSet));
        listFolders.push_back(scriptsWithPerturbations(11, -1, string("A081-DensitiesTh2"), exportFolder, chosenConfig, chosenSet));
        listFolders.push_back(scriptsWithPerturbations(12, -1, string("A082-DensitiesiTreg"), exportFolder, chosenConfig, chosenSet));
        listFolders.push_back(scriptsWithPerturbations(13, -1, string("A083-DensitiesTh17"), exportFolder, chosenConfig, chosenSet));
        listFolders.push_back(scriptsWithPerturbations(14, -1, string("A084-DensitiesTh0"), exportFolder, chosenConfig, chosenSet));

        nextTexFile = exportFolder + string("SumUp3-CellDensities") + codeTime() + string(".tex");
        for(int i = 0; i < (int) listFolders.size(); ++i){listFolders[i] += string("together.pdf");}
        mergePDFs(listFolders, nextTexFile);
        listFolders.clear();
    }

    if(ANA_SELECTED & ANA_TITR){
        cout << "      Titrations of cytokines : " << endl;
        cout << "- 20 :        Th1,  Doses of IL2                         " << endl;
        cout << "- 21 :        Th1,  Doses of IL4                         " << endl;
        cout << "- 22 :        Th1,  Doses of IL6                         " << endl;
        cout << "- 23 :        Th1,  Doses of IL12                        " << endl;
        cout << "- 24 :        Th1,  Doses of IL17                        " << endl;
        cout << "- 25 :        Th1,  Doses of IL21                        " << endl;
        cout << "- 26 :        Th1,  Doses of IFNG                        " << endl;
        listFolders.push_back(scriptsWithPerturbations(20, -1, string("A100-Th1DosesIL2"), exportFolder, chosenConfig, chosenSet));
        listFolders.push_back(scriptsWithPerturbations(21, -1, string("A101-Th1DosesIL4"), exportFolder, chosenConfig, chosenSet));
        listFolders.push_back(scriptsWithPerturbations(22, -1, string("A102-Th1DosesIL6"), exportFolder, chosenConfig, chosenSet));
        listFolders.push_back(scriptsWithPerturbations(23, -1, string("A103-Th1DosesIL12"), exportFolder, chosenConfig, chosenSet));
        listFolders.push_back(scriptsWithPerturbations(24, -1, string("A104-Th1DosesIL17"), exportFolder, chosenConfig, chosenSet));
        listFolders.push_back(scriptsWithPerturbations(25, -1, string("A105-Th1DosesIL21"), exportFolder, chosenConfig, chosenSet));
        listFolders.push_back(scriptsWithPerturbations(26, -1, string("A106-Th1DosesIFNG"), exportFolder, chosenConfig, chosenSet));

        cout << "- 30 :        Th2,  Doses of IL2                         " << endl;
        cout << "- 31 :        Th2,  Doses of IL4                         " << endl;
        cout << "- 32 :        Th2,  Doses of IL6                         " << endl;
        cout << "- 33 :        Th2,  Doses of IL12                        " << endl;
        cout << "- 34 :        Th2,  Doses of IL17                        " << endl;
        cout << "- 35 :        Th2,  Doses of IL21                        " << endl;
        cout << "- 36 :        Th2,  Doses of IFNG                        " << endl;
        listFolders.push_back(scriptsWithPerturbations(30, -1, string("A110-Th2DosesIL2"), exportFolder, chosenConfig, chosenSet));
        listFolders.push_back(scriptsWithPerturbations(31, -1, string("A111-Th2DosesIL4"), exportFolder, chosenConfig, chosenSet));
        listFolders.push_back(scriptsWithPerturbations(32, -1, string("A112-Th2DosesIL6"), exportFolder, chosenConfig, chosenSet));
        listFolders.push_back(scriptsWithPerturbations(33, -1, string("A113-Th2DosesIL12"), exportFolder, chosenConfig, chosenSet));
        listFolders.push_back(scriptsWithPerturbations(34, -1, string("A114-Th2DosesIL17"), exportFolder, chosenConfig, chosenSet));
        listFolders.push_back(scriptsWithPerturbations(35, -1, string("A115-Th2DosesIL21"), exportFolder, chosenConfig, chosenSet));
        listFolders.push_back(scriptsWithPerturbations(36, -1, string("A116-Th2DosesIFNG"), exportFolder, chosenConfig, chosenSet));

        cout << "- 40 :        iTreg,  Doses of IL2                         " << endl;
        cout << "- 41 :        iTreg,  Doses of IL4                         " << endl;
        cout << "- 42 :        iTreg,  Doses of IL6                         " << endl;
        cout << "- 43 :        iTreg,  Doses of IL12                        " << endl;
        cout << "- 44 :        iTreg,  Doses of IL17                        " << endl;
        cout << "- 45 :        iTreg,  Doses of IL21                        " << endl;
        cout << "- 46 :        iTreg,  Doses of IFNG                        " << endl;
        listFolders.push_back(scriptsWithPerturbations(40, -1, string("A120-iTregDosesIL2"), exportFolder, chosenConfig, chosenSet));
        listFolders.push_back(scriptsWithPerturbations(41, -1, string("A121-iTregDosesIL4"), exportFolder, chosenConfig, chosenSet));
        listFolders.push_back(scriptsWithPerturbations(42, -1, string("A122-iTregDosesIL6"), exportFolder, chosenConfig, chosenSet));
        listFolders.push_back(scriptsWithPerturbations(43, -1, string("A123-iTregDosesIL12"), exportFolder, chosenConfig, chosenSet));
        listFolders.push_back(scriptsWithPerturbations(44, -1, string("A124-iTregDosesIL17"), exportFolder, chosenConfig, chosenSet));
        listFolders.push_back(scriptsWithPerturbations(45, -1, string("A125-iTregDosesIL21"), exportFolder, chosenConfig, chosenSet));
        listFolders.push_back(scriptsWithPerturbations(46, -1, string("A126-iTregDosesIFNG"), exportFolder, chosenConfig, chosenSet));

        cout << "- 50 :        Th17,  Doses of IL2                         " << endl;
        cout << "- 51 :        Th17,  Doses of IL4                         " << endl;
        cout << "- 52 :        Th17,  Doses of IL6                         " << endl;
        cout << "- 53 :        Th17,  Doses of IL12                        " << endl;
        cout << "- 54 :        Th17,  Doses of IL17                        " << endl;
        cout << "- 55 :        Th17,  Doses of IL21                        " << endl;
        cout << "- 56 :        Th17,  Doses of IFNG                        " << endl;
        listFolders.push_back(scriptsWithPerturbations(50, -1, string("A130-Th17DosesIL2"), exportFolder, chosenConfig, chosenSet));
        listFolders.push_back(scriptsWithPerturbations(51, -1, string("A131-Th17DosesIL4"), exportFolder, chosenConfig, chosenSet));
        listFolders.push_back(scriptsWithPerturbations(52, -1, string("A132-Th17DosesIL6"), exportFolder, chosenConfig, chosenSet));
        listFolders.push_back(scriptsWithPerturbations(53, -1, string("A133-Th17DosesIL12"), exportFolder, chosenConfig, chosenSet));
        listFolders.push_back(scriptsWithPerturbations(54, -1, string("A134-Th17DosesIL17"), exportFolder, chosenConfig, chosenSet));
        listFolders.push_back(scriptsWithPerturbations(55, -1, string("A135-Th17DosesIL21"), exportFolder, chosenConfig, chosenSet));
        listFolders.push_back(scriptsWithPerturbations(56, -1, string("A136-Th17DosesIFNG"), exportFolder, chosenConfig, chosenSet));

        cout << "- 60 :        Th0,  Doses of IL2                         " << endl;
        cout << "- 61 :        Th0,  Doses of IL4                         " << endl;
        cout << "- 62 :        Th0,  Doses of IL6                         " << endl;
        cout << "- 63 :        Th0,  Doses of IL12                        " << endl;
        cout << "- 64 :        Th0,  Doses of IL17                        " << endl;
        cout << "- 65 :        Th0,  Doses of IL21                        " << endl;
        cout << "- 66 :        Th0,  Doses of IFNG                        " << endl;
        listFolders.push_back(scriptsWithPerturbations(60, -1, string("A140-Th0DosesIL2"), exportFolder, chosenConfig, chosenSet));
        listFolders.push_back(scriptsWithPerturbations(61, -1, string("A141-Th0DosesIL4"), exportFolder, chosenConfig, chosenSet));
        listFolders.push_back(scriptsWithPerturbations(62, -1, string("A142-Th0DosesIL6"), exportFolder, chosenConfig, chosenSet));
        listFolders.push_back(scriptsWithPerturbations(63, -1, string("A143-Th0DosesIL12"), exportFolder, chosenConfig, chosenSet));
        listFolders.push_back(scriptsWithPerturbations(64, -1, string("A144-Th0DosesIL17"), exportFolder, chosenConfig, chosenSet));
        listFolders.push_back(scriptsWithPerturbations(65, -1, string("A145-Th0DosesIL21"), exportFolder, chosenConfig, chosenSet));
        listFolders.push_back(scriptsWithPerturbations(66, -1, string("A146-Th0DosesIFNG"), exportFolder, chosenConfig, chosenSet));

        nextTexFile = exportFolder + string("SumUp4-CytokineTitration") + codeTime() + string(".tex");
        for(int i = 0; i < (int) listFolders.size(); ++i){listFolders[i] += string("together.pdf");}
        mergePDFs(listFolders, nextTexFile);
        listFolders.clear();
    }

    if(ANA_SELECTED & ANA_PARAM_AROUND){
        cout << "- 70 :        Th1,  Variations of the given parameter    " << endl;
        cout << "- 71 :        Th2,  Variations of the given parameter    " << endl;
        cout << "- 72 :        iTreg,Variations of the given parameter    " << endl;
        cout << "- 73 :        Th17, Variations of the given parameter    " << endl;
        cout << "- 74 :        Th0,  Variations of the given parameter    " << endl;
    }
    if(ANA_SELECTED & ANA_PARAM_SCAN){
        cout << "- 75 :        Th1,  Scanning the given parameter         " << endl;
        cout << "- 76 :        Th2,  Scanning the given parameter         " << endl;
        cout << "- 77 :        iTreg,Scanning the given parameter         " << endl;
        cout << "- 78 :        Th17, Scanning the given parameter         " << endl;
        cout << "- 79 :        Th0,  Scanning the given parameter         " << endl;
    }

    Modele* currentModel = new modeleLatentTbet2();
    for(int kp = 0; kp < currentModel->getNbParams(); ++kp){
        if(ANA_SELECTED & ANA_PARAM_AROUND){
            stringstream scrName;
            scrName << "B" << 2*kp << "-Th1ParamAround-" << currentModel->getParamName(kp);
            listFolders.push_back(scriptsWithPerturbations(70, kp, scrName.str(), exportFolder, chosenConfig, chosenSet));
        }
        if(ANA_SELECTED & ANA_PARAM_SCAN){
            stringstream scrName2;
            scrName2 << "B" << 2*kp+1 << "-Th1ParamScanning-" << currentModel->getParamName(kp);
            listFolders.push_back(scriptsWithPerturbations(75, kp, scrName2.str(), exportFolder, chosenConfig, chosenSet));
        }
        if(ANA_SELECTED & ANA_PARAM_AROUND){
            stringstream scrName;
            scrName << "C" << 2*kp << "-Th2ParamAround-" << currentModel->getParamName(kp);
            listFolders.push_back(scriptsWithPerturbations(71, kp, scrName.str(), exportFolder, chosenConfig, chosenSet));
        }
        if(ANA_SELECTED & ANA_PARAM_SCAN){
            stringstream scrName2;
            scrName2 << "C" << 2*kp+1 << "-Th2ParamScanning-" << currentModel->getParamName(kp);
            listFolders.push_back(scriptsWithPerturbations(76, kp, scrName2.str(), exportFolder, chosenConfig, chosenSet));
        }
        if(ANA_SELECTED & ANA_PARAM_AROUND){
            stringstream scrName;
            scrName << "D" << 2*kp << "-iTregParamAround-" << currentModel->getParamName(kp);
            listFolders.push_back(scriptsWithPerturbations(72, kp, scrName.str(), exportFolder, chosenConfig, chosenSet));
        }
        if(ANA_SELECTED & ANA_PARAM_SCAN){
            stringstream scrName2;
            scrName2 << "D" << 2*kp+1 << "-iTregParamScanning-" << currentModel->getParamName(kp);
            listFolders.push_back(scriptsWithPerturbations(77, kp, scrName2.str(), exportFolder, chosenConfig, chosenSet));
        }
        if(ANA_SELECTED & ANA_PARAM_AROUND){
            stringstream scrName;
            scrName << "E" << 2*kp << "-Th17ParamAround-" << currentModel->getParamName(kp);
            listFolders.push_back(scriptsWithPerturbations(73, kp, scrName.str(), exportFolder, chosenConfig, chosenSet));
        }
        if(ANA_SELECTED & ANA_PARAM_SCAN){
            stringstream scrName2;
            scrName2 << "E" << 2*kp+1 << "-Th17ParamScanning-" << currentModel->getParamName(kp);
            listFolders.push_back(scriptsWithPerturbations(78, kp, scrName2.str(), exportFolder, chosenConfig, chosenSet));
        }
        if(ANA_SELECTED & ANA_PARAM_AROUND){
            stringstream scrName;
            scrName << "F" << 2*kp << "-Th0ParamAround-" << currentModel->getParamName(kp);
            listFolders.push_back(scriptsWithPerturbations(74, kp, scrName.str(), exportFolder, chosenConfig, chosenSet));
        }
        if(ANA_SELECTED & ANA_PARAM_SCAN){
            stringstream scrName2;
            scrName2 << "F" << 2*kp+1 << "-Th0ParamScanning-" << currentModel->getParamName(kp);
            listFolders.push_back(scriptsWithPerturbations(79, kp, scrName2.str(), exportFolder, chosenConfig, chosenSet));
        }
    }

    if((ANA_SELECTED & ANA_PARAM_AROUND) || (ANA_SELECTED & ANA_PARAM_SCAN)){
        nextTexFile = exportFolder + string("SumUp5-ScanningParameters") + codeTime() + string(".tex");
        for(int i = 0; i < (int) listFolders.size(); ++i){listFolders[i] += string("together.pdf");}
        mergePDFs(listFolders, nextTexFile);
        listFolders.clear();
    }

    if(ANA_SELECTED & ANA_CYCLO){
        cout << "             All conditions, treatment with cycloheximidine at the given time   " << endl;
        listFolders.push_back(scriptsWithPerturbations(80, 5,  string("A150-Cvcloheximidine5hours"), exportFolder, chosenConfig, chosenSet));
        listFolders.push_back(scriptsWithPerturbations(80, 10, string("A151-Cvcloheximidine10hours"), exportFolder, chosenConfig, chosenSet));
        listFolders.push_back(scriptsWithPerturbations(80, 20, string("A152-Cvcloheximidine20hours"), exportFolder, chosenConfig, chosenSet));
        listFolders.push_back(scriptsWithPerturbations(80, 30, string("A153-Cvcloheximidine30hours"), exportFolder, chosenConfig, chosenSet));
        listFolders.push_back(scriptsWithPerturbations(80, 48, string("A154-Cvcloheximidine48hours"), exportFolder, chosenConfig, chosenSet));
        listFolders.push_back(scriptsWithPerturbations(80, 60, string("A155-Cvcloheximidine60hours"), exportFolder, chosenConfig, chosenSet));
        listFolders.push_back(scriptsWithPerturbations(80, 72, string("A156-Cvcloheximidine72hours"), exportFolder, chosenConfig, chosenSet));

        nextTexFile = exportFolder + string("SumUp6-Cyclohexximidine") + codeTime() + string(".tex");
        for(int i = 0; i < (int) listFolders.size(); ++i){listFolders[i] += string("together.pdf");}
        mergePDFs(listFolders, nextTexFile);
        listFolders.clear();
    }

    if(ANA_SELECTED & ANA_BACKGR){
        cout << "             All conditions for a single background of given index (0=WT, 1, ...)   " << endl;
        for(int kb = 0; kb < Back::NB_GLOB_BACK; ++kb){
            stringstream scrName;
            scrName << "G" << kb << "-Backgr-" << getBackgroundName(getBackgroundNr(kb));
            listFolders.push_back(scriptsWithPerturbations(90, kb, scrName.str(), exportFolder, chosenConfig, chosenSet));
        }

        nextTexFile = exportFolder + string("SumUp7-SingleDeficientBackgrounds") + codeTime() + string(".tex");
        for(int i = 0; i < (int) listFolders.size(); ++i){listFolders[i] += string("together.pdf");}
        mergePDFs(listFolders, nextTexFile);
        listFolders.clear();
    }

    //Modele* currentModel2 = new modeleLatentTbet2();
    // {
    //     stringstream scrName;
    //    scrName << "F" << 2*85 << "-Th0ParamAround-" << currentModel2->getParamName(85);
    //    listFolders.push_back(scriptsWithPerturbations(74, 85, scrName.str(), exportFolder, chosenConfig, chosenSet));
    // }
    return;
}
*/


/*
// it is better to have an independent random engine, to be separable from the optimizer library
std::random_device *rd; // allocate a pointer
std::mt19937 *gen;
std::uniform_int_distribution<> *SpreadDistrib;          // integer distribution
std::uniform_real_distribution<> *RealDistrib;
void initRandsIfNecessary(){
    static bool randsAreInit = false;
    if(randsAreInit) return;
    //rd   = new std::random_device(time(0));
    std::mt19937::result_type seed = time(0);
    gen  = new std::mt19937 (seed);  //(*rd)()
    cout << "      MultiObjive Seed (mt19937) : " << seed << endl;
    RealDistrib = new std::uniform_real_distribution<> (0,1);
    randsAreInit = true;
}
double RandReal(){
    initRandsIfNecessary();
    return (*RealDistrib)(*gen);
}
int RandGen(int a, int b){
    if(b <= 0) {cerr << "ERR: RandGen, a should be < b.\n"; return 0;}
    initRandsIfNecessary();
    static int last_min = 0;
    static int last_max = 10;
    if((a != last_min) || (b != last_max)){
        if(SpreadDistrib) delete SpreadDistrib;
        SpreadDistrib  = new std::uniform_int_distribution<> (a,b);
        last_min = a;
        last_max = b;
    }
    return (*SpreadDistrib)(*gen);
}



vector<double> createMultiRandom(int nb){
    //1- creates a vector with random numbers [0..1]
    vector<double> res;
    res.push_back(0.0);
    for(int i = 0; i < nb-1; ++i){
        res.push_back(RandReal());
    }
    //cout << printVector(res) << endl;
    //2 - sort it and create the vector of differences between numbers (so the total sum is 1)
    res.push_back(1.0);
    std::sort(res.begin(), res.end());
    //cout << printVector(res) << endl;
    vector<double> res2;
    for(int i = 0; i < nb; ++i){
        res2.push_back(res[i+1] - res[i]);
    }
    //cout << printVector(res2) << endl;
    //3 - shuffle

    std::shuffle(res2.begin(), res2.end(), *gen); // note;  make sure that init rand was called (ok: randreal is called)
    //cout << printVector(res2) << endl;
    return res2;
}

vector<double> createMultiRandomDominant(int nb){
    //1- creates a vector with random numbers [0..1]
    vector<double> res;
    res.push_back(RandReal());
    double sum = res[0];
    for(int i = 1; i < nb-1; ++i){
        res.push_back(RandReal() * (1.0 - sum));
        sum += res[i];
    }
    res.push_back(1-sum);
    //cout << printVector(res) << endl;
    //3 - shuffle
    std::shuffle(res.begin(), res.end(), *gen); //note : make sure init rand is called (ok, rand real is called)
    return res;
}


inline bool mycomp (const pair<int, double> p1, const pair<int, double> p2){
        return (p1.second < p2.second);}

//enum politicalMethods {ST_ONLYCANO, ST_ALL , ST_FROM, ST_TO, ST_RANDOM, ST_OSCILL, ST_ONLYONE, NBSTRATS};
//enum politicalMethod {ST_ONLYONE, ST_SUM, ST_RANDOM_EQUAL, ST_RANDOM_UNEQUAL, ST_EVOL_WEAK, ST_EVOL_STRONG, ST_OSCILL, ST_MAX, ST_MAX_EVOL, ST_CUSTOM, NBSTRATS};
string politicalName(politicalMethod p){
    switch(p){
        case ST_ONLYONE:        return string("ONLYONE: Fit Only one experiment");
        case ST_SUM:            return string("SUM: Sum cost of considered experiments");
        case ST_RANDOM_EQUAL:   return string("RANDOM_EQUAL: Gives weights to considered experiments (sum = 1, weights around 1/n)");
        case ST_RANDOM_UNEQUAL: return string("RANDOM_UNEQUAL: Gives weights to considered experiments (sum = 1, unequally distributed)");
        case ST_EVOL_WEAK:      return string("EVOL_WEAK: The (weakly) dominantly weighted experiment changes with time (in the given order).");
        case ST_EVOL_STRONG:    return string("EVOL_WEAK: The (strongly) dominantly weighted experiment changes with time (in the given order).");
        case ST_OSCILL:         return string("EVOL_WEAK: The (strongly) dominantly weighted experiment randomly changes from time-to-time");
        case ST_MAX:            return string("MAX: returns the cost of the worst considered experiment:");
        case ST_MAX_EVOL:       return string("MAX_EVOL: at stage n, returns the max cost of the best n experiments");
        case ST_CUSTOM:         return string("CUSTOM: doesn't touch the coefficient. Can be user defined.");
        default:                return string(":");
    }
}



    MultiExpThs::MultiExpThs(Modele* currentModel) : MultiExperiments(currentModel), pol(ST_SUM), changePoliticsEveryTime(true), lastNumber(-1), testMode(false) {
        vector<Experiment*> load = loadAllExperimentsWithData(currentModel);
        this->AddExperiment(load[ECANO]);
        this->AddExperiment(load[EFROMTH1]);
        this->AddExperiment(load[EFROMTH2]);
        this->AddExperiment(load[EFROMITREG]);
        this->AddExperiment(load[EFROMTH17]);
        this->AddExperiment(load[EFROMTH0]);
        this->AddExperiment(load[ETOTH1]);
        this->AddExperiment(load[ETOTH2]);
        this->AddExperiment(load[ETOITREG]);
        this->AddExperiment(load[ETOTH17]);
        this->AddExperiment(load[ETOTH0]);      // Be careful to keep them all in this order, so getExperiment(ENUM) is still good
        fakeCostsForTests.resize(nbBigExp(), 0.0);
    }

    void MultiExpThs::setPolitics(politicalMethod p){
        pol = p;
        changePoliticsEveryTime = true;
        int NEC = subExpsToConsider.size();
        for(int i = 0; i < nbBigExp(); ++i){
            setCoefficient(i, 0.0);
        }
        for(int i = 0; i < NEC; ++i){
            setCoefficient(subExpsToConsider[i], 1.0);
        }
    }

    void MultiExpThs::considerExp(int BigExpID){
        if((BigExpID < 0) || (BigExpID >= nbBigExp())) {cerr << "ERR : MultiExpThs::considerExp(" << BigExpID << "), only " << nbBigExp() << " experiments"; return;}
        for(int i = 0; i < (int) subExpsToConsider.size();++i){
            if(subExpsToConsider[i] == BigExpID) {cerr << "WRN: adding twice experiment " << BigExpID; return;}
        }
        subExpsToConsider.push_back(BigExpID);
    }

    void MultiExpThs::politics(){
        if(changePoliticsEveryTime){
            //if(cptNbSimus == lastNumber) return;
            //lastNumber = cptNbSimus;
            if(pol == ST_CUSTOM){       // note : the constructor puts the coefficients to 1.0 by default.
                changePoliticsEveryTime = false;
                return;
            }
            int NEC = subExpsToConsider.size();
            if(NEC == 0){
                cerr << "ERR : multiExpThs::politics(), no experiment selected for multi-objective optimization. Please use function considerExp()";
                changePoliticsEveryTime = false;
            }
            for(int i = 0; i < nbBigExp(); ++i){
                coefficients[i]= 0.0;
            }



            switch(pol){
                case ST_ONLYONE: {
                    if(NEC != 1) {cerr << "ERR: multiExpThs::politics(), more than one experiment to fit in the 'ST_ONLYONE'' case.\n"; return;}
                    setCoefficient(subExpsToConsider[0], 1.0);
                    changePoliticsEveryTime = false;        // need to be done only once
                    break;
                }
                case ST_SUM:{
                    for(int i = 0; i < NEC; ++i){
                        setCoefficient(subExpsToConsider[i], 1.0);
                    }
                    changePoliticsEveryTime = false;             // need to be done only once
                    break;
                }
                case ST_RANDOM_EQUAL:{
                    vector<double> listRd = createMultiRandom(NEC);
                    for(int i = 0; i < NEC; ++i){
                        setCoefficient(subExpsToConsider[i], listRd[i]);
                    }
                    break;
                }
                case ST_RANDOM_UNEQUAL:{
                    vector<double> listRd = createMultiRandomDominant(NEC);
                    for(int i = 0; i < NEC; ++i){
                        setCoefficient(subExpsToConsider[i], listRd[i]);
                    }
                    break;
                }
                case ST_EVOL_WEAK:
                case ST_EVOL_STRONG:{ /// designed for 50 000 cost calls, and then goes to equality with time ?
                    if(cptNbSimus < 10000) setCoefficient(subExpsToConsider[0], 1.0);
                    else {
                        double strong = (pol == ST_EVOL_WEAK) ? 0.3 : 0.7;
                        double weakWeight = (1 - strong) / ((double) NEC); // part of the weight to be divided between all.

                        for(int i = 0; i < NEC; ++i){
                            setCoefficient(subExpsToConsider[i], weakWeight);
                        }
                        int space = (int) (40000.0 / (double) NEC);
                        int currentExpStrong = (cptNbSimus - 10000) / space;
                        if(currentExpStrong >= NEC) currentExpStrong = NEC -1;

                        setCoefficient(subExpsToConsider[currentExpStrong], strong + weakWeight);

                        if(cptNbSimus >= 50000){
                            double equilibrium = 1.0 / ((double) NEC);
                            for(int i = 0; i < NEC; ++i){
                                coefficients[subExpsToConsider[i]] += (equilibrium - coefficients[subExpsToConsider[i]]) * (1.0 / 50000.);
                            }
                        }
                    }
                    break;
                }

                case ST_OSCILL:{ /// designed for 50 000 cost calls, and then goes to equality with time ?
                    if(cptNbSimus < 10000) setCoefficient(subExpsToConsider[0], 1.0);
                    else {
                        static int currentStrong = 0;
                        if((cptNbSimus % 2500) == (0 % 2500)) {
                            currentStrong = RandGen(0, NEC-1);
                        }
                        double strong = (pol == ST_EVOL_WEAK) ? 0.3 : 0.7;
                        double weakWeight = (1 - strong) / ((double) NEC); // part of the weight to be divided between all.
                        for(int i = 0; i < NEC; ++i){
                            setCoefficient(subExpsToConsider[i], weakWeight);
                        }
                        setCoefficient(subExpsToConsider[currentStrong], strong + weakWeight);
                    }
                    break;
                }
                case ST_MAX: case ST_MAX_EVOL:{ // before sim
                    for(int i = 0; i < NEC; ++i){
                        setCoefficient(subExpsToConsider[i], 1.0);
                    }
                    break;
                }
                default:{}
            }
        }
    }



    void MultiExpThs::postPolitics(){

        if((pol == ST_MAX) || (pol == ST_MAX_EVOL)){
            for(int i = 0; i < nbBigExp(); ++i){
                coefficients[i]= 0.0;
            }
            int NEC = subExpsToConsider.size();
            // note : without coefficients because they are all to 1
            vector<std::pair<int, double>> costPerExp;
            if(!testMode){
                for(int i = 0 ; i < NEC; ++i){
                    costPerExp.push_back(std::pair<int, double>(subExpsToConsider[i],costBigExp(subExpsToConsider[i])));
                }
            } else {
                for(int i = 0 ; i < NEC; ++i){
                    costPerExp.push_back(std::pair<int, double>(subExpsToConsider[i],fakeCostsForTests[subExpsToConsider[i]]));
                }
            }
            std::sort(costPerExp.begin(), costPerExp.end(), mycomp);
            if(pol == ST_MAX){
                setCoefficient(costPerExp[0].first, 1.0);
            } else {
                if(NEC == 1) {setCoefficient( subExpsToConsider[0], 1.0);}
                else{
                    int nbMultiExp = min(NEC, 1 + (cptNbSimus / (50000 / (NEC - 1))));
                    for(int i = 0; i < nbMultiExp; ++i){
                        setCoefficient(costPerExp[i].first, 1.0);
                    }
                }
            }
        } // Note ; might Need to replace parents with the algo...
    }

    void MultiExpThs::testPolitics() {
        testMode = true;
        vector<int> saveSubExps = subExpsToConsider;
        subExpsToConsider.clear();

        for(int i = 0; i < NBSTRATS; ++i){
            setPolitics((politicalMethod) i);
            if(i == 0) considerExp(ECANO);
            if(i == 1) {considerExp(ETOTH2);
                considerExp(EFROMTH2);}
            int NEC = subExpsToConsider.size();

            pol = (politicalMethod) i;
            cout << " ================== politics = " << politicalName(pol) << " =============== " << endl;
            cout << "Experiments being considered in the optimization : " << endl;
            for(int j = 0; j < NEC; ++j){
                cout << subExpsToConsider[j] << "\t" << getExperiment(subExpsToConsider[j])->Identification << endl;
            }

            cptNbSimus = 0;
            for(cptNbSimus = 0; cptNbSimus < 60000; cptNbSimus+= 500){
                politics();
                if((pol == ST_MAX) || (pol == ST_MAX_EVOL)){
                    for(int j = 0; j < nbBigExp(); ++j){
                        fakeCostsForTests[j] = RandReal() * 250;
                    }
                    postPolitics();
                }

                cout << cptNbSimus << "\t";
                double sum = 0;
                for(int j = 0; j < nbBigExp(); ++j){
                   sum += getCoefficient(j);
                }
                cout << sum;
                for(int j = 0; j < nbBigExp(); ++j){
                    cout << "\t" << getCoefficient(j);
                }
                cout << endl;
                if((pol == ST_MAX) || (pol == ST_MAX_EVOL)){
                    for(int j = 0; j < nbBigExp(); ++j){
                        cout << "\t" << fakeCostsForTests[j];
                    }
                    cout << endl;
                }
            }
        }
        testMode = false;
        subExpsToConsider = saveSubExps;
        cptNbSimus = 0;
    }

    string MultiExpThs::print(){
        stringstream res;
        res << " ================== politics = " << politicalName(pol) << " =============== " << endl;
        res << "Experiments being considered in the optimization : " << endl;
        int NEC = subExpsToConsider.size();
        for(int j = 0; j < NEC; ++j){
            res << subExpsToConsider[j] << "\t" << getExperiment(subExpsToConsider[j])->Identification << endl;
        }
        return res.str();
    }
*/



// enum localListExps {ECANO, EFROMTH1, EFROMTH2, EFROMITREG, EFROMTH17, EFROMTH0, ETOTH1, ETOTH2, ETOITREG, ETOTH17, ETOTH0, NBMULTIEXPS};
/*
void MultiObjective(int nb,string chosenConfig, string newParameterSet){
    if(nb < 0){
        cout << "MultiObjective Optimization (20 hours) " << endl;
        cout << "Options/scripts : " << endl;
        cout << "0- : Multi-objective using the sum of experiments cost " << endl;
        cout << "0:     Exp=Cano,                   Pol=ST_SUM" << endl;
        cout << "1:     Exp=ToTh2,                  Pol=ST_SUM" << endl;
        cout << "2:     Exp=FromTh2,                Pol=ST_SUM" << endl;
        cout << "3:     Exp=ToTh2 & FromTh2,        Pol=ST_SUM" << endl;
        cout << "4:     Exp=ToiTreg                 Pol=ST_SUM" << endl;
        cout << "5:     Exp=FromiTreg,              Pol=ST_SUM" << endl;
        cout << "6:     Exp=ToiTreg & From iTreg,   Pol=ST_SUM" << endl;
        cout << "7:     Exp=ToTh17,                 Pol=ST_SUM" << endl;
        cout << "8:     Exp=FromTh17,               Pol=ST_SUM" << endl;
        cout << "9:     Exp=ToTh17 & FromTh17,      Pol=ST_SUM" << endl;

        cout << "10- : Multi-objective using random weights between experiment costs (sum one) " << endl;
        cout << "10:     Exp=Cano,                   Pol=ST_RANDOM_EQUAL" << endl;
        cout << "11:     Exp=ToTh2,                  Pol=ST_RANDOM_EQUAL" << endl;
        cout << "12:     Exp=FromTh2,                Pol=ST_RANDOM_EQUAL" << endl;
        cout << "13:     Exp=ToTh2 & FromTh2,        Pol=ST_RANDOM_EQUAL" << endl;
        cout << "14:     Exp=ToiTreg                 Pol=ST_RANDOM_EQUAL" << endl;
        cout << "15:     Exp=FromiTreg,              Pol=ST_RANDOM_EQUAL" << endl;
        cout << "16:     Exp=ToiTreg & From iTreg,   Pol=ST_RANDOM_EQUAL" << endl;
        cout << "17:     Exp=ToTh17,                 Pol=ST_RANDOM_EQUAL" << endl;
        cout << "18:     Exp=FromTh17,               Pol=ST_RANDOM_EQUAL" << endl;
        cout << "19:     Exp=ToTh17 & FromTh17,      Pol=ST_RANDOM_EQUAL" << endl;

        cout << "20- : Multi-objective using random (unequal) weights between experiment costs (sum one) " << endl;
        cout << "20:     Exp=Cano,                   Pol=ST_RANDOM_UNEQUAL" << endl;
        cout << "21:     Exp=ToTh2,                  Pol=ST_RANDOM_UNEQUAL" << endl;
        cout << "22:     Exp=FromTh2,                Pol=ST_RANDOM_UNEQUAL" << endl;
        cout << "23:     Exp=ToTh2 & FromTh2,        Pol=ST_RANDOM_UNEQUAL" << endl;
        cout << "24:     Exp=ToiTreg                 Pol=ST_RANDOM_UNEQUAL" << endl;
        cout << "25:     Exp=FromiTreg,              Pol=ST_RANDOM_UNEQUAL" << endl;
        cout << "26:     Exp=ToiTreg & From iTreg,   Pol=ST_RANDOM_UNEQUAL" << endl;
        cout << "27:     Exp=ToTh17,                 Pol=ST_RANDOM_UNEQUAL" << endl;
        cout << "28:     Exp=FromTh17,               Pol=ST_RANDOM_UNEQUAL" << endl;
        cout << "29:     Exp=ToTh17 & FromTh17,      Pol=ST_RANDOM_UNEQUAL" << endl;

        cout << "30- : Multi-objective using a higher (weak) weight that shift from experiment over time " << endl;
        cout << "30:     Exp=Cano,                   Pol=ST_EVOL_WEAK" << endl;
        cout << "31:     Exp=ToTh2,                  Pol=ST_EVOL_WEAK" << endl;
        cout << "32:     Exp=FromTh2,                Pol=ST_EVOL_WEAK" << endl;
        cout << "33:     Exp=ToTh2 & FromTh2,        Pol=ST_EVOL_WEAK" << endl;
        cout << "34:     Exp=ToiTreg                 Pol=ST_EVOL_WEAK" << endl;
        cout << "35:     Exp=FromiTreg,              Pol=ST_EVOL_WEAK" << endl;
        cout << "36:     Exp=ToiTreg & From iTreg,   Pol=ST_EVOL_WEAK" << endl;
        cout << "37:     Exp=ToTh17,                 Pol=ST_EVOL_WEAK" << endl;
        cout << "38:     Exp=FromTh17,               Pol=ST_EVOL_WEAK" << endl;
        cout << "39:     Exp=ToTh17 & FromTh17,      Pol=ST_EVOL_WEAK" << endl;

        cout << "40- : Multi-objective using a higher (strong) weight that shift from experiment over time " << endl;
        cout << "40:     Exp=Cano,                   Pol=ST_EVOL_STRONG" << endl;
        cout << "41:     Exp=ToTh2,                  Pol=ST_EVOL_STRONG" << endl;
        cout << "42:     Exp=FromTh2,                Pol=ST_EVOL_STRONG" << endl;
        cout << "43:     Exp=ToTh2 & FromTh2,        Pol=ST_EVOL_STRONG" << endl;
        cout << "44:     Exp=ToiTreg                 Pol=ST_EVOL_STRONG" << endl;
        cout << "45:     Exp=FromiTreg,              Pol=ST_EVOL_STRONG" << endl;
        cout << "46:     Exp=ToiTreg & From iTreg,   Pol=ST_EVOL_STRONG" << endl;
        cout << "47:     Exp=ToTh17,                 Pol=ST_EVOL_STRONG" << endl;
        cout << "48:     Exp=FromTh17,               Pol=ST_EVOL_STRONG" << endl;
        cout << "49:     Exp=ToTh17 & FromTh17,      Pol=ST_EVOL_STRONG" << endl;

        cout << "50- : Multi-objective with a higher weight on an experiment, shifting randomly over time " << endl;
        cout << "50:     Exp=Cano,                   Pol=ST_OSCILL" << endl;
        cout << "51:     Exp=ToTh2,                  Pol=ST_OSCILL" << endl;
        cout << "52:     Exp=FromTh2,                Pol=ST_OSCILL" << endl;
        cout << "53:     Exp=ToTh2 & FromTh2,        Pol=ST_OSCILL" << endl;
        cout << "54:     Exp=ToiTreg                 Pol=ST_OSCILL" << endl;
        cout << "55:     Exp=FromiTreg,              Pol=ST_OSCILL" << endl;
        cout << "56:     Exp=ToiTreg & From iTreg,   Pol=ST_OSCILL" << endl;
        cout << "57:     Exp=ToTh17,                 Pol=ST_OSCILL" << endl;
        cout << "58:     Exp=FromTh17,               Pol=ST_OSCILL" << endl;
        cout << "59:     Exp=ToTh17 & FromTh17,      Pol=ST_OSCILL" << endl;

        cout << "60- : Multi-objective, optimizing the worst of the considered experiments" << endl;
        cout << "60:     Exp=Cano,                   Pol=ST_MAX" << endl;
        cout << "61:     Exp=ToTh2,                  Pol=ST_MAX" << endl;
        cout << "62:     Exp=FromTh2,                Pol=ST_MAX" << endl;
        cout << "63:     Exp=ToTh2 & FromTh2,        Pol=ST_MAX" << endl;
        cout << "64:     Exp=ToiTreg                 Pol=ST_MAX" << endl;
        cout << "65:     Exp=FromiTreg,              Pol=ST_MAX" << endl;
        cout << "66:     Exp=ToiTreg & From iTreg,   Pol=ST_MAX" << endl;
        cout << "67:     Exp=ToTh17,                 Pol=ST_MAX" << endl;
        cout << "68:     Exp=FromTh17,               Pol=ST_MAX" << endl;
        cout << "69:     Exp=ToTh17 & FromTh17,      Pol=ST_MAX" << endl;

        cout << "70- : Multi-objective, optimizing the worst of an increasing subset of the considered experiments" << endl;
        cout << "70:     Exp=Cano,                   Pol=ST_MAX_EVOL" << endl;
        cout << "71:     Exp=ToTh2,                  Pol=ST_MAX_EVOL" << endl;
        cout << "72:     Exp=FromTh2,                Pol=ST_MAX_EVOL" << endl;
        cout << "73:     Exp=ToTh2 & FromTh2,        Pol=ST_MAX_EVOL" << endl;
        cout << "74:     Exp=ToiTreg                 Pol=ST_MAX_EVOL" << endl;
        cout << "75:     Exp=FromiTreg,              Pol=ST_MAX_EVOL" << endl;
        cout << "76:     Exp=ToiTreg & From iTreg,   Pol=ST_MAX_EVOL" << endl;
        cout << "77:     Exp=ToTh17,                 Pol=ST_MAX_EVOL" << endl;
        cout << "78:     Exp=FromTh17,               Pol=ST_MAX_EVOL" << endl;
        cout << "79:     Exp=ToTh17 & FromTh17,      Pol=ST_MAX_EVOL" << endl;

    }
    cout << "launching Multiobjective, with script nr " << nb << endl;

    stringstream buildfolder; buildfolder << folderBaseResults << string("multiObj20hrs") << nb << "-at-" << codeTime() + string("/");
    string folderRes = buildfolder.str();
    createFolder(folderRes);

    Modele* currentModel = new modeleLatentTbet2();
    MultiExpThs* ME = new MultiExpThs(currentModel);

    string configFile;
    switch (nb % 10){
        case 0: {configFile = folder + string("BestConfigPlusFitte20hrs.txt"); break;}
        case 1: case 2: case 3: {configFile = folder + string("BestConfigPlusFitte20hrsForTh2.txt"); break;}
        case 4: case 5: case 6: {configFile = folder + string("BestConfigPlusFitte20hrsForiTreg.txt"); break;}
        case 7: case 8: case 9: {configFile = folder + string("BestConfigPlusFitte20hrsForTh17.txt"); break;}
    }

    ME->considerExp(ECANO);
    switch (nb % 10){
        case 0:{ break;}        // negative control
        case 1:{ ME->considerExp(ETOTH2); break;}
        case 2:{ ME->considerExp(EFROMTH2); break;}
        case 3:{ ME->considerExp(ETOTH2); ME->considerExp(EFROMTH2); break;}
        case 4:{ ME->considerExp(ETOITREG); break;}
        case 5:{ ME->considerExp(EFROMITREG); break;}
        case 6:{ ME->considerExp(ETOITREG); ME->considerExp(EFROMITREG); break;}
        case 7:{ ME->considerExp(ETOTH17); break;}
        case 8:{ ME->considerExp(EFROMTH17); break;}
        case 9:{ ME->considerExp(ETOTH17); ME->considerExp(EFROMTH17); break;}
    }
    switch(nb / 10){
        case 0:{ ME->setPolitics(ST_SUM); break;}
        case 1:{ ME->setPolitics(ST_RANDOM_EQUAL); break;}
        case 2:{ ME->setPolitics(ST_RANDOM_UNEQUAL); break;}
        case 3:{ ME->setPolitics(ST_EVOL_WEAK); break;}
        case 4:{ ME->setPolitics(ST_EVOL_STRONG); break;}
        case 5:{ ME->setPolitics(ST_OSCILL); break;}
        case 6:{ ME->setPolitics(ST_MAX); break;}
        case 7:{ ME->setPolitics(ST_MAX_EVOL); break;}
    }

    if(chosenConfig.size() > 0) configFile = chosenConfig;
    cout << "   -> Using model : " << currentModel->name << " for multiobjective optimization\n   -> performing script nr(" << nb << ")\n";
    if(chosenConfig.length() > 0)   cout << "      ... with configuration (" << chosenConfig << ")" << endl;
    if(newParameterSet.length() > 0) cout << "      ... with parameter set (" << newParameterSet << ")" << endl;
    if(newParameterSet.size() > 0) currentModel->loadParameters(newParameterSet);
    cout << "   -> using politics : " << politicalName(ME->pol) << endl;
    cout << "   -> considering experiments : " << endl;
    cout << ME->print() << endl;

    // --------------------- If no script, do manual simulations with the graphical interface ----------------------

    if(nb < 0){
        #ifndef WITHOUT_QT
        simuWin* p = new simuWin((MultiExperiments*) ME);
        for(int i = 0; i < NBMULTIEXPS; ++i){
            ME->considerExp(i);
        }
        cout << "Launch GUI ..." << endl;
        configFile = folder + string("BestConfigPlusFitte20hrs.txt");
        p->loadConfig(configFile);
        p->show();
        #else
        cout << "Script finished (without qt, because WITHOUR_QT was defined)\n";
        #endif
        return;
    }

    // =============== Optimization options ... ================

    stringstream headerOptimizer;
    if(TESTINGMODE) headerOptimizer << optFileHeader(GeneticFast);
    else headerOptimizer << optFileHeader(Genetic100k);
    */
    /*cerr << optFileHeader(Genetic500k) << endl;

    bool TESTE_ALL_CROSSMUT = false;
                                                      // each further script might use different optimizer options, will be stored in the following stringstream
    headerOptimizer << "geneticAlgorithm	14\n";
    headerOptimizer << (TESTE_ALL_CROSSMUT ? "10         #CEP  - All Mut&Cross\n" : "0	#CEP  - Classical Evolutionary Programming\n");
    headerOptimizer << "8          #Proportional / From Worst / Basic Sampling\n";
    headerOptimizer << "7	1      #SBX Cross-Over\n";
    headerOptimizer << "1          #Mutation normal all points\n";
    headerOptimizer << "0          #NO_NEED_REPLACEMENT\n";
    headerOptimizer << "0          #Select Best\n";
    headerOptimizer << "7	0.005	#MUTATIVE_SEPARATED\n";
    headerOptimizer << "1      #Nb Repeats\n";
    headerOptimizer << "500000	#Max nb of simulations-costs\n";
    headerOptimizer << "250	#Population Size\n";
    headerOptimizer << "0.2	#Proportion of CrossOver (vs offspring) in new individuals\n";
    headerOptimizer << "0.5	#Fork coeff (%renewed each generation)\n";//


    manageSims* msi = new manageSims(ME);        // manageSims is the class to perform optimizations/other things without graphical interface. simuWin is the extension with graphical interface.
    msi->loadConfig(configFile);                       // Now, loads a list of configurations (parameters + variables) to optimize, and optimizes them one by one
    vector<string> listGeneratedFilesSets;                      // will store the files with parameter sets that to re-load them later

    // ----------------- Part 1 : for each combination (parameters-variables), do a fitting -----------------------

    for(int i = 0; i < msi->nbCombs; ++i){

        stringstream codeSimu;      codeSimu << "CombNr" << i << "-" << codeTime();               // generates a text code for this particular optimization, in case parallel optimizations are running
        stringstream folderComb;    folderComb << folderRes << codeSimu.str() << "/";        // creates a folder for this particular optimization, to create figures etc ...
        createFolder(folderComb.str());

        cout << "   -> Optimizing combination (" << i << ") with ID: " << codeSimu.str() << "\n";

        // re-takes the initial parameter set because parameters were probably changed by previous optimization for parameters that will not necessarily be optimized/modified in the next combinations
        msi->resetParamSetFromConfig(configFile);

        // set options of simulation : dt initial = 10 sec, and no recording of regular kinetics (just recording of evaluators). Need to be done each time because simuWin->makeReports, etc will change the dt and will generate kinetics with its own dt in order to make plots
        currentModel->setPrintMode(false, 5000);
        currentModel->dt = 10;

        // creates the optimizer file for the combination of parameters to optimize, using boundaries from the configuration file, and the header from headeroptimizer
        string optOptions = msi->motherCreateOptimizerFile(i, headerOptimizer.str());       // for each combination, will need to re-create an optimizer file
        ofstream f1((folderComb.str() + string("Optimizer.txt")).c_str(), ios::out); if(f1) {f1 << optOptions << "\n"; f1.close();}

        // Optimize (using the data stated by this combination) !
        msi->motherOverrideUsingComb(i);                                                    // chose the variables to simulate and to replace by data according to this combination
        msi->motherOptimize(folderComb.str() + string("Optimizer.txt"), 1000);              // DOES THE OPTIMIZATION !!!, and records the 1000 best sets

        // saves the best sets of parameters
        msi->saveHistory(folderComb.str() + string("History.txt"));                         // SAVES all the best parameter sets. by default, 10 000, can be modified by             msi->history.resize(max_nb_sets_to_record);
        listGeneratedFilesSets.push_back(folderComb.str() + string("History.txt"));         // list[i] = historyFile for comb i

        // if QT allowed, generates the plots for this best set
        #ifndef WITHOUT_QT
        simuWin tempWindow(ME);   // funny, if in non pointer with simuWin tw = simuWin(currentExperiment), get a compiling error 'use of deleted function' ...
        tempWindow.loadHistory(QString((folderComb.str() + string("History.txt")).c_str()));
        tempWindow.useParamSetFromHistory(0);                                                     // takes the first set of parameters (the best), also possible to use msi->useParamSetFromHistory(0, i); for overriding only parameters from this combination,
        tempWindow.simulate();
        tempWindow.makeFigReportParamSet(folderComb.str());
        //ofstream f2((folderComb.str() + string("FitnessBestSetOf") + codeSimu.str() + string(".txt")).c_str(), ios::out); if(f2) {f2 << currentExperiment->costReport() << "\n"; f2.close();}
        ofstream f3((folderComb.str() + string("CostEvolutionDuringOptimization") + codeSimu.str() + string(".txt")).c_str(), ios::out); if(f3) {f3 << tempWindow.costRecords.print() << "\n"; f3.close();}
        #else
        msi->useParamSetFromHistory(0);                                                     // takes the first set of parameters (the best), also possible to use msi->useParamSetFromHistory(0, i); for overriding only parameters from this combination,
        msi->simulate();
        ofstream f2((folderComb.str() + string("FitnessBestSetOf") + codeSimu.str() + string(".txt")).c_str(), ios::out); if(f2) {f2 << currentExperiment->costReport() << "\n"; f2.close();}
        ofstream f3((folderComb.str() + string("CostEvolutionDuringOptimization.txt") + codeSimu.str()).c_str(), ios::out); if(f3) {f3 << msi->costRecords.print() << "\n"; f3.close();}
        #endif
    }


    cout << "   -> Script 20 hrs perturbations " << nb << " finished !\n   _____________________________________________________________\n";
    return;
}
*/











/*

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
///
///
///         4 - Script to do fittings with all the 20 hours perturbation experiments at the same time.
///
///
///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void scriptsWith20HoursExp(int nb,string chosenConfig, string newParameterSet){
    if(nb < 0){cout << "Scripts for 20 hours experiment " << endl;}
    cout << "launching Experiment 20 hours, with script nr " << nb << endl;

    string folderRes = folderBaseResults + string("sim20Hours") + codeTime() + string("/");
    createFolder(folderRes);

    string configFile;
    Modele* currentModel = new modeleLatentTbet2();
    Experiment* currentExperiment = NULL;
    configFile = folder + string("BestConfigPlusFitte20hrs.txt");
    if(chosenConfig.size() > 0) configFile = chosenConfig;
    currentExperiment = new exp20Hours(currentModel, 20);
    cout << "   -> Using model : " << currentModel->name << " for canonical differentiation\n   -> performing script nr(" << nb << ")\n";
    if(chosenConfig.length() > 0)   cout << "      ... with configuration (" << chosenConfig << ")" << endl;
    if(newParameterSet.length() > 0) cout << "      ... with parameter set (" << newParameterSet << ")" << endl;
    if(newParameterSet.size() > 0) currentModel->loadParameters(newParameterSet);

    // --------------------- Reading the data for all experiments with perturbation at 20 hours ----------------------

    TableCourse* AToTh1   = new TableCourse(folder + string("DATA/Th1ToTh1.txt"));
    TableCourse* AToTh2   = new TableCourse(folder + string("DATA/Th1ToTh2.txt"));
    TableCourse* AToiTreg = new TableCourse(folder + string("DATA/Th1ToTreg.txt"));
    TableCourse* AToTh17  = new TableCourse(folder + string("DATA/Th1ToTh17.txt"));
    TableCourse* AToTh0   = new TableCourse(folder + string("DATA/Th1ToTh0.txt"));
    TableCourse* AUntouched   = new TableCourse(folder + string("KineticsTh1.txt")); //new TableCourse(folder + string("DATA/Th1Untouched.txt"));
    TableCourse* BToTh1   = new TableCourse(folder + string("DATA/Th2ToTh1.txt"));
    TableCourse* BToTh2   = new TableCourse(folder + string("DATA/Th2ToTh2.txt"));
    TableCourse* BToiTreg = new TableCourse(folder + string("DATA/Th2ToTreg.txt"));
    TableCourse* BToTh17  = new TableCourse(folder + string("DATA/Th2ToTh17.txt"));
    TableCourse* BToTh0   = new TableCourse(folder + string("DATA/Th2ToTh0.txt"));
    TableCourse* BUntouched   = new TableCourse(folder + string("KineticsTh2.txt")); //new TableCourse(folder + string("DATA/Th2Untouched.txt"));
    TableCourse* CToTh1   = new TableCourse(folder + string("DATA/TregToTh1.txt"));
    TableCourse* CToTh2   = new TableCourse(folder + string("DATA/TregToTh2.txt"));
    TableCourse* CToiTreg = new TableCourse(folder + string("DATA/TregToTreg.txt"));
    TableCourse* CToTh17  = new TableCourse(folder + string("DATA/TregToTh17.txt"));
    TableCourse* CToTh0   = new TableCourse(folder + string("DATA/TregToTh0.txt"));
    TableCourse* CUntouched   = new TableCourse(folder + string("KineticsiTreg.txt")); //new TableCourse(folder + string("DATA/TregUntouched.txt"));
    TableCourse* DToTh1   = new TableCourse(folder + string("DATA/Th17ToTh1.txt"));
    TableCourse* DToTh2   = new TableCourse(folder + string("DATA/Th17ToTh2.txt"));
    TableCourse* DToiTreg = new TableCourse(folder + string("DATA/Th17ToTreg.txt"));
    TableCourse* DToTh17  = new TableCourse(folder + string("DATA/Th17ToTh17.txt"));
    TableCourse* DToTh0   = new TableCourse(folder + string("DATA/Th17ToTh0.txt"));
    TableCourse* DUntouched   = new TableCourse(folder + string("KineticsTh17.txt")); //new TableCourse(folder + string("DATA/Th17Untouched.txt"));
    TableCourse* EToTh1   = new TableCourse(folder + string("DATA/Th0ToTh1.txt"));
    TableCourse* EToTh2   = new TableCourse(folder + string("DATA/Th0ToTh2.txt"));
    TableCourse* EToiTreg = new TableCourse(folder + string("DATA/Th0ToTreg.txt"));
    TableCourse* EToTh17  = new TableCourse(folder + string("DATA/Th0ToTh17.txt"));
    //TableCourse* EToTh0   = new TableCourse(folder + string("DATA/Th0ToTh0.txt")); // no data for it
    TableCourse* EUntouched   = new TableCourse(folder + string("KineticsTh0.txt")); //new TableCourse(folder + string("DATA/Th0Untouched.txt"));
    // for later, no experiment line yet inside the experiment
    TableCourse* TTh1   = new TableCourse(folder + string("KineticsTh1.txt"));
    TableCourse* TTh2   = new TableCourse(folder + string("KineticsTh2.txt"));
    TableCourse* TiTreg = new TableCourse(folder + string("KineticsiTreg.txt"));
    TableCourse* TTh17  = new TableCourse(folder + string("KineticsTh17.txt"));
    TableCourse* TTh0   = new TableCourse(folder + string("KineticsTh0.txt"));

    // --------------------- Gives data points (for evaluating cost function / fitting)  ----------------------

    currentExperiment->giveData(AToTh1,      TH1_TO_TH1);
    currentExperiment->giveData(AToTh2,      TH1_TO_TH2);
    currentExperiment->giveData(AToiTreg,    TH1_TO_ITREG);
    currentExperiment->giveData(AToTh17,     TH1_TO_TH17);
    currentExperiment->giveData(AToTh0,      TH1_TO_TH0);
    currentExperiment->giveData(AUntouched,  TH1_UNTOUCHED);
    currentExperiment->giveData(BToTh1,      6+TH2_TO_TH1);
    currentExperiment->giveData(BToTh2,      6+TH2_TO_TH2);
    currentExperiment->giveData(BToiTreg,    6+TH2_TO_ITREG);
    currentExperiment->giveData(BToTh17,     6+TH2_TO_TH17);
    currentExperiment->giveData(BToTh0,      6+TH2_TO_TH0);
    currentExperiment->giveData(BUntouched,  6+TH2_UNTOUCHED);
    currentExperiment->giveData(CToTh1,      12+ITREG_TO_TH1);
    currentExperiment->giveData(CToTh2,      12+ITREG_TO_TH2);
    currentExperiment->giveData(CToiTreg,    12+ITREG_TO_ITREG);
    currentExperiment->giveData(CToTh17,     12+ITREG_TO_TH17);
    currentExperiment->giveData(CToTh0,      12+ITREG_TO_TH0);
    currentExperiment->giveData(CUntouched,  12+ITREG_UNTOUCHED);
    currentExperiment->giveData(DToTh1,      18+TH17_TO_TH1);
    currentExperiment->giveData(DToTh2,      18+TH17_TO_TH2);
    currentExperiment->giveData(DToiTreg,    18+TH17_TO_ITREG);
    currentExperiment->giveData(DToTh17,     18+TH17_TO_TH17);
    currentExperiment->giveData(DToTh0,      18+TH17_TO_TH0);
    currentExperiment->giveData(DUntouched,  18+TH17_UNTOUCHED);
    currentExperiment->giveData(EToTh1,      24+TH0_TO_TH1);
    currentExperiment->giveData(EToTh2,      24+TH0_TO_TH2);
    currentExperiment->giveData(EToiTreg,    24+TH0_TO_ITREG);
    currentExperiment->giveData(EToTh17,     24+TH0_TO_TH17);
    //currentExperiment->giveData(EToTh0,    24+TH0_TO_TH0);
    currentExperiment->giveData(EUntouched,  24+TH0_UNTOUCHED);

    // --------------------- Now processes the data and makes the list of time-points to compare with simulations ----------------------

    vector<string> GlobalNamesVariables = getGlobalNames();
    currentExperiment->giveHowToReadNamesInKinetics(GlobalNamesVariables);
    currentExperiment->loadEvaluators();    // => Now, can run simulations and compare with data



    // --------------------- Creates overriders to interpolate the data ----------------------

    bool useSplines = false;                                                            // false = linear interpolation, true = cubic splines
    overrider* OverAToTh1 = new overrider();                                               // Note : never create overrider as a non pointer, to be used by the graphical interface because they will be erased when function closes and gives control to the interface --> use a pointer and new ...
    overrider* OverAToTh2 = new overrider();
    overrider* OverAToiTreg = new overrider();
    overrider* OverAToTh17 = new overrider();
    overrider* OverAToTh0 = new overrider();
    overrider* OverAUnt = new overrider();
    overrider* OverBToTh1 = new overrider();
    overrider* OverBToTh2 = new overrider();
    overrider* OverBToiTreg = new overrider();
    overrider* OverBToTh17 = new overrider();
    overrider* OverBToTh0 = new overrider();
    overrider* OverBUnt = new overrider();
    overrider* OverCToTh1 = new overrider();
    overrider* OverCToTh2 = new overrider();
    overrider* OverCToiTreg = new overrider();
    overrider* OverCToTh17 = new overrider();
    overrider* OverCToTh0 = new overrider();
    overrider* OverCUnt = new overrider();
    overrider* OverDToTh1 = new overrider();
    overrider* OverDToTh2 = new overrider();
    overrider* OverDToiTreg = new overrider();
    overrider* OverDToTh17 = new overrider();
    overrider* OverDToTh0 = new overrider();
    overrider* OverDUnt = new overrider();
    overrider* OverEToTh1 = new overrider();
    overrider* OverEToTh2 = new overrider();
    overrider* OverEToiTreg = new overrider();
    overrider* OverEToTh17 = new overrider();
    //overrider* OverEToTh0 = new overrider();
    overrider* OverEUnt = new overrider();
    overrider* OverTh1 = new overrider();
    overrider* OverTh2 = new overrider();
    overrider* OveriTreg = new overrider();
    overrider* OverTh17 = new overrider();
    overrider* OverTh0 = new overrider();

    // --------------------- Do the interpolation : each overrider learns from a table course ----------------------

    vector<TableCourse*> kinetics = {AToTh1, AToTh2, AToiTreg, AToTh17, AToTh0, AUntouched,                     BToTh1, BToTh2, BToiTreg, BToTh17, BToTh0, BUntouched,                      CToTh1, CToTh2, CToiTreg, CToTh17, CToTh0, CUntouched,                      DToTh1, DToTh2, DToiTreg, DToTh17, DToTh0, DUntouched, EToTh1, EToTh2, EToiTreg, EToTh17, EUntouched, TTh1, TTh2, TiTreg, TTh17, TTh0};
    vector<overrider*> overs =      {OverAToTh1, OverAToTh2, OverAToiTreg, OverAToTh17, OverAToTh0, OverAUnt,   OverBToTh1, OverBToTh2, OverBToiTreg, OverBToTh17, OverBToTh0, OverBUnt,    OverCToTh1, OverCToTh2, OverCToiTreg, OverCToTh17, OverCToTh0, OverCUnt,    OverDToTh1, OverDToTh2, OverDToiTreg, OverDToTh17, OverDToTh0, OverDUnt, OverEToTh1, OverEToTh2, OverEToiTreg, OverEToTh17, OverEUnt, OverTh1, OverTh2, OveriTreg, OverTh17, OverTh0};        // saves the overriders and kinetics in a vector so it is easy to get them in a loop by kinetics[i] ...
    int nbDataSets = overs.size();

    for(int ne = 0; ne < nbDataSets; ++ne){                                             //  converts the name of variables (ex : 'gIL2') into their global index (ex: N::IL2)
        for(int i = 0; i < kinetics[ne]->nbVar; ++i){
            string ss = kinetics[ne]->headers[i+1];     // header of this variable

            // converting 'name in kinetics file ("gIL2", ...) --> index of variable (index = N::IL2 in the enum)' ======
            int GlobName = -1;
            for(int j = 0; j < (int) GlobalNamesVariables.size(); ++j){
                if(!GlobalNamesVariables[j].compare(ss)) GlobName = j;
            }

            // giving the data to overriders for interpolation (splines or linear) ======
            if(GlobName > -1){
                overs[ne]->learnSpl(GlobName,kinetics[ne]->getTimePoints(), kinetics[ne]->getTimeCourse(i), useSplines);
            } else cout << "Variable " << ss << " not found in the kinetics\n";
        }
    }

    // --------------------- Now give the overriders to the currentExperiment (associates each curve with an overrider) ----------------------

    currentExperiment->setOverrider(TH1_TO_TH1,OverAToTh1);
    currentExperiment->setOverrider(TH1_TO_TH2,OverAToTh2);
    currentExperiment->setOverrider( TH1_TO_ITREG,OverAToiTreg);
    currentExperiment->setOverrider(TH1_TO_TH17,OverAToTh17);
    currentExperiment->setOverrider(TH1_TO_TH0,OverAToTh0);
    currentExperiment->setOverrider(TH1_UNTOUCHED,OverAUnt);
    currentExperiment->setOverrider(6+TH2_TO_TH1,OverBToTh1);
    currentExperiment->setOverrider(6+TH2_TO_TH2,OverBToTh2);
    currentExperiment->setOverrider(6+TH2_TO_ITREG,OverBToiTreg);
    currentExperiment->setOverrider(6+TH2_TO_TH17,OverBToTh17);
    currentExperiment->setOverrider(6+TH2_TO_TH0,OverBToTh0);
    currentExperiment->setOverrider(6+TH2_UNTOUCHED,OverBUnt);
    currentExperiment->setOverrider(12+ITREG_TO_TH1,OverCToTh1);
    currentExperiment->setOverrider(12+ITREG_TO_TH2,OverCToTh2);
    currentExperiment->setOverrider(12+ITREG_TO_ITREG,OverCToiTreg);
    currentExperiment->setOverrider(12+ITREG_TO_TH17,OverCToTh17);
    currentExperiment->setOverrider(12+ITREG_TO_TH0,OverCToTh0);
    currentExperiment->setOverrider(12+ITREG_UNTOUCHED,OverCUnt);
    currentExperiment->setOverrider(18+TH17_TO_TH1,OverDToTh1);
    currentExperiment->setOverrider(18+TH17_TO_TH2,OverDToTh2);
    currentExperiment->setOverrider(18+TH17_TO_ITREG,OverDToiTreg);
    currentExperiment->setOverrider(18+TH17_TO_TH17,OverDToTh17);
    currentExperiment->setOverrider(18+TH17_TO_TH0,OverDToTh0);
    currentExperiment->setOverrider(18+TH17_UNTOUCHED,OverDUnt);
    currentExperiment->setOverrider(24+TH0_TO_TH1,OverEToTh1);
    currentExperiment->setOverrider(24+TH0_TO_TH2,OverEToTh2);
    currentExperiment->setOverrider(24+TH0_TO_ITREG,OverEToiTreg);
    currentExperiment->setOverrider(24+TH0_TO_TH17,OverEToTh17);
    //currentExperiment->setOverrider(24+TH0_TO_TH0 ,OverEToTh0);
    currentExperiment->setOverrider(24+TH0_TO_TH0 ,OverEUnt);    /// I know, this is cheating, but need all the experiments to have an overrider ...
    currentExperiment->setOverrider(24+TH0_UNTOUCHED ,OverEUnt);


    // --------------------- If no script, do manual simulations with the graphical interface ----------------------

    if(nb < 0){
        #ifndef WITHOUT_QT
        simuWin* p = new simuWin(currentExperiment);
        cout << "Launch GUI ..." << endl;
        p->loadConfig(configFile);
        p->show();
        #else
        cout << "Script finished (without qt, because WITHOUR_QT was defined)\n";
        #endif
        return;
    }



    // =============== Optimization options ... ================

    stringstream headerOptimizer;
    if(TESTINGMODE) headerOptimizer << optFileHeader(GeneticFast);
    else headerOptimizer << optFileHeader(Genetic500k);



    /// note : in the first scripts,, check that there is no confusion between configfile and folder + configfile
    switch(nb){
    case 0: {
        manageSims* msi = new manageSims(currentExperiment);        // manageSims is the class to perform optimizations/other things without graphical interface. simuWin is the extension with graphical interface.
        msi->loadConfig(configFile);                       // Now, loads a list of configurations (parameters + variables) to optimize, and optimizes them one by one
        vector<string> listGeneratedFilesSets;                      // will store the files with parameter sets that to re-load them later

        // ----------------- Part 1 : for each combination (parameters-variables), do a fitting -----------------------

        for(int i = 0; i < msi->nbCombs; ++i){

            stringstream codeSimu;      codeSimu << "CombNr" << i << "-" << codeTime();               // generates a text code for this particular optimization, in case parallel optimizations are running
            stringstream folderComb;    folderComb << folderRes << codeSimu.str() << "/";        // creates a folder for this particular optimization, to create figures etc ...
            createFolder(folderComb.str());

            cout << "   -> Optimizing combination (" << i << ") with ID: " << codeSimu.str() << "\n";

            // re-takes the initial parameter set because parameters were probably changed by previous optimization for parameters that will not necessarily be optimized/modified in the next combinations
            msi->resetParamSetFromConfig(configFile);

            // set options of simulation : dt initial = 10 sec, and no recording of regular kinetics (just recording of evaluators). Need to be done each time because simuWin->makeReports, etc will change the dt and will generate kinetics with its own dt in order to make plots
            currentExperiment->m->setPrintMode(false, 5000);
            currentExperiment->m->dt = 10;

            // creates the optimizer file for the combination of parameters to optimize, using boundaries from the configuration file, and the header from headeroptimizer
            string optOptions = msi->motherCreateOptimizerFile(i, headerOptimizer.str());       // for each combination, will need to re-create an optimizer file
            ofstream f1((folderComb.str() + string("Optimizer.txt")).c_str(), ios::out); if(f1) {f1 << optOptions << "\n"; f1.close();}

            // Optimize (using the data stated by this combination) !
            msi->motherOverrideUsingComb(i);                                                    // chose the variables to simulate and to replace by data according to this combination
            msi->motherOptimize(folderComb.str() + string("Optimizer.txt"), 1000);              // DOES THE OPTIMIZATION !!!, and records the 1000 best sets

            // saves the best sets of parameters
            msi->saveHistory(folderComb.str() + string("History.txt"));                         // SAVES all the best parameter sets. by default, 10 000, can be modified by             msi->history.resize(max_nb_sets_to_record);
            listGeneratedFilesSets.push_back(folderComb.str() + string("History.txt"));         // list[i] = historyFile for comb i

            // if QT allowed, generates the plots for this best set
            #ifndef WITHOUT_QT
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
        break;
    }
    } // end switch
    cout << "   -> Script 20 hrs perturbations " << nb << " finished !\n   _____________________________________________________________\n";
    return;
}
*/
































//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
///
///
///         5 - Tool functions
///
///
///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




void mergePDFs(vector<string> & listFiles, string outputFile){
    cout << "=> Merging files into one PDF ...\n";
    ofstream st(outputFile, ios::out);
    st << "\\documentclass{article}% or something else\n";
    st << "\\usepackage{pdfpages}\n";
    st << "\\begin{document}\n";
    for(int kf = 0; kf < (int) listFiles.size(); ++kf){
        st << "\\includepdf[pages=-]{" << listFiles[kf] << "}\n";
    }
    st << "\\end{document}\n";
    st.close();
    compileLatex(folderBaseResults, outputFile);
}

string textFileForFolder(string explanations){
    replace( explanations.begin(), explanations.end(), '_', '-');
    static int count = 0;
    string picOpt = string("height=1.4in");
    stringstream st;
    st << "\\documentclass[10pt,a4paper,final]{article}\n";
    st << "\\usepackage[utf8]{inputenc}\n";
    st << "\\usepackage{amsmath}\n";
    st << "\\usepackage{amsfonts}\n";
    st << "\\usepackage{amssymb}\n";
    st << "\\usepackage{graphicx}\n";
    st << "\\usepackage{caption}\n";
    st << "\\usepackage{subcaption}\n";
    //st << "\\usepackage[dvips]{epsfig, graphicx, color}\n";
    st << "\\usepackage[left=1.5cm,right=1.5cm,top=1.5cm,bottom=1.5cm]{geometry}\n";
    //st << "\\title{How to simulate a Germinal Centre}\n";
    //st << "\\date{\vspace{-5ex}}\n";
    //st << "\\usepackage[charter]{mathdesign}\n"; // not installed in brics
    st << "\\begin{document}\n";
    st << "\\setcounter{figure}{" << count << "}\n";

    //st << explanations << endl;
    /*st << "\\begin{figure}[]\n";
    st << "\\begin{center}\n";
    st << "\\begin{subfigure}[b]{0.45\\textwidth}\n";
    st << "\\includegraphics[" << picOpt << "]{Unsim-TBET.png}\n";
    st << "\\end{subfigure}\n";
    st << "\\begin{subfigure}[b]{0.45\\textwidth}\n";
    st << "\\includegraphics[" << picOpt << "]{Unsim-TBETmRNA.png}\n";
    st << "\\end{subfigure}\n";
    st << "\\begin{subfigure}[b]{0.45\\textwidth}\n";
    st << "\\includegraphics[" << picOpt << "]{Unsim-GATA3.png}\n";
    st << "\\end{subfigure}\n";
    st << "\\begin{subfigure}[b]{0.45\\textwidth}\n";
    st << "\\includegraphics[" << picOpt << "]{Unsim-GATA3mRNA.png}\n";
    st << "\\end{subfigure}\n";
    st << "\\begin{subfigure}[b]{0.45\\textwidth}\n";
    st << "\\includegraphics[" << picOpt << "]{Unsim-FOXP3.png}\n";
    st << "\\end{subfigure}\n";
    st << "\\begin{subfigure}[b]{0.45\\textwidth}\n";
    st << "\\includegraphics[" << picOpt << "]{Unsim-FOXP3mRNA.png}\n";
    st << "\\end{subfigure}\n";
    st << "\\begin{subfigure}[b]{0.45\\textwidth}\n";
    st << "\\includegraphics[" << picOpt << "]{Unsim-RORGT.png}\n";
    st << "\\end{subfigure}\n";
    st << "\\begin{subfigure}[b]{0.45\\textwidth}\n";
    st << "\\includegraphics[" << picOpt << "]{Unsim-RORGTmRNA.png}\n";
    st << "\\end{subfigure}\n";
    st << "\\caption[]{}\n";
    st << "\\end{center}\n";
    st << "\\end{figure}\n";*/

    st << "\\begin{figure}[ht!]\n";
    //st << "\\captionsetup{labelformat=empty}\n";
    st << "\\caption{" << explanations << "}\n";
    st << "\\begin{center}\n";
    st << "\\includegraphics[" << picOpt << "]{Unsim-TBET.png}\n";
    st << "\\includegraphics[" << picOpt << "]{Unsim-GATA3.png}\n";
    st << "\\includegraphics[" << picOpt << "]{Unsim-RORGT.png}\n";
    st << "\\includegraphics[" << picOpt << "]{Unsim-TBETmRNA.png}\n";
    st << "\\includegraphics[" << picOpt << "]{Unsim-GATA3mRNA.png}\n";
    st << "\\includegraphics[" << picOpt << "]{Unsim-RORGTmRNA.png}\n";
    st << "\\includegraphics[" << picOpt << "]{Unsim-FOXP3.png}\n";
    st << "\\includegraphics[" << picOpt << "]{Unsim-IFNG.png}\n";
    st << "\\includegraphics[" << picOpt << "]{Unsim-IL4.png}\n";
    st << "\\includegraphics[" << picOpt << "]{Unsim-FOXP3mRNA.png}\n";
    st << "\\includegraphics[" << picOpt << "]{Unsim-IFNGmRNA.png}\n";
    st << "\\includegraphics[" << picOpt << "]{Unsim-IL4mRNA.png}\n";
    st << "\\includegraphics[" << picOpt << "]{Unsim-IL21.png}\n";
    st << "\\includegraphics[" << picOpt << "]{Unsim-IL17.png}\n";
    st << "\\includegraphics[" << picOpt << "]{Unsim-TGFB.png}\n";
    st << "\\includegraphics[" << picOpt << "]{Unsim-IL21mRNA.png}\n";
    st << "\\includegraphics[" << picOpt << "]{Unsim-IL17mRNA.png}\n";
    st << "\\includegraphics[" << picOpt << "]{Unsim-TGFBmRNA.png}\n";
    st << "\\includegraphics[" << picOpt << "]{Unsim-IL12.png}\n";
    //st << "\\includegraphics[" << picOpt << "]{Unsim-IL6.png}\n";
    st << "\\includegraphics[" << picOpt << "]{Unsim-IL2mRNA.png}\n";
    st << "\\includegraphics[" << picOpt << "]{Unsim-IL2.png}\n";
    st << "\\end{center}\n";
    st << "\\end{figure}\n";
    st << "\\clearpage\n";


    st << "\\end{document}\n";
    count++;
    return st.str();
}




string codeTime(){
    time_t now = time(0);
    stringstream code;
    tm *ltm = localtime(&now);
    code << ltm->tm_mday;
    code << "-"<< 1 + ltm->tm_mon;
    code << "-"<< 1900 + ltm->tm_year;
    code << "at"<< 1 + ltm->tm_hour << "-";
    code << 1 + ltm->tm_min << "-";
    code << 1 + ltm->tm_sec;
    return code.str();
}





/* ---------- Informations about a text file : --------
/home/phr13/Desktop/Restart/RV2/R1/D7 simu Tbet InitFixed.txt
// ------------------ Content of file : ---------------
151	26	23
2.5	1	10	.	1	0	0	0	0	1	1	0	0	1	0	0	0	0	0	1	0	0	0	0	0	0	0
0.005	0.0001	0.2	.	1	0	0	0	0	1	1	0	0	1	0	0	0	0	0	1	0	0	0	0	0	0	0
2500	100	10000	.	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	1	0	0	0	0	0	1	0
8500	1.1	10000	.	1	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	1	0	0	0	0	0
2000	100	10000	.	0	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	1	0	0	0
1000	1.1	10000	.	0	0	0	0	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	1	0	0
15000	1.1	20000	.	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	1	0	0	0	0
1e-05	1e-06	0.0001	.	0	0	0	0	0	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0
1e-05	1e-06	0.0001	.	0	0	0	0	0	0	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0
5e-06	1e-06	0.0001	.	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
5e-06	1e-06	0.0001	.	0	0	0	0	0	0	0	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0
1e-07	1e-07	0.0001	.	0	0	0	0	0	0	0	0	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0
1e-07	1e-07	0.0001	.	0	0	0	0	0	0	0	0	0	0	0	0	0	0	1	0	0	0	0	0	0	0	0
1e-05	1e-06	0.0001	.	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
1.5e-05	1e-05	0.0001	.	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
2e-05	1e-05	0.0001	.	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	1	0	0	0	0	0	1	0
7e-05	1e-05	0.0001	.	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	1	0	0	0	0	0	0
4.9455e-05	1e-05	0.0001	.	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	1
1.3e-05	2e-06	5e-05	.	1	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	1	0	0	0	0	0
1e-05	2e-06	5e-05	.	0	1	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
1e-05	2e-06	5e-05	.	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
5e-05	2e-06	5e-05	.	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
0.0001	2e-06	5e-05	.	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
0.0002	2e-06	5e-05	.	0	0	0	0	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	1	0	0
0.0005	2e-06	5e-05	.	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	1	0	0	0	0
0.0001	2e-06	5e-05	.	0	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	1	0	0	0
3e-05	2e-06	5e-05	.	0	0	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
1e-05	2e-06	5e-05	.	0	0	0	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	0	0
0.0003	1e-06	0.001	.	0	0	0	0	0	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0
2e-06	1e-06	0.001	.	0	0	0	0	0	0	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0
0.0004	1e-06	0.001	.	0	0	0	0	0	0	0	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0
1.5e-06	1e-06	0.001	.	0	0	0	0	0	0	0	0	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0
6e-06	1e-06	0.001	.	0	0	0	0	0	0	0	0	0	0	0	0	0	0	1	0	0	0	0	0	0	0	0
5e-07	1e-07	0.001	.	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
1.8e-05	1e-06	0.001	.	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
3e-05	1e-06	0.001	.	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	1	0	0	0	0	0	1	0
8e-05	1e-06	0.001	.	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	1	0	0	0	0	0	0
9.10135e-05	1e-06	0.001	.	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	1
0.00025	1e-05	1	.	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
1e-05	1e-05	1	.	1	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	1	0	0	0	0	0
0.01	1e-06	0.9	.	1	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	1	0	0	0	0	0
10	0.01	1	.	1	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	1	0	0	0	0	0
2.5	0.25	4	.	1	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	1	0	0	0	0	0
1e-06	1e-05	1	.	0	1	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
100	1.1	0.1	.	0	1	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
2.1	0.01	1	.	0	1	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
2	0.25	4	.	0	1	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
1e-06	1e-05	1	.	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
80	1.1	0.1	.	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
6	0.01	1	.	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
4	0.25	4	.	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
1e-05	1e-05	1	.	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
10	1.1	0.1	.	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
2	0.01	1	.	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
3	0.25	4	.	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
1e-05	1e-05	1	.	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
100	1.1	0.1	.	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
1	0.01	1	.	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
2	0.25	4	.	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
1e-05	1e-05	1	.	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	1	0	0	0	0
3.5	1.1	10	.	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	1	0	0	0	0
1.6	1.1	0.1	.	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	1	0	0	0	0
2	0.01	1	.	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	1	0	0	0	0
1	0.25	4	.	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	1	0	0	0	0
250	1.1	0.1	.	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	1	0	0	0	0
0.2	0.01	1	.	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	1	0	0	0	0
2	0.25	4	.	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	1	0	0	0	0
0.005	1e-06	0.9	.	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	1	0	0	0	0
0.48	0.01	1	.	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	1	0	0	0	0
4	0.25	4	.	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	1	0	0	0	0
1	1e-06	0.9	.	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	1	0	0	0	0
5	0.01	1	.	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	1	0	0	0	0
2	0.25	4	.	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	1	0	0	0	0
0.1	1e-06	0.9	.	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	1	0	0	0	0
5	0.01	1	.	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	1	0	0	0	0
2	0.25	4	.	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	1	0	0	0	0
1e-06	1e-05	1	.	0	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	1	0	0	0
5	1.1	0.1	.	0	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	1	0	0	0
40	0.01	1	.	0	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	1	0	0	0
1.2	0.25	4	.	0	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	1	0	0	0
30	1.1	0.1	.	0	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	1	0	0	0
8	0.01	1	.	0	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	1	0	0	0
1.2	0.25	4	.	0	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	1	0	0	0
0.1	1e-06	0.9	.	0	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	1	0	0	0
5	0.01	1	.	0	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	1	0	0	0
1	0.25	4	.	0	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	1	0	0	0
40	1.1	0.1	.	0	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	1	0	0	0
1.2	0.01	1	.	0	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	1	0	0	0
4	0.25	4	.	0	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	1	0	0	0
0.1	1e-06	0.9	.	0	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	1	0	0	0
5	0.01	1	.	0	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	1	0	0	0
2	0.25	4	.	0	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	1	0	0	0
0.5	1e-06	0.9	.	0	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	1	0	0	0
2	0.01	1	.	0	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	1	0	0	0
1.2	0.25	4	.	0	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	1	0	0	0
5e-06	1e-05	1	.	0	0	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
6	1.1	10	.	0	0	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
2	1.1	0.1	.	0	0	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
1.2	0.01	1	.	0	0	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
0.9	0.25	4	.	0	0	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
15	1.1	0.1	.	0	0	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
0.169	0.01	1	.	0	0	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
3	0.25	4	.	0	0	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
0.5	1e-06	0.9	.	0	0	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
5	0.01	1	.	0	0	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
2	0.25	4	.	0	0	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
0.2	1e-06	0.9	.	0	0	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
5	0.01	1	.	0	0	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
2	0.25	4	.	0	0	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
0.01	1e-06	0.9	.	0	0	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
1	0.01	1	.	0	0	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
2	0.25	4	.	0	0	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
1e-05	1e-05	1	.	0	0	0	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	0	0
3	1.1	0.1	.	0	0	0	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	0	0
45	0.01	1	.	0	0	0	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	0	0
1	0.25	4	.	0	0	0	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	0	0
25	1.1	0.1	.	0	0	0	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	0	0
0.4	0.01	1	.	0	0	0	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	0	0
3	0.25	4	.	0	0	0	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	0	0
1e-06	1e-06	0.9	.	0	0	0	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	0	0
0.01	0.01	1	.	0	0	0	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	0	0
0.25	0.25	4	.	0	0	0	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	0	0
1e-06	1e-06	0.9	.	0	0	0	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	0	0
2	0.01	1	.	0	0	0	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	0	0
3	0.25	4	.	0	0	0	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	0	0
1e-06	1e-06	0.9	.	0	0	0	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	0	0
1	0.01	1	.	0	0	0	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	0	0
3	0.25	4	.	0	0	0	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	0	0
1e-05	1e-05	0.25	.	0	0	0	0	0	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0
1e-05	1e-05	0.25	.	0	0	0	0	0	0	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0
1e-05	1e-05	0.25	.	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
1e-05	1e-05	0.25	.	0	0	0	0	0	0	0	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0
1e-05	1e-05	0.25	.	0	0	0	0	0	0	0	0	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0
1e-05	1e-05	0.25	.	0	0	0	0	0	0	0	0	0	0	0	0	0	0	1	0	0	0	0	0	0	0	0
1e-05	1e-05	0.25	.	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
1e-05	1e-05	0.25	.	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
0.416	0.416	0.25	.	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	1	0	0	0	0	0	1	0
1e-06	1e-06	0.25	.	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	1	0	0	0	0	0	0
0.0433151	0.04	0.25	.	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	1
0.0094	0.0094	0.25	.	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	1	0	0	0	0	0
0.0165	0.0165	0.25	.	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
0.00016	0.00016	0.25	.	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
0.034	0.034	0.25	.	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
0.041	0.041	0.25	.	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
0.97	0.97	0.25	.	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	1	0	0
0.015	0.015	0.25	.	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	1	0	0	0	0
1.36	1.36	0.25	.	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	1	0	0	0
0.032	0.032	0.25	.	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
0.213	0.213	0.25	.	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
14.6	12	16	.	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
19.05	18	20	.	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
.	.	.	.	1	1	1	1	1	1	1	1	1	1	0	1	1	1	1	1	1	1	1	1	1	1	1
.	.	.	.	1	1	1	1	1	1	1	1	1	1	1	0	1	1	1	1	1	1	1	1	1	1	1
.	.	.	.	.	.	.	.	.	.	.	.	.	.	.	.	.	.	.	.	.	.	.	.	.	.	.
.	.	.	.	.	.	.	.	.	.	.	.	.	.	.	.	.	.	.	.	.	.	.	.	.	.	.
.	.	.	.	1	1	1	1	1	1	1	1	1	1	1	1	0	1	1	1	1	1	1	1	1	1	1
.	.	.	.	1	1	1	1	1	1	1	1	1	1	1	1	1	0	1	1	1	1	1	1	1	1	1
.	.	.	.	1	1	1	1	1	1	1	1	1	1	1	1	1	1	0	1	1	1	1	1	1	1	1
.	.	.	.	.	.	.	.	.	.	.	.	.	.	.	.	.	.	.	.	.	.	.	.	.	.	.
.	.	.	.	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
.	.	.	.	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	0	1	1	1	1	1	0	1
.	.	.	.	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	0	1	1	1	1	1	1
.	.	.	.	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	0
.	.	.	.	0	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	0	1	1	1	1	1
.	.	.	.	1	0	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1
.	.	.	.	1	1	0	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1
.	.	.	.	1	1	1	0	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1
.	.	.	.	1	1	1	1	0	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1
.	.	.	.	1	1	1	1	1	1	1	1	1	0	1	1	1	1	1	1	1	1	1	1	0	1	1
.	.	.	.	1	1	1	1	1	0	1	1	1	1	1	1	1	1	1	1	1	1	0	1	1	1	1
.	.	.	.	1	1	1	1	1	1	0	1	1	1	1	1	1	1	1	1	1	1	1	0	1	1	1
.	.	.	.	1	1	1	1	1	1	1	0	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1
.	.	.	.	1	1	1	1	1	1	1	1	0	1	1	1	1	1	1	1	1	1	1	1	1	1	1
.	.	.	.	.	.	.	.	.	.	.	.	.	.	.	.	.	.	.	.	.	.	.	.	.	.	.
.	.	.	.	.	.	.	.	.	.	.	.	.	.	.	.	.	.	.	.	.	.	.	.	.	.	.
.	.	.	.	.	.	.	.	.	.	.	.	.	.	.	.	.	.	.	.	.	.	.	.	.	.	.
.	.	.	.	.	.	.	.	.	.	.	.	.	.	.	.	.	.	.	.	.	.	.	.	.	.	.
// ---------------------------------------------------- */


void compileLatex(string folderRes, string texFile){
    ofstream action (folderRes + string("doPDF.bat"), ios::out);
    action << string("cd ") + folderRes + string("\npdflatex -interaction=nonstopmode ") + texFile + string(" > resLatexCompil.txt\n");
    action.close();
    #ifdef WINDOWS
    system((folderRes + string("doPDF.bat\n")).c_str());
    #endif
    #ifdef UNIX
    system((string("cd ") + folderRes + string("\nchmod +x doPDF.bat\n./doPDF.bat > resLatexCompil.txt \n")).c_str());
    #endif
}








/*
expFromTh17* currentExperiment = new expFromTh17(currentModel, 0.8);


#ifndef WITHOUT_QT
    simuWin* p = new simuWin(currentExperiment);
    p->show();
    cout << "Launch GUI ..." << endl;
    return b.exec();
#endif

    std::vector<int> v  {1,2,3};


    // ====== Manually overriding some of the variables. Can be done more easily by overriding using a combination ======

        bool overrideRNAs = false;
        bool overrideCytok = true;
        bool overrideTF = true;
        vector<int> VTO; // Vars to override
        if(overrideRNAs){
            VTO.push_back(N::FOXP3mRNA);
            VTO.push_back(N::GATA3mRNA);
            VTO.push_back(N::IFNGmRNA);
            VTO.push_back(N::IL4mRNA);
            VTO.push_back(N::IL21mRNA);
            VTO.push_back(N::IL2mRNA);
            VTO.push_back(N::IL17mRNA);
            VTO.push_back(N::RORGTmRNA);
            VTO.push_back(N::TGFBmRNA);
            VTO.push_back(N::TBETmRNA);
        }
        if(overrideCytok){
            VTO.push_back(N::IFNG);
            VTO.push_back(N::IL4);
            VTO.push_back(N::IL21);
            VTO.push_back(N::IL2);
            VTO.push_back(N::IL17);
            //VTO.push_back(N::TGFB);
        }
        if(overrideTF){
            VTO.push_back(N::FOXP3);
            VTO.push_back(N::GATA3);
            VTO.push_back(N::RORGT);
            //VTO.push_back(N::TBETmRNA);
        }
        for(int i = 0; i < (int) VTO.size(); ++i){
            OverTh1->setOver(VTO[i], true);
            OverTh2->setOver(VTO[i], true);
            OveriTreg->setOver(VTO[i], true);
            OverTh17->setOver(VTO[i], true);
            OverTh0->setOver(VTO[i], true);
        }
        currentExperiment->setOverrider(TH1,    &OverTh1);
        currentExperiment->setOverrider(TH2,    &OverTh2);
        currentExperiment->setOverrider(TREG,   &OveriTreg);
        currentExperiment->setOverrider(TH17,   &OverTh17);
        currentExperiment->setOverrider(TH0,    &OverTh0);



    //cout << generateActivFunction(0, 2);


    */




string optName(typeOptimizer toUse){
    switch (toUse){
    case GeneticFast: { return string("Genetic Algorithm, only a few rounds for tests"); break;}
    case SRESFast: { return string("SRES, only a few rounds for tests"); break;}
    case Genetic25k: { return string("Genetic Algorithm, 25 000 cost evaluations"); break;}
    case Genetic50k: { return string("Genetic Algorithm, 50 000 cost evaluations"); break;}
    case Genetic100k: { return string("Genetic Algorithm, 100 000 cost evaluations"); break;}
    case Genetic250k: { return string("Genetic Algorithm, 250 000 cost evaluations"); break;}
    case Genetic500k: { return string("Genetic Algorithm, 500 000 cost evaluations"); break;}
    case Genetic1M: { return string("Genetic Algorithm, 1 000 000 cost evaluations"); break;}
    case SRES25k: { return string("SRES, 25 000 cost evaluations"); break;}
    case SRES50k: { return string("SRES, 50 000 cost evaluations"); break;}
    case SRES100k: { return string("SRES, 100 000 cost evaluations"); break;}
    case SRES250k: { return string("SRES, 250 000 cost evaluations"); break;}
    case SRES500k: { return string("SRES, 500 000 cost evaluations"); break;}
    case SRES1M: { return string("SRES, 1 000 000 cost evaluations"); break;}
    case GeneticAllCombs25k: { return string("Genetic Algorithm, All Operators, 25 000 cost evaluations"); break;}
    case GeneticAllCombs50k: { return string("Genetic Algorithm, All Operators, 50 000 cost evaluations"); break;}
    case GeneticAllCombs100k: { return string("Genetic Algorithm, All Operators, 100 000 cost evaluations"); break;}
    case GeneticAllCombs250k: { return string("Genetic Algorithm, All Operators, 250 000 cost evaluations"); break;}
    default: {return string("");}
    }
    return string("");
}

string optFileHeader(typeOptimizer toUse){

    stringstream headerOptimizer;
    switch (toUse){
        case SRESFast:{
            headerOptimizer << "SRES	1   \n50\n";
            break;
        }
        case SRES25k:{
            headerOptimizer << "SRES	1   \n25000\n";
            break;
        }
        case SRES50k:{
            headerOptimizer << "SRES	1   \n50000\n";
            break;
        }
        case SRES100k:{
            headerOptimizer << "SRES	1   \n100000\n";
            break;
        }
        case SRES250k:{
            headerOptimizer << "SRES	1   \n250000\n";
            break;
        }
        case SRES500k:{
            headerOptimizer << "SRES	1   \n500000\n";
            break;
        }
        case SRES1M:        {
            headerOptimizer << "SRES	1   \n1000000\n";
            break;
        }

        default:{}
    }
    // finished for SRES

    bool TESTE_ALL_CROSSMUT = false;
    switch (toUse){
        case GeneticAllCombs25k:
        case GeneticAllCombs50k:
        case GeneticAllCombs100k:
        case GeneticAllCombs250k:   {
            TESTE_ALL_CROSSMUT = true;
            break;
        }
        default:{}
    }


    switch (toUse){
        case GeneticFast:
        case Genetic25k:
        case Genetic50k:
        case Genetic100k:
        case Genetic250k:
        case Genetic500k:
        case Genetic1M:
        case GeneticAllCombs25k:
        case GeneticAllCombs50k:
        case GeneticAllCombs100k:
        case GeneticAllCombs250k:   {
            headerOptimizer << "geneticAlgorithm	14\n";
            headerOptimizer << (TESTE_ALL_CROSSMUT ? "10         #CEP  - All Mut&Cross\n" : "0	#CEP  - Classical Evolutionary Programming\n");
            headerOptimizer << "8          #Proportional / From Worst / Basic Sampling\n";
            headerOptimizer << "7	1      #SBX Cross-Over\n";
            headerOptimizer << "1          #Mutation normal all points\n";
            headerOptimizer << "0          #NO_NEED_REPLACEMENT\n";
            headerOptimizer << "0          #Select Best\n";
            headerOptimizer << "7	0.005	#MUTATIVE_SEPARATED\n";
            headerOptimizer << "1      #Nb Repeats\n";
            break;
        }
        default:{}
    }

    switch (toUse){
        case GeneticFast:{
            headerOptimizer << "50	#Max nb of simulations-costs\n";
            headerOptimizer << "50	#Population Size\n";
            break;
        }
        case Genetic25k: case GeneticAllCombs25k:{
            headerOptimizer << "25000	#Max nb of simulations-costs\n";
            headerOptimizer << "250	#Population Size\n";
            break;
        }
        case Genetic50k: case GeneticAllCombs50k:{
            headerOptimizer << "50000	#Max nb of simulations-costs\n";
            headerOptimizer << "250	#Population Size\n";
            break;
        }
        case Genetic100k:  case GeneticAllCombs100k:{
            headerOptimizer << "100000	#Max nb of simulations-costs\n";
            headerOptimizer << "500	#Population Size\n";
            break;
        }
        case Genetic250k: case GeneticAllCombs250k:{
            headerOptimizer << "250000	#Max nb of simulations-costs\n";
            headerOptimizer << "750	#Population Size\n";
            break;
        }
        case Genetic500k:{
            headerOptimizer << "500000	#Max nb of simulations-costs\n";
            headerOptimizer << "1000	#Population Size\n";
            break;
        }
        case Genetic1M:{
            headerOptimizer << "1000000	#Max nb of simulations-costs\n";
            headerOptimizer << "2000	#Population Size\n";
            break;
        }
        default:{}
    }

    switch (toUse){
        case GeneticFast:
        case Genetic25k:
        case Genetic50k:
        case Genetic100k:
        case Genetic250k:
        case Genetic500k:
        case Genetic1M:
        case GeneticAllCombs25k:
        case GeneticAllCombs50k:
        case GeneticAllCombs100k:
        case GeneticAllCombs250k:   {
            headerOptimizer << "0.2	#Proportion of CrossOver (vs offspring) in new individuals\n";
            headerOptimizer << "0.5	#Fork coeff (%renewed each generation)\n";
            break;
        }
    default:{}
    }
    return headerOptimizer.str();

    /*headerOptimizer << "geneticAlgorithm	14\n";
    headerOptimizer << (TESTE_ALL_CROSSMUT ? "10         #CEP  - All Mut&Cross\n" : "0	#CEP  - Classical Evolutionary Programming\n");
    headerOptimizer << "8          #Proportional / From Worst / Basic Sampling\n";
    headerOptimizer << "7	1      #SBX Cross-Over\n";
    headerOptimizer << "1          #Mutation normal all points\n";
    headerOptimizer << "0          #NO_NEED_REPLACEMENT\n";
    headerOptimizer << "0          #Select Best\n";
    headerOptimizer << "7	0.005	#MUTATIVE_SEPARATED\n";
    headerOptimizer << "1      #Nb Repeats\n";
    headerOptimizer << "5000	#Max nb of simulations-costs\n";
    headerOptimizer << "250	#Population Size\n";
    headerOptimizer << "0.2	#Proportion of CrossOver (vs offspring) in new individuals\n";
    headerOptimizer << "0.5	#Fork coeff (%renewed each generation)\n";



    switch (toUse){
    case GeneticFast:   { break;}
    case SRESFast:      { break;}
    case Genetic25k:    { break;}
    case Genetic50k:    { break;}
    case Genetic100k:   { break;}
    case Genetic250k:   { break;}
    case Genetic500k:   { break;}
    case Genetic1M:     { break;}
    case SRES25k:       { break;}
    case SRES50k:       { break;}
    case SRES100k:      { break;}
    case SRES250k:      { break;}
    case SRES500k:      { break;}
    case SRES1M:        { break;}
    case GeneticAllCombs25k:    { break;}
    case GeneticAllCombs50k:    { break;}
    case GeneticAllCombs100k:   { break;}
    case GeneticAllCombs250k:   { break;}
    default:                    {return string("");}
    }

    */

}
