#include "tableCourse.h"
#include <algorithm>
#include <sstream>

void TableCourse::reset() {
    int nL = storage.size();
    for (int i = 0; i < nL; ++i) delete storage[i];
    storage.clear();
    attribut.clear();
    nbLignes = 0;
    headers.clear();
    headers.resize(nbVar + 1);
}

void TableCourse::setHeader(int i, string title) {
    // Header (0) = titre des attributs !!, commence à 1 !!
    if ((i < 0) || (i > nbVar)) {
        std::cerr << "ERR:setHeades, out of bounds " << i << std::endl;
        return;
    }
    headers[i] = title;
}

TableCourse::TableCourse(int _nbVar) : nbVar(_nbVar), nbLignes(0) { reset(); }

TableCourse::TableCourse(string fileToRead) {
    read(fileToRead);
}

TableCourse::~TableCourse() {
    //std::cerr << "DeleteKin" << print() << std::endl;
    int S = storage.size();
    for (int i = 0; i < S; ++i) {
        if (storage[i]) delete storage[i];
    }
    storage.clear();
}

TableCourse::TableCourse(TableCourse *toCopy) {
    nbVar = toCopy->nbVar;
    reset();
    nbLignes = toCopy->nbLignes;
    //if((int) toCopy->attribut.size() !=  nbLignes) {std::cerr << "ERR TableCourse::TableCourse(other TableCourse), attribut[] has wrong size" << std::endl; return;}
    //if((int) toCopy->storage.size() !=  nbLignes) {std::cerr << "ERR TableCourse::TableCourse(other TableCourse), storage[] has wrong size" << std::endl; return;}
    if ((int) toCopy->headers.size() != nbVar + 1) {
        std::cerr << "ERR TableCourse::TableCourse(other TableCourse), headers[] has wrong size" << std::endl;
        return;
    }
    attribut.resize(nbLignes, 0);
    storage.resize(nbLignes, NULL);
    for (int i = 0; i < nbLignes; ++i) {
        storage[i] = new vector<double>(nbVar, 0.0);
        attribut[i] = toCopy->attribut[i];
        if ((int) toCopy->storage[i]->size() != nbVar) {
            std::cerr << "ERR TableCourse::TableCourse(other TableCourse), storage[" << i << "] has wrong size" << std::endl;
            return;
        }
        for (int j = 0; j < nbVar; ++j) {
            (*(storage[i]))[j] = (*(toCopy->storage[i]))[j];
        }
    }
    for (int i = 0; i < nbVar + 1; ++i) {
        headers[i] = toCopy->headers[i];
    }
}

TableCourse::TableCourse(const TableCourse &toCopy) {
    // std::cerr << "ERR: implicit copy !!!" << std::endl;
    // sadly this function is called implicitely when resizing currentData which is a vector of tablecourse...
    nbVar = toCopy.nbVar;
    reset();
    nbLignes = toCopy.nbLignes;
    if ((int) toCopy.headers.size() != nbVar + 1) {
        std::cerr << "ERR TableCourse::TableCourse(other TableCourse), headers[] has wrong size" << std::endl;
        return;
    }
    attribut.resize(nbLignes, 0);
    storage.resize(nbLignes, NULL);
    for (int i = 0; i < nbLignes; ++i) {
        if ((int) toCopy.attribut.size() != nbLignes) {
            std::cerr << "ERR TableCourse::TableCourse(other TableCourse), attribut[] has wrong size" << std::endl;
            return;
        }
        if ((int) toCopy.storage.size() != nbLignes) {
            std::cerr << "ERR TableCourse::TableCourse(other TableCourse), storage[] has wrong size" << std::endl;
            return;
        }

        storage[i] = new vector<double>(nbVar, 0.0);
        attribut[i] = toCopy.attribut[i];
        if ((int) toCopy.storage[i]->size() != nbVar) {
            std::cerr << "ERR TableCourse::TableCourse(other TableCourse), storage[" << i << "] has wrong size" << std::endl;
            return;
        }
        for (int j = 0; j < nbVar; ++j) {
            (*(storage[i]))[j] = (*(toCopy.storage[i]))[j];
        }
    }
    for (int i = 0; i < nbVar + 1; ++i) {
        headers[i] = toCopy.headers[i];
    }
}


double TableCourse::operator()(int vari, typeTime timej) {
    if ((vari < 0) || (vari >= nbVar)) return 0;
    if ((timej < 0) || (timej >= nbLignes)) return 0;
    return (*(storage[timej]))[vari];
}

