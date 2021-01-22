#include "simuwin.h"
#include <sstream>
#include <fstream>

#ifndef WITHOUT_QT
#include "ui_simuwin.h"
#ifdef QT5
#include <QMessageBox>
#include <QFileDialog>
#include <QInputDialog>
#endif
#ifdef QT4
#include <QtGui/QMessageBox>
#include <QtGui/QFileDialog>
#include <QtGui/QInputDialog>
#endif
#include <QThread>
#endif

#include <algorithm> // for reverse
#include "../Framework/parameterSets.h"

// Maximum number of columns (combinations) for the interface
#define NBCOLS 101



/// =============================== Part Class without graphical interface ========================

double manageSims::getCost(){
   //std::cerr << ".Cost." << std::endl;                                                        //if(dimension > currentModel->getNbParams()) {std::cerr << "Optimizer has more parameters than model\n"; return -1;}      // commented because would cause delay,
                                              // this function is used during optimization, where the optimizer use manageSims as a 'generalImplementation' and gives parameters to the 'parameter' field and then call 'getCost'. Therefore, this function has to use the values in parameters[] to launch simulation and retrieve the cost.
    #ifdef ALLOW_OPTIMIZE                               // this requires the field 'parameters' inherited from the class generalImplementation --> need ALLOW_OPTIMIZE
        int NPs =  currentModel->getNbParams();
        for(int i = 0; i < NPs; ++i){                       // the parameters to optimize are real values, the other ones are NAN so they are not used to override the model's parameters.
            if(!std::isnan(parameters[i])) currentModel->setParam(i, parameters[i]);}
    #else
    std::cerr << "ERR: manageSims::getCost(), ALLOW_OPTIMIZE should be defined to use this function for optimization. Instead, the current parameter values from the model are taken for this time.\n";
    #endif

    simulate();

    double v1 = NAN, v2 = NAN;
    if(currentMode != MULTI_EXPERIMENT){
        v1 = currentExperiment->costVariableInModel();
        v2 = currentExperiment->getPenalities();
    } else {
        v1 = listExperiments->costVariableInModel();
        v2 = listExperiments->getPenalities();
    }
    vector<double> set = currentModel->getParameters();
    history.addSet(&set, v1+v2);
    costRecords.newValue(v1+v2);
    return v1 + v2;
}

void manageSims::simulate(){
    currentExperiment->init();                      // This looks important, to clear the evaluators ...
    currentModel->setPrintMode(false, 25000);
    if(currentMode != MULTI_EXPERIMENT){             // model initialization is done inside the function experiment->simulationsPart/simulate, no need to do it here
        currentExperiment->simulateAll(true);
    } else {
        listExperiments->simulateAll(true);
    }
}






/// ====================== Configuration <=> Model (independent of the current experiment) ==========================

bool manageSims::isInConfig(int idParameter, int idConfig){
    if((idConfig < 0) || (idConfig >= nbCombs)) {std::cerr << "manageSims::isInConfig(idParameter=" << idParameter << ", idConfig=" << idConfig << "), wrong config index (only " << nbCombs << " combinations defined\n"; return false;};
    if((idParameter < 0) || (idParameter >= currentModel->getNbParams())) {std::cerr << "manageSims::isInConfig(idParameter=" << idParameter << ", idConfig=" << idConfig << "), wrong parameter index (only " << currentModel->getNbParams() << " parameters\n"; return false;};
    return(! currentConfig[idParameter][idConfig+4].compare("1"));
}

void manageSims::saveConfig(string _name){
    if(!_name.compare("")){
       std::cerr << "ERR: manageSims::saveConfig, no file name entered" << std::endl; return;
    }
    int NP = this->currentModel->getNbParams();
    int NV = this->currentModel->getNbVars();
    std::cout << "      ... Writing into file " << _name << std::endl;
    std::ofstream f(_name.c_str(), std::ios::out);
    if(!f) {std::cerr << "ERR: manageSims::saveConfig(" << _name << "), file not found" << std::endl; return;}
    f << NP << "\t";
    f << NV << "\t";
    f << nbCombs << "\n";
    if((int) currentConfig.size() != NP + NV) {std::cerr << "ERR: currentConfig size problem " << currentConfig.size() << " NP " << NP << " NV " << NV << std::endl; return;}
    if(currentConfig.size() == 0) {std::cerr << "ERR: no config " << std::endl; return;}
    if((int) currentConfig[0].size() != nbCombs + 4) {std::cerr << "ERR: currentConfig size problem " << currentConfig[0].size() << " NC " << nbCombs << std::endl; return;}
    for(int i = 0; i < NP + NV; ++i){
        for(int j = 0; j < nbCombs + 4; ++j){
            f << currentConfig[i][j] << ((j < nbCombs + 3) ? "\t" : "");
        }
        f << "\n";
    }
    f.close();
}

vector<int> manageSims::parametersInConfig(int idConfig){
    vector<int> result;
    for(int i = 0; i < currentModel->getNbParams(); ++i){
        if(isInConfig(i, idConfig)){
            result.push_back(i);
        }
    }
    return result;
}

string manageSims::loadConfig(string _name){
    if(recording) currentMacro << "macro" << macroID << ".loadConfig(" << _name << ")\n";
    if(recording) addFileToMacro(_name);

    std::cout << "   -> Reading configuration file " << _name;
    std::ifstream f(_name.c_str(), std::ios::in);
    if(!f) {return string("ERR: loadConfig, file couldn't be opened '") + _name + string("'\n");}
    std::stringstream listErrors;
    string moreInfo = string("   Expected file format :\n      NbParameters NbVariables NbCombinaisons, \n      followed by a table of NbParameters + NbVariables rows \n      and Nbcomnbinaisons + 4 columns : \n      Param_value ParamMin ParamMax Opt? Comb1 Comb2 ... (one line for each parameter)\n      .<tab>.<tab>.<tab> Simulate?  Comb1 Comb2 ... (one line for each variable) ");

    int NP = 0, NV = 0, NC = 0;
    f >> NP;
    f >> NV;
    f >> NC;
    if(NP != currentModel->getNbParams()) listErrors << "   -> Incorrect number of parameters  : current model has " << currentModel->getNbParams() << " while file says " << NP << "\n";
    if(NV != currentModel->getNbVars()) listErrors <<   "   -> Incorrect number of variables   : current model has " << currentModel->getNbVars() << " while file says " << NV << "\n";
    if((NC < 0) || (NC > NBCOLS - 4)) listErrors <<     "   -> Incorrect number of combinaisons: maximum number is " << NBCOLS - 4 << " while file has " << NC << "\n";
    if(listErrors.str().size() > 0) {
        return string("\n   ERR: Incorrect formating\n") + listErrors.str() + moreInfo;
    }
    std::cout << "\n      ... got : (" << NP << " params, " << NV << "vars, " << NC << " combs)" << std::endl;

    currentConfig.clear();
    currentConfig.resize(NP + NV);
    for(int i = 0; i < NP + NV; ++i){
        currentConfig[i].resize(NC+4);
        for(int j = 0; j < NC + 4; ++j){
            f >> currentConfig[i][j];
            if(i < NP){
                if(j == 0) currentModel->setParam(i, (double) atof((currentConfig[i][j]).c_str()));
                if(j == 2) currentModel->setBounds(i, (double) atof((currentConfig[i][1]).c_str()), (double) atof((currentConfig[i][2]).c_str()) );
            }
            //std::cout << (double) atof(currentConfig[i][j].c_str()) << "\t";
        }
        //std::cout << std::endl;
    }
    f.close();
    nbCombs = NC;
    return string("");
}

/// Phi : I have the impression this function could be merged with the previous one
string manageSims::resetParamSetFromConfig(string _name){
    if(recording) currentMacro << "macro" << macroID << ".resetParamSetFromConfig(" << _name << ")\n";

    vector<double> newParameterSet;
    std::ifstream f(_name.c_str(), std::ios::in);
    if(!f) {return string("ERR: loadConfig, incorrect file name\n");}
    std::stringstream listErrors;
    string moreInfo = string("Expected file format :\n   NbParameters NbVariables NbCombinaisons, \n   followed by a table of NbParameters + NbVariables rows \n   and Nbcomnbinaisons + 4 columns : \n   Param_value ParamMin ParamMax Opt? Comb1 Comb2 ...");

    int NP = 0, NV = 0, NC = 0;
    f >> NP;
    f >> NV;
    f >> NC;
    if(NP != currentModel->getNbParams()) listErrors << "-> Incorrect number of parameters  : current model has " << currentModel->getNbParams() << " while file says " << NP << "\n";
    if(NV != currentModel->getNbVars()) listErrors <<   "-> Incorrect number of variables   : current model has " << currentModel->getNbVars() << " while file says " << NV << "\n";
    if((NC < 0) || (NC > NBCOLS - 4)) listErrors <<     "-> Incorrect number of combinaisons: maximum number is " << NBCOLS - 4 << " while file has " << NC << "\n";
    if(listErrors.str().size() > 0) {return string("Incorrect formating\n") + listErrors.str() + moreInfo;}

    currentConfig.clear();
    currentConfig.resize(NP + NV);
    for(int i = 0; i < NP + NV; ++i){
        currentConfig[i].resize(NC+4);
        for(int j = 0; j < NC + 4; ++j){
            f >> currentConfig[i][j];
            if(i < NP){
                //(see comment below) if(j == 0) currentModel->setParam(i, (double) atof((currentConfig[i][j]).c_str()));
                if(j == 0) newParameterSet.push_back((double) atof((currentConfig[i][j]).c_str()));
            }
        }
    }

    f.close();
    currentModel->setParameters(newParameterSet);   // note : this function will also check that the newparameterset has the good size.
                                                    // it is important to use setParameters(full set) rather than giving parameters one by one,
                                                    // because the model doesn't allow to be simulated without an initial full set of parameters,
                                                    // and the boolean checkpoint 'parametersLoaded' inside the Model is only checked when a full parameter set is given.
    return string();
}

void manageSims::resetConfigFromModel(){
    if(recording) currentMacro << "macro" << macroID << ".resetConfigFromModel()\n";

    int NP = currentModel->getNbParams();
    int NV = currentModel->getNbVars();
    int NC = 0;

    currentConfig.clear();
    currentConfig.resize(NP + NV);

    for(int i = 0; i < NP + NV; ++i){
        currentConfig[i].resize(NC+4);
        for(int j = 0; j < NC + 4; ++j){
            if(i < NP){
                std::stringstream ss;
                if(j == 0) ss << currentModel->getParam(i);
                if(j == 1) ss << currentModel->getLowerBound(i);
                if(j == 2) ss << currentModel->getUpperBound(i);
                currentConfig[i][j] = ss.str();
            }
        }
    }
    nbCombs = NC;
}

// this function only takes the parameter values and boundaries
void manageSims::updateConfigParamsFromModel(){
    if(recording) currentMacro << "macro" << macroID << ".updateConfigParamsFromModel()\n";

    int NP = currentModel->getNbParams();
    int NV = currentModel->getNbVars();

    if(currentConfig.size() == 0) resetConfigFromModel();       // in case no config loaded yet.
    if((int) currentConfig.size() != NP + NV) {std::cerr << "ERR: manageSims::updateConfigParamsFromModel(), incompatible sizes between model (NParams = " << NP << ", NVars = " << NV << " and configuration of size NP+NV = " << currentConfig.size() << std::endl; return;}

    for(int i = 0; i < NP + NV; ++i){
        for(int j = 0; j <= 2; ++j){    // just for parameter value and bounds
            if(i < NP){
                std::stringstream ss;
                if(j == 0) ss << currentModel->getParam(i);
                if(j == 1) ss << currentModel->getLowerBound(i);
                if(j == 2) ss << currentModel->getUpperBound(i);
                currentConfig[i][j] = ss.str();
            }
        }
    }
}



//============== History management =================




vector<double> manageSims::bestSetFromHistory(){
    return history.bestSet();
}

void manageSims::saveBestSetFromHistory(string _name){
    history.saveBestSet(_name);
}

void manageSims::saveHistory(string _name){
    if(recording) currentMacro << "macro" << macroID << "." << "saveHistory(" << _name << ")" << "\n";

    int NP = currentModel->getNbParams();
    int storeMax = 1e9;
    std::cout << "      ... Writing into file " << _name << std::endl;
    std::ofstream f(_name.c_str(), std::ios::out);
    if(!f) {std::cerr << "File not Found" << _name << std::endl; return;}
    vector<oneSet*> liste = history.toVector();
    //reverse(liste.begin(), liste.end());
    int ls = liste.size();

    f << NP << "\t";
    f << ls << "\n";

    for(int i = 0; (i < ls) && (i < storeMax); ++i){
        f << liste[i]->cost;
        int s = liste[i]->v.size();
        if(s != NP) std::cerr << "ERR : save History incorrect size for parameters\n";
        for(int j = 0; j < NP; ++j){
            f << "\t" << liste[i]->v[j];
        }
        f << "\n";
    }
    f.close();
    addFileToMacro( _name);
}

pSets readHistory(string _name){
    int storeMax = 1e9;
    std::cout << "      ... Reading history file " << _name << std::endl;
    std::ifstream f(_name.c_str(), std::ios::in);
    if(!f) {std::cerr << "ERR: pSets readHistory(" << _name << "), File not Found" << std::endl;}

    int NP = 0; // = currentModel->getNbParams();
    int ls = 0; // = liste.size();
    f >> NP;
    f >> ls;
    pSets history = pSets(10000, NP);
    history.clear();
    if((ls > storeMax) || (ls < 0)) {std::cerr << "manageSims::loadHistory(...) Incorrect number of lines (" << ls << ")\n"; return history;}

    for(int i = 0; (i < ls) && (i < storeMax); ++i){
        vector<double>* tempStore = new vector<double>(NP, 0.0);
        double tempCost = 0;
        f >> tempCost;
        for(int j = 0; j < NP; ++j){
            f >> (*tempStore)[j];
        }
        history.addSet(tempStore, tempCost);
        delete tempStore;
    }
    f.close();
    return history;
}


void manageSims::loadHistory(string _name){
    if(recording) currentMacro << "macro" << macroID << "." << "loadHistory(" << _name << ")" << "\n";
    int storeMax = 1e9;
    std::cout << "      ... Reading file " << _name << std::endl;
    std::ifstream f(_name.c_str(), std::ios::in);
    if(!f) {std::cerr << "File not Found" << std::endl; return;}

    history.clear();
    //vector<oneSet*> liste = history.toVector();
    //reverse(liste.begin(), liste.end());
    int NP = 0; // = currentModel->getNbParams();
    int ls = 0; // = liste.size();

    f >> NP;
    f >> ls;
    std::cout << "      ... Expecting " << NP << " parameters and " << ls << " lines"<< std::endl;
    if(NP != currentModel->getNbParams()) {std::cerr << "manageSims::loadHistory(...) Incorrect file format : " << NP << " parameters provided while " << currentModel->getNbParams() << " in the model\n"; return;}
    if((ls > storeMax) || (ls < 0)) {std::cerr << "manageSims::loadHistory(...) Incorrect number of lines (" << ls << ")\n"; return;}

    for(int i = 0; (i < ls) && (i < storeMax); ++i){
        vector<double>* tempStore = new vector<double>(NP, 0.0);
        double tempCost = 0;
        f >> tempCost;
        //std::cerr << tempCost << " - ";
        for(int j = 0; j < NP; ++j){
            f >> (*tempStore)[j];
            //std::cerr << j << "=" << (*tempStore)[j] << "\t";
        }
        //std::cerr << std::endl;
        history.addSet(tempStore, tempCost);
        delete tempStore;
    }
    f.close();
    addFileToMacro( _name);
}






/// returns the new list of parameters by "replacing" the parameters from indexSet,
/// **** according to the configuration ****,
vector<double> manageSims::useParamSetFromHistory(int indexSet, int indexCombToOverride){

    vector<oneSet*> v = history.toVector();
    //reverse(v.begin(), v.end());
    int s = v.size();
    if((indexSet < 0) || (indexSet >= s)) {std::cerr << "ERR: manageSims::useParamSetFromHistory(" << indexSet << "), wrong index (only " << s << " sets in the history) \n"; return vector<double>();}
    oneSet* theSet = v[indexSet];
    int NP = theSet->v.size();
    vector<double> result = vector<double>(NP, NAN);
    if(NP != (int) currentModel->getNbParams()) {std::cerr << "ERR: manageSims::useParamSetFromHistory(...), not the same parameter numbers in the history (" << NP << " than in the model " << currentModel->getNbParams() << std::endl; return result;}
    if(indexCombToOverride < 0){
        currentModel->setParameters(theSet->v); // to unlock simulations if no valid parameters set before
        /*for(int j = 0; j < NP; ++j){
           currentModel->setParam(j, theSet->v[j]);
        }*/
    } else if(indexCombToOverride < nbCombs){
        for(int j = 0; j < NP; ++j){    // note : in this case, a full valid set of parameters should have been given before
            if(!currentConfig[j][indexCombToOverride+4].compare(string("1"))){
                currentModel->setParam(j, theSet->v[j]);
                result[j] =  theSet->v[j];
            } else result[j] = currentModel->getParam(j);//to avoid NANs
        }
    } else std::cerr << "ERR: manageSims::useParamSetFromHistory(set nr:" << indexSet << ", comb nr:" << indexCombToOverride << "), invalid combination index, only " << nbCombs << " defined combinations\n";
    return result;
}









#ifndef WITHOUT_QT

void simuWin::buttonPerturbatePushed(){
    if(currentMode == modePerturbate){
        ui->pushButtonPerturb->setText(QString("Modulate"));
        ui->pushButtonPerturb->setStyleSheet("background-color: rgb(190, 190, 190)");
        switchBackNormalMode();
        return;
    }
    if(currentMode == MONO_EXPERIMENT){

        int NP = currentModel->getNbParams();
        QStringList items;
        for(int i = 0; i < NP; ++i){
            items << QString::number(i) + QString("-") + QString(currentModel->getParamName(i).c_str());
        }
        bool okPressed = false;
        QString chosenTextParameter = QInputDialog::getItem(this, QString("Choose Parameter"),QString("One parameter perturbation "), items,0, false, &okPressed);
        int chosenParameter = -1;
        for(int i = 0; i < NP; ++i){
            if(!(QString::number(i) + QString("-") + QString(currentModel->getParamName(i).c_str())).compare(chosenTextParameter)) chosenParameter = i;
        }
        if(chosenParameter < 0) {std::cerr << "ERR: button perturbate pushed, couldn't find which parameter was chosen - should not happen" << std::endl; return;}
        if(!okPressed) return;


        NP = currentExperiment->getNbCond();
        int chosenCondition = 0;
        if(NP < 1) {std::cerr << "ERR: buttonPerturbatePushed, Empty experiment!" << std::endl; return;}
        if(NP > 1){
            QStringList items;
            for(int i = 0; i < NP; ++i){
                items << QString::number(i) + QString("-") + QString(currentExperiment->getConditionName(i).c_str());
            }
            QString chosenTextCondition = QInputDialog::getItem(this, QString("Choose Condition"),QString("One parameter perturbation "), items,0, false, &okPressed);
            for(int i = 0; i < NP; ++i){
                if(!(QString::number(i) + QString("-") + QString(currentExperiment->getConditionName(i).c_str())).compare(chosenTextCondition)) chosenCondition = i;
            }
            if(chosenCondition < 0) {std::cerr << "ERR: button perturbate pushed, couldn't find which parameter was chosen - should not happen" << std::endl; return;}
            if(!okPressed) return;
        }


        switchToPerturbatedExperiment(chosenCondition, chosenParameter, expChangeOneParameter::NbVariantes);

        // if success
        if(currentMode == modePerturbate){
            ui->pushButtonPerturb->setText(QString("Back"));
            ui->pushButtonPerturb->setStyleSheet("background-color: rgb(255, 190, 190)");
        }
    }

}

