// ------- Automatically generated model -------- //
#include "modele0OneCompartment.h"

#include <sstream>

modele0OneCompartment::modele0OneCompartment() : Model(NbVariables, NbParameters), background(Back::WT) {
    name = string("modele0OneCompartment");
    dt = 0.001; // initial time step -> then it is adaptive
    print_every_dt = 1200; //every how many seconds it is plotting

    // Name of variables
    names[flu]          = string("flu");
    names[tDNs]         = string("tDNs");
    for(int i = divDNg0; i <= divDNg20; ++i){
        stringstream res; res << "divDN-g" <<  i - divDNg0;
        names[i] = res.str();
    }
    names[tOut]         = string("Output");

	// the names of variables that can be accessed by outside (global name-space)
    extNames[tDNs] = GlobalName(N::tDN);

    Nmax = divDNg20 - divDNg0 + 1;
    CoeffPerGen.clear();
    CoeffPerGen.resize(Nmax, 0);
    DoProlif.clear();
    DoProlif.resize(Nmax, 0);

    // Name of parameters
    paramNames[flu_peak]                = "flu_peak / peak of flu effect in days";
    paramNames[flu_std]                 = "flu_std / width of flu effect (stddev)";
    paramNames[fETP_tDN]                = "fETP_tDN / DN thymic Inflow";
    paramNames[NdivDN]                  = "NdivDN";
    paramNames[pDN]                     = "pDN";
    paramNames[dDN]                     = "dDN";
    paramNames[T_DN]                    = "TDN";
    paramNames[hypInflowCoeffETP]       = "hypInflowCoeffETP";
    paramNames[hypLessDivDN]            = "hypLessDivDN",
    paramNames[hypDeathCoeffDN]         = "hypDeathCoeffDN",
    paramNames[hypRandomOutputDN]       = "hypRandomOutputDN",
    paramNames[hypFasterCoeffDNtoDP]    = "hypFasterCoeffDNtoDP";
    paramNames[logisticThymus]          = "logisticThymus";
    paramNames[logisticStrength]        = "logisticStrength";

    paramLowBounds[flu_peak]    = 5;                paramUpBounds[flu_peak]     = 15;
    paramLowBounds[flu_std]     = 0.5;              paramUpBounds[flu_std]      = 10;
    paramLowBounds[fETP_tDN]    = 0.001;            paramUpBounds[fETP_tDN]     = 1;
    paramLowBounds[NdivDN]      = 0;                paramUpBounds[NdivDN]       = 0;
    paramLowBounds[pDN]         = 0;                paramUpBounds[pDN]          = 0;
    paramLowBounds[dDN]         = 0;                paramUpBounds[dDN]          = 0;
    paramLowBounds[T_DN]        = 0;                paramUpBounds[T_DN]         = 0;
    paramLowBounds[hypInflowCoeffETP]    = 0.05;    paramUpBounds[hypInflowCoeffETP]    = 20;
    paramLowBounds[hypLessDivDN]         = 0.01;	paramUpBounds[hypLessDivDN]         = 20;
    paramLowBounds[hypDeathCoeffDN]      = 0.05;    paramUpBounds[hypDeathCoeffDN]      = 20;
    paramLowBounds[hypRandomOutputDN]    = 0.05;    paramUpBounds[hypRandomOutputDN]    = 20;
    paramLowBounds[hypFasterCoeffDNtoDP] = 0.05;	paramUpBounds[hypFasterCoeffDNtoDP] = 20;
    paramLowBounds[logisticThymus]       = 0.1;     paramUpBounds[logisticThymus]       = 500;
    paramLowBounds[logisticStrength]     = 0.1;     paramUpBounds[logisticStrength]     = 10;
}

void modele0OneCompartment::setBaseParameters(){
    background = Back::WT;
	params.clear();     // to make sure they are all put to zero
    params.resize(NbParameters, 0.0);

    // Here, takes the value of the 'last generation only'
    params[flu_peak]                = 9;
    params[flu_std]                 = 2.5;
    params[fETP_tDN]                = 0.05	;
    params[NdivDN]                  = 5.0032;
    params[pDN]                     = 0.23;
    params[dDN]                     = 0.1;
    params[T_DN]                    = 2; // will depend on pDN and dDN
    params[hypInflowCoeffETP]       = 0.3;
    params[hypLessDivDN]            = 1;
    params[hypRandomOutputDN]       = 1;
    params[hypDeathCoeffDN]         = 5;
    params[hypFasterCoeffDNtoDP]    = 1;
    params[logisticThymus]          = 90;
    params[logisticStrength]        = 2.0;

	setBaseParametersDone();
}

