// ------- Automatically generated model -------- //
#include "modele5SuperDN.h"

#include <sstream>

modele5SuperDN::modele5SuperDN() : Model(NbVariables, NbParameters), background(Back::WT) {
    name = string("modele1ThymusSpleen");
    dt = 0.001; // initial time step -> then it is adaptive
    print_every_dt = 1200; //every how many seconds it is plotting

    // Name of variables
    names[flu]          = string("flu");
    names[tPreDN1]      = string("tPreDN1");
    names[tDN1s]        = string("tDN1s");
    names[tDN2s]         = string("tDN2");
    names[tDN3s]         = string("tDN3");
    names[tDN4s]         = string("tDN4");
    names[tDNs]         = string("tDNs");
    for(int i = tDN1g0; i <= tDN1g15; ++i){
        stringstream res; res << "tDN1g" <<  i - tDN1g0;
        names[i] = res.str();
    }
    for(int i = tDN2g0; i <= tDN2g15; ++i){
        stringstream res; res << "tDN2g" <<  i - tDN2g0;
        names[i] = res.str();
    }
    for(int i = tDN3g0; i <= tDN3g15; ++i){
        stringstream res; res << "tDN3g" <<  i - tDN3g0;
        names[i] = res.str();
    }
    for(int i = tDN4g0; i <= tDN4g15; ++i){
        stringstream res; res << "tDN4g" <<  i - tDN4g0;
        names[i] = res.str();
    }
    names[fracInPreDN1] = string("fracInPreDN1");
    names[fracInDN1]    = string("fracInDN1");
    names[fracInDN2]    = string("fracInDN2");
    names[fracInDN3]    = string("fracInDN3");
    names[fracInDN4]    = string("fracInDN4");
    names[floinDN1]     = string("floinDN1");
    names[floDN1to2]    = string("floDN1to2");
    names[floDN2to3]    = string("floDN2to3");
    names[floDN3to4]    = string("floDN3to4");
    names[flowDN4toDP]  = string("flowDN4toDP");

    // the names of variables that can be accessed by outside (global name-space)
    extNames[tDNs]  = GlobalName(N::tDN);
    extNames[tDN1s] = GlobalName(N::tDN1);
    extNames[tDN2s] = GlobalName(N::tDN2);
    extNames[tDN3s] = GlobalName(N::tDN3);
    extNames[tDN4s] = GlobalName(N::tDN4);
    extNames[fracInDN1] = GlobalName(N::ProDN1Potritt);
    extNames[fracInDN2] = GlobalName(N::ProDN2Potritt);
    extNames[fracInDN3] = GlobalName(N::ProDN3Potritt);
    extNames[fracInDN4] = GlobalName(N::ProDN4Potritt);

    NmaxDN1 = tDN1g15 - tDN1g0 + 1;
    NmaxDN2 = tDN2g15 - tDN2g0 + 1;
    NmaxDN3 = tDN3g15 - tDN3g0 + 1;
    NmaxDN4 = tDN4g15 - tDN4g0 + 1;
    ProlifDN1.clear();    ProlifDN1.resize(NmaxDN1, 0);
    ProlifDN2.clear();    ProlifDN2.resize(NmaxDN2, 0);
    ProlifDN3.clear();    ProlifDN3.resize(NmaxDN3, 0);
    ProlifDN4.clear();    ProlifDN4.resize(NmaxDN4, 0);

    // Name of parameters
    paramNames[flu_peak] = "flu_peak / peak of flu effect in days";
    paramNames[flu_std]  = "flu_std / width of flu effect (stddev)";
    paramNames[fETP_tDN] = "fETP_tDN / DN thymic Inflow";
    paramNames[decayDN1pre]   = "decayDN1pre";
    paramNames[NtotDN1]         = "NtotDN1";
    paramNames[cycleDN1]        = "cycleDN1";
    paramNames[nDivDN1]         = "nDivDN1";
    paramNames[deathDN1]        = "deathDN1";
    paramNames[FlowDN1to2]      = "F1to2";
    paramNames[NtotDN2]         = "NtotDN2";
    paramNames[cycleDN2]        = "cycleDN2";
    paramNames[nDivDN2]         = "nDivDN2";
    paramNames[deathDN2]        = "deathDN2";
    paramNames[FlowDN2to3]      = "F2to3";
    paramNames[NtotDN3]         = "NtotDN3";
    paramNames[cycleDN3]        = "cycleDN3";
    paramNames[nDivDN3]         = "nDivDN3";
    paramNames[deathDN3]        = "deathDN3";
    paramNames[FlowDN3to4]      = "F3to4";
    paramNames[NtotDN4]         = "NtotDN4";
    paramNames[cycleDN4]        = "cycleDN4";
    paramNames[nDivDN4]         = " nDivDN4";
    paramNames[deathDN4]        = "deathDN4";
    paramNames[FlowDN4toeDP]    = "F4toeDP";
    paramNames[hypInflowCoeffETP]=  "hypInflowCoeffETP";
    paramNames[hypDeathCoeffDN1]=   "hypDeathCoeffDN1",
    paramNames[hypDeathCoeffDN2]=   "hypDeathCoeffDN2",
    paramNames[hypDeathCoeffDN3]=   "hypDeathCoeffDN3",
    paramNames[hypDeathCoeffDN4]=   "hypDeathCoeffDN4",
    paramNames[hypLessDivDN]            = "hypLessDivDN",
    paramNames[hypRandomOutputDN]       = "hypRandomOutputDN",
    paramNames[hypChangeNDivDNs]    = "hypChangeNDivDNs";
    paramNames[logisticThymus]          = "logisticThymus";
    paramNames[logisticStrength]        = "logisticStrength";

    paramLowBounds[flu_peak]    = 	5;              paramUpBounds[flu_peak]     = 	15;
    paramLowBounds[flu_std]     = 	0.5;			paramUpBounds[flu_std]      = 	10;
    paramLowBounds[fETP_tDN]    = 	0.00001;        paramUpBounds[fETP_tDN]     = 	0.005;
    paramLowBounds[decayDN1pre] = 	1.0;            paramUpBounds[decayDN1pre]  = 	3;

    paramLowBounds[NtotDN1]     = 	0.010000;		paramUpBounds[NtotDN1]      = 	0.500000;
    paramLowBounds[cycleDN1]    = 	0.4;			paramUpBounds[cycleDN1]     = 	2.5;
    paramLowBounds[nDivDN1]     = 	2;				paramUpBounds[nDivDN1]      = 	14;
    paramLowBounds[deathDN1]    = 	0.005;          paramUpBounds[deathDN1]     = 	0.4;
    paramLowBounds[FlowDN1to2]  = 	0.005;          paramUpBounds[FlowDN1to2]   = 	0.070000;

    paramLowBounds[NtotDN2]     = 	0.050000;		paramUpBounds[NtotDN2]      = 	0.200000;
    paramLowBounds[cycleDN2]    = 	0.4;			paramUpBounds[cycleDN2]     = 	2.5;
    paramLowBounds[nDivDN2]     = 	1.2;			paramUpBounds[nDivDN2]      = 	10;
    paramLowBounds[deathDN2]    = 	0.005;          paramUpBounds[deathDN2]     = 	0.4;
    paramLowBounds[FlowDN2to3]  = 	0.020000;		paramUpBounds[FlowDN2to3]   = 	0.250000;

    paramLowBounds[NtotDN3]     = 	1.0;			paramUpBounds[NtotDN3]      = 	2.5;
    paramLowBounds[cycleDN3]    = 	0.4;			paramUpBounds[cycleDN3]     = 	2.5;
    paramLowBounds[nDivDN3]     = 	1.2;			paramUpBounds[nDivDN3]      = 	10;
    paramLowBounds[deathDN3]    = 	0.005;          paramUpBounds[deathDN3]     = 	0.4;
    paramLowBounds[FlowDN3to4]  = 	0.150000;		paramUpBounds[FlowDN3to4]   = 	1.2;

    paramLowBounds[NtotDN4]     = 	1.0;			paramUpBounds[NtotDN4]      = 	3.0;
    paramLowBounds[cycleDN4]    = 	0.4;			paramUpBounds[cycleDN4]     = 	2.5;
    paramLowBounds[nDivDN4]     = 	1.2;			paramUpBounds[nDivDN4]      = 	10;
    paramLowBounds[deathDN4]    = 	0.005;          paramUpBounds[deathDN4]     = 	0.4;
    paramLowBounds[FlowDN4toeDP]= 	0.150000;		paramUpBounds[FlowDN4toeDP] = 	1.2;

    paramLowBounds[hypInflowCoeffETP] = 0.05;		paramUpBounds[hypInflowCoeffETP]= 20;
    paramLowBounds[hypDeathCoeffDN1]  = 0.05;       paramUpBounds[hypDeathCoeffDN1] = 20;
    paramLowBounds[hypDeathCoeffDN2]  = 0.05;       paramUpBounds[hypDeathCoeffDN2] = 20;
    paramLowBounds[hypDeathCoeffDN3]  = 0.05;       paramUpBounds[hypDeathCoeffDN3] = 20;
    paramLowBounds[hypDeathCoeffDN4]  = 0.05;       paramUpBounds[hypDeathCoeffDN4] = 20;
    paramLowBounds[hypLessDivDN]         = 0.01;	paramUpBounds[hypLessDivDN]         = 20;
    paramLowBounds[hypRandomOutputDN]    = 0.05;    paramUpBounds[hypRandomOutputDN]    = 20;
    paramLowBounds[hypChangeNDivDNs] = 0.05;        paramUpBounds[hypChangeNDivDNs] = 20;
    paramLowBounds[logisticThymus]    = 0.1;        paramUpBounds[logisticThymus]   = 500;
    paramLowBounds[logisticStrength]  = 0.1;        paramUpBounds[logisticStrength] = 10;
}