void simuWin::buttonParamSetsPushed(){
    if(currentMode == modeComparison){
        ui->pushButtonCompare->setText(QString("Compare Sets"));
        ui->pushButtonCompare->setStyleSheet("background-color: rgb(190, 190, 190)");
        switchBackNormalMode();
        return;
    }

    if(currentMode == MONO_EXPERIMENT){

        bool okPressed;
        int NP = currentExperiment->getNbCond();
        int chosenCondition = 0;
        if(NP < 1) {std::cerr << "ERR: buttonPerturbatePushed, Empty experiment!" << std::endl; return;}
        if(NP > 1){
            QStringList items;
            for(int i = 0; i < NP; ++i){
                items << QString::number(i) + QString("-") + QString(currentExperiment->getConditionName(i).c_str());
            }
            QString chosenTextCondition = QInputDialog::getItem(this, QString("Choose Condition"),QString("One parameter perturbation "), items,0, false, &okPressed);
            for(int i = 0; i < NP; ++i){
                if(!(QString::number(i) + QString("-") + QString(currentExperiment->getConditionName(i).c_str())).compare(chosenTextCondition)) chosenCondition = i;
            }
            if(chosenCondition < 0) {std::cerr << "ERR: button perturbate pushed, couldn't find which parameter was chosen - should not happen" << std::endl; return;}
            if(!okPressed) return;
        }

        int nbSets = QInputDialog::getInt(this, QString("How many sets to compare from History?"), QString("Number Sets?"), 5, 1, 1000, 1, &okPressed);
        if(!okPressed) return;

        switchToComparingExperiment(chosenCondition, nbSets);

        // if worked, then
        if(currentMode == modeComparison){
            ui->pushButtonCompare->setText(QString("Back"));
            ui->pushButtonCompare->setStyleSheet("background-color: rgb(255, 190, 255)");
        }

    }
}

#endif

void manageSims::switchToPerturbatedExperiment(int IDcondition, int IDparameter, int nbCurves){
    if(currentMode != MONO_EXPERIMENT) return;

    savedExperiment = currentExperiment;

    vector<double> paramSet = currentModel->getParameters();
    currentExperiment = new expChangeOneParameter(savedExperiment, paramSet, IDparameter, IDcondition, nbCurves);

    currentData.clear();
    currentData.resize(currentExperiment->getNbCond(), NULL);
    // stores the current data
//    int ND = currentData.size();
//    savedCurrentData.clear();
//    savedCurrentData.resize(ND, NULL);
//    for(int i = 0; i < ND ; ++i){
//        savedCurrentData[i] = currentData[i];
//    }
//    currentData.clear();
//    currentData.resize(currentExperiment->getNbCond(), NULL);
//    if(savedCurrentData.at(IDcondition)){
//        currentData[0] = savedCurrentData.at(IDcondition); // only keeping the data from this condition
//    }


    int sizeExpDataToCopy = savedExperiment->ExpData[IDcondition].size();
    currentExperiment->ExpData[0].resize(sizeExpDataToCopy);
    for(int i = 0; i < sizeExpDataToCopy; ++i){
        currentExperiment->ExpData[0][i] = savedExperiment->ExpData[IDcondition][i];
    }
    int sizeExpDataStdToCopy = savedExperiment->ExpStdDevs[IDcondition].size();
    currentExperiment->ExpStdDevs[0].resize(sizeExpDataStdToCopy);
    for(int i = 0; i < sizeExpDataStdToCopy; ++i){
        currentExperiment->ExpStdDevs[0][i] = savedExperiment->ExpStdDevs[IDcondition][i];
    }

    currentMode = modePerturbate;
    simulate();
}

void manageSims::switchToComparingExperiment(int IDcondition, int nbSetsToComp){
    if(currentMode != MONO_EXPERIMENT) return;

    savedExperiment = currentExperiment;
    vector< vector<double> *> parameterSets;

    vector<oneSet*> v = history.toVector();
    //reverse(v.begin(), v.end());    // such that first is best
    int s = v.size();
    if(s == 0) {std::cerr << "ERR: No parameter set in History - please load or optimize or save sets in history" << std::endl; return;}
    nbSetsToComp = std::min(nbSetsToComp, s);

    for(int i = 0; i < nbSetsToComp; ++i){
        oneSet* theSet = v[i];
        vector<double>* copySet = new vector<double>(theSet->v.size(), 0);
        for(int j = 0; j < (int) theSet->v.size(); ++j){
            (*copySet)[j] = theSet->v[j];
        }
        parameterSets.push_back(copySet);
    }
    currentExperiment = new expCompParameterSets(savedExperiment, parameterSets, IDcondition);

    int sizeExpDataToCopy = savedExperiment->ExpData[IDcondition].size();
    currentExperiment->ExpData[0].resize(sizeExpDataToCopy);
    for(int i = 0; i < sizeExpDataToCopy; ++i){
        currentExperiment->ExpData[0][i] = savedExperiment->ExpData[IDcondition][i];
    }
    int sizeExpDataStdToCopy = savedExperiment->ExpStdDevs[IDcondition].size();
    currentExperiment->ExpStdDevs[0].resize(sizeExpDataStdToCopy);
    for(int i = 0; i < sizeExpDataStdToCopy; ++i){
        currentExperiment->ExpStdDevs[0][i] = savedExperiment->ExpStdDevs[IDcondition][i];
    }

    currentData.clear();
    currentData.resize(currentExperiment->getNbCond(), NULL);

//    int ND = currentData.size();
//    savedCurrentData.clear();
//    savedCurrentData.resize(ND, NULL);
//    for(int i = 0; i < ND ; ++i){
//        savedCurrentData[i] = currentData[i];
//    }
//    currentData.clear();
//    currentData.resize(currentExperiment->getNbCond(), NULL);
//    if(savedCurrentData.at(IDcondition)){
//        currentData[0] = savedCurrentData.at(IDcondition); // only keeping the data from this condition
//    }
    currentMode = modeComparison;
    simulate();

}

void manageSims::switchBackNormalMode(){
    if((currentMode == modePerturbate) || (currentMode == modeComparison)) {
        // would need to delete the currentExperiment. Not sure the desctructor is ok now, need to work on it
        if(!savedExperiment){std::cerr << "ERR: simuwin, switchBackNormalMode, saved experiment is NULL" << std::endl; return;}
        currentExperiment = savedExperiment;
        currentMode = MONO_EXPERIMENT;

        currentData.clear();
        currentData.resize(currentExperiment->getNbCond(), NULL);


//        int ND = savedCurrentData.size();
//        currentData.clear();
//        currentData.resize(ND, NULL);
//        for(int i = 0; i < ND ; ++i){
//            currentData[i] = savedCurrentData[i];
//        }
        simulate();
    }
}




/// Optimizes according to the current settings of the model:
/// overriding variables and defining parameter boundaries should have been done before calling this function.
void manageSims::motherOptimize(string optFileName, int nbSetsToRecord){
    if(recording) currentMacro << "macro" << macroID << "." << "motherOptimize(" << optFileName << "," << nbSetsToRecord << ")" << "\n";
    addFileToMacro(optFileName);

    #ifdef ALLOW_OPTIMIZE
    nbCostCalls = 0;
    history.resize(0);//nbSetsToRecord);
    history.MaxNb = nbSetsToRecord;
    history.clear();
    costRecords.clear();

    GeneralImplementation::initialize();                                    // is doing parameters.resize(currentModel->getNbParams(), NAN);
    myRandom::Randomize();
    myTimes::getDiffTime();
    BaseOptimizationProblem *E = this;                                      //instead of saying new simuWin(currentExperiment, this);
    BaseOptimizer *Opt = BaseOptimizer::createOptimizer(E, optFileName);
    //mySignal::addOptimizer(Opt);
    Opt->optimize();
    Opt->bestGlobal.print();
    currentModel->needNewParameterSet();
    //delete E; // program destructor first...
    delete Opt;
    std::cout << "      ... Optimization Complete, elapsed time : " << myTimes::getDiffTime() << " sec\n";
    #else
    std::cerr << "manageSims::motherOptimize(...), this function is only allowed when ALLOW_OPTIMIZE is defined, in order to include the optimizations files during compilation.\n";
    #endif
}

string manageSims::motherCreateOptimizerFile(int indexComb, string optMethodText, int parameterToExclude){
    if(parameterToExclude >= currentModel->getNbParams()) {std::cerr << "ERR: motherCreateOptimizerFile, incorrect parameter index (to exclude) " << parameterToExclude << std::endl; return string("");}
    if(parameterToExclude >= 0) std::cout << "      ... Excluding parameter from optimization : " << parameterToExclude << " (" << currentModel->getParamName(parameterToExclude) << ")\n";
    if(recording) {
        currentMacro << "string optMethod = string(\"" << optMethodText << "\"\n";
        currentMacro << "macro" << macroID << "." << "motherCreateOptimizerFile(" << indexComb << ", optMethod, " << parameterToExclude << ")" << "\n";    }
    if((indexComb < -1) || (indexComb >= nbCombs)) {std::cerr << "ERR:manageSims::createOptimizer, index comb is out of bounds. Note that indexComb=-1 means pooling parameters and variables from all combinations\n"; return string("");}
    int combStart = (indexComb < 0 ? 0 : indexComb);            // indexComb = -1 means pool all the parameters to optimize from each configuration
    int combEnd   = (indexComb < 0 ? nbCombs-1 : indexComb);

    int NP = currentModel->getNbParams();
    vector<bool> paramsToOptimize = vector<bool>(NP, false);

    std::stringstream f;
    f << optMethodText;
    f << "\n";
    int nbToOpt = 0;
    for(int i = 0; i < NP; ++i)
        for(int j = combStart; j <= combEnd; ++j){
            if((!currentConfig[i][4+j].compare("1")) && (i != parameterToExclude) && (!paramsToOptimize[i])) {nbToOpt++; paramsToOptimize[i] = true;}  }//std::cout << currentConfig[i][4+i] << ".";
    if(nbToOpt == 0){std::cerr << "ERR: manageSims::motherCreateOptimizerFile(index=" << indexComb << ",txt) - No parameter selected for optimization -> 0 parameter to optimize !!\n"; return f.str();}
    f << nbToOpt << "\n";
    for(int i = 0; i < NP; ++i){
        if((!paramsToOptimize[i]) || (i == parameterToExclude)) f << "#";   // comments the parameters that will not be optimized
        //f << "\t" << i << "\t" << currentModel->getLowerBound(i) << "\t" << currentModel->getUpperBound(i) << "\t#" << currentModel->getParamName(i) << std::endl;
        f << "\t" << i << "\t" << currentConfig[i][1] << "\t" << currentConfig[i][2] << "\t#" << currentModel->getParamName(i) << std::endl;
    }
    f << "\n\n0\nExponential\n0\n";
    return f.str();
}








// *** depends on the experiments ***

// Overrides a model according to the current combination
// this depends on the experiments (who are owning the overriders : a curve for each sub-experiment)
// for each variable which is requested to be overrided (by the configuration),
//    -> in MONO_EXPERIMENT mode, then it is overrided only if it is possible (if there is a data-curve for each sub-experiment)
//    -> in MULTI_EXPERIMENT mode, for each experiment, it is overrided according to the mono-exp separately.
void manageSims::motherOverrideUsingComb(int newIndex){
    std::cerr << "OVER using comb " << newIndex << std::endl;
    if((newIndex < -1) || (newIndex >= nbCombs)) {std::cerr << "Wrong comb index " << newIndex << "\n"; return;}
    if(recording) {currentMacro << "macro" << macroID << "." << "motherUseComb(" << newIndex << ")" << "\n";}
    int NP = currentModel->getNbParams();
    int NV = currentModel->getNbVars();
    if((int) currentConfig.size() != NP + NV) {std::cerr << "manageSims::motherOverrideUsingComb, Wrong size of saved configuration\n";return;}
    int combStart = (newIndex < 0 ? 0 : newIndex);
    int combEnd   = (newIndex < 0 ? nbCombs-1 : newIndex);

    for(int i = 0; i < NV; ++i){
        bool override = true;
        for(int j = combStart; j <= combEnd; ++j){              // override only if all selected combinations override (i.e. override the minimum, simulate the maximum)
            override = override && (!currentConfig[i+NP][4+j].compare("1"));
        }
        if(currentMode != MULTI_EXPERIMENT){
            override = override && (currentExperiment->canOverride(currentModel->getExternalName(i)));      // ... and if the variable has data to be overrided
            currentExperiment->overrideVariable(currentModel->getExternalName(i), override);

        } else {
            for(int pp = 0; pp < listExperiments->nbBigExp(); ++pp){
                bool localOverride  = override && (listExperiments->getExperiment(pp)->canOverride(currentModel->getExternalName(i)));      // ... and if the variable has data to be overrided
                /////§§§ toCHeck :: if(localOverride) std::cerr << "SUCCESS§§§" << std::endl; else std::cerr << "wHY§§§" << std::endl;
                listExperiments->getExperiment(pp)->overrideVariable(currentModel->getExternalName(i), localOverride);
            }
        }
        if(override)    std::cout << "         is overrided by data :   ";
        else            std::cout << "         is simulated :           ";
        std::cout << "Variable " << i << "\tglobalId = " << currentModel->getExternalName(i) << "\t(" << currentModel->getName(i) << ")";
        if(!override) std::cout << "*";
        std::cout << std::endl;
    }
}


// Independent : cuts a segment into n points (log or not)
vector<double> cutSpace(int nbPoints, bool logarithmic, double base, double vstart, double vending){
    if((nbPoints < 0) || (nbPoints > 1e9)) { std::cerr << "ERR: cutSpace, out of bounds number of points " << nbPoints << "\n"; return vector<double>();}
    vector<double> valuesToTest = vector<double>(nbPoints, 0.0);

    if(base < 0) base = 2.0;
    if(logarithmic){
        double lstart = log(vstart)/ log(base);
        double lending = log(vending) / log(base);
        double interval = (lending - lstart) / (nbPoints - 1);
        for(int i = 0; i < nbPoints; ++i){
            valuesToTest[i] = pow(base, lstart + interval * i);
            //std::cout << valuesToTest[i] << std::endl;
        }
    } else {
        double interval = (vending - vstart) / (nbPoints - 1);
        for(int i = 0; i < nbPoints; ++i){
            valuesToTest[i] = vstart + interval * i;
            //std::cout << valuesToTest[i] << std::endl;
        }
    }
    return valuesToTest;
}






#ifndef WITHOUT_QT
void simuWin::sensitivity(){
    vector<double> currentParamSet = currentModel->getParameters();
    motherSensitivity(currentParamSet, -1);

    QString newFolder = QFileDialog::getExistingDirectory(this, QString("Do you want to save the sensitivity result in a different folder than before? Stay emptz to continue in current working folder."));
    if(newFolder.size() > 0){
        ui->lineEditWorkingFolder->setText(newFolder);
    }
    makeFigReportParamSet(ui->lineEditWorkingFolder->text().toStdString() + string("/"));
}
#endif

// *** Analysis of a single experiment ***
void manageSims::motherSensitivity(vector<double>& initialSet, int parameterIndex, int nbPoints){

    std::cout << "Starting sensitivity analysis for parameter set \n" << printVector(initialSet) << std::endl;
    parameters = initialSet;
    std::cout << "Cost: " << getCost() << ", Parameter chosen (-1 for all) : " << parameterIndex << std::endl;

    if(currentMode == MULTI_EXPERIMENT){std::cerr << "ERR: manageSims::motherSensitivity is not allowed in the MULTI_EXPERIMENTS mode yet\n"; return;}
    int NP = currentModel->getNbParams();
    if(parameterIndex >= NP) return;
    if((int) sensitivities.size() != NP) {std::cerr << "Internal ERR:  manageSims::motherSensitivity, sensitivities has wrong size (" << sensitivities.size() << ")compared to nb of parameters (" << NP << ")\n";}
    //vector<double> initialParamSet = currentModel->getParameters();
    for(int i = 0; i < NP; ++i){
        if((parameterIndex == i) || (parameterIndex < 0)){
            //std::cerr << i << std::endl;
            if(sensitivities[i]) delete sensitivities[i];
            sensitivities[i] = new oneParameterAnalysis(initialSet);
            //std::cerr << "." << std::endl;


            // manually adds the initial parameter set. Note : it should not be sorted later.
            currentModel->setParameters(initialSet);


            std::cout << "PSet=\t" << printVector(initialSet) << std::endl;
            parameters = initialSet;

            // Simulates HERE
            double v = getCost();

            std::cout << "\t cost=" << v << std::endl;
            vector<double> costPerVariable = vector<double>(currentModel->getNbVars(), 0);
            for(int j = 0; j < currentModel->getNbVars(); ++j){
                costPerVariable[j] = currentExperiment->costVariableInModel(j);
            }
            vector<double> costPerExperiment = vector<double>(currentExperiment->getNbCond(), 0);
            for(int j = 0; j < currentExperiment->getNbCond(); ++j){
                costPerExperiment[j] = currentExperiment->costExp(j);
            }
            sensitivities[i]->add(i, initialSet[i], v, costPerVariable, costPerExperiment, currentModel->getParameters());

            double lowCorrect = currentModel->getLowerBound(i);
            if(currentModel->getLowerBound(i) < 1e-12) lowCorrect = initialSet[i] / 1000;
            motherRecursiveSensitivity(initialSet, i, (nbPoints == -1) ? 20 : nbPoints, true, 2, lowCorrect, currentModel->getUpperBound(i), 5);
            //std::cout << sensitivities[i]->print();
        }
    }

    // goes back to original simulation
    currentModel->setParameters(initialSet);
    parameters = initialSet;
    //double v = getCost(); // careful, for whatever reason, this will call the mother function simuwin if was called from simuwin
}

void manageSims::motherRecursiveSensitivity(vector<double>& initialSet, int parameterIndex, int nbPoints, bool logarithmic, double base, double vstart, double vending, int deepLevel){
    if(recording) currentMacro << "macro" << macroID << "." << ".motherRecursiveSensitivity(" << parameterIndex << "," << nbPoints << "," << (logarithmic ? "true": "false")  << "," << base << "," << vstart << "," << vending << "," << deepLevel << ")" << "\n";
    if(deepLevel == 0) return;
    if(deepLevel < 0) deepLevel = 0;
    if(deepLevel > 1000) { std::cerr << "ERR: manageSims::motherSensitivity, out of bounds number of levels " << deepLevel << std::endl; return;}
    if((parameterIndex < 0) || (parameterIndex > currentModel->getNbParams())){std::cerr << "ERR: manageSims::motherSensitivity, wrong parameter index "<< parameterIndex << ", only " << currentModel->getNbParams() << " parameters\n"; return;}
    if((nbPoints < 0) || (nbPoints > 1e9)) { std::cerr << "ERR: manageSims::motherSensitivity, out of bounds number of points " << nbPoints << "\n"; return;}
    if(vstart < 0) vstart = currentModel->getLowerBound(parameterIndex);
    if(vending < 0) vending = currentModel->getUpperBound(parameterIndex);

    vector<double> valuesToTest = cutSpace(nbPoints, logarithmic, base, vstart, vending);
    int NV = currentModel->getNbVars();
    for(int i = 0; i < nbPoints; ++i){
        std::cout << "sensitivity" << i << ", param" << parameterIndex << " = " << valuesToTest[i] ;
        currentModel->setParameters(initialSet);
        currentModel->setParam(parameterIndex, valuesToTest[i]);
        parameters = currentModel->getParameters();
        double v = getCost();
        std::cout << "\t cost=" << v << std::endl;
        vector<double> costPerVariable = vector<double>(NV, 0);
        for(int j = 0; j < NV; ++j){
            costPerVariable[j] = currentExperiment->costVariableInModel(j);
        }
        vector<double> costPerExperiment = vector<double>(currentExperiment->getNbCond(), 0);
        for(int j = 0; j < currentExperiment->getNbCond(); ++j){
            costPerExperiment[j] = currentExperiment->costExp(j);
        }
        sensitivities[parameterIndex]->add(parameterIndex, valuesToTest[i], v, costPerVariable, costPerExperiment, currentModel->getParameters());

    }
    //sensitivities[parameterIndex]->sort();

    // call the mother recursive
}


// *** Analysis of a single experiment ***