void modele0OneCompartment::calculateParameters(double _FasterCoeffDNtoDP){
    double dynamicNDiv  = min((double) Nmax + 0.9999999, _FasterCoeffDNtoDP *  params[NdivDN]);
    N               = (int) dynamicNDiv;
    divFloat     = dynamicNDiv - (double) N;
    params[T_DN]        = 1 / (max(params[pDN] + params[dDN], 1e-12));

    C = 0;
    if(divFloat < 1e-12) {N = max(0,N-1);}
    else {C = min(1000., (1 / params[T_DN]) * ((1 / divFloat) - 1));}

    for(int i = 0; i < Nmax; ++i){
        CoeffPerGen[i] = 0;
    }
    if(background & Back::B_UseC0){
        CoeffPerGen[N] = C;
    }
    if(background & Back::B_UseHighC){
        CoeffPerGen[N] = C;
        for(unsigned int i = N+1; i < CoeffPerGen.size(); ++i){
            CoeffPerGen[i] = 100;
        }
    }

    for(int i = 0; i <= N-1; ++i){
        DoProlif[i] = 1.0;
    }
    for(int i = N-1; i < Nmax; ++i){
        if(i >= 0) DoProlif[i] = 0;
    }
    if((!(background & Back::B_UseC0)) && (!(background & Back::B_UseHighC))) {
        if(N > 0) DoProlif[N-1] = divFloat; // weird case
    }
}

void modele0OneCompartment::initialise(long long _background){ // don't touch to parameters !
    val.clear();  val.resize(NbVariables, 0.0);
    init.clear(); init.resize(NbVariables, 0.0);

    background = _background;
    // change scaling inside moonfit !!!!!!
    init[flu] = 0;
    init[tDNs] = 0;     // aim 3.7M
    for(int i = divDNg0; i <= divDNg20; ++i){
        init[i] = 0;
    }

    calculateParameters();

    if(N < 1) cerr << "ERR : the model is not designed for Ndiv < 1" << endl;


    if(background & Back::B_StartSteadyState){

        // First model: with a C,
        if(params[NdivDN] < 1e-12) cout << "WRN: you use a multi-generation model and chose N=0. Cannot simulate that so I put proliferation pDN = 0. It will change T\n" << endl;

        //cout << "Init for Oen Compartment Model: Ndiv=" << params[NdivDN] << ", so C=" << C << " vec " << CoeffPerGen[0] << " "  << CoeffPerGen[1] << " "  << CoeffPerGen[2] << " "  << CoeffPerGen[3] << " "  << CoeffPerGen[4] << " "  << CoeffPerGen[5] << " "  << CoeffPerGen[6] << " "<< endl;

        double InflowToDN = params[fETP_tDN];
        init[ divDNg0] = InflowToDN / (max((params[pDN] + params[dDN] + CoeffPerGen[0]) , 1e-12));
        for(int i = 1; i < Nmax; ++i){
            init[ divDNg0+i] = 2*init[ divDNg0+i-1] * DoProlif[i-1] * (params[pDN]) / (max(1e-12, params[pDN] + params[dDN] + CoeffPerGen[i]));
        }
        //double outflowToDP = C * init[divDNg0 + N] + 2*init[divDNg0 + N] * (params[pDN]);
    }

    for(int i = 0; i < NbVariables; ++i){
		val[i] = init[i];}
	t = 0;
	initialiseDone();
}


void modele0OneCompartment::updateDerivedVariables(){
    val[tDNs] = 0;
    for(int i = divDNg0; i < divDNg20; ++i){
        val[tDNs] +=  val[i];
    }
    val[flu] = 0;
    if(background & Back::B_UseStep){
        if(t > (params[flu_peak] - 0.5 * params[flu_std])) val[flu] = 1;
    } else if (background & Back::B_UseSquare){
        if(fabs(t - params[flu_peak]) < 0.5*params[flu_std]) val[flu] = 1;
    } else {
        val[flu] = exp(-(t - params[flu_peak]) * (t - params[flu_peak]) / (params[flu_std] * params[flu_std]));
    }

    // maybe calculate parameters again ??
    calculateParameters();

    double          LessDivCoeffDN = 1;
    double          OutputCoeffOutDN = 0;
    if(background & Back::B_MoreOutputThymus){
        OutputCoeffOutDN	= 0 * (1 - val[flu]) + val[flu] * 1.0 * params[	hypRandomOutputDN	];
    }
    if(background & Back::B_DivisionReduced){
        LessDivCoeffDN = 1 * (1 - val[flu]) + val[flu] * params[hypLessDivDN];
    }
    double outflowToDP = 0;
    // The cells that are remaining in a compartment are still leaving the compartment (as they enter, they can still complete the cycle)
    for(int i = 0; i < Nmax; ++i){ // DO NOT REACH Nmax+1, there are only Nmax !!
        outflowToDP += OutputCoeffOutDN * val[divDNg0 + i];
        outflowToDP +=  CoeffPerGen[i] * val[divDNg0 + i];
        outflowToDP += 2*(1 - DoProlif[i]) * params[pDN] * LessDivCoeffDN * val[divDNg0 + i]; // No 2 here, they do not divide ??
    }      
    /*cout << t << "\t" << outflowToDP << " " << LessDivCoeffDN;
    for(int i = 0; i < Nmax; ++i){
        cout << "C" << i << "=" << CoeffPerGen[i] << " ";
    }
    for(int i = 0; i < Nmax; ++i){
        cout << "P" << i << "=" << DoProlif[i] << " ";
    }
    for(int i = 0; i < Nmax; ++i){
        cout << "N" << i << "=" << val[divDNg0 + i] << " ";
    }
    cout << endl;*/

    val[tOut] = outflowToDP; //deriv[divDNg0 + 5]; //now_out; // last calculated derivatives
}

