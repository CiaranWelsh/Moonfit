// ------- Automatically generated model -------- //
#include "../../common.h"

#include "modele0ManessoOnly.h"

#include <sstream>

modele0ManessoOnly::modele0ManessoOnly() : Modele(NbVariables, NbParameters), background(Back::WT) {
    name = string("modele1ThymusSpleen");
    dt = 0.001; // initial time step -> then it is adaptive
    print_all_secs = 1200; //every how many seconds it is plotting

    // Name of variables
    names[flu]          = string("flu");
    names[tPreDN1]      = string("tPreDN1");
    names[tDN1s]         = string("tDN1s");
    names[tDN2]         = string("tDN2");
    names[tDN3]         = string("tDN3");
    names[tDN4]         = string("tDN4");
    names[floDN1to2]    = string("floDN1to2");
    names[floDN2to3]    = string("floDN2to3");
    names[floDN3to4]    = string("floDN3to4");
    names[flowDN4toDP]  = string("flowDN4toDP");
    names[tDNs]         = string("tDNs");
    for(int i = tDN1g0; i <= tDN1g15; ++i){
        stringstream res; res << "tDN1g" <<  i - tDN1g0;
        names[i] = res.str();
    }
    names[fracInPreDN1] = string("fracInPreDN1");
    names[fracInDN1]    = string("fracInDN1");
    names[fracInDN2]    = string("fracInDN2");
    names[fracInDN3]    = string("fracInDN3");
    names[fracInDN4]    = string("fracInDN4");

	// the names of variables that can be accessed by outside (global name-space)
    extNames[tDNs] = N::tDN;
    extNames[tDN1s]= N::tDN1;
    extNames[tDN2] = N::tDN2;
    extNames[tDN3] = N::tDN3;
    extNames[tDN4] = N::tDN4;

    extNames[fracInDN1]    = N::ProDN1Potritt;
    extNames[fracInDN2]    = N::ProDN2Potritt;
    extNames[fracInDN3]    = N::ProDN3Potritt;
    extNames[fracInDN4]    = N::ProDN4Potritt;

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
    paramNames[	hypInflowCoeffETP	]="	hypInflowCoeffETP	";
    paramNames[	hypDeathCoeffDN1 ]="hypDeathCoeffDN1",
    paramNames[	hypDeathCoeffDN2 ]="hypDeathCoeffDN2",
    paramNames[	hypDeathCoeffDN3 ]="hypDeathCoeffDN3",
    paramNames[	hypDeathCoeffDN4 ]="hypDeathCoeffDN4",

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
    paramLowBounds[hypInflowCoeffETP] = 0.05;		paramUpBounds[hypInflowCoeffETP]= 20;
    paramLowBounds[hypDeathCoeffDN1]  = 0.05;       paramUpBounds[hypDeathCoeffDN1] = 20;
    paramLowBounds[hypDeathCoeffDN2]  = 0.05;       paramUpBounds[hypDeathCoeffDN2] = 20;
    paramLowBounds[hypDeathCoeffDN3]  = 0.05;       paramUpBounds[hypDeathCoeffDN3] = 20;
    paramLowBounds[hypDeathCoeffDN4]  = 0.05;       paramUpBounds[hypDeathCoeffDN4] = 20;
    paramLowBounds[logisticThymus]    = 0.1;        paramUpBounds[logisticThymus]   = 500;
    paramLowBounds[logisticStrength]  = 0.1;        paramUpBounds[logisticStrength] = 10;
    backSimulated.clear();
	backSimulated.push_back(Back::WT);
}

void modele0ManessoOnly::setBaseParameters(){
    background = Back::WT;
	params.clear();     // to make sure they are all put to zero
    params.resize(NbParameters, 0.0);

    // Here, takes the value of the 'last generation only'
    params[flu_peak]        = 9;
    params[flu_std]         = 2.5;
    params[fETP_tDN]        = 0.05	;
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
    params[hypInflowCoeffETP]   = 0.3;
    params[hypDeathCoeffDN1]    = 5;
    params[hypDeathCoeffDN2]    = 5;
    params[hypDeathCoeffDN3]    = 5;
    params[hypDeathCoeffDN4]    = 5;
    params[logisticThymus]      = 90;
    params[logisticStrength]    = 2.0;

	setBaseParametersDone();
}

