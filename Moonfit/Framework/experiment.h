#ifndef Experiment_H
#define Experiment_H

#include "evaluator.h"
#include "modele.h"
#include <vector>
#include <string>
#include <iostream>
using namespace std;

/// @defgroup Experiment Experiment
/// @brief An experiment is the design of simulations to be performed on a model.
/// @{


/// @brief An experiment is the design of a simulation performed on a model.
/// The same experiment can be performed on different models.
/// An experiment can have several conditions.
/// The Experiment class is used as mother class for each user-defined experiment,
/// and implements all basic functions for simulations and data management.
struct Experiment{

    Experiment(Model* _m, int _nbConditions, string _Identification = "");   // An experiment has to be intanciated with an existing model
    Model* m;
    int nbConditions;                             // Nb of simulations/curves inside this experiment

    // informations hat should be filled by the subclass:
    string Identification;                  // a name for this experiment !
    vector<string> names_exp;               // List of defined conditions the subclass can run

    // that should be reimplemented
    virtual void simulate(int IdExp, Evaluator* E = NULL, bool force = false);  // simulating one of the experiments. Do it only if the experiment is doable. If the estimator doesn't need values from this experiment, will not be simulated, unless you use force = true.
                    // Should describe how the model has to be simulated, for each condition,
                    // by putting initial values to variables, using Model::simulate for
                    // a certain duration, and by applying perturbations.
                    // The evaluator E will contain the experimental data and has to be passed
                    // to the Model::simulate() function to store simulated data.
                    // If force = false, will only simulate simulations that have data in E.

    // that can be reimplemented. The original code is in the motherXXX functions
    virtual void    init(){motherInit();}
    virtual double  costVariableInModel(int speciesGlobalID = -1){return motherCostVarInModel(speciesGlobalID);}        // returns the cost of an experiment compared to data (you have to provide the data & cost yourself)
    virtual double  costExternalVariable(string externalName){return motherCostExternalVariable(externalName);}
    virtual double  costExp(int ConditionID = -1){return motherCostExp(ConditionID);}        // returns the cost of an experiment compared to data (you have to provide the data & cost yourself)
    virtual void    reset(){motherReset();}                     // does nothing (except if reimplemented)
    virtual void    simulateAll(bool force = false){motherSimulateAll(force);}         // to do all the simulations

    // The code pre-implemented for all of them
    void            motherInit();
    double          motherCostVarInModel(int varID = -1);
    double          motherCostExternalVariable(string extName = string());
    double          motherCostExp(int IDcondition = -1);
    void            motherReset();
    bool            motherPrepareSimulate(int IdExp, Evaluator *&E, bool force); // Checks if doable,  // what the hell *& ??
    void            motherSimulateAll(bool force = false);

    // Basic I/O functions
    int getNbCond();                    // gives names_exp.size()
    string getConditionName(int i);          // reads names_exp[i]
    string print();

    // In order to store a list of points to simulate and record (avoids to record all the kinetics of all variables at all dt ...)
    vector<Evaluator*> VTG; // "Values to get", one evaluator per experiment
    double V(int IDexp, string Species, int time_sec){return VTG[IDexp]->getVal(m->uniqueInternValName(Species), time_sec);}
    double expV(int IDexp, string Species, int time_sec){return VTG[IDexp]->getExpVal(m->uniqueInternValName(Species), time_sec);}
    double totalPenalities;
    double getPenalities();

    // this should be programmed independently
    // In order to give experimental data with StdDev and compare with simulations or give to evaluators
    vector< vector<TableCourse*>> ExpData;
    vector< vector<TableCourse*>> ExpStdDevs;

    void giveData(TableCourse* kineticData, int IdExp, TableCourse *kineticStds = NULL);
    void loadEvaluators();

    // In order to replace variables by pre-defined curves
    vector<overrider*> Overs;
    void setOverrider(int IdExp, overrider* _ov = NULL);
    void overrideVariable(string extVarName, bool override = true, int IdExp = -1);
    bool canOverride(string extVarName, int IdExp = -1);

