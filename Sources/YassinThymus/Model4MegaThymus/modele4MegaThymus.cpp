// 2018-12-16
// Changes: how to modify proliferation: number of divisions or staying longer (higher T) or dividing faster (lower T)

#include "modele4MegaThymus.h"

modele4MegaThymus::modele4MegaThymus() : Model(NbVariables, NbParameters), background(Back::WT) {
    name = string("modeleCombinedManesso-Vaslin-MultiGen");
    dt = 0.001; // initial time step -> then it is adaptive
    print_every_dt = 1200; //every how many seconds it is plotting

    // 0 ---------------- The evil Flu
    names[flu] = string("flu");

    // 1 ---------------- Parameters for DN1->DN4 (manesso 2009 Interface)
    names[tPreDN1]      = string("tPreDN1");
    for(int i = tDN1g0; i <= tDN1g11; ++i){ // to g15
        stringstream res; res << "tDN1g" <<  i - tDN1g0;
        names[i] = res.str();
    }
    names[tDN1s]        = string("tDN1s");
    names[tDN2]         = string("tDN2");
    names[tDN3]         = string("tDN3");
    names[tDN4]         = string("tDN4");

#ifdef ReducedParams
    // Analysis variables
   /* names[floDN1to2]    = string("floDN1to2");
    names[floDN2to3]    = string("floDN2to3");
    names[floDN3to4]    = string("floDN3to4");
    names[flowDN4toDP]  = string("flowDN4toDP");*/
    names[fracInPreDN1] = string("fracInPreDN1"); // Fraction of all injected + DN cells in all DN1-4
    names[fracInDN1]    = string("fracInDN1");
    names[fracInDN2]    = string("fracInDN2");
    names[fracInDN3]    = string("fracInDN3");
    names[fracInDN4]    = string("fracInDN4");
    names[fracInDN1New] = string("fracInDN1New");
    names[fracInDN2New] = string("fracInDN2New");
    names[fracInDN34New] = string("fracInDN34New");
#endif
    // 2 ---------------- Parameters for eDP and lateDP (Thomas-Vaslin 2007 JI)

    names[ divDNg0] = string("divDN3-4g0");
    names[ divDNg1] = string("divDN3-4g1");
    names[ divDNg2] = string("divDN3-4g2");
    names[ divDNg3] = string("divDN3-4g3");
    names[ divDNg4] = string("divDN3-4g4");
    names[ divDNg5] = string("divDN3-4g5");
    names[ divDNg6] = string("divDN3-4g6");
    names[ DN34TS] = string("DN34TS");
    names[ eDPg0] = string("eDPg0");
    names[ eDPg1] = string("eDPGg1");
    names[ eDPg2] = string("eDPg2");
    names[ eDPg3] = string("eDPg3");
    names[ eDPg4] = string("eDPg4");
    names[ eDPg5] = string("eDPg5");
    names[ eDPg6] = string("eDPg6");
    names[ lDP] = string("lDP");
    // If SP4 would be simulated by Thomas-Vaslin et al
    names[ divSP4g0] = string("divSP4g0");
    names[ divSP4g1] = string("divSP4g1");
    names[ divSP4g2] = string("divSP4g2");
    //names[ restSP4] = string("restSP4");
    names[ divSP8g0] = string("divSP8g0");
    names[ divSP8g1] = string("divSP8g1");
    names[ divSP8g2] = string("divSP8g2");
    //names[ restSP8] = string("restSP8");
    // Analysis variables
    names[ DNtot] = string("DNtot");
    names[ eDPtot] = string("eDPtot");
    names[ DPtot] = string("DPtot");
    names[ SP4totTV] = string("SP4tot");
    names[ SP8totTV] = string("SP8tot");
#ifdef ReducedParams
    names[ floweDPtolDP] = string("floweDPtolDP");
    names[ flowDPtoSP4] = string("flowDPtoSP4");
    names[ flowDPtoSP8] = string("flowDPtoSP8");
    names[ floweDPtoDead] = string("floweDPtoDead");
    names[ flowlDPtoDead] = string("flowlDPtoDead");
    names[ flowSP4toDead] = string("flowSP4toDead");
    names[ flowSP8toDead] = string("flowSP8toDead");
#endif

    // 3 ---------------- Parameters for Tconv and Tregs, re-simulating CD4 and CD8 with a simple 1-compartment ODE
    names[ttotal] = string("total thymocytes");
    names[tSP8] = string("thymic SP CD8");
    names[tSP4] = string("Thymic SP CD4");
    names[tTconv] = string("thymic Tconv");
    names[tTRegP25] = string("thymic 25+ progenitors (P1)");
    names[tTRegPFp3] = string("thymic Foxp3+ progenitors (P2)");
    names[tTreg] = string("thymic mature Tregs");
    names[tSP8RagN] = string("thymic SP8 Rag-");
    names[tSP4RagN] = string("thymic SP4 Rag-");
    names[tTconvRagN] = string("thymic Tconv Rag-");
    names[tTregP1RagN] = string("thymic Treg Progenitor 1 Rag- (CD25+)");
    names[tTregP2RagN] = string("thymic Treg Progenitor 2 Rag- (Fp3+)");
    names[tTregRagN] = string("thymic mature Treg Rag-");
    names[pctDN] =       string("% tDN / tot cells");
    names[pctDP] =       string("% tDP / tot cells");
    names[pctSP8] =      string("% tSP8 / tot cells");
    names[pctSP4] =      string("% tSP4 / tot cells");
    names[pctTconv] =   string("% tTconv / CD4");
    names[pctTRegP1] =  string("% tSinger Precursors (1) / CD4");
    names[pctTRegP2] =  string("% tFoxp3+ Precutsors (2) / CD4");
    names[pctTreg] = string("% mature tTregs / CD4");
    names[pctSP8RagN] = string("% Rag- in tSP8");
    names[pctSP4RagN] = string("% Rag- in tSP4");
    names[pctTconvRagN] = string("% Rag- in Tconv");
    names[pctTRegP1RagN] = string("% Rag- in tSinger Prec (1)");
    names[pctTRegP2RagN] = string("% Rag- in tFoxp3+ Prec (2)");
    names[pctTregRagN] = string("% Rag- in mature tTreg ");
    names[stotal] = string("total splenocytes");
    names[sTconv] = string("splenic Tconv");
    names[sTreg] = string("splenic Treg");
    names[sCD8] = string("splenic CD8");
    names[sBcells] = string("splenic B cells");
    names[sTconvRagN] = string("splenic Tconv Rag-");
    names[sTregRagN] = string("splenic Treg Rag-");
    names[sCD8RagN] = string("splenic CD8 Rag-");
    names[pcsTconv] = string("% Tconv in spleen");
    names[pcsTreg] = string("% Treg in spleen");
    names[pcsCD8] = string("% CD8 in spleen");
    names[pcsBcells] = string("% B cells in spleen");
    names[pcsTconvRagN] = string("% Rag- in splenic Tconv");
    names[pcsTregRagN] = string("% Rag- in splenic Treg");
    names[pcsCD8RagN] = string("% Rag- in CD8");


    // the names of variables that can be accessed by outside (global name-space)
    extNames[tDN1s] = GlobalName(N::tDN1);
    extNames[tDN2] = GlobalName(N::tDN2);
    extNames[tDN3] = GlobalName(N::tDN3);
    extNames[tDN4] = GlobalName(N::tDN4);

#ifdef ReducedParams
    //names[fracInPreDN1] = string("fracInPreDN1"); // Fraction of all injected + DN cells in all DN1-4
    extNames[fracInDN1]    = GlobalName(N::ProDN1Potritt);
    extNames[fracInDN2]    = GlobalName(N::ProDN2Potritt);
    extNames[fracInDN3]    = GlobalName(N::ProDN3Potritt);
    extNames[fracInDN4]    = GlobalName(N::ProDN4Potritt);
    extNames[fracInDN1New] = GlobalName(N::ProDN1Potritt);
    extNames[fracInDN2New] = GlobalName(N::ProDN2Potritt);
    extNames[fracInDN34New] = GlobalName(N::ProDN34Potritt);
#endif

    extNames[ttotal] = GlobalName(N::ttotal);
    extNames[DNtot] = GlobalName(N::tDN);
    extNames[DPtot] = GlobalName(N::tDP);
    //extNames[SP8totTV] = GlobalName(N::tSP8;
    //extNames[SP4totTV] = GlobalName(N::tSP4;
    extNames[tSP8] = GlobalName(N::tSP8P);
    extNames[tSP4] = GlobalName(N::tSP4P);
    extNames[tTconv] = GlobalName(N::tTconvP);
    extNames[tTRegP25] = GlobalName(N::tTRegP1P);
    extNames[tTRegPFp3] = GlobalName(N::tTRegP2P);
    extNames[tTreg] = GlobalName(N::tTregP);
    extNames[tSP8RagN] = GlobalName(N::tSP8RagN);
    extNames[tSP4RagN] = GlobalName(N::tSP4RagN);
    extNames[tTconvRagN] = GlobalName(N::tTconvRagN);
    extNames[tTregP1RagN] = GlobalName(N::tTregP1RagN);
    extNames[tTregP2RagN] = GlobalName(N::tTregP2RagN);
    extNames[tTregRagN] = GlobalName(N::tTregRagN);
    extNames[pctDN] =     GlobalName(N::pctDN);
    extNames[pctDP] =  GlobalName(N::pctDP);
    extNames[pctSP8] =  GlobalName(N::pctSP8);
    extNames[pctSP4] =   GlobalName(N::pctSP4);
    extNames[pctTconv] =   GlobalName(N::pctTconvP);
    extNames[pctTRegP1] =  GlobalName(N::pctTRegP1P);
    extNames[pctTRegP2] =  GlobalName(N::pctTRegP2P);
    extNames[pctTreg] = GlobalName(N::pctTregP);
    extNames[pctSP8RagN] =GlobalName(N::pctSP8RagN);
    extNames[pctSP4RagN] = GlobalName(N::pctSP4RagN);
    extNames[pctTconvRagN] = GlobalName(N::pctTconvRagN);
    extNames[pctTRegP1RagN] = GlobalName(N::pctTRegP1RagN);
    extNames[pctTRegP2RagN] = GlobalName(N::pctTRegP2RagN);
    extNames[pctTregRagN] =GlobalName(N::pctTregRagN);
    extNames[stotal] = GlobalName(N::stotal);
    extNames[sTconv] = GlobalName(N::sTconv);
    extNames[sTreg] = GlobalName(N::sTreg);
    extNames[sCD8] = GlobalName(N::sCD8);
    extNames[sBcells] = GlobalName(N::sBcells);
    extNames[sTconvRagN] = GlobalName(N::sTconvRagN);
    extNames[sTregRagN] = GlobalName(N::sTregRagN);
    extNames[sCD8RagN] = GlobalName(N::sCD8RagN);
    extNames[pcsTconv] = GlobalName(N::pcsTconv);
    extNames[pcsTreg] = GlobalName(N::pcsTreg);
    extNames[pcsCD8] = GlobalName(N::pcsCD8);
    extNames[pcsBcells] = GlobalName(N::pcsBcells);
    extNames[pcsTconvRagN] = GlobalName(N::pcsTconvRagN);
    extNames[pcsTregRagN] = GlobalName(N::pcsTregRagN);
    extNames[pcsCD8RagN] = GlobalName(N::pcsCD8RagN);

    // Name of parameters
    paramNames[flu_peak] = "flu_peak / peak of flu effect in days";
    paramNames[flu_std]  = "flu_std / width of flu effect (stddev)";
    paramNames[fETP_tDN] = "fETP_tDN / DN thymic Inflow";
    paramNames[decayDN1pre]   = "decayDN1pre";
    paramNames[commitDN1to2]  = "commitDN1to2";
    paramNames[deathDN1]      = "deathDN1";
    paramNames[cycleDN1]     = "cycleDN1";
    paramNames[commitDN2to3]  = "commitDN2to3";
    paramNames[deathDN2]      = "deathDN2";
    paramNames[cycleDN2]     = "cycleDN2";
    paramNames[commitDN3to4]  = "commitDN3to4";
    paramNames[deathDN3]      = "deathDN3";
    paramNames[cycleDN3]     = "cycleDN3";
    paramNames[commitDN4toDP] = "commitDN4toDP";
    paramNames[deathDN4]      = "deathDN4";
    paramNames[cycleDN4]     = "cycleDN4";

    paramNames[ NdivDN] = string("NdivDN");
    paramNames[ pDN] = string("pDN");
    paramNames[ dDN] = string("dDN");
    paramNames[ NdivDP] = string("NdivDP");
    paramNames[ peDP] = string("peDP");
    paramNames[ deDP] = string("deDP");
    paramNames[ prestDP] = string("prestDP");
    paramNames[ drestDP] = string("drestDP");
    paramNames[ diffDPtoSP4] = string("TV-diffDPtoSP4");
    paramNames[ diffDPtoSP8] = string("TV-diffDPtoSP8");
    paramNames[ pSP4] = string("TV-pSP4");
    paramNames[ dSP4] = string("TV-dSP4");
     paramNames[ pcConvLastGenSP4] = string("pcConvLastGenSP4");
    paramNames[ NdivSP4] = string("TV-NdivSP4");
    paramNames[ pSP8] = string("TV-pSP8");
    paramNames[ dSP8] = string("TV-dSP8");
    paramNames[ NdivSP8] = string("TV-NdivSP8");
     paramNames[ pcConvLastGenSP4] = string("pcConvLastGenSP4");

    paramNames[ftDP_tTConv] = "ftDP_tTConv / conversion from DP to Tconv";
    paramNames[ftDP_tTregP25] = "ftDP_tTregP25 / conversion DP to shieh precursors";
    paramNames[ftDP_tTregFP3] = "ftDP_tTregFP3 / conversion DP to singer precursors";
    paramNames[ftDP_tSP8] = "ftDP_tSP8 / conversion DP to SP8";
    paramNames[out_tDP] = "out_tDP / outflow of DP";
    //paramNames[in_tDP] = "in_tDP / inflow (recirculation) of DP";
    paramNames[ptTregP25] = "ptTregP25 / prolif shieh precursors";
    paramNames[ftTregP25_tDPTreg] = "ftTregP25_tDPTreg / conversion shieh to mature Tregs";
    paramNames[out_tTregP25] = "out_tTregP25 / outflow shieh precursors";
    paramNames[ptTregFP3] = "ptTregFP3 / prolif singer precursors";
    paramNames[ftTregFP3_tDPTreg] = "ftTregFP3_tDPTreg / conversion singer to mature Tregs";
    paramNames[out_tTregFP3] = "out_tTregFP3 / outflow singer precursors";
    paramNames[in_tTregPFp3] = "in_tTregPFP3 / inflow singer precursors";
    paramNames[ptDPTregs] = "ptDPTregs / prolif mature Tregs";
    paramNames[out_tDPTregs] = "out_tDPTregs / outflow mature Tregs";
    paramNames[in_tDPTregs] = "in_tDPTregs / inflow (recirculation) mature Tregs";
    paramNames[ptTconv] = "ptTconv / prolif Tconvs";
    paramNames[out_tTconv] = "out_tTconv / outflow of Tconvs";
    paramNames[in_tTconv] = "in_tTconv / inflow of Tconvs";
    paramNames[ptSP8] = "ptSP8 / prolif SP8";
    paramNames[out_SP8] = "out_SP8 / outflow SP8";
    paramNames[in_SP8] = "in_SP8 / inflow (recirculation) SP8";
    paramNames[dtTregP25] = "dtTregP25 / death shiesh precursors";
    paramNames[dtTregFP3] = "dtTregFP3 / death singer precursors";
    paramNames[dtDPTregs] = "dtDPTregs / death mature Tregs";
    paramNames[dtTconv] = "dtTconv / death Tconv";
    paramNames[dtSP8] = "dtSP8 / death SP8";
    paramNames[fracTtoS] = "fracTtoS / frac. of thym out reaching SPL";
    paramNames[dsTconv] = "dsTconv / death splenic Tconv";
    paramNames[dsTreg] = "dsTreg / death splenic Tregs";
    paramNames[dsCD8] = "dsCD8 / death splenic CD8";
    paramNames[dsBcells] = "dsBcells / death splenic B cells";
    paramNames[decayRag] = "decayRag / decay of Rag-GFP";
    paramNames[	hypInflowCoeffETP	]="	hypInflowCoeffETP	";
    paramNames[	hypDeathCoeffDN ]="hypDeathCoeffDN",
    paramNames[	hypDeathCoeffDN1 ]="hypDeathCoeffDN1",
    paramNames[	hypDeathCoeffDN2 ]="hypDeathCoeffDN2",
    paramNames[	hypDeathCoeffDN3 ]="hypDeathCoeffDN3",
    paramNames[	hypDeathCoeffDN4 ]="hypDeathCoeffDN4",
    paramNames[ hypDeathCoeffAddEarlyDP] = "hypDeathCoeffAddEarlyD";
    paramNames[	hypDeathCoeffDP	]="	hypDeathCoeffDP	";
    paramNames[	hypDeathCoeffTconv	]="	hypDeathCoeffTconv	";
    paramNames[	hypDeathCoeffProFp3	]="	hypDeathCoeffProFp3	";
    paramNames[	hypDeathCoeffPro25	]="	hypDeathCoeffPro25	";
    paramNames[	hypDeathCoeffDPTregs	]="	hypDeathCoeffDPTregs	";
    paramNames[	hypDeathCoeffSP8	]="	hypDeathCoeffSP8	";
    paramNames[	hypOutputCoeffOutDP	]="	hypOutputCoeffOutDP	";
    paramNames[	hypOutputCoeffOutTconv	]="	hypOutputCoeffOutTconv	";
    paramNames[	hypOutputCoeffOutDPTregs	]="	hypOutputCoeffOutDPTregs	";
    paramNames[	hypOutputCoeffOutProFP3	]="	hypOutputCoeffOutProFP3	";
    paramNames[	hypOutputCoeffOutPro25	]="	hypOutputCoeffOutPro25	";
    paramNames[	hypOutputCoeffOutSP8	]="	hypOutputCoeffOutSP8	";
    paramNames[	hypFasterCoeffDNtoDP	]="	hypFasterCoeffDNtoDP	";
    paramNames[	hypFasterCoeffProFP3	]="	hypFasterCoeffProFP3	";
    paramNames[	hypFasterCoeffPro25	]="	hypFasterCoeffPro25	";
    paramNames[	hypFasterCoeffTconv	]="	hypFasterCoeffTconv	";
    paramNames[	hypFasterCoeffSP8	]="	hypFasterCoeffSP8	";
    paramNames[	hypSpaceOutputCoeff	]="	hypSpaceOutputCoeff	";
    paramNames[	hypLessDivDN	]="CoeffDivDN";
    paramNames[	hypLessDivDP	]="CoeffDivDP";
    paramNames[	hypLessDivTregPro25	]="CoeffDivTregPro25";
    paramNames[	hypLessDivTregProFP3	]="CoeffDivTregProFP3";
    paramNames[	hypLessDivDPTreg ] = "CoeffDivDPTreg";
    paramNames[	hypLessDivTconv	]="CoeffDivTconv";
    paramNames[	hypLessDivCD8	]="CoeffDivCD8";
    paramNames[ logisticThymus] = "logisticSizeThymus";
    paramNames[ logisticStrength] = "logisticStrength";

    paramLowBounds[flu_peak]    = 	5;              paramUpBounds[flu_peak]     = 	15;
    paramLowBounds[flu_std]     = 	0.5;			paramUpBounds[flu_std]      = 	10;
    paramLowBounds[fETP_tDN]    = 	0.001;          paramUpBounds[fETP_tDN]     = 	1;
    paramLowBounds[decayDN1pre] = 	0;				paramUpBounds[decayDN1pre]  = 	0;
    paramLowBounds[commitDN1to2]= 	0;				paramUpBounds[commitDN1to2] = 	0;
    paramLowBounds[deathDN1]    = 	0;              paramUpBounds[deathDN1]     = 	0;
    paramLowBounds[cycleDN1]   = 	0;				paramUpBounds[cycleDN1]    = 	0;
    paramLowBounds[commitDN2to3]= 	0;				paramUpBounds[commitDN2to3] = 	0;
    paramLowBounds[deathDN2]    = 	0;              paramUpBounds[deathDN2]     = 	0;
    paramLowBounds[cycleDN2]   = 	0;				paramUpBounds[cycleDN2]    = 	0;
    paramLowBounds[commitDN3to4]= 	0;				paramUpBounds[commitDN3to4] = 	0;
    paramLowBounds[deathDN3]    = 	0;              paramUpBounds[deathDN3]     = 	0;
    paramLowBounds[cycleDN3]   = 	0;				paramUpBounds[cycleDN3]    = 	0;
    paramLowBounds[commitDN4toDP] =	0;              paramUpBounds[commitDN4toDP]= 	0;
    paramLowBounds[deathDN4]    = 	0;              paramUpBounds[deathDN4]     = 	0;
    paramLowBounds[cycleDN4]   = 	0;				paramUpBounds[cycleDN4]    = 	0;

    paramLowBounds[ NdivDN] 	= 0;		paramUpBounds[NdivDN] 	= 0;
    paramLowBounds[ pDN] 	= 0;		paramUpBounds[pDN] 	= 0;
    paramLowBounds[ dDN] 	= 0;		paramUpBounds[dDN] 	= 0;
    paramLowBounds[ NdivDP] 	= 0;		paramUpBounds[NdivDP] 	= 0;
    paramLowBounds[ peDP] 	= 0;		paramUpBounds[peDP] 	= 0;
    paramLowBounds[ deDP] 	= 0;		paramUpBounds[deDP] 	= 0;
    paramLowBounds[ prestDP] 	= 0;		paramUpBounds[prestDP] 	= 0;
    paramLowBounds[ drestDP] 	= 0;		paramUpBounds[drestDP] 	= 0;
    paramLowBounds[ diffDPtoSP4] 	= 0;		paramUpBounds[diffDPtoSP4] 	= 0;
    paramLowBounds[ diffDPtoSP8] 	= 0;		paramUpBounds[diffDPtoSP8] 	= 0;
    paramLowBounds[ pSP4] 	= 0;		paramUpBounds[pSP4] 	= 0;
    paramLowBounds[ dSP4] 	= 0;		paramUpBounds[dSP4] 	= 0;
    paramLowBounds[ pcConvLastGenSP4] 	= 0;		paramUpBounds[pcConvLastGenSP4] 	= 0;
    paramLowBounds[ NdivSP4] 	= 0;		paramUpBounds[NdivSP4] 	= 0;
    paramLowBounds[ pSP8] 	= 0;		paramUpBounds[pSP8] 	= 0;
    paramLowBounds[ dSP8] 	= 0;		paramUpBounds[dSP8] 	= 0;
    paramLowBounds[ pcConvLastGenSP8] 	= 0;		paramUpBounds[pcConvLastGenSP8] 	= 0;
    paramLowBounds[ NdivSP8] 	= 0;		paramUpBounds[NdivSP8] 	= 0;

    paramLowBounds[	ftDP_tTConv	] = 	0.001	;				paramUpBounds[	ftDP_tTConv	] = 	10	;
    paramLowBounds[	ftDP_tTregP25	] = 	0.001	;				paramUpBounds[	ftDP_tTregP25	] = 	10	;
    paramLowBounds[	ftDP_tTregFP3	] = 	0.001	;				paramUpBounds[	ftDP_tTregFP3	] = 	10	;
    paramLowBounds[	ftDP_tSP8	] = 	0.001	;				paramUpBounds[	ftDP_tSP8	] = 	10	;
    paramLowBounds[	out_tDP	] = 	0.001	;				paramUpBounds[	out_tDP	] = 	10	;
    //paramLowBounds[	in_tDP	] = 	0.0001	;				paramUpBounds[	in_tDP	] = 	1	;
    paramLowBounds[	ptTregP25	] = 	0.01	;				paramUpBounds[	ptTregP25	] = 	10	;
    paramLowBounds[	ftTregP25_tDPTreg	] = 	0.001	;				paramUpBounds[	ftTregP25_tDPTreg	] = 	1	;
    paramLowBounds[	out_tTregP25	] = 	0.001	;				paramUpBounds[	out_tTregP25	] = 	1	;
    paramLowBounds[	ptTregFP3	] = 	0.01	;				paramUpBounds[	ptTregFP3	] = 	10	;
    paramLowBounds[	ftTregFP3_tDPTreg	] = 	0.001	;				paramUpBounds[	ftTregFP3_tDPTreg	] = 	10	;
    paramLowBounds[	out_tTregFP3	] = 	0.001	;				paramUpBounds[	out_tTregFP3	] = 	10	;
    paramLowBounds[	in_tTregPFp3	] = 	0.0001	;				paramUpBounds[	in_tTregPFp3	] = 	1	;
    paramLowBounds[	ptDPTregs	] = 	0.01	;				paramUpBounds[	ptDPTregs	] = 	10	;
    paramLowBounds[	out_tDPTregs	] = 	0.001	;				paramUpBounds[	out_tDPTregs	] = 	10	;
    paramLowBounds[	in_tDPTregs	] = 	0.0001	;				paramUpBounds[	in_tDPTregs	] = 	1	;
    paramLowBounds[	ptTconv	] = 	0.01	;				paramUpBounds[	ptTconv	] = 	10	;
    paramLowBounds[	out_tTconv	] = 	0.001	;				paramUpBounds[	out_tTconv	] = 	10	;
    paramLowBounds[	in_tTconv	] = 	0.0001	;				paramUpBounds[	in_tTconv	] = 	1	;
    paramLowBounds[	ptSP8	] = 	0.01	;				paramUpBounds[	ptSP8	] = 	10	;
    paramLowBounds[	out_SP8	] = 	0.001	;				paramUpBounds[	out_SP8	] = 	10	;
    paramLowBounds[	in_SP8	] = 	0.0001	;				paramUpBounds[	in_SP8	] = 	1	;
    paramLowBounds[	dtTregP25	] = 	0.001	;				paramUpBounds[	dtTregP25	] = 	10	;
    paramLowBounds[	dtTregFP3	] = 	0.001	;				paramUpBounds[	dtTregFP3	] = 	10	;
    paramLowBounds[	dtDPTregs	] = 	0.001	;				paramUpBounds[	dtDPTregs	] = 	10	;
    paramLowBounds[	dtTconv	] = 	0.001	;				paramUpBounds[	dtTconv	] = 	10	;
    paramLowBounds[	dtSP8	] = 	0.001	;				paramUpBounds[	dtSP8	] = 	10	;
    paramLowBounds[ fracTtoS ]=     0.0001  ;               paramUpBounds[  fracTtoS] =     1.0 ;
    paramLowBounds[	dsTconv	] = 	0.001	;				paramUpBounds[	dsTconv	] = 	10	;
    paramLowBounds[	dsTreg	] = 	0.001	;				paramUpBounds[	dsTreg	] = 	10	;
    paramLowBounds[	dsCD8	] = 	0.001	;				paramUpBounds[	dsCD8	] = 	10	;
    paramLowBounds[	dsBcells	] = 	0.001	;				paramUpBounds[	dsBcells	] = 	10	;
    paramLowBounds[	decayRag	] = 	0.001	;				paramUpBounds[	decayRag	] = 	10	;
    paramLowBounds[	hypInflowCoeffETP	] = 	0.05	;				paramUpBounds[	hypInflowCoeffETP	] = 	20	;
    paramLowBounds[	hypDeathCoeffDN  ] = 0.05;                      paramUpBounds[	hypDeathCoeffDN	] = 	20	;
    paramLowBounds[	hypDeathCoeffDN1  ] = 0.05;                      paramUpBounds[	hypDeathCoeffDN1	] = 	20	;
    paramLowBounds[	hypDeathCoeffDN2  ] = 0.05;                      paramUpBounds[	hypDeathCoeffDN2	] = 	20	;
    paramLowBounds[	hypDeathCoeffDN3  ] = 0.05;                      paramUpBounds[	hypDeathCoeffDN3	] = 	20	;
    paramLowBounds[	hypDeathCoeffDN4  ] = 0.05;                      paramUpBounds[	hypDeathCoeffDN4	] = 	20	;
    paramLowBounds[ hypDeathCoeffAddEarlyDP] = 0.05;                paramUpBounds[hypDeathCoeffAddEarlyDP] = 20;
    paramLowBounds[	hypDeathCoeffDP	] = 	0.05	;				paramUpBounds[	hypDeathCoeffDP	] = 	20	;
    paramLowBounds[	hypDeathCoeffTconv	] = 	0.05	;				paramUpBounds[	hypDeathCoeffTconv	] = 	20	;
    paramLowBounds[	hypDeathCoeffProFp3	] = 	0.05	;				paramUpBounds[	hypDeathCoeffProFp3	] = 	20	;
    paramLowBounds[	hypDeathCoeffPro25	] = 	0.05	;				paramUpBounds[	hypDeathCoeffPro25	] = 	20	;
    paramLowBounds[	hypDeathCoeffDPTregs	] = 	0.05	;				paramUpBounds[	hypDeathCoeffDPTregs	] = 	20	;
    paramLowBounds[	hypDeathCoeffSP8	] = 	0.05	;				paramUpBounds[	hypDeathCoeffSP8	] = 	20	;
    paramLowBounds[	hypOutputCoeffOutDP	] = 	0.05	;				paramUpBounds[	hypOutputCoeffOutDP	] = 	20	;
    paramLowBounds[	hypOutputCoeffOutTconv	] = 	0.05	;				paramUpBounds[	hypOutputCoeffOutTconv	] = 	20	;
    paramLowBounds[	hypOutputCoeffOutDPTregs	] = 	0.05	;				paramUpBounds[	hypOutputCoeffOutDPTregs	] = 	20	;
    paramLowBounds[	hypOutputCoeffOutProFP3	] = 	0.05	;				paramUpBounds[	hypOutputCoeffOutProFP3	] = 	20	;
    paramLowBounds[	hypOutputCoeffOutPro25	] = 	0.05	;				paramUpBounds[	hypOutputCoeffOutPro25	] = 	20	;
    paramLowBounds[	hypOutputCoeffOutSP8	] = 	0.05	;				paramUpBounds[	hypOutputCoeffOutSP8	] = 	20	;
    paramLowBounds[	hypFasterCoeffDNtoDP	] = 	0.05	;				paramUpBounds[	hypFasterCoeffDNtoDP	] = 	20	;
    paramLowBounds[	hypFasterCoeffProFP3	] = 	0.05	;				paramUpBounds[	hypFasterCoeffProFP3	] = 	20	;
    paramLowBounds[	hypFasterCoeffPro25	] = 	0.05	;				paramUpBounds[	hypFasterCoeffPro25	] = 	20	;
    paramLowBounds[	hypFasterCoeffTconv	] = 	0.05	;				paramUpBounds[	hypFasterCoeffTconv	] = 	20	;
    paramLowBounds[	hypFasterCoeffSP8	] = 	0.05	;				paramUpBounds[	hypFasterCoeffSP8	] = 	20	;
    paramLowBounds[	hypSpaceOutputCoeff	] = 	0.05	;				paramUpBounds[	hypSpaceOutputCoeff	] = 	20	;
    paramLowBounds[	hypLessDivDN	] = 	0.01	;				paramUpBounds[hypLessDivDN	] = 	20	;
    paramLowBounds[	hypLessDivDP	] = 	0.01	;				paramUpBounds[hypLessDivDP] = 	20	;
    paramLowBounds[	hypLessDivTregPro25	] = 	0.01	;				paramUpBounds[hypLessDivTregPro25] = 	20	;
    paramLowBounds[	hypLessDivTregProFP3	] = 	0.01	;				paramUpBounds[hypLessDivTregProFP3] = 	20	;
    paramLowBounds[	hypLessDivDPTreg	] = 	0.01	;				paramUpBounds[hypLessDivDPTreg] = 20;
    paramLowBounds[	hypLessDivTconv	] = 	0.01	;				paramUpBounds[hypLessDivTconv] = 	20	;
    paramLowBounds[	hypLessDivCD8	] = 	0.01	;				paramUpBounds[hypLessDivCD8] = 	20	;
    paramLowBounds[ logisticThymus ] = 0.1;                         paramUpBounds[logisticThymus] = 500;
    paramLowBounds[ logisticStrength] = 0.1;                        paramUpBounds[logisticStrength] = 10;
}

