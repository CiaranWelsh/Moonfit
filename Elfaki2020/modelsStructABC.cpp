// -------------- ODE model for perturbed thymyus dynamcis -------------
//
// Author:      Philippe A. Robert (philippe [dot] robert [at] ens-lyon.org, 8th Feb. 2020
// Source:      gitlab.com/Moonfit/Balthyse
// References   [1] Robert, P., Jönsson, E and Meyer-Hermann, M MoonFit, a minimal interface for fitting ODE
//                  dynamical models, bridging simulation by experimentalists and customization by C++ programmers,
//                  BioRxiV 2018, https://doi.org/10.1101/281188
//              [2] Elfaki, Y. et al. Influenza A virus-induced thymic atrophy differentially affects conventional
//                  and regulatory T cell developmental dynamics. EJI 2020

#include "modelsStructABC.h"

modele6GenericTVaslin::modele6GenericTVaslin() : Model(NbVariables, NbParameters), background(Back::WT) {

    name = string("Generic DN + TVaslin + single ODEs");
# ifdef DPtoFp3Prec
    name = string("(DP->Fp3)") + name;
#endif
# ifdef DPto25Prec
    name = string("(DP->25), ") + name;
#endif

#ifndef DPtoFp3Prec
#ifndef DPto25Prec
    name = string("(Tconv->TregPrec)") + name;
#endif
#endif

#ifdef equalProlif
    name = string("EqualProlif+") + name;
#endif

#ifdef equalExportTregs
    name = string("EqualExpTregs+") + name;
#endif
#ifdef equalExportAll
    name = string("ExpAll+") + name;
#endif


    dt = 0.001;             // initial time step -> then it is adaptive
    print_every_dt = 0.1;   //every how many seconds it is plotting

    NmaxDN = divDNg30LastDiv - divDNg0 + 1;     // Number of generations simulated at max.
    DoProlifDN.clear();
    DoProlifDN.resize(NmaxDN, 0);               // coefficients fi for DN
    NmaxDP = eDPg10 - eDPg0 + 1;                // Number of generations simulated at max
    DoProlifDP.clear();
    DoProlifDP.resize(NmaxDP, 0);               // coefficients fi for DP

    names[flu] = "flu";
    names[DNtot] = "DNtot";
    names[eDPtot] = "eDPtot";
    names[lDP] = "lDP";
    names[DPtot] = "DPtot";
    names[tSP8P] = "tSP8P";
    names[tSP8P69N] = "tSP8CD69-";
    names[tSP4P] = "tSP4P";
    names[tSP4P69N] = "tSP4CD69-";
    names[tTconvP] = "tTconvP";
    names[tTRegP25P] = "tTRegP25P";
    names[tTRegPFp3P] = "tTRegPFp3P";
    names[tTregP] = "tTregP";
    names[tSP8RagN] = "tSP8RagN";
    names[tSP4RagN] = "tSP4RagN";
    names[tTconvRagN] = "tTconvRagN";
    names[tTregP1RagN] = "tTregP1RagN";
    names[tTregP2RagN] = "tTregP2RagN";
    names[tTregRagN] = "tTregRagN";
    names[tSP8tot] = "tSP8tot";
    names[tSP4tot] = "tSP4tot";
    names[tTconvtot] = "tTconvtot";
    names[tTregP1tot] = "tTregP1tot";
    names[tTregP2tot] = "tTregP2tot";
    names[tTregtot] = "tTregtot";
    names[ttotal] = "ttotal";
    for (int i = divDNg0; i <= divDNg30LastDiv; ++i) {
        std::stringstream res;
        res << "divDNg" << i - divDNg0;
        names[i] = res.str();
    }
    for (int i = eDPg0; i <= eDPg10; ++i) {
        std::stringstream res;
        res << "eDPg" << i - eDPg0;
        names[i] = res.str();
    }
    names[pctDN] = "pctDN";
    names[pctDP] = "pctDP";
    names[pctSP8] = "pctSP8";
    names[pctSP4] = "pctSP4";
    names[pctTconvtot] = "pctTconvtot";
    names[pctTRegP1tot] = "pctTRegP1tot";
    names[pctTRegP2tot] = "pctTRegP2tot";
    names[pctTregtot] = "pctTregtot";
    names[pctTconvP] = "pctTconvP";
    names[pctTRegP1P] = "pctTRegP1P";
    names[pctTRegP2P] = "pctTRegP2P";
    names[pctTregP] = "pctTregP";
    names[pctSP8RagN] = "pctSP8RagN";
    names[pctSP4RagN] = "pctSP4RagN";
    names[pctTconvRagN] = "pctTconvRagN";
    names[pctTRegP1RagN] = "pctTRegP1RagN";
    names[pctTRegP2RagN] = "pctTRegP2RagN";
    names[pctTregRagN] = "pctTregRagN";
    names[SP4totTV] = "SP4totTV";
    names[SP8totTV] = "SP8totTV";
    names[divSP4g0] = "divSP4g0";
    names[divSP4g1] = "divSP4g1";
    names[divSP4g2] = "divSP4g2";
    names[divSP8g0] = "divSP8g0";
    names[divSP8g1] = "divSP8g1";
    names[divSP8g2] = "divSP8g2";
    names[SP4stage69hi] = "SP4stage69hi";
    names[SP4stage69lo] = "SP4stage69lo";
    names[SP8stage69hi] = "SP8stage69hi";
    names[SP8stage69lo] = "SP8stage69lo";
    names[SP4tot2St] = "SP4tot2St";
    names[SP8tot2St] = "SP8tot2St";
    names[floweDNtoeDP] = "floweDNtoeDP";
    names[floweDPtolDP] = "floweDPtolDP";
    names[flowDPtoSP4] = "flowDPtoSP4";
    names[flowDPtoSP8] = "flowDPtoSP8";
    names[flowDPtoTconv] = "flowDPtoTconv";
    names[flowDPtoTregP1] = "flowDPtoTregP1";
    names[flowDPtoTregP2] = "flowDPtoTregP2";
    names[flowTregP1toTreg] = "flowTregP1toTreg";
    names[flowTregP2toTreg] = "flowTregP2toTreg";
    names[flowSP4toOut] = "flowSP4toOut";
    names[flowSP8toOut] = "flowSP8toOut";
    names[flowTregtoOut] = "flowTregtoOut";
    names[floweDPtoDead] = "floweDPtoDead";
    names[flowlDPtoDead] = "flowlDPtoDead";
    names[flowSP4toDead] = "flowSP4toDead";
    names[flowSP8toDead] = "flowSP8toDead";
    names[flowTconvtoDead] = "flowTconvtoDead";
    names[flowTregP1toDead] = "flowTregP1toDead";
    names[flowTregP2toDead] = "flowTregP2toDead";
    names[flowTregtoDead] = "flowTregtoDead";

    // the names of variables as written in the column names in the data file

    // a- non-redundant list of variables used for the cost
    extNames[DNtot] = "tDN";
    extNames[DPtot] = "tDP";
    extNames[tSP8P] = "tSP8P";
    extNames[tTconvP] = "tTconvP";
    extNames[tTRegP25P] = "tTregP1P";
    extNames[tTRegPFp3P] = "tTregP2P";
    extNames[tTregP] = "tTregP";
    extNames[pctDN] = "pctDN";
    extNames[pctDP] = "pctDP";
    extNames[pctSP8] = "pctSP8";
    extNames[pctSP4] = "pctSP4";
    extNames[pctTconvtot] = "pctTconvtot";
    extNames[pctTRegP1tot] = "pctTregP1tot";
    extNames[pctTRegP2tot] = "pctTregP2tot";
    extNames[pctTregtot] = "pctTregtot";

    // b- redundant variables are not given so they are not included in the cost
    //extNames[tSP4P] =	"tSP4P";
    //extNames[tSP8RagN] =	"tSP8RagN";
    //extNames[tSP4RagN] =	"tSP4RagN";
    //extNames[tTconvRagN] =	"tTconvRagN";
    //extNames[tTregP1RagN] =	G"tTregP1RagN";
    //extNames[tTregP2RagN] =	"tTregP2RagN";
    //extNames[tTregRagN] =	"tTregRagN";
    //extNames[tSP8tot] =	"tSP8tot";
    //extNames[tSP4tot] =	"tSP4tot";
    //extNames[tTconvtot] =	"tTconvtot";
    //extNames[tTregP1tot] =	"tTRegP1tot";
    //extNames[tTregP2tot] =	"tTRegP2tot";
    //extNames[tTregtot] =	"tTregtot";
    //extNames[ttotal] =	"ttotal";
    //extNames[pctTconvP] =	"pctTconvP";
    //extNames[pctTRegP1P] =	 "pctTregP1P";
    //extNames[pctTRegP2P] =	"pctTregP2P";
    //extNames[pctTregP] =	"pctTregP";
    //extNames[pctSP8RagN] =	 "pctSP8RagN";
    //extNames[pctSP4RagN] =	"pctSP4RagN";
    //extNames[pctTconvRagN] =	"pctTconvRagN";
    //extNames[pctTRegP1RagN] =	"pctTregP1RagN";
    //extNames[pctTRegP2RagN] =	"pctTregP2RagN";
    //extNames[pctTregRagN] =	"pctTregRagN";

    // Name of parameters

    paramNames[flu_peak] = "flu_peak";
    paramNames[flu_std] = "flu_std";
    paramNames[fETP_tDN] = "fETP_tDN";
    paramNames[NdivDN] = "NdivDN";
    paramNames[pDN] = "pDN";
    paramNames[dDN] = "dDN";
    paramNames[T_DN] = "T_DN";
    paramNames[NdivDP] = "NdivDP";
    paramNames[peDP] = "peDP";
    paramNames[deDP] = "deDP";
    paramNames[prestDP] = "prestDP";
    paramNames[drestDP] = "drestDP";
    paramNames[out_tDP] = "out_tDP";
    paramNames[diffDPtoSP4] = "diffDPtoSP4";
    paramNames[diffDPtoSP8] = "diffDPtoSP8";
    paramNames[ptTconv] = "ptTconv";
    paramNames[dtTconv] = "dtTconv";
    paramNames[diffSP4P69PosToNeg] = "diffSP4P69PosToNeg";
    paramNames[out_tTconv] = "out_tTconv";
    paramNames[ptSP8] = "ptSP8";
    paramNames[dtSP8] = "dtSP8";
    paramNames[diffSP8P69PosToNeg] = "diffSP8P69PosToNeg";
    paramNames[out_SP8] = "out_SP8";
#ifdef DPtoFp3Prec
    paramNames[ftDP_tTregFP3] = "ftDP_tTregFP3";
#else
    paramNames[ftDP_tTregFP3] =     "ftTcon_tTregFP3";
#endif
#ifdef DPto25Prec
    paramNames[ftDP_tTregP25] = "ftDP_tTregP25";
#else
    paramNames[ftDP_tTregP25] =     "ftTcon_tTregP25";
#endif
    paramNames[ptTregP25] = "ptTregP25";
    paramNames[ftTregP25_tDPTreg] = "ftTregP25_tDPTreg";
    paramNames[dtTregP25] = "dtTregP25";
    paramNames[ptTregFP3] = "ptTregFP3";
    paramNames[ftTregFP3_tDPTreg] = "ftTregFP3_tDPTreg";
    paramNames[dtTregFP3] = "dtTregFP3";
    paramNames[ptDPTregs] = "ptDPTregs";
    paramNames[dtDPTregs] = "dtDPTregs";
    paramNames[out_tDPTregs] = "out_tDPTregs";
    paramNames[NdivSP4] = "NdivSP4";
    paramNames[pSP4] = "pSP4";
    paramNames[dSP4] = "dSP4";
    paramNames[pcConvLastGenSP4] = "pcConvLastGenSP4";
    paramNames[NdivSP8] = "NdivSP8";
    paramNames[pSP8] = "pSP8";
    paramNames[dSP8] = "dSP8";
    paramNames[pcConvLastGenSP8] = "pcConvLastGenSP8";
    paramNames[out_tTregP25] = "out_tTregP25";
    paramNames[out_tTregFP3] = "out_tTregFP3";
    paramNames[fracTtoS] = "fracTtoS";
    paramNames[dsTconv] = "dsTconv";
    paramNames[dsTreg] = "dsTreg";
    paramNames[dsCD8] = "dsCD8";
    paramNames[dsBcells] = "dsBcells";
    paramNames[decayRag] = "decayRag";
    paramNames[hypInflowCoeffETP] = "hypInflowCoeffETP";
    paramNames[hypDeathCoeffDN] = "hypDeathCoeffDN";
    paramNames[hypDeathCoeffAddEarlyDP] = "hypDeathCoeffAddEarlyDP";
    paramNames[hypDeathCoeffDP] = "hypDeathCoeffDP";
    paramNames[hypDeathCoeffTconv] = "hypDeathCoeffTconv";
    paramNames[hypDeathCoeffProFp3] = "hypDeathCoeffProFp3";
    paramNames[hypDeathCoeffPro25] = "hypDeathCoeffPro25";
    paramNames[hypDeathCoeffDPTregs] = "hypDeathCoeffDPTregs";
    paramNames[hypDeathCoeffSP8] = "hypDeathCoeffSP8";
    paramNames[hypOutputCoeffOutDP] = "hypOutputCoeffOutDP";
    paramNames[hypOutputCoeffOutTconv] = "hypOutputCoeffOutTconv";
    paramNames[hypOutputCoeffOutDPTregs] = "hypOutputCoeffOutDPTregs";
    paramNames[hypOutputCoeffOutProFP3] = "hypOutputCoeffOutProFP3";
    paramNames[hypOutputCoeffOutPro25] = "hypOutputCoeffOutPro25";
    paramNames[hypOutputCoeffOutSP8] = "hypOutputCoeffOutSP8";
    paramNames[hypFasterCoeffDNtoDP] = "hypFasterCoeffDNtoDP";
    paramNames[hypFasterCoeffDPtolDP] = "hypFasterCoeffDPtolDP";
    paramNames[hypFasterCoeffProFP3] = "hypFasterCoeffProFP3";
    paramNames[hypFasterCoeffPro25] = "hypFasterCoeffPro25";
    paramNames[hypFasterCoeffTconv] = "hypFasterCoeffTconv";
    paramNames[hypFasterCoeffSP8] = "hypFasterCoeffSP8";
    paramNames[hypOutputCoeffDNtoDP] = "hypOutputCoeffDNtoDP";
    paramNames[hypSpeedDivDN] = "hypSpeedDivDN";
    paramNames[hypSpeedDivDP] = "hypSpeedDivDP";
    paramNames[hypSpeedDivTregPro25] = "hypSpeedDivTregPro25";
    paramNames[hypSpeedDivTregProFP3] = "hypSpeedDivTregProFP3";
    paramNames[hypSpeedDivDPTreg] = "hypSpeedDivDPTreg";
    paramNames[hypSpeedDivTconv] = "hypSpeedDivTconv";
    paramNames[hypSpeedDivCD8] = "hypSpeedDivCD8";
    paramNames[logisticThymus] = "logisticThymus";
    paramNames[logisticStrength] = "logisticStrength";


    paramLowBounds[flu_peak] = 5;
    paramUpBounds[flu_peak] = 15;
    paramLowBounds[flu_std] = 0.25;
    paramUpBounds[flu_std] = 10;
    paramLowBounds[fETP_tDN] = 0.00005;
    paramUpBounds[fETP_tDN] = 0.1;
    paramLowBounds[NdivDN] = 4.5;
    paramUpBounds[NdivDN] = 19;
    paramLowBounds[pDN] = 0.1;
    paramUpBounds[pDN] = 5;
    paramLowBounds[dDN] = 0.001;
    paramUpBounds[dDN] = 0.5;
    paramLowBounds[T_DN] = 0.3;
    paramUpBounds[T_DN] = 4;
    paramLowBounds[NdivDP] = 4;
    paramUpBounds[NdivDP] = 8;
    paramLowBounds[peDP] = 0.1;
    paramUpBounds[peDP] = 5;
    paramLowBounds[deDP] = 0.0001;
    paramUpBounds[deDP] = 0.8;
    paramLowBounds[prestDP] = 0.0001;
    paramUpBounds[prestDP] = 0.2;
    paramLowBounds[drestDP] = 0.01;
    paramUpBounds[drestDP] = 10;
    paramLowBounds[out_tDP] = 0.01;
    paramUpBounds[out_tDP] = 5;
    paramLowBounds[diffDPtoSP4] = 0.01;
    paramUpBounds[diffDPtoSP4] = 0.4;
    paramLowBounds[diffDPtoSP8] = 0.01;
    paramUpBounds[diffDPtoSP8] = 0.4;
    paramLowBounds[ptTconv] = 0.01;
    paramUpBounds[ptTconv] = 0.8;
    paramLowBounds[dtTconv] = 0.01;
    paramUpBounds[dtTconv] = 2;
    paramLowBounds[diffSP4P69PosToNeg] = 0.01;
    paramUpBounds[diffSP4P69PosToNeg] = 2;
    paramLowBounds[out_tTconv] = 0.005;
    paramUpBounds[out_tTconv] = 2;
    paramLowBounds[ptSP8] = 0.01;
    paramUpBounds[ptSP8] = 0.8;
    paramLowBounds[dtSP8] = 0.01;
    paramUpBounds[dtSP8] = 2;
    paramLowBounds[diffSP8P69PosToNeg] = 0.01;
    paramUpBounds[diffSP8P69PosToNeg] = 2;
    paramLowBounds[out_SP8] = 0.005;
    paramUpBounds[out_SP8] = 2;
    paramLowBounds[ftDP_tTregP25] = 0.0001;
    paramUpBounds[ftDP_tTregP25] = 0.01;
    paramLowBounds[ftDP_tTregFP3] = 0.0001;
    paramUpBounds[ftDP_tTregFP3] = 0.01;
    paramLowBounds[ptTregP25] = 0.001;
    paramUpBounds[ptTregP25] = 2;
    paramLowBounds[ftTregP25_tDPTreg] = 0.01;
    paramUpBounds[ftTregP25_tDPTreg] = 2;
    paramLowBounds[dtTregP25] = 0.01;
    paramUpBounds[dtTregP25] = 2;
    paramLowBounds[ptTregFP3] = 0.001;
    paramUpBounds[ptTregFP3] = 2;
    paramLowBounds[ftTregFP3_tDPTreg] = 0.01;
    paramUpBounds[ftTregFP3_tDPTreg] = 2;
    paramLowBounds[dtTregFP3] = 0.01;
    paramUpBounds[dtTregFP3] = 2;
    paramLowBounds[ptDPTregs] = 0.001;
    paramUpBounds[ptDPTregs] = 2;
    paramLowBounds[dtDPTregs] = 0.01;
    paramUpBounds[dtDPTregs] = 2;
    paramLowBounds[out_tDPTregs] = 0.005;
    paramUpBounds[out_tDPTregs] = 2;
    paramLowBounds[NdivSP4] = 1;
    paramUpBounds[NdivSP4] = 2;
    paramLowBounds[pSP4] = 0.01;
    paramUpBounds[pSP4] = 2;
    paramLowBounds[dSP4] = 0.01;
    paramUpBounds[dSP4] = 2;
    paramLowBounds[pcConvLastGenSP4] = 0.01;
    paramUpBounds[pcConvLastGenSP4] = 1;
    paramLowBounds[NdivSP8] = 1;
    paramUpBounds[NdivSP8] = 2;
    paramLowBounds[pSP8] = 0.01;
    paramUpBounds[pSP8] = 2;
    paramLowBounds[dSP8] = 0.01;
    paramUpBounds[dSP8] = 2;
    paramLowBounds[pcConvLastGenSP8] = 0.01;
    paramUpBounds[pcConvLastGenSP8] = 1;
    paramLowBounds[out_tTregP25] = 0.0001;
    paramUpBounds[out_tTregP25] = 0.1;
    paramLowBounds[out_tTregFP3] = 0.0001;
    paramUpBounds[out_tTregFP3] = 0.1;
    paramLowBounds[fracTtoS] = 0.1;
    paramUpBounds[fracTtoS] = 0.8;
    paramLowBounds[dsTconv] = 0.001;
    paramUpBounds[dsTconv] = 1;
    paramLowBounds[dsTreg] = 0.001;
    paramUpBounds[dsTreg] = 1;
    paramLowBounds[dsCD8] = 0.001;
    paramUpBounds[dsCD8] = 1;
    paramLowBounds[dsBcells] = 0.001;
    paramUpBounds[dsBcells] = 1;
    paramLowBounds[decayRag] = 0.2;
    paramUpBounds[decayRag] = 0.6;
    paramLowBounds[hypInflowCoeffETP] = 0.01;
    paramUpBounds[hypInflowCoeffETP] = 20;
    paramLowBounds[hypDeathCoeffDN] = 0.01;
    paramUpBounds[hypDeathCoeffDN] = 20;
    paramLowBounds[hypDeathCoeffAddEarlyDP] = 0.01;
    paramUpBounds[hypDeathCoeffAddEarlyDP] = 20;
    paramLowBounds[hypDeathCoeffDP] = 0.01;
    paramUpBounds[hypDeathCoeffDP] = 20;
    paramLowBounds[hypDeathCoeffTconv] = 0.01;
    paramUpBounds[hypDeathCoeffTconv] = 20;
    paramLowBounds[hypDeathCoeffProFp3] = 0.01;
    paramUpBounds[hypDeathCoeffProFp3] = 20;
    paramLowBounds[hypDeathCoeffPro25] = 0.01;
    paramUpBounds[hypDeathCoeffPro25] = 20;
    paramLowBounds[hypDeathCoeffDPTregs] = 0.01;
    paramUpBounds[hypDeathCoeffDPTregs] = 20;
    paramLowBounds[hypDeathCoeffSP8] = 0.01;
    paramUpBounds[hypDeathCoeffSP8] = 20;
    paramLowBounds[hypOutputCoeffOutDP] = 0.01;
    paramUpBounds[hypOutputCoeffOutDP] = 20;
    paramLowBounds[hypOutputCoeffOutTconv] = 0.01;
    paramUpBounds[hypOutputCoeffOutTconv] = 20;
    paramLowBounds[hypOutputCoeffOutDPTregs] = 0.01;
    paramUpBounds[hypOutputCoeffOutDPTregs] = 20;
    paramLowBounds[hypOutputCoeffOutProFP3] = 0.01;
    paramUpBounds[hypOutputCoeffOutProFP3] = 20;
    paramLowBounds[hypOutputCoeffOutPro25] = 0.01;
    paramUpBounds[hypOutputCoeffOutPro25] = 20;
    paramLowBounds[hypOutputCoeffOutSP8] = 0.01;
    paramUpBounds[hypOutputCoeffOutSP8] = 20;
    paramLowBounds[hypFasterCoeffDNtoDP] = 0.01;
    paramUpBounds[hypFasterCoeffDNtoDP] = 20;
    paramLowBounds[hypFasterCoeffDPtolDP] = 0.01;
    paramUpBounds[hypFasterCoeffDPtolDP] = 20;
    paramLowBounds[hypFasterCoeffProFP3] = 0.01;
    paramUpBounds[hypFasterCoeffProFP3] = 20;
    paramLowBounds[hypFasterCoeffPro25] = 0.01;
    paramUpBounds[hypFasterCoeffPro25] = 20;
    paramLowBounds[hypFasterCoeffTconv] = 0.01;
    paramUpBounds[hypFasterCoeffTconv] = 20;
    paramLowBounds[hypFasterCoeffSP8] = 0.01;
    paramUpBounds[hypFasterCoeffSP8] = 20;
    paramLowBounds[hypOutputCoeffDNtoDP] = 0.0001;
    paramUpBounds[hypOutputCoeffDNtoDP] = 0.5;
    paramLowBounds[hypSpeedDivDN] = 0.01;
    paramUpBounds[hypSpeedDivDN] = 20;
    paramLowBounds[hypSpeedDivDP] = 0.01;
    paramUpBounds[hypSpeedDivDP] = 20;
    paramLowBounds[hypSpeedDivTregPro25] = 0.01;
    paramUpBounds[hypSpeedDivTregPro25] = 20;
    paramLowBounds[hypSpeedDivTregProFP3] = 0.01;
    paramUpBounds[hypSpeedDivTregProFP3] = 20;
    paramLowBounds[hypSpeedDivDPTreg] = 0.01;
    paramUpBounds[hypSpeedDivDPTreg] = 20;
    paramLowBounds[hypSpeedDivTconv] = 0.01;
    paramUpBounds[hypSpeedDivTconv] = 20;
    paramLowBounds[hypSpeedDivCD8] = 0.01;
    paramUpBounds[hypSpeedDivCD8] = 20;
    paramLowBounds[logisticThymus] = 0.1;
    paramUpBounds[logisticThymus] = 500;
    paramLowBounds[logisticStrength] = 0.1;
    paramUpBounds[logisticStrength] = 10;
}

