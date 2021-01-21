// Philippe Robert, 19-09-2014 - philippe-robert.com
// Model.h and Model.cpp  needs the TableCourse structure defined in tablecourse.h and tablecourse.cpp
//                          and the Evaluator structure. Remove/comment #define USE_EVALUATORS to use standalone
//                          and the Overrider structure. Remove/comment #define USE_OVERRIDERS to use standalone
#ifndef Model_H
#define Model_H
#define USE_EVALUATORS
#define USE_OVERRIDERS

// USER CHOICE: To use the RK4 solver from BOOST, uncomment:
//#define USE_BOOST_SOLVER

// USER CHOICE: Define here the stopping criterion for diverging simulations
#define STOP_VAL 1e12

// Note: to avoid excessive computations for low numbers, variables smaller than this value become 0 during solving.
#define MIN_VAL 1e-12


#include <iostream>
#include <vector>
#include <string>
#include <iomanip>      // for std::setprecision
#include <cmath>
#include <fstream>
#include "tableCourse.h"

#ifdef USE_OVERRIDERS

#include "overrider.h"

#endif

#ifdef USE_EVALUATORS

#include "evaluator.h"

#endif
#define DEFAULT_BACKGROUND_VALUE    1
using namespace std;


/// @defgroup Model Dynamical Model
/// @brief An model is a class that can perform dynamical simulations. It contains its own parameter set.
/// @{


/// @brief A general mother class to perform dynamical simulations. It contains its own parameter set and set
/// of equations / rules to evolve over time. It is possible to give simulation options through a parameter
/// called 'background' (for instance WT or treated cells).
/// You will need to program your own subclass of Model, so that you can use inherited function from this mother class.
/// It pre-defines all basic functions for simulations and data management, including calling ODE solver.
/// Agent-based models needs to use the derived modelAgentBased class as mother (see below).
struct Model {
    string name;                                            /// @brief Name of this model

    /// The general constraints your Model subclass should follow are here :

    /// 0 - Calling the constructor : the sub-model need to call the mother constructor and say the nb of variables and parameters to allocate
    Model(int _nbVars, int _nbParams);


    /// 1 - Using the storage provided by the mother class, to define the basic information of the model.
    ///     the model() constructor will allocate/size them but never change their content.
    ///     so the subclass need to fill those 7 fields (see tutorial / examples):
public:
    int nbVars;
    int nbParams;
    vector<double> init;                                    /// @brief initial values of variables (size bVars)
    vector<double> params;                                  /// @brief parameter values (size nbParams)
    vector<string> names;                                   /// @brief names of the variables
    vector<string> paramNames;                              /// @brief names of the parameters
    vector<string> extNames;                                /// @brief the 'official/global/external' name of each variable, when reading data / kinetics


public:
    /// 2 - The functions the sub-model HAS TO implement : time evolution for dt at time t, initialise and base parameter values
    virtual void derivatives(const vector<double> &x, vector<double> &dxdt,
                             const double t);    /// @brief computes the derivatives (at t) from position x
    virtual void
    setBaseParameters();                       /// @brief gives a correct set of parameters, if you don't load other set.
    virtual void initialise(
            long long _background = DEFAULT_BACKGROUND_VALUE);           /// @brief initialise, (parameters should be set before initializing) - sets t = 0 if necessary.
    /// @brief to avoid confusion, this function should not change the parameter values !!
    /// @brief the background parameter allows to give options of simulation (such as deficient mice)
    virtual void
    finalize() {}                               /// @brief It can be helpful that the experiments notifies the model when a simulation is finished.
    /// @brief For ODE models it might be not important, but for agent-based memory might need to be cleared


    /// 2b - This function is already implemented in the mother class, but as an option you can override it in the subclass
    virtual void loadParameters(
            string file_name);          /// @brief reads parameters from a text file with format : "NB_PARAMS\tparam1\tparam2\tparam3 ..."
    virtual void saveParameters(
            string file_name);          /// @brief writes parameters from a text file with format : "NB_PARAMS\tparam1\tparam2\tparam3 ..."