#ifndef WITHOUT_QT
void simuWin::identifiability(){
    int NP = currentModel->getNbParams();
    QStringList items;
    for(int i = 0; i < NP; ++i){
        items << QString::number(i) + QString("-") + QString(currentModel->getParamName(i).c_str());
    }
    bool okPressed = false;
    QString chosenTextParameter = QInputDialog::getItem(this, QString("Choose Parameter"),QString("Identifiability "), items,0, false, &okPressed);
    int chosenParameter = -1;
    for(int i = 0; i < NP; ++i){
        if(!(QString::number(i) + QString("-") + QString(currentModel->getParamName(i).c_str())).compare(chosenTextParameter)) chosenParameter = i;
    }
    if(chosenParameter < 0) {std::cerr << "ERR: identifiability, couldn't find which parameter was chosen - should not happen" << std::endl; return;}
    //takes long. Better to do it one parameter at a time. Use 'Stop' button if too long."
    //"Please choose which parameter to perform practical identifiability (likelyhood profile)
    if(!okPressed) return;

    okPressed = false;
    int nrPoints = QInputDialog::getInt(this, QString("Number of points"),QString("Choose the number of points for the identifiability"), 20, 2, 10000, 1, &okPressed);
    if((nrPoints < 2) || (nrPoints > 10000)) std::cerr << "ERR: simuWin::identifiability() picked out of bounds nmumber of points for identifiability " << nrPoints << ", should have been discarded by qt getInt??" << std::endl;
    if(!okPressed) return;

    stopOpt = false;
    currentlyOptimizing = true;
    nbCostCalls = 0;
    //if(ui->lineEditWorkingFolder->text().size() == 0)
    ui->lineEditWorkingFolder->setText(QFileDialog::getExistingDirectory(this, tr("Choose Directory to do identifiability!"), ui->lineEditWorkingFolder->text(),QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks));
    if(ui->lineEditWorkingFolder->text().size() == 0) {std::cerr << "No Directory\n"; return;}


    string  optMethodText = optChoice->generate();
    this->createComb();
    //for(int i = 0; i < NP; ++i){
        prepareOptFilesForIdentifibiality(ui->lineEditWorkingFolder->text().toStdString(), -1, nbCombs-1, optMethodText);
    //}
    vector<double> currentParamSet = currentModel->getParameters();

    ui->checkBoxDisplayCurves->setChecked(false);
    motherIdentifiability(currentParamSet, chosenParameter, nrPoints);

    makeIdentifibialityReport(chosenParameter, ui->lineEditWorkingFolder->text().toStdString() + string("/"));

    ui->checkBoxDisplayCurves->setChecked(true);
    stopOpt = true;
    currentlyOptimizing = false;

    makeFigReportParamSet(ui->lineEditWorkingFolder->text().toStdString() + string("/"));
}
#endif

void manageSims::prepareOptFilesForIdentifibiality(string folder, int parameterIndex, int indexComb, string optMethodText){
    int NP = currentModel->getNbParams();
    if(parameterIndex >= NP) {std::cerr << "ERR: manageSims::prepareOptFilesForIdentifibiality, parameterIndex out of bounds (" << parameterIndex << ")\n"; return;}
    optFileNamesIdentifiability.clear();
    optFileNamesIdentifiability.resize(NP);
    for(int i = 0; i < NP; ++i){
        if((i == parameterIndex) || (parameterIndex < 0)){
            std::stringstream fileName;
            fileName << folder << "/OptForParam" << i << "InComb" << indexComb << ".txt";
            optFileNamesIdentifiability[i] = fileName.str();
            std::cout << "   -> Creating optimizer file for the identifiability of parameter " << i << " (" << currentModel->getParamName(i) << ")" << std::endl;
            string optFileWithoutTheParameter = motherCreateOptimizerFile(indexComb, optMethodText, i);
            std::ofstream f(fileName.str().c_str(), std::ios::out);
            if(f){
                f << optFileWithoutTheParameter; f.close();
                std::cout << "      ... file saved in " << fileName.str() << std::endl;
            } else std::cerr << "ERR: manageSims::prepareOptFilesForIdentifibiality, could not create " << fileName.str() << std::endl;
        }
    }
}

void manageSims::motherIdentifiability(vector<double>& initialSet, int parameterIndex, int nrPoints){
    if(currentMode == MULTI_EXPERIMENT){std::cerr << "ERR: manageSims::motherIdentifiability is not allowed in the MULTI_EXPERIMENTS mode\n"; return;}
    int NP = currentModel->getNbParams();
    if(parameterIndex >= NP) return;
    if((int) identifiabilities.size() != NP) {std::cerr << "Internal ERR:  manageSims::motherIdentifiability, identifiabilities has wrong size (" << identifiabilities.size() << ")compared to nb of parameters (" << NP << ")\n";}
    //vector<double> initialParamSet = currentModel->getParameters();
    for(int i = 0; i < NP; ++i){
        if((parameterIndex == i) || (parameterIndex < 0)){

                if(stopOpt == true) {return;}

                if(identifiabilities[i]) delete identifiabilities[i];
                identifiabilities[i] = new oneParameterAnalysis(initialSet);

                ///// puts the initial set as the first line - actually, for identifiability, we don't need an initial parameter set, or maybe just as comparison
                currentModel->setParameters(initialSet);
                parameters = initialSet;
                double v = getCost();
                vector<double> costPerVariable = vector<double>(currentModel->getNbVars(), 0);
                for(int j = 0; j < currentModel->getNbVars(); ++j){
                    costPerVariable[j] = currentExperiment->costVariableInModel(j);
                }
                vector<double> costPerExperiment = vector<double>(currentExperiment->getNbCond(), 0);
                for(int j = 0; j < currentExperiment->getNbCond(); ++j){
                    costPerExperiment[j] = currentExperiment->costExp(j);
                }
                identifiabilities[i]->add(i, initialSet[i], v, costPerVariable, costPerExperiment, currentModel->getParameters());


                double lowCorrect = currentModel->getLowerBound(i);
                if(currentModel->getLowerBound(i) < 1e-12) lowCorrect = initialSet[i] / 1000;
                motherRecursiveIdentifibiality(initialSet, i, nrPoints, true, 2, lowCorrect, currentModel->getUpperBound(i), 5);
                std::cout << "Parameter " << i << " finished" << std::endl;


                //std::cout << identifiabilities[i]->print();

        }
    }
    currentModel->setParameters(initialSet);
    parameters = initialSet;
    //double v = getCost();
    std::cout << "Identifiability finished" << std::endl;
}

void manageSims::motherRecursiveIdentifibiality(vector<double>& initialSet, int parameterIndex, int nbPoints, bool logarithmic, double base, double vstart, double vending, int deepLevel){
    if(recording) currentMacro << "macro" << macroID << "." << ".motherRecursiveIdentifibiality(" << parameterIndex << "," << nbPoints << "," << (logarithmic ? "true": "false")  << "," << base << "," << vstart << "," << vending << "," << deepLevel << ")" << "\n";
    #ifdef ALLOW_OPTIMIZE
    if(deepLevel == 0) return;
    if(deepLevel < 0) deepLevel = 0;
    if(deepLevel > 1000) { std::cerr << "ERR: manageSims::motherRecursiveIdentifibiality, out of bounds number of levels " << deepLevel << std::endl; return;}
    if((parameterIndex < 0) || (parameterIndex > currentModel->getNbParams())){std::cerr << "ERR: manageSims::motherRecursiveIdentifibiality, wrong parameter index "<< parameterIndex << ", only " << currentModel->getNbParams() << " parameters\n"; return;}
    if((nbPoints < 0) || (nbPoints > 1e9)) { std::cerr << "ERR: manageSims::motherRecursiveIdentifibiality, out of bounds number of points " << nbPoints << "\n"; return;}
    if(vstart < 0) vstart = currentModel->getLowerBound(parameterIndex);
    if(vending < 0) vending = currentModel->getUpperBound(parameterIndex);

    vector<double> valuesToTest = cutSpace(nbPoints, logarithmic, base, vstart, vending);
    int NV = currentModel->getNbVars();
    for(int i = 0; i < (int) valuesToTest.size(); ++i){
        for(int nRep = 0; nRep < 5; ++nRep ){

            if(stopOpt == true) {
                std::cerr << "Identifiability stopped by the user" << std::endl;
                return; // if the optimization was stopped
            }

            history.resize(1);
            history.clear();
            nbCostCalls = 0;
            currentModel->setParameters(initialSet);
            currentModel->setParam(parameterIndex, valuesToTest[i]);
            std::cout << "      ... Identifiability, point " << i+1 << "." << nRep + 1 << " / " << nbPoints << ", param " << parameterIndex << "(" << currentModel->getParamName(parameterIndex) << ") = " << valuesToTest[i] << " ";
            GeneralImplementation::initialize();
            myRandom::Randomize();
            myTimes::getTime();
            BaseOptimizationProblem *E = this; //new simuWin(currentExperiment, this);
            BaseOptimizer *Opt = BaseOptimizer::createOptimizer(E, optFileNamesIdentifiability[parameterIndex]);
            //mySignal::addOptimizer(Opt);
            Opt->optimize();
            //Opt->bestGlobal.print();
            //delete E; // Do not do that :-)
            currentModel->needNewParameterSet();
            delete Opt;
            currentModel->setParameters(history.toVector()[0]->v);
            parameters = history.toVector()[0]->v;
            double v = getCost();
            std::cout << " -> Cost : " << v << std::endl;
            vector<double> costPerVariable = vector<double>(NV, 0);
            for(int j = 0; j < NV; ++j){
                costPerVariable[j] = currentExperiment->costVariableInModel(j);
            }
            vector<double> costPerExperiment = vector<double>(currentExperiment->getNbCond(), 0);
            for(int j = 0; j < currentExperiment->getNbCond(); ++j){
                costPerExperiment[j] = currentExperiment->costExp(j);
            }
            identifiabilities[parameterIndex]->add(parameterIndex, valuesToTest[i], v, costPerVariable, costPerExperiment, currentModel->getParameters());
            currentModel->needNewParameterSet();
        }
    }

    std::cout << "Identifiability finished for this parameter\n";

    //identifiabilities[parameterIndex]->sort();
    #else
    std::cerr << "manageSims::motherRecursiveIdentifibiality(...), this function is only allowed when ALLOW_OPTIMIZE is defined, in order to include the optimizations files during compilation.\n";
    #endif

}

void manageSims::makeIdentifibialityReport(int parameterID, string existingBaseFolder, int currentConfigID){
    if(currentMode == MULTI_EXPERIMENT){std::cerr << "ERR: manageSims::makeIdentifiabilityReport is not allowed in the MULTI_EXPERIMENTS mode\n"; return;}
    if(parameterID >= currentModel->getNbParams()){std::cerr << "ERR: manageSims::makeIdentifibialityReport(paramID= " << parameterID << "), out of bounds, only " << currentModel->getNbParams() << " parameters\n"; return;}
    if(parameterID < 0) {
        for(int i = 0; i < currentModel->getNbParams(); ++i){
            makeIdentifibialityReport(i, existingBaseFolder, currentConfigID);
        }
        return;
    }

    int NP = currentModel->getNbParams();
    int NV = currentModel->getNbVars();
    int NE = currentExperiment->getNbCond();
    oneParameterAnalysis* data = identifiabilities[parameterID];
    std::stringstream head;
    head << "PointNr\tIDparam\tValue\tCost\tNbExps\t";
    for(int i = 0; i < NE; ++i){
        head << "\"" << currentExperiment->getConditionName(i) << "\"\t";
    }
    head << "NbVars\t";
    for(int i = 0; i < NV; ++i){
        head << "\"" << currentModel->getName(i) << "\"\t";
    }
    head << "NbParameters\t";
    for(int i = 0; i < NP; ++i){
        head << "\"" << currentModel->getParamName(i) << "\"\t";
    }
    head << std::endl;
    head << data->print();

    std::stringstream fname; fname << existingBaseFolder << "/reportIdentifParam" << parameterID << ".txt";
    std::cout << "   -> Identifiability parameter " << parameterID << " saved in " << fname.str() << std::endl;
    std::fstream fp(fname.str(), std::ios::out); if(fp) {fp << head.str(); fp.close();} else {std::cerr << "ERR: Failed to write in " << fname.str() << std::endl;}




    std::stringstream Rscr;
    //Rscr << "install.packages(\"stringr\")\n";
    Rscr << "library(stringr) #for str_replace\n";
    Rscr << "setwd(\"" << existingBaseFolder << "\");\n";
    Rscr << "a <- read.table(\"" << fname.str() << "\", header=TRUE);";
    Rscr << "#changing . to space in the column names ; saved in nm\n";
    Rscr << "nm <- colnames(a)\n";
    Rscr << "nm <-str_replace_all(nm, fixed(\".\"), \" \")\n";
    Rscr << "# there are " << NP << " parameters, " << NV << " variables and " << NE << " conditions " << std::endl;

    // 1 ------------------- main plot : global cost
    Rscr << "png(filename=\"IdentifP" << parameterID << "A0.png\");\n";
    Rscr << "plot(a[,3], a[,4], type=\"o\", pch=1, cex = 1, col=\"mediumorchid4\", main=\"Cost profile for P" << parameterID << "(" << currentModel->getParamName(parameterID) << ")\", sub=\"Each point is an optimization around the best parameter set\", xlab=nm[3], ylab=nm[4], lwd=1);\n";
    Rscr << "dev.off();\n";





    vector<string> Rcolors = {string("red"), string("royalblue"), string("seagreen1"), string("darkorchid"), string("gold"), string("deeppink"), string("lightsalmon"), string("mediumpurple"), string("mediumspringgreen"), string("midnightblue"), string("orange1"), string("palegreen"), string("chartreuse3"), string("blue2"), string("firebrick1")};

    // 2 ------------------- cost per experiment
    for(int t = 0; t < 2; ++t)
    {
        Rscr << "png(filename=\"IdentifP" << parameterID << "A1-perExperiment" << ((t == 0) ? "-lin" : "-log") << ".png\");\n";
        Rscr << "axisMax = max_(a[,4]/" << NE;
        for(int i = 0; i < NE; ++i){
            Rscr << ", a[," << 6+i << "]";
        }
        Rscr << ");\n";

        Rscr << "plot(a[,3], a[,4]/" << NE << "," << ((t == 1) ? "log=\"x\"," : "") << "ylim=c(0, axisMax * 1.2), type=\"o\", pch=1, cex = 1, col=\"mediumorchid4\", main=\"Cost profile for P" << parameterID << "(" << currentModel->getParamName(parameterID) << ")\", sub=\"Each point is an optimization around the best parameter set\", xlab=nm[3], ylab=nm[4], lwd=1);\n";
        for(int i = 0; i < NE; ++i){
            Rscr << "lines(a[,3], a[," << 6+i << "], type=\"o\", pch=1, cex = 1, col=\"" << Rcolors[i] << "\", lwd=1);\n";
        }

        Rscr << "legend(\"topright\", inset=0.05, legend=c(\"Average\",";
        for(int i = 0; i < NE; ++i){
            if(i > 0) Rscr << ",";
            Rscr << "\"" << currentExperiment->getConditionName(i) << "\"";
        }
        Rscr << "), lwd=c(1,1), lty=c(1,1), pch=c(1,2), pt.cex=c(1,1),";
        Rscr << "col=c(\"mediumorchid4\"";
        for(int i = 0; i < NE; ++i){
            Rscr << ",\"" << Rcolors[i] << "\"";
        }
        Rscr << "), cex=1, bg=\"white\", box.lwd=0.5, box.lty=1, box.col=\"black\");\n";
        Rscr << "dev.off();\n";
    }

    // 3 ------------------- correlation between parameters

    for(int i = 0; i < NP; ++i){
        if((i != parameterID) && ((currentConfigID < 0) || isInConfig(i, currentConfigID))){
            Rscr << "axisMax = max_(a[,3], a[," << 8+ NE + NV + i << "]);\n";
            Rscr << "costMin = min(a[," << 8+ NE + NV + i << "]);\n";
            for(int t = 0; t < 2; ++t){

                Rscr << "png(filename=\"IdentifP" << parameterID << "B" << i << "correl" << currentModel->getParamName(i) << ((t == 0) ? "-lin" : "-log") << ".png\");\n";
                Rscr << "plot(a[,3], a[," << 8+ NE + NV + i << "]," << ((t == 1) ? "log=\"x\"," : "") <<  "ylim=c(0, axisMax * 1.2), type=\"o\", pch=1, cex = 1, col=\"mediumorchid4\", main=\"Best fit for P " << i << " (" << currentModel->getParamName(i) << "), when identifying P" << parameterID << "(" << currentModel->getParamName(parameterID) << ")\", sub=\"Each point is an optimization around the best parameter set\", xlab=\"forced value P" << parameterID << " (" << currentModel->getParamName(parameterID) << ")\", ylab=\"Fitted value for P" << i << " (" << currentModel->getParamName(i) << ")\", lwd=1);\n";
                Rscr << "dev.off();\n";

                Rscr << "png(filename=\"IdentifP" << parameterID << "B" << i << "correl" << currentModel->getParamName(i) << "Zoom" << ((t == 0) ? "-lin" : "-log") << ".png\");\n";
                Rscr << "plot(a[,3], a[," << 8+ NE + NV + i << "]," << ((t == 1) ? "log=\"x\"," : "") <<  "ylim=c(costMin, costMin * 2.5), type=\"o\", pch=1, cex = 1, col=\"mediumorchid4\", main=\"Best fit for P " << i << " (" << currentModel->getParamName(i) << "), when identifying P" << parameterID << "(" << currentModel->getParamName(parameterID) << ")\", sub=\"Each point is an optimization around the best parameter set\", xlab=\"forced value P" << parameterID << " (" << currentModel->getParamName(parameterID) << ")\", ylab=\"Fitted value for P" << i << " (" << currentModel->getParamName(i) << ")\", lwd=1);\n";
                Rscr << "dev.off();\n";
            }
        }
    }

    std::stringstream Rname; Rname << existingBaseFolder << "/RscriptP" << parameterID << ".R";
    std::fstream fR(Rname.str(), std::ios::out); if(fR) {fR << Rscr.str(); fR.close();}

    std::stringstream cmd; cmd << "R --vanilla < " << Rname.str() << std::endl;
    system(cmd.str().c_str());

}



/*  void test

double tryfunct(double x){
    return 0.02 * (x-2) * (x-3) * sin(x);
}

void tryrecursive(vector<double>& initialSet, int parameterIndex, int nbPoints, bool logarithmic, double base, double vstart, double vending, int deepLevel){
    if(deepLevel == 0) return;
    if(deepLevel < 0) deepLevel = 0;
    if(deepLevel > 1000) { std::cerr << "ERR: manageSims::motherRecursiveIdentifibiality, out of bounds number of levels " << deepLevel << std::endl; return;}
    if((nbPoints < 0) || (nbPoints > 1e9)) { std::cerr << "ERR: manageSims::motherRecursiveIdentifibiality, out of bounds number of points " << nbPoints << "\n"; return;}
    if(vstart < 0) vstart = 1.0;
    if(vending < 0) vending = 100.0;

    vector<double> valuesToTest = cutSpace(nbPoints, logarithmic, base, vstart, vending);

        identifiabilities[parameterIndex]->add(parameterIndex, valuesToTest[i], v, costPerVariable, costPerExperiment, currentModel->getParameters());

    //identifiabilities[parameterIndex]->sort();
    #else
    std::cerr << "manageSims::motherRecursiveIdentifibiality(...), this function is only allowed when ALLOW_OPTIMIZE is defined, in order to include the optimizations files during compilation.\n";
    #endif

}
*/















