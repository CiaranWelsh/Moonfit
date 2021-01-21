// -------------- ODE model for perturbed thymyus dynamcis -------------
//
// Author:      Philippe A. Robert (philippe [dot] robert [at] ens-lyon.org, 8th Feb. 2020
// Source:      gitlab.com/Moonfit/Balthyse
// References   [1] Robert, P., Jönsson, E and Meyer-Hermann, M MoonFit, a minimal interface for fitting ODE
//                  dynamical models, bridging simulation by experimentalists and customization by C++ programmers,
//                  BioRxiV 2018, https://doi.org/10.1101/281188
//              [2] Elfaki, Y. et al. Influenza A virus-induced thymic atrophy differentially affects conventional
//                  and regulatory T cell developmental dynamics. EJI 2020


#ifndef modele6Combined_H
#define modele6Combined_H

#include "../Moonfit/moonfit.h"

namespace Back {
    enum : long long {
        WT = 1,
        B_ReducedInflow = 2,
        B_MoreDeath = 4,
        B_MoreOutputThymus = 8,
        B_FasterDifferentiation = 16,
        B_SpaceDependentOutput = 32,
        B_DivisionReduced = 64,
        B_AllCombined = 127,
        B_LogisticTotalProlif = 256,
        B_InitThiault = 512,
        B_StartSteadyState = 1024,
        B_BRDU = 2048,
        B_Reconstitution = 4096,
        B_ProlifBlocked = 8192,
        B_UseC0 = 16384,
        B_UseHighC = 32768,
        B_UseStep = 65536,
        B_UseSquare = 131072
    };
}

//1: choose model structure, A, B or C
// careful of capital letters !!!
#define ModelStructureB

//2: for hypotheses with coupled parameters, meaning factorF has same impact on multiple outputs, choose:

//- for increased export of all SP cells equally, including SP8 [the parameter for Tconv applies to all then]
//#define equalExportAll

//- if not, for equal increased export of Tregs and progenitors, [the parameter for mature DPTregs applies to all then]
#define equalExportTregs

// and/or, for equal increased export of Tconv and SP8 [the parameter for Tconv applies to SP8], but Tregs have their own differen export,
//#define equalExportSP4SP8


#ifdef ModelStructureA
#define DPtoFp3Prec
#define DPto25Prec
#endif

#ifdef ModelStructureB
#endif

#ifdef ModelStructureC
#define DPto25Prec
#endif


struct modele6GenericTVaslin : public Model {
    modele6GenericTVaslin();

    int NmaxDN;
    double divFloatDN;
    vector<double> DoProlifDN;
    int NmaxDP;
    double divFloatDP;
    vector<double> DoProlifDP;

    void calculateParameters(double xFlu = 0.0);

    double InflowCoeffETP;
    double DeathCoeffDN;
    double DeathCoeffDP;
    double DeathCoeffTconv;
    double DeathCoeffProFp3;
    double DeathCoeffPro25;
    double DeathCoeffDPTregs;
    double DeathCoeffSP8;
    double DeathCoeffEarlyDP = 0; // attention !
    double OutputCoeffOutDP;
    double OutputCoeffOutTconv;
    double OutputCoeffOutDPTregs;
    double OutputCoeffOutProFP3;
    double OutputCoeffOutPro25;
    double OutputCoeffOutSP8;
    double LessDivisionsDN;
    double LessDivisionsDP;
    double FasterCoeffProFP3;
    double FasterCoeffPro25;
    double FasterCoeffTconv;
    double FasterCoeffSP8;
    double OutputCoeffDNtoDP;
    double SpaceOutputCoeffAll;
    double LessProlifSpeedDN;
    double LessProlifSpeedDP;
    double LessProlifSpeedTregPro25;
    double LessProlifSpeedTregProFP3;
    double LessProlifSpeedDPTreg;
    double LessProlifSpeedTconv;
    double LessProlifSpeedCD8;
    double OutputCoeffOutDN; // not used yet

    enum {
        flu,
        DNtot,
        eDPtot,
        lDP,
        DPtot,
        tSP8P,
        tSP8P69N,
        tSP4P,
        tSP4P69N,
        tTconvP,
        tTRegP25P,
        tTRegPFp3P,
        tTregP,
        tSP8RagN,
        tSP4RagN,
        tTconvRagN,
        tTregP1RagN,
        tTregP2RagN,
        tTregRagN,
        tSP8tot,
        tSP4tot,
        tTconvtot,
        tTregP1tot,
        tTregP2tot,
        tTregtot,
        ttotal,

        // percents of total T cells. SP4 include Tregs and co
        pctDN,
        pctDP,
        pctSP8,
        pctSP4,

        // percents inside CD4SP
        pctTconvtot,
        pctTRegP1tot,
        pctTRegP2tot,
        pctTregtot,

        pctTconvP,
        pctTRegP1P,
        pctTRegP2P,
        pctTregP,

        pctSP8RagN,
        pctSP4RagN,
        pctTconvRagN,
        pctTRegP1RagN,
        pctTRegP2RagN,
        pctTregRagN,

        //stotal, sTconv, sTreg, sCD8, sBcells,
        //sTconvRagN, sTregRagN, sCD8RagN,
        //pcsTconv, pcsTreg, pcsCD8, pcsBcells,
        //pcsTconvRagN, pcsTregRagN, pcsCD8RagN,

        // Thomas-Vaslin for SP4 and SP8
        SP4totTV,
        SP8totTV,
        divSP4g0,
        divSP4g1,
        divSP4g2,
        divSP8g0,
        divSP8g1,
        divSP8g2,

