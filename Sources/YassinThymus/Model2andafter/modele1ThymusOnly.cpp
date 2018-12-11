// ------- Automatically generated model -------- //
#include "../../common.h"

#include "modeleLeishmaniaMajor.h"

enum{k_Mrec0,
     alpha,
     S_M,

     k_i,
     k_a,
     k_ia,
     k_P,
     k_r,
     k_D,

     d_M,
     d_Mi,
     d_Mia,
     d_Ma,
     d_P,

     C_P,
     C_im,

     beta,

     C_iP,
     //Delay,
     NbParameters};

enum{M, Mi, Mia, Ma, Matot, P, D, NbVariables};
modeleLeishmania::modeleLeishmania() : Modele(NbVariables, NbParameters), background(Back::WT) {
    name = string("modeleLeishmania");
    dt = 0.001; // initial time step -> then it is adaptive
    print_all_secs = 1200; //every how many seconds it is plotting
	// Name of variables
    names[Mac] = string("Macrophages");
    names[Mi] = string("Macrophages infected");
    names[Mia] = string("Macrophages infected activated");
    names[Ma] = string("Macrophages activated");
    names[Matot] = string("Macrophages activated total");
    names[P] = string("Parasite");
    names[D] = string("Delay");
	
	// the names of variables that can be accessed by outside (global name-space)
    extNames[Mac] = N::Mac;
    extNames[Mi] = N::Mi;
    extNames[Mia] = N::Mia;
    extNames[Ma] = N::Ma;
    extNames[Matot] = N::Matot;
    extNames[P] = N::P;
    extNames[D] = N::D;

	// Name of parameters

    paramNames[k_Mrec0] = "Basal recruitment rate";
    paramNames[alpha] 	= "alpha";
    paramNames[S_M] 	= "S_M";

    paramNames[k_i] 	= "k_i";
    paramNames[k_a] 	= "k_a";
    paramNames[k_ia] 	= "k_ia";
    paramNames[k_P] 	= "k_P";
    paramNames[k_r] 	= "k_r";
    paramNames[k_D] 	= "k_D";

    paramNames[d_M] 	= "death rate M";
    paramNames[d_Mi] 	= "death rate Mi";
    paramNames[d_Mia] 	= "death rate Mia";
    paramNames[d_Ma] 	= "death rate Ma";
    paramNames[d_P] 	= "death rate P";

    paramNames[C_P] 	= "C_P";
    paramNames[C_im] 	= "C_im";

    paramNames[beta] 	= "beta";

    paramNames[C_iP] 	= "C_iP";
//----------------------------------------------------------------------
    paramLowBounds[k_Mrec0] = 1e0;
    paramLowBounds[alpha]   = 1e-4;
    paramLowBounds[S_M]     = 1e1;

    paramLowBounds[k_i] 	= 1e-3;
    paramLowBounds[k_a] 	= 1e-3;
    paramLowBounds[k_ia] 	= 1e-3;
    paramLowBounds[k_P] 	= 1e-3;
    paramLowBounds[k_r] 	= 1e-3;
    paramLowBounds[k_D] 	= 1e-3;

    paramLowBounds[d_M] 	= 1e-3;
    paramLowBounds[d_Mi] 	= 1e-3;
    paramLowBounds[d_Mia] 	= 1e-3;
    paramLowBounds[d_Ma] 	= 1e-3;
    paramLowBounds[d_P] 	= 1e-3;

    paramLowBounds[C_P] 	= 1e0;
    paramLowBounds[C_im] 	= 1e0;

    paramLowBounds[beta] 	= 1e-3;

    paramLowBounds[C_iP] 	= 1e0;
//-------------------------------------------------------------------
    paramUpBounds[k_Mrec0] 	= 1e5;
    paramUpBounds[alpha] 	= 1e4;
    paramUpBounds[S_M]      = 1e5;

    paramUpBounds[k_i]      = 1e4;
    paramUpBounds[k_a]      = 1e4;
    paramUpBounds[k_ia]     = 1e4;
    paramUpBounds[k_P]      = 1e4;
    paramUpBounds[k_r]      = 1e4;
    paramUpBounds[k_D]      = 1e4;

    paramUpBounds[d_M] 	    = 1e5;
    paramUpBounds[d_Mi] 	= 1e5;
    paramUpBounds[d_Mia] 	= 1e5;
    paramUpBounds[d_Ma] 	= 1e5;
    paramUpBounds[d_P]  	= 1e5;

    paramUpBounds[C_P] 	= 1e5;
    paramUpBounds[C_im] = 1e5;

    paramUpBounds[beta]	= 1e4;

    paramUpBounds[C_iP]	= 1e5;

    backSimulated.clear();
	backSimulated.push_back(Back::WT);
}

