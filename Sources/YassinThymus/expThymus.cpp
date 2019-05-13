#include "../Moonfit/moonfit.h"
#include "expThymus.h"
#include "namesThymus.h"

#include <iostream>
#include <fstream>
#include <sstream>

/*
expThymus::expOnlyDeath(Modele* _m) : Experiment(_m, 1){
    Identification = string("Influenza kills thymoctes");
    //Overs.resize(NB_EXP, NULL);
    //names_exp.resize(NB_EXP);
    names_exp[0] =                  string("MoreDeath");
    doable.clear();
    doable.resize(1, true);
    m->setBaseParameters();
}

expThymus::expOnlyMoreOutput(Modele* _m) : Experiment(_m, 1){
    Identification = string("Influenza outputs thymocytes");
    names_exp[0] =                  string("MoreOutputThymus");
    doable.clear();
    doable.resize(1, true);
    m->setBaseParameters();
}

expThymus::expOnlyFasterDifferentiation(Modele* _m) : Experiment(_m, 1){
    Identification = string("Influenza increases differentiation");
    names_exp[0] =                  string("FasterDifferentiation");
    doable.clear();
    doable.resize(1, true);
    m->setBaseParameters();
}*/

expCombinedHyp::expCombinedHyp(Model* _m) : Experiment(_m, 1){
    Identification = string("Influenza combines different mechanisms");
    names_exp[0] =                  string("All combined effects");
    m->setBaseParameters();
}

void expCombinedHyp::simulate(int IdExp, Evaluator* E, bool force){
    //if(!E) E = VTG[IdExp]; // seems not necessary ( I was afraid of destruction of E)
    if(motherPrepareSimulate(IdExp, E, force)){
        //m->initialise(Back::B_MoreDeath | Back::B_MoreOutputThymus | Back::B_FasterDifferentiation | Back::B_DivisionReduced);
        m->initialise(Back::B_ReducedInflow | Back::B_MoreDeath | Back::B_FasterDifferentiation | Back::B_DivisionReduced | Back::B_StartSteadyState | Back::B_MoreOutputThymus);
        m->simulate(25, E);
        m->setOverrider(NULL);
    }
}

expDNPotritt::expDNPotritt(Model* _m) : Experiment(_m, 3){
    Identification = string("Influenza combines different mechanisms");
    names_exp[0] =                  string("SteadyState");
    // Steady state first, to get parameters,
    names_exp[1] =                  string("Injection precursors");
    names_exp[2] =                  string("Reconstitution");
    m->setBaseParameters();
}

void expDNPotritt::simulate(int IdExp, Evaluator* E, bool force){
    //if(!E) E = VTG[IdExp]; // seems not necessary ( I was afraid of destruction of E)
    if(motherPrepareSimulate(IdExp, E, force)){
        if(IdExp == 0) m->initialise(Back::B_StartSteadyState); // | Back::B_ReducedInflow | Back::B_MoreDeath | Back::B_FasterDifferentiation | Back::B_DivisionReduced | Back::B_StartSteadyState | Back::B_MoreOutputThymus);
        if(IdExp == 1) m->initialise();
        if(IdExp == 2) m->initialise(Back::B_Reconstitution);
        m->simulate(40, E);
        m->setOverrider(NULL);
    }
}


expCompParameterSets::expCompParameterSets(Model* _m, vector< vector<double> *> _parameterSets) : Experiment(_m, _parameterSets.size()){
    Identification = string("Comparison of different parameter sets");
    parameterSets = _parameterSets;
    for(int i = 0; i < (int) parameterSets.size(); ++ i){
        stringstream nm; nm << "P" << i;
        names_exp[i] = nm.str();
    }
    m->setBaseParameters();
}