void modele5SuperDN::setBaseParameters(){
    background = Back::WT;
	params.clear();     // to make sure they are all put to zero
    params.resize(NbParameters, 0.0);

    params[flu_peak]        = 9;
    params[flu_std]         = 2.5;
    params[fETP_tDN]        = 0.000105	;
    params[decayDN1pre]     = 2.27; // day

    params[NtotDN1]     = 	0.107400;
    params[cycleDN1]    = 	1.1;
    params[nDivDN1]     = 	11;
    params[deathDN1]    = 	0.14;
    params[FlowDN1to2]  = 	0.070400;

    params[NtotDN2]     = 	0.098000;
    params[cycleDN2]    = 	0.631;
    params[nDivDN2]     = 	4;
    params[deathDN2]    = 	0.028;
    params[FlowDN2to3]  = 	0.095000;

    params[NtotDN3]     = 	1.217;
    params[cycleDN3]    = 	1.6;
    params[nDivDN3]     = 	2.6;
    params[deathDN3]    = 	0.2;
    params[FlowDN3to4]  = 	0.500000;

    params[NtotDN4]     = 	1.929;
    params[cycleDN4]    = 	1.5;
    params[nDivDN4]     = 	2.5;
    params[deathDN4]    = 	0.2;
    params[FlowDN4toeDP]= 	0.460000;

    params[hypInflowCoeffETP]   = 0.3;
    params[hypDeathCoeffDN1]    = 5;
    params[hypDeathCoeffDN2]    = 5;
    params[hypDeathCoeffDN3]    = 5;
    params[hypDeathCoeffDN4]    = 5;
    params[hypLessDivDN]            = 1;
    params[hypRandomOutputDN]       = 1;
    params[hypChangeNDivDNs]    = 1;
    params[logisticThymus]      = 90;
    params[logisticStrength]    = 2.0;

	setBaseParametersDone();
}