void modeleLeishmania::setBaseParameters(){
    background = Back::WT;
	params.clear();     // to make sure they are all put to zero
    params.resize(NbParameters, 0.0);

    params[k_Mrec0] = 97450.0;
    params[alpha]   = 9.0;
    params[S_M]     = 11979.0;

    params[k_i] 	= 2486.99984;
    params[k_a] 	= 9669.0010;
    params[k_ia] 	= 8199.00022;
    params[k_P] 	= 7124.11003;
    params[k_r] 	= 4949.1;
    params[k_D] 	= 8946.5;

    params[d_M] 	= 951.6;
    params[d_Mi] 	= 3197.76;
    params[d_Mia] 	= 673.76;
    params[d_Ma] 	= 2368.76;
    params[d_P] 	= 2753.6;

    params[C_P] 	= 52;
    params[C_im] 	= 6549;

    params[beta] 	= 1.5;

    params[C_iP] 	= 1e3;

	setBaseParametersDone();
}

void modeleLeishmania::initialise(long long _background){ // don't touch to parameters !
	val.clear();
    val.resize(NbVariables, 0.0);
	init.clear();
    init.resize(NbVariables, 0.0);

    // test if each possible background is in the current combination of backgrounds (stored in the field background)
    if((background != Back::WT) && (background != _background)){
        cerr << "WRN : modeleLeishmania::initialize, when the background has been changed from WT, you should not change it again, because parameters can not be retrieved. Please load parameters again" << endl;
    }
    background = _background;
    if(background == Back::WT){}
    //if(background == Back::M2){}
    //if(background == Back::TCRGATA3NEGKO){   params[KTCRGATA3]   = 0;} // for different options i.e. deficiency in something


    // if the initial values depend on parameters
    /*init[IL2] = params[IL2EQ];
    init[IL4] = params[IL4EQ];*/

    init[Mac]   = 33293;
    init[Mi]    = 36;
    init[Mia]   = 1;
    init[Ma]    = 291;
    init[Matot] = 146;
    init[P]     = 3391;
    init[D]     = 0.01; // maybe as a parameter is beter -> params[Delay] use a new name
    //init[D] = params[Delay];


    for(int i = 0; i < NbVariables; ++i){
		val[i] = init[i];}
	t = 0;
	initialiseDone();
}


void modeleLeishmania::derivatives(const vector<double> &x, vector<double> &dxdt, const double t){

        cerr << "ERROR" << endl;
}

