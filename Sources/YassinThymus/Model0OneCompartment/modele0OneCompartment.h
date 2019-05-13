#ifndef modele0OneComp_H
#define modele0OneComp_H
#include "../../Moonfit/moonfit.h"

#include "../namesThymus.h"

struct modele0OneCompartment : public Model {
    modele0OneCompartment();
    enum{
        flu,
        tDNs,
        divDNg0, divDNg1, divDNg2, divDNg3, divDNg4, divDNg5, divDNg6, divDNg7, divDNg8, divDNg9, divDNg10, divDNg11, divDNg12, divDNg13, divDNg14, divDNg15, divDNg16, divDNg17, divDNg18, divDNg19, divDNg20,
        tOut,
        NbVariables};
    enum{
        flu_peak,
        flu_std,
        fETP_tDN,
        NdivDN,
        pDN,
        dDN,
        T_DN,
        hypInflowCoeffETP,
        hypDeathCoeffDN,
        hypRandomOutputDN,
        hypLessDivDN,
        hypFasterCoeffDNtoDP,

        logisticThymus,
        logisticStrength,

        NbParameters};

    long long background; // for different models
    virtual void derivatives(const vector<double> &x, vector<double> &dxdt, const double t);
    void initialise(long long _background = Back::WT);
	void setBaseParameters();
    void updateDerivedVariables();
    void calculateParameters(double _FasterCoeffDNtoDP = 1.0);

    int Nmax;
    int N;
    double divFloat;
    double C;
    vector<double> CoeffPerGen;
    vector<double> DoProlif;

    void action(string name, double parameter){
        if(!name.compare("wash")){
            if((parameter > 1.0) || (parameter < 0)) {cerr << "ERR: ModeleMinLatent::action(" << name << ", " << parameter << "), wrong parameter value\n"; return;}
            // val[IL2] =    (1 - parameter) * val[IL2]; // example of how the hell it works
            return;
        }
    }
};

#endif