void TableCourse::addSet(double attr, vector<double> &toCopy) {
    //if(!toCopy) {std::cerr << "ERR: TableCourse, given table doesn't exist (NULL)" << std::endl; return;}
    if ((int) toCopy.size() != nbVar) {
        std::cerr << "ERR: TableCourse, given table has wrong size (" << toCopy.size() << ") instead of NbVar = " << nbVar
             << std::endl;
        return;
    }
    attribut.push_back(attr);
    vector<double> *vres = new vector<double>(nbVar, 0.0);
    for (int i = 0; i < nbVar; ++i) {
        (*vres)[i] = toCopy[i];
    }
    storage.push_back(vres);
    nbLignes++;
}

string TableCourse::print(bool fileExportVersion) {
    std::stringstream res;
    if (fileExportVersion) res << attribut.size() << "\t" << headers.size() - 1 << "\n";
    else
        res << "sizes : header " << headers.size() << " Attr" << attribut.size() << " storage" << storage.size()
            << " & nbLignes = " << nbLignes << std::endl;

    res << headers[0];
    for (int i = 1; i <= nbVar; ++i) {
        //if(fileExportVersion) if(headers[i-1].size() < 8) res << "\t"; // to align the headers whti the following data (when >= 8, the tab is shifted)
        res << "\t" << headers[i];
    }
    res << "\n"; // << std::fixed << std::setprecision(6);
    for (int i = 0; i < nbLignes; ++i) {
        res << attribut[i];
        for (int j = 0; j < nbVar; ++j) {
            res << "\t" << (*(storage[i]))[j];
        }
        res << "\n";
    }
    return res.str();
}

void TableCourse::save(string fileName, string title) {
    std::ofstream fichier(fileName.c_str(), std::ios::out);
    if (fichier) {
        //fichier << "#   Time course for " << title << "\n";
        fichier << storage.size() << "\t" << headers.size() - 1 << "\n";
        fichier << headers[0];
        for (int i = 1; i <= nbVar; ++i) {
            fichier << "\t" << headers[i];
        }
        fichier << "\n";
        for (int i = 0; i < nbLignes; ++i) {
            fichier << attribut[i];
            for (int j = 0; j < nbVar; ++j) {
                double currentValue = (*(storage[i]))[j];
                if (std::isnan(currentValue)) {
                    fichier << "\tNaN";
                } else if (std::isinf(currentValue)) {
                    fichier << "\tinf";
                } else {
                    fichier << "\t" << currentValue;
                }
            }
            fichier << "\n";
        }
        fichier.close();
    }
}

void TableCourse::read(string fileName) {

    nbLignes = 0;
    nbVar = 0;
    reset();
    std::ifstream fichier(fileName.c_str(), std::ios::out);
    if (fichier) {
        fichier >> nbLignes >> nbVar;
        std::cout << "      Reading kinetics from file " << fileName << ", got NbLignes : " << nbLignes << ", nbVar :"
             << nbVar << std::endl;
        int nbLignesToRemember = nbLignes;//because of reset
        reset();    // to put everything to the good size
        string push;
        fichier >> push;
        setHeader(0, push);
        for (int i = 1; i <= nbVar; ++i) {
            fichier >> push;
            setHeader(i, push);
        }
        std::stringstream tempBuffer;
        for (int i = 0; i < nbLignesToRemember; ++i) {
            double attr;
            fichier >> attr;
            vector<double> values;

            // Shit happens with iostream : NaN and inf are not recognized by iostream => read string, and then converts to number via a std::stringstream
            double db;
            string trash;
            for (int j = 0; j < nbVar; ++j) {
                fichier >> trash;
                if ((!trash.compare("NaN")) || (!trash.compare("NAN")) || (!trash.compare("nan")) ||
                    (!trash.compare("+inf")) || (!trash.compare("-inf")) || (!trash.compare("inf"))) {
                    trash.clear();
                    values.push_back(NAN);
                    //std::cout << "NaN" << "\t";
                } else {
                    tempBuffer << trash;
                    tempBuffer >> db;
                    tempBuffer.clear();
                    values.push_back(db);
                    //std::cout << db << "\t";
                }
                /*
                if(fichier >> db){
                    values.push_back(db);
                } else {
                    fichier.ignore(3);
                    string potentialNaN;
                    fichier >> potentialNaN;
                    fichier.unget();
                    //std::cout << "Success " << potentialNaN;
                }
                std::cout << db << "\t"; */
            }
            //std::cout << std::endl;
            addSet(attr, values);
        }
        fichier.close();
    } else std::cerr << "ERR:TableCourse::read(" << fileName << ", file not found - note that the tablecourse was cleared\n";
}


int TableCourse::findPosition(string nameVariable) {
    //std::cout << "look for " << sname;
    int n = nbVar;
    for (int i = 1; i < n + 1; ++i) {
        if (!(headers[i]).compare(nameVariable)) return i - 1;
    }
    return -1;
}


