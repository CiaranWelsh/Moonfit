// ------- Automatically generated model -------- //
#include "modele0ManessoOnly.h"

#include <sstream>

modele0ManessoOnly::modele0ManessoOnly() : Model(NbVariables, NbParameters), background(Back::WT) {
    name = string("modele0ManessoOnly");
    dt = 0.001;             // initial time step -> then it is adaptive
    print_every_dt = 1200;  //every how many seconds it is plotting

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
    extNames[tPreDN1] = GlobalName(N::tDN1pre);
    extNames[tDNs] = GlobalName(N::tDN);
    extNames[tDN1s]= GlobalName(N::tDN1);
    extNames[tDN2] = GlobalName(N::tDN2);
    extNames[tDN3] = GlobalName(N::tDN3);
    extNames[tDN4] = GlobalName(N::tDN4);

    extNames[fracInDN1]    = GlobalName(N::ProDN1Potritt);
    extNames[fracInDN2]    = GlobalName(N::ProDN2Potritt);
    extNames[fracInDN3]    = GlobalName(N::ProDN3Potritt);
    extNames[fracInDN4]    = GlobalName(N::ProDN4Potritt);

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
    paramLowBounds[fETP_tDN]    = 	0.00;           paramUpBounds[fETP_tDN]     = 	0;
    paramLowBounds[decayDN1pre] = 	1;				paramUpBounds[decayDN1pre]  = 	4;
    paramLowBounds[commitDN1to2]= 	0.5;			paramUpBounds[commitDN1to2] = 	1;
    paramLowBounds[deathDN1]    = 	0;              paramUpBounds[deathDN1]     = 	0.4;
    paramLowBounds[cycleDN1]   = 	0.8;			paramUpBounds[cycleDN1]    = 	1.3;
    paramLowBounds[commitDN2to3]= 	0.3;			paramUpBounds[commitDN2to3] = 	0.9;
    paramLowBounds[deathDN2]    = 	0;              paramUpBounds[deathDN2]     = 	0.4;
    paramLowBounds[cycleDN2]   = 	0.3;			paramUpBounds[cycleDN2]    = 	5;
    paramLowBounds[commitDN3to4]= 	0.1;			paramUpBounds[commitDN3to4] = 	0.8;
    paramLowBounds[deathDN3]    = 	0;              paramUpBounds[deathDN3]     = 	0.4;
    paramLowBounds[cycleDN3]   = 	0.3;			paramUpBounds[cycleDN3]    = 	5;
    paramLowBounds[commitDN4toDP] =	0.1;            paramUpBounds[commitDN4toDP]= 	0.9;
    paramLowBounds[deathDN4]    = 	0;              paramUpBounds[deathDN4]     = 	0.4;
    paramLowBounds[cycleDN4]   = 	0.3;			paramUpBounds[cycleDN4]    = 	3;
    paramLowBounds[hypInflowCoeffETP] = 0.05;		paramUpBounds[hypInflowCoeffETP]= 20;
    paramLowBounds[hypDeathCoeffDN1]  = 0.05;       paramUpBounds[hypDeathCoeffDN1] = 20;
    paramLowBounds[hypDeathCoeffDN2]  = 0.05;       paramUpBounds[hypDeathCoeffDN2] = 20;
    paramLowBounds[hypDeathCoeffDN3]  = 0.05;       paramUpBounds[hypDeathCoeffDN3] = 20;
    paramLowBounds[hypDeathCoeffDN4]  = 0.05;       paramUpBounds[hypDeathCoeffDN4] = 20;
    paramLowBounds[logisticThymus]    = 0.1;        paramUpBounds[logisticThymus]   = 500;
    paramLowBounds[logisticStrength]  = 0.1;        paramUpBounds[logisticStrength] = 10;
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

    background = _background;

    init[flu] = 0;
    init[tPreDN1] = 0.140; //0.183;
    init[tDN1s] = 0;
    init[tDN2] = 0;
    init[tDN3] = 0;
    init[tDN4] = 0;
    init[floDN1to2] = 0;
    init[floDN2to3] = 0;
    init[floDN3to4] = 0;
    init[flowDN4toDP] = 0;
    init[tDNs] = 0;         // aim 3.7M
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

    params[commitDN1to2] = 1 - params[deathDN1];
    //or: params[deathDN1] = 1 - params[commitDN1to2];

    // important: condition for not diverging: death + commit > 0.5, so gives upper boundary to death

    if((params[deathDN2] + params[commitDN2to3]) < 0.5) params[deathDN2] = 0.5 - params[commitDN2to3] + 1e-6;
    if((params[deathDN3] + params[commitDN3to4]) < 0.5) params[deathDN3] = 0.5 - params[commitDN3to4] + 1e-6;
    if((params[deathDN4] + params[commitDN4toDP]) < 0.5) params[deathDN4] = 0.5 - params[commitDN4toDP] + 1e-6;

    // To reproduce the curves for best parameter set in Manesso, addi this condition, always gives the same curve
    // params[cycleDN2] = (1 - 2* params[commitDN2to3] - 2*params[deathDN2]) / (-0.381887);
    // params[cycleDN3] = (1 - 2* params[commitDN3to4] - 2*params[deathDN3]) / (-0.00830189);

    if(background & Back::B_StartSteadyState){
        init[tDN1g0] = params[cycleDN1] * init[tPreDN1] / (max(1e-12, params[decayDN1pre]));
        for(int i = tDN1g1; i <= tDN1g15; ++i){
            init[i] = 2 * (1 - params[deathDN1]) * init[i-1];
        }
        init[tDN2] = - ((params[cycleDN2])/(1-2*params[commitDN2to3]-2*params[deathDN2])) * (params[commitDN1to2] * init[tDN1g11]) / (params[cycleDN1] + 1e-12);
        //cout << "initDN2= " << init[tDN2] << endl;
        init[tDN3] =  - ((params[cycleDN3])/(1-2*params[commitDN3to4]-2*params[deathDN3])) * (params[commitDN2to3] * init[tDN2]) / (params[cycleDN2] + 1e-12);;
        //cout << "initDN3= " << init[tDN3] << endl;
        init[tDN4] =  - ((params[cycleDN4])/(1-2*params[commitDN4toDP]-2*params[deathDN4])) * (params[commitDN3to4] * init[tDN3]) / (params[cycleDN3] + 1e-12);;
        //cout << "initDN4= " << init[tDN4] << endl;
    }
    for(int i = 0; i < NbVariables; ++i){
		val[i] = init[i];}
	t = 0;
	initialiseDone();
}