void modele0OneCompartment::derivatives(const vector<double> &x, vector<double> &dxdt, const double t){


    //paramNames[hypInflowCoeffETP]       = "hypInflowCoeffETP";
    //paramNames[hypLessDivDN]            = "hypLessDivDN",
    //paramNames[hypDeathCoeffDN]         = "hypDeathCoeffDN",
    //paramNames[hypFasterCoeffDNtoDP]    = "hypFasterCoeffDNtoDP";
    //paramNames[logisticThymus]          = "logisticThymus";
    //paramNames[logisticStrength]        = "logisticStrength";


    double          InflowCoeffETP = 1;
    double          LessDivCoeffDN = 1;
    double          DeathCoeffDN = 1;
    double          FasterCoeffDNtoDP = 1;
    double          OutputCoeffOutDN = 0;

    if(background & Back::B_ReducedInflow){
        InflowCoeffETP = 1 * (1 - x[flu]) + x[flu] * params[hypInflowCoeffETP];
    }
    if(background & Back::B_MoreDeath){
        DeathCoeffDN         = 1 * (1 - x[flu]) + x[flu] * params[hypDeathCoeffDN];
    }
    if(background & Back::B_MoreOutputThymus){
        OutputCoeffOutDN	= 0 * (1 - x[flu]) + x[flu] * 1.0 * params[	hypRandomOutputDN	];
    }
    if(background & Back::B_FasterDifferentiation){
        FasterCoeffDNtoDP	= 1 * (1 - x[flu]) + x[flu] * params[	hypFasterCoeffDNtoDP	];
    }
    if(background & Back::B_DivisionReduced){
        LessDivCoeffDN = 1 * (1 - x[flu]) + x[flu] * params[hypLessDivDN];
    }
    if(false) if (background & Back::B_LogisticTotalProlif){
        double coeff = (1/(1 - 1 / (params[logisticStrength]+1e-9)))*(1 - ((1/(params[logisticStrength] + 1e-9))*x[tDNs] / (params[logisticThymus] + 1e-9)));
        //    double coeff = 2*(1 - (0.5*x[ttotal] / (init[tDN] + init[tDP] + init[tTconv] + init[tTRegP25] + init[tTRegPFp3] + init[tTreg] + init[tSP8] + 1e-9)));
        LessDivCoeffDN *= coeff;
    }

    // recalculates nDiv and coefficients prolif[] or C[]
    calculateParameters(FasterCoeffDNtoDP);

    // Note: even if a population is not proliferating, it should still be simulated. Indeed, Ndiv can be dynamic, and it might be cells remaining in that stage.
    double InflowToDN   = InflowCoeffETP * params[fETP_tDN];

    if(!over( divDNg0)) {
        dxdt[divDNg0] 	=  InflowToDN +                                                  ( - params[pDN] * LessDivCoeffDN - CoeffPerGen[0]  - params[dDN] * DeathCoeffDN - OutputCoeffOutDN) * x[divDNg0];
    }
    for(int i = 1; i < Nmax; ++i){
        if(!over( divDNg0 + i)) {
            dxdt[divDNg0 + i] 	= 2 * DoProlif[i-1] * params[pDN] * LessDivCoeffDN * x[divDNg0 + i-1] + ( - params[pDN] * LessDivCoeffDN - CoeffPerGen[i]  - params[dDN] * DeathCoeffDN - OutputCoeffOutDN) *  x[divDNg0 + i];
        }
    }
}


//int Nmax            = divDNg20 - divDNg0 + 1;
//double dynamicNDiv  = min((double) Nmax + 0.9999999, FasterCoeffDNtoDP *  params[NdivDN]);
//int N               = (int) dynamicNDiv;
//double divFloat     = dynamicNDiv - (double) N;
//params[T_DN]        = 1 / (max(params[pDN] + params[dDN], 1e-12));

//double C = 0;
//if(divFloat < 1e-12) {N = max(0,N-1);}
//else {C = min(1000., (1 / params[T_DN]) * ((1 / divFloat) - 1));}

//vector<double> CoeffPerGen = vector<double>(Nmax, 0);
//if(background & Back::B_UseC0){
//    CoeffPerGen[N] = C;
//}
//if(background & Back::B_UseHighC){
//    CoeffPerGen[N] = C;
//    for(int i = N+1; i < CoeffPerGen.size(); ++i){
//        CoeffPerGen[i] = 100;
//    }
//}

//vector<double> DoProlif = vector<double>(Nmax, 0);
//for(int i = 0; i <= N-1; ++i){
//    if(i >= 0) DoProlif[i] = 1.0;
//}
//if((!(background & Back::B_UseC0)) && (!(background & Back::B_UseHighC))) {
//    if(N > 0) DoProlif[N-1] = divFloat; // weird case
//}