void expCompParameterSets::simulate(int IdExp, Evaluator* E, bool force){
    //if(!E) E = VTG[IdExp]; // seems not necessary ( I was afraid of destruction of E)
    if(motherPrepareSimulate(IdExp, E, force)){
        if((IdExp < 0) || (IdExp >= (int) parameterSets.size())) cerr << "expCompParameterSets, Problem between Nb Exp and Nb of given parameter sets " << endl;
        vector<double>* v = parameterSets[IdExp];
        if(!v) cerr << "ERR: expCompParameterSets, non-existing parameter set" << endl;
        m->setParameters(*v);
        m->initialise();
        m->simulate(40, E);
        m->setOverrider(NULL);
    }
}


expStopProlif::expStopProlif(Model* _m) : Experiment(_m, 7){
    Identification = string("Blocking proliferation");
    names_exp[0] =                  string("SteadyState");
    names_exp[1] =                  string("Block 1 day");
    names_exp[2] =                  string("Block 2 days");
    names_exp[3] =                  string("Block 3 days");
    names_exp[4] =                  string("Block 5 days");
    names_exp[5] =                  string("Block 7 days");
    names_exp[6] =                  string("Block 10 days");
    m->setBaseParameters();
}

void expStopProlif::simulate(int IdExp, Evaluator* E, bool force){
    //if(!E) E = VTG[IdExp]; // seems not necessary ( I was afraid of destruction of E)
    if(motherPrepareSimulate(IdExp, E, force)){
        m->initialise(Back::B_ProlifBlocked | Back::B_ReducedInflow | Back::B_MoreDeath | Back::B_FasterDifferentiation | Back::B_DivisionReduced | Back::B_StartSteadyState | Back::B_MoreOutputThymus);
        m->simulate(5, E);
        int timeBlock = 0;
        switch(IdExp){
        case 0: timeBlock = 0; break;
        case 1: timeBlock = 1; break;
        case 2: timeBlock = 2; break;
        case 3: timeBlock = 3; break;
        case 4: timeBlock = 5; break;
        case 5: timeBlock = 7; break;
        case 6: timeBlock = 10; break;
        }
        m->simulate(timeBlock, E);
        m->simulate(35 - timeBlock, E);
        m->setOverrider(NULL);
    }
}



expCombinedHypLog::expCombinedHypLog(Model* _m) : Experiment(_m, 1){
    Identification = string("Combined effect + Logistic");
    names_exp[0] =                  string("All combined effects");
    m->setBaseParameters();
}

void expCombinedHypLog::simulate(int IdExp, Evaluator* E, bool force){
    //if(!E) E = VTG[IdExp]; // seems not necessary ( I was afraid of destruction of E)
    if(motherPrepareSimulate(IdExp, E, force)){
        m->initialise(Back::B_LogisticTotalProlif | Back::B_MoreDeath | Back::B_MoreOutputThymus | Back::B_FasterDifferentiation | Back::B_DivisionReduced | Back::B_MoreOutputThymus);
        m->simulate(100, E);
        m->setOverrider(NULL);
    }
}









expOneCompartment::expOneCompartment(Model* _m) : Experiment(_m, 13){
    Identification = string("Blocking proliferation");
    names_exp[0] =                  string("SteadyState");
    names_exp[1] =                  string("Ndiv - Smooth");
    names_exp[2] =                  string("Ndiv - Step");
    names_exp[3] =                  string("Ndiv - Square");
    names_exp[4] =                  string("HighC - Smooth");
    names_exp[5] =                  string("HighC - Step");
    names_exp[6] =                  string("HighC - Square");
    names_exp[7] =                  string("NoC - Smooth");
    names_exp[8] =                  string("NoC - Step");
    names_exp[9] =                  string("NoC - Square");
    names_exp[10] =                 string("Reconstitution - Ndiv");
    names_exp[11] =                 string("Reconstitution - HighC");
    names_exp[12] =                 string("Reconstitution - NoC");
    m->setBaseParameters();
}