void modele4MegaThymus::setBaseParameters(){
    background = Back::WT;
	params.clear();     // to make sure they are all put to zero
    params.resize(NbParameters, 0.0);

    // Now everything is in millions
    params[flu_peak]        = 9;
    params[flu_std]         = 2.5;
    params[fETP_tDN]        = 0.00005	;
    params[decayDN1pre]     = 2.27; // day
    // put commit afterwards
    params[deathDN1]        = 0.14;
    // depends on death
    params[commitDN1to2]    = 1.0 - params[deathDN1]; // all of them after the last gen.
    params[cycleDN1]       = 1.07;
    params[commitDN2to3]    = 0.58;
    params[deathDN2]        = 0.028;
    params[cycleDN2]       = 0.631;
    params[commitDN3to4]    = 0.295; //*** wrong number
    params[deathDN3]        = 0.216;
    params[cycleDN3]       = 2.65;
    params[commitDN4toDP]   = 0.480;
    params[deathDN4]        = 0.073;
    params[cycleDN4]       = 0.514;

    params[ NdivDN] = 5.00328915; // equiv thomas-vaslin 4; // alpha = 0.29, n = 127 <-> DNg4 all convert to next but none of g3
    params[ pDN] = 0.23; // 1/day
    params[ dDN] = 0;//
    params[ NdivDP] = 5; // alpha = 0.20, n = 127 <-> DPg5 all convert to next but none of g4
    params[ peDP] = 4.5;//4.5 max pb boundary
    params[ deDP] = 0;//
    params[ prestDP] = 0;
    params[ drestDP] = 0.37*(1 - 0.01 - 0.06);
    params[ diffDPtoSP4] = 0.37*0.06;
    params[ diffDPtoSP8] = 0.37*0.01;
    params[ pSP4] = 0.23;
    params[ dSP4] = 0;
    params[ pcConvLastGenSP4] = 0.23 * (-1 + 2* 4.02 / 2.49); //0.27;
    params[ NdivSP4] = 2;  // alpha = 0.99, n = 127 <-> rate 0.27 of g1 convert and all of g2 [but with infinite speed ?] WRONG !! missing decimals :!!
    params[ pSP8] = 0.23;
    params[ dSP8] = 0;
    params[ pcConvLastGenSP8] = 0.23 * (-1 + 2* 0.77 / 0.48); //0.05;
    params[ NdivSP8] = 3; // alpha = 0.48, n = 127 <-> 0.5% of g2 convert and 100% of g3

    params[	ftDP_tTConv	] = 	0.1	;
    params[	ftDP_tTregP25	] = 	0.005	;
    params[	ftDP_tTregFP3	] = 	0.005	;
    params[	ftDP_tSP8	] = 	0.05	;
    params[	out_tDP	] = 	0.005	;
    //params[	in_tDP	] = 	0.005	;
    params[	ptTregP25	] = 	0.01	;
    params[	ftTregP25_tDPTreg	] = 	0.05	;
    params[	out_tTregP25	] = 	0.05	;
    params[	ptTregFP3	] = 	0.001	;
    params[	ftTregFP3_tDPTreg	] = 	0.05	;
    params[	out_tTregFP3	] = 	0.05	;
    params[	in_tTregPFp3	] = 	0.05	;
    params[	ptDPTregs	] = 	0.001	;
    params[	out_tDPTregs	] = 	0.08	;
    params[	in_tDPTregs	] = 	0.01	;
    params[	ptTconv	] = 	0.001	;
    params[	out_tTconv	] = 	0.05	;
    params[	in_tTconv	] = 	0.01	;
    params[	ptSP8	] = 	0.001	;
    params[	out_SP8	] = 	0.05	;
    params[	in_SP8	] = 	0.0008	;
    params[	dtTregP25	] = 	0.03	;
    params[	dtTregFP3	] = 	0.03	;
    params[	dtDPTregs	] = 	0.03	;
    params[	dtTconv	] = 	0.03	;
    params[	dtSP8	] = 	0.03	;
    params[ fracTtoS] =     0.5;
    params[	dsTconv	] = 	0.03	;
    params[	dsTreg	] = 	0.03	;
    params[	dsCD8	] = 	0.03	;
    params[	dsBcells	] = 	0.03	;
    params[	decayRag	] = 	0.01	;

    params[	hypInflowCoeffETP	] = 	0.3	;
    params[	hypDeathCoeffDN ] = 5;
    params[ hypDeathCoeffDN1]    = 5;
    params[ hypDeathCoeffDN2]    = 5;
    params[ hypDeathCoeffDN3]    = 5;
    params[ hypDeathCoeffDN4]    = 5;
    params[ hypDeathCoeffAddEarlyDP] = 5;
    params[	hypDeathCoeffDP	] = 	10	;
    params[	hypDeathCoeffTconv	] = 	1	;
    params[	hypDeathCoeffProFp3	] = 	1	;
    params[	hypDeathCoeffPro25	] = 	1	;
    params[	hypDeathCoeffDPTregs	] = 	1	;
    params[	hypDeathCoeffSP8	] = 	1	;
    params[	hypOutputCoeffOutDP	] = 	0.2	;
    params[	hypOutputCoeffOutTconv	] = 	1	;
    params[	hypOutputCoeffOutDPTregs	] = 	1	;
    params[	hypOutputCoeffOutProFP3	] = 	1	;
    params[	hypOutputCoeffOutPro25	] = 	1	;
    params[	hypOutputCoeffOutSP8	] = 	1	;
    params[	hypFasterCoeffDNtoDP	] = 	1	;
    params[	hypFasterCoeffProFP3	] = 	5	;
    params[	hypFasterCoeffPro25	] = 	1	;
    params[	hypFasterCoeffTconv	] = 	1	;
    params[	hypFasterCoeffSP8	] = 	1	;
    params[	hypSpaceOutputCoeff	] = 	0.2	;
    params[	hypLessDivDN	] = 	0.2	;
    params[	hypLessDivDP	] = 	0.2	;
    params[	hypLessDivTregPro25	] = 	1	;
    params[	hypLessDivTregProFP3	] = 	1	;
    params[	hypLessDivDPTreg] = 1;
    params[	hypLessDivTconv	] = 	0.35	;
    params[	hypLessDivCD8	] = 	0.35	;
    params[ logisticThymus ] = 90;
    params[ logisticStrength] = 2.0;

	setBaseParametersDone();
}

