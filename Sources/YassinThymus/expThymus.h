#ifndef EXPERIMENTSTHALL_H
#define EXPERIMENTSTHALL_H



#include "namesThymus.h"
#include "../Framework/Experiment.h"
#include "../Framework/evaluator.h"
#include "../Framework/modele.h"
#include "../Framework/overrider.h"

#include <vector>
#include <string>
#include <iostream>

using namespace std;

enum EXP{PBS, MoreDeath, MoreOutputThymus, FasterDifferentiation, DivisionReduced, LogisticTotalProlif, ReducedInflow, LogisticTotalProlifMoreOut, LogisticTotalProlifFasterDiff, NB_EXP}; // AllCombined, , Infection, ReducedInflow, SpaceDependentOutput, NB_EXP};// experiments

struct expThymus : public Experiment {
    expThymus(Modele* _m);

    //void init();
    void simulate(int IdExp, Evaluator* E = NULL, bool force = false); // if no E is given, VTG[i] is used
};

struct expCombinedHyp : public Experiment {
    expCombinedHyp(Modele* _m);

    //void init();
    void simulate(int IdExp, Evaluator* E = NULL, bool force = false); // if no E is given, VTG[i] is used
};

struct expCombinedHypLog : public Experiment {
    expCombinedHypLog(Modele* _m);

    //void init();
    void simulate(int IdExp, Evaluator* E = NULL, bool force = false); // if no E is given, VTG[i] is used
};


struct expRecirculation: public Experiment {
    expRecirculation(Modele* _m);

    //void init();
    void simulate(int IdExp, Evaluator* E = NULL, bool force = false); // if no E is given, VTG[i] is used
};

struct expDevlopment: public Experiment {
    expDevlopment(Modele* _m);

    //void init();
    void simulate(int IdExp, Evaluator* E = NULL, bool force = false); // if no E is given, VTG[i] is used
};

struct expDNPotritt: public Experiment {
    expDNPotritt(Modele* _m);

    //void init();
    void simulate(int IdExp, Evaluator* E = NULL, bool force = false); // if no E is given, VTG[i] is used
};


#endif // EXPERIMENTSTHALL_H