void modele0ManessoOnly::initialise(long long _background){ // don't touch to parameters !
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
    if(background & Back::WT){}
    if(background & Back::B_ReducedInflow){}
    if(background & Back::B_MoreDeath){}
    if(background & Back::B_AllCombined){}

    // if the initial values depend on parameters
    /*init[IL2] = params[IL2EQ]*/


    // change scaling inside moonfit !!!!!!
    init[flu] = 0;
    init[tPreDN1] = 0.000190;
    init[tDN1s] = 0;
    init[tDN2] = 0;
    init[tDN3] = 0;
    init[tDN4] = 0;
    init[floDN1to2] = 0;
    init[floDN2to3] = 0;
    init[floDN3to4] = 0;
    init[flowDN4toDP] = 0;
    init[tDNs] = 0;     // aim 3.7M
    init[tDN1g0] = 0;
    init[tDN1g1] = 0;
    init[tDN1g2] = 0;
    init[tDN1g3] = 0;
    init[tDN1g4] = 0;
    init[tDN1g5] = 0;
    init[tDN1g6] = 0;
    init[tDN1g7] = 0;
    init[tDN1g8] = 0;
    init[tDN1g9] = 0;
    init[tDN1g10] = 0;
    init[tDN1g11] = 0;
    init[tDN1g12] = 0;
    init[tDN1g13] = 0;
    init[tDN1g14] = 0;
    init[tDN1g15] = 0;
    init[fracInPreDN1] = 0;
    init[fracInDN1] = 0;
    init[fracInDN2] = 0;
    init[fracInDN3] = 0;
    init[fracInDN4] = 0;

    if(background & Back::B_StartSteadyState){
        init[tDN1g0] = params[cycleDN1] * init[tPreDN1] / (max(1e-12, params[decayDN1pre]));
        for(int i = tDN1g1; i <= tDN1g15; ++i){
            init[i] = 2 * (1 - params[deathDN1]) * init[i-1];
        }
    //    init[tDN1g11] = 20.853;
        init[tDN2] = - ((params[cycleDN2])/(1-2*params[commitDN2to3]-2*params[deathDN2])) * (params[commitDN1to2] * init[tDN1g11]) / (params[cycleDN1] + 1e-12);
        cout << "initDN2= " << init[tDN2] << endl;
        init[tDN3] =  - ((params[cycleDN3])/(1-2*params[commitDN3to4]-2*params[deathDN3])) * (params[commitDN2to3] * init[tDN2]) / (params[cycleDN2] + 1e-12);;
        cout << "initDN3= " << init[tDN3] << endl;
        init[tDN4] =  - ((params[cycleDN4])/(1-2*params[commitDN4toDP]-2*params[deathDN4])) * (params[commitDN3to4] * init[tDN3]) / (params[cycleDN3] + 1e-12);;
        cout << "initDN4= " << init[tDN4] << endl;
    }

    //cerr << "Initializing from new parameter values ... to be at steady state" << endl;
/*  params[ptSP8] = (- params[in_SP8] * init[sCD8] -  init[tDP] * params[ftDP_tSP8]) / init[tSP8] + params[out_SP8] + params[dtSP8];
    if(params[ptDN] < 0){
        //cerr << "ERR: the initial conditions + parameters don't allow the parameter [ptDN] to be positive / allow steady state" << endl;
        //cerr << "     Please put params[fETP_tDN] < " << (params[ftDN_tDP] +  params[dtDN]) * init[tDN] << " instead of " << params[fETP_tDN] << endl;
        params[ptDN] = 0;
    }*/
    for(int i = 0; i < NbVariables; ++i){
		val[i] = init[i];}
	t = 0;
	initialiseDone();
}


void modele0ManessoOnly::updateDerivedVariables(){

        //val[pctSP8RagN] = 100 * min(1.0, val[] / max(1e-8, val[]));
    val[tDN1s] = 0;
    for(int i = tDN1g0; i < tDN1g15; ++i){
        val[tDN1s] +=  val[i];
    }
    val[tDNs] = val[tDN1s] + val[tDN2] + val[tDN3] + val[tDN4];
    val[fracInPreDN1]   =  100 * min(1.0, val[tPreDN1] / max(1e-4, val[tDNs]));
    val[fracInDN1]      =  100 * min(1.0, val[tDN1s] / max(1e-4, val[tDNs]));
    val[fracInDN2]      =  100 * min(1.0, val[tDN2] / max(1e-4, val[tDNs]));
    val[fracInDN3]      =  100 * min(1.0, val[tDN3] / max(1e-4, val[tDNs]));
    val[fracInDN4]      =  100 * min(1.0, val[tDN4] / max(1e-4, val[tDNs]));

    val[floDN1to2] = 0;
    val[floDN2to3] = 0;
    val[floDN3to4] = 0;
    val[flowDN4toDP] = 0;

    val[flu] = exp(-(t - params[flu_peak]) * (t - params[flu_peak]) / (params[flu_std] * params[flu_std]));
}