void expOneCompartment::simulate(int IdExp, Evaluator* E, bool force){
    if(motherPrepareSimulate(IdExp, E, force)){
        long long unsigned int BackDef = Back::B_ProlifBlocked | Back::B_ReducedInflow | Back::B_MoreDeath | Back::B_FasterDifferentiation | Back::B_DivisionReduced | Back::B_MoreOutputThymus;
        //cout << "Initialize " << IdExp << endl;
        switch(IdExp){
        case 0: m->initialise(Back::B_StartSteadyState); break;     // Note: by default, this is Use_n_div
        case 1: m->initialise(Back::B_StartSteadyState | BackDef ); break;
        case 2: m->initialise(Back::B_StartSteadyState | BackDef | Back::B_UseStep); break;
        case 3: m->initialise(Back::B_StartSteadyState | BackDef | Back::B_UseSquare); break;
        case 4: m->initialise(Back::B_StartSteadyState | BackDef | Back::B_UseHighC); break;
        case 5: m->initialise(Back::B_StartSteadyState | BackDef | Back::B_UseHighC | Back::B_UseStep); break;
        case 6: m->initialise(Back::B_StartSteadyState | BackDef | Back::B_UseHighC | Back::B_UseSquare); break;
        case 7: m->initialise(Back::B_StartSteadyState | BackDef | Back::B_UseC0); break;
        case 8: m->initialise(Back::B_StartSteadyState | BackDef | Back::B_UseC0 | Back::B_UseStep); break;
        case 9: m->initialise(Back::B_StartSteadyState | BackDef | Back::B_UseC0 | Back::B_UseSquare); break;
        case 10: m->initialise(); break;
        case 11: m->initialise(Back::B_UseHighC); break;
        case 12: m->initialise(Back::B_UseC0); break;
        }
        m->simulate(35, E);
        m->setOverrider(NULL);
    } else {
        cerr << "No idea didnt work" << endl;
    }
}

expSmoothCompartment::expSmoothCompartment(Model* _m) : Experiment(_m, 1){
    Identification = string("Blocking proliferation");
    names_exp[0] =                  string("Ndiv - Smooth");
    m->setBaseParameters();
}

void expSmoothCompartment::simulate(int IdExp, Evaluator* E, bool force){
    if(motherPrepareSimulate(IdExp, E, force)){
        long long unsigned int BackDef = Back::B_ProlifBlocked | Back::B_ReducedInflow | Back::B_MoreDeath | Back::B_FasterDifferentiation | Back::B_DivisionReduced | Back::B_MoreOutputThymus;
        //cout << "Initialize " << IdExp << endl;
        switch(IdExp){
        case 0: m->initialise(Back::B_StartSteadyState | BackDef ); break;
        }
        m->simulate(35, E);
        m->setOverrider(NULL);
    } else {
        cerr << "No idea didnt work" << endl;
    }
}




expThymus::expThymus(Model* _m) : Experiment(_m, NB_EXP){
    Identification = string("Thymic infection with influenza");
    //Overs.resize(NB_EXP, NULL);
    //names_exp.resize(NB_EXP);
    names_exp[PBS] = string("PBS control"); // activation (TCR Only)");
    names_exp[MoreDeath] =                  string("MoreDeath");
    names_exp[MoreOutputThymus] =           string("MoreOutputThymus");
    names_exp[FasterDifferentiation] =      string("FasterDifferentiation");
    names_exp[DivisionReduced] =            string("DivisionReduced");
    names_exp[LogisticTotalProlif] =      string("MoreDeath-LogisticProlif");
 //     AllCombined
    names_exp[ReducedInflow] =              string("ReducedInflow");
    names_exp[LogisticTotalProlifMoreOut] = string("MoreOutput-LogisticProlif");
    names_exp[LogisticTotalProlifFasterDiff] = string("MoreOutput-FasterDiff");

 //   names_exp[SpaceDependentOutput] =       string("SpaceDependentOutput");
 //   names_exp[Infection] = string("Infected"); // activation (TCR Only)");

    m->setBaseParameters();
}


