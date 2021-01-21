// Philippe Robert, 09-02-2020 - philippe [dot] robert [at] ens-lyon [dot] org
#ifndef EVALUATOR_H
#define EVALUATOR_H

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>      // for std::setprecision
#include <cmath>
#include <utility>      // for std::pair
#include <sstream>

using namespace std;

#include "tableCourse.h"



/// @defgroup CostEval Cost Definitions
/// @brief The cost of a simulation versus data is first evaluated point-by-point (fitnessFunction)
/// and then at the scale of a simulation by the evaluator class. Different cost functions
/// and normalizations are defined here.
/// @{



/// @brief Main function to calculate the cost for one data-point, between simulation and experimental data.
/// This function can calculate the different possible costs defined below. See the class evaluator for
/// the cost calculation of whole simulations.
double fitnessFunction(double measured, double expected, double StdDev_or_zero);


/// @brief Different types of costs (between a simulation and experimental dataset),
/// this will define how each data-point is treated. See fitnessFunction().
/// with Xi the simulated datapoint and Ei the experimental one,
///
/// - SQUARE_COST (RSS) gives the square difference at this data-point:
///     (Xi - Ei)^2
///
/// - SQUARE_COST_STD (RSS) sums the square difference at this time-point, divided by square of
///     experimental given standard deviation. If no standard deviation, uses 1. instead.
///     Std values less than 1e-8 are not counted (see minimumBoundaryStandardDeviations below).
///     (Xi - Ei)^2 / Stdi^2,   Stdi > 1e-8
///
/// - LOG_COST sums the absolute difference between the ln of simulation versus data.
///     the log is rescaled such that values lower than 1e-8 all return a ln of zero.
///     (see minimumBoundaryLogCost below)
///     Abs(ln(Xi) - ln(Ei)),   Xi, Ei > 1e-8
///
/// - PROPORTION_COST returns the ratio between experimental to experimental.
///     Denominator values less than 1e-3 stay 1e-3 (see minimumBoundaryProportionCost below)
///     abs(Xi / max(1e-3, Ei))
///
/// Note that it will be possible to give an artificial penalty when a simulation crashed and a data-point
/// has not been computed (see 'penaltyNotRecorded' below. By default it is 0).
enum {
    SQUARE_COST, SQUARE_COST_STD, LOG_COST, PROPORTION_COST
};


/// @brief Different types of normalizations, that will be done by the evaluator class.
/// Note that each condition receives an independent cost calculation. Therefore a normalization
/// is done WITHIN one condition separately.
///
/// - NO_NORM: Equally sums the costs of each datapoints (fitness function), for each variable in this condition.
///
/// - NORM_AVERAGE: For each variable, takes the experimental average of this variable
///     over the experimental time-points (curve) of this condition. Each data-point cost (fitness function)
///     will be divided by this **average square**. Therefore, only use for SQUARE costs.
///     Be careful that the average of a variable in different conditions will be different, so
///     each curve's cost will be normalized differently. This can be good or bad depending on the
///     problem.
///
/// - NORM_NB_PTS: For each variable, the cost of the time-points is divided by the number of
///     experimental datapoints of this variable in this condition.
///
/// - NORM_MAX: For each variable, takes the experimental maximum of this variable
///     over the experimental time-points (curve) of this condition. Each data-point cost (fitness function)
///     will be divided by this **maximum square**. Therefore, only use for SQUARE costs.
///     Be careful that the maximum of a variable in different conditions will be different, so
///     each curve's cost will be normalized differently. This can be good or bad depending on the
///     problem.
///
/// - NORM_AVG_AND_NB_PTS: divides by both the average square and the nb of points.
///
/// - NORM_MAX_AND_NB_PTS: divides by both the maximum square and the nb of points.
///
enum {
    NO_NORM, NORM_AVERAGE, NORM_NB_PTS, NORM_AVG_AND_NB_PTS, NORM_MAX, NORM_MAX_AND_NB_PTS
};


/// @brief Static class that stores the current type of cost and normalization used for fitting \ingroup CostEval
struct costConfig {
    static int typeCost;
    static int typeNorm;

