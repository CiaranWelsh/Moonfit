#include "../Framework/Experiment.h"
#include "expThymus.h"
#include "../Framework/evaluator.h"
#include "../Framework/modele.h"
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

expCombinedHyp::expCombinedHyp(Modele* _m) : Experiment(_m, 1){
    Identification = string("Influenza combines different mechanisms");
    names_exp[0] =                  string("All combined effects");
    doable.clear();
    doable.resize(1, true);
    m->setBaseParameters();
}

void expCombinedHyp::simulate(int IdExp, Evaluator* E, bool force){
    //if(!E) E = VTG[IdExp]; // seems not necessary ( I was afraid of destruction of E)
    if(motherPrepareSimulate(IdExp, E, force)){
        //m->initialise(Back::B_MoreDeath | Back::B_MoreOutputThymus | Back::B_FasterDifferentiation | Back::B_DivisionReduced);
        m->initialise(Back::B_ReducedInflow | Back::B_MoreDeath | Back::B_FasterDifferentiation | Back::B_DivisionReduced | Back::B_StartSteadyState);
        m->simulate(25, E);
        m->setOverrider(NULL);
    }
}

expDNPotritt::expDNPotritt(Modele* _m) : Experiment(_m, 3){
    Identification = string("Influenza combines different mechanisms");
    names_exp[0] =                  string("SteadyState");
    // Steady state first, to get parameters,
    names_exp[1] =                  string("Injection precursors");
    names_exp[2] =                  string("BRDU on eDP");
    doable.clear();
    doable.resize(3, true);
    m->setBaseParameters();
}

void expDNPotritt::simulate(int IdExp, Evaluator* E, bool force){
    //if(!E) E = VTG[IdExp]; // seems not necessary ( I was afraid of destruction of E)
    if(motherPrepareSimulate(IdExp, E, force)){
        if(IdExp == 0) m->initialise(Back::B_ReducedInflow | Back::B_MoreDeath | Back::B_FasterDifferentiation | Back::B_DivisionReduced | Back::B_StartSteadyState);
        if(IdExp == 1) m->initialise();
        if(IdExp == 2) m->initialise(Back::B_BRDU);
        m->simulate(40, E);
        m->setOverrider(NULL);
    }
}



expCombinedHypLog::expCombinedHypLog(Modele* _m) : Experiment(_m, 1){
    Identification = string("Combined effect + Logistic");
    names_exp[0] =                  string("All combined effects");
    doable.clear();
    doable.resize(1, true);
    m->setBaseParameters();
}

void expCombinedHypLog::simulate(int IdExp, Evaluator* E, bool force){
    //if(!E) E = VTG[IdExp]; // seems not necessary ( I was afraid of destruction of E)
    if(motherPrepareSimulate(IdExp, E, force)){
        m->initialise(Back::B_LogisticTotalProlif | Back::B_MoreDeath | Back::B_MoreOutputThymus | Back::B_FasterDifferentiation | Back::B_DivisionReduced);
        m->simulate(100, E);
        m->setOverrider(NULL);
    }
}







expThymus::expThymus(Modele* _m) : Experiment(_m, NB_EXP){
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
    doable.clear();
    doable.resize(NB_EXP, true);

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
            //m->setValue(N::P, 5000.0);
            break;}
        case Infection: {
            //m->setValue(N::P, 15000.0);
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



expRecirculation::expRecirculation(Modele* _m) : Experiment(_m, NB_EXP_RECIR){
    Identification = string("Recirculation over time");
    names_exp[WT_recir] = string("WT");
    doable.clear();
    doable.resize(NB_EXP, true);
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

expDevlopment::expDevlopment(Modele* _m) : Experiment(_m, NB_EXP_RECIR){
    Identification = string("Recirculation over time");
    //Overs.resize(NB_EXP, NULL);
    //names_exp.resize(NB_EXP);
    names_exp[WT_recir] = string("WT");
    doable.clear();
    doable.resize(NB_EXP, true);
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

