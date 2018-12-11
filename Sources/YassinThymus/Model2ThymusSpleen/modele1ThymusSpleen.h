// ------- Automatically generated model -------- //
#ifndef modele1ThymusSpl_H
#define modele1ThymusSpl_H
#include "../../common.h"
#include "../../Framework/modele.h"
#include "../namesThymus.h"




struct modele1ThymusSpleen : public Modele {
    modele1ThymusSpleen();
    enum{
        flu,
        ttotal, tDN, tDP, tSP8, tSP4, tTconv, tTRegP25, tTRegPFp3, tTreg,
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

        ptDN, // prolif DN4 prolif a lot.
        ftDN_tDP, // conversion DN to DP
        dtDN,

        ptDP, // should be low
        ftDP_tTConv, // conversion from DP to Tconv
        ftDP_tTregP25, // direct conversion to shieh precursors // can be set to 0
        ftDP_tTregFP3, // direct conversion to singer precursors
        ftDP_tSP8,
        dtDP,
        out_tDP, // outflow of DP

        ptTregP25, // prolif shieh
        ftTregP25_tDPTreg, // conversion shieh to Mature DPTregs
        dtTregP25,
        out_tTregP25, // outflow of shieh put to zero

        ptTregFP3, // prolif singer
        ftTregFP3_tDPTreg, // conversion singer to mature DPTregs
        dtTregFP3,
        out_tTregFP3, // outflow of singer
        in_tTregPFp3,

        ptDPTregs,
        dtDPTregs,
        out_tDPTregs,
        in_tDPTregs,

        ptTconv,
        dtTconv,
        out_tTconv,
        in_tTconv,

        ptSP8,
        dtSP8,
        out_SP8,
        in_SP8,

        fracTtoS,
        dsTconv, dsTreg, dsCD8, dsBcells,
        decayRag,

        // Hypotheses parameters
        //ReducedInflow,
        hypInflowCoeffETP,

        //MoreDeath,
        hypDeathCoeffDN,
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