void modele6GenericTVaslin::setBaseParameters() {
    background = Back::WT;
    params.clear();     // to make sure they are all put to zero
    params.resize(NbParameters, 0.0);

    params[flu_peak] = 9;
    params[flu_std] = 0.9;
    params[fETP_tDN] = 0.00005;
    params[NdivDN] = 5.00328915;
    params[pDN] = 0.23;
    params[dDN] = 0.1;
    params[T_DN] = 0;    // derived
    params[NdivDP] = 5;
    params[peDP] = 4.5;
    params[deDP] = 0;
    params[prestDP] = 0;
    params[drestDP] = 0.37 * (1 - 0.01 - 0.06);
    params[out_tDP] = 0;
    params[diffDPtoSP4] = 0.37 * 0.06;
    params[diffDPtoSP8] = 0.37 * 0.01;
    params[ptTconv] = 0.23;
    params[dtTconv] = 0;
    params[diffSP4P69PosToNeg] = 0.25;
    params[out_tTconv] = 0.3;
    params[ptSP8] = 0.3;
    params[dtSP8] = 0.4;
    params[diffSP8P69PosToNeg] = 0.25;
    params[out_SP8] = 0.3;
    params[ftDP_tTregP25] = 0.00099;
    params[ftDP_tTregFP3] = 0.003;
    params[ptTregP25] = 0.9;
    params[ftTregP25_tDPTreg] = 0.7;
    params[dtTregP25] = 0.65;
    params[ptTregFP3] = 0.86;
    params[ftTregFP3_tDPTreg] = 0.8;
    params[dtTregFP3] = 0.6;
    params[ptDPTregs] = 0.0074;
    params[dtDPTregs] = 1.2;
    params[out_tDPTregs] = 0.02;
    params[NdivSP4] = 2;
    params[pSP4] = 0.23;
    params[dSP4] = 0;
    params[pcConvLastGenSP4] = 0.27;
    params[NdivSP8] = 2;
    params[pSP8] = 0.23;
    params[dSP8] = 0;
    params[pcConvLastGenSP8] = 0.05;
    params[out_tTregP25] = 0;
    params[out_tTregFP3] = 0;
    params[fracTtoS] = 0.5;
    params[dsTconv] = 0.03;
    params[dsTreg] = 0.03;
    params[dsCD8] = 0.03;
    params[dsBcells] = 0.03;
    params[decayRag] = 0.45;
    params[hypInflowCoeffETP] = 1;
    params[hypDeathCoeffDN] = 1;
    params[hypDeathCoeffAddEarlyDP] = 0;
    params[hypDeathCoeffDP] = 1;
    params[hypDeathCoeffTconv] = 1;
    params[hypDeathCoeffProFp3] = 1;
    params[hypDeathCoeffPro25] = 1;
    params[hypDeathCoeffDPTregs] = 1;
    params[hypDeathCoeffSP8] = 1;
    params[hypOutputCoeffOutDP] = 0;
    params[hypOutputCoeffOutTconv] = 1;
    params[hypOutputCoeffOutDPTregs] = 1;
    params[hypOutputCoeffOutProFP3] = 1;
    params[hypOutputCoeffOutPro25] = 1;
    params[hypOutputCoeffOutSP8] = 1;
    params[hypFasterCoeffDNtoDP] = 1;
    params[hypFasterCoeffDPtolDP] = 1;
    params[hypFasterCoeffProFP3] = 1;
    params[hypFasterCoeffPro25] = 1;
    params[hypFasterCoeffTconv] = 1;
    params[hypFasterCoeffSP8] = 1;
    params[hypOutputCoeffDNtoDP] = 0;
    params[hypSpeedDivDN] = 1;
    params[hypSpeedDivDP] = 1;
    params[hypSpeedDivTregPro25] = 1;
    params[hypSpeedDivTregProFP3] = 1;
    params[hypSpeedDivDPTreg] = 1;
    params[hypSpeedDivTconv] = 1;
    params[hypSpeedDivCD8] = 1;
    params[logisticThymus] = 90;
    params[logisticStrength] = 2;

    setBaseParametersDone();
}

