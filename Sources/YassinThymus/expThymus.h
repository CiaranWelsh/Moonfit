#ifndef EXPERIMENTSTHALL_H
#define EXPERIMENTSTHALL_H



#include "namesThymus.h"
#include "../Moonfit/moonfit.h"

#include <vector>
#include <string>
#include <iostream>

using namespace std;

enum EXP{PBS, MoreDeath, MoreOutputThymus, FasterDifferentiation, DivisionReduced, LogisticTotalProlif, ReducedInflow, LogisticTotalProlifMoreOut, LogisticTotalProlifFasterDiff, NB_EXP}; // AllCombined, , Infection, ReducedInflow, SpaceDependentOutput, NB_EXP};// experiments

struct expThymus : public Experiment {
    expThymus(Model* _m);

    //void init();
    void simulate(int IdExp, Evaluator* E = NULL, bool force = false); // if no E is given, VTG[i] is used
};

struct expCombinedHyp : public Experiment {
    expCombinedHyp(Model* _m);

    //void init();
    void simulate(int IdExp, Evaluator* E = NULL, bool force = false); // if no E is given, VTG[i] is used
};

struct expCombinedHypLog : public Experiment {
    expCombinedHypLog(Model* _m);

    //void init();
    void simulate(int IdExp, Evaluator* E = NULL, bool force = false); // if no E is given, VTG[i] is used
};


struct expRecirculation: public Experiment {
    expRecirculation(Model* _m);

    //void init();
    void simulate(int IdExp, Evaluator* E = NULL, bool force = false); // if no E is given, VTG[i] is used
};

struct expDevlopment: public Experiment {
    expDevlopment(Model* _m);

    //void init();
    void simulate(int IdExp, Evaluator* E = NULL, bool force = false); // if no E is given, VTG[i] is used
};

struct expDNPotritt: public Experiment {
    expDNPotritt(Model* _m);

    //void init();
    void simulate(int IdExp, Evaluator* E = NULL, bool force = false); // if no E is given, VTG[i] is used
};

/*struct expCompParameterSets: public Experiment {
    expCompParameterSets(Model* _m, vector< vector<double> *> _parameterSets);
    vector< vector<double> *> parameterSets;
    void simulate(int IdExp, Evaluator* E = NULL, bool force = false); // if no E is given, VTG[i] is used
};*/



struct expStopProlif: public Experiment {
    expStopProlif(Model* _m);

    //void init();
    void simulate(int IdExp, Evaluator* E = NULL, bool force = false); // if no E is given, VTG[i] is used
};

struct expSmoothCompartment : public Experiment {
    expSmoothCompartment(Model* _m);

    //void init();
    void simulate(int IdExp, Evaluator* E = NULL, bool force = false); // if no E is given, VTG[i] is used
};

struct expOneCompartment : public Experiment {
    expOneCompartment(Model* _m);

    //void init();
    void simulate(int IdExp, Evaluator* E = NULL, bool force = false); // if no E is given, VTG[i] is used
};

// Note: put paramdefault at the end so the last simulation restores the parameter
enum{Param005, Param01, Param02, Param05, Param08, Param12,Param15,Param20,Param50,Param100,ParamDefault,NbParamChange};
struct PerturbParam : public Experiment {
    int parameter;
    double valueAround;

    PerturbParam(Model* _m, int _parameter) : Experiment(_m, NbParamChange), parameter(_parameter) {
        Identification = string("Perturbate") + _m->getParamName(parameter);
        valueAround = m->getParam(parameter);
        stringstream valInString; valInString << valueAround; string val = valInString.str();
        names_exp[ParamDefault] = string("default=") + val;
        names_exp[Param005] = string("5%");
        names_exp[Param01] = string("10%");
        names_exp[Param02] = string("20%");
        names_exp[Param05] = string("50%");
        names_exp[Param08] = string("80%");
        names_exp[Param12] = string("120%");
        names_exp[Param15] = string("150%");
        names_exp[Param20] = string("x2");
        names_exp[Param50] = string("x5");
        names_exp[Param100] = string("x10");
        //m->setBaseParameters();
    }
    /// 2018-11-21 Should not use the parameter value from creation, but the current from the table
    void init(){
        valueAround = m->getParam(parameter);
        stringstream valInString; valInString << valueAround; string val = valInString.str();
        names_exp[ParamDefault] = string("default=") + val;
        motherInit();
    }
    /// Careful, this function should restore the exact same paameter values as before being called
    void simulate(int IdExp, Evaluator* E = NULL, bool force = false) {// if no E is given, VTG[i] is used
        if(motherPrepareSimulate(IdExp, E, force)){
            switch(IdExp){
            case Param005:{
                m->setParam(parameter, valueAround * 0.05);break;}
            case Param01:{
                m->setParam(parameter, valueAround * 0.1);break;}
            case Param02:{
                m->setParam(parameter, valueAround * 0.2);break;}
            case Param05:{
                m->setParam(parameter, valueAround * 0.5);break;}
            case Param08:{
                m->setParam(parameter, valueAround * 0.8);break;}
            case Param12:{
                m->setParam(parameter, valueAround * 1.2);break;}
            case Param15:{
                m->setParam(parameter, valueAround * 1.5);break;}
            case Param20:{
                m->setParam(parameter, valueAround * 2.0);break;}
            case Param50:{
                m->setParam(parameter, valueAround * 5.0);break;}
            case Param100:{
                m->setParam(parameter, valueAround * 10.0);break;}
            // cheating: finishing by the original parameter value to restore the good one
            case ParamDefault:{
                m->setParam(parameter, valueAround);
                cerr << " value for param " << m->getParamName(parameter) << " is " << valueAround << endl;
                break;
            }
            }
            m->initialise(Back::B_StartSteadyState | Back::B_ReducedInflow | Back::B_MoreDeath | Back::B_FasterDifferentiation | Back::B_DivisionReduced | Back::B_MoreOutputThymus);
            m->simulate(40, E);
            m->setOverrider(NULL);
        }
    }
};


#endif // EXPERIMENTSTHALL_H