void model1::derivatives(const vector<double> &x, vector<double> &dxdt, const double t){

// Model 1
    if(!over(Mac)) {// if it is not overrided by data then make the computaiton below
        dxdt[Mac] 	= params[k_Mrec0]+ params[alpha]*x[P]/(params[S_M] + x[P]) - params[k_i]*x[P]*x[Mac] - params[k_a]*x[D]*x[Mac]/(params[C_im] + x[Matot]) - params[d_M]*x[Mac];
        //cerr << "waza" << endl;
    }
    if(!over(Mi)) // if it is not overrided by data then make the computaiton below
        dxdt[Mi] 	= params[k_i]*x[P]*x[Mac] - params[k_a]*x[D]*x[Mi]/(params[C_im] + x[Matot]) - params[d_Mi]*x[Mi];

    if(!over(Mia)) // if it is not overrided by data then make the computaiton below
        dxdt[Mia] 	= params[k_a]*x[D]*x[Mi]/(params[C_im] + x[Matot]) + params[k_ia]*x[P]*x[Ma] - params[d_Mia]*x[Mia];

    if(!over(Ma)) // if it is not overrided by data then make the computaiton below
        dxdt[Ma] 	= params[k_a]*x[D]*x[Mac]/(params[C_im] + x[Matot]) - params[k_ia]*x[P]*x[Ma] - params[d_Ma]*x[Ma];

    if(!over(P)) // if it is not overrided by data then make the computaiton below
        dxdt[P] 	= params[k_P]*(1 - x[P]/params[C_P])*x[P]*(x[Mi] + x[Mia]) - params[k_r]*x[P]*x[Mia] - params[d_P]*x[P];

    if(!over(Matot)) // if it is not overrided by data then make the computaiton below
        dxdt[Matot] = params[k_a]*x[D]*(x[Mi] + x[Mac])/(params[C_im] + x[Matot]) - params[d_Mia]*x[Mia] - params[d_Ma]*x[Ma];

    if(!over(D)) // if it is not overrided by data then make the computaiton below
        dxdt[D] 	= params[k_D]*x[P]*(1 - x[D])*x[D];
    //*/

}

void model2::derivatives(const vector<double> &x, vector<double> &dxdt, const double t){

// Model 2
    if(!over(M)) // if it is not overrided by data then make the computaiton below
        dxdt[Mac] 	= params[k_Mrec0]+ params[alpha]*x[P]/(params[S_M] + x[P]) - params[k_i]*x[P]*x[Mac] - params[k_a]*x[D]*x[Mac]/(params[C_im] + x[Matot]) - params[d_M]*x[Mac];

    if(!over(Mi)) // if it is not overrided by data then make the computaiton below
        dxdt[Mi] 	= params[k_i]*x[P]*x[Mac] - params[k_a]*x[D]*x[Mi]/(params[C_im] + x[Matot]) - params[d_Mi]*x[Mi];

    if(!over(Mia)) // if it is not overrided by data then make the computaiton below
        dxdt[Mia] 	= params[k_a]*x[D]*params[Mi]/(params[C_im] + x[Matot]) + params[k_ia]*x[P]*x[Ma] - params[d_Mia]*x[Mia];

    if(!over(Ma)) // if it is not overrided by data then make the computaiton below
        dxdt[Ma] 	= params[k_a]*x[D]*x[Mac]/(params[C_im] + x[Matot]) - params[k_ia]*x[P]*x[Ma] - params[d_Ma]*x[Ma];

    if(!over(P)) // if it is not overrided by data then make the computaiton below
        dxdt[P] 	= params[k_P]*(1 - x[P]/params[C_P])*x[P]*(x[Mi] + params[beta]*x[Mia]) - params[d_P]*x[P];

    if(!over(Matot)) // if it is not overrided by data then make the computaiton below
        dxdt[Matot] = params[k_a]*x[D]*(x[Mi] + x[Mac])/(params[C_im] + x[Matot]) - params[d_Mia]*x[Mia] - params[d_Ma]*x[Ma];

    if(!over(D)) // if it is not overrided by data then make the computaiton below
        dxdt[D] 	= params[k_D]*x[P]*(1 - x[D])*x[D];
        //*/

}

