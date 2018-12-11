#ifndef NAMES_H
#define NAMES_H

#include <vector>
#include <string>
using namespace std;

enum {WT_recir, NB_EXP_RECIR};

namespace N{
     enum{NoName,
          ttotal, tDN, tDN1, tDN2, tDN3, tDN4, tDP, tSP8, tSP4, tTconv, tTRegP25, tTRegPFp3, tTreg,
          tSP8RagN, tSP4RagN, tTconvRagN, tTregP1RagN, tTregP2RagN, tTregRagN,
          pctDN, pctDP, pctSP8, pctSP4, pctTconv, pctTRegP1, pctTRegP2, pctTreg,
          pctSP8RagN, pctSP4RagN, pctTconvRagN, pctTRegP1RagN, pctTRegP2RagN, pctTregRagN,
          stotal, sTconv, sTreg, sCD8, sBcells,
          sTconvRagN, sTregRagN, sCD8RagN,
          pcsTconv, pcsTreg, pcsCD8, pcsBcells,
          pcsTconvRagN, pcsTregRagN, pcsCD8RagN, ProDN1Potritt, ProDN2Potritt, ProDN3Potritt, ProDN4Potritt,  ProDN1PotrittNew, ProDN2PotrittNew, ProDN34Potritt,
          NB_GLOB_VARS};
}

namespace Back {
    enum : long long {WT= 1, B_ReducedInflow = 2, B_MoreDeath = 4, B_MoreOutputThymus = 8, B_FasterDifferentiation = 16, B_SpaceDependentOutput = 32, B_DivisionReduced = 64, B_AllCombined = 127, B_LogisticTotalProlif = 256, B_InitThiault = 512, B_StartSteadyState = 1024, B_BRDU = 2048 };
}

/*long long getBackgroundNr(int i = -1); // if -1, returns the number of backgrounds
string getBackgroundName(long long background);
void testBackgroundSystem();*/

string GlobalName(int id);
//string CodingName(int id);
//string CodingNameExp(int id);
//vector<string> getCodingNames();
vector<string> getGlobalNames();


#endif // NAMES_H