void modele0ManessoOnly::updateDerivedVariables(){
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
    // time-dependent coefficient if impact of flu
    double          InflowCoeffETP = 1;
    double          DeathCoeffDN1 = 1;
    double          DeathCoeffDN2 = 1;
    double          DeathCoeffDN3 = 1;
    double          DeathCoeffDN4 = 1;

    if(background & Back::B_ReducedInflow){
        InflowCoeffETP = 1 * (1 - x[flu]) + x[flu] * params[hypInflowCoeffETP];
    }
    if(background & Back::B_MoreDeath){
        DeathCoeffDN1         = 1 * (1 - x[flu]) + x[flu] * params[hypDeathCoeffDN1];
        DeathCoeffDN2         = 1 * (1 - x[flu]) + x[flu] * params[hypDeathCoeffDN2];
        DeathCoeffDN3         = 1 * (1 - x[flu]) + x[flu] * params[hypDeathCoeffDN3];
        DeathCoeffDN4         = 1 * (1 - x[flu]) + x[flu] * params[hypDeathCoeffDN4];
    }

    // to use logistic strength, uncomment this one
    /* double LessDivCoeffDN = 1;
    double coeff = (1/(1 - 1 / (params[logisticStrength]+1e-9)))*(1 - ((1/(params[logisticStrength] + 1e-9))*x[tDNs] / (params[logisticThymus] + 1e-9)));
    if(background & Back::B_LogisticTotalProlif){
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
}