void model3::derivatives(const vector<double> &x, vector<double> &dxdt, const double t){
    if(!over(M)) // if it is not overrided by data then make the computaiton below
        dxdt[Mac] 	= params[k_Mrec0]+ params[alpha]*x[P]/(params[S_M] + x[P]) - params[k_i]*x[P]*x[Mac] - params[k_a]*x[D]*x[Mac]/(params[C_im] + x[Matot]) - params[d_M]*x[Mac];

    if(!over(Mi)) // if it is not overrided by data then make the computaiton below
        dxdt[Mi] 	= params[k_i]*x[P]*x[Mac] - params[k_a]*x[D]*x[Mi]/(params[C_im] + x[Matot]) - params[d_Mi]*x[Mi];

    if(!over(Mia)) // if it is not overrided by data then make the computaiton below
        dxdt[Mia] 	= params[k_a]*x[D]*params[Mi]/(params[C_im] + x[Matot]) + params[k_ia]*x[P]*x[Ma] - params[d_Mia]*x[Mia];

    if(!over(Ma)) // if it is not overrided by data then make the computaiton below
        dxdt[Ma] 	= params[k_a]*x[D]*x[Mac]/(params[C_im] + x[Matot]) - params[k_ia]*x[P]*x[Ma] - params[d_Ma]*x[Ma];

    if(!over(P)) // if it is not overrided by data then make the computaiton below
        dxdt[P] 	= params[k_P]*(1 - x[P]/params[C_P])*x[P]*(x[Mi] + params[beta]*x[Mia]) - params[k_r]*x[P]*params[Mia] - params[d_P]*x[P];

    if(!over(Matot)) // if it is not overrided by data then make the computaiton below
        dxdt[Matot] = params[k_a]*x[D]*(x[Mi] + x[Mac])/(params[C_im] + x[Matot]) - params[d_Mia]*x[Mia] - params[d_Ma]*x[Ma];

    if(!over(D)) // if it is not overrided by data then make the computaiton below
        dxdt[D] 	= params[k_D]*x[P]*(1 - x[D])*x[D];
    //*/

}

void model4::derivatives(const vector<double> &x, vector<double> &dxdt, const double t){
    if(!over(M)) // if it is not overrided by data then make the computaiton below
        dxdt[Mac] 	= params[k_Mrec0]+ params[alpha]*x[P]/(params[S_M] + x[P]) - params[k_i]*x[P]*x[Mac] - params[k_a]*x[D]*x[Mac]/(params[C_im] + x[Matot]) - params[d_M]*x[Mac];

    if(!over(Mi)) // if it is not overrided by data then make the computaiton below
        dxdt[Mi] 	= params[k_i]*x[P]*x[Mac] - params[k_a]*x[D]*x[Mi]/(params[C_im] + x[Matot]) - params[d_Mi]*x[Mi];

    if(!over(Mia)) // if it is not overrided by data then make the computaiton below
        dxdt[Mia] 	= params[k_a]*x[D]*params[Mi]/(params[C_im] + x[Matot]) + params[k_ia]*x[P]*x[Ma] - params[d_Mia]*x[Mia];

    if(!over(Ma)) // if it is not overrided by data then make the computaiton below
        dxdt[Ma] 	= params[k_a]*x[D]*x[Mac]/(params[C_im] + x[Matot]) - params[k_ia]*x[P]*x[Ma] - params[d_Ma]*x[Ma];

    if(!over(P)) // if it is not overrided by data then make the computaiton below
        dxdt[P] 	= params[k_P]*(1 - x[P]/params[C_P])*x[P]*(x[Mi] + x[Mia]) - params[k_r]*x[P]*x[Matot] - params[d_P]*x[P];

    if(!over(Matot)) // if it is not overrided by data then make the computaiton below
        dxdt[Matot] = params[k_a]*x[D]*(x[Mi] + x[Mac])/(params[C_im] + x[Matot]) - params[d_Mia]*x[Mia] - params[d_Ma]*x[Ma];

    if(!over(D)) // if it is not overrided by data then make the computaiton below
        dxdt[D] = params[k_D]*x[P]*(1 - x[D])*x[D];
}