void modele6GenericTVaslin::calculateParameters(double xFlu) {

    InflowCoeffETP = 1;
    DeathCoeffDN = 1;
    DeathCoeffDP = 1;
    DeathCoeffTconv = 1;
    DeathCoeffProFp3 = 1;
    DeathCoeffPro25 = 1;
    DeathCoeffDPTregs = 1;
    DeathCoeffSP8 = 1;
    DeathCoeffEarlyDP = 0; // attention !
    OutputCoeffOutDP = 0;
    OutputCoeffOutTconv = 1;
    OutputCoeffOutDPTregs = 1;
    OutputCoeffOutProFP3 = 1;
    OutputCoeffOutPro25 = 1;
    OutputCoeffOutSP8 = 1;
    LessDivisionsDN = 1;
    FasterCoeffProFP3 = 1;
    FasterCoeffPro25 = 1;
    FasterCoeffTconv = 1;
    FasterCoeffSP8 = 1;
    OutputCoeffDNtoDP = 1;
    SpaceOutputCoeffAll = 1;
    LessProlifSpeedDN = 1;
    LessProlifSpeedDP = 1;
    LessProlifSpeedTregPro25 = 1;
    LessProlifSpeedTregProFP3 = 1;
    LessProlifSpeedDPTreg = 1;
    LessProlifSpeedTconv = 1;
    LessProlifSpeedCD8 = 1;

    if (background & Back::B_ReducedInflow) {
        InflowCoeffETP = 1 * (1 - xFlu) + xFlu * params[hypInflowCoeffETP];
    }
    if (background & Back::B_MoreDeath) {
        DeathCoeffDN = 1 * (1 - xFlu) + xFlu * params[hypDeathCoeffDN];
        DeathCoeffDP = 1 * (1 - xFlu) + xFlu * params[hypDeathCoeffDP];
        DeathCoeffTconv = 1 * (1 - xFlu) + xFlu * params[hypDeathCoeffTconv];
        DeathCoeffProFp3 = 1 * (1 - xFlu) + xFlu * params[hypDeathCoeffProFp3];
        DeathCoeffPro25 = 1 * (1 - xFlu) + xFlu * params[hypDeathCoeffPro25];
        DeathCoeffDPTregs = 1 * (1 - xFlu) + xFlu * params[hypDeathCoeffDPTregs];
        DeathCoeffSP8 = 1 * (1 - xFlu) + xFlu * params[hypDeathCoeffSP8];
        DeathCoeffEarlyDP = 0 * (1 - xFlu) + xFlu * params[hypDeathCoeffAddEarlyDP];
    }
    //Philippe: 02/07/2019, now decide all export are additive, to be fair between variables
    if (background & Back::B_MoreOutputThymus) {
        OutputCoeffDNtoDP = 0 * (1 - xFlu) + xFlu * params[hypOutputCoeffDNtoDP];
        OutputCoeffOutDP = 0 * (1 - xFlu) + xFlu * params[hypOutputCoeffOutDP];
        OutputCoeffOutTconv = /*1 * (1 - xFlu) */ +xFlu * params[hypOutputCoeffOutTconv];
        OutputCoeffOutDPTregs =/* 1 * (1 - xFlu)*/ +xFlu * params[hypOutputCoeffOutDPTregs];
        OutputCoeffOutProFP3 = 0 * (1 - xFlu) + xFlu * params[hypOutputCoeffOutProFP3];
        OutputCoeffOutPro25 = 0 * (1 - xFlu) + xFlu * params[hypOutputCoeffOutPro25];
        OutputCoeffOutSP8 = /* 1 * (1 - xFlu)*/ +xFlu * params[hypOutputCoeffOutSP8];
    }




    // concretely, that means less divisions so go faster to next!
    if (background & Back::B_FasterDifferentiation) {
        LessDivisionsDN = 1 * (1 - xFlu) + xFlu * params[hypFasterCoeffDNtoDP];
        LessDivisionsDP = 1 * (1 - xFlu) + xFlu * params[hypFasterCoeffDPtolDP];
        // For the other coefficients, it means faster coefficient of flow. Means faster conv towards this subset.
        FasterCoeffProFP3 = 1 * (1 - xFlu) + xFlu * params[hypFasterCoeffProFP3];
        FasterCoeffPro25 = 1 * (1 - xFlu) + xFlu * params[hypFasterCoeffPro25];
        FasterCoeffTconv = 1 * (1 - xFlu) + xFlu * params[hypFasterCoeffTconv];
        FasterCoeffSP8 = 1 * (1 - xFlu) + xFlu * params[hypFasterCoeffSP8];
    }
    if (background & Back::B_SpaceDependentOutput) {
        SpaceOutputCoeffAll = 1;
    }
    if (background & Back::B_DivisionReduced) {
        LessProlifSpeedDN = 1 * (1 - xFlu) + xFlu * params[hypSpeedDivDN];
        LessProlifSpeedDP = 1 * (1 - xFlu) + xFlu * params[hypSpeedDivDP];
        LessProlifSpeedTregPro25 = 1 * (1 - xFlu) + xFlu * params[hypSpeedDivTregPro25];
        LessProlifSpeedTregProFP3 = 1 * (1 - xFlu) + xFlu * params[hypSpeedDivTregProFP3];
        LessProlifSpeedDPTreg = 1 * (1 - xFlu) + xFlu * params[hypSpeedDivDPTreg],
                LessProlifSpeedTconv = 1 * (1 - xFlu) + xFlu * params[hypSpeedDivTconv];
        LessProlifSpeedCD8 = 1 * (1 - xFlu) + xFlu * params[hypSpeedDivCD8];
    }

    params[logisticStrength] = 1. / (1. - init[ttotal] / (params[logisticThymus] + 1e-9));
    double coeff = params[logisticStrength] * (1 - val[ttotal] / (params[logisticThymus] + 1e-9));
    LessDivisionsDP *= coeff;

    params[T_DN] = 1 / (std::max(params[pDN] + params[dDN], 1e-12));

    double dynamicNDivDN = std::min((double) NmaxDN + 0.9999999, LessDivisionsDN * params[NdivDN]);
    int N_DN = (int) dynamicNDivDN;
    divFloatDN = dynamicNDivDN - (double) N_DN;
    if (divFloatDN < 1e-12) { N_DN = std::max(0, N_DN - 1); }
    for (int i = 0; i <= N_DN - 1; ++i) { DoProlifDN[i] = 1.0; }
    for (int i = N_DN; i < NmaxDN; ++i) { DoProlifDN[i] = 0; }
    if (N_DN > 0) DoProlifDN[N_DN - 1] = divFloatDN;

    double dynamicNDivDP = std::min((double) NmaxDP + 0.9999999, LessDivisionsDP * params[NdivDP]);
    int NeDP = (int) dynamicNDivDP;
    divFloatDP = dynamicNDivDP - (double) NeDP;
    if (divFloatDP < 1e-12) { NeDP = std::max(0, NeDP - 1); }
    for (int i = 0; i <= NeDP - 1; ++i) { DoProlifDP[i] = 1.0; }
    for (int i = NeDP; i < NmaxDP; ++i) { DoProlifDP[i] = 0; }
    if (NeDP > 0) DoProlifDP[NeDP - 1] = divFloatDP;
}

