
#include "common.h"
#include <sstream>

#include <iostream>
#include <fstream>
#include <ctime>
#include <iostream>
#include <stdio.h>

using namespace std;

#ifdef WINDOWS
#include <windows.h>
#include <io.h>
#endif
#if defined(UNIX) || defined(MAC)

#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#endif


/**
 * (cw) macros for including the filesystem on c++17 in cross platform way.
 * This way I don't have to figure out how to fix old code in cross platform way
 * Usage: fs namespace to replace both filesystem and experimental::filestsyem
 */
#if __cplusplus >= 201703L // c++17 or above

// if using gcc 8.0 or greater we can use <filesystem>
// otherwise we need experimental/filesystem
//#pragma message( "Compiling " __FILE__ )
//#define CPLUSPLUS(X) #X
//#define SCPLUSPLUS(X) CPLUSPLUS(X)
//#pragma message( "The value of __cplusplus is: " SCPLUSPLUS(__cplusplus) )
#   ifdef __linux__
/*
 *      For gcc 4.0.1
 *      #define __GNUC__ 4
 *      #define __GNUC_MINOR__ 0
 *      #define __GNUC_PATCHLEVEL__ 1
 *
 */
#       if __GNUC__ >= 8
#          include <filesystem>
namespace fs = std::filesystem;
#        else
#       include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#       endif
#   else
/**
 * we assume microsoft and apple have their shit together
 */
#   include <filesystem>
namespace fs = std::filesystem;

#   endif //__linux__
#endif // __cplusplus >= 201703L


bool dirExists(const string& dirName) {

#if defined(UNIX) || defined(MAC)
    struct stat info;

    if (stat(dirName.c_str(), &info) != 0)
        return false;
    else if (info.st_mode & S_IFDIR)
        return true;
    else
        return false;
#endif
#ifdef WINDOWS

    DWORD ftyp = GetFileAttributesA(dirName.c_str()); // from Kernel32.dll
    if (ftyp == INVALID_FILE_ATTRIBUTES)
      return false;  //something is wrong with your path!

    if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
      return true;   // this is a directory!

    return false;    // this is not a directory!
#endif
}


#if __cplusplus >= 201703L
void createFolder(const string &folderName) {
    if (fs::is_directory(folderName)) {
        return;
    } else {
        fs::create_directory(folderName);
    }
}

#else

