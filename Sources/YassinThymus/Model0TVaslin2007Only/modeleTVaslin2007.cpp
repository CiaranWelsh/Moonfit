// ------- Automatically generated model -------- //
#include "modeleTVaslin2007.h"

//#include <sstream>

ModeleTVaslin2007::ModeleTVaslin2007() : Model(NBVAR, NBPARAM), background(Back::WT) {


    name = string("modele0Thomas-Vaslin2007 (JI)");
    dt = 0.00001; // initial time step -> then it is adaptive
    print_every_dt = 1200; //every how many seconds it is plotting

//        divDNg0, divDNg1, divDNg2, divDNg3, divDNg4, divDNg5, divDNg6, eDPg0, eDPGg1, eDPg2, eDPg3, eDPg4, eDPg5, eDPg6, lDP, divSP4g0, divSP4g1, divSP4g2, restSP4, divSP8g0, divSP8g1, divSP8g2, restSP8, DNtot, DPtot, SP4tot, SP8tot,
//        infloDN, NdivDN, pDN, dDN, NdivDP, peDP, deDP, prestDP, drestDP, diffDPtoSP4, diffDPtoSP8, pSP4, dSP4, NdivSP4, pSP8, dSP8, NdivSP8,
/*    flowDNtoDP,
            floweDPtolDP
    flowDPtoSP4,
    flowDPtoSP8,
    flowDNtoDead,
    floweDPtoDead,
    flowlDPtoDead,
    flowSP4toDead,
    flowSP8toDead,
*/
    names[ flu] = string("flu");
    names[ divDNg0] = string("divDNg0");
    names[ divDNg1] = string("divDNg1");
    names[ divDNg2] = string("divDNg2");
    names[ divDNg3] = string("divDNg3");
    names[ divDNg4] = string("divDNg4");
    names[ divDNg5] = string("divDNg5");
    names[ divDNg6] = string("divDNg6");
    names[ eDPg0] = string("eDPg0");
    names[ eDPg1] = string("eDPGg1");
    names[ eDPg2] = string("eDPg2");
    names[ eDPg3] = string("eDPg3");
    names[ eDPg4] = string("eDPg4");
    names[ eDPg5] = string("eDPg5");
    names[ eDPg6] = string("eDPg6");
    names[ lDP] = string("lDP");
    names[ divSP4g0] = string("divSP4g0");
    names[ divSP4g1] = string("divSP4g1");
    names[ divSP4g2] = string("divSP4g2");
    names[ restSP4] = string("restSP4");
    names[ divSP8g0] = string("divSP8g0");
    names[ divSP8g1] = string("divSP8g1");
    names[ divSP8g2] = string("divSP8g2");
    names[ restSP8] = string("restSP8");
    names[ DNtot] = string("DNtot");
    names[ eDPtot] = string("eDPtot");
    names[ DPtot] = string("DPtot");
    names[ SP4tot] = string("SP4tot");
    names[ SP8tot] = string("SP8tot");
    names[ flowDNtoDP] = string("flowDNtoDP");
    names[ floweDPtolDP] = string("floweDPtolDP");
    names[ flowDPtoSP4] = string("flowDPtoSP4");
    names[ flowDPtoSP8] = string("flowDPtoSP8");
    names[ flowDNtoDead] = string("flowDNtoDead");
    names[ floweDPtoDead] = string("floweDPtoDead");
    names[ flowlDPtoDead] = string("flowlDPtoDead");
    names[ flowSP4toDead] = string("flowSP4toDead");
    names[ flowSP8toDead] = string("flowSP8toDead");

	// the names of variables that can be accessed by outside (by setValue and getValue)
    extNames[DNtot] = GlobalName(N::tDN);
    extNames[DPtot] = GlobalName(N::tDP);
    extNames[SP4tot] = GlobalName(N::tSP4tot);
    extNames[SP8tot] = GlobalName(N::tSP8tot);

    paramNames[flu_peak] = "flu_peak / peak of flu effect in days";
    paramNames[flu_std]  = "flu_std / width of flu effect (stddev)";
    paramNames[ infloDN] = string("infloDN");
    paramNames[ NdivDN] = string("NdivDN");
    paramNames[ pDN] = string("pDN");
    paramNames[ dDN] = string("dDN");
    paramNames[ NdivDP] = string("NdivDP");
    paramNames[ peDP] = string("peDP");
    paramNames[ deDP] = string("deDP");
    paramNames[ prestDP] = string("prestDP");
    paramNames[ drestDP] = string("drestDP");
    paramNames[ diffDPtoSP4] = string("diffDPtoSP4");
    paramNames[ diffDPtoSP8] = string("diffDPtoSP8");
    paramNames[ pSP4] = string("pSP4");
    paramNames[ dSP4] = string("dSP4");
    paramNames[ NdivSP4] = string("NdivSP4");
    paramNames[ pSP8] = string("pSP8");
    paramNames[ dSP8] = string("dSP8");
    paramNames[ NdivSP8] = string("NdivSP8");
    paramNames[	hypInflowCoeffETP	]="	hypInflowCoeffETP	";
    paramNames[	hypDeathCoeffDN ]="hypDeathCoeffDN",
    paramNames[	hypDeathCoeffDP	]="	hypDeathCoeffDP	";
    paramNames[	hypDeathCoeffTconv	]="	hypDeathCoeffTconv	";
    paramNames[	hypDeathCoeffSP8	]="	hypDeathCoeffSP8	";
    paramNames[	hypOutputCoeffOutDP	]="	hypOutputCoeffOutDP	";
    paramNames[	hypOutputCoeffOutTconv	]="	hypOutputCoeffOutTconv	";
    paramNames[	hypOutputCoeffOutSP8	]="	hypOutputCoeffOutSP8	";
    paramNames[	hypFasterCoeffDNtoDP	]="	hypFasterCoeffDNtoDP	";
    paramNames[	hypFasterCoeffTconv	]="	hypFasterCoeffTconv	";
    paramNames[	hypFasterCoeffSP8	]="	hypFasterCoeffSP8	";
    paramNames[	hypSpaceOutputCoeff	]="	hypSpaceOutputCoeff	";
    paramNames[	hypLessDivDN	]="CoeffDivDN";
    paramNames[	hypLessDivDP	]="CoeffDivDP";
    paramNames[	hypLessDivTconv	]="CoeffDivTconv";
    paramNames[	hypLessDivCD8	]="CoeffDivCD8";
    paramNames[ logisticThymus] = "logisticSizeThymus";
    paramNames[ logisticStrength] = "logisticStrength";

    paramLowBounds[flu_peak]    = 	5;              paramUpBounds[flu_peak]     = 	15;
    paramLowBounds[flu_std]     = 	0.5;			paramUpBounds[flu_std]      = 	10;
    paramLowBounds[ infloDN] 	= 0;		paramUpBounds[infloDN] 	= 0;
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
    paramLowBounds[ hypInflowCoeffETP] 	= 0;		paramUpBounds[hypInflowCoeffETP] 	= 0;
    paramLowBounds[ hypDeathCoeffDN] 	= 0;		paramUpBounds[hypDeathCoeffDN] 	= 0;
    paramLowBounds[	hypInflowCoeffETP	] = 	0.05	;				paramUpBounds[	hypInflowCoeffETP	] = 	20	;
    paramLowBounds[	hypDeathCoeffDN  ] = 0.05;                      paramUpBounds[	hypDeathCoeffDN	] = 	20	;
    paramLowBounds[	hypDeathCoeffDP	] = 	0.05	;				paramUpBounds[	hypDeathCoeffDP	] = 	20	;
    paramLowBounds[	hypDeathCoeffTconv	] = 	0.05	;				paramUpBounds[	hypDeathCoeffTconv	] = 	20	;
    paramLowBounds[	hypDeathCoeffSP8	] = 	0.05	;				paramUpBounds[	hypDeathCoeffSP8	] = 	20	;
    paramLowBounds[	hypOutputCoeffOutDP	] = 	0.05	;				paramUpBounds[	hypOutputCoeffOutDP	] = 	20	;
    paramLowBounds[	hypOutputCoeffOutTconv	] = 	0.05	;				paramUpBounds[	hypOutputCoeffOutTconv	] = 	20	;
    paramLowBounds[	hypOutputCoeffOutSP8	] = 	0.05	;				paramUpBounds[	hypOutputCoeffOutSP8	] = 	20	;
    paramLowBounds[	hypFasterCoeffDNtoDP	] = 	0.05	;				paramUpBounds[	hypFasterCoeffDNtoDP	] = 	20	;
    paramLowBounds[	hypFasterCoeffTconv	] = 	0.05	;				paramUpBounds[	hypFasterCoeffTconv	] = 	20	;
    paramLowBounds[	hypFasterCoeffSP8	] = 	0.05	;				paramUpBounds[	hypFasterCoeffSP8	] = 	20	;
    paramLowBounds[	hypSpaceOutputCoeff	] = 	0.05	;				paramUpBounds[	hypSpaceOutputCoeff	] = 	20	;
    paramLowBounds[	hypLessDivDN	] = 	0.01	;				paramUpBounds[hypLessDivDN	] = 	20	;
    paramLowBounds[	hypLessDivDP	] = 	0.01	;				paramUpBounds[hypLessDivDP] = 	20	;
    paramLowBounds[	hypLessDivTconv	] = 	0.01	;				paramUpBounds[hypLessDivTconv] = 	20	;
    paramLowBounds[	hypLessDivCD8	] = 	0.01	;				paramUpBounds[hypLessDivCD8] = 	20	;
    paramLowBounds[ logisticThymus ] = 0.1;                         paramUpBounds[logisticThymus] = 500;
    paramLowBounds[ logisticStrength] = 0.1;                        paramUpBounds[logisticStrength] = 10;
}