    /// 2c - A function to perform personnalized actions by the model, without a specific function, but by a name of action, (ex : adding a cytokine at day 2)
    virtual void action(string name,
                        double parameter);     /// @brief function to perform personnalized actions by the model by a name of action,
    virtual void action(string name, vector<double> parameters);

    /// 2d - An additional function that can be designed by the user to simulate variable depending on other ones. Exemple: percents, ratios, etc ...
    virtual void updateDerivedVariables(
            double _t = 0);     /// @brief  Will be called when the solver stops at each point -> use it to calculate variables that depend on other ones
    /// (i.e. not defined by their derivatives). This is called only after solving, NOT DURING!
    /// for variables that need to be calculated during solving od ODEs, they need to be calculated INSIDE derivatives,
    /// but they should not access val[]. They only can modify x[] and dxdt[] the arguments of derivatives,
    /// because the solver can be at any point or trying things or diverging, independently of the one that will be saved in val[] at the end.


public:
    /// 2d - the 'event' functions that the virtual functions of the sub-classes should call, so the mother class knows what's happening,
    void initialiseDone();

    void setBaseParametersDone();

    void loadParametersDone();

    ///     During a simulation, these variables will be used by the solver.
    double t;                                               /// @brief advised to do 't=0;' in the initialize function
    vector<double> val;                                     /// @brief variables at time t
    vector<double> deriv;                                   /// @brief derivatives at time , updated each time the solver stops for output

public:
    /// @brief In case the parameters are modified (like by optimization), it's a way to forbid to run simulations with this parameter set. (need to reload/restore a good one)
    void needNewParameterSet();

public:


/// Now, the interests of using the Model mother class are coming :
/// whatever the sub-class model, the following functions are implemented and can be used to simulate, or do interesting manipulations of the model.

#ifndef USE_EVALUATORS
    typedef void Evaluator;
#endif

/// 3 - functions for simulating (automatically calling the sub-class derivatives function, using the solver)

    virtual void simulate(double _sec_max, Evaluator *E = NULL);    /// @brief Simulates from t (not changed), to t + _sec_max, by calling one_step
    /// the evaluator, if given, is a structure that says when to store data from the simulation, and avoids to store everything.
    /// if the simulation diverges, it is stopped and a penalty is computed in the field penalities (of the mother class)

public:
    double dt;                                   /// @brief minimum dt used for simulations. The tunable dt will start at dt*10 and be limited between dt and dt*100
public:
    double penalities;                           /// @brief automatically updated by the mother class : put to zero when initialiseDone() called and increased when the simulation diverges.

public:
/// 4 - I/O functions


/// 4a - to print the state of a simulation



/// 4b - to get simulations as tables of values (kinetics) of simulation

    /// before a simulation, one has to activate the kinetic mode.
    /// Then, for every simulation, the simulation data will be put in a new table, that can be retrieved by getCinetique.
    /// Note that 'initialiseDone' clears the current table
public:
    bool saveKinetics;                                      /// @brief sets the mode : simulates a kinetics to record or just simulate what you ask without stopping
    double print_every_dt;                                  /// @brief frequency of saving/displaying data for kinetics
    void setPrintMode(bool z,
                      double _print_every_dt);      /// @brief to set the 'recording mode' to ON/OFF, and the frequency of recording
    TableCourse
    getCinetique();                             /// @brief then, each time initialiseDone() is called, the kinetics is cleared, and
    vector<double> getInit();

    double getT();

/// 4c - to get the value of a particular variable at a particular time point during a simulation,

/// then, the best way is to create an optimizer* E, give him the data points you want, and do the simulation with simulate(int _sec_max, E)
/// so the simulation is filling automatically the evaluator with those data points. See the class Optimizer for that.

/// 4d to print most informations about the model