void modele0ManessoOnly::derivatives(const vector<double> &x, vector<double> &dxdt, const double t){

    //double LAMBDA = params[TCRCOEFF] / (params[TCRPEAK] * params[TCRCOEFF] - TCRBASAL);
    //double LAMBDA = 1.0 / (params[flu_peak] * 1.0);
    // now, there are two ways to get the TCR signaling value over time :
    // 1/ using directly the function of TCR(t) --> this is tcr val and this is accurate,
    //double tcrval = (-TCRBASAL + params[TCRCOEFF] * (t/3600.0)) * exp(-(t/3600.0) * LAMBDA) + TCRBASAL;
    //double tcrval = (t * exp(-t * LAMBDA);
    // and 2/ by giving the dTCR/dt as output, so that the simulation is also calculating TCR step by step. This is less accurate, so I use tcrval in the formula, but I still give dTCR/dT to have the curve of TCR together with the curves of the other variables . In sum up, dTCR/dT is not required in the program, I just did it to consider TCR as a normal variable like IL2 or whatever.
    // dxdt[flu] = -LAMBDA * t * exp(- t * LAMBDA) + exp(- t * LAMBDA);
/*    if(!over(flu))   {
        if(t < (params[flu_peak] - 3)) dxdt[flu] = 0;
        else if(t <= (params[flu_peak])) dxdt[flu] = 1. / 3.;
        else if(t <= (params[flu_peak] + 3)) dxdt[flu] = -1. / 3.;
        else dxdt[flu] = 0;
    }*/
    // want function exp(

    double          InflowCoeffETP = 1;
    double          DeathCoeffDN1 = 1;
    double          DeathCoeffDN2 = 1;
    double          DeathCoeffDN3 = 1;
    double          DeathCoeffDN4 = 1;
//    double          LessDivCoeffDN = 1;

    if(background & Back::B_ReducedInflow){
        InflowCoeffETP = 1 * (1 - x[flu]) + x[flu] * params[hypInflowCoeffETP];
    }
    if(background & Back::B_MoreDeath){
        DeathCoeffDN1         = 1 * (1 - x[flu]) + x[flu] * params[hypDeathCoeffDN1];
        DeathCoeffDN2         = 1 * (1 - x[flu]) + x[flu] * params[hypDeathCoeffDN2];
        DeathCoeffDN3         = 1 * (1 - x[flu]) + x[flu] * params[hypDeathCoeffDN3];
        DeathCoeffDN4         = 1 * (1 - x[flu]) + x[flu] * params[hypDeathCoeffDN4];
    }

    //double coeff = (1/(1 - 1 / (params[logisticStrength]+1e-9)))*(1 - ((1/(params[logisticStrength] + 1e-9))*x[tDNs] / (params[logisticThymus] + 1e-9)));

    /*if(background & Back::B_LogisticTotalProlif){
        LessDivCoeffDN *= coeff;
    }*/

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
/*    if(!over(tDN1g12)) {
        dxdt[tDN1g12] 	= (2 * x[tDN1g11] * (1 - DeathCoeffDN1 * params[deathDN1]) - x[tDN1g12]) / (params[cycleDN1] + 1e-12);
    }
    if(!over(tDN1g13)) {
        dxdt[tDN1g13] 	= (2 * x[tDN1g12] * (1 - DeathCoeffDN1 * params[deathDN1]) - x[tDN1g13]) / (params[cycleDN1] + 1e-12);
    }
    if(!over(tDN1g14)) {
        dxdt[tDN1g14] 	= (2 * x[tDN1g13] * (1 - DeathCoeffDN1 * params[deathDN1]) - x[tDN1g14]) / (params[cycleDN1] + 1e-12);
    }
    if(!over(tDN1g15)) {
        dxdt[tDN1g15] 	= (2 * x[tDN1g14] * (1 - DeathCoeffDN1 * params[deathDN1]) - x[tDN1g15]) / (params[cycleDN1] + 1e-12);
    }
    */
    if(!over(tDN2)) {
         dxdt[tDN2] 	= (x[tDN1g11] * params[commitDN1to2]) / (params[cycleDN1] + 1e-12) + (1 - 2*params[commitDN2to3] - 2*DeathCoeffDN2*params[deathDN2]) * x[tDN2] / (params[cycleDN2] + 1e-12);
    }
    if(!over(tDN3)) {
        dxdt[tDN3] 	= (x[tDN2] * params[commitDN2to3]) / (params[cycleDN2] + 1e-12) + (1 - 2*params[commitDN3to4] - 2*DeathCoeffDN3*params[deathDN3]) * x[tDN3]/ (params[cycleDN3] + 1e-12);
    }
    if(!over(tDN4)) {
        dxdt[tDN4] 	= (x[tDN3] * params[commitDN3to4]) / (params[cycleDN3] + 1e-12) + (1 - 2*params[commitDN4toDP] - 2*DeathCoeffDN4*params[deathDN4]) * x[tDN4] / (params[cycleDN4] + 1e-12);
    }





/*
   if(!over(tDN)) {
        dxdt[tDN] 	= InflowCoeffETP * params[fETP_tDN] + x[tDN] * (LessDivCoeffDN * params[ptDN] - FasterCoeffDNtoDP * params[ftDN_tDP] - DeathCoeffDN * params[dtDN]);
   }
   if(!over(tDP)) {
        dxdt[tDP] 	= x[tDN] * FasterCoeffDNtoDP * params[ftDN_tDP] +  x[tDP] * (- SpaceOutputCoeff * OutputCoeffOutDP * params[out_tDP] + LessDivCoeffDP * params[ptDP] - FasterCoeffTconv * params[ftDP_tTConv] - FasterCoeffPro25 * params[ftDP_tTregP25] - FasterCoeffProFP3 * params[ftDP_tTregFP3] - FasterCoeffSP8 * params[ftDP_tSP8] - DeathCoeffDP * params[dtDP]);
   }
   if(!over(tTconv)) {
        dxdt[tTconv] 	= params[in_tTconv] * x[sTconv]  + x[tDP] * FasterCoeffTconv * params[ftDP_tTConv] + x[tTconv] * (- SpaceOutputCoeff * OutputCoeffOutTconv * params[out_tTconv] + LessDivCoeffTconv * params[ptTconv] - DeathCoeffTconv * params[dtTconv]);
   }
   if(!over(tTRegP25)) {
        dxdt[tTRegP25] 	=   x[tDP] * FasterCoeffPro25 * params[ftDP_tTregP25] + x[tTRegP25] * (- SpaceOutputCoeff * OutputCoeffOutPro25 * params[out_tTregP25] + LessDivCoeffTregPro25 * params[ptTregP25] - params[ftTregP25_tDPTreg] - DeathCoeffPro25 * params[dtTregP25]);
   }
   if(!over(tTRegPFp3)) {
        dxdt[tTRegPFp3] 	= params[in_tTregPFp3] * x[sTreg] + x[tDP] * FasterCoeffProFP3 * params[ftDP_tTregFP3] + x[tTRegPFp3] * ( - SpaceOutputCoeff * OutputCoeffOutProFP3 * params[out_tTregFP3] + LessDivCoeffTregProFP3 * params[ptTregFP3] - params[ftTregFP3_tDPTreg] - DeathCoeffProFp3 * params[dtTregFP3]);
   }
   if(!over(tTreg)) {
        dxdt[tTreg] 	= params[in_tDPTregs] * x[sTreg] +  x[tTRegP25] * params[ftTregP25_tDPTreg] + x[tTRegPFp3] * params[ftTregFP3_tDPTreg] + x[tTreg] * (- SpaceOutputCoeff * OutputCoeffOutDPTregs * params[out_tDPTregs]  + LessDivCoeffDPTreg * params[ptDPTregs] - DeathCoeffDPTregs * params[dtDPTregs]);
   }
   if(!over(tSP8)) {
        dxdt[tSP8] 	= params[in_SP8] * x[sCD8]  + x[tDP] * FasterCoeffSP8 * params[ftDP_tSP8] + x[tSP8] * (- SpaceOutputCoeff * OutputCoeffOutSP8 * params[out_SP8] + LessDivCoeffCD8 * params[ptSP8] - DeathCoeffSP8 * params[dtSP8]);
   }



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
   */

}
