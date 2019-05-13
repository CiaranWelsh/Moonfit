#ifndef modele5SuperDN_H
#define modele5SuperDN_H
#include "../../Moonfit/moonfit.h"
#include "../namesThymus.h"

struct modele5SuperDN : public Model {
    modele5SuperDN();

    vector<double> ProlifDN1;
    vector<double> ProlifDN2;
    vector<double> ProlifDN3;
    vector<double> ProlifDN4;
    int NmaxDN1;
    int NmaxDN2;
    int NmaxDN3;
    int NmaxDN4;

    // transforms the dynamic number of divisions nDivDNx into the vector of coefficients fi (Prolif) => the vector is the output.
    void calculateParameters(vector<double> & ProlifDNx, double nDivDNx, int NdivMax);
    enum{
        flu,
        tPreDN1,
        tDN1s, tDN2s, tDN3s, tDN4s, tDNs,
        fracInPreDN1, fracInDN1, fracInDN2, fracInDN3, fracInDN4,
        floinDN1, floDN1to2, floDN2to3, floDN3to4, flowDN4toDP,
        tDN1g0, tDN1g1, tDN1g2, tDN1g3, tDN1g4, tDN1g5, tDN1g6, tDN1g7, tDN1g8, tDN1g9, tDN1g10, tDN1g11, tDN1g12, tDN1g13, tDN1g14, tDN1g15,
        tDN2g0, tDN2g1, tDN2g2, tDN2g3, tDN2g4, tDN2g5, tDN2g6, tDN2g7, tDN2g8, tDN2g9, tDN2g10, tDN2g11, tDN2g12, tDN2g13, tDN2g14, tDN2g15,
        tDN3g0, tDN3g1, tDN3g2, tDN3g3, tDN3g4, tDN3g5, tDN3g6, tDN3g7, tDN3g8, tDN3g9, tDN3g10, tDN3g11, tDN3g12, tDN3g13, tDN3g14, tDN3g15,
        tDN4g0, tDN4g1, tDN4g2, tDN4g3, tDN4g4, tDN4g5, tDN4g6, tDN4g7, tDN4g8, tDN4g9, tDN4g10, tDN4g11, tDN4g12, tDN4g13, tDN4g14, tDN4g15,
        NbVariables};
    enum{
        flu_peak,
        flu_std,

        fETP_tDN,   // (1)
        decayDN1pre,// (2)

        NtotDN1,    // (11) because unknown (20 000 to 100 000)
        cycleDN1,   // (7)
        nDivDN1,    // derived from Ntot, cycle, flow In and flow Out
        deathDN1,   // derived from Ntot, cycle, flow In and flow Out
        FlowDN1to2, // (3)

        NtotDN2,
        cycleDN2,   // (8)
        nDivDN2,    // derived from Ntot, cycle, flow In and flow Out
        deathDN2,   // derived from Ntot, cycle, flow In and flow Out
        FlowDN2to3, // (4)

        NtotDN3,
        cycleDN3,   // (9)
        nDivDN3,    // derived from Ntot, cycle, flow In and flow Out
        deathDN3,   // derived from Ntot, cycle, flow In and flow Out
        FlowDN3to4, // (5)

        NtotDN4,
        cycleDN4,   // (10)
        nDivDN4,    // derived from Ntot, cycle, flow In and flow Out
        deathDN4,   // derived from Ntot, cycle, flow In and flow Out
        FlowDN4toeDP,   // (6)

        hypInflowCoeffETP,
        hypDeathCoeffDN1,
        hypDeathCoeffDN2,
        hypDeathCoeffDN3,
        hypDeathCoeffDN4,
        hypLessDivDN,
        hypRandomOutputDN,
        hypChangeNDivDNs,
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
