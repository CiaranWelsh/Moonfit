#include "namesThymus.h"
#include <iostream>
#include <cmath>
#include <sstream>
using namespace std;

static vector<string> GNames;
static vector<string> codingNames;
static vector<string> expCodingNames;
static vector<long long> backgrounds;

long long getBackgroundNr(int i){
    static bool loaded = false;
    if(!loaded){
        backgrounds.push_back(Back::WT);
      //backgrounds.push_back(Back::TCRGATA3NEGKO);
    }
    if(i < 0)  return backgrounds.size();
    if((i < 0) || (i >= (int) backgrounds.size())){
        cerr << "ERR:  backgrounds(" << i << ") is not defined, only " << backgrounds.size() << " backgrounds" << endl;
        return -1;
    }
    return backgrounds[i];
}

string getBackgroundName(long long background){
    stringstream res;
    if(background & Back::WT)	res << "-WT";
    //if(background & Back::TCRGATA3NEGKO)	res << "-TCRGATA3NEGKO";

    return res.str();
}


/*void testBackgroundSystem(){
    long a1 = pow(2,10);
    long b1 = pow(2,5);
    long c1 = a1 | b1;  // adding backgrounds
    cerr << a1 << "," << b1 << "," << (a1 | b1) << endl;
    // recovering backgrounds
    cerr << (c1 & ((long) pow(2,1))) << "\t";
    cerr << (c1 & ((long) pow(2,2))) << "\t";
    cerr << (c1 & ((long) pow(2,3))) << "\t";
    cerr << (c1 & ((long) pow(2,4))) << "\t";
    cerr << (c1 & ((long) pow(2,5))) << "\t";
    cerr << (c1 & ((long) pow(2,6))) << "\t";
    cerr << (c1 & ((long) pow(2,7))) << "\t";
    cerr << (c1 & ((long) pow(2,8))) << "\t";
    cerr << (c1 & ((long) pow(2,9))) << "\t";
    cerr << (c1 & ((long) pow(2,10))) << "\t";
}*/


string CodingNameExp(int id){
    static bool loaded = false;
    if(!loaded){
        expCodingNames.push_back(string("PBS"));
        expCodingNames.push_back(string("Infection"));
    }
    if((id < 0) || (id >= (int)  expCodingNames.size())) {
          return string("Not Found");
    }
    else return expCodingNames[id];
}

string GlobalName(int id){
    static bool loaded = false;

    GNames.resize(N::NB_GLOB_VARS);
    if(!loaded){
        GNames[N::NoName] = "NoName";
        GNames[N::tDN1pre ] = "tDN1pre";
        GNames[N::tDN1 ] = "tDN1";
        GNames[N::tDN2 ] = "tDN2";
        GNames[N::tDN3 ] = "tDN3";
        GNames[N::tDN4 ] = "tDN4";
        GNames[N::tDN ] = "tDN";
        GNames[N::tDP ] = "tDP";
        GNames[N::tSP8P] = "tSP8P";
        GNames[N::tSP4P] = "tSP4P";
        GNames[N::tTconvP] = "tTconvP";
        GNames[N::tTRegP1P] = "tTregP1P"; // raaah stupid capitals, need to reformat !!
        GNames[N::tTRegP2P] = "tTregP2P"; // idem
        GNames[N::tTregP] = "tTregP";
        GNames[N::tSP8RagN ] = "tSP8RagN";
        GNames[N::tSP4RagN ] = "tSP4RagN";
        GNames[N::tTconvRagN ] = "tTconvRagN";
        GNames[N::tTregP1RagN ] = "tTregP1RagN";
        GNames[N::tTregP2RagN ] = "tTregP2RagN";
        GNames[N::tTregRagN] = "tTregRagN";
        GNames[N::tSP8tot] = "tSP8tot";
        GNames[N::tSP4tot] = "tSP4tot";
        GNames[N::tTconvtot] = "tTconvtot";
        GNames[N::tTRegP1tot] = "tTRegP1tot";
        GNames[N::tTRegP2tot] = "tTRegP2tot";
        GNames[N::tTregtot] = "tTregtot";
        GNames[N::ttotal ] = "ttotal";
        GNames[N::pctDN ] = "pctDN";
        GNames[N::pctDP ] = "pctDP";
        GNames[N::pctSP8 ] = "pctSP8";
        GNames[N::pctSP4 ] = "pctSP4";
        GNames[N::pctTconvtot] = "pctTconvtot";
        GNames[N::pctTRegP1tot] = "pctTregP1tot";
        GNames[N::pctTRegP2tot] = "pctTregP2tot";
        GNames[N::pctTregtot] = "pctTregtot";
        GNames[N::pctTconvP] = "pctTconvP";
        GNames[N::pctTRegP1P] = "pctTregP1P";
        GNames[N::pctTRegP2P] = "pctTregP2P";
        GNames[N::pctTregP] = "pctTregP";
        GNames[N::pctSP8RagN ] = "pctSP8RagN";
        GNames[N::pctSP4RagN ] = "pctSP4RagN";
        GNames[N::pctTconvRagN ] = "pctTconvRagN";
        GNames[N::pctTRegP1RagN ] = "pctTregP1RagN";
        GNames[N::pctTRegP2RagN ] = "pctTregP2RagN";
        GNames[N::pctTregRagN] = "pctTregRagN";
        GNames[N::stotal ] = "stotal";
        GNames[N::sTconv ] = "sTconv";
        GNames[N::sTreg ] = "sTreg";
        GNames[N::sCD8 ] = "sCD8";
        GNames[N::sBcells] = "sBcells";
        GNames[N::sTconvRagN ] = "sTconvRagN";
        GNames[N::sTregRagN ] = "sTregRagN";
        GNames[N::sCD8RagN] = "sCD8RagN";
        GNames[N::pcsTconv ] = "pcsTconv";
        GNames[N::pcsTreg ] = "pcsTreg";
        GNames[N::pcsCD8 ] = "pcsCD8";
        GNames[N::pcsBcells] = "pcsBcells";
        GNames[N::pcsTconvRagN ] = "pcsTconvRagN";
        GNames[N::pcsTregRagN ] = "pcsTregRagN";
        GNames[N::pcsCD8RagN ] = "pcsCD8RagN";
        GNames[N::ProDN1Potritt ] = "ProDN1Potritt";
        GNames[N::ProDN2Potritt ] = "ProDN2Potritt";
        GNames[N::ProDN3Potritt ] = "ProDN3Potritt";
        GNames[N::ProDN4Potritt ] = "ProDN4Potritt";
        GNames[N::ProDN34Potritt] = "ProDN34Potritt";
            }
    if((id < 0) || (id >= (int) GNames.size())) {
          return string("Not Found");
    }
    else return GNames[id];
}


/*vector<string> getCodingNames(){
    CodingName(0); // to make sure it's loaded
    return codingNames;
}*/

vector<string> getGlobalNames(){
    GlobalName(0); // to make sure it's loaded
    return GNames;
}
