#ifndef COMMON_H
#define COMMON_H





// This is a common header that all files of the project are including
// In theory, you don't need to change this file to perform simulations, but rather for fine-tuning of compiling options.

// 1 - please specify if you want to exclude the Qt Library from the compiling (then, say #define WITHOUT_QT )
//     to compile without QT, I suggest to use the ...NoQt.pro file, which defines WITHOUT_QT automatically.
//#define WITHOUT_QT

// 2 - please specify which graphical library you want to use for plotting : QWT or QCP=QCustomPlot,
// DO NOT USE BOTH !!
//#define USE_QWT
#define USE_QCP

/* Note : the QWT library requires the following modules of QT, which have to be given in the .pro file by using :
QT += printsupport
QT += opengl
QT += svg
You don't need these modules for QCP, and they are not suitable for static compiling (personal experience)
*/

//3 - Please define if automatically generated models (by the class generate.h) should be compiled or not (to avoid weird behaviour).
//#define COMPILE_AUTOGEN

//4 -  Now, the code below automatically detects the version of QT and the platform,
// and will define the proper tags (QT4, QT5, WINDOWS, UNIX, MAC) automatically, to be used by all the files of the folder
//
// NOTE : in case of platform problems in linux, this package might be required
// sudo apt-get install build-essential g++

// =========  please don't touch anything below !... ===========
#ifndef WITHOUT_QT
#include <QtGlobal>
#if QT_VERSION >= 0x050000
#define QT5
#else
#define QT4
#endif
#endif

#ifdef _WIN32
//define something for Windows (32-bit and 64-bit, this part is common)
#define WINDOWS
#ifdef _WIN64
   //define something for Windows (64-bit only)
#endif
#elif __APPLE__
#define MAC

#include "TargetConditionals.h"

#if TARGET_IPHONE_SIMULATOR
// iOS Simulator
#elif TARGET_OS_IPHONE
// iOS device
#elif TARGET_OS_MAC
// Other kinds of Mac OS
#else
#   error "Unknown Apple platform"
#endif
#elif __linux__
#define UNIX
// linux
#elif __unix__ // all unices not caught above
#define UNIX
// Unix
#elif defined(_POSIX_VERSION)
// POSIX
#else
#   error "Unknown compiler"
#endif

#ifdef WINDOWS
#include <windows.h>
#endif

#ifdef UNIX
#include <sys/stat.h>
#endif

#include <string>
#include <vector>

using namespace std;

void createFolder(string folderName);       // because this sh** is OS dependent, better in a function

vector<string> listSubDirectories(string dir);

string removeFolderFromFile(string file);

string
codeTime();                                              /// @brief a function to give a different name each time called (based on the time)
void compileLatex(string folderRes,
                  string texFile);            /// @brief ask the system to compile a tex file and put the result in folderRes
void mergePDFs(vector<string> &listFiles, string outputFile,
               string compilingFolder = "");  /// @brief merges PDF files into one with a new name

bool dirExists(string dirName);

string currentDir();

string getParentFolder(string dir);

vector<string> getAllResultSubFolders(string dir); // folders containing a 'History' file
vector<string> listFilesInDir(string dir, string containing = string(""));

string locateProjectDirectory(string projectFileToFind = string("")); // if not stated, will look for "AllProjects.pro"
vector<string> findAllResultFolders(string dir);

void printVector(vector<string> v);

void testDirectoryFunctions();

string printVector(vector<double> &v);

/// @brief standardization of common options for optimizing.
enum typeOptimizer {
    GeneticFast,
    SRESFast,
    Genetic25k,
    Genetic50k,
    Genetic100k,
    Genetic250k,
    Genetic500k,
    Genetic1M,
    SRES25k,
    SRES50k,
    SRES100k,
    SRES250k,
    SRES500k,
    SRES1M,
    GeneticAllCombs25k,
    GeneticAllCombs50k,
    GeneticAllCombs100k,
    GeneticAllCombs250k
};

string optName(typeOptimizer toUse);

string optFileHeader(typeOptimizer toUse);


#endif // COMMON_H