/*
void manageSims::orderSensitivityPoints(int parameterIndex){
    // stupid n² sort
    int nbPts = sensitivityXs[parameterIndex]->size();
    for(int i = 0; i < nbPts-1; ++i){
        for(int j = 0; j < nbPts - i; ++i){
            if((* sensitivityXs[parameterIndex])[i] > (* sensitivityXs[parameterIndex])[i+1]){
                double buf1 =           (* sensitivityXs[parameterIndex])[i];
                double buf2 =           (* sensitivityCosts[parameterIndex])[i];
                vector<double> buf3 =   (* sensitivityCostsPerVariable[parameterIndex])[i];
                (* sensitivityXs[parameterIndex])[i] =                  (* sensitivityXs[parameterIndex])[i+1];
                (* sensitivityCosts[parameterIndex])[i] =               (* sensitivityCosts[parameterIndex])[i+1];
                (* sensitivityCostsPerVariable[parameterIndex])[i] =    (* sensitivityCostsPerVariable[parameterIndex])[i+1];
                (* sensitivityXs[parameterIndex])[i+1] = buf1;
                (* sensitivityCosts[parameterIndex])[i+1] = buf2;
                (* sensitivityCostsPerVariable[parameterIndex])[i+1] = buf3;
            }
        }
    }
}

void manageSims::nextValues(int parameterIndex){
    // Look at the median dCost (for each variable)
    orderSensitivityPoints(parameterIndex);
    int currentNb = sensitivityXs[parameterIndex]->size();
    vector< vector<double> > slopesPerVariable;
    // for each interval that is more than the average
    for(int i = 0; i < currentNb-1; ++i){
        double slope = (* sensitivityCostsPerVariable[parameterIndex])[i];
    }
    vector<double>


}
*/
// change all _ into - for latex
string cure(string tocure){
    replace( tocure.begin(), tocure.end(), '_', '-');
    return tocure;
}

/* Analysis of a single experiment */
string manageSims::makeTextReportParamSet(string _folder, int configuration, double simDt, double displayDt){
    //if(currentMode == MULTI_EXPERIMENT){std::cerr << "WRN: Be careful that the report is done only for the current experiment (not for all of them) !!\n";}

    //if(currentConfig.size() == 0) { "ERR: manageSims::makeTextReportParamSet, you have to load a configuration first, before doing a parameter set report. Sorry !\n"; return string("");}
    if(_folder.size() == 0) {std::cerr << "ERR: manageSims::makeTextReportParamSet, empty folder name\n"; return string("");}
    if((configuration < 0) || (configuration >= nbCombs)) {std::cerr << "ERR: manageSims::makeTextReportParamSet, bad configuration index(" << configuration << " out of " << nbCombs << " possible configurations\n"; return string("");}

    // - the folder has to be created before
    // - Recapitulates the list of simulated variables and optimized parameters with their names and boundary,
    // - for each simulated variable, table of values for simulations versus data (if there is data), and cost of this curve
    // ?? - makes a fitness report : for each data point, simulated value versus data

     currentModel->setPrintMode(true, currentModel->print_every_dt);

     if(displayDt > 0){
        if(( displayDt <= 1e-6) || ( displayDt >= 1e12)) {std::cerr << "ERR: manageSims::makeTextReportParamSet, too huge/small dt for fsaving the kinetics(" << displayDt << ")\n"; return string("");}
        currentModel->setPrintMode(true, displayDt);    // ui->doubleSpinBoxGraphDT->value();
    }
    if(simDt > 0){
        currentModel->dt = simDt;                       //  ui->doubleSpinBoxSimDT->value();
        if((simDt <= 1e-9) || (simDt >= 1e12)) {std::cerr << "ERR: manageSims::makeTextReportParamSet, too huge/small dt for simulation(" << simDt << ")\n"; return string("");}
    }

    std::stringstream f;
    std::stringstream tex;
    f << "================== Parameter set report =================== \n\n" ;


    int NV = currentModel->getNbVars();
    int NP = currentModel->getNbParams();


    f << "Fitted parameter values, inside their boundaries : \n";
    //std::cerr << currentConfig.size() << "\t" << nbCombs << "\t" << configuration << std::endl;
    for(int i = 0; i < NP; ++i){
        if(!currentConfig[i][4+configuration].compare("1")) f << i << "\t" << currentModel->getParamName(i) << "\t" << currentModel->getParam(i) << "\t" << currentModel->getLowerBound(i) << "\t" << currentModel->getUpperBound(i) << "\n";
        else f << i << "\t" << currentModel->getParamName(i) << "\t" << currentModel->getParam(i) << "\t" << "fixed" << "\t" << "fixed" << "\n";
    }
    f << "Simulated variables : \n";
    for(int i = 0; i < NV; ++i){
        if(! currentModel->over(i)) f << i << "\t" << currentModel->getName(i) << "\n";
    }

    // ========================= building a tex with the same information =======================
    tex << "\\part{Report of simulation, generated automatically from Moonfit.}\n";
    tex << "All infos are also available inside the same folder, including: \n";
    tex << "\\begin{enumerate}\n";
    tex << "\\item {\\bf{SimResult.txt:}} The list of parameter values, the numerical values for the simulation of each curve, either sorted per variable or per condition (experiment), and the cost of each curve compared to its own dataset.\n";
    tex << "\\item {\\bf{ConfigPlusCurrent.txt:}} The current configuration when the report was generated. The current combinations of variables to optimized, chosen by manual checking in the graphical interface, is added as a new, last combination.\n";
    tex << "\\end{enumerate}\n";
    tex << "\\subsection{Parameter values and fitting configuration}\n";
    tex << "\\begin{tabular}{| c | l | c | c | c | }\n";
    tex << "\\hline\n index \t& param. name \t& value simulated \t& max_ fit bound \t& min fit bound \\\\\n";
    tex << "\\hline\n\\hline\n";
    for(int i = 0; i < NP; ++i){
        if(!currentConfig[i][4+configuration].compare("1"))
            tex << i << "\t& " << cure(currentModel->getParamName(i)) << "\t& " << currentModel->getParam(i) << "\t& " << currentModel->getLowerBound(i) << "\t& " << currentModel->getUpperBound(i) << "\\\\\n";
        else
            f << i << "\t& " << cure(currentModel->getParamName(i)) << "\t& " << currentModel->getParam(i) << "\t& " << "fixed" << "\t& " << "fixed" << "\\\\\n";
    }
    tex << "\\hline\n";
    tex << "\\end{tabular}\n";
    tex << "\n\nNote: the parameter set shown in the table is used to make the plots. It was the current parameter set when the report was made, potentially modified by the user in the graphical interface, so it is not necessarily the result of a fitting.\n";

    tex << "\\subsection{Variables simulated and overrider by data}\n";

    tex << "\\begin{tabular}{| c | l | c |}\n";
    tex << "\\hline\n index \t& var. name \t& sim or replaced by data\\\\\n";
    tex << "\\hline\n\\hline\n";
    for(int i = 0; i < NV; ++i){
        if(! currentModel->over(i)) tex << i << "\t& " << cure(currentModel->getName(i)) << "\t& simulated\\\\\n";
        else tex << i << "\t& " << cure(currentModel->getName(i)) << "\t& replaced by dynamical data (all curves)\\\\\n";
    }
    tex << "\\end{tabular}\n";

    tex << "\\subsection{Cost of the simulation compared to data}\n";
    tex << "The data used to get the cost calculation and to override data are detailed inside the file experiment.txt\n";
    tex << "\n\\vspace{0.3cm}\nTotal cost for the current parameter set : " << currentExperiment->costVariableInModel() << std::endl;
    tex << "\nThe function used to calculate the cost is:" << costConfig::CurrentCost() << ", i.e.,";

    switch(costConfig::typeCost){
    case SQUARE_COST:
        tex << "SQUARE-COST: RSS (without using data standard deviation): $\\sum_{idExp i,idDataPt j}(Xsim_{i,j}- Xdata_{i,j})^2$\n";
        tex << "Note: this cost functions is NOT normalized to the number of datapoints per experiment.\n";
    break;
    case SQUARE_COST_STD:
        tex << "SQUARE-COST-STD: RSS with standard deviations $\\sigma$ (= max_ likelyhood): $\\sum_{idExp i,idDataPt j}(\\frac{Xsim_{i,j}- Xdata_{i,j}}{\\sigma_{i,j}}})^2$ (but using $\\sigma_{i,j} = 1$ when $abs(\\sigma_{i,j}}) < 1e^{-8}$) \n";
        tex << "Note: this cost functions is NOT normalized to the number of datapoints per experiment.\n";
    break;
    case LOG_COST:
        tex << "LOG-COST: Log scale comparison : $\\sum_{idExp i,idDataPt j}abs(log(abs(Xsim_{i,j}))- log(abs(Xdata_{i,j})))$\n";
        tex << "Note: this cost functions is NOT normalized to the number of datapoints per experiment.\n";
    break;
    case PROPORTION_COST:
        tex << "PROPORTION-COST: comparison as ratio to the mean (without using data standard deviation): $\\sum_{idExp i,idDataPt j}\\frac{Xsim_{i,j}}{max_(abs(Xdata_{i,j}, 1e-3)})$. Note: if the data is less than $1e-3$, its value is bounded such that this datapoints doesn't get a cost diverging to infinite and taking over the cost compared to other datapoints. If your data falls around this range you might need to change the 1e-3 bound, see inside evaluator.cpp, fitness function\n";
        tex << "Note: this cost functions is NOT normalized to the number of datapoints per experiment.\n";
    break;
    }

    switch(costConfig::typeNorm){
        case NO_NORM: {tex << "NO-NORM - no normalization \n"; break;}
        case NORM_AVERAGE: {tex << "NORM-AVERAGE: for each variable, and each condition, the average value among all time-points is used to normalize the cost of each-point.\n"; break;}
        case NORM_NB_PTS:  {tex << "NORM-NB_PTS: for each variable and each condition, the cost is divided by the number of points. \n"; break;}
        case NORM_AVG_AND_NB_PTS:  {tex << "NORM-AVG-AND-NB-PTS: for each variable, and each condition, the average value among all time-points is used to normalize the cost of each-point, and also divided by the number of points in this curve.\n"; break;}
        case NORM_MAX:  {tex << "NORM-MAX: for each variable, and each condition, the maximum value among all time-points is used to normalize the cost of each-point. \n"; break;}
        case NORM_MAX_AND_NB_PTS:  {tex << "NORM-MAX-AND-NB-PTS: for each variable, and each condition, the maximum value among all time-points is used to normalize the cost of each-point, and also divided by the number of points in this curve. \n"; break;}
    }

    tex << "If no cost function is displayed here, it means it is a customized one. To define your own customized cost function, look at evaluator.cpp inside the fitness() function and define a new one and modify the choice of the used cost function inside evaluator.h. You may update this message in simuwin.cpp - function makeTextReportParamSet()\n";

    tex << "\n\\begin{centering}\n";
    tex << "\n\n\\begin{tabular}{| c | l | c |}\n";
    tex << "\\hline\n";
    tex << "ExpNr   \t& Name \t& Cost Condition \\\\\n";
    tex << "\\hline\n";
    tex << "\\hline\n";
    for(int i = 0; i < currentExperiment->nbConditions; ++i){
        tex << i << "\t& " << cure(currentExperiment->names_exp[i]) << "\t& " << currentExperiment->costExp(i) << "\\\\\n";
    }
    tex << "\\hline\n";
    tex << "\\end{tabular}\n";
    tex << "\\begin{tabular}{| c | l | l | c |}\n";
    tex << "\\hline\n";
    tex << "VarNr   \t& Var Name \t& Var Global Name \t& Cost all exps \\\\\n";
    tex << "\\hline\n";
    tex << "\\hline\n";
    for(int i = 0; i < currentExperiment->m->getNbVars(); ++i){
        tex << i << "\t& " << cure(currentExperiment->m->getName(i)) << "\t& " << currentExperiment->m->getExternalName(i) << "\t& " << currentExperiment->costVariableInModel(i)  << "\\\\\n";
    }
    tex << "\\hline\n";
    tex << "\\end{tabular}\n";
    tex << "\\end{centering}\n";
    tex << "\\newpage\n";

    std::ofstream expT(_folder + "texReport.tex");
    expT << tex.str() << std::endl;
    expT.close();

    // ===================== End of tex file =========================


    std::ofstream expf(_folder + "experiment.txt");
    expf << currentExperiment->print() << std::endl;
    expf.close();

    std::ofstream expS(_folder + "LastSensitivity.txt");
    int SI = sensitivities.size();
    for(int i = 0; i < SI; ++i){
        if(sensitivities[i]) expS << sensitivities[i]->print() << std::endl;
    }
    expS.close();

    std::ofstream expI(_folder + "LastIdentifiability.txt");
    int SI2 = identifiabilities.size();
    for(int i = 0; i < SI2; ++i){
        if(identifiabilities[i]) expI << identifiabilities[i]->print() << std::endl;
    }
    expI.close();



    //std::cerr << "Step 1" << std::endl;
    //std::ofstream f1((_folder + string("")).c_str(), std::ios::out);
    //if(!f1) {std::cerr << "File not Found" << std::endl; return;}


    int nbExp = currentExperiment->getNbCond();

    // simulate once for the kinetics, per experiment, and store everything in currentData
    if(currentData.size() == 0) currentData.resize(currentExperiment->getNbCond(), NULL);
    for(int i = 0; i < nbExp; ++i){
        f << "Simulated kinetics for experiment " << currentExperiment->names_exp[i] << "\n";
        currentExperiment->simulate(i, NULL, true);
        if(currentData[i]) {delete currentData[i]; currentData[i] = NULL;}
        currentData[i] = new TableCourse(currentModel->getCinetique());
        if(currentModel->penalities > 0){
            f << "Note : simulation diverged for experiment (" << currentExperiment->getConditionName(i) << ") with penalty " << currentExperiment->m->penalities << "\n";
        }
        f << currentModel->getCinetique().print();
    }
    //std::cerr << "Step 2" << std::endl;
    f << "Total cost of parameter set : " << currentExperiment->costVariableInModel() << std::endl;
    for(int j = 0; j < NV; ++j){
        if(! currentModel->over(j)){
            f << "Simulated kinetics for variable " << j << " : " << currentModel->getName(j) << "\n";
            if(currentExperiment->canOverride(currentModel->getExternalName(j))) {f << "Cost : " << currentExperiment->costVariableInModel(j) << "\n";}
            if(nbExp < 1) return string("No Experiment !");
            vector<double> Xs = currentData[0]->getTimePoints();
            vector< vector<double>* > packData;
            for(int i = 0; i < currentExperiment->getNbCond(); ++i){
                packData.push_back(new vector<double>(currentData[i]->getTimeCourse(j)));
                //// if(packData[i]->size() != Xs.size()) std::cerr << "ERR: manageSims::makeTextReportParamSet, exp " << currentExperiment->expName(i) << ", kinetics from different variables have different number of time points\n";
            }
            int nbTp = Xs.size();


            for(int k = 0; k < nbTp; ++k){
                f << Xs[k];
                for(int i = 0; i < currentExperiment->getNbCond(); ++i){
                    if(k < packData[i]->size()){
                        f << "\t" << (*packData[i])[k];
                    } else {
                        f << "\t" << NAN;
                    }
                }
                f << "\n";
            }
        }
    }
    //std::cerr << "Step 3" << std::endl;
    f << "Detailed costs \n";
    f << currentExperiment->costReport();


    std::cerr << "Report finished" << std::endl;
    return f.str();
}




void manageSims::addMacro(string text){
    currentMacro << text << "\n";
}
void manageSims::addFileTextToMacro(string text, string fileName){
    currentMacro << "/* ---------- Informations about a text file : -------- \n";
    if(fileName.size() > 0) currentMacro << fileName << "\n";
    currentMacro << "// ------------------ Content of file : --------------- \n";
    currentMacro << text;
    currentMacro << "// ---------------------------------------------------- */\n";
}
string manageSims::getMacro(){
    return currentMacro.str();
}
void manageSims::startMacro(string experimentName){
    recording = true;
    currentMacro.clear();
    currentMacro << "// ================= New automatically generated macro ============ \n";
    currentMacro << "manageSims* macro" << macroID << " = new manageSims(experimentName)\n";
}
void manageSims::addFileToMacro(string fileName){
    std::ifstream inFile;
    inFile.open(fileName);//open the input file
    std::stringstream strStream;
    strStream << inFile.rdbuf();
    addFileTextToMacro(strStream.str(), fileName);
}


















/// =============================== GRAPHICAL INTERFACE ===================================

























#ifndef WITHOUT_QT

#define TABLE currentTable
simuWin::simuWin(Experiment* _Exp, QWidget *parent): manageSims(_Exp),
    ui(new Ui::simuWin), paramSetID(0) // QWidget(parent),
{
    ui->setupUi(this);
    reset();
    #ifdef ALLOW_OPTIMIZE
    optChoice = new optSelect(ui->widgetOpt);
    #endif
}

simuWin::simuWin(MultiExperiments* _Exp, QWidget *parent): manageSims(_Exp),
    ui(new Ui::simuWin), paramSetID(0) // QWidget(parent),
{
    ui->setupUi(this);
    reset();
    #ifdef ALLOW_OPTIMIZE
    optChoice = new optSelect(ui->widgetOpt);
    #endif
}

void simuWin::updateCostLabel(){
    if((costConfig::typeCost != ui->comboBoxCostType->currentIndex()) || (costConfig::typeNorm != ui->comboBoxCostNorm->currentIndex())){
        std::cout << "Changing the type of cost function from " << costConfig::CurrentCost() << " to ";
        std::cout << ui->comboBoxCostType->currentText().toStdString() << " Norm: " << ui->comboBoxCostNorm->currentText().toStdString() << std::endl;
        int res = QMessageBox::question(this, QString("Confirm Cost Change"), QString("The Cost function will be changed, the history will be cleared and the previous sensitivities/identifiabilities will be cleared. Do you confirm ?"), QMessageBox::Yes | QMessageBox::No);
        if(res == QMessageBox::No) return;
    } else return;

    costConfig::typeCost = ui->comboBoxCostType->currentIndex();
    costConfig::typeNorm = ui->comboBoxCostNorm->currentIndex();

    ui->labelCostFn->setText(QString(costConfig::CurrentCost().c_str()));

    history.clear();
    refreshHistory();

    int NS = sensitivities.size();
    for(int i = 0; i < NS; ++i){
        delete sensitivities[i];
        sensitivities[i] = NULL;
    }

    int NI = identifiabilities.size();
    for(int i = 0; i < NI; ++i){
        delete identifiabilities[i];
        identifiabilities[i] = NULL;
    }

    simulate();
}