void ModeleTVaslin2007::setBaseParameters(){
	params.clear();     // to make sure they are all put to zero
	params.resize(NBPARAM, 0.0);

    // scenario 5
    params[flu_peak]        = 9;
    params[flu_std]         = 2.5;
    params[ infloDN] = 0.02 ; // in millions
    params[ NdivDN] = 4; // alpha = 0.29, n = 127 <-> DNg4 all convert to next but none of g3
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
    params[ hypInflowCoeffETP] = 1;
    params[ hypDeathCoeffDN] = 1;
    params[	hypDeathCoeffDP	] = 	1	;
    params[	hypDeathCoeffTconv	] = 	1	;
    params[	hypDeathCoeffSP8	] = 	1	;
    params[	hypOutputCoeffOutDP	] = 	1	;
    params[	hypOutputCoeffOutTconv	] = 	1	;
    params[	hypOutputCoeffOutSP8	] = 	1	;
    params[	hypFasterCoeffDNtoDP	] = 	1	;
    params[	hypFasterCoeffTconv	] = 	1	;
    params[	hypFasterCoeffSP8	] = 	1	;
    params[	hypSpaceOutputCoeff	] = 	1	;
    params[	hypLessDivDN	] = 	1	;
    params[	hypLessDivDP	] = 	1	;
    params[	hypLessDivTconv	] = 	1	;
    params[	hypLessDivCD8	] = 	1	;
    params[ logisticThymus ] = 90;
    params[ logisticStrength] = 2.0;

	setBaseParametersDone();
}