    string print();

    string printVarNames(double _t);

    string printVarValues(double _t);

    string printParNames();

    string printParValues();

/// 5 - Accessing variables from an external name, and defining backgrounds
///     even if the model has its internal variable names, you might want to say that this vairable represents this cytokine,
///     in this case, a model can attribute an 'external' name to each variable
///     additionally, a model can declare the list of backgrounds it is able to simulate.
///     in that way, it is possible to interrogate what a model is able to simulate (variables, background).

///     vectors that can be filled by the subclass :

    vector<string> getListExternalNames() { return extNames; }


///     Then, the values of variables can be accessed with the 'external ID' with the following functions
///     these already implemented functions can be overrided if wanted (for instance if changing the value of a variable needs to be done in a particular way)
public:
    virtual void setValue(string nameExternalVariable,
                          double val);      /// @brief to modify the value of a variable from the global ID of it
    virtual void addValue(string nameExternalVariable,
                          double val);      /// @brief to modify the value of a variable from the global ID of it
    virtual double
    getValue(string nameExternalVariable);                  /// @brief to get the value of a variable from its global ID
    virtual bool isVarKnown(
            string externalNameVariable);                /// @brief to know if a variable can be simulated by the model (from its global ID)
    virtual vector<int>
    internValName(string externalNameVariable);        /// @brief index of variables for this external name
    virtual int uniqueInternValName(
            string externalNameVariable);      /// @brief index of variables for this external name; raises an error if there are multiple...

/// 7 - Working directly with the parameters of a model (important for managing the interface with the optimizer (fitting class))

    int getNbParams();

    void setParam(int i, double v);

    double getParam(int i);

    vector<double> getParameters();

    void setParameters(vector<double> &newParamSet);

/// 8 - to get information on the (internal) variables.

    int getNbVars();

    string getName(int internalID);

    string getExternalName(int internalID);

/// 9 - Overriding certain variables with data,

#ifdef USE_OVERRIDERS
    /// Idea : provide data as an overrider:
    ///      overrider(i) says if you override or not this variable (global name/ID)
    ///      overrider(i,t) gives forced value for variable i (global name) at time t (linear or spline interpolation)
    ///
    ///      for simulating, the solver might be confused if the x value is changed from external data (the error might be big depending on delta t)
    ///      solution : the solver will force the data each time-step before calling the solver
public :
    void setOverrider(overrider *newOverrider = nullptr);

protected:
    overrider *currentOverrider;
public:
    void applyOverride(vector<double> &x, double t);

    void clearOverride(vector<double> &x, vector<double> &dxdt);

#endif

    bool over(int indexLocal);      /// @brief says if a variable is overrided (then, no need to calculate derivatives)
    /// if no USE_OVERRIDERS defined, then returns false ! So a program can use this
    /// function independently of the define options

/// 10 - names and boundaries for parameters

protected:
    vector<double> paramUpBounds;
    vector<double> paramLowBounds;
public:
    string getParamName(int i);

    double getLowerBound(int i);

    double getUpperBound(int i);

    void setBounds(int i, double vLow, double vHi);

    void setBounds(vector<double> upVals, vector<double> lowVals);

/// 11 - Internal functions

    /// Checking for errors: a model should never be copied, in which cases destroying one copy creates a segfault on the other one
    Model(const Model &) { cerr << "Checking for errors - you are copy a Model, why ?" << endl; }

    virtual ~Model() {}

    /// internal way of managing kinetics (automatically used)
protected: // for modelAgentBased
    TableCourse *cinetique;

    void deleteCinetique();

    void newCinetiqueIfRequired();

    void save_state(
            double _t);                                     /// the simule function call this to record data of a time point into the Cinetique.
protected:
    double
    max(double, double);                                     // Auxiliary functions, not available by default (??) ...
    bool parametersLoaded;                                          // to make sure setparameters is done before initialize
    bool checkDivergence();

