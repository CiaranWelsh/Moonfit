#include "evaluator.h"
#include <set>

// default values:
int costConfig::typeCost = SQUARE_COST;
int costConfig::typeNorm = NO_NORM;

string costConfig::CurrentCost(){
    stringstream res;
    switch(typeCost){
        case SQUARE_COST: res << "RSS"; break;
        case SQUARE_COST_STD: res << "RSS + StdDev"; break;
        case LOG_COST: res << "Log"; break;
        case PROPORTION_COST: res << "Ratios"; break;
    }
    switch(typeNorm){
        case NO_NORM: res << " (No Norm)"; break;
        case NORM_AVERAGE: res << " Norm/Avg vars"; break;
        case NORM_NB_PTS: res << " Norm/Nb Points"; break;
        case NORM_AVG_AND_NB_PTS: res << " Norm/Avg and Nb Pts "; break;
    }
    return res.str();
}

// The log functions is
double boundedLog(double x){
    return 18.4207 + max(log(max(1e-8,x)), -18.4207);
}

// Function used to compute the cost of single values (Data, Sim, Data Stddev)
double fitnessFunction(double valueToCompare, double refExpectedValue, double StdDev){
    switch(costConfig::typeCost){
        case SQUARE_COST:{
            return (refExpectedValue- valueToCompare) * (refExpectedValue - valueToCompare);}
        case SQUARE_COST_STD:{
            if(fabs(StdDev < 1e-8)) return (refExpectedValue - valueToCompare) * (refExpectedValue - valueToCompare);
            return (refExpectedValue- valueToCompare) * (refExpectedValue - valueToCompare) / (StdDev * StdDev);}
        case LOG_COST:{
            return fabs(boundedLog(fabs(refExpectedValue)) - boundedLog(fabs(valueToCompare)));}
        case PROPORTION_COST:{
            if(fabs(fabs(refExpectedValue) < 1e-3)) return fabs(valueToCompare) * 1000;
            return fabs((refExpectedValue- valueToCompare) / refExpectedValue);}
        default:{
            cerr << "No cost function policy defined. Please put choose a type cost in evaluator.h (struct costConfig), or define your own cost function \n";
            return NAN;}
    }
    return NAN;
}

/// Here, you can define a penalty in the cost when the simulation stopped before this point, so no data was recorded for that point.
#define penaltyNotRecorded 0.0




double Evaluator::getFitnessSpecies(int _Species){
    int nbVals = 0; double addCosts = 0;
    double averageData = 0;
    for(int i = 0; i < nbPoints; ++i){
        if(Species[i] == _Species){
            nbVals++;
            averageData += ExpectedValues[i];
            addCosts += fitnessFunction(simuData[i], ExpectedValues[i], StdDeviations[i]);
        }
    }
    if(nbVals == 0) {return 0;}
    if(nbVals > 0) averageData /= nbVals;
    if((costConfig::typeNorm == NORM_AVERAGE) || (costConfig::typeNorm == NORM_AVG_AND_NB_PTS)){
        if(fabs(averageData) > 1e-15) addCosts /= (averageData * averageData);
    }
    if((costConfig::typeNorm == NORM_NB_PTS) || (costConfig::typeNorm == NORM_AVG_AND_NB_PTS)){
        addCosts /= nbVals;
    }
    return addCosts;
}

double Evaluator::getTotalFitness(){
    double addCosts = 0;
    if(costConfig::typeNorm == NO_NORM){
        int nbVals = 0;
        for(int i = 0; i < nbPoints; ++i){
                nbVals++;
                addCosts += fitnessFunction(simuData[i], ExpectedValues[i], StdDeviations[i]);
        }
        if(nbVals == 0) {return NAN;}
    } else { // if normalization, calls getFitness species for each of them separately
        std::set<int> listSpecies;
        for(int i = 0; i < nbPoints; ++i){
            int thisSpecies = Species[i];
            if(listSpecies.find(thisSpecies) == listSpecies.end()){ // i.e. not yet in the list
                addCosts += getFitnessSpecies(thisSpecies);
                listSpecies.insert(thisSpecies);
            }
        }
    }
    return addCosts;
}

// note: this function is not normalized, just point by point
double Evaluator::getFitnessPoint(int _Species, typeTime _time_sec){
    int a = findIndex(_Species, _time_sec);
    if(a < 0) {
        cerr << "ERR: Species = " << _Species << ", t = " << _time_sec << " sec, not found in evaluator record !!\n";
        return 0;
    }
    if(! recorded[a]) return penaltyNotRecorded;
    return fitnessFunction(simuData[a], ExpectedValues[a], StdDeviations[a]);
}

