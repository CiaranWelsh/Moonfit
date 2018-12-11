
#ifndef modeleThomasVasin_h
#define modeleThomasVasin_h

#include "../../common.h"
#include "../../Framework/modele.h"
#include "../namesThymus.h"

struct ModeleTVaslin2007 : public Modele {
    ModeleTVaslin2007();
    enum {flu,

          DNtot,
          eDPtot,
          DPtot,
          SP4tot,
          SP8tot,

          divDNg0, divDNg1, divDNg2, divDNg3, divDNg4, divDNg5, divDNg6,
          eDPg0, eDPg1, eDPg2, eDPg3, eDPg4, eDPg5, eDPg6,
          lDP,
          divSP4g0, divSP4g1, divSP4g2,
          restSP4,
          divSP8g0, divSP8g1, divSP8g2,
          restSP8,
// the tot were here, just reorganized
          flowDNtoDP,
          floweDPtolDP,
          flowDPtoSP4,
          flowDPtoSP8,
          flowDNtoDead,
          floweDPtoDead,
          flowlDPtoDead,
          flowSP4toDead,
          flowSP8toDead,
          //TregP25, TregPFP3, Treg,
          NBVAR};
    enum {
        flu_peak,
        flu_std,
        infloDN,
        NdivDN,
        pDN, dDN,

        NdivDP,
        peDP, deDP,
        prestDP, drestDP,
        diffDPtoSP4,
        diffDPtoSP8,

        pSP4, dSP4,
        pcConvLastGenSP4,
        NdivSP4,

        pSP8, dSP8,
        pcConvLastGenSP8,
        NdivSP8,

        hypInflowCoeffETP,
        hypDeathCoeffDN,

        hypDeathCoeffDP,
        hypDeathCoeffTconv,
        hypDeathCoeffSP8,

        //MoreOutputThymus,
        hypOutputCoeffOutDP,
        hypOutputCoeffOutTconv,
        hypOutputCoeffOutSP8,

        //FasterDifferentiation,
        hypFasterCoeffDNtoDP,
        hypFasterCoeffTconv,
        hypFasterCoeffSP8,

        //SpaceDependentOutput
        hypSpaceOutputCoeff,

        //ImpactProlifRates
        hypLessDivDN,
        hypLessDivDP,
        hypLessDivTconv,
        hypLessDivCD8,

        logisticThymus,
        logisticStrength,
        NBPARAM};

    long long background;
	void derivatives(const vector<double> &x, vector<double> &dxdt, const double t);
    void initialise(long long _background = Back::WT);
	void setBaseParameters();
    void updateDerivedVariables();
    };

#endif