//bool isIn(double Val, double vmin, double vmax){return ((vmin <= Val) && (Val <= vmax));}


////// gné force is missing in simulate
void expThymus::simulate(int IdExp, Evaluator* E, bool force){
    //if(!E) E = VTG[IdExp]; // seems not necessary ( I was afraid of destruction of E)
    if(motherPrepareSimulate(IdExp, E, force)){
        switch(IdExp){
            /*case TH1_IFNGRKO: case IFNG_IFNGRKO: {
                m->initialise(Back::IFNGRKO); break;}*/

            case ReducedInflow: {
                m->initialise(Back::B_ReducedInflow);break;}
            case MoreDeath: {
                m->initialise(Back::B_MoreDeath);break;}
            case MoreOutputThymus: {
                m->initialise(Back::B_MoreOutputThymus);break;}
            case FasterDifferentiation: {
                m->initialise(Back::B_FasterDifferentiation);break;}
            case DivisionReduced:{
                m->initialise(Back::B_DivisionReduced);break;}
            case LogisticTotalProlif:{
                m->initialise(Back::B_LogisticTotalProlif | Back::B_MoreDeath); break;}
            case LogisticTotalProlifMoreOut:{
                m->initialise(Back::B_LogisticTotalProlif | Back::B_MoreOutputThymus); break;}
            case LogisticTotalProlifFasterDiff:{
                m->initialise(Back::B_LogisticTotalProlif | Back::B_FasterDifferentiation); break;}


            // all
            //case SpaceDependentOutput : {
            //    m->initialise(Back::B_SpaceDependentOutput);break;}
            default: {m->initialise(Back::WT); break;}

        }
        // here, no need to stabilization - m.stabilize(2*3600);
        //m->setPrintMode(true, 10800);

        switch(IdExp){
        /*case PBS:{
            //m->setValue(GlobalName(N::P), 5000.0);
            break;}
        case Infection: {
            //m->setValue(GlobalName(N::P), 15000.0);
            break;}
        case ReducedInflow: {
            break;}
        case MoreDeath: {
            break;}
        case MoreOutputThymus: {
            break;}
        case FasterDifferentiation: {
            break;}
        case SpaceDependentOutput : {
            break;}*/
        }
        m->simulate(25, E);
        m->setOverrider(NULL);
    }
}



expRecirculation::expRecirculation(Model* _m) : Experiment(_m, NB_EXP_RECIR){
    Identification = string("Recirculation over time");
    names_exp[WT_recir] = string("WT");
    m->setBaseParameters();
}


void expRecirculation::simulate(int IdExp, Evaluator* E, bool force){
    if(motherPrepareSimulate(IdExp, E, force)){
        switch(IdExp){
            //case PBS: {
            //    m->initialise(Back::B_ReducedInflow);break;}
            default: {m->initialise(Back::B_InitThiault); break;}

        }
        // here, no need to stabilization - m.stabilize(2*3600);
        //m->setPrintMode(true, 10800);
        m->simulate(350, E);
        m->setOverrider(NULL);
    }
}

expDevlopment::expDevlopment(Model* _m) : Experiment(_m, NB_EXP_RECIR){
    Identification = string("Recirculation over time");
    //Overs.resize(NB_EXP, NULL);
    //names_exp.resize(NB_EXP);
    names_exp[WT_recir] = string("WT");
    m->setBaseParameters();
}

////// gné force is missing in simulate
void expDevlopment::simulate(int IdExp, Evaluator* E, bool force){
    //if(!E) E = VTG[IdExp]; // seems not necessary ( I was afraid of destruction of E)
    if(motherPrepareSimulate(IdExp, E, force)){
        switch(IdExp){
            default: {m->initialise(Back::WT); break;}
        }
        m->simulate(25, E);
        m->setOverrider(NULL);
    }
}

