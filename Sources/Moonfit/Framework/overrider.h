#ifndef _overrider_h
#define _overrider_h
#include "spline.h"
#include "tableCourse.h"
#include <cstdio>
#include <cassert>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
using namespace std;
using namespace tk;     // for the spline library, see spline.h

/// ================= A class to store multiple curves (kinetic data and interpolates it) =========================

typedef string key;

struct overrider {
    enum typeData {NODATA, SPLINE, FUNCTION, NBDATATYPES};
    overrider();
    overrider(TableCourse * kinetics, bool useSplines = false);

    /// 1 - Data storage : list of curves stored as spline or function
    int nbIndices;                                  /// Number of space allocated
    int nbIDsGiven;
    void reset();
    void extend(int newNbIndices);
    vector<typeData> typeStorage;                   /// Each curve can be function / interpolated tata
    vector<tk::spline*> dataSpl;                    /// Storage as a spline for each curve
    vector<double (*)(double)> dataFunct;           /// OR : storage as a function (double --> double)

    std::map<key,int> name2ID;
    int getID(key extNameVariable);

    /// 2 - Accessing the data
    bool hasData(key index);                        /// returns false if NODATA or if index > nbIndices
    double operator ()(key index, double value);    /// gets interpolated value for curve nr index, at time value. if nodata, returns -1

    /// 3 - Adding curves to the data (by saying the index of the curve to add).
    ///     note : the data structure is automatically extended up to the index if it didn't exist yet. No risk of seg fault there.
    void learnSpl(key index, vector<double> xs, vector<double> ys, bool yesSplnoLinearInterpol);
    void learnFunct(key index, double (*f)(double));

    /// 4 - Storage to decide for each curve, if it will be used to replace data or not.
    vector<bool> override;                          /// decision, for each curve, to use it or not to replace a variable during simulation
    bool operator ()(key index);                    /// returns override[i]. Returns false if out of bounds.
    void setOver(key nameVar = string(""), bool value = true);/// to decide which curve to override for later simulations. Use index = -1 to override everything

    string print();
};











/* OLD ONE
 *
 * struct overrider  {
    int nbVars;
    vector<tk::spline> storage;
    vector<bool> overriding;

    void learnKinetics(int IDLocalVariable, vector<double> x, vector<double> y, bool YesSplineNoLinear){
        if(x.size() != y.size()) {cerr << "ERR: overrider::feedKinetics, x and y should have same size ...\n"; return;}
        if((IDLocalVariable < 0) || (IDLocalVariable >= nbVars)) {cerr << "ERR: overrider::feedKinetics, incorrect IDLocalVariable(" << IDLocalVariable << ") - there are " << nbVars << " variables.\n"; return;}
        storage[IDLocalVariable].set_points(x,y, YesSplineNoLinear);
        overriding[IDLocalVariable] = true;
    }

    void learnKinetics(int IDLocalVariable, TableCourse A, int TableCourseIDVariable, bool YesSplineNoLinear){
        learnKinetics(IDLocalVariable, A.getTimePoints(), A.getTimeCourse(TableCourseIDVariable), YesSplineNoLinear);
    }

    overrider(int _nbVars) :  nbVars(_nbVars) {
        storage.resize(nbVars);
        overriding.resize(nbVars, false);
    }
    double operator()(int IDLocalVariable, int t){
        if((IDLocalVariable < 0) || (IDLocalVariable >= nbVars)) return -1;
        return (storage[IDLocalVariable])(t);
    }

}; */

#endif /* overrider_h */