void modele5SuperDN::calculateParameters(vector<double> & ProlifDNx, double nDivDNx, int NdivMax){
    double dynamicNDiv  = min((double) NdivMax + 0.9999999, nDivDNx);
    int N_DNx                = (int) dynamicNDiv;
    double divFloatDNx          = dynamicNDiv - (double) N_DNx;
    if(divFloatDNx < 1e-12) {N_DNx = max(0,N_DNx-1);}
    if((int) ProlifDNx.size() < NdivMax) cerr << "Wrong size for ProlifDNx, seg fault to happen" << endl;
    for(int i = 0; i <= N_DNx-1; ++i){
        if(i >= 0) ProlifDNx[i] = 1.0;
    }
    if(N_DNx > 0) ProlifDNx[N_DNx-1] = divFloatDNx;
    for(int i = N_DNx; i < NdivMax; ++i){
        ProlifDNx[i] = 0;
    }
}

void modele5SuperDN::initialise(long long _background){ // don't touch to parameters !
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
    /*if(background & Back::WT){}
    if(background & Back::B_ReducedInflow){}
    if(background & Back::B_MoreDeath){}
    if(background & Back::B_AllCombined){}*/

    // if the initial values depend on parameters
    /*init[IL2] = params[IL2EQ]*/


    params[cycleDN2] = params[cycleDN1];
    //params[cycleDN3] = params[cycleDN1];
    //params[cycleDN4] = params[cycleDN1];

    //params[deathDN2] = params[deathDN1];
    //params[deathDN3] = params[deathDN1];
    //params[deathDN4] = params[deathDN1];

    // Forcing death of DN1 and DN2 to be super low
    params[FlowDN1to2] = params[fETP_tDN] + params[NtotDN1] / (max(1e-12, params[cycleDN1]));
    params[FlowDN2to3] = params[FlowDN1to2] + params[NtotDN2] / (max(1e-12, params[cycleDN2]));

    // change scaling inside moonfit !!!!!!
    init[flu] = 0;
    init[tPreDN1] = 0.000190;

    if(background & Back::B_Reconstitution){
        init[tPreDN1] = 0;
    }


    // Note: stupid C++ math library: 'log' means LN
    // Very important: adapts the parameters nDiv and death to In, Out, T
    // note: at steady state, the progenitors have same input and output (no death neither prolif)
    params[deathDN1] = 0.5* ((1. / params[cycleDN1]) + ((params[fETP_tDN] - params[FlowDN1to2]) / params[NtotDN1]));
    params[nDivDN1] = (std::log(params[FlowDN1to2]) - std::log(params[fETP_tDN])) / (std::log(1 + params[cycleDN1] * ((- params[fETP_tDN] + params[FlowDN1to2]) / params[NtotDN1])));

    params[deathDN2] = 0.5* ((1. / params[cycleDN2]) + ((params[FlowDN1to2] - params[FlowDN2to3]) / params[NtotDN2]));
    params[nDivDN2] = (std::log(params[FlowDN2to3]) - std::log(params[FlowDN1to2])) / (std::log(1 + params[cycleDN2] * ((- params[FlowDN1to2] + params[FlowDN2to3]) / params[NtotDN2])));

    params[deathDN3] = 0.5* ((1. / params[cycleDN3]) + ((params[FlowDN2to3] - params[FlowDN3to4]) / params[NtotDN3]));
    params[nDivDN3] = (std::log(params[FlowDN3to4]) - std::log(params[FlowDN2to3])) / (std::log(1 + params[cycleDN3] * ((- params[FlowDN2to3] + params[FlowDN3to4]) / params[NtotDN3])));

    params[deathDN4] = 0.5* ((1. / params[cycleDN4]) + ((params[FlowDN3to4] - params[FlowDN4toeDP]) / params[NtotDN4]));
    params[nDivDN4] = (std::log(params[FlowDN4toeDP]) - std::log(params[FlowDN3to4])) / (std::log(1 + params[cycleDN4] * ((- params[FlowDN3to4] + params[FlowDN4toeDP]) / params[NtotDN4])));

    /*init[tDN1s] = 0;
    init[tDN2s] = 0;
    init[tDN3s] = 0;
    init[tDN4s] = 0;
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
    init[fracInDN4] = 0;*/

    if(background & Back::B_StartSteadyState){

        calculateParameters(ProlifDN1, params[nDivDN1], NmaxDN1);
        calculateParameters(ProlifDN2, params[nDivDN2], NmaxDN2);
        calculateParameters(ProlifDN3, params[nDivDN3], NmaxDN3);
        calculateParameters(ProlifDN4, params[nDivDN4], NmaxDN4);

        //if(params[NdivDN1] < 1e-12) cout << "WRN: you use a multi-generation model and chose N=0. Cannot simulate that so I put proliferation pDN = 0. It will change T\n" << endl;

        double pDN1 = 1. / (max(params[cycleDN1], 1e-12)) - params[deathDN1];
        double pDN2 = 1. / (max(params[cycleDN2], 1e-12)) - params[deathDN2];
        double pDN3 = 1. / (max(params[cycleDN3], 1e-12)) - params[deathDN3];
        double pDN4 = 1. / (max(params[cycleDN4], 1e-12)) - params[deathDN4];

        init[tPreDN1] = params[fETP_tDN] * params[decayDN1pre];
        init[floinDN1] = params[fETP_tDN];

        init[tDN1g0] = init[floinDN1] * params[cycleDN1]; // * init[tPreDN1] / (max(1e-12, params[decayDN1pre]));
        for(int i = 1; i < NmaxDN1; ++i){
            init[tDN1g0+i] = 2*init[tDN1g0+i-1] * ProlifDN1[i-1] * (pDN1) / (max(1e-12, pDN1 + params[deathDN1]));
        }

        double outflowToDN2 = 0;
        for(int i = 0; i < NmaxDN1; ++i){
            outflowToDN2 += 2*(1 - ProlifDN1[i]) * pDN1 * init[tDN1g0 + i];
        }
        init[floDN1to2] = outflowToDN2;

        init[tDN2g0] = outflowToDN2 * params[cycleDN2];
        for(int i = 1; i < NmaxDN2; ++i){
            init[tDN2g0+i] = 2*init[ tDN2g0+i-1] * ProlifDN2[i-1] * (pDN2) / (max(1e-12, pDN2 + params[deathDN2]));
        }

        double outflowToDN3 = 0;
        for(int i = 0; i < NmaxDN2; ++i){
            outflowToDN3 += 2*(1 - ProlifDN2[i]) * pDN2 * init[tDN2g0 + i];
        }
        init[floDN2to3] = outflowToDN3;

        init[tDN3g0] = outflowToDN3 * params[cycleDN3];
        for(int i = 1; i < NmaxDN3; ++i){
            init[tDN3g0+i] = 2*init[ tDN3g0+i-1] * ProlifDN3[i-1] * (pDN3) / (max(1e-12, pDN3 + params[deathDN3]));
        }

        double outflowToDN4 = 0;
        for(int i = 0; i < NmaxDN3; ++i){
            outflowToDN4 += 2*(1 - ProlifDN3[i]) * pDN3 * init[tDN3g0 + i];
        }
        init[floDN3to4] = outflowToDN4;

        init[tDN4g0] = outflowToDN4 * params[cycleDN4];
        for(int i = 1; i < NmaxDN4; ++i){
            init[tDN4g0+i] = 2*init[ tDN4g0+i-1] * ProlifDN4[i-1] * (pDN4) / (max(1e-12, pDN4 + params[deathDN4]));
        }

        double outflowToeDP = 0;
        for(int i = 0; i < NmaxDN4; ++i){
            outflowToeDP += 2*(1 - ProlifDN4[i]) * pDN4 * init[tDN4g0 + i];
        }
        init[flowDN4toDP] = outflowToeDP;

        //cout << "STEADY STATE" << init[tDN1g0] << endl;


        //    init[tDN1g11] = 20.853;
        //init[tDN2] = - ((params[cycleDN2])/(1-2*params[commitDN2to3]-2*params[deathDN2])) * (params[commitDN1to2] * init[tDN1g11]) / (params[cycleDN1] + 1e-12);
        //cout << "initDN2= " << init[tDN2] << endl;
        //init[tDN3] =  - ((params[cycleDN3])/(1-2*params[commitDN3to4]-2*params[deathDN3])) * (params[commitDN2to3] * init[tDN2]) / (params[cycleDN2] + 1e-12);;
        //cout << "initDN3= " << init[tDN3] << endl;
        //init[tDN4] =  - ((params[cycleDN4])/(1-2*params[commitDN4toDP]-2*params[deathDN4])) * (params[commitDN3to4] * init[tDN3]) / (params[cycleDN3] + 1e-12);;
        //cout << "initDN4= " << init[tDN4] << endl;
    }

    for(int i = 0; i < NbVariables; ++i){
		val[i] = init[i];}
	t = 0;
	initialiseDone();
}