// not : didn't test whether reset() can be called multiple times ...
void simuWin::reset(){
    if(!currentModel) {std::cerr << "simuWin::reset() was called from a non-existing model"; return;}
    if((currentMode != MULTI_EXPERIMENT) && (!currentExperiment)) {std::cerr << "simuWin()::reset() was called from a non-existing experiment (MONO_exp mode)\n"; return;}
    if((currentMode == MULTI_EXPERIMENT) && (!listExperiments)) {std::cerr << "simuWin()::reset() was called from a non-existing group of experiment (MULTI_exp mode)\n"; return;}

    nbCombs = 0;                    // empty configuration to start ...
    removeMode = false;             // the buttons of the configuration panel are in 'Add' or 'Del' mode
    stopOpt = false;                // signal to stop an optimization at any time
    currentlyOptimizing = false;
    lastParamID = -1;               // ID of the last parameter that was modified from the table --> will have its own spin bow under the main graph
    nbCostCalls = 0;

    ui->doubleSpinBoxGraphDT->setMaximum(1000000);
    ui->doubleSpinBoxGraphDT->setValue(currentModel->print_every_dt);
    ui->groupBoxFuture->hide();     // buttons not yet implemente
    ui->labelModelName->setText(currentModel->name.c_str());
    ui->checkBoxAll->setChecked(true);

    // Creates the main graph and plots an example graphe to check that the plotting is working. This example should be erased just afterwards.
#ifdef USE_QWT
    currentGraphe = new Graphe2(ui->widgetGraphe);
    costGraphe = new Graphe2(ui->widgetCostEvolution);
#endif
#ifdef USE_QCP
    currentGraphe = new grapheCustom(ui->widgetGraphe);
    costGraphe = new grapheCustom(ui->widgetCostEvolution);
#endif
    currentGraphe->Example();
    costGraphe->Example();
    costGraphe->setNbCurves(4);
    costGraphe->logarithmic(true);

#ifdef USE_BOOST_SOLVER
    ui->labelSolver->setText(QString("Solver: Adap-RK4"));
#else
    ui->labelSolver->setText(QString("Solver: Adap-Euler"));
#endif

    // STOP Val is defined inside evaluator.h
    ui->labelDivergence->setText(QString("Diverge: > ") + QString::number(STOP_VAL));


    QStringList ListCost;
    // take SAME ORDER AS enum{SQUARE_COST, SQUARE_COST_STD, LOG_COST, PROPORTION_COST};
    ListCost << "RSS" << "RSS+StdDev" << "Log" << "Ratios";
    ui->comboBoxCostType->insertItems(0, ListCost);
    ui->comboBoxCostType->setCurrentIndex(costConfig::typeCost);

    QStringList ListNorm;
    //take SAME ORDER AS enum{ NO_NORM, NORM_AVERAGE, NORM_NB_PTS, NORM_AVG_AND_NB_PTS
    ListNorm << "None" << "/ Average each var" << "/ N points each var" << "/ avg and N points" << "/ Max each var" << "/ Max and N points";
    ui->comboBoxCostNorm->insertItems(0, ListNorm);
    ui->comboBoxCostNorm->setCurrentIndex(costConfig::typeNorm);

    ui->labelCostFn->setText(QString(costConfig::CurrentCost().c_str()));

    // this function takes the combobox index and applies it to the config class and to the labels.
    updateCostLabel();

    QObject::connect(ui->comboBoxCostType, SIGNAL(currentIndexChanged(int)), this, SLOT(updateCostLabel()));
    QObject::connect(ui->comboBoxCostNorm, SIGNAL(currentIndexChanged(int)), this, SLOT(updateCostLabel()));
    ui->doubleSpinBoxCostMultiExp->setDisabled(true);
    ui->doubleSpinBoxCostMultiExp->setMaximum(1e8);
    ui->doubleSpinBoxCostMultiExp->setDecimals(5);
    ui->doubleSpinBoxCostExp->setDisabled(true);
    ui->doubleSpinBoxCostExp->setMaximum(1e8);
    ui->doubleSpinBoxCostExp->setDecimals(5);
    ui->doubleSpinBoxCostVar->setDisabled(true);
    ui->doubleSpinBoxCostVar->setMaximum(1e8);
    ui->doubleSpinBoxCostVar->setDecimals(5);
    ui->doubleSpinBoxLastParam->setDecimals(7);
    ui->lcdNumberCostCall->setDigitCount(10);
    ui->spinBoxDisplay->setValue(100);
    ui->spinBoxDisplay->setMinimum(10);
    ui->spinBoxDisplay->setMaximum(10000);
    ui->spinBoxStore->setValue(10000);
    ui->spinBoxStore->setMinimum(10);
    ui->spinBoxStore->setMaximum(1e9);
    ui->doubleSpinBoxSimDT->setMinimum(0.000001);
    ui->doubleSpinBoxSimDT->setMaximum(1000);
    ui->doubleSpinBoxGraphDT->setMinimum(0.01);
    ui->doubleSpinBoxGraphDT->setMaximum(100000);

    ui->doubleSpinBoxLastParam->setMinimum(1e-8);
    ui->doubleSpinBoxLastParam->setMaximum(1e8);

/*    // Values for Leishmania
    ui->doubleSpinBoxSimDT->setValue(0.0010);
    ui->doubleSpinBoxGraphDT->setValue(0.5);
    // Values for THDiff
    ui->doubleSpinBoxSimDT->setValue(10);
    ui->doubleSpinBoxGraphDT->setValue(5000); */

    ui->doubleSpinBoxSimDT->setValue(currentModel->dt);
    //ui->doubleSpinBoxGraphDT->setValue(currentModel->dt * 50);

    ui->checkBoxDisplayCurves->setChecked(true);
    ui->tabWidgetRight->setTabText(0, QString("Opt Method"));
    ui->tabWidgetRight->setTabText(1, QString("Cost in time"));
    ui->tabWidgetRight->setTabText(2, QString("Macro"));
    ui->checkBoxLinkToCombs->setChecked(false);

    ui->doubleSpinBoxCostExp->setButtonSymbols(QAbstractSpinBox::NoButtons);
    ui->doubleSpinBoxCostVar->setButtonSymbols(QAbstractSpinBox::NoButtons);



    // Table for the configuration
    currentModel->setBaseParameters();
    currentModel->initialise();     // needed to show parameters depending on other ones... Simulate will do it again...
    int Start = currentModel->getNbParams();
    int NV = currentModel->getNbVars();

    // In multi-experiment mode, fills a combo to chose which experiment. By default, the first one will be taken as currentExperiment (because it is the default selected one of the combo)
    ui->comboBoxMultiExperiment->clear();
    if(currentMode == MULTI_EXPERIMENT){
        // Fills combo
        int NE = listExperiments->nbBigExp();
        std::cout << "Initializing interface for " << NE << " experiments " << std::endl;
        for(int i = 0; i < NE; ++i){
            ui->comboBoxMultiExperiment->addItem(QString(listExperiments->getExperiment(i)->Identification.c_str()));
        }

        // Creates the table to compare the cost of each variable in each experiment
        tableMultiExpCosts = new QStandardItemModel(NE, NV+2, ui->tableViewMultiExp);
        for(int i = 0; i < NE; ++i){
            tableMultiExpCosts->setVerticalHeaderItem(i, new QStandardItem(QString(listExperiments->getExperiment(i)->Identification.c_str())));
        }
        tableMultiExpCosts->setHorizontalHeaderItem(0, new QStandardItem(QString("Coefficient")));
        tableMultiExpCosts->setHorizontalHeaderItem(1, new QStandardItem(QString("Total")));
        for(int j = 0; j < NV; ++j){
            tableMultiExpCosts->setHorizontalHeaderItem(j+2, new QStandardItem(QString(currentModel->getName(j).c_str())));
        }
        for(int i = 0; i < NE; ++i){    // the QStandardItems need to be created even if they are empty ...
            tableMultiExpCosts->setItem(i,0, new QStandardItem(QString::number((double) listExperiments->getCoefficient(i))));
            for(int j = 1; j < NV + 2; ++j){
                tableMultiExpCosts->setItem(i,j, new QStandardItem(QString("")));
                //tableHistory->item(j,i)->setBackground(QBrush(QColor(Qt::lightGray)));
            }
        }
    } else {
        ui->labelMultiExp->setText(QString((string("Experiment:    ") + currentExperiment->Identification).c_str()));
        ui->comboBoxMultiExperiment->hide();
        ui->doubleSpinBoxCostMultiExp->hide();
        ui->checkBoxCostMultiExp->hide();

        // the table will just show the cost of each variable for the current experiment.
        tableMultiExpCosts = new QStandardItemModel(1, NV+2, ui->tableViewMultiExp);
        tableMultiExpCosts->setHorizontalHeaderItem(0, new QStandardItem(QString("Coefficient")));
        tableMultiExpCosts->setHorizontalHeaderItem(1, new QStandardItem(QString("Total")));
        for(int j = 0; j < NV; ++j){
            tableMultiExpCosts->setHorizontalHeaderItem(j+2, new QStandardItem(QString(currentModel->getName(j).c_str())));
        }
        tableMultiExpCosts->setItem(0,0, new QStandardItem(QString("1")));          // coefficient
        tableMultiExpCosts->item(0,0)->setBackground(QBrush(QColor(Qt::lightGray)));
        for(int j = 1; j < NV + 2; ++j){
            tableMultiExpCosts->setItem(0,j, new QStandardItem(QString("")));
        }
    }
    ui->tableViewMultiExp->resizeColumnsToContents();
    ui->tableViewMultiExp->setModel(tableMultiExpCosts);

    //QObject::connect(ui->tableViewMultiExp, SIGNAL(entered(QModelIndex)), this, SLOT(coefficientsChanged(QModelIndex)));
    QObject::connect(tableMultiExpCosts, SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)), this, SLOT(coefficientsChanged(QModelIndex, QModelIndex)));

    TABLE = new QTableWidget(ui->widgetForTable);           // note : TABLE is 'currentTable'
    TABLE = new QTableWidget(currentModel->getNbParams() + currentModel->getNbVars()+1, NBCOLS, ui->widgetForTable);
    TABLE->setMinimumHeight(720);
    TABLE->setMinimumWidth(640);
    TABLE->setColumnWidth(0, 100);
    TABLE->setColumnWidth(1, 70);
    TABLE->setColumnWidth(2, 70);
    TABLE->setColumnWidth(3, 35);
    for(int i = 4; i < NBCOLS; ++i){
        TABLE->setColumnWidth(i,18);
    }
    // ui->textEditParamSet->clear();
    // ui->tableWidget->resizeColumnsToContents();
    for(int i = 0; i < Start; ++i){
        TABLE->setVerticalHeaderItem(i, new QTableWidgetItem(QString(currentModel->getParamName(i).c_str())));
        TABLE->setItem(i,0, new QTableWidgetItem(true));
        TABLE->setItem(i,1, new QTableWidgetItem(true));
        TABLE->setItem(i,2, new QTableWidgetItem(true)); // need to give item to every cell, if not, segfault if clicked ...
        TABLE->setItem(i,3, new QTableWidgetItem(true));
        QCheckBox* qcb = new QCheckBox();
        qcb->setChecked(true);
        TABLE->setCellWidget(i,3,qcb);
    }
    for(int i = 0; i < NV+1; ++i){
        for(int j = 0; j < 3; ++j){
            TABLE->setItem(Start+i,j, new QTableWidgetItem(QString("")));
            TABLE->item(Start+i,j)->setBackground(QBrush(QColor(Qt::lightGray)));
            TABLE->item(Start+i,j)->setFlags(Qt::ItemIsEnabled);
        }
    }
    for(int i = 0; i < NV; ++i){
        ///HEREHERE
        TABLE->setItem(Start + i,3, new QTableWidgetItem(true));
        TABLE->setVerticalHeaderItem(Start + i, new QTableWidgetItem(QString(currentModel->getName(i).c_str())));
        QCheckBox* qcb = new QCheckBox();
        qcb->setProperty("VarIndex", i);        // a trick to know which check box is sending signals : each check box gets an additional ID
        TABLE->setCellWidget(Start + i,3,qcb);
        // => the state of the check boxes will be updated in 'currentExperimentChanged'
        QObject::connect(qcb, SIGNAL(stateChanged(int)), this, SLOT(changeOverride(int)));
        // Another check to decide whether it will be used for the cost calculation or not.
        /*QCheckBox* qcb2 = new QCheckBox();
        qcb2->setProperty("VarIndex", i);        // a trick to know which check box is sending signals : each check box gets an additional ID
        TABLE->setCellWidget(Start + i,1,qcb2);
        QObject::connect(qcb2, SIGNAL(stateChanged(int)), this, SLOT(changeUseData(int)));*/
    }

    // A cell without widget, once clicked, returns seg fault
    for(int i = 0; i < NV + Start + 1; ++i){
        for(int j = 4; j < NBCOLS; ++j){
            TABLE->setItem(i,j, new QTableWidgetItem(QString(".")));
            TABLE->item(i,j)->setBackground(QBrush(QColor(Qt::lightGray)));
            TABLE->item(i,j)->setFlags(Qt::ItemIsEnabled);
        }
    }

    for(int i = 4; i < NBCOLS; ++i){
        QPushButton* btn = new QPushButton(QString("Use"));
        btn->setProperty("IndComb", i-4);
        QObject::connect(btn,SIGNAL(released()), this, SLOT(useComb()));
        if(i-3 > nbCombs) btn->hide();  //doesn't work, snif
        TABLE->setCellWidget(NV+Start,i,btn);
    }
    QPushButton* cre = new QPushButton(QString("Create"));
    QObject::connect(cre, SIGNAL(released()), this, SLOT(createComb()));
    TABLE->setCellWidget(NV+Start,3,cre);
    //cre->hide();
    QPushButton* rem = new QPushButton(QString("Del. Mode"));
    QObject::connect(rem, SIGNAL(released()), this, SLOT(removeCombs()));
    TABLE->setCellWidget(NV+Start,2,rem);
    //cre->hide();


    TABLE->setHorizontalHeaderItem(1, new QTableWidgetItem( QString("Low. Bound")));
    TABLE->setHorizontalHeaderItem(2, new QTableWidgetItem( QString("Up. Bound")));
    TABLE->setHorizontalHeaderItem(0, new QTableWidgetItem( QString("Param.")));
    TABLE->setHorizontalHeaderItem(3, new QTableWidgetItem( QString("Opt?")));
    for(int i = 4; i < NBCOLS; ++i){
        TABLE->setHorizontalHeaderItem(i, new QTableWidgetItem( QString::number(i-4)));
    }

    QObject::connect(TABLE, SIGNAL(cellChanged(int, int)), this, SLOT(cellChanged(int, int)));
    QObject::connect(ui->tableViewHistory, SIGNAL(doubleClicked(const QModelIndex &)), this, SLOT(paramSetDoubleClickedFromHistory(const QModelIndex &)));

    int show = ui->spinBoxDisplay->value();
    tableHistory = new QStandardItemModel(ui->spinBoxDisplay->value(), Start + 1, ui->tableViewHistory);
    for(int i = 0; i < Start+1; ++i){
        for(int j = 0; j < show; ++j){
            tableHistory->setItem(j,i, new QStandardItem(QString("")));
            //tableHistory->item(j,i)->setBackground(QBrush(QColor(Qt::lightGray)));
        }
    }


    QObject::connect(ui->pushButtonResetParams, SIGNAL(released()), this, SLOT(resetParams()));
    QObject::connect(ui->pushButtonGo, SIGNAL(released()), this, SLOT(simulate()));
    QObject::connect(ui->pushButtonSensitivity, SIGNAL(released()), this, SLOT(sensitivity()));
    QObject::connect(ui->pushButtonIdentifiability, SIGNAL(released()), this, SLOT(identifiability()));
    QObject::connect(ui->pushButtonLoadOpt, SIGNAL(released()), this, SLOT(loadOptim()));
    QObject::connect(ui->pushButtonLoadSet, SIGNAL(released()), this, SLOT(loadSet()));
    QObject::connect(ui->pushButtonSaveSet, SIGNAL(released()), this, SLOT(saveSet()));
    QObject::connect(ui->pushButtonLoadConfig, SIGNAL(released()), this, SLOT(loadConfig()));
    QObject::connect(ui->pushButtonSaveConfig, SIGNAL(released()), this, SLOT(saveConfig()));
    QObject::connect(ui->pushButtonCompare, SIGNAL(released()), this, SLOT(buttonParamSetsPushed()));
    QObject::connect(ui->pushButtonPerturb, SIGNAL(released()), this, SLOT(buttonPerturbatePushed()));
    QObject::connect(ui->pushButtonStop, SIGNAL(released()), this, SLOT(stopOptimization()));
    QObject::connect(ui->pushButtonExpandPlot, SIGNAL(released()), this, SLOT(expandPlot()));
    QObject::connect(ui->comboBoxVariable, SIGNAL(activated(int)), this, SLOT(varChanged(int)));
    QObject::connect(ui->pushButtonOptimize, SIGNAL(released()), this, SLOT(optimize()));
    QObject::connect(ui->comboBoxSubExperiment, SIGNAL(activated(int)), this, SLOT(simulate()));
    QObject::connect(ui->checkBoxAll, SIGNAL(stateChanged(int)), this, SLOT(simulate())); /// mistake! why ???
    QObject::connect(ui->checkBoxCostMultiExp, SIGNAL(stateChanged(int)), this, SLOT(simulate()));
    QObject::connect(ui->doubleSpinBoxLastParam, SIGNAL(valueChanged(double)), this, SLOT(paramChangedFromBox(double)));
    QObject::connect(ui->pushButtonRefresh, SIGNAL(released()), this, SLOT(refreshHistory()));
    QObject::connect(ui->pushButtonRefreshMacro, SIGNAL(released()), this, SLOT(refreshMacro()));
    QObject::connect(ui->pushButtonResetMacro, SIGNAL(released()), this, SLOT(resetMacro()));
    QObject::connect(ui->checkBoxRecord, SIGNAL(stateChanged(int)), this, SLOT(changeRecord(int)));
    QObject::connect(ui->pushButtonSaveHistory, SIGNAL(released()), this, SLOT(saveHistory()));
    QObject::connect(ui->pushButtonLoadHistory, SIGNAL(released()), this, SLOT(loadHistory()));
    QObject::connect(ui->pushButtonReport, SIGNAL(released()), this, SLOT(makeFigReportParamSet()));
    QObject::connect(ui->checkBoxOnlyComb, SIGNAL(stateChanged(int)), this, SLOT(showOnlyCombChecked(int)));
    QObject::connect(ui->comboBoxMultiExperiment, SIGNAL(activated(int)), this, SLOT(currentExperimentChanged()));

    ui->pushButtonReport->setStyleSheet("background-color: rgb(190, 190, 255)");
    ui->pushButtonSaveConfig->setStyleSheet("background-color: rgb(190, 190, 255)");
    ui->pushButtonLoadConfig->setStyleSheet("background-color: rgb(190, 190, 255)");
    ui->pushButtonSensitivity->setStyleSheet("background-color: rgb(190, 190, 255)");
    ui->pushButtonIdentifiability->setStyleSheet("background-color: rgb(190, 190, 255)");
    ui->pushButtonGo->setStyleSheet("background-color: rgb(190, 190, 255)");
    ui->pushButtonOptimize->setStyleSheet("background-color: rgb(190, 190, 255)");
    ui->pushButtonStop->setStyleSheet("background-color: rgb(190, 190, 255)");
    ui->pushButtonLoadHistory->setStyleSheet("background-color: rgb(190, 190, 255)");
    ui->pushButtonSaveHistory->setStyleSheet("background-color: rgb(190, 190, 255)");
    ui->pushButtonRefresh->setStyleSheet("background-color: rgb(190, 190, 255)");

    QObject::connect(ui->checkBoxLog, SIGNAL(stateChanged(int)), this, SLOT(changeLogY(int)));
    updateParmsFromModel();         // to fill the values from the model.
    currentExperimentChanged();     // to finish the set-up according to the current configuration

    /*simulate();  // why do I have to call it ???
    ui->checkBoxAll->setChecked(true);      // now, can request to simulate all !
    simulate();  // why do I have to call it ???*/

    simuWin::simulate();
}



void simuWin::coefficientsChanged(QModelIndex left, QModelIndex right){
    int row = left.row();
    int column = left.column();
    if((right.row() != row) || (right.column() != column)) std::cerr << "ERR: simuWin::coefficientsChanged, you are not supposed to change more than one cell at a time" << std::endl;
    if(currentMode != MULTI_EXPERIMENT) return;
    if((column == 0) && (row >= 0) && (row < listExperiments->nbBigExp())) {
        double paramValue = this->tableMultiExpCosts->item(row, column)->text().toDouble();
        listExperiments->setCoefficient(row, paramValue);
        std::cout << "      changing coefficient to " << paramValue << " for experiment: " << listExperiments->getExperiment(row)->Identification << std::endl;
    }
    simulate();         // does currentExperiment->init() inside
}