string Evaluator::reportTotalFitness(){
    int nbVals = 0; double addCosts = 0;
    stringstream ss;
    ss << "List of cost point by point, but without normalization per variable" << endl;
    ss << "time\tvariable\tsimulation\tdata\tstddev\tlocalCost\n";
    for(int i = 0; i < nbPoints; ++i){
            nbVals++;
            addCosts = fitnessFunction(simuData[i], ExpectedValues[i], StdDeviations[i]);
            ss << Times[i] << "\t" << Species[i] << "\t" << simuData[i] << "\t" << ExpectedValues[i] << "\t" << StdDeviations[i] << "\t" << addCosts << endl;
    }
    if(nbVals == 0) {
        return string("No Data for this evaluator.");}
    ss << "List of cost, per variable, including normalizations " << endl;
    ss << "Cost function used: " << costConfig::CurrentCost() << endl;
    ss << "variable\tNorm cost\n";
    std::set<int> listSpecies;
    for(int i = 0; i < nbPoints; ++i){
        int thisSpecies = Species[i];
        if(listSpecies.find(thisSpecies) == listSpecies.end()){ // i.e. not yet in the list
            ss << thisSpecies << "\t" << getFitnessSpecies(thisSpecies) << endl;
            listSpecies.insert(thisSpecies);
        }
    }
    return ss.str();
}

void testFitnessFunction(){
    vector<double> exp = {0, 0, 0.1, 0.1, 0.1, 1, 1, 1,      1.5,   1.5, 2,     5, 5, 5, 5,     10, 0.00001, 0.00001, 0.001};
    vector<double> mes = {0, 1, 0.1, 0.3, 1  , 1, 2, 0.0001, 1000,  0,   1.5,   3, 4, 5, 10,    100,0.0001,  0.001,    1};
    int L = exp.size();
    for(int i = 0; i < L; ++i){
        cout << std::setprecision(8) << "Exp= " << exp[i] << ",   \tmes= " << mes[i] << "   \tcost= " << fitnessFunction(mes[i], exp[i], 0) << "\t\t" << boundedLog(exp[i]) << "," << boundedLog(mes[i]) << endl;
    }
}








Evaluator::Evaluator() : recording_before_simulation(true), nbPoints(0), nextTimePoint(1e8) {
        Species.clear();
        Times.clear();
        simuData.clear();
        recorded.clear();
        ExpectedValues.clear();
        StdDeviations.clear();
}
string Evaluator::printState(){
    stringstream res;
    res << "Eva : " << nbPoints << " pts, nextTime=" << nextTimePoint << endl;
    for(int i = 0; i < nbPoints; ++i){
        res << "Sp="<< Species[i] << "\t=" << Times[i] << ", val=" << simuData[i] << ", expected= " << ExpectedValues[i] << ", std-dev=" << StdDeviations[i] << ", rec=" << (recorded[i] == true ? "Oui" : "Non") << "\n";
    }
    return res.str();
}

// This function takes a table of time/variables (a kinetics, type Tablecourse), and optionally a table of standard deviations (same points : time & variables)
// + it takes the list of external names of variables in the model. So it converts the names of headers in the kinetics
// into the ID of the variable inside the model.
bool Evaluator::getValsFromKinetics(TableCourse* _expectedValues, vector<string> listExtNamesVarsInModel, TableCourse* _StdDevs){

    if(! _expectedValues) {cerr << "ERR GetValFromKinetics(), empty table course for expected values\n"; return false;}
    vector<string> heads = _expectedValues->headers;
    vector<typeTime> timepts = _expectedValues->getTimePoints();

    // If a StdDev table is given, it should have the same time-points and same variables in the same order !!
    vector<string> heads2 = (_StdDevs ? _StdDevs->headers : vector<string> ());
    vector<typeTime> timepts2 = (_StdDevs ? _StdDevs->getTimePoints() : vector<typeTime> ());
    if(_StdDevs) if(heads.size() != heads2.size()){cerr << "ERR: Evaluator::getValsFromKinetics(), the two tables should have same sizes and headers"; return false;}
    if(_StdDevs) if(timepts.size() != timepts2.size()){cerr << "ERR: Evaluator::getValsFromKinetics(), the two tables should have same sizes and headers"; return false;}

    int nbTimePoints = timepts.size();
    int nbHeaders = heads.size();
    int sizeNames = listExtNamesVarsInModel.size();

    //cout << "getVals" << nbHeaders << endl;
    for(int nt = 0; nt < nbTimePoints; ++nt){
        if(_StdDevs) if(timepts[nt] != timepts2[nt]) {cerr << "ERR : getValsFromKinetics, the kinetics for expected values and std deviations have different time points\n"; return false;}
        for(int i = 1; i < nbHeaders; ++i){        // headers[0] is the title of the table
            if(_StdDevs) if(heads[i].compare(heads2[i])) {cerr << "ERR: Evaluator::getValsFromKinetics(), the two tables should have same sizes and headers"; return false;}
            for(int j = 0; j < sizeNames; ++j){
                if(! listExtNamesVarsInModel[j].compare(heads[i])) {        // Note: a model can contain two times the same external name, it's fine. For instance if model simulates the same external variable by two different ways (two internal variables) or so
                    double currentExpValue = ((*_expectedValues)(i-1, nt));
                    if(!((std::isnan(currentExpValue) || std::isinf(currentExpValue)))){
                        getVal(j, timepts[nt], (*_expectedValues)(i-1, nt), (_StdDevs ? (*_StdDevs)(i-1, nt) : 0));
                    }
                }
            }
        }
    }

    return true;
}