void modele5SuperDN::updateDerivedVariables(){

    val[flu] = exp(-(t - params[flu_peak]) * (t - params[flu_peak]) / (params[flu_std] * params[flu_std]));

    double          ChangeNDivDN1 = 1;
    double          ChangeNDivDN2 = 1;
    double          ChangeNDivDN3 = 1;
    double          ChangeNDivDN4 = 1;
    double          LessDivCoeffDN1 = 1;
    double          LessDivCoeffDN2 = 1;
    double          LessDivCoeffDN3 = 1;
    double          LessDivCoeffDN4 = 1;
    double          OutputCoeffOutDN1 = 0;
    double          OutputCoeffOutDN2 = 0;
    double          OutputCoeffOutDN3 = 0;
    double          OutputCoeffOutDN4 = 0;
    if(background & Back::B_FasterDifferentiation){
        ChangeNDivDN1	= 1 * (1 - val[flu]) + val[flu] * params[hypChangeNDivDNs];
        ChangeNDivDN2	= 1 * (1 - val[flu]) + val[flu] * params[hypChangeNDivDNs];
        ChangeNDivDN3	= 1 * (1 - val[flu]) + val[flu] * params[hypChangeNDivDNs];
        ChangeNDivDN4	= 1 * (1 - val[flu]) + val[flu] * params[hypChangeNDivDNs];
    }
    if(background & Back::B_MoreOutputThymus){
        OutputCoeffOutDN1	= 0 * (1 - val[flu]) + val[flu] * 1.0 * params[	hypRandomOutputDN	];
        OutputCoeffOutDN2	= 0 * (1 - val[flu]) + val[flu] * 1.0 * params[	hypRandomOutputDN	];
        OutputCoeffOutDN3	= 0 * (1 - val[flu]) + val[flu] * 1.0 * params[	hypRandomOutputDN	];
        OutputCoeffOutDN4	= 0 * (1 - val[flu]) + val[flu] * 1.0 * params[	hypRandomOutputDN	];
    }
    if(background & Back::B_DivisionReduced){
        LessDivCoeffDN1 = 1 * (1 - val[flu]) + val[flu] * params[hypLessDivDN];
        LessDivCoeffDN2 = 1 * (1 - val[flu]) + val[flu] * params[hypLessDivDN];
        LessDivCoeffDN3 = 1 * (1 - val[flu]) + val[flu] * params[hypLessDivDN];
        LessDivCoeffDN4 = 1 * (1 - val[flu]) + val[flu] * params[hypLessDivDN];
    }

    // recalculates nDiv and coefficients prolif[]
    calculateParameters(ProlifDN1, ChangeNDivDN1 * params[nDivDN1], NmaxDN1);
    calculateParameters(ProlifDN2, ChangeNDivDN2 * params[nDivDN2], NmaxDN2);
    calculateParameters(ProlifDN3, ChangeNDivDN3 * params[nDivDN3], NmaxDN3);
    calculateParameters(ProlifDN4, ChangeNDivDN4 * params[nDivDN4], NmaxDN4);


    val[tDN1s] = 0;
    for(int i = tDN1g0; i < tDN1g15; ++i){
        val[tDN1s] +=  val[i];
    }
    val[tDN2s] = 0;
    for(int i = tDN2g0; i < tDN2g15; ++i){
        val[tDN2s] +=  val[i];
    }
    val[tDN3s] = 0;
    for(int i = tDN3g0; i < tDN3g15; ++i){
        val[tDN3s] +=  val[i];
    }
    val[tDN4s] = 0;
    for(int i = tDN4g0; i < tDN4g15; ++i){
        val[tDN4s] +=  val[i];
    }
    val[tDNs]           =  val[tDN1s] + val[tDN2s] + val[tDN3s] + val[tDN4s];
    val[fracInPreDN1]   =  100 * min(1.0, val[tPreDN1] / max(1e-4, val[tDNs]));
    val[fracInDN1]      =  100 * min(1.0, val[tDN1s] / max(1e-4, val[tDNs]));
    val[fracInDN2]      =  100 * min(1.0, val[tDN2s] / max(1e-4, val[tDNs]));
    val[fracInDN3]      =  100 * min(1.0, val[tDN3s] / max(1e-4, val[tDNs]));
    val[fracInDN4]      =  100 * min(1.0, val[tDN4s] / max(1e-4, val[tDNs]));

    double pDN1 = 1. / (max(params[cycleDN1], 1e-12)) - params[deathDN1];
    double pDN2 = 1. / (max(params[cycleDN2], 1e-12)) - params[deathDN2];
    double pDN3 = 1. / (max(params[cycleDN3], 1e-12)) - params[deathDN3];
    double pDN4 = 1. / (max(params[cycleDN4], 1e-12)) - params[deathDN4];

    double InflowToDN   =  val[tPreDN1] / (max(params[decayDN1pre],1e-12));
    val[floinDN1] = InflowToDN;
    double outflowToDN2 = 0;
    for(int i = 0; i < NmaxDN1; ++i){
        outflowToDN2 += OutputCoeffOutDN1 * val[tDN1g0 + i];
        outflowToDN2 += 2*(1 - ProlifDN1[i]) * pDN1 * LessDivCoeffDN1 * val[tDN1g0 + i];
    }
    val[floDN1to2] = outflowToDN2;
    double outflowToDN3 = 0;
    for(int i = 0; i < NmaxDN2; ++i){
        outflowToDN3 += OutputCoeffOutDN2 * val[tDN2g0 + i];
        outflowToDN3 += 2*(1 - ProlifDN2[i]) * pDN2 * LessDivCoeffDN2 * val[tDN2g0 + i];
    }
    val[floDN2to3] = outflowToDN3;
    double outflowToDN4 = 0;
    for(int i = 0; i < NmaxDN3; ++i){
        outflowToDN4 += OutputCoeffOutDN3 * val[tDN3g0 + i];
        outflowToDN4 += 2*(1 - ProlifDN3[i]) * pDN3 * LessDivCoeffDN3 * val[tDN3g0 + i];
    }
    val[floDN3to4] = outflowToDN4;
    double outflowToeDP = 0;
    for(int i = 0; i < NmaxDN4; ++i){
        outflowToeDP += OutputCoeffOutDN4 * val[tDN4g0 + i];
        outflowToeDP += 2*(1 - ProlifDN4[i]) * pDN4 * LessDivCoeffDN4 * val[tDN4g0 + i];
    }
    val[flowDN4toDP] = outflowToeDP;


}

