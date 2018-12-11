// ------- Automatically generated model -------- //
#ifndef modeleLatentTbet2_H
#define modeleLatentTbet2_H
#include "../../common.h"
#include "../../Framework/modele.h"
#include "../namesLMajor.h"




struct modeleMinimal : public Modele {
    modeleMinimal();
    enum{
        cDN_DP, cDP_SP4, cDP_SP8, cConv_P25, cConv_PFp3, cP25_Reg, cPFp3_Reg,
        dDN, dDP, dtTConv, dtTregs, dtTregP25, dtTregPFp3, dtCD8,



        , NbParameters};

    enum{tDN, tDP, tTRegP25, tTRegPFp3,

        tRNTConv, tRPTConv, tRNTreg, tRPTreg, tRPSP8, tRNSP8,                             tSP4, tSP8, tTreg, tTconv,                  // thymus
        lRNTconv, lRPTConv, lRNTreg, lRPTreg, lRPSP8, lRNSP8,  lRPDP, lRNDP,        lCD3, lSP4, lSP8, lTreg, lTconv, lRPB, lRNB, // lung
        sRNTConv, sRPTConv, sRNTreg, sRPTreg, sRPSP8, sRNSP8,                       sCD3, sSP4, sSP8, sTreg, sTconv, sRPB, sRNB, // Spleen
        mRNTconv, mRPTConv, mRNTreg, mRPTreg, mRPSP8, mRNSP8,                       mCD3, mSP4, mSP8, mTreg, mTconv, mRPB, mRNB,  // mLNs
        dRNTconv, dRPTConv, dRNTreg, dRPTreg, dRPSP8, dRNSP8,                       dCD3, dSP4, dSP8, dTreg, dTconv, dRPB, dRNB, // draining -> mediastinal LN

        NbVariables};


/* This model has  unknown parameters, +  */
struct modeleLeishmania : public Modele {
    modeleLeishmania();
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