    /// @brief Outputs the current type of cost and normalization \ingroup CostEval
    static string CurrentCost();
};

/// @brief Change the type of Cost
void setTypeCost(int _typeCost);

/// @brief Change the type of Normalization
void setTypeNorm(int _typeNorm);


/// @brief Predefined boundaries for the fitness function when experimental or simulated values get extreme,
/// to avoid that the cost calculation diverges.
#define minimumBoundaryLogCost 1e-8
#define minimumBoundaryProportionCost 1e-3
#define minimumBoundaryStandardDeviations 1e-8


/// a test function for the current fitness function
void testFitnessFunction();
/// @}






/// @defgroup Eval Cost Evaluation
/// @brief The class Evaluator stores datapoints for each variables during one simulation (one condition).
/// - it stores a list of: Variable - time-point - experimental value - experimental std_dev - simulated data
/// - it handles the calculation of a simulation cost for all the variables' datapoints in this conditions.
/// - It handles the different types of normalizations per variable. However, it has no information on the
/// simulation results of other conditions. Each experimental condition will have its own evaluator class.
/// @{



/// ============================ Evaluator structure: WISH-LIST with experimental datapoints ========================
/// this structure stores a list of values (species-time point) to be compared with simulations later.
/// basically, you say first which couples of (time-point, variable) you want to record,
/// (you can give expected values, it's optional). During the simulation, you provide the simulation values
/// and after the simulation, you can also retrieve these values - it avoids to record a whole simulation,
/// but will just store the wished data-points.
///
/// Automatic use:
///     The class Experiment and Model automatically take care of loading the evaluators before a simulation and retrieving
///     the cost of a simulation afterwards => you usually don't need to use this class manually.
///
/// Manual use example :

/** @code
 void testeEvaluator() {
     Evaluator E = Evaluator();

     // says variables 1, 3 and 5 need to be recorded at these time-points
     E.getVal(1,15);
     E.getVal(3,20);
     E.getVal(1,20);
     E.getVal(5,50);

     E.recordingCompleted();

     //during simulation
     //E.printState();
     for(int i = 0; i < 100; ++i){
         if(E.takeDataAtThisTime(i)){
             int z = E.speciesToUpdate();
             while(z >= 0){
                 // fills the simulated data (z*100 here) at this time point only
                 E.setValNow(z, (double) (i + z*100));
                 // gets the next species/variable that needs to be recorded.
                 z = E.speciesToUpdate();
             }
             //E.printState();
         }
     }
     cerr << "\n";
     // retrieves the simulated values
     cerr << E.getVal(1,15) << "\t";
     cerr << E.getVal(3,20) << "\t";
     cerr << E.getVal(1,20) << "\t";
     cerr << E.getVal(5,50) << "\n";
     cerr << E.printState();
 }
 @endcode **/
///     - before the simulation,
///         => call 'double getVal(species, time, expectedValue = 0, stdDev = 0)' to add this point
///         in the wish list (you don't need to provide an expected value nor a standard deviation)
///
///             OR
///
///         => call bool getValsFromKinetics(TableCourse* _expectedValues, vector<string> listExtNamesVarsInModel, TableCourse* _StdDevs = nullptr)
///         where vector<string> listExtNamesVarsInModel gives the name to be read in the TableCourse for each
///         variable in the model in the same order.
///     - to complete the wish list, call   'void recordingCompleted();'
///     - during the simulation, call       'bool takeDataAtThisTame(int t_sec)' to see if
///         there are wished data at this time point (or earlier time-points that were missed)
///     - then, call                        'int speciesToUpdate();'  to know which vaiables are desired
///         for this time-point (continue until the function gives -1, meaning 'no more species desired'
///     - for each variable, call           'void setValNow(int _Species, double value); to give
///         the value to the evaluator
///     - then, each recorded simulated data can be accessed by   'double getVal(species, time)'
///         note that this is the same function for adding a data-point and getting the simulated value.
///         [It can be handy if you use self-made cost functions, to call it once before and once after]
///     - to re-access the experimental value, for each, call 'double getExpVal(species, time)'
///
///  --> note:
/// 	- to save memory : inside evaluator, no time kinetics are stored excepted wished values
///
struct Evaluator {
public:
    Evaluator();

private:
    /// @brief Storage: list of pairs<species, time> wanted. Note. species = variable.
    /// nbPoints = nb couples (Species[i], Times[i])
    int nbPoints;
    vector<int> Species;
    vector<typeTime> Times;
    /// @brief additionally, the experimental (expected) and their standard deviation can be given & stored,
    vector<double> ExpectedValues;
    vector<double> StdDeviations;
    /// @brief table for simulated values that have to be filled with data using setValNow, then recorded[i] = true.
    /// note: initially, recorded[..] = false.
    vector<double> simuData;
    vector<bool> recorded;

public:
    /// @brief: means : 'I want the value of this species(=variable) at this time point'
    /// during recording phase, returns 0 but stores the (species, time-point) in the wish list
    /// when recording is completed, returns the recorded value.
    double getVal(int _Species, typeTime _time_sec, double _expectedValue = 0, double _stdDev = 0);