void modele5SuperDN::derivatives(const vector<double> &x, vector<double> &dxdt, const double t){

    double          InflowCoeffETP = 1;
    double          LessDivCoeffDN1 = 1;
    double          LessDivCoeffDN2 = 1;
    double          LessDivCoeffDN3 = 1;
    double          LessDivCoeffDN4 = 1;
    double          DeathCoeffDN1 = 1;
    double          DeathCoeffDN2 = 1;
    double          DeathCoeffDN3 = 1;
    double          DeathCoeffDN4 = 1;
    double          ChangeNDivDN1 = 1;
    double          ChangeNDivDN2 = 1;
    double          ChangeNDivDN3 = 1;
    double          ChangeNDivDN4 = 1;
    double          OutputCoeffOutDN1 = 0;
    double          OutputCoeffOutDN2 = 0;
    double          OutputCoeffOutDN3 = 0;
    double          OutputCoeffOutDN4 = 0;

    if(background & Back::B_ReducedInflow){
        InflowCoeffETP = 1 * (1 - x[flu]) + x[flu] * params[hypInflowCoeffETP];
    }
    if(background & Back::B_MoreDeath){
        DeathCoeffDN1         = 1 * (1 - x[flu]) + x[flu] * params[hypDeathCoeffDN1];
        DeathCoeffDN2         = 1 * (1 - x[flu]) + x[flu] * params[hypDeathCoeffDN2];
        DeathCoeffDN3         = 1 * (1 - x[flu]) + x[flu] * params[hypDeathCoeffDN3];
        DeathCoeffDN4         = 1 * (1 - x[flu]) + x[flu] * params[hypDeathCoeffDN4];
    }
    if(background & Back::B_MoreOutputThymus){
        OutputCoeffOutDN1	= 0 * (1 - x[flu]) + x[flu] * 1.0 * params[	hypRandomOutputDN	];
        OutputCoeffOutDN2	= 0 * (1 - x[flu]) + x[flu] * 1.0 * params[	hypRandomOutputDN	];
        OutputCoeffOutDN3	= 0 * (1 - x[flu]) + x[flu] * 1.0 * params[	hypRandomOutputDN	];
        OutputCoeffOutDN4	= 0 * (1 - x[flu]) + x[flu] * 1.0 * params[	hypRandomOutputDN	];
    }
    if(background & Back::B_FasterDifferentiation){
        ChangeNDivDN1	= 1 * (1 - x[flu]) + x[flu] * params[hypChangeNDivDNs];
        ChangeNDivDN2	= 1 * (1 - x[flu]) + x[flu] * params[hypChangeNDivDNs];
        ChangeNDivDN3	= 1 * (1 - x[flu]) + x[flu] * params[hypChangeNDivDNs];
        ChangeNDivDN4	= 1 * (1 - x[flu]) + x[flu] * params[hypChangeNDivDNs];
    }
    if(background & Back::B_DivisionReduced){
        LessDivCoeffDN1 = 1 * (1 - x[flu]) + x[flu] * params[hypLessDivDN];
        LessDivCoeffDN2 = 1 * (1 - x[flu]) + x[flu] * params[hypLessDivDN];
        LessDivCoeffDN3 = 1 * (1 - x[flu]) + x[flu] * params[hypLessDivDN];
        LessDivCoeffDN4 = 1 * (1 - x[flu]) + x[flu] * params[hypLessDivDN];
    }

    // recalculates nDiv and coefficients prolif[]
    calculateParameters(ProlifDN1, ChangeNDivDN1 * params[nDivDN1], NmaxDN1);
    calculateParameters(ProlifDN2, ChangeNDivDN2 * params[nDivDN2], NmaxDN2);
    calculateParameters(ProlifDN3, ChangeNDivDN3 * params[nDivDN3], NmaxDN3);
    calculateParameters(ProlifDN4, ChangeNDivDN4 * params[nDivDN4], NmaxDN4);

    double inflow = 0;
    if((background & Back::B_Reconstitution) || (background & Back::B_StartSteadyState)){
        inflow = InflowCoeffETP * params[fETP_tDN];
    }
    if(!over(tPreDN1)) {
         dxdt[tPreDN1] 	= inflow -x[tPreDN1] / (params[decayDN1pre] + 1e-12);
    }


    double InflowToDN   =  x[tPreDN1] / (max(params[decayDN1pre],1e-12));

    // ----------- Birth and death for DN1 --------------
    double pDN1 = 1. / (max(params[cycleDN1], 1e-12)) - params[deathDN1];
    if(!over( tDN1g0)) {
        dxdt[tDN1g0] 	=  InflowToDN +                                                          ( - pDN1 * LessDivCoeffDN1 - params[deathDN1] * DeathCoeffDN1 - OutputCoeffOutDN1) * x[tDN1g0];
    }
    for(int i = 1; i < NmaxDN1; ++i){
        if(!over( tDN1g0 + i)) {
            dxdt[tDN1g0 + i] 	= 2 * ProlifDN1[i-1] * pDN1 * LessDivCoeffDN1 * x[tDN1g0 + i-1] + ( - pDN1 * LessDivCoeffDN1 - params[deathDN1] * DeathCoeffDN1 - OutputCoeffOutDN1) * x[tDN1g0 + i];
        }
    }
    double outflowToDN2 = 0;
    for(int i = 0; i < NmaxDN1; ++i){
        outflowToDN2 += OutputCoeffOutDN1 * x[tDN1g0 + i];
        outflowToDN2 += 2*(1 - ProlifDN1[i]) * pDN1 * LessDivCoeffDN1 * x[tDN1g0 + i];
    }

    // ----------- Birth and death for DN2 --------------
    double pDN2 = 1. / (max(params[cycleDN2], 1e-12)) - params[deathDN2];
    if(!over( tDN2g0)) {
        dxdt[tDN2g0] 	=  outflowToDN2 +                                                          ( - pDN2 * LessDivCoeffDN2 - params[deathDN2] * DeathCoeffDN2 - OutputCoeffOutDN2) * x[tDN2g0];
    }
    for(int i = 1; i < NmaxDN2; ++i){
        if(!over( tDN2g0 + i)) {
            dxdt[tDN2g0 + i] 	= 2 * ProlifDN2[i-1] * pDN2 * LessDivCoeffDN2 * x[tDN2g0 + i-1] + ( - pDN2 * LessDivCoeffDN2 - params[deathDN2] * DeathCoeffDN2 - OutputCoeffOutDN2) * x[tDN2g0 + i];
        }
    }
    double outflowToDN3 = 0;
    for(int i = 0; i < NmaxDN2; ++i){
        outflowToDN3 += OutputCoeffOutDN2 * x[tDN2g0 + i];
        outflowToDN3 += 2*(1 - ProlifDN2[i]) * pDN2 * LessDivCoeffDN2 * x[tDN2g0 + i];
    }

    // ----------- Birth and death for DN3 --------------
    double pDN3 = 1. / (max(params[cycleDN3], 1e-12)) - params[deathDN3];
    if(!over( tDN3g0)) {
        dxdt[tDN3g0] 	=  outflowToDN3 +                                                          ( - pDN3 * LessDivCoeffDN3 - params[deathDN3] * DeathCoeffDN3 - OutputCoeffOutDN3) * x[tDN3g0];
    }
    for(int i = 1; i < NmaxDN3; ++i){
        if(!over( tDN3g0 + i)) {
            dxdt[tDN3g0 + i] 	= 2 * ProlifDN3[i-1] * pDN3 * LessDivCoeffDN3 * x[tDN3g0 + i-1] + ( - pDN3 * LessDivCoeffDN3 - params[deathDN3] * DeathCoeffDN3 - OutputCoeffOutDN3) * x[tDN3g0 + i];
        }
    }
    double outflowToDN4 = 0;
    for(int i = 0; i < NmaxDN3; ++i){
        outflowToDN4 += OutputCoeffOutDN3 * x[tDN3g0 + i];
        outflowToDN4 += 2*(1 - ProlifDN3[i]) * pDN3 * LessDivCoeffDN3 * x[tDN3g0 + i];
    }

    // ----------- Birth and death for DN4 --------------
    double pDN4 = 1. / (max(params[cycleDN4], 1e-12)) - params[deathDN4];
    if(!over( tDN4g0)) {
        dxdt[tDN4g0] 	=  outflowToDN4 +                                                          ( - pDN4 * LessDivCoeffDN4 - params[deathDN4] * DeathCoeffDN4 - OutputCoeffOutDN4) * x[tDN4g0];
    }
    for(int i = 1; i < NmaxDN4; ++i){
        if(!over( tDN4g0 + i)) {
            dxdt[tDN4g0 + i] 	= 2 * ProlifDN4[i-1] * pDN4 * LessDivCoeffDN4 * x[tDN4g0 + i-1] + ( - pDN4 * LessDivCoeffDN4 - params[deathDN4] * DeathCoeffDN4 - OutputCoeffOutDN4) * x[tDN4g0 + i];
        }
    }
    double outflowToeDP = 0;
    for(int i = 0; i < NmaxDN4; ++i){
        outflowToeDP += OutputCoeffOutDN4 * x[tDN4g0 + i];
        outflowToeDP += 2*(1 - ProlifDN4[i]) * pDN4 * LessDivCoeffDN4 * x[tDN4g0 + i];
    }

}




/*void modele5SuperDN::calculateParameters(double nDivDN1, double nDivDN2, double nDivDN3, double nDivDN4){

    double dynamicNDiv1  = min((double) NmaxDN1 + 0.9999999, nDivDN1);
    N_DN1                = (int) dynamicNDiv1;
    double divFloatDN1          = dynamicNDiv1 - (double) N_DN1;
    if(divFloatDN1 < 1e-12) {N_DN1 = max(0,N_DN1-1);}

    for(int i = 0; i <= N-1; ++i){
        if(i >= 0) ProlifDN1[i] = 1.0;
    }
    if(N > 0) ProlifDN1[N-1] = divFloat;
    for(int i = N; i < NmaxDN1; ++i){
        ProlifDN1[i] = 0;
    }
}*/