void simuWin::currentExperimentChanged(){

    QObject::disconnect(TABLE, SIGNAL(cellChanged(int, int)), this, SLOT(cellChanged(int, int)));

    // selects the current Experiment
    if(currentMode == MULTI_EXPERIMENT){
        int selected = ui->comboBoxMultiExperiment->currentIndex();
        currentExperiment = listExperiments->getExperiment(selected);
    }
    if(!currentExperiment) {std::cerr << "ERR::simuWin::currentExperimentChanged, the new experiment is NULL"; return;}
    int NC = currentExperiment->getNbCond();

    for(int i = 0; i < (int) currentData.size(); ++i){
        delete currentData[i];
        currentData[i] = NULL;
    }
    currentData.clear();
    // Philippe 2018:  be careful, because everything is continued to be plotted, so will look for currentData etc ...
    currentData.resize(NC, NULL);

    // Update the combo-box to chose the different conditions of the current experiment
    QObject::disconnect(ui->comboBoxSubExperiment, SIGNAL(activated(int)), this, SLOT(simulate()));
    listSubExps = new QListWidget(ui->comboBoxSubExperiment);    // the combo box for the experiments is made using ListWidgets (instead of usual combo), because they can be enabled / disabled
    listSubExps->hide();
    ui->comboBoxSubExperiment->setModel(listSubExps->model());
    std::cout << " -> New exp. selected : " << currentExperiment->Identification << std::endl; // ui->comboBoxMultiExperiment->currentText().toStdString() << std::endl;
    std::cout << "       Nb Conditions (sub-exp) : " << NC << std::endl;
    ui->comboBoxSubExperiment->clear();
    for(int i = 0; i < NC; ++i){
        listSubExps->addItem(currentExperiment->getConditionName(i).c_str());
        //if(currentExperiment->isDoable(i)){
              std::cout << "       - " << currentExperiment->getConditionName(i).c_str() << std::endl;
        //} else {
        //    QListWidgetItem *item = listSubExps->item(i);
        //    item->setFlags(item->flags() & ~Qt::ItemIsEnabled);
        //    std::cout << "       X " << currentExperiment->getNameCondition(i).c_str() << std::endl;
        //}
    }

    // Update the check boxes. They just represent the state of the table override[] of the currentExperiment.
    int NP = currentModel->getNbParams();
    int NV = currentModel->getNbVars();
    for(int i = 0; i < NV; ++i){
        QCheckBox* qcb = (QCheckBox*) TABLE->cellWidget(i+NP,3);
        QObject::disconnect(qcb, SIGNAL(stateChanged(int)), this, SLOT(changeOverride(int)));
        if(currentExperiment->canOverride(currentModel->getExternalName(i))) {
            int nbExpsOvers = 0;
            for(int j = 0; j < currentExperiment->getNbCond();++j){
                overrider* ov = currentExperiment->Overs[j];
                nbExpsOvers += (((*ov)(currentModel->getExternalName(i))) ? 1 : 0);
            }
            qcb->setEnabled(true);
            qcb->setChecked(nbExpsOvers == currentExperiment->getNbCond());
            if((nbExpsOvers > 0) && (nbExpsOvers < currentExperiment->getNbCond())){
                std::cerr << "ERR: Simuwin::currentExperimentChanged() for exp name " << currentExperiment->Identification << ", the variable " << currentModel->getName(i) << " is overriden for some conditions but not all. This is not allowed." << std::endl;
                TABLE->item(i+NP,2)->setText(QString("Partially(") + QString::number(nbExpsOvers) + QString("/") + QString(currentExperiment->getNbCond()) + QString(")"));
            }
        } else {
            TABLE->item(i+NP,2)->setText(QString("No Data ->"));
            qcb->setEnabled(false);
            qcb->setChecked(false);
        }
        QObject::connect(qcb, SIGNAL(stateChanged(int)), this, SLOT(changeOverride(int)));
    }
    QObject::connect(ui->comboBoxSubExperiment, SIGNAL(activated(int)), this, SLOT(simulate()));

    simulate();
    QObject::connect(TABLE, SIGNAL(cellChanged(int, int)), this, SLOT(cellChanged(int, int)));
}





void simuWin::updateParmsFromModel(){
    updateConfigParamsFromModel();          // inherited from manageSims
    QObject::disconnect(TABLE, SIGNAL(cellChanged(int, int)), this, SLOT(cellChanged(int, int)));
    if(currentModel){
        int NP = currentModel->getNbParams();
        int NV = currentModel->getNbVars();
        for(int i = 0; i < NP; ++i){
            //ui->textEditParamSet->append(QString::number(currentModel->getParam(i)) + QString("\t"));
            TABLE->item(i,0)->setText(QString::number(currentModel->getParam(i)));
            TABLE->item(i,1)->setText(QString::number(currentModel->getLowerBound(i)));
            TABLE->item(i,2)->setText(QString::number(currentModel->getUpperBound(i)));
        }
        ui->comboBoxVariable->clear();
        for(int i = 0; i < NV; ++i){
            ui->comboBoxVariable->addItem(QString(currentModel->getName(i).c_str()));
        }
    }
    QObject::connect(TABLE, SIGNAL(cellChanged(int, int)), this, SLOT(cellChanged(int, int)));
}


void simuWin::paramChangedFromBox(double newValue){
    std::cout << "Parameter changed from Box, new value " << newValue << std::endl;
    //QObject::disconnect(ui->doubleSpinBoxLastParam, SIGNAL(valueChanged(double)), this, SLOT(paramChangedFromBox(double)));
    if(lastParamID > -1){
        currentModel->setParam(lastParamID, newValue);
        int varSel = ui->comboBoxVariable->currentIndex();
        updateParmsFromModel();
        ui->comboBoxVariable->setCurrentIndex(varSel);
        simulate();
    }
    //QObject::connect(ui->doubleSpinBoxLastParam, SIGNAL(valueChanged(double)), this, SLOT(paramChangedFromBox(double)));
}




void simuWin::cellClicked(int row, int column){
    std::cerr << "cell clicked, ligne=" << row << ", col=" << column << ", newValue = " << TABLE->item(row, column)->text().toStdString() << std::endl;}
void simuWin::cellPressed(int row, int column){
    std::cerr << "cell clicked, ligne=" << row << ", col=" << column << ", newValue = " << TABLE->item(row, column)->text().toStdString() << std::endl;}

void simuWin::createComb(){
    QObject::disconnect(TABLE, SIGNAL(cellChanged(int, int)), this, SLOT(cellChanged(int, int)));
    if(nbCombs + 4 >= NBCOLS) return;
    nbCombs++;
    for(int i = 0; i < (int) currentConfig.size(); ++i){
        currentConfig[i].resize(nbCombs+4);
    }
    int NP = currentModel->getNbParams();
    int NV = currentModel->getNbVars();
    for(int i = 0; i < NP + NV; ++i){
        QWidget* ww = TABLE->cellWidget(i,3);
        if(ww){
            //std::cout << i << " is " << ww->metaObject()->className() << std::endl;
            if(((QCheckBox*) TABLE->cellWidget(i,3))->isChecked()){
                TABLE->item(i,3+nbCombs)->setText(QString("1"));
                currentConfig[i][nbCombs+3] = "1";
                TABLE->item(i,3+nbCombs)->setBackground(QBrush(QColor(Qt::green)));}
            else {
                TABLE->item(i,3+nbCombs)->setText(QString("0"));
                currentConfig[i][nbCombs+3] = "0";
                TABLE->item(i,3+nbCombs)->setBackground(QBrush(QColor(Qt::white)));
            }
            TABLE->item(i,3+nbCombs)->setFlags(TABLE->item(i,3+nbCombs)->flags() | Qt::ItemIsEnabled | Qt::ItemIsEditable | Qt::ItemIsSelectable );

        }
    }
    //std::cout << "Added" << std::endl;
    QObject::connect(TABLE, SIGNAL(cellChanged(int, int)), this, SLOT(cellChanged(int, int)));

}

void simuWin::removeCombs(){
    removeMode = !removeMode;
    int MaxRows = currentModel->getNbParams() + currentModel->getNbVars() + 1;
    for(int i = 4; i < NBCOLS; ++i){
        QPushButton* ww =  (QPushButton*) TABLE->cellWidget(MaxRows-1,i);
        if(ww){
            if(removeMode) ww->setText(QString("DEL"));
            else ww->setText(QString("Use"));
        }
    }
}

void simuWin::useComb(int IDComb){
    int z = (IDComb < 0) ? sender()->property("IndComb").toInt() : IDComb;
    if(recording) currentMacro << "macro" << macroID << ".motherUseComb(" << z << ")\n";
    if(!removeMode){

        if(z >= nbCombs) return;
        std::cout << "      Note : Use comb nr(0..) " << z <<  std::endl;
        int NP = currentModel->getNbParams();
        int NV = currentModel->getNbVars();
        for(int i = 0; i < NP + NV; ++i){
            int check = TABLE->item(i, 4+z)->text().toInt();
            //std::cout << check << std::endl;
            if(((QCheckBox*) TABLE->cellWidget(i,3))) ((QCheckBox*) TABLE->cellWidget(i,3))->setChecked((check > 0));
            //if((i >= NP)){
            //    currentExperiment->overrideVariable(currentModel->getExternalName(i-NP), check && currentExperiment->canOverride(currentModel->getExternalName(i-NP)));
            //}
        }
    }
    else {
        if(IDComb >= 0) std::cerr << "ERR : simuWin::useComb(int IDComb = " << IDComb << ") is not supposed to be used for deleting" << std::endl;
        if(z >= nbCombs) return;    // and ensures that nbCombs will not get negative at the end
        std::cerr << "Delete comb nr(0..) " << z <<  std::endl;
        int res = QMessageBox::question(this, QString("Confirm?"), QString("Confirm the deletion ?"), QMessageBox::Yes | QMessageBox::No);
        if(res == QMessageBox::No) return;
        QObject::disconnect(TABLE, SIGNAL(cellChanged(int, int)), this, SLOT(cellChanged(int, int)));
        int NP = currentModel->getNbParams();
        int NV = currentModel->getNbVars();
        // Move all the configs afterwards of one index on the left
        for(int k = 4 + z +1; k < 4 + nbCombs; ++k){
            for(int i = 0; i < NP + NV; ++i){
                TABLE->item(i, k-1)->setText(TABLE->item(i,k)->text());
                TABLE->item(i, k-1)->setBackgroundColor(TABLE->item(i,k)->backgroundColor());
            }
        }
        for(int i = 0; i < NP + NV; ++i){
            TABLE->item(i, 4 + nbCombs - 1)->setText(".");
            TABLE->item(i, 4 + nbCombs - 1)->setBackgroundColor(QColor(Qt::gray));
        }
        nbCombs--;
        QObject::connect(TABLE, SIGNAL(cellChanged(int, int)), this, SLOT(cellChanged(int, int)));
    }
}



void simuWin::changeOverride(int newState){
    //if(currentMode == MULTI_EXPERIMENT) {std::cerr << "ERR : change Override called in the Multi-obj mode, return.\n"; return;}
    int z = sender()->property("VarIndex").toInt();
    if(recording) currentMacro << "macro" << macroID << ".currentModel->applyOverride(macro" << macroID << ".currentModel->getExternalName(" << z << "), " << (newState > 0 ? "true" : "false") << ")\n";
    std::cout << "Change override of var " << z << " to " << newState << std::endl;
    if(currentMode != MULTI_EXPERIMENT){
        if(currentExperiment->canOverride(currentModel->getExternalName(z))){
            currentExperiment->overrideVariable(currentModel->getExternalName(z), (newState > 0));
        }
    } else {
        //////§§§§ Philippe HEREHERE
        listExperiments->overrideVariable(currentModel->getExternalName(z), (newState > 0));
    }
    simulate();
}

void simuWin::simulate(){

    int NV = currentModel->getNbVars();


    ui->doubleSpinBoxCostExp->setEnabled(ui->checkBoxAll->isChecked());
    ui->doubleSpinBoxCostVar->setEnabled(ui->checkBoxAll->isChecked());
    ui->doubleSpinBoxCostExp->setValue(0.0);
    ui->doubleSpinBoxCostVar->setValue(0.0);

    currentExperiment->init();      // to clear the evaluators, for the cost (to not keep values from the previous simulation ??)
    // keep track of the variable selectzed to display
    int varSel = ui->comboBoxVariable->currentIndex();
    // note that currentModel and currentExperiment->m are exactly the same thing (same pointer)
    ui->textBrowserStatus->clear();
    if(currentExperiment){
        // says the time step for recording a kinetics
        currentModel->setPrintMode(true, ui->doubleSpinBoxGraphDT->value());
        // gives the starting dt (it will be tuned by the solver)
        currentModel->dt = ui->doubleSpinBoxSimDT->value();
        // model initialization is done inside the function experiment->simulationsPart/simulate, no need to do it here
        int nbExp = currentExperiment->getNbCond();
        if(ui->checkBoxAll->isChecked()){
            // disables the selection of experiments
            if(ui->checkBoxDisplayCurves->isChecked()){
                ui->comboBoxSubExperiment->setDisabled(true);
                ui->progressBar->show();
                ui->progressBar->setValue(0.0);
            }
            if(!currentlyOptimizing) ui->pushButtonGo->hide(); // just to make things fast during optimization: no need to show and hide buttons  / progressbars all the time
            for(int i = 0; i < nbExp; ++i){
                // SIMULATE !!
                currentExperiment->simulate(i, NULL, true);
                if(ui->checkBoxDisplayCurves->isChecked()){
                    if(currentData[i]) {delete currentData[i]; currentData[i] = NULL;}
                    if(i > (int) currentData.size()) std::cerr << "Something happened to currentData" << std::endl;
                    currentData[i] = new TableCourse(currentExperiment->m->getCinetique());
                    if(!currentlyOptimizing) ui->progressBar->setValue((100 * (i+1)) / nbExp);
                    if(currentExperiment->m->penalities > 0){
                        ui->textBrowserStatus->append(QString("ERR : simulation diverged for ") + QString(currentExperiment->getConditionName(i).c_str()) + QString(", penality : ") + QString::number(currentExperiment->m->penalities));
                    }
                }
            }
            if(!currentlyOptimizing) {
                ui->pushButtonGo->show();
                if(ui->checkBoxDisplayCurves->isChecked()){
                    ui->progressBar->hide();
                }
            }
        } else {
            ui->comboBoxSubExperiment->setEnabled(true);
            ui->progressBar->hide();
            if(!currentlyOptimizing) ui->pushButtonGo->hide();
            currentExperiment->simulate(ui->comboBoxSubExperiment->currentIndex(), NULL, true); //dangereux le 'currentIndex' !!
            if(!currentlyOptimizing) ui->pushButtonGo->show();
            if(currentData[ui->comboBoxSubExperiment->currentIndex()]) delete currentData[ui->comboBoxSubExperiment->currentIndex()];
            currentData[ui->comboBoxSubExperiment->currentIndex()] = new TableCourse(currentExperiment->m->getCinetique());
            if(currentModel->penalities > 0){
                ui->textBrowserStatus->append(QString("ERR : simulation diverged for ") + ui->comboBoxSubExperiment->currentText() + QString(", penality : ") + QString::number(currentExperiment->m->penalities));
            }
        }
    }

    // updates the plots
    if(ui->checkBoxDisplayCurves->isChecked()) varChanged(varSel);

    QObject::disconnect(tableMultiExpCosts, SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)), this, SLOT(coefficientsChanged(QModelIndex, QModelIndex)));
    // Note : the cost has to be takken AFTER the simulation !!!
    if((currentMode == MULTI_EXPERIMENT) && (ui->checkBoxCostMultiExp->isChecked())) {
        manageSims::simulate();
        double v1 = NAN, v2 = NAN;
        v1 = listExperiments->costVariableInModel();
        v2 = listExperiments->getPenalities();
        double costToSimAll = v1 + v2;
        ui->doubleSpinBoxCostMultiExp->setEnabled(true);
        ui->doubleSpinBoxCostMultiExp->setValue(costToSimAll);

        int NE = listExperiments->nbBigExp();
        for(int i = 0; i < NE; ++i){
            for(int j = 0; j < NV; ++j){
                tableMultiExpCosts->item(i,j+2)->setText(QString::number(listExperiments->getExperiment(i)->costVariableInModel(j)));
            }
            tableMultiExpCosts->item(i,1)->setText(QString::number(listExperiments->getExperiment(i)->costExp())); // note: this is different than putting listExperiment(i)->costBigExp, which is multiplied by coefficient
            tableMultiExpCosts->item(i,0)->setText(QString::number(listExperiments->getCoefficient(i)));
        }


    } else {
        ui->doubleSpinBoxCostMultiExp->setEnabled(false);
        ui->doubleSpinBoxCostMultiExp->setValue(0.0);

        for(int j = 0; j < NV; ++j){
            tableMultiExpCosts->item(0,j+2)->setText(QString::number((double) currentExperiment->costVariableInModel(j)));
        }
        tableMultiExpCosts->item(0,1)->setText(QString::number(currentExperiment->costExp()));
        tableMultiExpCosts->item(0,0)->setText(QString("1"));

        if(currentMode == MULTI_EXPERIMENT){
            // erase the rest
            int NE = listExperiments->nbBigExp();
            for(int i = 1; i < NE; ++i){ // i = row
                for(int j = 0; j < NV; ++j){
                    tableMultiExpCosts->item(i,j+2)->setText(QString(""));
                }
                tableMultiExpCosts->item(i,1)->setText(QString(""));
                tableMultiExpCosts->item(i,0)->setText(QString(""));
            }
        }
    }
    QObject::connect(tableMultiExpCosts, SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)), this, SLOT(coefficientsChanged(QModelIndex, QModelIndex)));


    /*if(currentExperiment && (currentExperiment->m->getCinetique())){
        QString title = QString("Model: ") + ui->comboBoxModele->currentText() + QString("Model: ") + ui->comboBoxDataSet->currentText() + QString("Modele: ") + ui->comboBoxExperiment->currentText();
        currentExperiment->m->getCinetique()->save(string("C:/Users/parobert/Desktop/Optimisation/ThModeles/Modeles/SimulOutput.txt"), title.toStdString());
    }*/
    if(ui->checkBoxDisplayCurves->isChecked()){
        updateParmsFromModel(); // to update the parameters that depend on other ones upon currentModel->init()
    }
    ui->comboBoxVariable->setCurrentIndex(varSel);

}

void simuWin::varChanged(int idVar){
    //std::cerr << "var changed " << std::endl;
    if(currentExperiment){
        if(ui->checkBoxAll->isChecked()){
            if(ui->checkBoxDisplayCurves->isChecked()){
                ////§§§ to check ui->textBrowserStatus->clear();
                currentGraphe->setNbCurves(2*currentExperiment->getNbCond());
                currentGraphe->setTitle(ui->comboBoxVariable->currentText());
                for(int i = 0; i < currentExperiment->getNbCond(); ++i){
                    // currentData is the ***simulated curve from the model***
                    vector<double> Xs = currentData[i]->getTimePoints(idVar);
                    vector<double> Ys = currentData[i]->getTimeCourse(idVar);

                    //std::cout << "Data, var " << idVar << ", name " << currentModel->getName(idVar) << ", " << Xs.size() << " - " << Ys.size() << " time-points from simu" << ((Xs.size() > 0) ? Xs[0] : NAN) << " ..." << std::endl;
                    // needs to find the index of the variable
                    //std::cout << "looks for ID " << currentModel->getExternalName(j) << "\tglobalName=" << currentModel->getExternalName(j) << "\t";

                    //int nbTp = Xs.size();
                    //for(int l = 0; l < nbTp; ++l){
                    //    Xs[l] = Xs[l]; // / 3600.0;
                    //}
                    currentGraphe->Plot(2*i, Ys, Xs, QString(currentExperiment->getConditionName(i).c_str()), currentGraphe->baseList(i));

                    // Now plots the experimental data: std::cerr << currentGraphe->nbCurves << " Curves and nbexp" << currentExperiment->nbCond() << std::endl;
                    int S = currentExperiment->ExpData[i].size();
                    int S2 = currentExperiment->ExpStdDevs[i].size();
                    vector<double> Ys2;
                    vector<double> Yerrs2;
                    vector<double> Xs2;
                    for(int j = 0; j < min(S,S2); ++j){
                        if(currentExperiment->ExpData[i][j]){
                            int k = currentExperiment->ExpData[i][j]->findPosition(currentModel->getExternalName(idVar));
                            if(k >= 0){         // note: maybe should return an error if k < 0, but it naturally happens when there is no data for this variable
                                if(Xs2.size() > 0) std::cerr << "ERR: the same curve is defined in two different datasets. Experiment nr " << j << ", variable " << i << "(" << currentModel->getName(i) << "), total " << S << " datasets defined..." << std::endl;
                                Xs2 = currentExperiment->ExpData[i][j]->getTimePoints(k);
                                Ys2 = currentExperiment->ExpData[i][j]->getTimeCourse(k);
                                if (currentExperiment->ExpStdDevs[i][j]) Yerrs2 = currentExperiment->ExpStdDevs[i][j]->getTimeCourse(k);
                            }
                            //ui->textBrowserStatus->append();
                            if(((int) Xs2.size() != (int) Ys2.size())) std::cerr << "Problems reading exp kinetics, size Xs" << Xs2.size() << ", Ys " << Ys2.size() << "\n";
                                //std::cout << "Data for Exp: " << currentExperiment->getNameCondition(i) << ", variable " << currentModel->getExternalName(j) << std::endl;
                                //for(int l = 0; l < (int) Xs2.size();++l){ std::cout << "x=" << Xs2[l] << ", y=" << Ys2[l] << std::endl;}
                            // in case resize in the X axis
                            /*int nbTp2 = Xs2.size();
                            for(int l = 0; l < nbTp2; ++l){
                                Xs2[l] = Xs2[l]; // / 3600.0;
                            }*/
                            //std::cout << "Experiment " << i << ", " << Xs2.size() << " experimental points added to the curve" << std::endl;
                        }
                    }
                    currentGraphe->Plot(2*i+1, Ys2, Yerrs2, Xs2, QString("") /*QString("Data ") + QString(currentExperiment->expName(i).c_str()) */, currentGraphe->baseList(i), Qt::DotLine, QCPScatterStyle::ssCircle);

                    if(S == 0)currentGraphe->Plot(2*i+1, vector<double>(), vector<double>(), QString(""));
                    //std::cout << "Finished" << std::endl;
                }
            }
            //std::cout << std::endl;
            double costExp = currentExperiment->costVariableInModel();
            ui->doubleSpinBoxCostExp->setValue(costExp);

            // only display variable cost if there is data for it
            double costVar = /*currentExperiment->canOverride(currentModel->getExternalName(j)) ? */ currentExperiment->costVariableInModel(idVar); // : 0;
            ui->doubleSpinBoxCostVar->setValue(costVar);
            ui->labelCostVar->setText(ui->comboBoxVariable->currentText());
        } else { // If 'simulate all' not checked, then only show the current simulation/condition
            if(ui->checkBoxDisplayCurves->isChecked()){
                currentGraphe->setNbCurves(1);
                currentGraphe->Plot(0, currentExperiment->m->getCinetique().getTimeCourse(idVar), currentExperiment->m->getCinetique().getTimePoints(idVar), QString(""), currentGraphe->baseList(ui->comboBoxSubExperiment->currentIndex()));
            }
        }
    }
}