void ModeleTVaslin2007::initialise(long long _background){ // don't touch to parameters !
	background = _background;
	val.clear();
	val.resize(NBVAR, 0.0);
	init.clear();
	init.resize(NBVAR, 0.0);

if(background & Back::B_StartSteadyState){
    init[ divDNg0] = 0.09;
    init[ divDNg1] = 0.18;
    init[ divDNg2] = 0.36;
    init[ divDNg3] = 0.72;
    init[ divDNg4] = 0.003;
    init[ divDNg5] = 0;
    init[ divDNg6] = 0;
    init[ eDPg0] = 0.07;
    init[ eDPg1] = 0.14;
    init[ eDPg2] = 0.29;
    init[ eDPg3] = 0.58;
    init[ eDPg4] = 1.16;
    init[ eDPg5] = 0.94;
    init[ eDPg6] = 0.08;
    init[ lDP] = 40.29;
    init[ divSP4g0] = 4.02;
    init[ divSP4g1] = 2.49;
    init[ divSP4g2] = 0.01;
    init[ restSP4] = 0;
    init[ divSP8g0] = 0.77;
    init[ divSP8g1] = 0.48;
    init[ divSP8g2] = 0.002;
    init[ restSP8] = 0;
    init[ DNtot] = 0;
    init[ eDPtot] = 0;
    init[ DPtot] = 0;
    init[ SP4tot] = 0;
    init[ SP8tot] = 0;
    init[ flowDNtoDP] = 0;
    init[ floweDPtolDP] = 0;
    init[ flowDPtoSP4] = 0;
    init[ flowDPtoSP8] = 0;
    init[ flowDNtoDead] = 0;
    init[ floweDPtoDead] = 0;
    init[ flowlDPtoDead] = 0;
    init[ flowSP4toDead] = 0;
    init[ flowSP8toDead] = 0;
}

	for(int i = 0; i < NBVAR; ++i){
		val[i] = init[i];}
	t = 0;
	initialiseDone();
}