    // a super cool function to extract a table of results from simulation of different experiments
    string extractData(vector<int> timePoints, vector<string> extNamesToSelect, vector<int> IDexps = vector<int>());

    string costReport();
    virtual ~Experiment(){}
    bool evaluatorLoaded;
};


/// @brief A MultiExperiments is made from multiple used-defined Experiments,
/// and allows to simulate them together and get a multi-experiment cost between
/// simulations and data.
/// The same model is used for each experiment, therefore the same model parameters.
/// Each experiment can be given a coefficient for the total cost calculation.
struct MultiExperiments{
    MultiExperiments(Model* _m);   // m is the model that will be used to do simulations
    Model* m;

    int NbBigExps;
    vector<Experiment*> ListBigExperiments;
    void AddExperiment(Experiment* Ex);
    Experiment* getExperiment(int BigExpID);

    vector<double> coefficients;
    int cptNbSimus;

    // function called by the cost functions, need to be re-implemented, and can change the coefficients whenever.
    virtual void politics(){}
    virtual void postPolitics(){}


    // that should be reimplemented
    virtual void simulate(int IdExp, Evaluator* E = NULL, bool force = false);  // simulating one of the experiments. Do it only if the experiment is doable. If the estimator doesn't need values from this experiment, will not be simulated, unless you use force = true.


    // just call the same function in all the Experiment of the list
    void    init();
    virtual double  costVariableInModel(int speciesGlobalID = -1);
    virtual double  costExternalVariable(string extName = string(""));
    virtual double  costBigExp(int BigExpID = -1);
    void    reset();
    void    simulateAll(bool force = false);

    // Basic I/O functions
    int nbBigExp();                    // gives names_exp.size()
    string BigExpName(int i);          //
    string print();

    double getCoefficient(int BigExpID);
    void setCoefficient(int BigExpID, double newValue);

    double getPenalities();
    void loadEvaluators();
    void overrideVariable(string extNameVar, bool override);

    string costReport();


    virtual ~MultiExperiments(){}
};



/// @brief expCompParameterSets takes an experiment and compares one of its condition with different parameter sets.
/// you give an experiment, and a list of parameter sets, it creates a new experiment whose conditions are each parameter set.
///    if the original experiment has 1 condition, nothing to do
///    if ----------------------- had more than 1 condition, choose which condition to compare.
///    - Be careful that each parameter set will be used to call 'initialize' from the experiment successively, make sure
///      it has no effect on the next parameter set.
///    - Note that only the experimental data from the chosen condition will be taken //TODO!!//.
struct expCompParameterSets: public Experiment {
    expCompParameterSets(Experiment* Exp, vector< vector<double> *> _parameterSets, int _IDconditionToUse = 0);
    vector< vector<double> *> parameterSets;
    Experiment* builtOnExperiment;
    int IDconditionToUse;
    void simulate(int IdExp, Evaluator* E = NULL, bool force = false);
};





/// @brief expChangeOneParameter takes an experiment and compares one of its condition from a parameter set
/// but changing one parameter along perturbated values around the original value.
struct expChangeOneParameter: public Experiment {
    enum {Param05, Param20, Param01, Param100, Param08, Param12, Param02, Param15, Param005, Param50, ParamDefault, NbVariantes};
    expChangeOneParameter(Experiment* Exp, vector<double> & _parameterSet, int _parameterToChange, int _IDconditionToUse = 0, int _nbCurves = expChangeOneParameter::NbVariantes);
    void init();
    vector<double> parameterSet; // this is the initial one, will be updated from the model each time simulated
    int parameter;
    int nbCurves;
    double valueAround;
    Experiment* builtOnExperiment;
    int IDconditionToUse;
    void simulate(int IdExp, Evaluator* E = NULL, bool force = false);
};
/// @}







#endif // Experiment_H