vector<double> TableCourse::getTimeCourse(int var) {
    vector<double> res = vector<double>();
    if ((var < 0) || (var > nbVar)) {
        std::cerr << "ERR::TableCourse, getTimeCourse(" << var << "), out of bounds. nbVars = " << nbVar << std::endl;
        return res;
    }
    //res.resize(nbLignes);
    for (int i = 0; i < nbLignes; ++i) {
        double currentVal = (*(storage[i]))[var];
        if (!(std::isnan(currentVal) || std::isinf(currentVal))) {
            res.push_back((*(storage[i]))[var]);
        }
    }
    return res;
}

vector<double> TableCourse::getTimePoints(int var) {
    if (var < 0) {
        vector<double> res1 = vector<double>(attribut);
        return res1;
    }
    vector<double> res = vector<double>();
    if (var > nbVar) {
        std::cerr << "ERR::TableCourse, getTimePoints(" << var << "), out of bounds. nbVars = " << nbVar << std::endl;
        return res;
    }
    for (int i = 0; i < nbLignes; ++i) {
        double currentVal = (*(storage[i]))[var];
        if (!(std::isnan(currentVal) || std::isinf(currentVal))) {
            res.push_back(attribut[i]);
        } //else std::cout << "!";
    }
    return res;
}

// vector<string> getGlobalNames();
// timePoints should be ordered !!!
TableCourse TableCourse::subKinetics(vector<int> timePoints,
                                     vector<string> namesVariables /* same names than in the tablecourse */) {
    std::cout << "  --> Extracting subKinetics ..." << std::endl;

    int nbTP = timePoints.size();
    int nbWantedVars = namesVariables.size();
    if (nbTP == 0) {
        std::cerr << "ERR: TableCourse::subKinetics, no time point given " << std::endl;
        return TableCourse(0);
    }
    sort(timePoints.begin(), timePoints.end());     // the time points should be sorted !!

    // tables to extract the variables we want to keep in the subKinetics:
    vector<int> placeHeaderInNewKin;    //STARTS AT ZERO for each variable placeHeaderInNewKin[header variable position] -> will go to position x in the subkinetics.-1 if not taken
    placeHeaderInNewKin.resize(headers.size(), -1);
    vector<string> listeNamesNewTable;     // list of headers of the subkinetics   listeIDsNewTable[header position in subkinetics] -> name

    if (nbWantedVars == 0) {
        for (int i = 1; i < (int) headers.size(); ++i) {
            placeHeaderInNewKin[i] = i - 1;    // STARTS AT ZERO, (indice for data vector later)
            listeNamesNewTable.push_back(headers[i]);
        }
    } else {
        std::stringstream errs;
        for (int i = 0; i < nbWantedVars; ++i) {
            string wantedVar = namesVariables[i];
            bool done = false;
            for (int j = 1; j < (int) headers.size(); ++j) {
                if (!headers[j].compare(wantedVar)) {   // if the jth variable
                    //std::cout << " compare " << headers[j] << " and " << wantedVar << std::endl;
                    if (!done) {
                        listeNamesNewTable.push_back(wantedVar);
                        if (placeHeaderInNewKin[j] >= 0)
                            std::cerr << "ERR : TableCourse::subKinetics, you're asking twice the same variable !!\n";
                        placeHeaderInNewKin[j] = listeNamesNewTable.size() - 1;
                    } // i.e. the last position
                    done = true;
                }
            }
            if (!done) errs << "\t" << namesVariables[i];
        }
        if (errs.str().size() > 0)
            std::cerr << "WRN : TableCourse::subKinetics, variables not found (probably not simulated) in kinetics"
                 << errs.str() << std::endl;
    }

    int nbVarReduced = listeNamesNewTable.size();
    TableCourse Tbres(nbVarReduced);
    Tbres.setHeader(0, "time");
    for (int i = 0; i < nbVarReduced; ++i) {
        Tbres.setHeader(i + 1, listeNamesNewTable[i]);
    }

    vector<double> data;
    data.resize(nbVarReduced, 0.0);

    int pointerTimePoint = 0; // already checked NBTP > 0
    for (int i = 0; (i < nbLignes) && (pointerTimePoint < nbTP); ++i) {
        if (attribut[i] == timePoints[pointerTimePoint]) { // if timepoint is required
            pointerTimePoint++;
            for (int j = 0; j < nbVar; ++j) {
                if (placeHeaderInNewKin[j + 1] >= 0)   // le +1 qui tue ...
                    data[placeHeaderInNewKin[j + 1]] = (*(storage[i]))[j];
            }
            if ((int) data.size() != nbVarReduced)
                std::cerr << "ERR : TableCourse::subKinetics, for time point " << attribut[i]
                     << " , some variables where not found. Should not happen !!\n";
            Tbres.addSet(attribut[i], data);
        }
    }
    if (pointerTimePoint < nbTP)
        std::cerr << "WRN :  TableCourse::subKinetics, some time points were not found (first not found is : "
             << timePoints[pointerTimePoint] << ")\n";

    return Tbres;
}