    /// @brief: means : 'I want the value of these species(=variables) at these time point',
    /// stored in a Table (TableCourse class)
    /// Note: the data points with NAN or inf are not taken into the list of "wish list to record" points.
    /// Possible to add multiple TableCourse one by one, and when experimental values are missing, write 'nan'
    bool getValsFromKinetics(TableCourse *_expectedValues, vector<string> listExtNamesVarsInModel,
                             TableCourse *_StdDevs = NULL);

    /// @brief means : the wish list is complete, now I can use 'takeDataAtThisTime?' and 'setValNow'
    void recordingCompleted();

private:
    bool recording_before_simulation;


public:
    int size();

    /// @brief requests if a species - time point is in the wish list. returns -1 if not found
    int findIndex(int _Species, typeTime _time_sec);

    /// @brief Returns the next wanted time-point. when finished, returns 1e8
    typeTime nextPoint();

private:
    /// @brief calculates the next wanted time-point (minimum of not-recorded-yet time points) - when finished, returns 1e8
    typeTime updateNextPoint();

    typeTime nextTimePoint;


public:
    /// @brief says if data is required at this time point. Says no until the time is equal or later than
    /// the next time-point to record (in case the time-step of simulation doesn't fall exactly at that time).
    bool takeDataAtThisTime(typeTime t_sec);

    /// @brief gives the next wanted species for the current 'nextTimePoint' ; gives -1 when time point is completed,
    /// you need to have updated all the values and then the last call of this function will update the next point automatically
    int speciesToUpdate();

    /// @brief to fill the experimental value for a couple (Species-Value)
    void setValNow(int _Species, double value);

    /// @brief is this variable/species inside the wish list?
    double contains(int _Species);

    /// @brief retrieve experimental value
    double getExpVal(int _Species, typeTime _time_sec);

    /// @brief retrieve experimental standard deviation
    double getStdDev(int _Species, typeTime _time_sec);

    /// @brief get the cost of one time-point (after it is recorded).
    /// this does not include normalizations
    double getFitnessPoint(int _species, typeTime _time_sec);

    /// @brief get the summed cost of a full variable/species among all time-points.
    /// this includes normalization
    double getFitnessSpecies(int _species);

    /// @brief Sums the cost of each variable (with normalization)
    double getTotalFitness();

    /// @brief Gives a written report of the individual cost of each variable and data-point.
    string reportTotalFitness();

    /// @brief Outputs all the information stored in the evaluator so far.
    string printState();

    /// @brief Clears the simulated data but keeps the experimental values.
    void resetDataKeepingExpected();

    typedef int iteratorForEvaluator;

    iteratorForEvaluator begin() { return 0; }

    iteratorForEvaluator end() { return nbPoints; }

    pair<int, typeTime> operator()(iteratorForEvaluator i) { return pair<int, typeTime>(Species[i], Times[i]); }
};

/// @brief Here, you can define a penalty in the cost when the simulation stopped before this point, so no data was recorded for that point.
#define penaltyNotRecorded 0.0

/// @}








#endif // EVALUATOR_H
