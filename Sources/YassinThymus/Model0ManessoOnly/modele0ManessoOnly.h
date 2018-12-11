#ifndef modele1ThymusSpl_H
#define modele1ThymusSpl_H
#include "../../common.h"
#include "../../Framework/modele.h"
#include "../namesThymus.h"

struct modele0ManessoOnly : public Modele {
    modele0ManessoOnly();
    enum{
        flu,
        tPreDN1,
        tDN1s, tDN2, tDN3, tDN4,
        floDN1to2, floDN2to3, floDN3to4, flowDN4toDP,
        tDNs,
        tDN1g0, tDN1g1, tDN1g2, tDN1g3, tDN1g4, tDN1g5, tDN1g6, tDN1g7, tDN1g8, tDN1g9, tDN1g10, tDN1g11, tDN1g12, tDN1g13, tDN1g14, tDN1g15,
        fracInPreDN1, fracInDN1, fracInDN2, fracInDN3, fracInDN4,
        NbVariables};
    enum{
        flu_peak,
        flu_std,

        fETP_tDN,
        decayDN1pre,

        commitDN1to2,
        deathDN1,
        cycleDN1,

        commitDN2to3,
        deathDN2,
        cycleDN2,

        commitDN3to4,
        deathDN3,
        cycleDN3,

        commitDN4toDP,
        deathDN4,
        cycleDN4,

        hypInflowCoeffETP,
        hypDeathCoeffDN1,
        hypDeathCoeffDN2,
        hypDeathCoeffDN3,
        hypDeathCoeffDN4,

        logisticThymus,
        logisticStrength,

        NbParameters};

    long long background; // for different models
    virtual void derivatives(const vector<double> &x, vector<double> &dxdt, const double t);
    void initialise(long long _background = Back::WT);
	void setBaseParameters();
    void updateDerivedVariables();

    void action(string name, double parameter){
        if(!name.compare("wash")){
            if((parameter > 1.0) || (parameter < 0)) {cerr << "ERR: ModeleMinLatent::action(" << name << ", " << parameter << "), wrong parameter value\n"; return;}
            // val[IL2] =    (1 - parameter) * val[IL2]; // example of how the hell it works
            return;
        }
    }
};

#endif