void modele4MegaThymus::initialise(long long _background){ // don't touch to parameters !
	val.clear();
    val.resize(NbVariables, 0.0);
	init.clear();
    init.resize(NbVariables, 0.0);

    // test if each possible background is in the current combination of backgrounds (stored in the field background)
    if((background != Back::WT) && (background != _background)){
        //cerr << "WRN : modeleLeishmania::initialize, when the background has been changed from WT, you should not change it again, because parameters can not be retrieved. Please load parameters again" << endl;
    }

    /// PHIlippe todo change with combinations !!
    background = _background;
   /*if(background == Back::WT){}
    if(background == Back::B_ReducedInflow){}
    if(background == Back::B_MoreDeath){}
    if(background == Back::B_MoreOutputThymus){}
    if(background == Back::B_FasterDifferentiation){}
    if(background == Back::B_SpaceDependentOutput){}
    if(background == Back::B_DivisionReduced){}
    if(background == Back::B_AllCombined){}*/

    init[tPreDN1] = 0.000190;



  #ifdef ReducedParams
    init[fracInPreDN1] = 0;
    init[fracInDN1] = 0;
    init[fracInDN2] = 0;
    init[fracInDN3] = 0;
    init[fracInDN4] = 0;
    init[fracInDN1New] = 0;
    init[fracInDN2New] = 0;
    init[fracInDN34New] = 0;
#endif


    params[commitDN1to2] = 1 - params[deathDN1];

    // steady state Manesso
    if(background & Back::B_StartSteadyState){
        init[tPreDN1] =  params[decayDN1pre] * params[fETP_tDN];
        init[tDN1g0] = params[cycleDN1] * init[tPreDN1] / (max(1e-12, params[decayDN1pre]));
        for(int i = tDN1g1; i <= tDN1g11; ++i){
            init[i] = 2 * (1 - params[deathDN1]) * init[i-1];
        }
    //    init[tDN1g11] = 20.853;
        init[tDN2] = - ((params[cycleDN2])/(1-2*params[commitDN2to3]-2*params[deathDN2])) * (params[commitDN1to2] * init[tDN1g11]) / (params[cycleDN1] + 1e-12);
        //cout << "initDN2= " << init[tDN2] << endl;
        init[tDN3] =  - ((params[cycleDN3])/(1-2*params[commitDN3to4]-2*params[deathDN3])) * (params[commitDN2to3] * init[tDN2]) / (params[cycleDN2] + 1e-12);;
        //cout << "initDN3= " << init[tDN3] << endl;
        init[tDN4] =  - ((params[cycleDN4])/(1-2*params[commitDN4toDP]-2*params[deathDN4])) * (params[commitDN3to4] * init[tDN3]) / (params[cycleDN3] + 1e-12);;
        //cout << "initDN4= " << init[tDN4] << endl;


        // steady state TVaslin
        int N = (int) params[NdivDN];
        double divFloat = params[NdivDN] - (double) N;
        double T_DN = 1 / (max(params[pDN] + params[dDN], 1e-12));
        double C = 0;
        if(divFloat < 1e-12) {
            N = N-1;
            C = 0;
        } else {
            C = (1 / T_DN) * ((1 / divFloat) - 1);
        }

        if(params[NdivDN] < 1e-12) {
            cout << "WRN: you use a multi-generation model and chose N=0. Cannot simulate that so I put proliferation pDN = 0. It will change T\n" << endl;
            N = 0;
            params[pDN] = 0;
            C = 0;
        }

        vector<double> CoeffPerGen = vector<double>(7, 0);
        //CoeffPerGen[N] = C;
        vector<double> DoProlif = vector<double>(7, 0);
        for(int i = 0; i < N; ++i){
            DoProlif[i] = 1.0;
        }
        DoProlif[N] = divFloat;

        cout << "Init for TV2009: Ndiv=" << params[NdivDN] << ", so C=" << C << " vec " << CoeffPerGen[0] << " "  << CoeffPerGen[1] << " "  << CoeffPerGen[2] << " "  << CoeffPerGen[3] << " "  << CoeffPerGen[4] << " "  << CoeffPerGen[5] << " "  << CoeffPerGen[6] << " "<< endl;

        double InflowToDN34 = init[tDN2] * params[commitDN2to3] / (max(params[cycleDN2], 1e-12));
        init[ divDNg0] = InflowToDN34 / (max((params[pDN] + params[dDN] + CoeffPerGen[0]) , 1e-12));
        init[ divDNg1] = 2*init[ divDNg0] * DoProlif[0] * (params[pDN]) / (max(1e-12, params[pDN] + params[dDN] + CoeffPerGen[1]));
        init[ divDNg2] = 2*init[ divDNg1] * DoProlif[1] * (params[pDN]) / (max(1e-12, params[pDN] + params[dDN] + CoeffPerGen[2]));
        init[ divDNg3] = 2*init[ divDNg2] * DoProlif[2] * (params[pDN]) / (max(1e-12, params[pDN] + params[dDN] + CoeffPerGen[3]));
        init[ divDNg4] = 2*init[ divDNg3] * DoProlif[3] * (params[pDN]) / (max(1e-12, params[pDN] + params[dDN] + CoeffPerGen[4]));
        init[ divDNg5] = 2*init[ divDNg4] * DoProlif[4] * (params[pDN]) / (max(1e-12, params[pDN] + params[dDN] + CoeffPerGen[5]));
        init[ divDNg6] = 2*init[ divDNg5] * DoProlif[5] * (params[pDN]) / (max(1e-12, params[pDN] + params[dDN] + CoeffPerGen[6]));
        double outflowToDP = C * init[divDNg0 + N] + 2*init[divDNg0 + N] * (params[pDN]);

        double fastDiv = 100;
        init[ eDPg0] = outflowToDP /  (max(1e-12, params[peDP] + params[deDP]));  //0.07;
        init[ eDPg1] = 2*init[eDPg0] * params[peDP] / (max(1e-12, params[peDP] + params[deDP]));  // 0.14;
        init[ eDPg2] = 2*init[eDPg1] * params[peDP] / (max(1e-12, params[peDP] + params[deDP]));  // 0.29;
        init[ eDPg3] = 2*init[eDPg2] * params[peDP] / (max(1e-12, params[peDP] + params[deDP]));  // 0.58;
        init[ eDPg4] = 2*init[eDPg3] * params[peDP] / (max(1e-12, params[peDP] + params[deDP]));  //1.16;
        init[ eDPg5] = 2*init[eDPg4] * params[peDP] / (max(1e-12, params[peDP] + params[deDP] + (4.5*(- 1 + 2*1.1397 /0.94))));  //0.94;
        init[ eDPg6] = 2*init[eDPg5] * params[peDP] / (max(1e-12, params[peDP] + params[deDP] + fastDiv));  // 0.08;

        init[ lDP] = (fastDiv *  init[ eDPg6] + (4.5*(- 1 + 2*1.1397 /0.94)) * init[eDPg5]   + 2 * params[peDP] * init[eDPg6]) / (max(1e-12, params[prestDP] + params[drestDP] + params[diffDPtoSP4] + params[diffDPtoSP8])); //  40.29;
        // initial values from the model thomas-Vaslin. They need to be rescaled to the thymus size here
        /*init[ divSP4g0] = 4.02;
        init[ divSP4g1] = 2.49;
        init[ divSP4g2] = 0.01;
        //init[ restSP4] = 0;
        init[ divSP8g0] = 0.77;
        init[ divSP8g1] = 0.48;
        init[ divSP8g2] = 0.002;*/

        init[divSP4g0] 	= (params[diffDPtoSP4] *  init[lDP])/ (+ params[pSP4]  + params[dSP4] );
        init[divSP4g1] 	= (2 * params[pSP4] * init[divSP4g0])/ (+ params[pSP4]  + params[dSP4]  + params[pcConvLastGenSP4]);
        init[divSP4g2]	= (2 * params[pSP4] * init[divSP4g1])/ ( + params[dSP4]  + 100);
        init[divSP8g0] 	= (params[diffDPtoSP8]  *  init[lDP])/ (+ params[pSP8]   + params[dSP8] );
        init[divSP8g1] 	= (2 * params[pSP8] * init[divSP8g0])/ (+ params[pSP8]   + params[dSP8]  + params[pcConvLastGenSP8]);
        init[divSP8g2] 	= (2 * params[pSP8] * init[divSP8g1]) / (+ params[pSP8]   + params[dSP8]  + 100);

        //init[ restSP8] = 0;
       /* init[ DNtot] = 0;
        init[ eDPtot] = 0;
        init[ DPtot] = 0;
        init[ SP4totTV] = 0;
        init[ SP8totTV] = 0;*/
    #ifdef ReducedParams
        init[ floweDPtolDP] = 0;
        init[ flowDPtoSP4] = 0;
        init[ flowDPtoSP8] = 0;
        init[ floweDPtoDead] = 0;
        init[ flowlDPtoDead] = 0;
        init[ flowSP4toDead] = 0;
        init[ flowSP8toDead] = 0;
    #endif

        //init[tDN] = 3.7; //3.5e7; //3e6;
        //init[tDP] = 60; //100e6;
        init[tTconv] = 9.6; // 8.5; //12e6;
        init[tTRegP25] = 0.042; // 0.0446; //5.8e6; //50000;
        init[tTRegPFp3] = 0.216; // 0.154; //0.216; //18; ///1.1e6;//50000; // changed
        init[tTreg] = 0.257; //0.134; //§§§§0.257; //0.22; //8e6;//1e6;
        init[tSP8] = 3.4; //5e6; //1.3e8; //5e6;
        init[sTreg] = 1.3;
        init[sTconv] = 10;
        init[sCD8] = 7.5;
        init[sBcells] = 25;

        init[tSP8RagN] = 0.250;
        init[tSP4RagN] = 0.600;
        init[tTconvRagN] = 0.45; // useless, will be the sum
        init[tTregP1RagN] = 0.0025;
        init[tTregP2RagN] = 0.035;
        init[tTregRagN] = 0.088;
        init[sTconvRagN] = 3.6;
        init[sTregRagN] = 1;
        init[sCD8RagN] = 4;
        //init[tSP4] = init[tTconv] + init[tTRegP25] + init[tTRegPFp3] + init[tDPTreg];

        // only done the first time (steady state). The second experiment will reuse the parameter values
        params[ptTconv] = -(params[in_tTconv] * init[sTconv]  + init[lDP]  * params[diffDPtoSP4]) / init[tTconv] + params[out_tTconv]  + params[dtTconv];
        params[ptTregP25] = - init[lDP] * params[ftDP_tTregP25] / init[tTRegP25]  + params[out_tTregP25] + params[ftTregP25_tDPTreg] + params[dtTregP25];
        params[ptTregFP3] = (- params[in_tTregPFp3] - init[lDP] * params[ftDP_tTregFP3]) / init[tTRegPFp3] + params[out_tTregFP3] + params[ftTregFP3_tDPTreg] + params[dtTregFP3];
        params[ptDPTregs] = (- params[in_tDPTregs] - init[tTRegP25] * params[ftTregP25_tDPTreg] - init[tTRegPFp3] * params[ftTregFP3_tDPTreg]) / init[tTreg] +
                params[out_tDPTregs] + params[dtDPTregs];
        params[ptSP8] = (- params[in_SP8] * init[sCD8] -  init[lDP] * params[diffDPtoSP8]) / init[tSP8] +
                params[out_SP8] + params[dtSP8];
    }

    //if(background == Back::M2){}
    //if(background == Back::TCRGATA3NEGKO){   params[KTCRGATA3]   = 0;} // for different options i.e. deficiency in something


    // if the initial values depend on parameters
    /*init[IL2] = params[IL2EQ];
    init[IL4] = params[IL4EQ];*/



    /*
    //params[ptDN] = params[ftDN_tDP] +  params[dtDN] - params[fETP_tDN] / init[tDN];
    //params[ptDP] = - (init[tDN] * params[ftDN_tDP]) / init[tDP]  + params[out_tDP]  + params[ftDP_tTConv] + params[ftDP_tTregP25] + params[ftDP_tTregFP3] + params[ftDP_tSP8] + params[dtDP];
    params[ptTconv] = -(params[in_tTconv] * init[sTconv]  + init[DPtot]  * params[ftDP_tTConv]) / init[tTconv] + params[out_tTconv]  + params[dtTconv];
    params[ptTregP25] = - init[DPtot] * params[ftDP_tTregP25] / init[tTRegP25]  + params[out_tTregP25] + params[ftTregP25_tDPTreg] + params[dtTregP25];
    params[ptTregFP3] = (- params[in_tTregPFp3] - init[DPtot] * params[ftDP_tTregFP3]) / init[tTRegPFp3] + params[out_tTregFP3] + params[ftTregFP3_tDPTreg] + params[dtTregFP3];
    params[ptDPTregs] = (- params[in_tDPTregs] - init[tTRegP25] * params[ftTregP25_tDPTreg] - init[tTRegPFp3] * params[ftTregFP3_tDPTreg]) / init[tTreg] +
            params[out_tDPTregs] + params[dtDPTregs];
    params[ptSP8] = (- params[in_SP8] * init[sCD8] -  init[DPtot] * params[ftDP_tSP8]) / init[tSP8] +
            params[out_SP8] + params[dtSP8];*/


    //params[ptDN] = params[ftDN_tDP] +  params[dtDN] - params[fETP_tDN] / init[tDN];
    //params[ptDP] = - (init[tDN] * params[ftDN_tDP]) / init[tDP]  + params[out_tDP]  + params[ftDP_tTConv] + params[ftDP_tTregP25] + params[ftDP_tTregFP3] + params[ftDP_tSP8] + params[dtDP];


     params[ftDP_tTConv] = params[diffDPtoSP4];
     params[ftDP_tSP8] = params[diffDPtoSP8];



    if(params[ptTconv] < 0){
        //cerr << "ERR: the initial conditions + parameters don't allow the parameter [ptTconv] to be positive / allow steady state" << endl;
        //
        //cerr << "     Please, put params[ftDP_tTConv]) < " <<
        //        (- params[in_tTconv] + init[tTconv] * params[out_tTconv] + params[dtTconv]) / init[tDP] << " instead of " << params[ftDP_tTConv] << endl;
        params[ptTconv] = 0;
    }

    if(params[ptTregP25] < 0){
        //cerr << "ERR: the initial conditions + parameters don't allow the parameter [ptTregP25] to be positive / allow steady state" << endl;
        //cerr << "     Please, put params[ftDP_tTregP25] < " << init[tTRegP25] * (params[out_tTregP25] + params[ftTregP25_tDPTreg] + params[dtTregP25]) / init[tDP] << endl;
        params[ptTregP25] = 0;
    }

    if(params[ptTregFP3] < 0){
        //cerr << "ERR: the initial conditions + parameters don't allow the parameter [ptTregP25] to be positive / allow steady state" << endl;
        //cerr << "     Please, put params[ftDP_tTregFP3] < " << init[tTRegPFp3] * (params[out_tTregFP3] + params[ftTregFP3_tDPTreg] + params[dtTregFP3]) /  init[tDP] << endl;
        params[ptTregFP3] = 0;
    }

    if(params[ptDPTregs] < 0){
        //cerr << "ERR: the initial conditions + parameters don't allow the parameter [ptDPTregs] to be positive / allow steady state" << endl;


        /*params[ptDPTregs] = (- params[in_tDPTregs] - init[tTRegP25] * params[ftTregP25_tDPTreg] - init[tTRegPFp3] * params[ftTregFP3_tDPTreg]) / init[tDPTreg] +
                params[out_tDPTregs] + params[dtDPTregs];
        params[ptSP8] = (- params[in_SP8] -  init[tDP] * params[ftDP_tSP8]) / init[tSP8] +
                params[out_SP8] + params[dtSP8];*/

        params[ptDPTregs] = 0;
    }

    if(params[ptSP8] < 0){
        //cerr << "ERR: the initial conditions + parameters don't allow the parameter [ptSP8] to be positive / allow steady state" << endl;
        params[ptSP8] = 0;
    }

    for(int i = 0; i < NbVariables; ++i){
		val[i] = init[i];}
    //val[tDP] = 0;
	t = 0;
	initialiseDone();
}


