// ------- Automatically generated model -------- //
#ifndef modele3Combined_H
#define modele3Combined_H
#include "../../common.h"
#include "../../Framework/modele.h"
#include "../namesThymus.h"


#define ReducedParams


struct modele3MultiDiv : public Modele {
    modele3MultiDiv();
    enum{

        // 0 ---------------- The evil Flu
        flu,
        // MAnesso
        tDN1s, tDN2,
        // T Vaslin for DN and DP
        DN34TS,
        DNtot,
        eDPtot,
        lDP,
        DPtot,

        // Thomas-Vaslin for SP4 and SP8
        SP4totTV,
        SP8totTV,

        // ODE for SP4 and SP8 and Tregs
        tSP8, tSP4,
        tTconv, tTRegP25, tTRegPFp3, tTreg,
        ttotal,


        // Main variables

        // 1 ---------------- Parameters for DN1->DN4 (manesso 2009 Interface)
        // Manesso
        tPreDN1,
        //tDN1s, tDN2,
        tDN1g0, tDN1g1, tDN1g2, tDN1g3, tDN1g4, tDN1g5, tDN1g6, tDN1g7, tDN1g8, tDN1g9, tDN1g10, tDN1g11,//        tDN1g12, tDN1g13, tDN1g14, tDN1g15,
        tDN3, tDN4,

#ifdef ReducedParams
        //floDN1to2, floDN2to3, floDN3to4, flowDN4toDP,
        fracInPreDN1, fracInDN1, fracInDN2, fracInDN3, fracInDN4,
        fracInDN1New, fracInDN2New, fracInDN34New,
#endif

        // 2 ---------------- Parameters for eDP and lateDP (Thomas-Vaslin 2007 JI)
        // Thomas-vaslin
        /*DN34TS,
        DNtot,
        eDPtot,
        lDP,
        DPtot,*/
        divDNg0, divDNg1, divDNg2, divDNg3, divDNg4, divDNg5, divDNg6,
        eDPg0, eDPg1, eDPg2, eDPg3, eDPg4, eDPg5, eDPg6,
        divSP4g0, divSP4g1, divSP4g2,
        //restSP4,
        divSP8g0, divSP8g1, divSP8g2,
        //restSP8,
        //SP4totTV,
        //SP8totTV,
#ifdef ReducedParams
        floweDPtolDP,
        flowDPtoSP4,
        flowDPtoSP8,
        floweDPtoDead,
        flowlDPtoDead,
        flowSP4toDead,
        flowSP8toDead,
#endif

        // 3 ---------------- Parameters for Tconvs and Tregs
        //Model with Treg
        /*tSP8, tSP4,
        tTconv, tTRegP25, tTRegPFp3, tTreg,
        ttotal,*/
        tSP8RagN, tSP4RagN, tTconvRagN, tTregP1RagN, tTregP2RagN, tTregRagN,
        pctDN, pctDP, pctSP8, pctSP4, pctTconv, pctTRegP1, pctTRegP2, pctTreg,
        pctSP8RagN, pctSP4RagN, pctTconvRagN, pctTRegP1RagN, pctTRegP2RagN, pctTregRagN,
        stotal, sTconv, sTreg, sCD8, sBcells,
        sTconvRagN, sTregRagN, sCD8RagN,
        pcsTconv, pcsTreg, pcsCD8, pcsBcells,
        pcsTconvRagN, pcsTregRagN, pcsCD8RagN,


        NbVariables};
    enum{
        flu_peak,
        flu_std,
        fETP_tDN, // inflow

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

        NdivDN,
        pDN, dDN,
        NdivDP,
        peDP, deDP,
        prestDP, drestDP,
        diffDPtoSP4,
        diffDPtoSP8,
        pSP4, dSP4,
        pcConvLastGenSP4,
        NdivSP4,
        pSP8, dSP8,
        pcConvLastGenSP8,
        NdivSP8,

        ptTconv,
        dtTconv,
        out_tTconv,

        ptSP8,
        dtSP8,
        out_SP8,

        ftDP_tTregP25, // direct conversion to shieh precursors // can be set to 0
        ftDP_tTregFP3, // direct conversion to singer precursors

        ptTregP25, // prolif shieh
        ftTregP25_tDPTreg, // conversion shieh to Mature DPTregs
        dtTregP25,

        ptTregFP3, // prolif singer
        ftTregFP3_tDPTreg, // conversion singer to mature DPTregs
        dtTregFP3,


        ptDPTregs,
        dtDPTregs,
        out_tDPTregs,

        // useless
        ftDP_tTConv, // conversion from DP to Tconv
        ftDP_tSP8,
        out_tDP, // outflow of DP

        /*ptTregP25, // prolif shieh
        ftTregP25_tDPTreg, // conversion shieh to Mature DPTregs
        dtTregP25,*/
        out_tTregP25, // outflow of shieh put to zero

        /*ptTregFP3, // prolif singer
        ftTregFP3_tDPTreg, // conversion singer to mature DPTregs
        dtTregFP3,*/
        out_tTregFP3, // outflow of singer
        in_tTregPFp3,

        //ptDPTregs,
        //dtDPTregs,
        //out_tDPTregs,
        in_tDPTregs,

        //ptTconv,
        //dtTconv,
        //out_tTconv,
        in_tTconv,

        //ptSP8,
        //dtSP8,
        //out_SP8,
        in_SP8,

        fracTtoS,
        dsTconv, dsTreg, dsCD8, dsBcells,
        decayRag,

        // Hypotheses parameters
        //ReducedInflow,
        hypInflowCoeffETP,

        //MoreDeath,
        hypDeathCoeffDN,
        hypDeathCoeffDN1,
        hypDeathCoeffDN2,
        hypDeathCoeffDN3,
        hypDeathCoeffDN4,
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
        hypFasterCoeffProFP3,
        hypFasterCoeffPro25,
        hypFasterCoeffTconv,
        hypFasterCoeffSP8,

        //SpaceDependentOutput
        hypSpaceOutputCoeff,

        //ImpactProlifRates
        hypLessDivDN,
        hypLessDivDP,
        hypLessDivTregPro25,
        hypLessDivTregProFP3,
        hypLessDivDPTreg,
        hypLessDivTconv,
        hypLessDivCD8,

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

/* for excel:
 * fETP_tDN
ptDN
ftDN_tDP
ptDP
ftDP_tTConv
ftDP_tTregP25
ftDP_tTregFP3
ftDP_tSP8
out_tDP
ptTregP25
ftTregP25_tDPTreg
out_tTregP25
ptTregFP3
ftTregFP3_tDPTreg
out_tTregFP3
ptDPTregs
out_tDPTregs
in_tDPTregs
ptTconv
out_tTconv
in_tTconv
ptSP8
out_SP8
in_SP8
*/