// Important: only by using 'start by steady state', will the proliferation rates be calculated
// so when using experiments, make sure that the first experiment is from steady state to get good parameters !!
void modele6GenericTVaslin::initialise(long long _background) { // don't touch to parameters !
    background = _background;


    val.clear();
    val.resize(NbVariables, 0.0);
    init.clear();
    init.resize(NbVariables, 0.0);

    // Calculates the values of division coefficients (and dynamic coefficients put at 1 because xFlu = 0)
    calculateParameters();

    // Now constraints on the death rate,
    // 1/ CD25+ Progenitors die 3.7x more than Foxp3+ Progenitors
    // 2/ Mature Tregs die more or less the same as Foxp3+ progenitors
    params[dtDPTregs] = 1.9 * params[dtTconv];  // data from Plaza: Foxp3+ cells die 1.9 times more than Tconvs
    params[dtTregFP3] = 1.9 * params[dtTconv];
    params[dtTregP25] = 3.67 * params[dtDPTregs];

#ifdef equalProlif
    params[hypDeathCoeffDPTregs] =  params[hypDeathCoeffTconv];
    params[hypDeathCoeffPro25] =    params[hypDeathCoeffTconv];
    params[hypDeathCoeffProFp3] =   params[hypDeathCoeffTconv];
#endif

#ifdef equalExportAll
    params[hypOutputCoeffOutDPTregs] = params[hypOutputCoeffOutTconv];
    params[hypOutputCoeffOutPro25] = params[hypOutputCoeffOutTconv];
    params[hypOutputCoeffOutProFP3] = params[hypOutputCoeffOutTconv];
    params[hypOutputCoeffOutSP8] = params[hypOutputCoeffOutTconv];
#endif
#ifdef equalExportTregs
    params[hypOutputCoeffOutPro25] = params[hypOutputCoeffOutDPTregs];
    params[hypOutputCoeffOutProFP3] = params[hypOutputCoeffOutDPTregs];
#endif

#ifdef equalExportSP4SP8
    params[hypOutputCoeffOutSP8] = params[hypOutputCoeffOutTconv];
#endif

    if (background & Back::B_StartSteadyState) {

        if (params[NdivDN] < 1e-12)
            std::cout << "ERR: you use a multi-generation model for DNs and chose NdivDN =0. Cannot simulate that ... \n"
                 << std::endl;
        if (params[NdivDP] < 1e-12)
            std::cout << "ERR: you use a multi-generation model for DPs and chose NdivDP =0. Cannot simulate that ... \n"
                 << std::endl;

        double InflowToDN = params[fETP_tDN];
        init[divDNg0] = InflowToDN / (std::max((params[pDN] /*+ params[dDN]*/), 1e-12));
        for (int i = 1; i < std::min(12, NmaxDN); ++i) {
            // here, no death, so p = 1/T
            init[divDNg0 + i] = 2 * init[divDNg0 + i - 1] * DoProlifDN[i -
                                                                       1];// /* * (params[pDN])*/ / (max(1e-12, /*params[pDN] +*/ params[T_DN] * params[dDN]));
        }
        for (int i = 12; i < NmaxDN; ++i) {
            init[divDNg0 + i] = 2 * init[divDNg0 + i - 1] * DoProlifDN[i - 1] * (params[pDN]) /
                                (std::max(1e-12, params[pDN] + params[dDN]));
        }

        double outflowToDP = 0;
        for (int i = 0; i < NmaxDN; ++i) {
            outflowToDP +=
                    2 * (1 - DoProlifDN[i]) * params[pDN] * init[divDNg0 + i]; // No 2 here, they do not divide ??
        }

        init[eDPg0] = outflowToDP / (std::max((params[peDP] + params[deDP]), 1e-12));
        for (int i = 1; i < NmaxDP; ++i) {
            init[eDPg0 + i] = 2 * init[eDPg0 + i - 1] * DoProlifDP[i - 1] * (params[peDP]) /
                              (std::max(1e-12, params[peDP] + params[deDP]));
        }

        double outflowTolateDP = 0;
        for (int i = 0; i < NmaxDP; ++i) {
            outflowTolateDP +=
                    2 * (1 - DoProlifDP[i]) * params[peDP] * init[eDPg0 + i]; // No 2 here, they do not divide ??
        }

        double denominator = params[prestDP] + params[drestDP] + params[diffDPtoSP4] + params[diffDPtoSP8];
#ifdef DPtoFp3Prec
        denominator += params[ftDP_tTregFP3];
#endif
#ifdef DPto25Prec
        denominator += params[ftDP_tTregP25];
#endif
        init[lDP] = outflowTolateDP / (std::max(1e-12, denominator));

        //init[ lDP] = outflowTolateDP / (max(1e-12, params[prestDP] + params[drestDP] + params[diffDPtoSP4] + params[diffDPtoSP8] + params[ftDP_tTregP25] + params[ftDP_tTregFP3]));
        //init[ lDP] = outflowTolateDP / (max(1e-12, params[prestDP] + params[drestDP] + params[diffDPtoSP4] + params[diffDPtoSP8])); //  40.29;


        // original code for TVaslin
        //        double fastDiv = 100;
        //        init[ eDPg0] = outflowToDP /  (max(1e-12, params[peDP] + params[deDP]));  //0.07;
        //        init[ eDPg1] = 2*init[eDPg0] * params[peDP] / (max(1e-12, params[peDP] + params[deDP]));  // 0.14;
        //        init[ eDPg2] = 2*init[eDPg1] * params[peDP] / (max(1e-12, params[peDP] + params[deDP]));  // 0.29;
        //        init[ eDPg3] = 2*init[eDPg2] * params[peDP] / (max(1e-12, params[peDP] + params[deDP]));  // 0.58;
        //        init[ eDPg4] = 2*init[eDPg3] * params[peDP] / (max(1e-12, params[peDP] + params[deDP]));  //1.16;
        //        init[ eDPg5] = 2*init[eDPg4] * params[peDP] / (max(1e-12, params[peDP] + params[deDP] + (4.5*(- 1 + 2*1.1397 /0.94))));  //0.94;
        //        init[ eDPg6] = 2*init[eDPg5] * params[peDP] / (max(1e-12, params[peDP] + params[deDP] + fastDiv));  // 0.08;
        //        init[ lDP] = (fastDiv *  init[ eDPg6] + (4.5*(- 1 + 2*1.1397 /0.94)) * init[eDPg5]   + 2 * params[peDP] * init[eDPg6]) / (max(1e-12, params[prestDP] + params[drestDP] + params[diffDPtoSP4] + params[diffDPtoSP8])); //  40.29;

        init[divSP4g0] = (params[diffDPtoSP4] * init[lDP]) / (+params[pSP4] + params[dSP4]);
        init[divSP4g1] =
                (2 * params[pSP4] * init[divSP4g0]) / (+params[pSP4] + params[dSP4] + params[pcConvLastGenSP4]);
        init[divSP4g2] = (2 * params[pSP4] * init[divSP4g1]) / (+params[dSP4] + 100);
        init[divSP8g0] = (params[diffDPtoSP8] * init[lDP]) / (+params[pSP8] + params[dSP8]);
        init[divSP8g1] =
                (2 * params[pSP8] * init[divSP8g0]) / (+params[pSP8] + params[dSP8] + params[pcConvLastGenSP8]);
        init[divSP8g2] = (2 * params[pSP8] * init[divSP8g1]) / (+params[pSP8] + params[dSP8] + 100);


        init[tSP8P] = 2.787;
        //init[	tSP4P	] = 	derived	;
        init[tTconvP] = 8.387;
        init[tTRegP25P] = 0.04793;
        init[tTRegPFp3P] = 0.142;
        init[tTregP] = 0.121;
        init[tSP8RagN] = 0.229;
        //init[	tSP4RagN	] = 	derived	;
        init[tTconvRagN] = 0.4292;
        init[tTregP1RagN] = 0.002348;
        init[tTregP2RagN] = 0.03896;
        init[tTregRagN] = 0.07389;

        // only done the first time (steady state). The second experiment will reuse the parameter values

        params[ptTconv] = -(init[lDP] * params[diffDPtoSP4]) / init[tTconvP] + params[out_tTconv] + params[dtTconv];
#ifndef DPtoFp3Prec
        params[ptTconv] += params[ftDP_tTregFP3];
#endif
#ifndef DPto25Prec
        params[ptTconv] += params[ftDP_tTregP25];
#endif

#ifdef DPtoFp3Prec
        params[ptTregFP3] = (-init[lDP] * params[ftDP_tTregFP3]) / init[tTRegPFp3P] + params[out_tTregFP3] +
                            params[ftTregFP3_tDPTreg] + params[dtTregFP3];
#else
        params[ptTregFP3] = ( - init[tTconvP] * params[ftDP_tTregFP3]) / init[tTRegPFp3P] + params[out_tTregFP3] + params[ftTregFP3_tDPTreg] + params[dtTregFP3];
#endif

#ifdef DPto25Prec
        params[ptTregP25] = -init[lDP] * params[ftDP_tTregP25] / init[tTRegP25P] + params[out_tTregP25] +
                            params[ftTregP25_tDPTreg] + params[dtTregP25];
#else
        params[ptTregP25] = - init[tTconvP] * params[ftDP_tTregP25] / init[tTRegP25P]  + params[out_tTregP25] + params[ftTregP25_tDPTreg] + params[dtTregP25];
#endif

        params[ptDPTregs] =
                (-init[tTRegP25P] * params[ftTregP25_tDPTreg] - init[tTRegPFp3P] * params[ftTregFP3_tDPTreg]) /
                init[tTregP] +
                params[out_tDPTregs] + params[dtDPTregs];
        params[ptSP8] = (-init[lDP] * params[diffDPtoSP8]) / init[tSP8P] +
                        params[out_SP8] + params[dtSP8];

        //
        //params[ptTconv] = -(init[lDP]  * params[diffDPtoSP4]) / init[tTconvP] + params[out_tTconv]  + params[dtTconv];
        //params[ptTconv] = -(init[lDP]  * params[diffDPtoSP4]) / init[tTconvP] + params[out_tTconv]  + params[dtTconv] + params[ftDP_tTregP25] + params[ftDP_tTregFP3]; // OK
        //

        double SteadySP4stage69hi = 0.6 * init[tTconvP];
        double SteadySP4stage69lo = 0.4 * init[tTconvP];
        double SteadySP8stage69hi = 0.6 * init[tSP8P];
        double SteadySP8stage69lo = 0.4 * init[tSP8P];

        init[SP4stage69hi] = SteadySP4stage69hi;
        init[SP4stage69lo] = SteadySP4stage69lo;
        init[SP8stage69hi] = SteadySP8stage69hi;
        init[SP8stage69lo] = SteadySP8stage69lo;

        //params[ptTconv] = params[dtTconv] - (init[lDP]  * params[diffDPtoSP4] - params[out_tTconv] * SteadySP4stage69lo) / (SteadySP4stage69hi + SteadySP4stage69lo);
        //params[ptSP8]   = params[dtSP8]   - (init[lDP]  * params[diffDPtoSP8] - params[out_SP8]    * SteadySP8stage69lo) / (SteadySP8stage69hi + SteadySP8stage69lo);

        params[diffSP4P69PosToNeg] =
                +params[ptTconv] + init[lDP] * params[diffDPtoSP4] / SteadySP4stage69hi - params[dtTconv];
        //params[ptTconv] = - x[SP4stage69hi] * params[diffSP4P69PosToNeg] / SteadySP4stage69lo + params[out_tTconv] + params[dtTconv];
        params[diffSP8P69PosToNeg] =
                +params[ptSP8] + init[lDP] * params[diffDPtoSP8] / SteadySP8stage69hi - params[dtSP8];
        //params[ptSP8] = - x[SP8stage69hi] * params[diffSP8P69PosToNeg]     / SteadySP8stage69lo  +   params[out_tTconv] + params[dtTconv] ;
    }

    //if(background == Back::M2){}

    if (params[ptTconv] < 0) {
        //std::cerr << "ERR: the initial conditions + parameters don't allow the parameter [ptTconv] to be positive / allow steady state" << std::endl;
        //std::cerr << "     Please, put params[ftDP_tTConv]) < " << (- params[in_tTconv] + init[tTconv] * params[out_tTconv] + params[dtTconv]) / init[tDP] << " instead of " << params[ftDP_tTConv] << std::endl;
        params[ptTconv] = 0;
    }

    if (params[ptTregP25] < 0) {
        //std::cerr << "ERR: the initial conditions + parameters don't allow the parameter [ptTregP25] to be positive / allow steady state" << std::endl;
        //std::cerr << "     Please, put params[ftDP_tTregP25] < " << init[tTRegP25] * (params[out_tTregP25] + params[ftTregP25_tDPTreg] + params[dtTregP25]) / init[tDP] << std::endl;
        params[ptTregP25] = 0;
    }

    if (params[ptTregFP3] < 0) {
        //std::cerr << "ERR: the initial conditions + parameters don't allow the parameter [ptTregP25] to be positive / allow steady state" << std::endl;
        //std::cerr << "     Please, put params[ftDP_tTregFP3] < " << init[tTRegPFp3] * (params[out_tTregFP3] + params[ftTregFP3_tDPTreg] + params[dtTregFP3]) /  init[tDP] << std::endl;
        params[ptTregFP3] = 0;
    }

    if (params[ptDPTregs] < 0) {
        //std::cerr << "ERR: the initial conditions + parameters don't allow the parameter [ptDPTregs] to be positive / allow steady state" << std::endl;
        /*params[ptDPTregs] = (- params[in_tDPTregs] - init[tTRegP25] * params[ftTregP25_tDPTreg] - init[tTRegPFp3] * params[ftTregFP3_tDPTreg]) / init[tDPTreg] +
                params[out_tDPTregs] + params[dtDPTregs];
        params[ptSP8] = (- params[in_SP8] -  init[tDP] * params[ftDP_tSP8]) / init[tSP8] +
                params[out_SP8] + params[dtSP8];*/
        params[ptDPTregs] = 0;
    }

    if (params[ptSP8] < 0) {
        //std::cerr << "ERR: the initial conditions + parameters don't allow the parameter [ptSP8] to be positive / allow steady state" << std::endl;
        params[ptSP8] = 0;
    }

    for (int i = 0; i < NbVariables; ++i) { val[i] = init[i]; }
    t = 0;

    init[ttotal] = 77.3;

    initialiseDone();
}