void modele4MegaThymus::updateDerivedVariables(){

    if(background & Back::B_BRDU){
        double efficiencyBRDUPulse = 1.0;
        val[eDPg0] = efficiencyBRDUPulse*0.1033;
        val[eDPg1] = efficiencyBRDUPulse*0.2066;
        val[eDPg2] = efficiencyBRDUPulse*0.4133;
        val[eDPg3] = efficiencyBRDUPulse*0.8267;
        //val[eDPg4] = efficiencyBRDUPulse*1.6535;
        //val[eDPg5] = efficiencyBRDUPulse*1.3638;
        //val[eDPg6] = efficiencyBRDUPulse*0.1174; to create a delay
    }

    // Manesso
    val[tDN1s] = 0;
    for(int i = tDN1g0; i <= tDN1g11; ++i){
        val[tDN1s] +=  val[i];
    }
    val[DNtot] = val[tDN1s] + val[tDN2] + // + val[tDN3] + val[tDN4];
                 val[divDNg0] + val[divDNg1] + val[divDNg2] + val[divDNg3] + val[divDNg4] + val[divDNg5] + val[divDNg6]
                 + 0.5; // this is the non-simulated DN1s that are not DN1s . Note, DNtot should notbe used inside calculations !!!
    double manessoDNtot = val[tDN1s] + val[tDN2] + val[tDN3] + val[tDN4];
    double DNtotsInSim = val[tDN1s] + val[tDN2] + val[divDNg0] + val[divDNg1] + val[divDNg2] + val[divDNg3] + val[divDNg4] + val[divDNg5] + val[divDNg6];

#ifdef ReducedParams
    // careful of DNtot + 0.5
    val[fracInPreDN1]   =  100 * min(1.0, val[tPreDN1] / max(1e-4, val[tPreDN1] + manessoDNtot));
    val[fracInDN1]      =  100 * min(1.0, val[tDN1s] / max(1e-4, /*val[tPreDN1] + */manessoDNtot));
    val[fracInDN2]      =  100 * min(1.0, val[tDN2] / max(1e-4, /*val[tPreDN1] + */ manessoDNtot));
    val[fracInDN3]      =  100 * min(1.0, val[tDN3] / max(1e-4, /*val[tPreDN1] + */ manessoDNtot));
    val[fracInDN4]      =  100 * min(1.0, val[tDN4] / max(1e-4, /*val[tPreDN1] + */ manessoDNtot));

    val[fracInDN1New]      =  100 * min(1.0, val[tDN1s] / max(1e-12, /*val[tPreDN1] + */ DNtotsInSim));
    val[fracInDN2New]      =  100 * min(1.0, val[tDN2] / max(1e-12, /*val[tPreDN1] + */ DNtotsInSim));
    //val[fracInDN34New]      =  val[fracInDN3] + val[fracInDN4] ; // + 100 * min(1.0, (val[tDN3] + val[tDN4]  /* val[divDNg0] + val[divDNg1] + val[divDNg2] + val[divDNg3] + val[divDNg4] + val[divDNg5] + val[divDNg6]*/) / max(1e-12, /*val[tPreDN1] + */ manessoDNtot /*DNtotsInSim*/));
    val[fracInDN34New]      =  100 * min(1.0, ( val[divDNg0] + val[divDNg1] + val[divDNg2] + val[divDNg3] + val[divDNg4] + val[divDNg5] + val[divDNg6]) / max(1e-12, /*val[tPreDN1] + */ DNtotsInSim));
#endif
    /*val[floDN1to2] = 0;
    val[floDN2to3] = 0;
    val[floDN3to4] = 0;
    val[flowDN4toDP] = 0;*/

    // Thomas-Vaslin
    val[DN34TS] = val[divDNg0] + val[divDNg1] + val[divDNg2] + val[divDNg3] + val[divDNg4] + val[divDNg5] + val[divDNg6];
    val[eDPtot] = val[eDPg0] + val[eDPg1] + val[eDPg2] + val[eDPg3] + val[eDPg4] + val[eDPg5] + val[eDPg6];
    val[DPtot] = val[eDPtot] + val[lDP];
    val[SP4totTV] = val[divSP4g0] + val[divSP4g1] + val[divSP4g2]; //+ val[restSP4];
    val[SP8totTV] = val[divSP8g0] + val[divSP8g1] + val[divSP8g2]; //+ val[restSP8];

    double fastDiv = 100;
#ifdef ReducedParams
    //val[flowDNtoDP] = fastDiv * val[divDNg4] + 2 * params[pDN] * val[divDNg4];
    val[floweDPtolDP] = (4.5*(- 1 + 2*1.1397 /0.94)) * val[eDPg5] + fastDiv *  val[eDPg6] + 2*params[peDP] * val[eDPg6];
    val[flowDPtoSP4] = params[diffDPtoSP4] *  val[lDP];
    val[flowDPtoSP8] = params[diffDPtoSP8] *  val[lDP];
    //val[flowDNtoDead] = params[dDN] * val[DNtot];
    val[floweDPtoDead] = params[deDP] * val[eDPtot];
    val[flowlDPtoDead] = params[drestDP] * val[eDPtot];
    val[flowSP4toDead] = params[dSP4] * val[SP4totTV];
    val[flowSP8toDead] = params[dSP8] * val[SP8totTV];
#endif

    //val[pctSP8RagN] = 100 * min(1.0, val[] / max(1e-8, val[]));
    val[tSP4] =  val[tTconv] + val[tTRegP25] + val[tTRegPFp3] + val[tTreg];
    val[ttotal] = val[DNtot] + val[DPtot] + val[tSP8] + val[tSP4];
    val[tSP4RagN] = val[tTregRagN] + val[tTregP2RagN] + val[tTconvRagN];
    val[pctDN] =  100 * min(1.0, val[DNtot] / max(1e-8, val[ttotal]));
    val[pctDP] =  100 * min(1.0, val[DPtot] / max(1e-8, val[ttotal]));
    val[pctSP8] = 100 * min(1.0, val[tSP8] / max(1e-8, val[ttotal]));
    val[pctSP4] = 100 * min(1.0, val[tSP4] / max(1e-8, val[ttotal]));
    val[pctTconv] = 100 * min(1.0, val[tTconv] / max(1e-8, val[tSP4]));
    val[pctTRegP1] = 100 * min(1.0, val[tTRegP25] / max(1e-8, val[tSP4]));
    val[pctTRegP2] = 100 * min(1.0, val[tTRegPFp3] / max(1e-8, val[tSP4]));
    val[pctTreg] = 100 * min(1.0, val[tTreg] / max(1e-8, val[tSP4]));
    val[pctSP8RagN] = 100 * min(1.0, val[tSP8RagN] / max(1e-8, val[tSP8]));
    val[pctSP4RagN] = 100 * min(1.0, val[tSP4RagN] / max(1e-8, val[tSP4]));
    val[pctTconvRagN] = 100 * min(1.0, val[tTconvRagN] / max(1e-8, val[tTconv]));
    val[pctTRegP1RagN] = 100 * min(1.0, val[tTregP1RagN] / max(1e-8, val[tTRegP25]));
    val[pctTRegP2RagN] = 100 * min(1.0, val[tTregP2RagN] / max(1e-8, val[tTRegPFp3]));
    val[pctTregRagN] = 100 * min(1.0, val[tTregRagN] / max(1e-8, val[tTreg]));
    val[stotal] = val[sTconv] + val[sTreg] + val[sCD8] + val[sBcells];
    val[pcsTconv] = 100 * min(1.0, val[sTconv] / max(1e-8, val[stotal]));
    val[pcsTreg] = 100 * min(1.0, val[sTreg] / max(1e-8, val[stotal]));
    val[pcsCD8] = 100 * min(1.0, val[sCD8] / max(1e-8, val[stotal]));
    val[pcsBcells] = 100 * min(1.0, val[sBcells] / max(1e-8, val[stotal]));
    val[pcsCD8RagN] = 100 * min(1.0, val[sCD8RagN] / max(1e-8, val[sCD8]));
    val[pcsTregRagN] = 100 * min(1.0, val[sTregRagN] / max(1e-8, val[sTreg]));
    val[pcsTconvRagN] = 100 * min(1.0, val[sTconvRagN] / max(1e-8, val[sTconv]));

    val[flu] = exp(-(t - params[flu_peak]) * (t - params[flu_peak]) / (params[flu_std] * params[flu_std]));
}