    enum{Mac, Mi, Mia, Ma, Matot, P, D, NbVariables};
    //enum {IL2, IL4, IL6, IL12, IL17, IL21, IFNG, TGFB, TBET, GATA3, RORGT, FOXP3, IL2mRNA, IL4mRNA, IL17mRNA, IL21mRNA, IFNGmRNA, TGFBmRNA, TBETmRNA, GATA3mRNA, RORGTmRNA, FOXP3mRNA, TCR, antiIL4, antiIFNg, antiIL2, openIL2, openIL21, openFOXP3, openRORGT, openTBET, transl, secret, NBVAR};
    //enum {TCRPEAK, TCRCOEFF, KTCRGATA3, KTCRIL2, KTCRGATA3POS, KTCRTGFB, KTCRTBET, KTCRIFNG, KDIL2, KDIL4, KDIL12, KDIL17, KDIL21, KDIFNG, KDTGFB, KDTBET, KDGATA3, KDRORGT, KDFOXP3, KDIL2mRNA, KDIL4mRNA, KDIL17mRNA, KDIL21mRNA, KDIFNGmRNA, KDTGFBmRNA, KDTBETmRNA, KDGATA3mRNA, KDRORGTmRNA, KDFOXP3mRNA, PIL2, PIL4, PIL17, PIL21, PIFNG, PTGFB, PTBET, PGATA3, PRORGT, PFOXP3, CTGFBmRNA, CIL2mRNA, SIL2_TO_IL2mRNA, KIL2_TO_IL2mRNA, NIL2_TO_IL2mRNA, SIL4_TO_IL2mRNA, KIL4_TO_IL2mRNA, NIL4_TO_IL2mRNA,  CIL4mRNA, SGATA3_TO_IL4mRNA, KGATA3_TO_IL4mRNA, NGATA3_TO_IL4mRNA, CIL17mRNA, SRORGT_TO_IL17mRNA, KRORGT_TO_IL17mRNA, NRORGT_TO_IL17mRNA, CIL21mRNA, FIL6_TO_IL21mRNA, SRORGT_TO_IL21mRNA, KRORGT_TO_IL21mRNA, NRORGT_TO_IL21mRNA, CIFNGmRNA, FIL12_TO_IFNGmRNA, STBET_TO_IFNGmRNA, KTBET_TO_IFNGmRNA, NTBET_TO_IFNGmRNA, CTBETmRNA, FIL6_TO_TBETmRNA, /*CIL2_TBETmRNA, KIL2_TO_TBETmRNA, NIL2_TO_TBETmRNA, SIL2_TO_TBETmRNA, */ SIL12_TO_TBETmRNA, KIL12_TO_TBETmRNA, NIL12_TO_TBETmRNA, SIFNG_TO_TBETmRNA, KIFNG_TO_TBETmRNA, NIFNG_TO_TBETmRNA, SGATA3_TO_TBETmRNA, KGATA3_TO_TBETmRNA, NGATA3_TO_TBETmRNA, SRORGT_TO_TBETmRNA, KRORGT_TO_TBETmRNA, NRORGT_TO_TBETmRNA, SFOXP3_TO_TBETmRNA, KFOXP3_TO_TBETmRNA, NFOXP3_TO_TBETmRNA, CGATA3mRNA, FIL12_TO_GATA3mRNA, SIL2_TO_GATA3mRNA, KIL2_TO_GATA3mRNA, NIL2_TO_GATA3mRNA, SIL4_TO_GATA3mRNA, KIL4_TO_GATA3mRNA, NIL4_TO_GATA3mRNA, SIFNG_TO_GATA3mRNA, KIFNG_TO_GATA3mRNA, NIFNG_TO_GATA3mRNA, STBET_TO_GATA3mRNA, KTBET_TO_GATA3mRNA, NTBET_TO_GATA3mRNA, SGATA3_TO_GATA3mRNA, KGATA3_TO_GATA3mRNA, NGATA3_TO_GATA3mRNA, SRORGT_TO_GATA3mRNA, KRORGT_TO_GATA3mRNA, NRORGT_TO_GATA3mRNA, SFOXP3_TO_GATA3mRNA, KFOXP3_TO_GATA3mRNA, NFOXP3_TO_GATA3mRNA, CRORGTmRNA, FIL6_TO_RORGTmRNA, SIL21_TO_RORGTmRNA, KIL21_TO_RORGTmRNA, NIL21_TO_RORGTmRNA, STGFB_TO_RORGTmRNA, KTGFB_TO_RORGTmRNA, NTGFB_TO_RORGTmRNA, STBET_TO_RORGTmRNA, KTBET_TO_RORGTmRNA, NTBET_TO_RORGTmRNA, SGATA3_TO_RORGTmRNA, KGATA3_TO_RORGTmRNA, NGATA3_TO_RORGTmRNA, SFOXP3_TO_RORGTmRNA, KFOXP3_TO_RORGTmRNA, NFOXP3_TO_RORGTmRNA, CFOXP3mRNA, SIL2_TO_FOXP3mRNA, KIL2_TO_FOXP3mRNA, NIL2_TO_FOXP3mRNA, STGFB_TO_FOXP3mRNA, KTGFB_TO_FOXP3mRNA, NTGFB_TO_FOXP3mRNA, STBET_TO_FOXP3mRNA, KTBET_TO_FOXP3mRNA, NTBET_TO_FOXP3mRNA, SGATA3_TO_FOXP3mRNA, KGATA3_TO_FOXP3mRNA, NGATA3_TO_FOXP3mRNA, SRORGT_TO_FOXP3mRNA, KRORGT_TO_FOXP3mRNA, NRORGT_TO_FOXP3mRNA, IL2EQ, IL4EQ, IL12EQ, IL17EQ, IL21EQ, IFNGEQ, TGFBEQ, TBETEQ, GATA3EQ, RORGTEQ, FOXP3EQ, IL2mRNAEQ, IL4mRNAEQ, IL17mRNAEQ, IL21mRNAEQ, IFNGmRNAEQ, TGFBmRNAEQ, TBETmRNAEQ, GATA3mRNAEQ, RORGTmRNAEQ, FOXP3mRNAEQ, IL4INITTH2, IL2INITTREG,  FORCEIL2, FORCEIL21, FORCEFOXP3, FORCERORGT, FORCETBET, FORCETRANSL, FORCESECRET, KANTI_IL2, KANTI_IFNG, KANTI_IL4, NBPARAM};


    long long background; // for different models
    virtual void derivatives(const vector<double> &x, vector<double> &dxdt, const double t);
    void initialise(long long _background = Back::WT);
	void setBaseParameters();


    void action(string name, double parameter){
        if(!name.compare("wash")){
            if((parameter > 1.0) || (parameter < 0)) {cerr << "ERR: ModeleMinLatent::action(" << name << ", " << parameter << "), wrong parameter value\n"; return;}
            // val[IL2] =    (1 - parameter) * val[IL2]; // example of how the hell it works
            return;
        }
    }
};

struct model1 : public modeleLeishmania {
   model1() : modeleLeishmania(){ name = string("model 1"); }
   //void modeleLeishmania::derivatives(const vector<double> &x, vector<double> &dxdt, const double t);
   void derivatives(const vector<double> &x, vector<double> &dxdt, const double t);
};

struct model2 : public modeleLeishmania {
   model2() : modeleLeishmania(){ name = string("model 2"); }
   void derivatives(const vector<double> &x, vector<double> &dxdt, const double t);
};
struct model3 : public modeleLeishmania {
   model3() : modeleLeishmania(){ name = string("model 3"); }
   void derivatives(const vector<double> &x, vector<double> &dxdt, const double t);
};
struct model4 : public modeleLeishmania {
   model4() : modeleLeishmania(){ name = string("model 4"); }
   void derivatives(const vector<double> &x, vector<double> &dxdt, const double t);
};
struct model5 : public modeleLeishmania {
   model5() : modeleLeishmania(){  name = string("model 5"); }
   void derivatives(const vector<double> &x, vector<double> &dxdt, const double t);
};
struct model6 : public modeleLeishmania {
   model6() : modeleLeishmania(){  name = string("model 6"); }
   void derivatives(const vector<double> &x, vector<double> &dxdt, const double t);
};
#endif