void ModeleTVaslin2007::updateDerivedVariables(){
    val[DNtot] = val[divDNg0] + val[divDNg1] + val[divDNg2] + val[divDNg3] + val[divDNg4] + val[divDNg5] + val[divDNg6];
    val[eDPtot] = val[eDPg0] + val[eDPg1] + val[eDPg2] + val[eDPg3] + val[eDPg4] + val[eDPg5] + val[eDPg6];
    val[DPtot] = val[eDPtot] + val[lDP];
    val[SP4tot] = val[divSP4g0] + val[divSP4g1] + val[divSP4g2] + val[restSP4];
    val[SP8tot] = val[divSP8g0] + val[divSP8g1] + val[divSP8g2] + val[restSP8];

    double fastDiv = 100;
    val[flowDNtoDP] = fastDiv * val[divDNg4] + 2 * params[pDN] * val[divDNg4];
    val[floweDPtolDP] = (4.5*(- 1 + 2*1.1397 /0.94)) * val[eDPg5] + fastDiv *  val[eDPg6] + 2*params[peDP] * val[eDPg6];
    val[flowDPtoSP4] = params[diffDPtoSP4] *  val[lDP];
    val[flowDPtoSP8] = params[diffDPtoSP8] *  val[lDP];
    val[flowDNtoDead] = params[dDN] * val[DNtot];
    val[floweDPtoDead] = params[deDP] * val[eDPtot];
    val[flowlDPtoDead] = params[drestDP] * val[eDPtot];
    val[flowSP4toDead] = params[dSP4] * val[SP4tot];
    val[flowSP8toDead] = params[dSP8] * val[SP8tot];

    val[flu] = exp(-(t - params[flu_peak]) * (t - params[flu_peak]) / (params[flu_std] * params[flu_std]));
}