void modele4MegaThymus::derivatives(const vector<double> &x, vector<double> &dxdt, const double t){

    double          InflowCoeffETP = 1;
    double          DeathCoeffDN = 1;
    double          DeathCoeffDP = 1;
    double          DeathCoeffTconv = 1;
    double          DeathCoeffProFp3 = 1;
    double          DeathCoeffPro25 = 1;
    double          DeathCoeffDPTregs = 1;
    double          DeathCoeffSP8 = 1;
    double          DeathCoeffEarlyDP = 0; // attention !
    double          OutputCoeffOutDP = 1;
    double          OutputCoeffOutTconv = 1;
    double          OutputCoeffOutDPTregs = 1;
    double          OutputCoeffOutProFP3 = 1;
    double          OutputCoeffOutPro25 = 1;
    double          OutputCoeffOutSP8 = 1;
    double          FasterCoeffDNtoDP = 1;
    double          FasterCoeffProFP3 = 1;
    double          FasterCoeffPro25 = 1;
    double          FasterCoeffTconv = 1;
    double          FasterCoeffSP8 = 1;
    double          SpaceOutputCoeff = 1;
    double          LessDivCoeffDN = 1;
    double          LessDivCoeffDP = 1;
    double          LessDivCoeffTregPro25 = 1;
    double          LessDivCoeffTregProFP3 = 1;
    double          LessDivCoeffDPTreg = 1;
    double          LessDivCoeffTconv = 1;
    double          LessDivCoeffCD8 = 1;
    double          DeathCoeffDN1 = 1;
    double          DeathCoeffDN2 = 1;
    double          DeathCoeffDN3 = 1;
    double          DeathCoeffDN4 = 1;

    if(background & Back::B_ReducedInflow){
        InflowCoeffETP = 1 * (1 - x[flu]) + x[flu] * params[hypInflowCoeffETP];
    }
    if(background & Back::B_MoreDeath){
        DeathCoeffDN         = 1 * (1 - x[flu]) + x[flu] * params[hypDeathCoeffDN];
        DeathCoeffDP         = 1 * (1 - x[flu]) + x[flu] * params[hypDeathCoeffDP];
        DeathCoeffTconv      = 1 * (1 - x[flu]) + x[flu] * params[hypDeathCoeffTconv];
        DeathCoeffProFp3     = 1 * (1 - x[flu]) + x[flu] * params[hypDeathCoeffProFp3];
        DeathCoeffPro25      = 1 * (1 - x[flu]) + x[flu] * params[hypDeathCoeffPro25];
        DeathCoeffDPTregs    = 1 * (1 - x[flu]) + x[flu] * params[hypDeathCoeffDPTregs];
        DeathCoeffSP8        = 1 * (1 - x[flu]) + x[flu] * params[hypDeathCoeffSP8];
        DeathCoeffDN1         = 1 * (1 - x[flu]) + x[flu] * params[hypDeathCoeffDN1];
        DeathCoeffDN2         = 1 * (1 - x[flu]) + x[flu] * params[hypDeathCoeffDN2];
        DeathCoeffDN3         = 1 * (1 - x[flu]) + x[flu] * params[hypDeathCoeffDN3];
        DeathCoeffDN4         = 1 * (1 - x[flu]) + x[flu] * params[hypDeathCoeffDN4];
        DeathCoeffEarlyDP         = 0 * (1 - x[flu]) + x[flu] * params[hypDeathCoeffAddEarlyDP];
    }
    if(background & Back::B_MoreOutputThymus){
        OutputCoeffOutDP	= 1 * (1 - x[flu]) + x[flu] * params[	hypOutputCoeffOutDP	];
        OutputCoeffOutTconv	= 1 * (1 - x[flu]) + x[flu] * params[	hypOutputCoeffOutTconv	];
        OutputCoeffOutDPTregs	= 1 * (1 - x[flu]) + x[flu] * params[	hypOutputCoeffOutDPTregs	];
        OutputCoeffOutProFP3	= 1 * (1 - x[flu]) + x[flu] * params[	hypOutputCoeffOutProFP3	];
        OutputCoeffOutPro25	= 1 * (1 - x[flu]) + x[flu] * params[	hypOutputCoeffOutPro25	];
        OutputCoeffOutSP8	= 1 * (1 - x[flu]) + x[flu] * params[	hypOutputCoeffOutSP8	];
    }
    if(background & Back::B_FasterDifferentiation){
        FasterCoeffDNtoDP	= 1 * (1 - x[flu]) + x[flu] * params[	hypFasterCoeffDNtoDP	];
        FasterCoeffProFP3	= 1 * (1 - x[flu]) + x[flu] * params[	hypFasterCoeffProFP3	];
        FasterCoeffPro25	= 1 * (1 - x[flu]) + x[flu] * params[	hypFasterCoeffPro25	];
        FasterCoeffTconv	= 1 * (1 - x[flu]) + x[flu] * params[	hypFasterCoeffTconv	];
        FasterCoeffSP8	= 1 * (1 - x[flu]) + x[flu] * params[	hypFasterCoeffSP8	];
    }
    if(background & Back::B_SpaceDependentOutput){
        SpaceOutputCoeff  = 1 * (1 - x[flu]) + x[flu] * params[hypSpaceOutputCoeff];
    }
    if(background & Back::B_DivisionReduced){
        LessDivCoeffDN = 1 * (1 - x[flu]) + x[flu] * params[hypLessDivDN];
        LessDivCoeffDP = 1 * (1 - x[flu]) + x[flu] * params[hypLessDivDP];
        LessDivCoeffTregPro25 = 1 * (1 - x[flu]) + x[flu] * params[hypLessDivTregPro25];
        LessDivCoeffTregProFP3 = 1 * (1 - x[flu]) + x[flu] * params[hypLessDivTregProFP3];
        LessDivCoeffDPTreg = 1 * (1 - x[flu]) + x[flu] * params[hypLessDivDPTreg],
        LessDivCoeffTconv = 1 * (1 - x[flu]) + x[flu] * params[hypLessDivTconv];
        LessDivCoeffCD8 = 1 * (1 - x[flu]) + x[flu] * params[hypLessDivCD8];
    }
    if(background & Back::B_LogisticTotalProlif){
        double coeff = (1/(1 - 1 / (params[logisticStrength]+1e-9)))*(1 - ((1/(params[logisticStrength] + 1e-9))*x[ttotal] / (params[logisticThymus] + 1e-9)));
        //    double coeff = 2*(1 - (0.5*x[ttotal] / (init[tDN] + init[tDP] + init[tTconv] + init[tTRegP25] + init[tTRegPFp3] + init[tTreg] + init[tSP8] + 1e-9)));
        LessDivCoeffDN *= coeff;
        LessDivCoeffDP *= coeff;
        LessDivCoeffTregPro25 *= coeff;
        LessDivCoeffTregProFP3 *= coeff;
        LessDivCoeffDPTreg *= coeff;
        LessDivCoeffTconv *= coeff;
        LessDivCoeffCD8 *= coeff;
    }

    // Equations for DN stages from Manesso et al.
    if(!over(tPreDN1)) {
         dxdt[tPreDN1] 	= InflowCoeffETP * params[fETP_tDN] -x[tPreDN1] / (params[decayDN1pre] + 1e-12);
    }
    if(!over(tDN1g0)) {
         dxdt[tDN1g0] 	= x[tPreDN1] / (params[decayDN1pre] + 1e-12) - x[tDN1g0] / (params[cycleDN1] + 1e-12);
    }
    if(!over(tDN1g1)) {
         dxdt[tDN1g1] 	= (2 * x[tDN1g0] * (1 - DeathCoeffDN1 * params[deathDN1]) - x[tDN1g1]) / (params[cycleDN1] + 1e-12); // don't get why 1/cycle = death and prolif ... maybe it's not the same.
    }
    if(!over(tDN1g2)) {
        dxdt[tDN1g2] 	= (2 * x[tDN1g1] * (1 - DeathCoeffDN1 * params[deathDN1]) - x[tDN1g2]) / (params[cycleDN1] + 1e-12);
    }
    if(!over(tDN1g3)) {
        dxdt[tDN1g3] 	= (2 * x[tDN1g2] * (1 - DeathCoeffDN1 * params[deathDN1]) - x[tDN1g3]) / (params[cycleDN1] + 1e-12);
    }
    if(!over(tDN1g4)) {
        dxdt[tDN1g4] 	= (2 * x[tDN1g3] * (1 - DeathCoeffDN1 * params[deathDN1]) - x[tDN1g4]) / (params[cycleDN1] + 1e-12);
    }
    if(!over(tDN1g5)) {
        dxdt[tDN1g5] 	= (2 * x[tDN1g4] * (1 - DeathCoeffDN1 * params[deathDN1]) - x[tDN1g5]) / (params[cycleDN1] + 1e-12);
    }
    if(!over(tDN1g6)) {
        dxdt[tDN1g6] 	= (2 * x[tDN1g5] * (1 - DeathCoeffDN1 * params[deathDN1]) - x[tDN1g6]) / (params[cycleDN1] + 1e-12);
    }
    if(!over(tDN1g7)) {
        dxdt[tDN1g7] 	= (2 * x[tDN1g6] * (1 - DeathCoeffDN1 * params[deathDN1]) - x[tDN1g7]) / (params[cycleDN1] + 1e-12);
    }
    if(!over(tDN1g8)) {
        dxdt[tDN1g8] 	= (2 * x[tDN1g7] * (1 - DeathCoeffDN1 * params[deathDN1]) - x[tDN1g8]) / (params[cycleDN1] + 1e-12);
    }
    if(!over(tDN1g9)) {
        dxdt[tDN1g9] 	= (2 * x[tDN1g8] * (1 - DeathCoeffDN1 * params[deathDN1]) - x[tDN1g9]) / (params[cycleDN1] + 1e-12);
    }
    if(!over(tDN1g10)) {
        dxdt[tDN1g10] 	= (2 * x[tDN1g9] * (1 - DeathCoeffDN1 * params[deathDN1]) - x[tDN1g10]) / (params[cycleDN1] + 1e-12);
    }
    if(!over(tDN1g11)) {
        dxdt[tDN1g11] 	= (2 * x[tDN1g10] * (1 - DeathCoeffDN1 * params[deathDN1]) - x[tDN1g11]) / (params[cycleDN1] + 1e-12);
    }
    if(!over(tDN2)) {
        dxdt[tDN2] 	= (x[tDN1g11] * params[commitDN1to2]) / (params[cycleDN1] + 1e-12) + (1 - 2*params[commitDN2to3] - 2*DeathCoeffDN2*params[deathDN2]) * x[tDN2] / (params[cycleDN2] + 1e-12);
    }





    // discarding DN3 and DN4 from manesso, because wrong dynamics
    if(!over(tDN3)) {
        dxdt[tDN3] 	= (x[tDN2] * params[commitDN2to3]) / (params[cycleDN2] + 1e-12) + (1 - 2*params[commitDN3to4] - 2*DeathCoeffDN3*params[deathDN3]) * x[tDN3]/ (params[cycleDN3] + 1e-12);
    }
    if(!over(tDN4)) {
        dxdt[tDN4] 	= (x[tDN3] * params[commitDN3to4]) / (params[cycleDN3] + 1e-12) + (1 - 2*params[commitDN4toDP] - 2*DeathCoeffDN4*params[deathDN4]) * x[tDN4] / (params[cycleDN4] + 1e-12);
    }





    // Division parameters, TV. Note: this needs to be recomputed each time because ndiv might be a dynamic parameter.
    double dynamicNDiv = FasterCoeffDNtoDP *  params[NdivDN];
    int N = (int) dynamicNDiv;
    double divFloat = dynamicNDiv - (double) N;
    double T_DN = 1 / (max(params[pDN] + params[dDN], 1e-12));
    double C = 0;
    if(divFloat < 1e-12) {N = max(0,N-1);} else {C = min(100., (1 / T_DN) * ((1 / divFloat) - 1));}
    N = min(6,N); // to avoid segfault

    vector<double> CoeffPerGen = vector<double>(7, 0);
    CoeffPerGen[N] = 0; // decide o C ??C; // why putting 0 ?????
    for(int i = N+1; i <=6;++i){
        CoeffPerGen[i] = 0; //100;
    }
    vector<double> DoProlif = vector<double>(7, 0);
    for(int i = 0; i < N; ++i){
        DoProlif[i] = 1.0;
    }
    DoProlif[N] = divFloat;
    if(dynamicNDiv < 1e-12) DoProlif[0] = 0;




    // Note: even if a population is not proliferating, it should still be simulated. Indeed, Ndiv can be dynamic, and it might be cells remaining in that stage.
    double InflowToDN34 = (x[tDN2] * params[commitDN2to3]) / (max(params[cycleDN2] , 1e-12));

    if(!over( divDNg0)) {
        dxdt[divDNg0] 	=  InflowToDN34 +                                               ( - params[pDN] * LessDivCoeffDN - CoeffPerGen[0]  - params[dDN] * DeathCoeffDN * DeathCoeffDN3) * x[divDNg0];
    }
    if(!over( divDNg1)) {
        dxdt[divDNg1] 	= 2 * DoProlif[0] * params[pDN] * LessDivCoeffDN * x[divDNg0] + ( - params[pDN] * LessDivCoeffDN - CoeffPerGen[1]  - params[dDN] * DeathCoeffDN * DeathCoeffDN3) *  x[divDNg1];
    }
    if(!over( divDNg2)) {
        dxdt[divDNg2] 	= 2 * DoProlif[1] * params[pDN] * LessDivCoeffDN * x[divDNg1] + ( - params[pDN] * LessDivCoeffDN - CoeffPerGen[2]  - params[dDN] * DeathCoeffDN * DeathCoeffDN3) * x[divDNg2];
    }
    if(!over( divDNg3)) {
        dxdt[divDNg3] 	= 2 * DoProlif[2] * params[pDN] * LessDivCoeffDN * x[divDNg2] + ( - params[pDN] * LessDivCoeffDN - CoeffPerGen[3]  - params[dDN] * DeathCoeffDN * DeathCoeffDN3) * x[divDNg3];
    }
    if(!over( divDNg4)) {
        dxdt[divDNg4] 	= 2 * DoProlif[3] * params[pDN] * LessDivCoeffDN * x[divDNg3] + ( - params[pDN] * LessDivCoeffDN - CoeffPerGen[4]  - params[dDN] * DeathCoeffDN * DeathCoeffDN3) * x[divDNg4];
    }
    if(!over( divDNg5)) {
        dxdt[divDNg5] 	= 2 * DoProlif[4] * params[pDN] * LessDivCoeffDN * x[divDNg4] + ( - params[pDN] * LessDivCoeffDN - CoeffPerGen[5]  - params[dDN] * DeathCoeffDN * DeathCoeffDN3) * x[divDNg5]; // just very fast, no prolif
    }
    if(!over( divDNg6)) {
        dxdt[divDNg6] 	= 2 * DoProlif[5] * params[pDN] * LessDivCoeffDN * x[divDNg5] + ( - params[pDN] * LessDivCoeffDN - CoeffPerGen[6]  - params[dDN] * DeathCoeffDN * DeathCoeffDN3) * x[divDNg6]; // just very fast, no prolif
    }
    double outflowToDP = 0; //*C * x[divDNg0 + N] +*/ 2*x[divDNg0 + N] * params[pDN] * LessDivCoeffDN;
    // The cells that are remaining in a compartment are still leaving the compartment (as they enter, they can still complete the cycle)
    for(int i = 0; i < 6; ++i){
        outflowToDP +=  CoeffPerGen[i] * x[divDNg0 + i];
        outflowToDP += 2 * (1 - DoProlif[i]) * params[pDN] * LessDivCoeffDN * x[divDNg0 + i];
    }

    // now from TVaslin for the DN3 and DN4 compartments combined
    double fastDiv = 100.0;

    // early (proliferating) and late (resting) DPs from thomas-Vaslin 2007 JI. Note: DN4 proliferation stays in DN4 and only commitment leads to DP.
    if(!over( eDPg0)) {
        dxdt[eDPg0] 	= /*params[commitDN4toDP] * x[tDN4]*/ outflowToDP + ( - params[peDP] * LessDivCoeffDP - params[deDP] - DeathCoeffEarlyDP) * x[eDPg0];
    }
    if(!over( eDPg1)) {
        dxdt[eDPg1] 	= 2 * params[peDP] * LessDivCoeffDP * x[eDPg0] + ( - params[peDP] * LessDivCoeffDP - params[deDP] - DeathCoeffEarlyDP) * x[eDPg1];
    }
    if(!over( eDPg2)) {
        dxdt[eDPg2] 	= 2 * params[peDP] * LessDivCoeffDP * x[eDPg1] + ( - params[peDP] * LessDivCoeffDP - params[deDP] - DeathCoeffEarlyDP) * x[eDPg2];
    }
    if(!over( eDPg3)) {
        dxdt[eDPg3] 	= 2 * params[peDP] * LessDivCoeffDP * x[eDPg2] + ( - params[peDP] * LessDivCoeffDP - params[deDP] - DeathCoeffEarlyDP) * x[eDPg3];
    }
    if(!over( eDPg4)) {
        dxdt[eDPg4] 	= 2 * params[peDP] * LessDivCoeffDP * x[eDPg3] + ( - params[peDP] * LessDivCoeffDP - params[deDP] - DeathCoeffEarlyDP) * x[eDPg4];
    }
    if(!over( eDPg5)) {
        dxdt[eDPg5] 	= 2 * params[peDP] * LessDivCoeffDP * x[eDPg4] + ( - (4.5*(- 1 + 2*1.1397 /0.94)) - params[peDP] * LessDivCoeffDP - params[deDP] - DeathCoeffEarlyDP) * x[eDPg5]; // the coeffecient given by (alppha^n) is wrong. probably wrong rounfding up of 0.2^127. The formula here extracts the coefficient of outflow from table III in the JI paper 2007
    }
    if(!over( eDPg6)) {
        dxdt[eDPg6] 	= 2 * params[peDP] * LessDivCoeffDP * x[eDPg5] + ( - params[peDP] * LessDivCoeffDP - 100  - params[deDP] - DeathCoeffEarlyDP) * x[eDPg6];
    }
    if(!over( lDP)) {
        dxdt[lDP] 	= (4.5*(- 1 + 2*1.1397 /0.94)) * x[eDPg5] + fastDiv *  x[eDPg6] + 2*params[peDP] * LessDivCoeffDP * x[eDPg6] + (- params[drestDP] * DeathCoeffDP - params[diffDPtoSP4]* FasterCoeffTconv - params[diffDPtoSP8] * FasterCoeffSP8) * x[lDP];
    }


    // If SP4 and SP8 are simulated by thomas-vaslin
    if(!over( divSP4g0)) {
        dxdt[divSP4g0] 	= params[diffDPtoSP4] * FasterCoeffTconv *  x[lDP] + (- params[pSP4] * LessDivCoeffTconv  - params[dSP4] * DeathCoeffTconv) * x[divSP4g0];
    }
    if(!over( divSP4g1)) {
        dxdt[divSP4g1] 	= 2 * params[pSP4] * x[divSP4g0] + (- params[pSP4] * LessDivCoeffTconv  - params[dSP4] * DeathCoeffTconv - params[pcConvLastGenSP4]) * x[divSP4g1];
    }
    if(!over( divSP4g2)) {
        dxdt[divSP4g2] 	= 2 * params[pSP4] * x[divSP4g1] + (/* no prolif */  - params[dSP4] * DeathCoeffTconv - 100) * x[divSP4g2];
    }
    if(!over( divSP8g0)) {
        dxdt[divSP8g0] 	= params[diffDPtoSP8] * FasterCoeffSP8 *  x[lDP] + (- params[pSP8] * LessDivCoeffCD8  - params[dSP8] * DeathCoeffSP8) * x[divSP8g0];
    }
    if(!over( divSP8g1)) {
        dxdt[divSP8g1] 	= 2 * params[pSP8] * x[divSP8g0] + (- params[pSP8] * LessDivCoeffCD8  - params[dSP8] * DeathCoeffSP8 - params[pcConvLastGenSP8]) * x[divSP8g1];
    }
    if(!over( divSP8g2)) {
        dxdt[divSP8g2] 	= 2 * params[pSP8] * x[divSP8g1] + (- params[pSP8] * LessDivCoeffCD8  - params[dSP8] * DeathCoeffSP8 - 100) * x[divSP8g2];
    }


   // If SP4 and SP8 were simulated by thomas-vaslin
   if(!over(tTconv)) {
        dxdt[tTconv] 	= params[in_tTconv] * x[sTconv]  + x[lDP] * FasterCoeffTconv * params[ftDP_tTConv] + x[tTconv] * (- SpaceOutputCoeff * OutputCoeffOutTconv * params[out_tTconv] + LessDivCoeffTconv * params[ptTconv] - DeathCoeffTconv * params[dtTconv]);
   }
   if(!over(tTRegP25)) {
        dxdt[tTRegP25] 	=   x[lDP] * FasterCoeffPro25 * params[ftDP_tTregP25] + x[tTRegP25] * (- SpaceOutputCoeff * OutputCoeffOutPro25 * params[out_tTregP25] + LessDivCoeffTregPro25 * params[ptTregP25] - params[ftTregP25_tDPTreg] - DeathCoeffPro25 * params[dtTregP25]);
   }
   if(!over(tTRegPFp3)) {
        dxdt[tTRegPFp3] 	= params[in_tTregPFp3] * x[sTreg] + x[lDP] * FasterCoeffProFP3 * params[ftDP_tTregFP3] + x[tTRegPFp3] * ( - SpaceOutputCoeff * OutputCoeffOutProFP3 * params[out_tTregFP3] + LessDivCoeffTregProFP3 * params[ptTregFP3] - params[ftTregFP3_tDPTreg] - DeathCoeffProFp3 * params[dtTregFP3]);
   }
   if(!over(tTreg)) {
        dxdt[tTreg] 	= params[in_tDPTregs] * x[sTreg] +  x[tTRegP25] * params[ftTregP25_tDPTreg] + x[tTRegPFp3] * params[ftTregFP3_tDPTreg] + x[tTreg] * (- SpaceOutputCoeff * OutputCoeffOutDPTregs * params[out_tDPTregs]  + LessDivCoeffDPTreg * params[ptDPTregs] - DeathCoeffDPTregs * params[dtDPTregs]);
   }
   if(!over(tSP8)) {
        dxdt[tSP8] 	= params[in_SP8] * x[sCD8]  + x[lDP] * FasterCoeffSP8 * params[ftDP_tSP8] + x[tSP8] * (- SpaceOutputCoeff * OutputCoeffOutSP8 * params[out_SP8] + LessDivCoeffCD8 * params[ptSP8] - DeathCoeffSP8 * params[dtSP8]);
   }

   // Careful, make the rag- as an exit the pool of Rag+
   if(!over(tTconvRagN)) {
        dxdt[tTconvRagN] 	= params[in_tTconv] * x[sTconvRagN] +  x[tTconv] * params[decayRag] + x[tTconvRagN] * (- SpaceOutputCoeff * OutputCoeffOutTconv * params[out_tTconv] + LessDivCoeffTconv * params[ptTconv] - DeathCoeffTconv * params[dtTconv]);
   }
   if(!over(tTregP1RagN)) {
        dxdt[tTregP1RagN] 	=                                      x[tTRegP25] * params[decayRag] + x[tTregP1RagN] * (- SpaceOutputCoeff * OutputCoeffOutPro25 * params[out_tTregP25] + LessDivCoeffTregPro25 * params[ptTregP25] - params[ftTregP25_tDPTreg] - DeathCoeffPro25 * params[dtTregP25]);
   }
   if(!over(tTregP2RagN)) {
        dxdt[tTregP2RagN] = params[in_tTregPFp3] * x[sTregRagN] +  x[tTRegPFp3] * params[decayRag] + x[tTregP2RagN] * ( - SpaceOutputCoeff * OutputCoeffOutProFP3 * params[out_tTregFP3] + LessDivCoeffTregProFP3 * params[ptTregFP3] - params[ftTregFP3_tDPTreg] - DeathCoeffProFp3 * params[dtTregFP3]);
   }
   if(!over(tTregRagN)) {
        dxdt[tTregRagN] 	= params[in_tDPTregs] * x[sTregRagN] + x[tTreg] * params[decayRag] +
            x[tTregP1RagN] * params[ftTregP25_tDPTreg] + x[tTregP2RagN] * params[ftTregFP3_tDPTreg] + x[tTregRagN] * (- SpaceOutputCoeff * OutputCoeffOutDPTregs * params[out_tDPTregs]  + LessDivCoeffDPTreg * params[ptDPTregs] - DeathCoeffDPTregs * params[dtDPTregs]);
   }
   if(!over(tSP8RagN)) {
        dxdt[tSP8RagN] 	= params[in_SP8] * x[sCD8RagN]  + x[tSP8] * params[decayRag] + x[tSP8RagN] * (- SpaceOutputCoeff * OutputCoeffOutSP8 * params[out_SP8]                               + LessDivCoeffCD8 * params[ptSP8] - DeathCoeffSP8 * params[dtSP8]);
   }

   // where do outDP go ??? where do the treg precursors go ?
   // inflow of Precursors, does it make sense ?
   if(!over(sTconv)){
       dxdt[sTconv] = params[out_tTconv] * params[fracTtoS] * x[tTconv] - x[sTconv] * (params[in_tTconv] + params[dsTconv]);
   }
   if(!over(sTreg)){
       dxdt[sTreg] = params[out_tDPTregs] * params[fracTtoS] * x[tTreg] - x[sTreg] * (params[in_tDPTregs] + params[in_tTregPFp3] + params[dsTreg]);
   }
   if(!over(sCD8)){
       dxdt[sCD8] = params[out_SP8] * params[fracTtoS] * x[tSP8] - x[sCD8] * (params[in_SP8] + params[dsCD8]);
   }

   if(!over(sTconvRagN)){
       dxdt[sTconvRagN] = x[sTconv] * params[decayRag] + params[out_tTconv] * params[fracTtoS] * x[tTconvRagN] - x[sTconvRagN] * (params[in_tTconv] + params[dsTconv]);
   }
   if(!over(sTregRagN)){
       dxdt[sTregRagN] = x[sTreg] * params[decayRag] + params[out_tDPTregs] * params[fracTtoS] * x[tTregRagN] - x[sTregRagN] * (params[in_tDPTregs] + params[in_tTregPFp3] + params[dsTreg]);
   }
   if(!over(sCD8RagN)){
       dxdt[sCD8RagN] = x[sCD8] * params[decayRag] + params[out_SP8] * params[fracTtoS] * x[tSP8RagN] - x[sCD8RagN] * (params[in_SP8] + params[dsCD8]);
   }

}