void simuWin::cellChanged(int row, int column){
    //if(currentMode == MULTI_EXPERIMENT) {std::cerr << "ERR : cellChanged called in the Multi-obj mode, return."; return;}

    //std::cerr << "cell changed, ligne=" << row << ", col=" << column << ", newValue = " << TABLE->item(row, column)->text().toStdString() << std::endl;
    QObject::disconnect(ui->doubleSpinBoxLastParam, SIGNAL(valueChanged(double)), this, SLOT(paramChangedFromBox(double)));
    if((column == 0) && (row < currentModel->getNbParams())) {
        double paramValue = TABLE->item(row, column)->text().toDouble();
        currentExperiment->m->setParam(row, paramValue);
        ui->doubleSpinBoxLastParam->setValue(paramValue);
        ui->labelLastParam->setText(QString(currentExperiment->m->getParamName(row).c_str()));
        ui->doubleSpinBoxLastParam->setSingleStep(paramValue / 10.0);
        lastParamID = row;
    }
    if((column == 1) && (row < currentModel->getNbParams())) {
        double paramValue = TABLE->item(row, column)->text().toDouble();
        currentExperiment->m->setBounds(row, paramValue, currentExperiment->m->getUpperBound(row));
    }
    if((column == 2) && (row < currentModel->getNbParams())) {
        double paramValue = TABLE->item(row, column)->text().toDouble();
        currentExperiment->m->setBounds(row, currentExperiment->m->getLowerBound(row), paramValue);
    }
    currentExperiment->m->initialise();

    simulate();         // does currentExperiment->init() inside
    QObject::connect(ui->doubleSpinBoxLastParam, SIGNAL(valueChanged(double)), this, SLOT(paramChangedFromBox(double)));
}

void simuWin::paramSetDoubleClickedFromHistory(const QModelIndex & QMI){
    int row = QMI.row();
    // not allowed in optimize mode
    //if(!stopOpt){QMessageBox::information(this, QString("Error"), QString("You are not allowed to simulate a new parameter set while an optimization is running")); return;}
    int indexComb = -1;
    if(ui->checkBoxLinkToCombs->isChecked()) indexComb = QInputDialog::getInt(this, QString("Choose Comb:"), QString("You want to apply the clicked parameter set to according to a combination. Please give the associated combination index (starts at 0) ?"), 0, -1 /* min */, nbCombs - 1, 1 /* step */);
    if(indexComb >= 0) std::cout << "Overriding only parameters from combination nr :" << indexComb << std::endl;
    //if(indexComb >= 0) ui->tableViewHistory->setHorizontalHeader();
    useParamSetFromHistory(row, indexComb);
    updateParmsFromModel();

    simulate();         // does currentExperiment->init() inside
}

void simuWin::expandPlot(){

    static bool expanded = true;
    ui->groupBoxHistory->setHidden(expanded);
    ui->tabWidgetRight->setHidden(expanded);
    ui->groupBoxOptim->setHidden(expanded);
    ui->textBrowserStatus->setHidden(expanded);
    ui->pushButtonExpandPlot->setText((expanded) ? QString("Small") : QString("Big"));
    if(expanded){
        //for(int i = 0; i < (int) currentGraphes.size();++i){
        //    currentGraphes[i] -> logarithmic(true);
        //}
        ui->groupBoxPlot->resize(1000,700);
        ui->widgetGraphe->resize(980, 670);
        currentGraphe->resize(980, 670);
        currentGraphe->bigPlot->resize(980, 670);
    } else {
        //for(int i = 0; i < (int) currentGraphes.size();++i){
        //    currentGraphes[i] -> logarithmic(false);
        //}
        ui->groupBoxPlot->resize(611,431);
        ui->widgetGraphe->resize(591, 361);
        currentGraphe->resize(591, 361);
        currentGraphe->bigPlot->resize(591, 361);
        ui->textBrowserStatus->show();
    }
    expanded = !expanded;
}





void simuWin::optimize(){
    #ifdef ALLOW_OPTIMIZE
    stopOpt = false;
    currentlyOptimizing = true;
    ui->pushButtonOptimize->setEnabled(false);
    nbCostCalls = 0;
    if(ui->lineEditWorkingFolder->text().size() == 0)
        ui->lineEditWorkingFolder->setText(QFileDialog::getExistingDirectory(this, tr("Open Directory"), "",QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks));
    string optText = createOptimizerFile();
    if(ui->lineEditWorkingFolder->text().size() == 0) {std::cerr << "No Directory\n"; return;}
    string optFileName = (ui->lineEditWorkingFolder->text() + QString("Opt.txt")).toStdString();

//double costVar = currentExperiment->costPart(currentModel->getExternalName(j));

    std::ofstream fichier((const char*) optFileName.c_str(), std::ios::out);
    if(fichier){
        fichier << optText << "\n0\n" << std::endl;
        fichier.close();}
    else {QMessageBox::information(this, QString("Error"), QString("The optimizer file could not be written in the provided file location : ") + (ui->lineEditWorkingFolder->text()));
        return;}

    if(recording) {
        currentMacro << "string optTxt = string(\"" << optText << "\");\n";
        currentMacro << "macro" << macroID << ".motherOptimize(optTxt, 50)\n";
    }
    history.resize(0);

    history.clear();
    costRecords.clear();
    refreshHistory();

    ui->pushButtonGo->hide();
    ui->progressBar->hide();

    myRandom::Randomize();
            myTimes::getTime();
            ui->checkBoxAll->setChecked(true);
            GeneralImplementation::initialize();
            BaseOptimizationProblem *E = this; //new simuWin(currentExperiment, this);
            BaseOptimizer *Opt = BaseOptimizer::createOptimizer(E, optFileName);
                //mySignal::addOptimizer(Opt);
                Opt->optimize();
                Opt->bestGlobal.print();
                //delete E; // program destructor first...
                delete Opt;
                std::cout << "Optimization Complete\n";

    #else
    QMessageBox::information(this, QString("Error"), QString("ERR : SimuWin::optimize(), function not available, you should do #define ALLOW_OPTIMIZATION in common.h and compile again ! \n"));
    std::cerr << "ERR : SimuWin::optimize(), function not available, you should do #define ALLOW_OPTIMIZATION\n";
    #endif
    stopOpt = true;
    currentlyOptimizing = false;
    ui->pushButtonOptimize->setEnabled(true);
    ui->pushButtonGo->show();
    ui->progressBar->show();
}


#ifdef ALLOW_OPTIMIZE
double simuWin::getCost(){
    nbCostCalls++;
    if((stopOpt == true) && (currentlyOptimizing)) {               // to stop the optimization, replace a simulation by a huge value ...
        if((nbCostCalls % 100000) == 0) QCoreApplication::processEvents();
        return 1e15;
    }
    if((nbCostCalls % 50) == 1) {       // plots the evolution of costs every 50 simulations
        costGraphe->Plot(MINS, costRecords.mins, costRecords.Xs, QString("Min"), costGraphe->baseList(MINS));
        costGraphe->Plot(MAXS, costRecords.maxs, costRecords.Xs, QString("Max"), costGraphe->baseList(MAXS));
        costGraphe->Plot(MEANS, costRecords.means, costRecords.Xs, QString("Average"), costGraphe->baseList(MEANS));
        costGraphe->Plot(STDDEVS, costRecords.stddevs, costRecords.Xs, QString("Variances"), costGraphe->baseList(STDDEVS));
    }
    if((nbCostCalls % 10) == 0){        // displays the number of simulations
        ui->lcdNumberCostCall->display(nbCostCalls);
    }
    if((nbCostCalls % 15) == 0) {       // refreshes the interface regularly to avoid freezing during all the optimization
        QCoreApplication::processEvents();
    }
    if((nbCostCalls % 100) == 0) {       // refreshes the interface regularly to avoid freezing during all the optimization
        refreshHistory();
    }

    //if(dimension > currentModel->getNbParams) {std::cerr << "Optimizer has more parameters than model\n"; return -1;}

    // applies the values from the optimizer (stored in parameters[i]) into the model

        int NPs =  currentModel->getNbParams();
        for(int i = 0; i < NPs; ++i){
            if(!std::isnan(parameters[i])) currentModel->setParam(i, parameters[i]);
        }


    // simulates ... (calling currentExperiment->simulate)

    simulate();             // does currentExperiment->init() inside
    double v1 = NAN, v2 = NAN;
    if(currentMode != MULTI_EXPERIMENT){
        v1 = currentExperiment->costVariableInModel();
        v2 = currentExperiment->getPenalities();         // penalty in case of divergence
    } else {
        v1 = listExperiments->costVariableInModel();
        v2 = listExperiments->getPenalities();
    }
    // stores the parameter set with its cost in the history
    vector<double> set = currentModel->getParameters();
    history.addSet(&set, v1+v2);
    costRecords.newValue(v1+v2);

    return v1 + v2;
}
#else
double simuWin::getCost(){
    std::cerr << "ERR : SimuWin::getCost(), function not available, you should do #define ALLOW_OPTIMIZATION\n";
    return 0;
}
#endif

void simuWin::stopOptimization(){
    stopOpt = true;
    //currentlyOptimizing = false; very important
    ui->pushButtonGo->show();
    ui->progressBar->show();
    //ui->pushButtonOptimize->setEnabled(true); // will happel automatically I guess
    ui->checkBoxDisplayCurves->setChecked(true);
    this->useParamSetFromHistory(0);
    simulate();             // does currentExperiment->init() inside
    this->refreshHistory();
    //updateParmsFromModel();
    //history.print();
}

void simuWin::refreshHistory(){
    history.MaxNb = ui->spinBoxStore->value();
    if((int) history.store.size() > history.MaxNb) history.resize(history.MaxNb); // need to create a function setMaxNb or so

    int NP = currentModel->getNbParams();
    int show = ui->spinBoxDisplay->value();
    if(tableHistory->rowCount() != show){
        std::cout << "Re-sizing history table \n";
        tableHistory->clear();
        tableHistory = new QStandardItemModel(show, NP + 1, ui->tableViewHistory);
        for(int i = 0; i < NP+1; ++i){
            for(int j = 0; j < show; ++j){
                tableHistory->setItem(j,i, new QStandardItem(QString("")));
                //tableHistory->item(j,i)->setBackground(QBrush(QColor(Qt::lightGray)));
            }
        }
        // should I delete all the previous items ?
    }

    ui->tableViewHistory->setColumnWidth(0, 80);
    tableHistory->setHorizontalHeaderItem(0, new QStandardItem(QString("Cost")));
    for(int i = 0; i < currentModel->getNbParams(); ++i){
        //ui->textEditParamSet->append(QString::number(currentModel->getParam(i)) + QString("\t"));
        tableHistory->setHorizontalHeaderItem(i+1, new QStandardItem(QString(currentModel->getParamName(i).c_str())));
    }
    vector<oneSet*> liste = history.toVector();
    //std::cerr << "Size of history : " << history.toVector().size() << std::endl;
    //reverse(liste.begin(), liste.end());
    int ls = liste.size();
    for(int i = 0; (i < ls) && (i < show); ++i){
        tableHistory->item(i,0)->setText(QString::number(liste[i]->cost));
        int s = liste[i]->v.size();
        if(s != NP) std::cerr << "ERR : refresh History incorrect size for parameters\n";
        for(int j = 0; j < NP; ++j){
            tableHistory->item(i, j+1)->setText(QString::number(liste[i]->v[j]));
        }
    }
    for(int i = ls; i < show; ++i){
        tableHistory->item(i,0)->setText(QString(""));
        for(int j = 0; j < NP; ++j){
            tableHistory->item(i, j+1)->setText(QString(""));
        }
    }
    ui->tableViewHistory->setModel(tableHistory);
}

void simuWin::saveHistory(QString _name){
    if(!_name.compare(QString(""))){
         _name = QFileDialog::getSaveFileName(this, QString(""), ui->lineEditWorkingFolder->text());
    }
    if(recording) {currentMacro << "macro" << macroID << ".saveHistory(" << _name.toStdString() << ")\n";}
    int NP = currentModel->getNbParams();

    vector<oneSet*> liste = history.toVector();
    //reverse(liste.begin(), liste.end());
    int ls = liste.size();

    int store = ls; //  ui->spinBoxStore->value();
    std::cout << "      ... Writing into file " << _name.toStdString() << std::endl;
    std::ofstream f(_name.toStdString().c_str(), std::ios::out);
    if(!f) {QMessageBox::information(this, QString("Error"), QString("File not Found")); return;}
    f << NP << "\t";
    f << store << "\t";


    for(int i = 0; (i < ls) && (i < store); ++i){
        f << liste[i]->cost;
        int s = liste[i]->v.size();
        if(s != NP) std::cerr << "ERR : save History incorrect size for parameters\n";
        for(int j = 0; j < NP; ++j){
            f << "\t" << liste[i]->v[j];
        }
        f << "\n";
    }
    f.close();
}

void simuWin::loadHistory(QString _name){
    if(!_name.compare(QString(""))){
         _name = QFileDialog::getOpenFileName(this, QString(""), ui->lineEditWorkingFolder->text());
    }
    if(recording) {currentMacro << "macro" << macroID << ".loadHistory(" << _name.toStdString() << ")\n";}
    manageSims::loadHistory(_name.toStdString());

    refreshHistory();
}



//#ifdef ALLOW_OPTIMIZE
string simuWin::createOptimizerFile(){
    // generates the text file for the optimizer and the text file for
    std::stringstream f;
    f << optChoice->generate();
    f << "\n";
    int NV = currentModel->getNbParams();
    int nbToOpt = 0;
    for(int i = 0; i < NV; ++i){
        if(((QCheckBox*) TABLE->cellWidget(i,3))->isChecked()) nbToOpt++;
    }
    f << nbToOpt << "\n";
    if(nbToOpt == 0){
        QMessageBox::information(this, QString("Error"), QString("No parameter selected for optimization -> 0 parameter to optimize !!"));
    }
    for(int i = 0; i < NV; ++i){
        if(! ((QCheckBox*) TABLE->cellWidget(i,3))->isChecked()) f << "#";
        f << "\t" << i << "\t";
        f << currentModel->getLowerBound(i) << "\t" << currentModel->getUpperBound(i) << "\t#" << currentModel->getParamName(i) << std::endl;
    }
    f << "\n\n0\nExponential\n0\n";
    ui->plainTextEditOptFile->setPlainText(QString(f.str().c_str()));
    return f.str();
}

//#endif

// nOte : by calling the loadConfig function of hte mother class, the model is updated according the config's parameters, be careful !
string simuWin::loadConfig(string _name){
    ////////int erase = QMessageBox::question(this, QString("Erase"), QString("This will erase all the table, do you confirm ?"), QMessageBox::Yes|QMessageBox::No);
    //////if(erase != QMessageBox::Yes) return string("Loading cancelled.");
    if(!_name.compare("")){_name = QFileDialog::getOpenFileName(this, QString(""), ui->lineEditWorkingFolder->text()).toStdString();}
    //QFile file(_name);
    //file.open(QFile::ReadOnly | QFile::Text);
    //QTextStream ReadFile(&file);
    //ui->textEditOptimizerFile->setText(ReadFile.readAll());

    string raisedErrors = manageSims::loadConfig(_name);

    if(raisedErrors.size() > 0) {
         std::cout<< "\n Raised errors while loading config: \n"<< raisedErrors <<std::endl;
         QMessageBox::information(this, QString("Error"), QString("Problems with file format :\n") + QString(raisedErrors.c_str()));
         return raisedErrors;
    }
    int NP = currentModel->getNbParams();
    int NV = currentModel->getNbVars();
    int NC = nbCombs;

    QObject::disconnect(TABLE, SIGNAL(cellChanged(int, int)), this, SLOT(cellChanged(int, int)));
    for(int i = 0; i < NP + NV; ++i){
        for(int j = 0; j < NC + 4; ++j){
            if(((i < NP) || (j > 2)) && (j != 3))
                TABLE->item(i,j)->setText(QString(currentConfig[i][j].c_str()));
            if((j > 3)){
                if(!currentConfig[i][j].compare("1"))
                    TABLE->item(i,j)->setBackground(QBrush(QColor(Qt::green)));
                else if(!currentConfig[i][j].compare("."))
                    TABLE->item(i,j)->setBackground(QBrush(QColor(Qt::lightGray)));
                else
                    TABLE->item(i,j)->setBackground(QBrush(QColor(Qt::white)));
            }
        }
    }
    if(NC < nbCombs){
        for(int i = 0; i < NP + NV; ++i){
            for(int j = 4+NC; j < 4+nbCombs;++j){
                 TABLE->item(i,j)->setBackground(QBrush(QColor(Qt::gray)));
                 TABLE->item(i,j)->setText(QString(""));
            }
        }
    }
    QObject::connect(TABLE, SIGNAL(cellChanged(int, int)), this, SLOT(cellChanged(int, int)));
    return string("");
}


// why did I remove saveConfig from manageSims ???????
void simuWin::saveConfig(string _name){
    if(!_name.compare("")){
         _name = QFileDialog::getSaveFileName(this, QString(""), ui->lineEditWorkingFolder->text()).toStdString();
    }
    //QFile file(_name);
    //file.open(QFile::ReadOnly | QFile::Text);
    //QTextStream ReadFile(&file);
    //ui->textEditOptimizerFile->setText(ReadFile.readAll());

    int NP = currentModel->getNbParams();
    int NV = currentModel->getNbVars();
    std::cout << "      ... Writing into file " << _name << std::endl;
    std::ofstream f(_name.c_str(), std::ios::out);
    if(!f) {QMessageBox::information(this, QString("Error"), QString("File not Found")); return;}
    f << NP << "\t";
    f << NV << "\t";
    f << nbCombs << "\n";
    for(int i = 0; i < NP + NV; ++i){
        for(int j = 0; j < nbCombs + 4; ++j){
            if(((i < NP) || (j > 2)) && (j != 3))
                f << TABLE->item(i,j)->text().toStdString();    // to avoid to save the "NoData" or any comments in the grey left bottom area
            else f << ".";
            if(j < nbCombs + 3) f << "\t";
        }
        f << "\n";
    }
    f.close();
}