void ModeleTVaslin2007::derivatives(const vector<double> &x, vector<double> &dxdt, const double t){

    //if(!over(tDN1g10)) {
    //    dxdt[tDN1g10] 	= (2 * x[tDN1g9] * (1 - DeathCoeffDN1 * params[deathDN1]) - x[tDN1g10]) / (params[cycleDN1] + 1e-12);
    //}

    //, NdivDN, pDN, dDN, NdivDP, peDP, deDP, prestDP, drestDP, diffDPtoSP4, diffDPtoSP8, pSP4, dSP4, NdivSP4, pSP8, dSP8, NdivSP8,
    double          InflowCoeffETP = 1;
    double          DeathCoeffDN = 1;
    double          DeathCoeffDP = 1;
    double          DeathCoeffTconv = 1;
    double          DeathCoeffSP8 = 1;
    //double          OutputCoeffOutDP = 1; // similar to death !!!
    //double          OutputCoeffOutTconv = 1;
    //double          OutputCoeffOutSP8 = 1;
    double          FasterCoeffDNtoDP = 1;
    double          FasterCoeffTconv = 1;
    double          FasterCoeffSP8 = 1;
    //double          SpaceOutputCoeff = 1;
    double          LessDivCoeffDN = 1;
    double          LessDivCoeffDP = 1;
    double          LessDivCoeffTconv = 1;
    double          LessDivCoeffCD8 = 1;

            // Change: put a logical or/and
    if(background & Back::B_ReducedInflow){
        InflowCoeffETP = 1 * (1 - x[flu]) + x[flu] * params[hypInflowCoeffETP];
    }
    if(background & Back::B_MoreDeath){
        DeathCoeffDN         = 1 * (1 - x[flu]) + x[flu] * params[hypDeathCoeffDN];
        DeathCoeffDP         = 1 * (1 - x[flu]) + x[flu] * params[hypDeathCoeffDP];
        DeathCoeffTconv      = 1 * (1 - x[flu]) + x[flu] * params[hypDeathCoeffTconv];
        DeathCoeffSP8        = 1 * (1 - x[flu]) + x[flu] * params[hypDeathCoeffSP8];
    }
    //if(background & Back::B_MoreOutputThymus){
    //    OutputCoeffOutDP	= 1 * (1 - x[flu]) + x[flu] * params[	hypOutputCoeffOutDP	];
    //    OutputCoeffOutTconv	= 1 * (1 - x[flu]) + x[flu] * params[	hypOutputCoeffOutTconv	];
    //    OutputCoeffOutSP8	= 1 * (1 - x[flu]) + x[flu] * params[	hypOutputCoeffOutSP8	];
    //}
    if(background & Back::B_FasterDifferentiation){
        FasterCoeffDNtoDP	= 1 * (1 - x[flu]) + x[flu] * params[	hypFasterCoeffDNtoDP	];
        FasterCoeffTconv	= 1 * (1 - x[flu]) + x[flu] * params[	hypFasterCoeffTconv	];
        FasterCoeffSP8	= 1 * (1 - x[flu]) + x[flu] * params[	hypFasterCoeffSP8	];
    }
    //if(background & Back::B_SpaceDependentOutput){
    //    SpaceOutputCoeff  = 1 * (1 - x[flu]) + x[flu] * params[hypSpaceOutputCoeff]; // no interest ?
    //}
    if(background & Back::B_DivisionReduced){
        LessDivCoeffDN = 1 * (1 - x[flu]) + x[flu] * params[hypLessDivDN];
        LessDivCoeffDP = 1 * (1 - x[flu]) + x[flu] * params[hypLessDivDP];
        LessDivCoeffTconv = 1 * (1 - x[flu]) + x[flu] * params[hypLessDivTconv];
        LessDivCoeffCD8 = 1 * (1 - x[flu]) + x[flu] * params[hypLessDivCD8];
    }


    double fastDiv = 100.0;
    if(!over( divDNg0)) {
        dxdt[divDNg0] 	= params[infloDN] * InflowCoeffETP + ( - params[pDN] * LessDivCoeffDN - params[dDN] * DeathCoeffDN) * x[divDNg0];
    }
    if(!over( divDNg1)) {
        dxdt[divDNg1] 	= 2 * params[pDN] * LessDivCoeffDN * x[divDNg0] + ( - params[pDN] * LessDivCoeffDN - params[dDN] * DeathCoeffDN) * x[divDNg1];
    }
    if(!over( divDNg2)) {
        dxdt[divDNg2] 	= 2 * params[pDN] * LessDivCoeffDN * x[divDNg1] + ( - params[pDN] * LessDivCoeffDN - params[dDN] * DeathCoeffDN) * x[divDNg2];
    }
    if(!over( divDNg3)) {
        dxdt[divDNg3] 	= 2 * params[pDN] * LessDivCoeffDN * x[divDNg2] + ( - params[pDN] * LessDivCoeffDN - params[dDN] * DeathCoeffDN) * x[divDNg3];
    }
    if(!over( divDNg4)) {
        dxdt[divDNg4] 	= 2 * params[pDN] * LessDivCoeffDN * x[divDNg3] + ( - params[pDN] * LessDivCoeffDN - fastDiv * FasterCoeffDNtoDP - params[dDN] * DeathCoeffDN) * x[divDNg4]; // just very fast, no prolif
    }


    if(!over( eDPg0)) {
        dxdt[eDPg0] 	= fastDiv * FasterCoeffDNtoDP * x[divDNg4] + 2 * params[pDN] * LessDivCoeffDN * x[divDNg4] + ( - params[peDP] * LessDivCoeffDP - params[deDP] * DeathCoeffDP) * x[eDPg0];
    }
    if(!over( eDPg1)) {
        dxdt[eDPg1] 	= 2 * params[peDP] * LessDivCoeffDP * x[eDPg0] + ( - params[peDP] * LessDivCoeffDP - params[deDP] * DeathCoeffDP) * x[eDPg1];
    }
    if(!over( eDPg2)) {
        dxdt[eDPg2] 	= 2 * params[peDP] * LessDivCoeffDP * x[eDPg1] + ( - params[peDP] * LessDivCoeffDP - params[deDP] * DeathCoeffDP) * x[eDPg2];
    }
    if(!over( eDPg3)) {
        dxdt[eDPg3] 	= 2 * params[peDP] * LessDivCoeffDP * x[eDPg2] + ( - params[peDP] * LessDivCoeffDP - params[deDP] * DeathCoeffDP) * x[eDPg3];
    }
    if(!over( eDPg4)) {
        dxdt[eDPg4] 	= 2 * params[peDP] * LessDivCoeffDP * x[eDPg3] + ( - params[peDP] * LessDivCoeffDP - params[deDP] * DeathCoeffDP) * x[eDPg4];
    }
    if(!over( eDPg5)) {
        dxdt[eDPg5] 	= 2 * params[peDP] * LessDivCoeffDP * x[eDPg4] + ( - (4.5*(- 1 + 2*1.1397 /0.94)) - params[peDP] * LessDivCoeffDP - params[deDP] * DeathCoeffDP) * x[eDPg5]; // the coeffecient given by (alppha^n) is wrong. probably wrong rounfding up of 0.2^127. The formula here extracts the coefficient of outflow from table III in the JI paper 2007
    }
    if(!over( eDPg6)) {
        dxdt[eDPg6] 	= 2 * params[peDP] * LessDivCoeffDP * x[eDPg5] + ( - params[peDP] * LessDivCoeffDP - fastDiv  - params[deDP] * DeathCoeffDP) * x[eDPg6];
    }


    if(!over( lDP)) {
        dxdt[lDP] 	= (4.5*(- 1 + 2*1.1397 /0.94)) * x[eDPg5] + fastDiv *  x[eDPg6] + 2*params[peDP] * LessDivCoeffDP * x[eDPg6] + (- params[drestDP] * DeathCoeffDP - params[diffDPtoSP4]* FasterCoeffTconv - params[diffDPtoSP8] * FasterCoeffSP8) * x[lDP];
    }

    if(!over( divSP4g0)) {
        dxdt[divSP4g0] 	= params[diffDPtoSP4] * FasterCoeffTconv *  x[lDP] + (- params[pSP4] * LessDivCoeffTconv  - params[dSP4] * DeathCoeffTconv) * x[divSP4g0];
    }
    if(!over( divSP4g1)) {
        dxdt[divSP4g1] 	= 2 * params[pSP4] * x[divSP4g0] + (- params[pSP4] * LessDivCoeffTconv  - params[dSP4] * DeathCoeffTconv - params[pcConvLastGenSP4]) * x[divSP4g1];
    }
    if(!over( divSP4g2)) {
        dxdt[divSP4g2] 	= 2 * params[pSP4] * x[divSP4g1] + (/* no prolif */  - params[dSP4] * DeathCoeffTconv - fastDiv) * x[divSP4g2];
    }
    // Says SP4 only divide.
    //if(!over( restSP4)) {
    //    dxdt[] 	= (  - x[]) / ( + 1e-12);
    //}


    if(!over( divSP8g0)) {
        dxdt[divSP8g0] 	= params[diffDPtoSP8] * FasterCoeffSP8 *  x[lDP] + (- params[pSP8] * LessDivCoeffCD8  - params[dSP8] * DeathCoeffSP8) * x[divSP8g0];
    }
    if(!over( divSP8g1)) {
        dxdt[divSP8g1] 	= 2 * params[pSP8] * x[divSP8g0] + (- params[pSP8] * LessDivCoeffCD8  - params[dSP8] * DeathCoeffSP8 - params[pcConvLastGenSP8]) * x[divSP8g1];
    }
    if(!over( divSP8g2)) {
        dxdt[divSP8g2] 	= 2 * params[pSP8] * x[divSP8g1] + (- params[pSP8] * LessDivCoeffCD8  - params[dSP8] * DeathCoeffSP8 - fastDiv) * x[divSP8g2];
    }

}

