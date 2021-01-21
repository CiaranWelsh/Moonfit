#ifndef TABLE_COURSE_H
#define TABLE_COURSE_H

#define typeTime double

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>      // std::setprecision
#include <cmath>
#include <fstream>

using namespace std;

/// @defgroup TableCourse Table Course
/// @brief Storing dynamical time-courses of variables (kinetics), as table, either experimental or simulated
/// @{

/// @brief Data structure to store the discrete kinetics of several variables (ideal for plotting simulations)
/// as a table (meaning, for a list of time-points, store the values of all these selected variables)
///
///     note : - for storing continuous kinetics, use the *overrider* class instead.
///            - for storing only some variables from some time-points, use the *evaluator* class instead
///
struct TableCourse {
    vector<double> attribut;            /// @brief List of time points (left column)
    vector<vector<double> *> storage; /// @brief data (2D) storage[i][j] = value at time point i (t = attribut[i]) of variable j (whose name is headers[j])
    vector<string> headers;             /// @brief Names of the variables (columns), size = nbVars + 1. The first header is the name of the table (or title of the left column (ex: time))
    int nbVar;                          /// @brief nb of variables
    int nbLignes;                       /// @brief nb of time points

    /// Reading a table from another table or from a file
    TableCourse(TableCourse *toCopy);   /// @brief copy from another one
    TableCourse(const TableCourse &tc);

    TableCourse(string fileToRead);     /// @brief reads from a file.
    /// @code
    /// SYNTAX of a TableCourse file (read or exported):
    ///
    /// nbRows(time-pts)     nbColumns(nbVars)
    /// headerLeft      headerVar1      headerVar2      ...
    /// time1           valVar1         valVar2         ...
    /// time2           valVar1         valVar2         ...
    /// ...
    /// @endcode

    /// Manually making and writing into a table
    TableCourse(int _nbVar);            /// @brief creates empty, number of columns
    ~TableCourse();

    void setHeader(int i,
                   string title);                    /// Danger : starts at index 1 for variables. Header[0] = titre of the table
    void addSet(double attr,
                vector<double> &toCopy);       /// @brief Add a line (i.e. the value of each variable at the new time (attr)
    void reset();

    /// Additional I/O :
    void read(string fileName);

    void save(string fileName, string title = string(""));

    vector<double> getTimeCourse(int var);

    vector<double> getTimePoints(int var = -1);

    double operator()(int vari, typeTime timej);

    TableCourse subKinetics(vector<int> timePoints,
                            vector<string> namesVariables = vector<string>()/* same names than are in the tablecourse headers */);

    int findPosition(string nameVariable);

    //void print();
    string print(bool fileExportVersion = true);
};
/// @}



#endif // TABLE_COURSE_H


