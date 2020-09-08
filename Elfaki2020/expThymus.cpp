// -------------- Experiment to perform thymic atrophy simulations / optimizations -------------
//
// Author:      Philippe A. Robert (philippe [dot] robert [at] ens-lyon.org, 8th Feb. 2020
// Source:      gitlab.com/Moonfit/Balthyse
// References   [1] Robert, P., Jönsson, E and Meyer-Hermann, M MoonFit, a minimal interface for fitting ODE
//                  dynamical models, bridging simulation by experimentalists and customization by C++ programmers,
//                  BioRxiV 2018, https://doi.org/10.1101/281188
//              [2] Elfaki, Y. et al. Influenza A virus-induced thymic atrophy differentially affects conventional
//                  and regulatory T cell developmental dynamics. EJI 2020

#include "../Moonfit/moonfit.h"
#include "expThymus.h"

// the model defines a list of backgrounds (hypotheses).
#include "modelsStructABC.h"

#include <iostream>
#include <fstream>
#include <sstream>

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
            //m->setValue("ExternalNameVariable", 5000.0);
            break;}
        case Infection: {
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
        m->setOverrider(nullptr);
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