double Evaluator::getVal(int _Species, typeTime _time_sec, double _expectedValue, double _stdDev){
    if(recording_before_simulation && (_expectedValue >= 0) && (! std::isnan(_expectedValue))){    // negative values forbidden for kinetics --> excluded for cost
        //cerr << "Requires species " << _Species << " at time " << _time_sec << endl;
        if(findIndex(_Species, _time_sec) >= 0) return 0;
        else {
            nbPoints++;
            Species.push_back(_Species);
            Times.push_back(_time_sec);
            ExpectedValues.push_back(_expectedValue);
            StdDeviations.push_back(_stdDev);
            return 0;
        }
    } else {
        int a = findIndex(_Species, _time_sec);
        if(a < 0) {
            cout << "   WRN : Species = " << _Species << ", t = " << _time_sec << " sec, not found in evaluator record !!\n";
            return 0;}
        else {
            if(! recorded[a]) cout << "WRN: data not recorded for species " << _Species << "/n";
            return simuData[a];
        }
    }
}

int Evaluator::findIndex(int _Species, typeTime _time_sec){
    for(int i = 0; i < nbPoints; ++i){
        if((Species[i] == _Species) && (Times[i] == _time_sec)) return i;}
    return -1;
}
void Evaluator::recordingCompleted(){
    simuData.clear();
    simuData.resize(nbPoints, 0.0);
    recording_before_simulation = false;
    recorded.clear();
    recorded.resize(nbPoints, false);
    updateNextPoint();
}
typeTime Evaluator::updateNextPoint(){
    for(int i = 0; i < nbPoints; ++i){
        if((! recorded[i]) && (Times[i] < nextTimePoint))
            nextTimePoint = Times[i];}
    return nextTimePoint;
}

bool Evaluator::takeDataAtThisTime(typeTime t_sec){
    if(t_sec < nextTimePoint) return false;
    return true;
}

int Evaluator::speciesToUpdate(){
    for(int i = 0; i < nbPoints; ++i){
        if((Times[i] == nextTimePoint) && (recorded[i] == false)) return Species[i];
    }
    nextTimePoint = 1e8;
    updateNextPoint();
    return -1;
}

void Evaluator::setValNow(int _Species, double value){
    int a = findIndex(_Species, nextTimePoint);
    if(a < 0) {cerr << "ERR : SetValNow(" << _Species << ", ) for t=" << nextTimePoint << " not found in wish list\n"; return;}
    simuData[a] = value;
    //cerr << "   ... data added : Sp=" << _Species << ", t=" << nextTimePoint << ", val=" << value << endl;
    recorded[a] = true;
}

int Evaluator::size(){
    return nbPoints;
}

typeTime Evaluator::nextPoint(){
    return nextTimePoint;
}

void Evaluator::resetDataKeepingExpected(){
    simuData.clear();
    simuData.resize(nbPoints, 0.0);
    recording_before_simulation = false;
    nextTimePoint = 1e8;
    recorded.clear();
    recorded.resize(nbPoints, false);
    updateNextPoint();
}

/* vector<int>         Species;
vector<typeTime>    Times;
/// additionally, the experimental (expected) and their standard deviation can be given & stored,
vector<double>      ExpectedValues;
vector<double>      StdDeviations;
/// table that have to be filled with data using setValNow (initially, recorded[..] = false
vector<double>      theData;
vector<bool>        recorded;
*/

double Evaluator::getExpVal(int _Species, typeTime _time_sec){
    if(recording_before_simulation){
        cerr << "ERR: Evaluator::getExpVal, you are still in 'recording phase' and you are not supposed to access any data at this point./n";
        return 0;
    }
    int a = findIndex(_Species, _time_sec);
    if(a < 0) {
        cerr << "ERR: Species = " << _Species << ", t = " << _time_sec << " sec, not found in evaluator record !!\n";
        return 0;}
    else return ExpectedValues[a];
}

double Evaluator::getStdDev(int _Species, typeTime _time_sec){
    if(recording_before_simulation){
        cerr << "ERR: Evaluator::getExpVal, you are still in 'recording phase' and you are not supposed to access any data at this point./n";
        return 0;
    }
    int a = findIndex(_Species, _time_sec);
    if(a < 0) {
        cerr << "ERR: Species = " << _Species << ", t = " << _time_sec << " sec, not found in evaluator record !!\n";
        return 0;}
    else return StdDeviations[a];
}



double Evaluator::contains(int _Species){
    for(int i = 0; i < nbPoints; ++i){
        if(Species[i] == _Species){
            return true;
        }
    }
    return false;
}