void modele6GenericTVaslin::updateDerivedVariables(double _t) {

    val[flu] = exp(-(_t - params[flu_peak]) * (_t - params[flu_peak]) / (params[flu_std] * params[flu_std]));

    // recalculates all time-dependent parameterss + nDiv and coefficients prolifDN[] and prolifDP[]
    calculateParameters(val[flu]);

    if (!over(DNtot)) {
        val[DNtot] = 0;
        for (int i = divDNg0; i < divDNg30LastDiv; ++i) {
            val[DNtot] += val[i];
        }
    }
    if (!over(eDPtot)) {
        val[eDPtot] = 0;
        for (int i = eDPg0; i < eDPg10; ++i) {
            val[eDPtot] += val[i];
        }
    }
    if (!over(DPtot)) val[DPtot] = val[eDPtot] + val[lDP];
    if (!over(tSP4P)) val[tSP4P] = val[tTconvP] + val[tTRegP25P] + val[tTRegPFp3P] + val[tTregP];
    if (!over(tSP4RagN)) val[tSP4RagN] = val[tTconvRagN] + val[tTregP1RagN] + val[tTregP2RagN] + val[tTregRagN];
    if (!over(tSP8tot)) val[tSP8tot] = val[tSP8P] + val[tSP8RagN];
    if (!over(tSP4tot)) val[tSP4tot] = val[tSP4P] + val[tSP4RagN];
    if (!over(tTconvtot)) val[tTconvtot] = val[tTconvP] + val[tTconvRagN];
    if (!over(tTregP1tot)) val[tTregP1tot] = val[tTRegP25P] + val[tTregP1RagN];
    if (!over(tTregP2tot)) val[tTregP2tot] = val[tTRegPFp3P] + val[tTregP2RagN];
    if (!over(tTregtot)) val[tTregtot] = val[tTregP] + val[tTregRagN];
    if (!over(ttotal)) val[ttotal] = val[DNtot] + val[DPtot] + val[tSP4tot] + val[tSP8tot];

    //val[pctSP8RagN] = 100 * std::min(1.0, val[] / max(1e-8, val[]));
    if (!over(pctDN)) val[pctDN] = 100 * std::min(1.0, val[DNtot] / std::max(1e-8, val[ttotal]));
    if (!over(pctDP)) val[pctDP] = 100 * std::min(1.0, val[DPtot] / std::max(1e-8, val[ttotal]));
    if (!over(pctSP8)) val[pctSP8] = 100 * std::min(1.0, val[tSP8tot] / std::max(1e-8, val[ttotal]));
    if (!over(pctSP4)) val[pctSP4] = 100 * std::min(1.0, val[tSP4tot] / std::max(1e-8, val[ttotal]));

    //val[tSP4tot] = val[SP4stage69hi] + val[SP4stage69lo]; /// CAREADAOIFHQNSNJKCJQLJ§§§§
    if (!over(pctTconvtot)) val[pctTconvtot] = 100 * std::min(1.0, val[tTconvtot] / std::max(1e-8, val[tSP4tot]));
    if (!over(pctTRegP1tot)) val[pctTRegP1tot] = 100 * std::min(1.0, val[tTregP1tot] / std::max(1e-8, val[tSP4tot]));
    if (!over(pctTRegP2tot)) val[pctTRegP2tot] = 100 * std::min(1.0, val[tTregP2tot] / std::max(1e-8, val[tSP4tot]));
    if (!over(pctTregtot)) val[pctTregtot] = 100 * std::min(1.0, val[tTregtot] / std::max(1e-8, val[tSP4tot]));

    if (!over(pctTconvP)) val[pctTconvP] = 100 * std::min(1.0, val[tTconvP] / std::max(1e-8, val[tSP4tot]));
    if (!over(pctTRegP1P)) val[pctTRegP1P] = 100 * std::min(1.0, val[tTRegP25P] / std::max(1e-8, val[tSP4tot]));
    if (!over(pctTRegP2P)) val[pctTRegP2P] = 100 * std::min(1.0, val[tTRegPFp3P] / std::max(1e-8, val[tSP4tot]));
    if (!over(pctTregP)) val[pctTregP] = 100 * std::min(1.0, val[tTregP] / std::max(1e-8, val[tSP4tot]));

    if (!over(pctSP8RagN)) val[pctSP8RagN] = 100 * std::min(1.0, val[tSP8RagN] / std::max(1e-8, val[tSP8tot]));
    if (!over(pctSP4RagN)) val[pctSP4RagN] = 100 * std::min(1.0, val[tSP4RagN] / std::max(1e-8, val[tSP4tot]));
    if (!over(pctTconvRagN)) val[pctTconvRagN] = 100 * std::min(1.0, val[tTconvRagN] / std::max(1e-8, val[tTconvtot]));
    if (!over(pctTRegP1RagN))val[pctTRegP1RagN] = 100 * std::min(1.0, val[tTregP1RagN] / std::max(1e-8, val[tTregP1tot]));
    if (!over(pctTRegP2RagN))val[pctTRegP2RagN] = 100 * std::min(1.0, val[tTregP2RagN] / std::max(1e-8, val[tTregP2tot]));
    if (!over(pctTregRagN)) val[pctTregRagN] = 100 * std::min(1.0, val[tTregRagN] / std::max(1e-8, val[tTregtot]));

    // Thomas-Vaslin
    if (!over(SP4totTV)) val[SP4totTV] = val[divSP4g0] + val[divSP4g1] + val[divSP4g2]; //+ val[restSP4];
    if (!over(SP8totTV)) val[SP8totTV] = val[divSP8g0] + val[divSP8g1] + val[divSP8g2]; //+ val[restSP8];

    if (!over(SP4tot2St)) val[SP4tot2St] = val[SP4stage69hi] + val[SP4stage69lo];
    if (!over(SP8tot2St)) val[SP8tot2St] = val[SP8stage69hi] + val[SP8stage69lo];

    double outflowToDP = 0;
    // The cells that are remaining in a compartment are still leaving the compartment (as they enter, they can still complete the cycle)
    for (int i = 0; i < NmaxDN; ++i) { // DO NOT REACH Nmax+1, there are only Nmax !!
        outflowToDP += OutputCoeffDNtoDP * val[divDNg0 + i];
        outflowToDP += 2 * (1 - DoProlifDN[i]) * params[pDN] * LessProlifSpeedDN *
                       val[divDNg0 + i]; // No 2 here, they do not divide ??
    }
    if (!over(floweDNtoeDP))val[floweDNtoeDP] = outflowToDP;

    double outflowTolateDP = 0;
    for (int i = 0; i < NmaxDP; ++i) {
        outflowTolateDP += 2 * (1 - DoProlifDP[i]) * params[peDP] * LessProlifSpeedDP *
                           val[eDPg0 + i]; // No 2 here, they do not divide ??
    }

    if (!over(floweDPtolDP)) val[floweDPtolDP] = outflowTolateDP;
    if (!over(flowDPtoSP8)) val[flowDPtoSP8] = params[diffDPtoSP8] * FasterCoeffSP8 * val[lDP];
    if (!over(flowDPtoTconv)) val[flowDPtoTconv] = params[diffDPtoSP4] * FasterCoeffTconv * val[lDP];
    if (!over(flowDPtoTregP1)) val[flowDPtoTregP1] = val[lDP] * FasterCoeffPro25 * params[ftDP_tTregP25];
    if (!over(flowDPtoTregP2)) val[flowDPtoTregP2] = val[lDP] * FasterCoeffProFP3 * params[ftDP_tTregFP3];
    if (!over(flowDPtoSP4)) val[flowDPtoSP4] = val[flowDPtoTconv] + val[flowDPtoTregP1] + val[flowDPtoTregP2];

    if (!over(flowTregP1toTreg)) val[flowTregP1toTreg] = val[tTRegP25P] * params[ftTregP25_tDPTreg];
    if (!over(flowTregP2toTreg)) val[flowTregP2toTreg] = val[tTRegPFp3P] * params[ftTregFP3_tDPTreg];
    if (!over(flowSP4toOut))
        val[flowSP4toOut] = val[tTconvP] * SpaceOutputCoeffAll * OutputCoeffOutTconv * params[out_tTconv];
    if (!over(flowSP8toOut)) val[flowSP8toOut] = val[tSP8P] * SpaceOutputCoeffAll * OutputCoeffOutSP8 * params[out_SP8];
    if (!over(flowTregtoOut))
        val[flowTregtoOut] = val[tTregP] * SpaceOutputCoeffAll * OutputCoeffOutDPTregs * params[out_tDPTregs];

    //for(int i = 0; i < NmaxDN; ++i){
    //        val[flowDNtoDead] 	=  - params[dDN] * DeathCoeffDN  *  val[divDNg0 + i];
    //}
    if (!over(floweDPtoDead)) {
        val[floweDPtoDead] = 0;
        for (int i = 0; i < NmaxDP; ++i) {
            val[floweDPtoDead] += params[deDP] * DeathCoeffDP * val[divDNg0 + i];
        }
    }
    if (!over(flowlDPtoDead)) val[flowlDPtoDead] = val[lDP] * params[drestDP] * DeathCoeffDP;
    if (!over(flowSP8toDead)) val[flowSP8toDead] = val[tSP8P] * DeathCoeffSP8 * params[dtSP8];
    if (!over(flowTconvtoDead)) val[flowTconvtoDead] = val[tTconvP] * DeathCoeffTconv * params[dtTconv];
    if (!over(flowTregP1toDead)) val[flowTregP1toDead] = val[tTRegP25P] * DeathCoeffPro25 * params[dtTregP25];
    if (!over(flowTregP2toDead)) val[flowTregP2toDead] = val[tTRegPFp3P] * DeathCoeffProFp3 * params[dtTregFP3];
    if (!over(flowTregtoDead)) val[flowTregtoDead] = val[tTregP] * DeathCoeffDPTregs * params[dtDPTregs];
    if (!over(flowSP4toDead))
        val[flowSP4toDead] = val[flowTconvtoDead] + val[flowTregP1toDead] + val[flowTregP2toDead] + val[flowTregtoDead];

    //    val[stotal] = val[sTconv] + val[sTreg] + val[sCD8] + val[sBcells];
    //    val[pcsTconv] = 100 * std::min(1.0, val[sTconv] / max(1e-8, val[stotal]));
    //    val[pcsTreg] = 100 * std::min(1.0, val[sTreg] / max(1e-8, val[stotal]));
    //    val[pcsCD8] = 100 * std::min(1.0, val[sCD8] / max(1e-8, val[stotal]));
    //    val[pcsBcells] = 100 * std::min(1.0, val[sBcells] / max(1e-8, val[stotal]));
    //    val[pcsCD8RagN] = 100 * std::min(1.0, val[sCD8RagN] / max(1e-8, val[sCD8]));
    //    val[pcsTregRagN] = 100 * std::min(1.0, val[sTregRagN] / max(1e-8, val[sTreg]));
    //    val[pcsTconvRagN] = 100 * std::min(1.0, val[sTconvRagN] / max(1e-8, val[sTconv]));
}