void simuWin::refreshMacro(){
    ui->textBrowserMacro->setPlainText(QString(currentMacro.str().c_str()));
}
void simuWin::resetMacro(){
    startMacro(string("modeleMinNoIL10"));
    ui->textBrowserMacro->setPlainText(QString(currentMacro.str().c_str()));
}
void simuWin::changeRecord(int z){
    recording = (z > 0);
}

void simuWin::costReport(){
    if(currentMode == MULTI_EXPERIMENT) {std::cerr << "ERR : cost Report called in the Multi-obj mode, return."; return;}

    std::cout << "Comparison between experiment and simulation" << std::endl;
    currentExperiment->costReport();
}

/*
string textFileForFolder(string explanations){
    replace( explanations.begin(), explanations.end(), '_', '-');
    static int count = 0;
    string picOpt = string("height=1.4in");
    std::stringstream st;
    st << "\\documentclass[10pt,a4paper,final]{article}\n";
    st << "\\usepackage[utf8]{inputenc}\n";
    st << "\\usepackage{amsmath}\n";
    st << "\\usepackage{amsfonts}\n";
    st << "\\usepackage{amssymb}\n";
    st << "\\usepackage{graphicx}\n";
    st << "\\usepackage{caption}\n";
    st << "\\usepackage{subcaption}\n";
    //st << "\\usepackage[dvips]{epsfig, graphicx, color}\n";
    st << "\\usepackage[left=1.5cm,right=1.5cm,top=1.5cm,bottom=1.5cm]{geometry}\n";
    //st << "\\title{How to simulate a Germinal Centre}\n";
    //st << "\\date{\vspace{-5ex}}\n";
    //st << "\\usepackage[charter]{mathdesign}\n"; // not installed in brics
    st << "\\begin{document}\n";
    st << "\\setcounter{figure}{" << count << "}\n";

    //st << explanations << std::endl;*/
    /*st << "\\begin{figure}[]\n";
    st << "\\begin{center}\n";
    st << "\\begin{subfigure}[b]{0.45\\textwidth}\n";
    st << "\\includegraphics[" << picOpt << "]{Unsim-TBET.png}\n";
    st << "\\end{subfigure}\n";
    st << "\\begin{subfigure}[b]{0.45\\textwidth}\n";
    st << "\\includegraphics[" << picOpt << "]{Unsim-TBETmRNA.png}\n";
    st << "\\end{subfigure}\n";
    st << "\\begin{subfigure}[b]{0.45\\textwidth}\n";
    st << "\\includegraphics[" << picOpt << "]{Unsim-GATA3.png}\n";
    st << "\\end{subfigure}\n";
    st << "\\begin{subfigure}[b]{0.45\\textwidth}\n";
    st << "\\includegraphics[" << picOpt << "]{Unsim-GATA3mRNA.png}\n";
    st << "\\end{subfigure}\n";
    st << "\\begin{subfigure}[b]{0.45\\textwidth}\n";
    st << "\\includegraphics[" << picOpt << "]{Unsim-FOXP3.png}\n";
    st << "\\end{subfigure}\n";
    st << "\\begin{subfigure}[b]{0.45\\textwidth}\n";
    st << "\\includegraphics[" << picOpt << "]{Unsim-FOXP3mRNA.png}\n";
    st << "\\end{subfigure}\n";
    st << "\\begin{subfigure}[b]{0.45\\textwidth}\n";
    st << "\\includegraphics[" << picOpt << "]{Unsim-RORGT.png}\n";
    st << "\\end{subfigure}\n";
    st << "\\begin{subfigure}[b]{0.45\\textwidth}\n";
    st << "\\includegraphics[" << picOpt << "]{Unsim-RORGTmRNA.png}\n";
    st << "\\end{subfigure}\n";
    st << "\\caption[]{}\n";
    st << "\\end{center}\n";
    st << "\\end{figure}\n";

    st << "\\begin{figure}[ht!]\n";
    //st << "\\captionsetup{labelformat=empty}\n";
    st << "\\caption{" << explanations << "}\n";
    st << "\\begin{center}\n";
    st << "\\includegraphics[" << picOpt << "]{Unsim-TBET.png}\n";
    st << "\\includegraphics[" << picOpt << "]{Unsim-GATA3.png}\n";
    st << "\\includegraphics[" << picOpt << "]{Unsim-RORGT.png}\n";
    st << "\\includegraphics[" << picOpt << "]{Unsim-TBETmRNA.png}\n";
    st << "\\includegraphics[" << picOpt << "]{Unsim-GATA3mRNA.png}\n";
    st << "\\includegraphics[" << picOpt << "]{Unsim-RORGTmRNA.png}\n";
    st << "\\includegraphics[" << picOpt << "]{Unsim-FOXP3.png}\n";
    st << "\\includegraphics[" << picOpt << "]{Unsim-IFNG.png}\n";
    st << "\\includegraphics[" << picOpt << "]{Unsim-IL4.png}\n";
    st << "\\includegraphics[" << picOpt << "]{Unsim-FOXP3mRNA.png}\n";
    st << "\\includegraphics[" << picOpt << "]{Unsim-IFNGmRNA.png}\n";
    st << "\\includegraphics[" << picOpt << "]{Unsim-IL4mRNA.png}\n";
    st << "\\includegraphics[" << picOpt << "]{Unsim-IL21.png}\n";
    st << "\\includegraphics[" << picOpt << "]{Unsim-IL17.png}\n";
    st << "\\includegraphics[" << picOpt << "]{Unsim-TGFB.png}\n";
    st << "\\includegraphics[" << picOpt << "]{Unsim-IL21mRNA.png}\n";
    st << "\\includegraphics[" << picOpt << "]{Unsim-IL17mRNA.png}\n";
    st << "\\includegraphics[" << picOpt << "]{Unsim-TGFBmRNA.png}\n";
    st << "\\includegraphics[" << picOpt << "]{Unsim-IL12.png}\n";
    //st << "\\includegraphics[" << picOpt << "]{Unsim-IL6.png}\n";
    st << "\\includegraphics[" << picOpt << "]{Unsim-IL2mRNA.png}\n";
    st << "\\includegraphics[" << picOpt << "]{Unsim-IL2.png}\n";
    st << "\\end{center}\n";
    st << "\\end{figure}\n";
    st << "\\clearpage\n";


    st << "\\end{document}\n";
    count++;
    return st.str();
}
*/



// problem : this config is created from nothing, so it takes the current parameter values from the model
vector<string> simuWin::makeFigReportParamSet(string _folder, string explanations){
    //std::cerr << "WRN : simuWin::makeFigReportParamSet(), not too sure about this function" << std::endl;
    if(_folder.size() == 0) _folder = (QFileDialog::getExistingDirectory(this, tr("Open Directory (Create it yourself if necessary)"), ui->lineEditWorkingFolder->text(),QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks)).toStdString() + string("/");
    replace( explanations.begin(), explanations.end(), '_', '-');

    ui->checkBoxAll->setChecked(true);
    // creates combination, uses it and destroys it !
    createComb();
    saveConfig(_folder + string("ConfigPlusCurrent.txt"));

    vector<string> res;
    res.push_back(_folder);
    {       

        // Latex preface for a PDF report
        string picOpt = string("height=1.4in");
        std::stringstream st;
        st << "\\documentclass[10pt,a4paper,final]{article}\n";
        st << "\\usepackage[utf8]{inputenc}\n";
        st << "\\usepackage{amsmath}\n";
        st << "\\usepackage{amsfonts}\n";
        st << "\\usepackage{amssymb}\n";
        st << "\\usepackage{graphicx}\n";
        st << "\\usepackage{caption}\n";
        st << "\\usepackage{subcaption}\n";
        st << "%%% DO NOT PUT dvips, it screws PDF figures !!!\\usepackage[dvips]{epsfig, graphicx, color}\n";
        st << "\\usepackage[left=1.5cm,right=1.5cm,top=1.5cm,bottom=1.5cm]{geometry}\n";
        st << "\\begin{document}\n";
        //st << "\\setcounter{figure}{" << count << "}\n";
        st << explanations << std::endl;

        useComb(nbCombs-1); // starts at 0
        //loadConfig(_folder + string("ConfigPlusCurrent.txt"));
        string res = makeTextReportParamSet(_folder, nbCombs-1, ui->doubleSpinBoxSimDT->value(), ui->doubleSpinBoxGraphDT->value());
        std::ofstream f1((_folder + string("SimResult.txt")).c_str(), std::ios::out);
        std::cout << "      ... writing in " << _folder + string("SimResult.txt") << std::endl;
        if(f1) {f1 << res; f1.close();}

        st << "\\input{" << _folder << "texReport.tex}\n";
        st << "\\section{Curves}\n";


        int NV = currentModel->getNbVars();
        //int NP = currentModel->getNbParams();
        // removes the last combination
        /*for(int i = 0; i < NP + NV; ++i){
            TABLE->item(i, 4 + nbCombs - 1)->setText(".");
            TABLE->item(i, 4 + nbCombs - 1)->setBackgroundColor(QColor(Qt::gray));
        }
        nbCombs--;
        currentConfig.resize(nbCombs); // might leave/leak a non deleted vector*/

        //simulate(); is already done by makeTextReportParamSet

        std::cout << "      ... Saving plots in " << _folder << std::endl;
        for(int i = 0; i < NV; ++i){
                ui->comboBoxVariable->setCurrentIndex(i);
                varChanged(i);// and on top have the good title !
                string add = string("Unsim-"); ////// DOES NOT WORK !!! string(((TABLE->cellWidget(NP+i,3)) && (!((QCheckBox*) TABLE->cellWidget(NP+i,3))->isChecked())) ? "Sim-" : "Unsim-" );
                QString outFile = QString((_folder + add + currentModel->getName(i) + ".png").c_str());
                //std::cout << "Var " << i << ", Figure saved in " << outFile.toStdString() << std::endl;
                //currentGraphe->bigPlot

                currentGraphe->exportToPng(outFile);
                QString outFilePDF = QString((_folder + add + currentModel->getName(i) + ".pdf").c_str());
                currentGraphe->exportToPDF(outFilePDF, ui->widgetGraphe->width(), ui->widgetGraphe->height());

                st << "\\begin{subfigure}[b]{0.33\\textwidth}\n";
                st << "\\includegraphics[" << picOpt << "]{" << outFilePDF.toStdString() << "}\n";
                st << "\\end{subfigure}\n";

            //}
        }
        st << "\\caption[]{}\n";
        st << "\\end{center}\n";
        st << "\\end{figure}\n";
        st << "\\clearpage\n";
        st << "\\end{document}\n";
        std::ofstream ftex(_folder + string("SimResult.tex"));
        ftex << st.str() << std::endl;
        ftex.close();
        compileLatex(_folder, _folder + string("SimResult.tex"));
    }
    if(currentMode == MULTI_EXPERIMENT){
        for(int i = 0; i < listExperiments->nbBigExp(); ++i){
            ui->comboBoxMultiExperiment->setCurrentIndex(i);
            currentExperimentChanged();
            //currentExperiment = listExperiments->getExperiment(i); // is done inside currentExperimentChanged
            useComb(nbCombs-1); // starts at 0
            //loadConfig(_folder + string("ConfigPlusCurrent.txt"));
            string subFolder = _folder + string("ForExp") + QString::number(i).toStdString() + listExperiments->getExperiment(i)->Identification + string("/");
            createFolder(subFolder);
            res.push_back(subFolder);
            string res = makeTextReportParamSet(subFolder, nbCombs-1, ui->doubleSpinBoxSimDT->value(), ui->doubleSpinBoxGraphDT->value());
            std::ofstream f1((subFolder + string("SimResult.txt")).c_str(), std::ios::out);
            std::cout << "      ... writing in " << subFolder + string("SimResult.txt") << std::endl;
            if(f1) {f1 << res; f1.close();}

            int NV = currentModel->getNbVars();
            //int NP = currentModel->getNbParams();
            // removes the last combination
            /*for(int i = 0; i < NP + NV; ++i){
                TABLE->item(i, 4 + nbCombs - 1)->setText(".");
                TABLE->item(i, 4 + nbCombs - 1)->setBackgroundColor(QColor(Qt::gray));
            }
            nbCombs--;
            currentConfig.resize(nbCombs); // might leave/leak a non deleted vector*/

            //simulate(); is already done by makeTextReportParamSet

            std::cout << "      ... Saving plots in " << subFolder << std::endl;
            for(int i = 0; i < NV; ++i){
                    ui->comboBoxVariable->setCurrentIndex(i);
                    varChanged(i);// and on top have the good title !
                    string add = string("Unsim-"); ////// DOES NOT WORK !!! string(((TABLE->cellWidget(NP+i,3)) && (!((QCheckBox*) TABLE->cellWidget(NP+i,3))->isChecked())) ? "Sim-" : "Unsim-" );
                    QString outFile = QString((subFolder + add + currentModel->getName(i) + ".png").c_str());
                    //std::cout << "Var " << i << ", Figure saved in " << outFile.toStdString() << std::endl;
                    //currentGraphe->bigPlot
                    currentGraphe->exportToPng(outFile);

                    QString outFilePDF = QString((subFolder + add + currentModel->getName(i) + ".pdf").c_str());
                    currentGraphe->exportToPDF(outFilePDF, ui->widgetGraphe->width(), ui->widgetGraphe->height());


                //}
            }

        }


    }
    return res;

}

void simuWin::setColorScale(int newScale){
    //if(nbGraphes == 0) std::cerr << "WRN: simuWin::setColorScale(), no graph yet to " << std::endl;
    //for(int i = 0; i < this->nbGraphes; ++i){
        if(!currentGraphe) {std::cerr << "ERR: simuWin::setColorScale(), graphes not initialized yet " << std::endl; return;}
        currentGraphe->setColorScale(newScale);
    //}
}














void simuWin::loadOptim(string _name){
     if(!_name.compare("")){
             _name = QFileDialog::getOpenFileName(this).toStdString();
     }
     QFile file(_name.c_str());
     file.open(QFile::ReadOnly | QFile::Text);

     QTextStream ReadFile(&file);
     //ui->textEditOptimizerFile->setText(ReadFile.readAll());

     std::cout << "      ... Reading file " << _name << std::endl;
     std::ifstream fichier(_name.c_str(), std::ios::in);
     if(!fichier) std::cerr << "file not found\n" << std::endl;
     fichier.close();
}

void simuWin::loadSet(string dest){
    if(currentModel) {
         if(!dest.compare("")) dest = QFileDialog::getOpenFileName(this,"Open ...",QDir::currentPath().toStdString().c_str(), tr("Text Files (*.txt)")).toStdString();
         currentModel->loadParameters(dest);
         //ui->textEditParamSet->clear();
         QString res = QString("");
         for(int i = 0; i < currentModel->getNbParams(); ++i){
             res.append(QString::number(currentModel->getParam(i)) + QString("\t"));
         }
         //ui->textEditParamSet->append(res);
         // Experiments fera le initialize
         updateParmsFromModel();
         simulate();
    }
}




void simuWin::saveSet(string _name){
    if(!_name.compare("")){
         _name = QFileDialog::getSaveFileName(this, QString(""), ui->lineEditWorkingFolder->text()).toStdString();
    }
    currentModel->saveParameters(_name);
}


void simuWin::resetParams(){
    std::cout << "Reset Parameters\n";
    currentModel->setBaseParameters();
    //for(int i = 0; i < currentModel->getNbParams(); ++i){
        //currentModel->setParam(i, currentModel->getLowerBound(i));
        //std::cout << i << " , " << currentModel->getParam(i) << std::endl;
    //}
    //currentExperiment->m->initialise();
    updateParmsFromModel();
/*    QModelIndex startOfRow = tableContents->index(0, 0);
    tableContents->item(0,0)->setData(1); //>setData(QString("1"));
    emit tableContents->dataChanged(startOfRow, startOfRow);
    ui->tableView->repaint();
*/
    simulate();
}

simuWin::~simuWin()
{
    delete ui;
}

/*Optimizer::Optimizer(simuWin* _currentWindow) : currentWindow(_currentWindow){}
Optimizer::~Optimizer(){}
void Optimizer::process(){
    currentWindow->optimize();
    emit finished();
}


void simuWin::optimizeThread(){
    thread = new QThread;
    opt = new Optimizer(this);
    opt->moveToThread(thread);
    connect(opt, SIGNAL(error(QString)), this, SLOT(errorString(QString)));
    connect(thread, SIGNAL(started()), opt, SLOT(process()));
    connect(opt, SIGNAL(finished()), thread, SLOT(quit()));
    connect(opt, SIGNAL(finished()), opt, SLOT(deleteLater()));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();
}
*/
#endif

evolution::evolution(int _sizeGroups) : sizeGroups(_sizeGroups), currentGroup(0), nbInCurrentGroup(0) {
    if((sizeGroups < 1) || (sizeGroups > 1e6)) {std::cerr << "ERR evolution : size group (" << sizeGroups << " is out of bounds. 1e6 taken\n"; sizeGroups = 1e6;}
    clear();
}

void evolution::clear(){
    int NL = tables.size();
    for(int i = 0; i < NL; ++i)
        if(tables[i]) delete tables[i];
    tables.clear();
    tables.push_back(new vector<double>(sizeGroups, 1e12));
    currentGroup = 0;   // is also the number of finished groups
    nbInCurrentGroup = 0;
    stddevs.clear(); // size : currentGroup, attention !
    mins.clear();
    maxs.clear();
    means.clear();
    Xs.clear();
}

void evolution::newValue(double _v){
    if(nbInCurrentGroup == sizeGroups) {
        static int cptNew = 0;
        cptNew++;
        if(cptNew > 10000) std::cerr << "WRN: Would need to free memory inside evolution::newValue" << std::endl;
        tables.push_back(new vector<double>(sizeGroups, 1e12));
        nbInCurrentGroup = 0;
        double sum = 0;
        double ecarts = 0;
        double locmin = (* tables[currentGroup])[0];
        double locmax = (* tables[currentGroup])[0];
        for(int i = 0; i < sizeGroups; ++i){
            double val = (* tables[currentGroup])[i];
            sum += val;
            ecarts += val * val;
            locmin = std::min(locmin, val);
            locmax = std::max(locmax, val);
        }
        if(currentGroup > 0) {
            locmin = std::min(locmin, mins[currentGroup-1]); // indice to check
        }
        mins.push_back(locmin);
        maxs.push_back(locmax);
        means.push_back(sum / (double) sizeGroups);
        stddevs.push_back(sqrt((ecarts / (double) sizeGroups) - means[currentGroup] * means[currentGroup]));
        currentGroup++;
        Xs.push_back(currentGroup * sizeGroups);
    }
    (*(tables[currentGroup]))[nbInCurrentGroup] = _v;
    nbInCurrentGroup++;
}

string evolution::print(){
    std::stringstream f;
    f << "Evolution of cost over time, evaluated for every group of (" << sizeGroups << ") new simulations\n";
    f << currentGroup << "\t" << 5 << "\n";
    f << "nb\tMin\tMax\tAverage\tStdDev\n";
    for(int i = 0; i < currentGroup; ++i){
        f << std::setprecision(5) << i << "\t" << mins[i] << "\t" << maxs[i] << "\t" << means[i] << "\t" << stddevs[i] << "\n";
    }
    return f.str();
}

#ifndef WITHOUT_QT
void simuWin::changeLogY(int putToLog){
    currentGraphe->logarithmic(putToLog == Qt::Checked);
    varChanged(ui->comboBoxVariable->currentIndex());
}

void simuWin::showOnlyCombChecked(int newState){
    int NP = currentModel->getNbParams();
    int NV = currentModel->getNbVars();
    ui->spinBoxOnlyComb->setMinimum(0);
    ui->spinBoxOnlyComb->setMaximum(nbCombs - 1);
    int selectedConf = ui->spinBoxOnlyComb->value();
    for(int i = 0; i < NP; ++i){
        if(newState > 0){
            currentTable->setRowHidden(i, currentConfig[i][selectedConf + 4].compare("1"));
        }
        else currentTable->setRowHidden(i, false);
    }
    for(int i = NP; i < NP + NV; ++i){
        currentTable->setRowHidden(i, (newState > 0));
    }

}
#endif