        SP4stage69hi,
        SP4stage69lo,
        SP8stage69hi,
        SP8stage69lo,
        SP4tot2St,
        SP8tot2St,

        floweDNtoeDP,
        floweDPtolDP,
        flowDPtoSP4,
        flowDPtoSP8,
        flowDPtoTconv,
        flowDPtoTregP1,
        flowDPtoTregP2,
        flowTregP1toTreg,
        flowTregP2toTreg,
        flowSP4toOut,
        flowSP8toOut,
        flowTregtoOut,
        floweDPtoDead,
        flowlDPtoDead,
        flowSP4toDead,
        flowSP8toDead,
        flowTconvtoDead,
        flowTregP1toDead,
        flowTregP2toDead,
        flowTregtoDead,

        divDNg0,
        divDNg1,
        divDNg2,
        divDNg3,
        divDNg4,
        divDNg5,
        divDNg6,
        divDNg7,
        divDNg8,
        divDNg9,
        divDNg10,
        divDNg11,
        divDNg12,
        divDNg13,
        divDNg14,
        divDNg15,
        divDNg16,
        divDNg17,
        divDNg18,
        divDNg19,
        divDNg20,
        divDNg21,
        divDNg22,
        divDNg23,
        divDNg24,
        divDNg25,
        divDNg26,
        divDNg27,
        divDNg28,
        divDNg29,
        divDNg30LastDiv,
        eDPg0,
        eDPg1,
        eDPg2,
        eDPg3,
        eDPg4,
        eDPg5,
        eDPg6,
        eDPg7,
        eDPg8,
        eDPg9,
        eDPg10,

        NbVariables
    };
    enum {
        flu_peak,
        flu_std,
        fETP_tDN, // inflow

        // General N-div model. pDN derived from other coefficients
        NdivDN,
        pDN,
        dDN,
        T_DN,

        // Thomas-Vaslin for DP. drestDP + diffDPtoSP4 + diffDPtoSP8 is the 'outflow' of DP and can be kept constant / identifiable
        NdivDP,
        peDP,
        deDP,
        prestDP,    // = 0, no meaning
        drestDP,
        // the diff INCLUDES tregs
        out_tDP,
        diffDPtoSP4,
        diffDPtoSP8,

        // two-step ODE model for SP4 and SP8, just p and d + diff first ODE to second ODE,
        ptTconv,
        dtTconv,
        diffSP4P69PosToNeg,
        out_tTconv,

        ptSP8,
        dtSP8,
        diffSP8P69PosToNeg,
        out_SP8,

        // two-step Tregs models:
        ftDP_tTregP25,
        ftDP_tTregFP3,

        ptTregP25,
        ftTregP25_tDPTreg,
        dtTregP25,

        ptTregFP3, // prolif singer
        ftTregFP3_tDPTreg, // conversion singer to mature DPTregs
        dtTregFP3,

        ptDPTregs,
        dtDPTregs,
        out_tDPTregs,


        // Parameters T-Vaslin
        NdivSP4,
        pSP4,
        dSP4,
        pcConvLastGenSP4,
        NdivSP8,
        pSP8,
        dSP8,
        pcConvLastGenSP8,


        out_tTregP25,
        out_tTregFP3,

        fracTtoS,
        dsTconv,
        dsTreg,
        dsCD8,
        dsBcells,
        decayRag,

        // Hypotheses parameters
        //ReducedInflow,
        hypInflowCoeffETP,

        //MoreDeath,
        hypDeathCoeffDN,
        hypDeathCoeffAddEarlyDP,
        hypDeathCoeffDP,
        hypDeathCoeffTconv,
        hypDeathCoeffProFp3,
        hypDeathCoeffPro25,
        hypDeathCoeffDPTregs,
        hypDeathCoeffSP8,

        //MoreOutputThymus,
        hypOutputCoeffOutDP,
        hypOutputCoeffOutTconv,
        hypOutputCoeffOutDPTregs,
        hypOutputCoeffOutProFP3,
        hypOutputCoeffOutPro25,
        hypOutputCoeffOutSP8,

        //FasterDifferentiation,
        hypFasterCoeffDNtoDP,
        hypFasterCoeffDPtolDP,
        hypFasterCoeffProFP3,
        hypFasterCoeffPro25,
        hypFasterCoeffTconv,
        hypFasterCoeffSP8,

        //SpaceDependentOutput
        hypOutputCoeffDNtoDP,

        //ImpactProlifRates
        hypSpeedDivDN,
        hypSpeedDivDP,
        hypSpeedDivTregPro25,
        hypSpeedDivTregProFP3,
        hypSpeedDivDPTreg,
        hypSpeedDivTconv,
        hypSpeedDivCD8,

        logisticThymus,
        logisticStrength,

        NbParameters
    };

    long long background; // for different models
    virtual void derivatives(const vector<double> &x, vector<double> &dxdt, const double t);

    void initialise(long long _background = Back::WT);

    void setBaseParameters();

    void updateDerivedVariables(double _t);

    void action(string name, double parameter) {
        if (!name.compare("wash")) {
            if ((parameter > 1.0) || (parameter < 0)) {
                cerr << "ERR: ModeleMinLatent::action(" << name << ", " << parameter << "), wrong parameter value\n";
                return;
            }
            // val[xxx] =   xxx; // example of how the hell it works
            return;
        }
    }

    virtual ~modele6GenericTVaslin() {}
};

#endif

