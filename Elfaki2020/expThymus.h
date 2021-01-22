// -------------- Experiment to perform thymic atrophy simulations / optimizations -------------
//
// Author:      Philippe A. Robert (philippe [dot] robert [at] ens-lyon.org, 8th Feb. 2020
// Source:      gitlab.com/Moonfit/Balthyse
// References   [1] Robert, P., Jönsson, E and Meyer-Hermann, M MoonFit, a minimal interface for fitting ODE
//                  dynamical models, bridging simulation by experimentalists and customization by C++ programmers,
//                  BioRxiV 2018, https://doi.org/10.1101/281188
//              [2] Elfaki, Y. et al. Influenza A virus-induced thymic atrophy differentially affects conventional
//                  and regulatory T cell developmental dynamics. EJI 2020

#ifndef EXPERIMENTSTHALL_H
#define EXPERIMENTSTHALL_H

#include "../Moonfit/moonfit.h"

#include <vector>
#include <string>
#include <iostream>

// using namespace std;
using std::string;
using std::vector;

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

struct expStopProlif: public Experiment {
    expStopProlif(Model* _m);

    //void init();
    void simulate(int IdExp, Evaluator* E = NULL, bool force = false); // if no E is given, VTG[i] is used
};

#endif // EXPERIMENTSTHALL_H