void model5::derivatives(const vector<double> &x, vector<double> &dxdt, const double t){
    if(!over(M)) // if it is not overrided by data then make the computaiton below
        dxdt[Mac] 	= params[k_Mrec0]+ params[alpha]*x[P]/(params[S_M] + x[P]) - params[k_i]*x[P]*x[Mac] - params[k_a]*x[D]*x[Mac]/(params[C_im] + x[Matot]) - params[d_M]*x[Mac];

    if(!over(Mi)) // if it is not overrided by data then make the computaiton below
        dxdt[Mi] 	= params[k_i]*x[P]*x[Mac] - params[k_a]*x[D]*x[Mi]/(params[C_im] + x[Matot]) - params[d_Mi]*x[Mi];

    if(!over(Mia)) // if it is not overrided by data then make the computaiton below
        dxdt[Mia] 	= params[k_a]*x[D]*params[Mi]/(params[C_im] + x[Matot]) + params[k_ia]*x[P]*x[Ma] - params[d_Mia]*x[Mia];

    if(!over(Ma)) // if it is not overrided by data then make the computaiton below
        dxdt[Ma] 	= params[k_a]*x[D]*x[Mac]/(params[C_im] + x[Matot]) - params[k_ia]*x[P]*x[Ma] - params[d_Ma]*x[Ma];

    if(!over(P)) // if it is not overrided by data then make the computaiton below
        dxdt[P] 	= params[k_P]*(1 - x[P]*x[P]/params[C_P])*(x[Mi] + x[Mia])/(params[C_iP]+x[Matot])- params[d_P]*x[P];

    if(!over(Matot)) // if it is not overrided by data then make the computaiton below
        dxdt[Matot] = params[k_a]*x[D]*(x[Mi] + x[Mac])/(params[C_im] + x[Matot]) - params[d_Mia]*x[Mia] - params[d_Ma]*x[Ma];

    if(!over(D)) // if it is not overrided by data then make the computaiton below
        dxdt[D] 	= params[k_D]*x[P]*(1 - x[D])*x[D];
    //*/
}

void model6::derivatives(const vector<double> &x, vector<double> &dxdt, const double t){
    if(!over(M)) // if it is not overrided by data then make the computaiton below
        dxdt[Mac] 	= params[k_Mrec0]+ params[alpha]*x[P]/(params[S_M] + x[P]) - params[k_i]*x[P]*x[Mac] - params[k_a]*x[D]*x[Mac]/(params[C_im] + x[Matot]) - params[d_M]*x[Mac];

    if(!over(Mi)) // if it is not overrided by data then make the computaiton below
        dxdt[Mi] 	= params[k_i]*x[P]*x[Mac] - params[k_a]*x[D]*x[Mi]/(params[C_im] + x[Matot]) - params[d_Mi]*x[Mi];

    if(!over(Mia)) // if it is not overrided by data then make the computaiton below
        dxdt[Mia] 	= params[k_a]*x[D]*params[Mi]/(params[C_im] + x[Matot]) + params[k_ia]*x[P]*x[Ma] - params[d_Mia]*x[Mia];

    if(!over(Ma)) // if it is not overrided by data then make the computaiton below
        dxdt[Ma] 	= params[k_a]*x[D]*x[Mac]/(params[C_im] + x[Matot]) - params[k_ia]*x[P]*x[Ma] - params[d_Ma]*x[Ma];

    if(!over(P)) // if it is not overrided by data then make the computaiton below
        dxdt[P] 	= params[k_P]*(1 - x[P]*x[P]/params[C_P])*(x[Mi] + x[Mia])/(params[C_iP]+x[Matot]) - params[k_r]*x[P]*x[Matot] - params[d_P]*x[P];

    if(!over(Matot)) // if it is not overrided by data then make the computaiton below
        dxdt[Matot] = params[k_a]*x[D]*(x[Mi] + x[Mac])/(params[C_im] + x[Matot]) - params[d_Mia]*x[Mia] - params[d_Ma]*x[Ma];

    if(!over(D)) // if it is not overrided by data then make the computaiton below
        dxdt[D] 	= params[k_D]*x[P]*(1 - x[D])*x[D];
    //*/
}