    bool stopCriterionReached;
};


/// @brief A general mother class to perform agent-based dynamical simulations. It contains its own parameter set
/// and variables, that will be observations of the agent-based model.
/// The used needs to define a sub-class that will implement the functions /// timeStep(...) and analyzeState(...),
/// on top of the functions required by the Model mother class.
/// All functions of the Model class are available, except simulate(...), that calls timeStep(...) instead of an ODE solver.
struct modelAgentBased : public Model {
    modelAgentBased(int _nbVars, int _nbParams) : Model(_nbVars, _nbParams) {}

    void simulate(double sec_max, Evaluator *E);

    /// @brief Function to be implemented by the user, that will perform time-steps between t=tstart to t=tend
    virtual void timeStep(const double tstart, const double tend) {}

    /// @brief Function to be implemented by the user, that analyses the agent-based model, and fills
    /// values of the variables (observations) that are plotted and used for cost.
    virtual void analyzeState(const double t) {}
};

/// @}



/// Example of a minimalistic model :
/// for simulating : Creation: --(KF)--> A --(K12)--> B --(K23)--> C --(KFB)--| A,
///                  with respecitve death/degradation rates KD1, KD2, KD3 for A,B and C
///                  and with a mutant where K12 is modified into K12m
///
/// struct ModelA1 : public Model {
///     ModelA1();
///     enum {A, B, C, NBVAR};							// List of variables
///     enum {KF, KD1, KD2, KD3, K12, K23, KFB, K12m, NBPARAM};	// List of parameters
///     enum {WT, MUT, NBBACK};                         // List of backgrounds
///     long long  background;
///
///     void initialise(long long _background = WT);
///     void setBaseParameters();
///     void one_step(double _t, double _delta_t);
/// };
///
/// ModelA1::ModelA1() : Model(NBVAR, NBPARAM), background(WT) {
///     names[A] = string("PopA");
///     names[B] = string("PopB");
///     names[C] = string("PopC");
/// }
///
/// void ModelA1::setBaseParameters(){
///     params.clear(); params.resize(NBPARAM);     // to erase previous values
///     params[KF]   = 1e-3;
///     params[KD1]  = 1e-4;
///     params[KD2]  = 1e-6;
///     params[KD3]  = 1e-6;
///     params[K12]  = 1e-6;
///     params[K23]  = 1e-5;
///     params[KFB]  = 0.1;
///     params[K12m] = 1e-4;
///     setBaseParametersDone();
/// }
///
/// void ModelA1::initialise(long long _background){
///     background = _background;
///     val.clear();     val.resize(NBVAR, 0.0);        // to erase previous values
///     valTemp.clear(); valTemp.resize(NBVAR, 0.0);
///     init.clear();    init.resize(NBVAR, 0.0);
///     for(int i = 0; i < NBVAR; ++i){val[i] = init[i];}
///     t = 0;
///     initialiseDone();
/// }
///
/// void ModelA1::one_step(double _t, double delta_t){
///     double pK12 = (background == WT) ? params[K12] : params[K12m];
///     valTemp[A] = delta_t * (params[KF] * (1- val[C] / params[KFB]) - (params[KD1] + pK12) * val[A]);
///     valTemp[B] = delta_t * (pK12 * val[A] - (params[KD2] + params[K23]) * val[B]);
///     valTemp[C] = delta_t* (params[K23] * val[B] - params[KD3] * val[C]);
///     for(int i = 0; i < NBVAR; ++i){val[i] += valTemp[i];}
/// } */
///
/// // To perform simulations with this model (see below for 'simulate'):
///
/// ModelA1 A();
/// A.setBaseParameters();
/// // or : A.loadParameters(string("Params.txt"));, where Params.txt contains "8\t1e-3\t1e-4\t1e-6\t1e-6\t1e-6\t1e-5\t0.1\t1e-4\n"
/// A.initialise(A::WT);
/// A.simulate(100);
/// A.initialise(A::MUT);
/// A.simulate(100);



