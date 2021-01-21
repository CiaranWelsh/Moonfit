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

/// @defgroup Overrider Overrider
/// @brief Overriding (replacing) a variable by interpolated experimental data (linear or spline)
/// @{

typedef string key;

/// @brief A class to store multiple curves interpolated from experimental data points
struct overrider {
    enum typeData {
        NODATA, SPLINE, FUNCTION, NBDATATYPES
    };

    overrider();

    overrider(TableCourse *kinetics, bool useSplines = false);

    /// 1 - Data storage : list of curves stored as spline or function
    int nbIndices;                                  /// @brief Number of space allocated
    int nbIDsGiven;

    void reset();

    void extend(int newNbIndices);

    vector<typeData> typeStorage;                   /// @brief Each curve can be function / interpolated tata
    vector<tk::spline *> dataSpl;                    /// @brief Storage as a spline for each curve
    vector<double (*)(double)> dataFunct;           /// @brief OR : storage as a function (double --> double)

    std::map<key, int> name2ID;

    int getID(key extNameVariable);

    /// 2 - Accessing the data
    bool hasData(key index);                        /// @brief returns false if NODATA or if index > nbIndices
    double operator()(key index,
                      double value);    /// @brief gets interpolated value for curve nr index, at time value. if nodata, returns -1

    /// 3 - Adding curves to the data (by saying the index of the curve to add).
    ///     note : the data structure is automatically extended up to the index if it didn't exist yet. No risk of seg fault there.
    void learnSpl(key index, vector<double> xs, vector<double> ys, bool yesSplnoLinearInterpol);

    void learnFunct(key index, double (*f)(double));

    /// 4 - Storage to decide for each curve, if it will be used to replace data or not.
    vector<bool> override;                          /// @brief decision, for each curve, to use it or not to replace a variable during simulation
    bool operator()(key index);                    /// @brief returns override[i]. Returns false if out of bounds.
    void setOver(key nameVar = string(""),
                 bool value = true);/// @brief to decide which curve to override for later simulations. Use index = -1 to override everything

    string print();
};
/// @]

#endif /* overrider_h */