void createFolder(string folderName){

#ifdef WINDOWS
    // .................. Now this is all the shit required to create a folder in windows : .............. need to be in the wchar* type, not char*, so need to convert.
    const char *p= folderName.c_str(); const WCHAR *pwcsName;
    int nChars = MultiByteToWideChar(CP_ACP, 0, p, -1, NULL, 0);
    pwcsName = new WCHAR[nChars];
    MultiByteToWideChar(CP_ACP, 0, p, -1, (LPWSTR)pwcsName, nChars);
    CreateDirectory(pwcsName, NULL); delete [] pwcsName;
#endif

#if defined(UNIX) || defined(MAC)
const int dir_err = mkdir(folderName.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
if ((-1 == dir_err) && (errno != EEXIST)){cerr << "Error creating directory : " << folderName << endl;}
#endif
}
#endif


string removeFolderFromFile(string file) {
    int S = file.size();
    int cpt = 0;
    for (int i = 0; i < S; ++i) {
        if ((file[i] == '\\') || (file[i] == '/')) {
            cpt = i + 1;
        }
    }
    return file.substr(cpt, S - cpt);
}


// listing the subfolders in a folder :
// from http://stackoverflow.com/questions/6133647/how-do-i-list-subdirectories-in-windows-using-c




using namespace std;
#if __cplusplus >= 201703L
std::vector<std::string> listSubDirectories(const std::string& dir){
    std::vector<std::string> r;
    for(auto& p : fs::recursive_directory_iterator(dir))
        if (fs::exists(p))
            r.push_back(p.path().string());
    return r;
}

#else

#ifdef WINDOWS
// here, keep the whole path
vector<string> listSubDirectories(string dir)
{
    vector<string> res;
    char originalDirectory[_MAX_PATH];

    // Get the current directory so we can return to it
    _getcwd(originalDirectory, _MAX_PATH);

    //SetCurrentDirectory(dir.c_str())
    chdir(dir.c_str());  // Change to the working directory
    _finddata_t fileinfo;

    // This will grab the first file in the directory
    // "*" can be changed if you only want to look for specific files
    intptr_t handle = _findfirst("*", &fileinfo);

    if(handle == -1)  // No files or directories found
    {
        perror("Error searching for file");
        exit(1);
    }

    do
    {
        if(strcmp(fileinfo.name, ".") == 0 || strcmp(fileinfo.name, "..") == 0)
            continue;
        if(fileinfo.attrib & _A_SUBDIR){ // Use bitmask to see if this is a directory
            //cout << "This is a directory : " << fileinfo.name << endl;
            res.push_back(dir + string(fileinfo.name) + string("/"));
        }
        else
        {//cout << "This is a file : " << fileinfo.name << endl;
        }
    } while(_findnext(handle, &fileinfo) == 0);

    _findclose(handle); // Close the stream

    chdir(originalDirectory);
    return res;
}
#endif // ifdef WINDOWS



#if defined(UNIX) || defined(MAC)

// here, keep the whole path
vector<string> listSubDirectories(string namedir) {
    vector<string> res;
    DIR *dir = opendir(namedir.c_str());
    struct dirent *entry;
    if (!(entry = readdir(dir))) { return res; }
    do {
        if ((!string(entry->d_name).compare(string("."))) ||
            (!string(entry->d_name).compare(".."))) // didnt find strcomp ... don't like it anyways
            continue;
        if (entry->d_type == DT_DIR) {
            res.push_back(namedir + string(entry->d_name) + string("/"));
        } else {//cout << "This is a file : " << fileinfo.name << endl;
        }
    } while ((entry = readdir(dir)) != NULL);
    closedir(dir);
    return res;
}

#endif
#endif // #if __cplusplus >= 201703L


#if __cplusplus >= 201703L
string currentDir() {
    return fs::current_path().string();
}
#else

#ifdef WINDOWS
string currentDir(){
    char originalDirectory[_MAX_PATH];
    _getcwd(originalDirectory, _MAX_PATH);
    string res = string(originalDirectory);
    res.replace(res.begin(), res.end(), '\\', '/');
    return res;
}
#endif


#if defined(UNIX) || defined(MAC)

string currentDir() {
    char originalDirectory[1024];
    getcwd(originalDirectory, 1024);
    string res = string(originalDirectory);
    //replace(res.begin(), res.end(), '\\', '/');
    return res;
}

#endif
#endif // #if __cplusplus >= 201703L


// from http://www.cplusplus.com/reference/string/string/find_last_of/
/*void SplitFilename (string& str)
{
  size_t found;
  cout << "Splitting: " << str << endl;
  found=str.find_last_of("/\\");
  cout << " folder: " << str.substr(0,found) << endl;
  cout << " file: " << str.substr(found+1) << endl;
  return
}*/

string getParentFolder(string dir) {
    if (dir.size() == 0) return dir;
    if ((dir[dir.size() - 1] == '\\') || (dir[dir.size() - 1] == '/')) {
        dir = dir.substr(0, dir.size() - 1);
    }
    size_t found = dir.find_last_of("/\\"); //,dir.find_last_of("/\/")) ; /// §§§§ THIS SHOULD BE TESTED IN LINUX
    return dir.substr(0, found) + string("/");
}

vector<string> getAllResultSubFolders(string dir) {
    vector<string> res;
    //if(dir.size() == 0) dir = folder;
    if (dir.size() == 0) return res;

    vector<string> foldersToRead;
    foldersToRead.push_back(dir);
    int cpt = 0;

    while ((foldersToRead.size() > 0) && (cpt < 1000)) {
        string nextFolder = foldersToRead.back();
        foldersToRead.pop_back();
        res.push_back(nextFolder);
        vector<string> newFolders = listSubDirectories(nextFolder);
        for (int i = 0; i < (int) newFolders.size(); ++i) {
            foldersToRead.push_back(newFolders[i]);
        }
        cpt++;
    }
    if (cpt == 1000)
        cerr << "ERR:  getAllResultSubFolders(" << dir << "), too many subfolder, or infinite loop." << endl;
    return res;
}

#if __cplusplus >= 201703L

vector<string> listFilesInDir(string dir, string containing) {
    std::string path = "/path/to/directory";
    vector<string> x;
    for (const auto &entry : fs::directory_iterator(path))
        x.push_back(entry.path().string());
    return x;
}

#else
#ifdef WINDOWS
vector<string> listFilesInDir(string dir, string containing)
{
    vector<string> res;
    //cerr << "Check Folder :" << dir << endl;
    char originalDirectory[_MAX_PATH];

    // Get the current directory so we can return to it
    _getcwd(originalDirectory, _MAX_PATH);

    //SetCurrentDirectory(dir.c_str())
    chdir(dir.c_str());  // Change to the working directory
    _finddata_t fileinfo;

    // This will grab the first file in the directory
    // "*" can be changed if you only want to look for specific files
    intptr_t handle = _findfirst("*", &fileinfo);

    if(handle == -1)  {
        //perror("Error searching for file");
        //exit(1);
        return res;
    }
    do {
        if(strcmp(fileinfo.name, ".") == 0 || strcmp(fileinfo.name, "..") == 0)
            continue;
        if(fileinfo.attrib & _A_SUBDIR){ // Use bitmask to see if this is a directory
            //cout << "This is a directory : " << fileinfo.name << endl;
            //res.push_back(string(fileinfo.name));
        }
        else {
            string tp = string(fileinfo.name);
            if(((containing.size() > 0) && (tp.find(containing) != std::string::npos)) || (containing.size() == 0)){
                res.push_back(tp);
                //cerr << "GOT IT !" << endl;
            }
            //cout << "This is a file : " << fileinfo.name << endl;
        }
    } while(_findnext(handle, &fileinfo) == 0);
    _findclose(handle); // Close the stream
    chdir(originalDirectory);
    return res;
}
#endif

#ifdef UNIX

// here, keep the whole path
vector<string> listFilesInDir(string namedir, string containing) {
    vector<string> res;
    DIR *dir = opendir(namedir.c_str());
    struct dirent *entry;
    if (!(entry = readdir(dir))) { return res; }
    do {
        if ((!string(entry->d_name).compare(string("."))) ||
            (!string(entry->d_name).compare(".."))) // didnt find strcomp ... don't like it anyways
            continue;
        if (entry->d_type == DT_REG) { // regular file
            string tp = string(entry->d_name);
            if (((containing.size() > 0) && (tp.find(containing) != std::string::npos)) || (containing.size() == 0)) {
                res.push_back(tp);
            }
        } else {//cout << "This is a file : " << fileinfo.name << endl;
        }
    } while ((entry = readdir(dir)) != NULL);
    closedir(dir);
    return res;
}

#endif

#ifdef MAC
// here, keep the whole path
vector<string> listFilesInDir(string namedir, string containing)
{
    vector<string> res;
    cerr << "Sorry, couldn't male ListFilesInDir run on MAC yet (see common.h/cpp)" << endl;
    return res;
}
#endif
#endif //#if __cplusplus >= 201703L


// I don't use qtcreator/qt routines here because it should be able to work in a Qt free computer as well.
// looks for the THdiff.pro folder.
// first solution : look, from the exe folder, ../Sources/ and look for THDiff.pro
// second solution : look inside the exe folder if there is THDiff.pro
// third solution : look ../ and look for THdiff.pro

string locateProjectDirectory(string projectFileToFind) {
    if (projectFileToFind.size() == 0) projectFileToFind = string("AllProjects.pro");
    string exeFolder = currentDir();
#ifdef MAC
    exeFolder = string("../../../../") + exeFolder;
#endif
    if (listFilesInDir(getParentFolder(exeFolder) + string("Sources/"), projectFileToFind).size() > 0)
        return getParentFolder(exeFolder) + string("Sources/");
    if (listFilesInDir(exeFolder, projectFileToFind).size() > 0) return exeFolder;
    if (listFilesInDir(getParentFolder(exeFolder), projectFileToFind).size() > 0) return getParentFolder(exeFolder);
    return string("NotFound!!!");

    /* for info, different ways to access folders:
     *  cout << "0 (noQt) - " << getParentFolder(currentDir()) + string("Sources/") << endl;
    cout << "1 (noQt) - " << getParentFolder(getParentFolder( getParentFolder(  getParentFolder(currentDir()) ))) << endl;
    #ifndef WITHOUT_QT
    QFileInfo fi("temp"); cout << "2 - " << fi.absolutePath().toStdString() << endl;
    QDir dir("."); cout << "3 - " << dir.absolutePath().toStdString() << endl;
    QApplication b(argc, argv);     // Starts the Qt application
    cout << "4 - " <<  QCoreApplication::applicationDirPath().toStdString() << endl;
    cout << "5 - " <<  QCoreApplication::applicationFilePath().toStdString() << endl;
    // for MAC
    cout << "6 - " << getParentFolder(getParentFolder( getParentFolder(  getParentFolder(  QCoreApplication::applicationDirPath().toStdString())))) << endl;
    #ifndef MAC
    cout << "7 - " << locateProjectDirectory(string("*.pro")) + string("Examples/");
    #endif
    #endif
    */
}

vector<string> findAllResultFolders(string dir) {
    vector<string> liste1 = getAllResultSubFolders(dir);
    vector<string> res;
    for (int i = 0; i < (int) liste1.size(); ++i) {
        if (listFilesInDir(liste1[i], string("History.txt")).size() > 0) {
            res.push_back(liste1[i]);
        }
    }
    return res;
}

void printVector(vector<string> l) {
    cout << "[" << l.size() << "] ";
    for (int i = 0; i < (int) l.size(); ++i) {
        cout << l[i] << ((i < (int) l.size()) ? "\n" : "");
    }
}

void testDirectoryFunctions() {
    string exeFolder = currentDir();
    printVector(getAllResultSubFolders(exeFolder));
    cout << getParentFolder(exeFolder) << endl;
    printVector(listFilesInDir(exeFolder));
}


/*void printVector(vector<string> v){
    for(int i = 0; i < (int) v.size(); ++i){
        cout << v[i] << endl;
    }
}*/

string printVector(vector<double> &v) {
    stringstream ss;
    int s = v.size();
    ss << "V(" << s << ") :";
    for (int i = 0; i < s; ++i) {
        ss << "\t" << v[i];
    }
    return ss.str();
}

void compileLatex(string folderRes, string texFile) {
    ofstream action(folderRes + string("doPDF.bat"), ios::out);
    action << string("cd ") + folderRes + string("\npdflatex -interaction=nonstopmode ") + texFile +
              string(" > resLatexCompil.txt\n");
    action.close();
#ifdef WINDOWS
    system((folderRes + string("doPDF.bat\n")).c_str());
#endif
#if defined(UNIX) || defined(MAC)
    system((string("cd ") + folderRes + string("\nchmod +x doPDF.bat\n./doPDF.bat > resLatexCompil.txt \n")).c_str());
#endif
}


string codeTime() {
    time_t now = time(0);
    stringstream code;
    tm *ltm = localtime(&now);
    code << ltm->tm_mday;
    code << "-" << 1 + ltm->tm_mon;
    code << "-" << 1900 + ltm->tm_year;
    code << "at" << 1 + ltm->tm_hour << "-";
    code << 1 + ltm->tm_min << "-";
    code << 1 + ltm->tm_sec;
    return code.str();
}


void mergePDFs(vector<string> &listFiles, string outputFile, string compilingFolder) {
    cout << "=> Merging files into one PDF ...\n";
    ofstream st(outputFile, ios::out);
    st << "\\documentclass{article}% or something else\n";
    st << "\\usepackage{pdfpages}\n";
    st << "\\begin{document}\n";
    for (int kf = 0; kf < (int) listFiles.size(); ++kf) {
        st << "\\includepdf[pages=-]{" << listFiles[kf] << "}\n";
    }
    st << "\\end{document}\n";
    st.close();
    compileLatex(compilingFolder, outputFile);
}


string optName(typeOptimizer toUse) {
    switch (toUse) {
        case GeneticFast: {
            return string("Genetic Algorithm, only a few rounds for tests");
            break;
        }
        case SRESFast: {
            return string("SRES, only a few rounds for tests");
            break;
        }
        case Genetic25k: {
            return string("Genetic Algorithm, 25 000 cost evaluations");
            break;
        }
        case Genetic50k: {
            return string("Genetic Algorithm, 50 000 cost evaluations");
            break;
        }
        case Genetic100k: {
            return string("Genetic Algorithm, 100 000 cost evaluations");
            break;
        }
        case Genetic250k: {
            return string("Genetic Algorithm, 250 000 cost evaluations");
            break;
        }
        case Genetic500k: {
            return string("Genetic Algorithm, 500 000 cost evaluations");
            break;
        }
        case Genetic1M: {
            return string("Genetic Algorithm, 1 000 000 cost evaluations");
            break;
        }
        case SRES25k: {
            return string("SRES, 25 000 cost evaluations");
            break;
        }
        case SRES50k: {
            return string("SRES, 50 000 cost evaluations");
            break;
        }
        case SRES100k: {
            return string("SRES, 100 000 cost evaluations");
            break;
        }
        case SRES250k: {
            return string("SRES, 250 000 cost evaluations");
            break;
        }
        case SRES500k: {
            return string("SRES, 500 000 cost evaluations");
            break;
        }
        case SRES1M: {
            return string("SRES, 1 000 000 cost evaluations");
            break;
        }
        case GeneticAllCombs25k: {
            return string("Genetic Algorithm, All Operators, 25 000 cost evaluations");
            break;
        }
        case GeneticAllCombs50k: {
            return string("Genetic Algorithm, All Operators, 50 000 cost evaluations");
            break;
        }
        case GeneticAllCombs100k: {
            return string("Genetic Algorithm, All Operators, 100 000 cost evaluations");
            break;
        }
        case GeneticAllCombs250k: {
            return string("Genetic Algorithm, All Operators, 250 000 cost evaluations");
            break;
        }
        default: {
            return string("");
        }
    }
    return string("");
}

string optFileHeader(typeOptimizer toUse) {

    stringstream headerOptimizer;
    switch (toUse) {
        case SRESFast: {
            headerOptimizer << "SRES	1   \n50\n";
            break;
        }
        case SRES25k: {
            headerOptimizer << "SRES	1   \n25000\n";
            break;
        }
        case SRES50k: {
            headerOptimizer << "SRES	1   \n50000\n";
            break;
        }
        case SRES100k: {
            headerOptimizer << "SRES	1   \n100000\n";
            break;
        }
        case SRES250k: {
            headerOptimizer << "SRES	1   \n250000\n";
            break;
        }
        case SRES500k: {
            headerOptimizer << "SRES	1   \n500000\n";
            break;
        }
        case SRES1M: {
            headerOptimizer << "SRES	1   \n1000000\n";
            break;
        }

        default: {
        }
    }
    // finished for SRES

    bool TESTE_ALL_CROSSMUT = false;
    switch (toUse) {
        case GeneticAllCombs25k:
        case GeneticAllCombs50k:
        case GeneticAllCombs100k:
        case GeneticAllCombs250k: {
            TESTE_ALL_CROSSMUT = true;
            break;
        }
        default: {
        }
    }


    switch (toUse) {
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
        case GeneticAllCombs250k: {
            headerOptimizer << "geneticAlgorithm	14\n";
            headerOptimizer << (TESTE_ALL_CROSSMUT ? "10         #CEP  - All Mut&Cross\n"
                                                   : "0	#CEP  - Classical Evolutionary Programming\n");
            headerOptimizer << "8          #Proportional / From Worst / Basic Sampling\n";
            headerOptimizer << "7	1      #SBX Cross-Over\n";
            headerOptimizer << "1          #Mutation normal all points\n";
            headerOptimizer << "0          #NO_NEED_REPLACEMENT\n";
            headerOptimizer << "0          #Select Best\n";
            headerOptimizer << "7	0.005	#MUTATIVE_SEPARATED\n";
            headerOptimizer << "1      #Nb Repeats\n";
            break;
        }
        default: {
        }
    }

    switch (toUse) {
        case GeneticFast: {
            headerOptimizer << "50	#Max nb of simulations-costs\n";
            headerOptimizer << "50	#Population Size\n";
            break;
        }
        case Genetic25k:
        case GeneticAllCombs25k: {
            headerOptimizer << "25000	#Max nb of simulations-costs\n";
            headerOptimizer << "250	#Population Size\n";
            break;
        }
        case Genetic50k:
        case GeneticAllCombs50k: {
            headerOptimizer << "50000	#Max nb of simulations-costs\n";
            headerOptimizer << "250	#Population Size\n";
            break;
        }
        case Genetic100k:
        case GeneticAllCombs100k: {
            headerOptimizer << "100000	#Max nb of simulations-costs\n";
            headerOptimizer << "500	#Population Size\n";
            break;
        }
        case Genetic250k:
        case GeneticAllCombs250k: {
            headerOptimizer << "250000	#Max nb of simulations-costs\n";
            headerOptimizer << "750	#Population Size\n";
            break;
        }
        case Genetic500k: {
            headerOptimizer << "500000	#Max nb of simulations-costs\n";
            headerOptimizer << "1000	#Population Size\n";
            break;
        }
        case Genetic1M: {
            headerOptimizer << "1000000	#Max nb of simulations-costs\n";
            headerOptimizer << "2000	#Population Size\n";
            break;
        }
        default: {
        }
    }

    switch (toUse) {
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
        case GeneticAllCombs250k: {
            headerOptimizer << "0.2	#Proportion of CrossOver (vs offspring) in new individuals\n";
            headerOptimizer << "0.5	#Fork coeff (%renewed each generation)\n";
            break;
        }
        default: {
        }
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