/*  // an example using all the possibilities :

namespace N     {enum {IL12, STAT4P, TBET, IFNG, R12, RL12, STAT4, RIFN, IFNGR, STAT1, STAT1P, SOCS1, NB_GLOB_VARS};}
namespace Back  {enum {WT, IFNGRKO, STAT4KO, TBETKO, NB_GLOB_BACK};}

struct Model110L : public Model {
    Model110L();
    enum  {IL12, STAT4P, TBET, NBVAR};
    enum {KD12, KDS4P, KDTBET, S4PEQ, CS4P, TBETEQ, CTBET, CTCR, BS4P, BTBET, NBPARAM};
    long long background;
    void one_step(double _t, double _delta_t);
    void initialise(long long _background = Back::WT);
    void setBaseParameters();
};

Model110L::Model110L() : Model(NBVAR, NBPARAM), background(Back::WT) {
    // overwrites the values of the generic constructor Model::Model()
    dt = 0.2;
    print_every_dt = 1200;

    names[IL12] = string("IL12");
    names[STAT4P] = string("STAT4P");
    names[TBET] = string("TBET");

    extNames[IL12] = GlobalName(N::IL12);
    extNames[STAT4P] = GlobalName(N::STAT4P);
    extNames[TBET] = GlobalName(N::TBET);



    #ifdef PRINT_KIN
    cerr << "Model for Th1 differentiation (M110L) Nb of parameters : " << NBPARAM << ", variables :" << NBVAR << endl;
    #endif
}

void Model110L::setBaseParameters(){
    params.clear();
    params.resize(NBPARAM);
    params[KD12] = 1.1e-4;
    params[KDS4P] = 2e-5;
    params[KDTBET] = 1e-5;
    params[S4PEQ] = 0.05;
    params[CS4P] = 1.0;
    params[TBETEQ] = 0.05;
    params[CTBET] = 1.0;
    params[CTCR] = 1.0;
    // params[BS4P] and params[BTBET] will be defined in initialize
    setBaseParametersDone();
}

void Model110L::initialise(long long _background){

    background = _background;
    val.clear();        val.resize(NBVAR, 0.0);
    valTemp.clear();    valTemp.resize(NBVAR, 0.0);
    init.clear();       init.resize(NBVAR, 0.0);

    // parameters that depend on other ones are better here in case one wants to use loadParameters
    params[BS4P]  = params[KDS4P] * params[S4PEQ];
    params[BTBET] = params[KDTBET] * params[TBETEQ] - params[CTBET] * params[S4PEQ] * params[TBETEQ] * (1 + params[CTCR]);
    if(params[BS4P]  < 0) params[BS4P] = 0;
    if(params[BTBET] < 0) params[BTBET] = 0;

    init[IL12]   = 0.0;
    init[TBET]   = params[TBETEQ];
    init[STAT4P] = params[S4PEQ];

    if(background == Back::STAT4KO) init[STAT4P] = 0.0;
    if(background == Back::TBETKO) init[TBET] = 0.0;

    for(int i = 0; i < NBVAR; ++i){val[i] = init[i];}
    t = 0;
}

void Model110L::one_step(double _t, double delta_t){
    valTemp[IL12] = delta_t * (- params[KD12] * val[IL12]);
    valTemp[STAT4P] = delta_t * (- params[KDS4P] * val[STAT4P] + params[BS4P] + params[CS4P] * val[IL12] * val[STAT4P]);
    valTemp[TBET] = delta_t * (- params[KDTBET] * val[TBET] + params[BTBET] + params[CTBET] * val[STAT4P] * val[TBET] * (1 + params[CTCR]));
    for(int i = 0; i < NBVAR; ++i){val[i] = valTemp[i];}
}


*/

#endif // Model_H