void modele6GenericTVaslin::derivatives(const vector<double> &x, vector<double> &dxdt, const double t) {

    double theEvilFlu = exp(-(t - params[flu_peak]) * (t - params[flu_peak]) / (params[flu_std] * params[flu_std]));

    // recalculates all time-dependent parameterss + nDiv and coefficients prolifDN[] and prolifDP[]
    calculateParameters(theEvilFlu);

    //double coeff = (1/(1 - init[ttotal] / (params[logisticStrength]+1e-9)))*(1 - ((1/(params[logisticStrength] + 1e-9))*x[ttotal] / (params[logisticThymus] + 1e-9)));
    //double coeff = (1/(1 - 1 / (params[logisticStrength]+1e-9)))*(1 - ((1/(params[logisticStrength] + 1e-9)) * (1 - x[ttotal] / (params[logisticThymus] + 1e-9)) / (1 - init[ttotal] / (params[logisticThymus] + 1e-9));
    //std::cout << t << " coeff " << init[ttotal] << std::endl;
    //if(background & Back::B_LogisticTotalProlif){
    //DeathCoeffDP /= coeff; // be sure calculate params is always called before
    /*        LessDivCoeffDN *= coeff;
    LessDivCoeffDP *= coeff;
    LessDivCoeffTregPro25 *= coeff;
    LessDivCoeffTregProFP3 *= coeff;
    LessDivCoeffDPTreg *= coeff;
    LessDivCoeffTconv *= coeff;
    LessDivCoeffCD8 *= coeff;*/
    //}
    //std::cout << t << " " << x[ttotal] << "  " << coeff << "  " << DeathCoeffDP << "\n";


    // Note: even if a population is not proliferating, it should still be simulated. Indeed, Ndiv can be dynamic, and it might be cells remaining in that stage.
    double InflowToDN = InflowCoeffETP * params[fETP_tDN];

    double increasedDeath = params[dDN] * (DeathCoeffDN -
                                           1.0); // this allows to increase the death of early DNs as much (in absolute) as it is increased inside late DNs

    if (!over(divDNg0)) {
        dxdt[divDNg0] = InflowToDN +
                        (-params[pDN] * LessProlifSpeedDN   /*- params[dDN] * DeathCoeffDN*/ - OutputCoeffDNtoDP -
                         increasedDeath) * x[divDNg0];
    }
    for (int i = 1; i < std::min(12, NmaxDN); ++i) {
        if (!over(divDNg0 + i)) {
            dxdt[divDNg0 + i] = 2 * DoProlifDN[i - 1] * (1. / params[T_DN]) /*params[pDN]*/ * LessProlifSpeedDN *
                                x[divDNg0 + i - 1] + (-(1. / params[T_DN]) /*params[pDN]*/ *
                                                      LessProlifSpeedDN  /*- params[dDN] * DeathCoeffDN*/ -
                                                      OutputCoeffDNtoDP - increasedDeath) * x[divDNg0 + i];
        }
    }
    for (int i = 12; i < NmaxDN; ++i) {
        if (!over(divDNg0 + i)) {
            dxdt[divDNg0 + i] = 2 * DoProlifDN[i - 1] * params[pDN] * LessProlifSpeedDN * x[divDNg0 + i - 1] +
                                (-params[pDN] * LessProlifSpeedDN - params[dDN] * DeathCoeffDN - OutputCoeffDNtoDP) *
                                x[divDNg0 + i];
        }
    }

    double outflowToDP = 0;
    // The cells that are remaining in a compartment are still leaving the compartment (as they enter, they can still complete the cycle)
    for (int i = 0; i < NmaxDN; ++i) { // DO NOT REACH Nmax+1, there are only Nmax !!
        outflowToDP += OutputCoeffDNtoDP * x[divDNg0 + i];
        outflowToDP += 2 * (1 - DoProlifDN[i]) * params[pDN] * LessProlifSpeedDN *
                       x[divDNg0 + i]; // No 2 here, they do not divide ??
    }


    if (!over(eDPg0)) {
        dxdt[eDPg0] = outflowToDP +
                      (-params[peDP] * LessProlifSpeedDP - params[deDP] - DeathCoeffEarlyDP - OutputCoeffOutDP) *
                      x[eDPg0];
    }
    for (int i = 1; i < NmaxDP; ++i) {
        if (!over(eDPg0 + i)) {
            dxdt[eDPg0 + i] = 2 * DoProlifDP[i - 1] * params[peDP] * LessProlifSpeedDP * x[eDPg0 + i - 1] +
                              (-params[peDP] * LessProlifSpeedDP - params[deDP] - DeathCoeffEarlyDP -
                               OutputCoeffOutDP) * x[eDPg0 + i];
        }
    }

    double outflowTolateDP = 0;
    for (int i = 0; i < NmaxDP; ++i) {
        outflowTolateDP += 2 * (1 - DoProlifDP[i]) * params[peDP] * LessProlifSpeedDP *
                           x[eDPg0 + i]; // No 2 here, they do not divide ??
    }

    double coeffEvoDP = -params[drestDP] * DeathCoeffDP - params[diffDPtoSP4] * FasterCoeffTconv -
                        params[diffDPtoSP8] * FasterCoeffSP8;
# ifdef DPtoFp3Prec
    coeffEvoDP += -FasterCoeffProFP3 * params[ftDP_tTregFP3];
#endif
# ifdef DPto25Prec
    coeffEvoDP += -FasterCoeffPro25 * params[ftDP_tTregP25];
#endif
    if (!over(lDP)) {
        dxdt[lDP] = outflowTolateDP + (coeffEvoDP) * x[lDP];
    }

    //# ifdef DPtoFp3Prec
    //#else
    //    if(!over(lDP)) {
    //        dxdt[lDP] 	= outflowTolateDP + (- params[drestDP] * DeathCoeffDP - params[diffDPtoSP4]* FasterCoeffTconv - params[diffDPtoSP8] * FasterCoeffSP8 ) * x[lDP];
    //    }
    //#endif

    // old code from Thomas-Vaslin
    //    double fastDiv = 100.0;
    //    // early (proliferating) and late (resting) DPs from thomas-Vaslin 2007 JI. Note: DN4 proliferation stays in DN4 and only commitment leads to DP.
    //    if(!over( eDPg0)) {
    //        dxdt[eDPg0] 	= /*params[commitDN4toDP] * x[tDN4]*/ outflowToDP + ( - params[peDP] * LessProlifSpeedDP - params[deDP] - DeathCoeffEarlyDP) * x[eDPg0];
    //    }
    //    if(!over( eDPg1)) {
    //        dxdt[eDPg1] 	= 2 * params[peDP] * LessProlifSpeedDP * x[eDPg0] + ( - params[peDP] * LessProlifSpeedDP - params[deDP] - DeathCoeffEarlyDP) * x[eDPg1];
    //    }
    //    if(!over( eDPg2)) {
    //        dxdt[eDPg2] 	= 2 * params[peDP] * LessProlifSpeedDP * x[eDPg1] + ( - params[peDP] * LessProlifSpeedDP - params[deDP] - DeathCoeffEarlyDP) * x[eDPg2];
    //    }
    //    if(!over( eDPg3)) {
    //        dxdt[eDPg3] 	= 2 * params[peDP] * LessProlifSpeedDP * x[eDPg2] + ( - params[peDP] * LessProlifSpeedDP - params[deDP] - DeathCoeffEarlyDP) * x[eDPg3];
    //    }
    //    if(!over( eDPg4)) {
    //        dxdt[eDPg4] 	= 2 * params[peDP] * LessProlifSpeedDP * x[eDPg3] + ( - params[peDP] * LessProlifSpeedDP - params[deDP] - DeathCoeffEarlyDP) * x[eDPg4];
    //    }
    //    if(!over( eDPg5)) {
    //        dxdt[eDPg5] 	= 2 * params[peDP] * LessProlifSpeedDP * x[eDPg4] + ( - (4.5*(- 1 + 2*1.1397 /0.94)) - params[peDP] * LessProlifSpeedDP - params[deDP] - DeathCoeffEarlyDP) * x[eDPg5]; // the coeffecient given by (alppha^n) is wrong. probably wrong rounfding up of 0.2^127. The formula here extracts the coefficient of outflow from table III in the JI paper 2007
    //    }
    //    if(!over( eDPg6)) {
    //        dxdt[eDPg6] 	= 2 * params[peDP] * LessProlifSpeedDP * x[eDPg5] + ( - params[peDP] * LessProlifSpeedDP - 100  - params[deDP] - DeathCoeffEarlyDP) * x[eDPg6];
    //    }
    //    if(!over( lDP)) {
    //        dxdt[lDP] 	= (4.5*(- 1 + 2*1.1397 /0.94)) * x[eDPg5] + fastDiv *  x[eDPg6] + 2*params[peDP] * LessProlifSpeedDP * x[eDPg6] + (- params[drestDP] * DeathCoeffDP - params[diffDPtoSP4]* FasterCoeffTconv - params[diffDPtoSP8] * FasterCoeffSP8) * x[lDP];
    //    }

    // If SP4 and SP8 are simulated by thomas-vaslin
    if (!over(divSP4g0)) {
        dxdt[divSP4g0] = params[diffDPtoSP4] * FasterCoeffTconv * x[lDP] +
                         (-params[pSP4] * LessProlifSpeedTconv - params[dSP4] * DeathCoeffTconv) * x[divSP4g0];
    }
    if (!over(divSP4g1)) {
        dxdt[divSP4g1] = 2 * params[pSP4] * x[divSP4g0] +
                         (-params[pSP4] * LessProlifSpeedTconv - params[dSP4] * DeathCoeffTconv -
                          params[pcConvLastGenSP4]) * x[divSP4g1];
    }
    if (!over(divSP4g2)) {
        dxdt[divSP4g2] =
                2 * params[pSP4] * x[divSP4g1] + (/* no prolif */  -params[dSP4] * DeathCoeffTconv - 100) * x[divSP4g2];
    }
    if (!over(divSP8g0)) {
        dxdt[divSP8g0] = params[diffDPtoSP8] * FasterCoeffSP8 * x[lDP] +
                         (-params[pSP8] * LessProlifSpeedCD8 - params[dSP8] * DeathCoeffSP8) * x[divSP8g0];
    }
    if (!over(divSP8g1)) {
        dxdt[divSP8g1] = 2 * params[pSP8] * x[divSP8g0] +
                         (-params[pSP8] * LessProlifSpeedCD8 - params[dSP8] * DeathCoeffSP8 -
                          params[pcConvLastGenSP8]) * x[divSP8g1];
    }
    if (!over(divSP8g2)) {
        dxdt[divSP8g2] = 2 * params[pSP8] * x[divSP8g1] +
                         (-params[pSP8] * LessProlifSpeedCD8 - params[dSP8] * DeathCoeffSP8 - 100) * x[divSP8g2];
    }

    // If SP4 and SP8 are simulated as t

    if (!over(SP4stage69hi)) {
        dxdt[SP4stage69hi] = x[lDP] * FasterCoeffTconv * params[diffDPtoSP4] + x[SP4stage69hi] *
                                                                               (-params[diffSP4P69PosToNeg] +
                                                                                LessProlifSpeedTconv * params[ptTconv] -
                                                                                DeathCoeffTconv * params[dtTconv]);
    }
    if (!over(SP4stage69lo)) {
        dxdt[SP4stage69lo] = x[SP4stage69hi] * params[diffSP4P69PosToNeg] + x[SP4stage69lo] * (-SpaceOutputCoeffAll *
                                                                                               (OutputCoeffOutTconv +
                                                                                                params[out_tTconv]) +
                                                                                               LessProlifSpeedTconv *
                                                                                               params[ptTconv] -
                                                                                               DeathCoeffTconv *
                                                                                               params[dtTconv]);
    }
    if (!over(SP8stage69hi)) {
        dxdt[SP8stage69hi] = x[lDP] * FasterCoeffTconv * params[diffDPtoSP8] + x[SP8stage69hi] *
                                                                               (-params[diffSP8P69PosToNeg] +
                                                                                LessProlifSpeedTconv * params[ptTconv] -
                                                                                DeathCoeffTconv * params[dtTconv]);
    }
    if (!over(SP8stage69lo)) {
        dxdt[SP8stage69lo] = x[SP8stage69hi] * params[diffSP8P69PosToNeg] + x[SP8stage69lo] * (-SpaceOutputCoeffAll *
                                                                                               (OutputCoeffOutTconv +
                                                                                                params[out_tTconv]) +
                                                                                               LessProlifSpeedTconv *
                                                                                               params[ptTconv] -
                                                                                               DeathCoeffTconv *
                                                                                               params[dtTconv]);
    }

    // If SP4 and SP8 are simulated as simple ODEs, just the RAG+ subset first
    if (!over(tSP8P)) {
        dxdt[tSP8P] = x[lDP] * FasterCoeffSP8 * params[diffDPtoSP8] + x[tSP8P] * (-SpaceOutputCoeffAll *
                                                                                  (OutputCoeffOutSP8 +
                                                                                   params[out_SP8]) /* changed here */        +
                                                                                  LessProlifSpeedCD8 * params[ptSP8] -
                                                                                  DeathCoeffSP8 * params[dtSP8]);
    }


#ifdef DPtoFp3Prec
    if (!over(tTRegPFp3P)) {
        dxdt[tTRegPFp3P] = x[lDP] * FasterCoeffProFP3 * params[ftDP_tTregFP3] + x[tTRegPFp3P] * (-SpaceOutputCoeffAll *
                                                                                                 OutputCoeffOutProFP3 *
                                                                                                 params[out_tTregFP3] +
                                                                                                 LessProlifSpeedTregProFP3 *
                                                                                                 params[ptTregFP3] -
                                                                                                 params[ftTregFP3_tDPTreg] -
                                                                                                 DeathCoeffProFp3 *
                                                                                                 params[dtTregFP3]);
    }
#else
    if(!over(tTRegPFp3P)) {
        dxdt[tTRegPFp3P] 	=   x[tTconvP] * FasterCoeffProFP3 * params[ftDP_tTregFP3]                                  + x[tTRegPFp3P] * ( - SpaceOutputCoeffAll * (OutputCoeffOutProFP3 + params[out_tTregFP3])    + LessProlifSpeedTregProFP3 * params[ptTregFP3] - params[ftTregFP3_tDPTreg]     - DeathCoeffProFp3 * params[dtTregFP3]);
    }
#endif

#ifdef DPto25Prec
    if (!over(tTRegP25P)) {
        dxdt[tTRegP25P] = x[lDP] * FasterCoeffPro25 * params[ftDP_tTregP25] + x[tTRegP25P] * (-SpaceOutputCoeffAll *
                                                                                              OutputCoeffOutPro25 *
                                                                                              params[out_tTregP25] +
                                                                                              LessProlifSpeedTregPro25 *
                                                                                              params[ptTregP25] -
                                                                                              params[ftTregP25_tDPTreg] -
                                                                                              DeathCoeffPro25 *
                                                                                              params[dtTregP25]);
    }
#else
    if(!over(tTRegP25P)) {       // changed here
        dxdt[tTRegP25P] 	=   x[tTconvP] * FasterCoeffPro25  * params[ftDP_tTregP25]                              + x[tTRegP25P] *  (- SpaceOutputCoeffAll * (OutputCoeffOutPro25 +   params[out_tTregP25])    + LessProlifSpeedTregPro25 * params[ptTregP25] - params[ftTregP25_tDPTreg]      - DeathCoeffPro25 * params[dtTregP25]);
    }
#endif

    double coeffEvoTconv =
            -SpaceOutputCoeffAll * (OutputCoeffOutTconv + params[out_tTconv]) + LessProlifSpeedTconv * params[ptTconv] -
            DeathCoeffTconv * params[dtTconv];
#ifndef DPtoFp3Prec
    coeffEvoTconv += -FasterCoeffProFP3 * params[ftDP_tTregFP3];
#endif
#ifndef DPto25Prec
    coeffEvoTconv += - FasterCoeffPro25  * params[ftDP_tTregP25] ;
#endif
    if (!over(tTconvP)) {
        dxdt[tTconvP] = x[lDP] * FasterCoeffTconv * params[diffDPtoSP4] + x[tTconvP] * (coeffEvoTconv);
    }

    if (!over(tTregP)) {
        dxdt[tTregP] = x[tTRegP25P] * params[ftTregP25_tDPTreg] + x[tTRegPFp3P] * params[ftTregFP3_tDPTreg] +
                       x[tTregP] * (-SpaceOutputCoeffAll * (OutputCoeffOutDPTregs + params[out_tDPTregs]) +
                                    LessProlifSpeedDPTreg * params[ptDPTregs] - DeathCoeffDPTregs * params[dtDPTregs]);
    }

    // Careful, make the rag- as an exit the pool of Rag+
    if (!over(tTconvRagN)) {
        dxdt[tTconvRagN] = 0;
    }
    if (!over(tTregP1RagN)) {
        dxdt[tTregP1RagN] = 0;
    }
    if (!over(tTregP2RagN)) {
        dxdt[tTregP2RagN] = 0;
    }
    if (!over(tTregRagN)) {
        dxdt[tTregRagN] = 0;
    }
    if (!over(tSP8RagN)) {
        dxdt[tSP8RagN] = 0;
    }
}

/*if(background == Back::WT){}
 if(background == Back::B_ReducedInflow){}
 if(background == Back::B_MoreDeath){}
 if(background == Back::B_MoreOutputThymus){}
 if(background == Back::B_FasterDifferentiation){}
 if(background == Back::B_SpaceDependentOutput){}
 if(background == Back::B_DivisionReduced){}
 if(background == Back::B_AllCombined){}*/


