// ------- Automatically generated model -------- //
#include "../../common.h"

#include "modele1ThymusOnly.h"

/*
struct modele1ThymusOnly : public Modele {
    modele1ThymusOnly();
    enum{
        tDN, tDP, tTconv, tTRegP25, tTRegPFp3, tDPTreg, tSP8, tSP4, NbParameters};
    enum{
        fETP_tDN, ptDN, ftDN_tDP,
        ptDP, ftDP_tTConv, ftDP_tTregP25, ftDP_tTregFP3, ftDP_tSP8, out_tDP,
        ptTregP25, ftTregP25_tDPTreg, out_tTregP25,
        ptTregFP3,  ftTregFP3_tDPTreg, out_tTregFP3,
        ptDPTregs, out_tDPTregs, in_tDPTregs,
        ptTconv, out_tTconv, in_tTconv,
        ptSP8, out_SP8, in_SP8,

*/

/* Explicit solutions :

syms DN(t) DP(t) SP4(t) Singer(t) Treg(t) SP8(t) pC1 pC2 pC3 pC4 pC5 pC6 f1 f2 f3 f4 f5 DNinit DPinit SP4init Singerinit Treginit SP8init infloDN infloSinger infloTreg infloSP8 infloSP4
eqns = [diff(DN,t)==(pC1 - f1)*DN + infloDN, diff(DP,t)==(pC2 - f2 -f3 -f5)*DP+f1*DN, diff(SP4,t) == (pC3-f4)*SP4 + f2*DP + infloSP4,     diff(Singer,t) == (pC4-f4)*Singer + f3*DP + infloSinger,     diff(Treg,t) == (pC5)*Treg + f4*Singer + infloTreg,    diff(SP8,t) == (pC6)*SP8+f5*DP + infloSP8 ];
cond = [DN(0) == DNinit, DP(0) == DPinit, SP4(0)==SP4init, Singer(0) == Singerinit, Treg(0)== Treginit, SP8(0) == SP8init] ;
sol = dsolve(eqns, cond)
solDN(t) = sol.DN
solDP(t) = sol.DP
solSP4(t) = sol.SP4
solSinger(t) = sol.Singer
solTreg(t) = sol.Treg
solSP8(t) = sol.SP8


=> Gives:
solDN(t) =

(exp(-t*(f1 - pC1))*((f1*f5*infloDN*exp(f1*t - pC1*t))/((f1 - pC1)*(f1*f2 + f1*f3 + f1*f5 + 2*f1*pC1 - f1*pC2 - f2*pC1 - f3*pC1 - f5*pC1 - f1*pC6 + f2*pC6 + f3*pC6 + f5*pC6 + pC1*pC2 + pC1*pC6 - pC2*pC6 - f1^2 - pC1^2)) - (f1*f5*(infloDN - DNinit*f1 + DNinit*pC1))/((f1 - pC1)*(f1 - pC1 + pC6)*(f2 - f1 + f3 + f5 + pC1 - pC2)))*(f1 - pC1 + pC6)*(f2 - f1 + f3 + f5 + pC1 - pC2))/(f1*f5)


solDP(t) =

(exp(-t*(f2 + f3 + f5 - pC2))*((f5*(f1*infloDN + DPinit*f2^2 + DPinit*f3^2 + DPinit*f5^2 + DPinit*pC2^2 - DNinit*f1*f2 - DNinit*f1*f3 - DNinit*f1*f5 - DPinit*f1*f2 - DPinit*f1*f3 + 2*DPinit*f2*f3 - DPinit*f1*f5 + 2*DPinit*f2*f5 + 2*DPinit*f3*f5 + DNinit*f1*pC2 + DPinit*f1*pC2 + DPinit*f2*pC1 - 2*DPinit*f2*pC2 + DPinit*f3*pC1 - 2*DPinit*f3*pC2 + DPinit*f5*pC1 - 2*DPinit*f5*pC2 - DPinit*pC1*pC2))/((f2 + f3 + f5 - pC2)*(f2 + f3 + f5 - pC2 + pC6)*(f2 - f1 + f3 + f5 + pC1 - pC2)) - (f1*f5*infloDN*exp(f2*t + f3*t + f5*t - pC2*t))/((f2 + f3 + f5 - pC2)*(2*f2*f3 - f1*f3 - f1*f2 - f1*f5 + 2*f2*f5 + 2*f3*f5 + f1*pC2 + f2*pC1 - 2*f2*pC2 + f3*pC1 - 2*f3*pC2 + f5*pC1 - f1*pC6 - 2*f5*pC2 + f2*pC6 + f3*pC6 + f5*pC6 - pC1*pC2 + pC1*pC6 - pC2*pC6 + f2^2 + f3^2 + f5^2 + pC2^2)))*(f2 + f3 + f5 - pC2 + pC6))/f5 + (exp(-t*(f1 - pC1))*((f1*f5*infloDN*exp(f1*t - pC1*t))/((f1 - pC1)*(f1*f2 + f1*f3 + f1*f5 + 2*f1*pC1 - f1*pC2 - f2*pC1 - f3*pC1 - f5*pC1 - f1*pC6 + f2*pC6 + f3*pC6 + f5*pC6 + pC1*pC2 + pC1*pC6 -\\\r\n pC2*pC6 - f1^2 - pC1^2)) - (f1*f5*(infloDN - DNinit*f1 + DNinit*pC1))/((f1 - pC1)*(f1 - pC1 + pC6)*(f2 - f1 + f3 + f5 + pC1 - pC2)))*(f1 - pC1 + pC6))/f5


solSP4(t) =

exp(-t*(f4 - pC3))*((exp(f4*t - pC3*t)*(f4^2*infloSP4 + infloSP4*pC3^2 + f1*f2*infloDN + f1*f2*infloSP4 + f1*f3*infloSP4 - f1*f4*infloSP4 + f1*f5*infloSP4 - f2*f4*infloSP4 - f3*f4*infloSP4 - f4*f5*infloSP4 - f1*infloSP4*pC2 - f2*infloSP4*pC1 + f1*infloSP4*pC3 - f3*infloSP4*pC1 + f2*infloSP4*pC3 + f4*infloSP4*pC1 + f3*infloSP4*pC3 + f4*infloSP4*pC2 - f5*infloSP4*pC1 - 2*f4*infloSP4*pC3 + f5*infloSP4*pC3 + infloSP4*pC1*pC2 - infloSP4*pC1*pC3 - infloSP4*pC2*pC3))/((f4 - pC3)*(f1*f2 + f1*f3 - f1*f4 + f1*f5 - f2*f4 - f3*f4 - f4*f5 - f1*pC2 - f2*pC1 + f1*pC3 - f3*pC1 + f2*pC3 + f4*pC1 + f3*pC3 + f4*pC2 - f5*pC1 - 2*f4*pC3 + f5*pC3 + pC1*pC2 - pC1*pC3 - pC2*pC3 + f4^2 + pC3^2)) - (SP4init*pC3^3 - SP4init*f4^3 + f4^2*infloSP4 + infloSP4*pC3^2 + f1*f2*infloDN + f1*f2*infloSP4 + f1*f3*infloSP4 - f1*f4*infloSP4 + f1*f5*infloSP4 - f2*f4*infloSP4 - f3*f4*infloSP4 - f4*f5*infloSP4 - f1*infloSP4*pC2 - f2*infloSP4*pC1 + f1*infloSP4*pC3 - f3*infloSP4*pC1 + f2*infloSP4*pC3 + f4*infloSP4*pC1 + f3*infloS\\\r\nP4*pC3 + f4*infloSP4*pC2 - f5*infloSP4*pC1 - 2*f4*infloSP4*pC3 + f5*infloSP4*pC3 + infloSP4*pC1*pC2 - infloSP4*pC1*pC3 - infloSP4*pC2*pC3 + DPinit*f2*f4^2 + DPinit*f2*pC3^2 + SP4init*f1*f4^2 + SP4init*f2*f4^2 + SP4init*f3*f4^2 + SP4init*f4^2*f5 + SP4init*f1*pC3^2 + SP4init*f2*pC3^2 - SP4init*f4^2*pC1 + SP4init*f3*pC3^2 - SP4init*f4^2*pC2 - 3*SP4init*f4*pC3^2 + 3*SP4init*f4^2*pC3 + SP4init*f5*pC3^2 - SP4init*pC1*pC3^2 - SP4init*pC2*pC3^2 + SP4init*pC1*pC2*pC3 - DNinit*f1*f2*f4 - DPinit*f1*f2*f4 + DNinit*f1*f2*pC3 + DPinit*f1*f2*pC3 + DPinit*f2*f4*pC1 - 2*DPinit*f2*f4*pC3 - SP4init*f1*f2*f4 - SP4init*f1*f3*f4 - SP4init*f1*f4*f5 - DPinit*f2*pC1*pC3 + SP4init*f1*f2*pC3 + SP4init*f1*f3*pC3 + SP4init*f1*f4*pC2 + SP4init*f2*f4*pC1 - 2*SP4init*f1*f4*pC3 + SP4init*f3*f4*pC1 + SP4init*f1*f5*pC3 - 2*SP4init*f2*f4*pC3 - 2*SP4init*f3*f4*pC3 + SP4init*f4*f5*pC1 - 2*SP4init*f4*f5*pC3 - SP4init*f1*pC2*pC3 - SP4init*f2*pC1*pC3 - SP4init*f3*pC1*pC3 - SP4init*f4*pC1*pC2 + 2*SP4init*f4*pC1*pC3 + 2*SP4ini\\\r\nt*f4*pC2*pC3 - SP4init*f5*pC1*pC3)/((f4 - pC3)*(f1 - f4 - pC1 + pC3)*(f2 + f3 - f4 + f5 - pC2 + pC3))) - (f2*exp(-t*(f1 - pC1))*((f1*f5*infloDN*exp(f1*t - pC1*t))/((f1 - pC1)*(f1*f2 + f1*f3 + f1*f5 + 2*f1*pC1 - f1*pC2 - f2*pC1 - f3*pC1 - f5*pC1 - f1*pC6 + f2*pC6 + f3*pC6 + f5*pC6 + pC1*pC2 + pC1*pC6 - pC2*pC6 - f1^2 - pC1^2)) - (f1*f5*(infloDN - DNinit*f1 + DNinit*pC1))/((f1 - pC1)*(f1 - pC1 + pC6)*(f2 - f1 + f3 + f5 + pC1 - pC2)))*(f1 - pC1 + pC6))/(f5*(f1 - f4 - pC1 + pC3)) - (f2*exp(-t*(f2 + f3 + f5 - pC2))*((f5*(f1*infloDN + DPinit*f2^2 + DPinit*f3^2 + DPinit*f5^2 + DPinit*pC2^2 - DNinit*f1*f2 - DNinit*f1*f3 - DNinit*f1*f5 - DPinit*f1*f2 - DPinit*f1*f3 + 2*DPinit*f2*f3 - DPinit*f1*f5 + 2*DPinit*f2*f5 + 2*DPinit*f3*f5 + DNinit*f1*pC2 + DPinit*f1*pC2 + DPinit*f2*pC1 - 2*DPinit*f2*pC2 + DPinit*f3*pC1 - 2*DPinit*f3*pC2 + DPinit*f5*pC1 - 2*DPinit*f5*pC2 - DPinit*pC1*pC2))/((f2 + f3 + f5 - pC2)*(f2 + f3 + f5 - pC2 + pC6)*(f2 - f1 + f3 + f5 + pC1 - pC2)) - (f1*f5*infloDN*exp(f2*t + f3*t \\\r\n+ f5*t - pC2*t))/((f2 + f3 + f5 - pC2)*(2*f2*f3 - f1*f3 - f1*f2 - f1*f5 + 2*f2*f5 + 2*f3*f5 + f1*pC2 + f2*pC1 - 2*f2*pC2 + f3*pC1 - 2*f3*pC2 + f5*pC1 - f1*pC6 - 2*f5*pC2 + f2*pC6 + f3*pC6 + f5*pC6 - pC1*pC2 + pC1*pC6 - pC2*pC6 + f2^2 + f3^2 + f5^2 + pC2^2)))*(f2 + f3 + f5 - pC2 + pC6))/(f5*(f2 + f3 - f4 + f5 - pC2 + pC3))


solSinger(t) =

- (exp(-t*(f4 - pC4))*((f4*exp(f4*t - pC4*t)*(infloSinger*pC4^2 + f1*f3*infloDN + f1*f2*infloSinger + f1*f3*infloSinger + f1*f5*infloSinger - f1*infloSinger*pC2 - f2*infloSinger*pC1 - f3*infloSinger*pC1 + f1*infloSinger*pC4 + f2*infloSinger*pC4 - f5*infloSinger*pC1 + f3*infloSinger*pC4 + f5*infloSinger*pC4 + infloSinger*pC1*pC2 - infloSinger*pC1*pC4 - infloSinger*pC2*pC4) - f4^2*exp(f4*t - pC4*t)*(f1*infloSinger + f2*infloSinger + f3*infloSinger + f5*infloSinger - infloSinger*pC1 - infloSinger*pC2 + 2*infloSinger*pC4) + f4^3*infloSinger*exp(f4*t - pC4*t))/((f4 - pC4)*(f1*f4^2 + f2*f4^2 + f3*f4^2 + f4^2*f5 + f1*pC4^2 - f4^2*pC1 + f2*pC4^2 - f4^2*pC2 + f3*pC4^2 - 3*f4*pC4^2 + 3*f4^2*pC4 + f5*pC4^2 - f4^2*pC5 - pC1*pC4^2 - pC2*pC4^2 - pC4^2*pC5 - f4^3 + pC4^3 - f1*f2*f4 - f1*f3*f4 - f1*f4*f5 + f1*f2*pC4 + f1*f4*pC2 + f2*f4*pC1 - f1*f2*pC5 + f1*f3*pC4 + f3*f4*pC1 - f1*f3*pC5 - 2*f1*f4*pC4 + f1*f4*pC5 + f1*f5*pC4 - 2*f2*f4*pC4 + f4*f5*pC1 - f1*f5*pC5 + f2*f4*pC5 - 2*f3*f4*pC4 + f3*f4*pC5 -\\\r\n 2*f4*f5*pC4 + f4*f5*pC5 - f1*pC2*pC4 - f2*pC1*pC4 - f4*pC1*pC2 + f1*pC2*pC5 + f2*pC1*pC5 - f3*pC1*pC4 + f3*pC1*pC5 + 2*f4*pC1*pC4 - f1*pC4*pC5 - f4*pC1*pC5 + 2*f4*pC2*pC4 - f5*pC1*pC4 - f2*pC4*pC5 - f4*pC2*pC5 + f5*pC1*pC5 - f3*pC4*pC5 + 2*f4*pC4*pC5 - f5*pC4*pC5 + pC1*pC2*pC4 - pC1*pC2*pC5 + pC1*pC4*pC5 + pC2*pC4*pC5)) + (f4*(Singerinit*pC4^3 - Singerinit*f4^3 + f4^2*infloSinger + infloSinger*pC4^2 + f1*f3*infloDN + f1*f2*infloSinger + f1*f3*infloSinger - f1*f4*infloSinger + f1*f5*infloSinger - f2*f4*infloSinger - f3*f4*infloSinger - f4*f5*infloSinger - f1*infloSinger*pC2 - f2*infloSinger*pC1 - f3*infloSinger*pC1 + f1*infloSinger*pC4 + f4*infloSinger*pC1 + f2*infloSinger*pC4 + f4*infloSinger*pC2 - f5*infloSinger*pC1 + f3*infloSinger*pC4 - 2*f4*infloSinger*pC4 + f5*infloSinger*pC4 + infloSinger*pC1*pC2 - infloSinger*pC1*pC4 - infloSinger*pC2*pC4 + DPinit*f3*f4^2 + DPinit*f3*pC4^2 + Singerinit*f1*f4^2 + Singerinit*f2*f4^2 + Singerinit*f3*f4^2 + Singerinit*f4^2*f5 + Singerinit*f1*pC4^2\\\r\n - Singerinit*f4^2*pC1 + Singerinit*f2*pC4^2 - Singerinit*f4^2*pC2 + Singerinit*f3*pC4^2 - 3*Singerinit*f4*pC4^2 + 3*Singerinit*f4^2*pC4 + Singerinit*f5*pC4^2 - Singerinit*pC1*pC4^2 - Singerinit*pC2*pC4^2 + Singerinit*pC1*pC2*pC4 - DNinit*f1*f3*f4 - DPinit*f1*f3*f4 + DNinit*f1*f3*pC4 + DPinit*f1*f3*pC4 + DPinit*f3*f4*pC1 - 2*DPinit*f3*f4*pC4 - Singerinit*f1*f2*f4 - Singerinit*f1*f3*f4 - Singerinit*f1*f4*f5 - DPinit*f3*pC1*pC4 + Singerinit*f1*f2*pC4 + Singerinit*f1*f4*pC2 + Singerinit*f2*f4*pC1 + Singerinit*f1*f3*pC4 + Singerinit*f3*f4*pC1 - 2*Singerinit*f1*f4*pC4 + Singerinit*f1*f5*pC4 - 2*Singerinit*f2*f4*pC4 + Singerinit*f4*f5*pC1 - 2*Singerinit*f3*f4*pC4 - 2*Singerinit*f4*f5*pC4 - Singerinit*f1*pC2*pC4 - Singerinit*f2*pC1*pC4 - Singerinit*f4*pC1*pC2 - Singerinit*f3*pC1*pC4 + 2*Singerinit*f4*pC1*pC4 + 2*Singerinit*f4*pC2*pC4 - Singerinit*f5*pC1*pC4))/((f4 - pC4)*(f4 - pC4 + pC5)*(f1 - f4 - pC1 + pC4)*(f2 + f3 - f4 + f5 - pC2 + pC4)))*(f4 - pC4 + pC5))/f4 - (f3*exp(-t*(f1 - pC1))*((f\\\r\n1*f5*infloDN*exp(f1*t - pC1*t))/((f1 - pC1)*(f1*f2 + f1*f3 + f1*f5 + 2*f1*pC1 - f1*pC2 - f2*pC1 - f3*pC1 - f5*pC1 - f1*pC6 + f2*pC6 + f3*pC6 + f5*pC6 + pC1*pC2 + pC1*pC6 - pC2*pC6 - f1^2 - pC1^2)) - (f1*f5*(infloDN - DNinit*f1 + DNinit*pC1))/((f1 - pC1)*(f1 - pC1 + pC6)*(f2 - f1 + f3 + f5 + pC1 - pC2)))*(f1 - pC1 + pC6))/(f5*(f1 - f4 - pC1 + pC4)) - (f3*exp(-t*(f2 + f3 + f5 - pC2))*((f5*(f1*infloDN + DPinit*f2^2 + DPinit*f3^2 + DPinit*f5^2 + DPinit*pC2^2 - DNinit*f1*f2 - DNinit*f1*f3 - DNinit*f1*f5 - DPinit*f1*f2 - DPinit*f1*f3 + 2*DPinit*f2*f3 - DPinit*f1*f5 + 2*DPinit*f2*f5 + 2*DPinit*f3*f5 + DNinit*f1*pC2 + DPinit*f1*pC2 + DPinit*f2*pC1 - 2*DPinit*f2*pC2 + DPinit*f3*pC1 - 2*DPinit*f3*pC2 + DPinit*f5*pC1 - 2*DPinit*f5*pC2 - DPinit*pC1*pC2))/((f2 + f3 + f5 - pC2)*(f2 + f3 + f5 - pC2 + pC6)*(f2 - f1 + f3 + f5 + pC1 - pC2)) - (f1*f5*infloDN*exp(f2*t + f3*t + f5*t - pC2*t))/((f2 + f3 + f5 - pC2)*(2*f2*f3 - f1*f3 - f1*f2 - f1*f5 + 2*f2*f5 + 2*f3*f5 + f1*pC2 + f2*pC1 - 2*f2*pC2 + f3*pC1 -\\\r\n 2*f3*pC2 + f5*pC1 - f1*pC6 - 2*f5*pC2 + f2*pC6 + f3*pC6 + f5*pC6 - pC1*pC2 + pC1*pC6 - pC2*pC6 + f2^2 + f3^2 + f5^2 + pC2^2)))*(f2 + f3 + f5 - pC2 + pC6))/(f5*(f2 + f3 - f4 + f5 - pC2 + pC4))


solTreg(t) =

exp(-t*(f4 - pC4))*((f4*exp(f4*t - pC4*t)*(infloSinger*pC4^2 + f1*f3*infloDN + f1*f2*infloSinger + f1*f3*infloSinger + f1*f5*infloSinger - f1*infloSinger*pC2 - f2*infloSinger*pC1 - f3*infloSinger*pC1 + f1*infloSinger*pC4 + f2*infloSinger*pC4 - f5*infloSinger*pC1 + f3*infloSinger*pC4 + f5*infloSinger*pC4 + infloSinger*pC1*pC2 - infloSinger*pC1*pC4 - infloSinger*pC2*pC4) - f4^2*exp(f4*t - pC4*t)*(f1*infloSinger + f2*infloSinger + f3*infloSinger + f5*infloSinger - infloSinger*pC1 - infloSinger*pC2 + 2*infloSinger*pC4) + f4^3*infloSinger*exp(f4*t - pC4*t))/((f4 - pC4)*(f1*f4^2 + f2*f4^2 + f3*f4^2 + f4^2*f5 + f1*pC4^2 - f4^2*pC1 + f2*pC4^2 - f4^2*pC2 + f3*pC4^2 - 3*f4*pC4^2 + 3*f4^2*pC4 + f5*pC4^2 - f4^2*pC5 - pC1*pC4^2 - pC2*pC4^2 - pC4^2*pC5 - f4^3 + pC4^3 - f1*f2*f4 - f1*f3*f4 - f1*f4*f5 + f1*f2*pC4 + f1*f4*pC2 + f2*f4*pC1 - f1*f2*pC5 + f1*f3*pC4 + f3*f4*pC1 - f1*f3*pC5 - 2*f1*f4*pC4 + f1*f4*pC5 + f1*f5*pC4 - 2*f2*f4*pC4 + f4*f5*pC1 - f1*f5*pC5 + f2*f4*pC5 - 2*f3*f4*pC4 + f3*f4*pC5 - 2*\\\r\nf4*f5*pC4 + f4*f5*pC5 - f1*pC2*pC4 - f2*pC1*pC4 - f4*pC1*pC2 + f1*pC2*pC5 + f2*pC1*pC5 - f3*pC1*pC4 + f3*pC1*pC5 + 2*f4*pC1*pC4 - f1*pC4*pC5 - f4*pC1*pC5 + 2*f4*pC2*pC4 - f5*pC1*pC4 - f2*pC4*pC5 - f4*pC2*pC5 + f5*pC1*pC5 - f3*pC4*pC5 + 2*f4*pC4*pC5 - f5*pC4*pC5 + pC1*pC2*pC4 - pC1*pC2*pC5 + pC1*pC4*pC5 + pC2*pC4*pC5)) + (f4*(Singerinit*pC4^3 - Singerinit*f4^3 + f4^2*infloSinger + infloSinger*pC4^2 + f1*f3*infloDN + f1*f2*infloSinger + f1*f3*infloSinger - f1*f4*infloSinger + f1*f5*infloSinger - f2*f4*infloSinger - f3*f4*infloSinger - f4*f5*infloSinger - f1*infloSinger*pC2 - f2*infloSinger*pC1 - f3*infloSinger*pC1 + f1*infloSinger*pC4 + f4*infloSinger*pC1 + f2*infloSinger*pC4 + f4*infloSinger*pC2 - f5*infloSinger*pC1 + f3*infloSinger*pC4 - 2*f4*infloSinger*pC4 + f5*infloSinger*pC4 + infloSinger*pC1*pC2 - infloSinger*pC1*pC4 - infloSinger*pC2*pC4 + DPinit*f3*f4^2 + DPinit*f3*pC4^2 + Singerinit*f1*f4^2 + Singerinit*f2*f4^2 + Singerinit*f3*f4^2 + Singerinit*f4^2*f5 + Singerinit*f1*pC4^2 - \\\r\nSingerinit*f4^2*pC1 + Singerinit*f2*pC4^2 - Singerinit*f4^2*pC2 + Singerinit*f3*pC4^2 - 3*Singerinit*f4*pC4^2 + 3*Singerinit*f4^2*pC4 + Singerinit*f5*pC4^2 - Singerinit*pC1*pC4^2 - Singerinit*pC2*pC4^2 + Singerinit*pC1*pC2*pC4 - DNinit*f1*f3*f4 - DPinit*f1*f3*f4 + DNinit*f1*f3*pC4 + DPinit*f1*f3*pC4 + DPinit*f3*f4*pC1 - 2*DPinit*f3*f4*pC4 - Singerinit*f1*f2*f4 - Singerinit*f1*f3*f4 - Singerinit*f1*f4*f5 - DPinit*f3*pC1*pC4 + Singerinit*f1*f2*pC4 + Singerinit*f1*f4*pC2 + Singerinit*f2*f4*pC1 + Singerinit*f1*f3*pC4 + Singerinit*f3*f4*pC1 - 2*Singerinit*f1*f4*pC4 + Singerinit*f1*f5*pC4 - 2*Singerinit*f2*f4*pC4 + Singerinit*f4*f5*pC1 - 2*Singerinit*f3*f4*pC4 - 2*Singerinit*f4*f5*pC4 - Singerinit*f1*pC2*pC4 - Singerinit*f2*pC1*pC4 - Singerinit*f4*pC1*pC2 - Singerinit*f3*pC1*pC4 + 2*Singerinit*f4*pC1*pC4 + 2*Singerinit*f4*pC2*pC4 - Singerinit*f5*pC1*pC4))/((f4 - pC4)*(f4 - pC4 + pC5)*(f1 - f4 - pC1 + pC4)*(f2 + f3 - f4 + f5 - pC2 + pC4))) - exp(pC5*t)*((exp(-pC5*t)*(infloTreg*pC5^3 - infloT\\\r\nreg*pC1*pC5^2 - infloTreg*pC2*pC5^2 - infloTreg*pC4*pC5^2 + f1*infloTreg*pC5^2 + f2*infloTreg*pC5^2 + f3*infloTreg*pC5^2 + f4*infloTreg*pC5^2 + f5*infloTreg*pC5^2 + f4*infloSinger*pC5^2 - f1*f2*infloTreg*pC4 - f1*f4*infloTreg*pC2 - f2*f4*infloTreg*pC1 + f1*f2*infloTreg*pC5 - f1*f3*infloTreg*pC4 - f3*f4*infloTreg*pC1 + f1*f3*infloTreg*pC5 + f1*f4*infloTreg*pC5 - f1*f5*infloTreg*pC4 - f4*f5*infloTreg*pC1 + f1*f5*infloTreg*pC5 + f2*f4*infloTreg*pC5 + f3*f4*infloTreg*pC5 + f4*f5*infloTreg*pC5 - f1*f4*infloSinger*pC2 - f2*f4*infloSinger*pC1 - f3*f4*infloSinger*pC1 + f1*f4*infloSinger*pC5 - f4*f5*infloSinger*pC1 + f2*f4*infloSinger*pC5 + f3*f4*infloSinger*pC5 + f4*f5*infloSinger*pC5 + f1*infloTreg*pC2*pC4 + f2*infloTreg*pC1*pC4 + f4*infloTreg*pC1*pC2 - f1*infloTreg*pC2*pC5 - f2*infloTreg*pC1*pC5 + f3*infloTreg*pC1*pC4 - f3*infloTreg*pC1*pC5 - f1*infloTreg*pC4*pC5 - f4*infloTreg*pC1*pC5 + f5*infloTreg*pC1*pC4 - f2*infloTreg*pC4*pC5 - f4*infloTreg*pC2*pC5 - f5*infloTreg*pC1*pC5 - f3*infloTreg\\\r\n*pC4*pC5 - f5*infloTreg*pC4*pC5 + f4*infloSinger*pC1*pC2 - f4*infloSinger*pC1*pC5 - f4*infloSinger*pC2*pC5 - infloTreg*pC1*pC2*pC4 + infloTreg*pC1*pC2*pC5 + infloTreg*pC1*pC4*pC5 + infloTreg*pC2*pC4*pC5 + f1*f3*f4*infloDN + f1*f2*f4*infloTreg + f1*f3*f4*infloTreg + f1*f4*f5*infloTreg + f1*f2*f4*infloSinger + f1*f3*f4*infloSinger + f1*f4*f5*infloSinger))/(pC5*(f1*pC5^2 + f2*pC5^2 + f3*pC5^2 + f4*pC5^2 + f5*pC5^2 - pC1*pC5^2 - pC2*pC5^2 - pC4*pC5^2 + pC5^3 + f1*f2*f4 + f1*f3*f4 + f1*f4*f5 - f1*f2*pC4 - f1*f4*pC2 - f2*f4*pC1 + f1*f2*pC5 - f1*f3*pC4 - f3*f4*pC1 + f1*f3*pC5 + f1*f4*pC5 - f1*f5*pC4 - f4*f5*pC1 + f1*f5*pC5 + f2*f4*pC5 + f3*f4*pC5 + f4*f5*pC5 + f1*pC2*pC4 + f2*pC1*pC4 + f4*pC1*pC2 - f1*pC2*pC5 - f2*pC1*pC5 + f3*pC1*pC4 - f3*pC1*pC5 - f1*pC4*pC5 - f4*pC1*pC5 + f5*pC1*pC4 - f2*pC4*pC5 - f4*pC2*pC5 - f5*pC1*pC5 - f3*pC4*pC5 - f5*pC4*pC5 - pC1*pC2*pC4 + pC1*pC2*pC5 + pC1*pC4*pC5 + pC2*pC4*pC5)) - (Treginit*pC5^4 + infloTreg*pC5^3 - infloTreg*pC1*pC5^2 - infloTreg*pC2*pC5^2 - infl\\\r\noTreg*pC4*pC5^2 + Singerinit*f4*pC5^3 + Treginit*f1*pC5^3 + Treginit*f2*pC5^3 + Treginit*f3*pC5^3 + Treginit*f4*pC5^3 + Treginit*f5*pC5^3 - Treginit*pC1*pC5^3 - Treginit*pC2*pC5^3 - Treginit*pC4*pC5^3 + f1*infloTreg*pC5^2 + f2*infloTreg*pC5^2 + f3*infloTreg*pC5^2 + f4*infloTreg*pC5^2 + f5*infloTreg*pC5^2 + f4*infloSinger*pC5^2 - f1*f2*infloTreg*pC4 - f1*f4*infloTreg*pC2 - f2*f4*infloTreg*pC1 + f1*f2*infloTreg*pC5 - f1*f3*infloTreg*pC4 - f3*f4*infloTreg*pC1 + f1*f3*infloTreg*pC5 + f1*f4*infloTreg*pC5 - f1*f5*infloTreg*pC4 - f4*f5*infloTreg*pC1 + f1*f5*infloTreg*pC5 + f2*f4*infloTreg*pC5 + f3*f4*infloTreg*pC5 + f4*f5*infloTreg*pC5 - f1*f4*infloSinger*pC2 - f2*f4*infloSinger*pC1 - f3*f4*infloSinger*pC1 + f1*f4*infloSinger*pC5 - f4*f5*infloSinger*pC1 + f2*f4*infloSinger*pC5 + f3*f4*infloSinger*pC5 + f4*f5*infloSinger*pC5 + f1*infloTreg*pC2*pC4 + f2*infloTreg*pC1*pC4 + f4*infloTreg*pC1*pC2 - f1*infloTreg*pC2*pC5 - f2*infloTreg*pC1*pC5 + f3*infloTreg*pC1*pC4 - f3*infloTreg*pC1*pC5 - f1*infl\\\r\noTreg*pC4*pC5 - f4*infloTreg*pC1*pC5 + f5*infloTreg*pC1*pC4 - f2*infloTreg*pC4*pC5 - f4*infloTreg*pC2*pC5 - f5*infloTreg*pC1*pC5 - f3*infloTreg*pC4*pC5 - f5*infloTreg*pC4*pC5 + f4*infloSinger*pC1*pC2 - f4*infloSinger*pC1*pC5 - f4*infloSinger*pC2*pC5 - infloTreg*pC1*pC2*pC4 + infloTreg*pC1*pC2*pC5 + infloTreg*pC1*pC4*pC5 + infloTreg*pC2*pC4*pC5 + DPinit*f3*f4*pC5^2 + Singerinit*f1*f4*pC5^2 + Singerinit*f2*f4*pC5^2 + Singerinit*f3*f4*pC5^2 + Singerinit*f4*f5*pC5^2 + Treginit*f1*f2*pC5^2 + Treginit*f1*f3*pC5^2 + Treginit*f1*f4*pC5^2 + Treginit*f1*f5*pC5^2 + Treginit*f2*f4*pC5^2 + Treginit*f3*f4*pC5^2 + Treginit*f4*f5*pC5^2 - Singerinit*f4*pC1*pC5^2 - Singerinit*f4*pC2*pC5^2 - Treginit*f1*pC2*pC5^2 - Treginit*f2*pC1*pC5^2 - Treginit*f3*pC1*pC5^2 - Treginit*f1*pC4*pC5^2 - Treginit*f4*pC1*pC5^2 - Treginit*f2*pC4*pC5^2 - Treginit*f4*pC2*pC5^2 - Treginit*f5*pC1*pC5^2 - Treginit*f3*pC4*pC5^2 - Treginit*f5*pC4*pC5^2 + Treginit*pC1*pC2*pC5^2 + Treginit*pC1*pC4*pC5^2 + Treginit*pC2*pC4*pC5^2 + f1\\\r\n*f3*f4*infloDN + f1*f2*f4*infloTreg + f1*f3*f4*infloTreg + f1*f4*f5*infloTreg + f1*f2*f4*infloSinger + f1*f3*f4*infloSinger + f1*f4*f5*infloSinger + DNinit*f1*f3*f4*pC5 + DPinit*f1*f3*f4*pC5 - DPinit*f3*f4*pC1*pC5 + Singerinit*f1*f2*f4*pC5 + Singerinit*f1*f3*f4*pC5 + Singerinit*f1*f4*f5*pC5 + Treginit*f1*f2*f4*pC5 + Treginit*f1*f3*f4*pC5 + Treginit*f1*f4*f5*pC5 - Singerinit*f1*f4*pC2*pC5 - Singerinit*f2*f4*pC1*pC5 - Singerinit*f3*f4*pC1*pC5 - Singerinit*f4*f5*pC1*pC5 - Treginit*f1*f2*pC4*pC5 - Treginit*f1*f4*pC2*pC5 - Treginit*f2*f4*pC1*pC5 - Treginit*f1*f3*pC4*pC5 - Treginit*f3*f4*pC1*pC5 - Treginit*f1*f5*pC4*pC5 - Treginit*f4*f5*pC1*pC5 + Singerinit*f4*pC1*pC2*pC5 + Treginit*f1*pC2*pC4*pC5 + Treginit*f2*pC1*pC4*pC5 + Treginit*f4*pC1*pC2*pC5 + Treginit*f3*pC1*pC4*pC5 + Treginit*f5*pC1*pC4*pC5 - Treginit*pC1*pC2*pC4*pC5)/(pC5*(f1 - pC1 + pC5)*(f4 - pC4 + pC5)*(f2 + f3 + f5 - pC2 + pC5))) + (f3*f4*exp(-t*(f2 + f3 + f5 - pC2))*((f5*(f1*infloDN + DPinit*f2^2 + DPinit*f3^2 + DPinit*f5^2 +\\\r\n DPinit*pC2^2 - DNinit*f1*f2 - DNinit*f1*f3 - DNinit*f1*f5 - DPinit*f1*f2 - DPinit*f1*f3 + 2*DPinit*f2*f3 - DPinit*f1*f5 + 2*DPinit*f2*f5 + 2*DPinit*f3*f5 + DNinit*f1*pC2 + DPinit*f1*pC2 + DPinit*f2*pC1 - 2*DPinit*f2*pC2 + DPinit*f3*pC1 - 2*DPinit*f3*pC2 + DPinit*f5*pC1 - 2*DPinit*f5*pC2 - DPinit*pC1*pC2))/((f2 + f3 + f5 - pC2)*(f2 + f3 + f5 - pC2 + pC6)*(f2 - f1 + f3 + f5 + pC1 - pC2)) - (f1*f5*infloDN*exp(f2*t + f3*t + f5*t - pC2*t))/((f2 + f3 + f5 - pC2)*(2*f2*f3 - f1*f3 - f1*f2 - f1*f5 + 2*f2*f5 + 2*f3*f5 + f1*pC2 + f2*pC1 - 2*f2*pC2 + f3*pC1 - 2*f3*pC2 + f5*pC1 - f1*pC6 - 2*f5*pC2 + f2*pC6 + f3*pC6 + f5*pC6 - pC1*pC2 + pC1*pC6 - pC2*pC6 + f2^2 + f3^2 + f5^2 + pC2^2)))*(f2 + f3 + f5 - pC2 + pC6))/(f5*(f2 + f3 + f5 - pC2 + pC5)*(f2 + f3 - f4 + f5 - pC2 + pC4)) + (f3*f4*exp(-t*(f1 - pC1))*((f1*f5*infloDN*exp(f1*t - pC1*t))/((f1 - pC1)*(f1*f2 + f1*f3 + f1*f5 + 2*f1*pC1 - f1*pC2 - f2*pC1 - f3*pC1 - f5*pC1 - f1*pC6 + f2*pC6 + f3*pC6 + f5*pC6 + pC1*pC2 + pC1*pC6 - pC2*pC6 - f1^2 - pC1^2\\\r\n)) - (f1*f5*(infloDN - DNinit*f1 + DNinit*pC1))/((f1 - pC1)*(f1 - pC1 + pC6)*(f2 - f1 + f3 + f5 + pC1 - pC2)))*(f1 - pC1 + pC6))/(f5*(f1 - pC1 + pC5)*(f1 - f4 - pC1 + pC4))


solSP8(t) =

exp(pC6*t)*((SP8init*pC6^3 + infloSP8*pC6^2 + f1*f5*infloDN + f1*f2*infloSP8 + f1*f3*infloSP8 + f1*f5*infloSP8 - f1*infloSP8*pC2 - f2*infloSP8*pC1 - f3*infloSP8*pC1 - f5*infloSP8*pC1 + f1*infloSP8*pC6 + f2*infloSP8*pC6 + f3*infloSP8*pC6 + f5*infloSP8*pC6 + infloSP8*pC1*pC2 - infloSP8*pC1*pC6 - infloSP8*pC2*pC6 + DPinit*f5*pC6^2 + SP8init*f1*pC6^2 + SP8init*f2*pC6^2 + SP8init*f3*pC6^2 + SP8init*f5*pC6^2 - SP8init*pC1*pC6^2 - SP8init*pC2*pC6^2 + SP8init*pC1*pC2*pC6 + DNinit*f1*f5*pC6 + DPinit*f1*f5*pC6 - DPinit*f5*pC1*pC6 + SP8init*f1*f2*pC6 + SP8init*f1*f3*pC6 + SP8init*f1*f5*pC6 - SP8init*f1*pC2*pC6 - SP8init*f2*pC1*pC6 - SP8init*f3*pC1*pC6 - SP8init*f5*pC1*pC6)/(pC6*(f1 - pC1 + pC6)*(f2 + f3 + f5 - pC2 + pC6)) - (exp(-pC6*t)*(infloSP8*pC6^2 + f1*f5*infloDN + f1*f2*infloSP8 + f1*f3*infloSP8 + f1*f5*infloSP8 - f1*infloSP8*pC2 - f2*infloSP8*pC1 - f3*infloSP8*pC1 - f5*infloSP8*pC1 + f1*infloSP8*pC6 + f2*infloSP8*pC6 + f3*infloSP8*pC6 + f5*infloSP8*pC6 + infloSP8*pC1*pC2 - infloSP8*pC1*pC\\\r\n6 - infloSP8*pC2*pC6))/(pC6*(f1*f2 + f1*f3 + f1*f5 - f1*pC2 - f2*pC1 - f3*pC1 - f5*pC1 + f1*pC6 + f2*pC6 + f3*pC6 + f5*pC6 + pC1*pC2 - pC1*pC6 - pC2*pC6 + pC6^2))) - exp(-t*(f2 + f3 + f5 - pC2))*((f5*(f1*infloDN + DPinit*f2^2 + DPinit*f3^2 + DPinit*f5^2 + DPinit*pC2^2 - DNinit*f1*f2 - DNinit*f1*f3 - DNinit*f1*f5 - DPinit*f1*f2 - DPinit*f1*f3 + 2*DPinit*f2*f3 - DPinit*f1*f5 + 2*DPinit*f2*f5 + 2*DPinit*f3*f5 + DNinit*f1*pC2 + DPinit*f1*pC2 + DPinit*f2*pC1 - 2*DPinit*f2*pC2 + DPinit*f3*pC1 - 2*DPinit*f3*pC2 + DPinit*f5*pC1 - 2*DPinit*f5*pC2 - DPinit*pC1*pC2))/((f2 + f3 + f5 - pC2)*(f2 + f3 + f5 - pC2 + pC6)*(f2 - f1 + f3 + f5 + pC1 - pC2)) - (f1*f5*infloDN*exp(f2*t + f3*t + f5*t - pC2*t))/((f2 + f3 + f5 - pC2)*(2*f2*f3 - f1*f3 - f1*f2 - f1*f5 + 2*f2*f5 + 2*f3*f5 + f1*pC2 + f2*pC1 - 2*f2*pC2 + f3*pC1 - 2*f3*pC2 + f5*pC1 - f1*pC6 - 2*f5*pC2 + f2*pC6 + f3*pC6 + f5*pC6 - pC1*pC2 + pC1*pC6 - pC2*pC6 + f2^2 + f3^2 + f5^2 + pC2^2))) - exp(-t*(f1 - pC1))*((f1*f5*infloDN*exp(f1*t - pC1*t))/((f1 -\\\r\n pC1)*(f1*f2 + f1*f3 + f1*f5 + 2*f1*pC1 - f1*pC2 - f2*pC1 - f3*pC1 - f5*pC1 - f1*pC6 + f2*pC6 + f3*pC6 + f5*pC6 + pC1*pC2 + pC1*pC6 - pC2*pC6 - f1^2 - pC1^2)) - (f1*f5*(infloDN - DNinit*f1 + DNinit*pC1))/((f1 - pC1)*(f1 - pC1 + pC6)*(f2 - f1 + f3 + f5 + pC1 - pC2)))

*/

modele1ThymusOnly::modele1ThymusOnly() : Modele(NbVariables, NbParameters), background(Back::WT) {
    name = string("modeleLeishmania");
    dt = 0.001; // initial time step -> then it is adaptive
    print_all_secs = 1200; //every how many seconds it is plotting
	// Name of variables           
    names[tDN] = string("thymic DN");
    names[tDP] = string("thymic DP");
    names[tTconv] = string("thymic Tconv");
    names[tTRegP25] = string("thymic 25+ progenitors");
    names[tTRegPFp3] = string("thymic Foxp3+ progenitors");
    names[tDPTreg] = string("thymic mature Tregs");
    names[tSP8] = string("thymic SP CD8");
    names[tSP4] = string("Thymic SP CD4");


    names[pcDN] =       string("% DN / tot cells");
    names[pcDP] =       string("% DP / tot cells");
    names[pcSP4] =      string("% SP4 / tot cells");
    names[pcSP8] =      string("% SP8 / tot cells");
    names[pcDPTreg] =   string("% Mature Tregs / CD4");
    names[pcSingerP] =  string("% Singer Precursors / CD4");
    names[pcFp3P] =     string("% Foxp3+ Precutsors / CD4");
    names[pcTotTregs] = string("% total Tregs / CD4");

	// the names of variables that can be accessed by outside (global name-space)
    extNames[tDN] = N::tDN;
    extNames[tDP] = N::tDP;
    extNames[tTconv] = N::tTconv;
    extNames[tTRegP25] = N::tTRegP25;
    extNames[tTRegPFp3] = N::tTRegPFp3;
    extNames[tDPTreg] = N::tTreg;
    extNames[tSP8] = N::tSP8;
    extNames[tSP4] = N::tSP4;

	// Name of parameters


    paramNames[fETP_tDN] = "fETP_tDN / DN thymic Inflow";
    paramNames[ptDN] = "ptDN / prolif DN";
    paramNames[ftDN_tDP] = "ftDN_tDP / conversion DN to DP";
    paramNames[ptDP] = "pdDP / proliferation DP (low)";
    paramNames[ftDP_tTConv] = "ftDP_tTConv / conversion from DP to Tconv";
    paramNames[ftDP_tTregP25] = "ftDP_tTregP25 / conversion DP to shieh precursors";
    paramNames[ftDP_tTregFP3] = "ftDP_tTregFP3 / conversion DP to singer precursors";
    paramNames[ftDP_tSP8] = "ftDP_tSP8 / conversion DP to SP8";
    paramNames[out_tDP] = "out_tDP / outflow of DP";
    //paramNames[in_tDP] = "in_tDP / inflow (recirculation) of DP";
    paramNames[ptTregP25] = "ptTregP25 / prolif shieh precursors";
    paramNames[ftTregP25_tDPTreg] = "ftTregP25_tDPTreg / conversion shieh to mature Tregs";
    paramNames[out_tTregP25] = "out_tTregP25 / outflow shieh precursors";
    paramNames[ptTregFP3] = "ptTregFP3 / prolif singer precursors";
    paramNames[ftTregFP3_tDPTreg] = "ftTregFP3_tDPTreg / conversion singer to mature Tregs";
    paramNames[out_tTregFP3] = "out_tTregFP3 / outflow singer precursors";
    paramNames[ptDPTregs] = "ptDPTregs / prolif mature Tregs";
    paramNames[out_tDPTregs] = "out_tDPTregs / outflow mature Tregs";
    paramNames[in_tDPTregs] = "in_tDPTregs / inflow (recirculation) mature Tregs";
    paramNames[ptTconv] = "ptTconv / prolif Tconvs";
    paramNames[out_tTconv] = "out_tTconv / outflow of Tconvs";
    paramNames[in_tTconv] = "in_tTconv / inflow of Tconvs";
    paramNames[ptSP8] = "ptSP8 / prolif SP8";
    paramNames[out_SP8] = "out_SP8 / outflow SP8";
    paramNames[in_SP8] = "in_SP8 / inflow (recirculation) SP8";
    paramNames[dtDN] = "dtDN / death DN";
    paramNames[dtDP] = "dtDP / death DP";
    paramNames[dtTregP25] = "dtTregP25 / death shiesh precursors";
    paramNames[dtTregFP3] = "dtTregFP3 / death singer precursors";
    paramNames[dtDPTregs] = "dtDPTregs / death mature Tregs";
    paramNames[dtTconv] = "dtTconv / death Tconv";
    paramNames[dtSP8] = "dtSP8 / death SP8";
    paramNames[	hypInflowCoeffETP	]="	hypInflowCoeffETP	";
    paramNames[	hypDeathCoeffDP	]="	hypDeathCoeffDP	";
    paramNames[	hypDeathCoeffTconv	]="	hypDeathCoeffTconv	";
    paramNames[	hypDeathCoeffProFp3	]="	hypDeathCoeffProFp3	";
    paramNames[	hypDeathCoeffPro25	]="	hypDeathCoeffPro25	";
    paramNames[	hypDeathCoeffDPTregs	]="	hypDeathCoeffDPTregs	";
    paramNames[	hypDeathCoeffSP8	]="	hypDeathCoeffSP8	";
    paramNames[	hypOutputCoeffOutDP	]="	hypOutputCoeffOutDP	";
    paramNames[	hypOutputCoeffOutTconv	]="	hypOutputCoeffOutTconv	";
    paramNames[	hypOutputCoeffOutDPTregs	]="	hypOutputCoeffOutDPTregs	";
    paramNames[	hypOutputCoeffOutProFP3	]="	hypOutputCoeffOutProFP3	";
    paramNames[	hypOutputCoeffOutPro25	]="	hypOutputCoeffOutPro25	";
    paramNames[	hypOutputCoeffOutSP8	]="	hypOutputCoeffOutSP8	";
    paramNames[	hypFasterCoeffDNtoDP	]="	hypFasterCoeffDNtoDP	";
    paramNames[	hypFasterCoeffProFP3	]="	hypFasterCoeffProFP3	";
    paramNames[	hypFasterCoeffPro25	]="	hypFasterCoeffPro25	";
    paramNames[	hypFasterCoeffTconv	]="	hypFasterCoeffTconv	";
    paramNames[	hypFasterCoeffSP8	]="	hypFasterCoeffSP8	";
    paramNames[	hypSpaceOutputCoeff	]="	hypSpaceOutputCoeff	";






    paramLowBounds[fETP_tDN] = 1;                   paramUpBounds[fETP_tDN] = 1;
    paramLowBounds[ptDN] = 1;                       paramUpBounds[ptDN] = 1;
    paramLowBounds[ftDN_tDP] = 1;		paramUpBounds[ftDN_tDP] = 1;
    paramLowBounds[ptDP] = 1;		paramUpBounds[ptDP] = 1;
    paramLowBounds[ftDP_tTConv] = 1;		paramUpBounds[ftDP_tTConv] = 1;
    paramLowBounds[ftDP_tTregP25] = 1;		paramUpBounds[ftDP_tTregP25] = 1;
    paramLowBounds[ftDP_tTregFP3] = 1;		paramUpBounds[ftDP_tTregFP3] = 1;
    paramLowBounds[ftDP_tSP8] = 1;		paramUpBounds[ftDP_tSP8] = 1;
    paramLowBounds[out_tDP] = 1;		paramUpBounds[out_tDP] = 1;
    //paramLowBounds[in_tDP] = 1;		paramUpBounds[in_tDP] = 1;
    paramLowBounds[ptTregP25] = 1;		paramUpBounds[ptTregP25] = 1;
    paramLowBounds[ftTregP25_tDPTreg] = 1;		paramUpBounds[ftTregP25_tDPTreg] = 1;
    paramLowBounds[out_tTregP25] = 1;		paramUpBounds[out_tTregP25] = 1;
    paramLowBounds[ptTregFP3] = 1;		paramUpBounds[ptTregFP3] = 1;
    paramLowBounds[ftTregFP3_tDPTreg] = 1;		paramUpBounds[ftTregFP3_tDPTreg] = 1;
    paramLowBounds[out_tTregFP3] = 1;		paramUpBounds[out_tTregFP3] = 1;
    paramLowBounds[ptDPTregs] = 1;		paramUpBounds[ptDPTregs] = 1;
    paramLowBounds[out_tDPTregs] = 1;		paramUpBounds[out_tDPTregs] = 1;
    paramLowBounds[in_tDPTregs] = 1;		paramUpBounds[in_tDPTregs] = 1;
    paramLowBounds[ptTconv] = 1;		paramUpBounds[ptTconv] = 1;
    paramLowBounds[out_tTconv] = 1;		paramUpBounds[out_tTconv] = 1;
    paramLowBounds[in_tTconv] = 1;		paramUpBounds[in_tTconv] = 1;
    paramLowBounds[ptSP8] = 1;		paramUpBounds[ptSP8] = 1;
    paramLowBounds[out_SP8] = 1;		paramUpBounds[out_SP8] = 1;
    paramLowBounds[in_SP8] = 1;		paramUpBounds[in_SP8] = 1;
    paramLowBounds[dtDN] = 1;		paramUpBounds[dtDN] = 1;
    paramLowBounds[dtDP] = 1;		paramUpBounds[dtDP] = 1;
    paramLowBounds[dtTregP25] = 1;		paramUpBounds[dtTregP25] = 1;
    paramLowBounds[dtTregFP3] = 1;		paramUpBounds[dtTregFP3] = 1;
    paramLowBounds[dtDPTregs] = 1;		paramUpBounds[dtDPTregs] = 1;
    paramLowBounds[dtTconv] = 1;		paramUpBounds[dtTconv] = 1;
    paramLowBounds[dtSP8] = 1;		paramUpBounds[dtSP8] = 1;
    paramLowBounds[hypInflowCoeffETP] = 1;		paramUpBounds[hypInflowCoeffETP] = 1;
    paramLowBounds[hypDeathCoeffDP] = 1;		paramUpBounds[hypDeathCoeffDP] = 1;
    paramLowBounds[hypDeathCoeffTconv] = 1;		paramUpBounds[hypDeathCoeffTconv] = 1;
    paramLowBounds[hypDeathCoeffProFp3] = 1;		paramUpBounds[hypDeathCoeffProFp3] = 1;
    paramLowBounds[hypDeathCoeffPro25] = 1;		paramUpBounds[hypDeathCoeffPro25] = 1;
    paramLowBounds[hypDeathCoeffDPTregs] = 1;		paramUpBounds[hypDeathCoeffDPTregs] = 1;
    paramLowBounds[hypDeathCoeffSP8] = 1;		paramUpBounds[hypDeathCoeffSP8] = 1;
    paramLowBounds[hypOutputCoeffOutDP] = 1;		paramUpBounds[hypOutputCoeffOutDP] = 1;
    paramLowBounds[hypOutputCoeffOutTconv] = 1;		paramUpBounds[hypOutputCoeffOutTconv] = 1;
    paramLowBounds[hypOutputCoeffOutDPTregs] = 1;		paramUpBounds[hypOutputCoeffOutDPTregs] = 1;
    paramLowBounds[hypOutputCoeffOutProFP3] = 1;		paramUpBounds[hypOutputCoeffOutProFP3] = 1;
    paramLowBounds[hypOutputCoeffOutPro25] = 1;		paramUpBounds[hypOutputCoeffOutPro25] = 1;
    paramLowBounds[hypOutputCoeffOutSP8] = 1;		paramUpBounds[hypOutputCoeffOutSP8] = 1;
    paramLowBounds[hypFasterCoeffDNtoDP] = 1;		paramUpBounds[hypFasterCoeffDNtoDP] = 1;
    paramLowBounds[hypFasterCoeffProFP3] = 1;		paramUpBounds[hypFasterCoeffProFP3] = 1;
    paramLowBounds[hypFasterCoeffPro25] = 1;		paramUpBounds[hypFasterCoeffPro25] = 1;
    paramLowBounds[hypFasterCoeffTconv] = 1;		paramUpBounds[hypFasterCoeffTconv] = 1;
    paramLowBounds[hypFasterCoeffSP8] = 1;		paramUpBounds[hypFasterCoeffSP8] = 1;
    paramLowBounds[hypSpaceOutputCoeff] = 1;		paramUpBounds[hypSpaceOutputCoeff] = 1;










    backSimulated.clear();
	backSimulated.push_back(Back::WT);
}

void modele1ThymusOnly::setBaseParameters(){
    background = Back::WT;
	params.clear();     // to make sure they are all put to zero
    params.resize(NbParameters, 0.0);

    params[fETP_tDN] = 50000;
    params[ptDN] = 0.05;
    params[ftDN_tDP] = 0.1;
    params[ptDP] = 0.01;
    params[ftDP_tTConv] = 0.1;
    params[ftDP_tTregP25] = 0.005;
    params[ftDP_tTregFP3] = 0.005;
    params[ftDP_tSP8] = 0.05;
    params[out_tDP] = 0.005;
    //params[in_tDP] = 0.005;
    params[ptTregP25] = 0.01;
    params[ftTregP25_tDPTreg] = 0.05;
    params[out_tTregP25] = 0.05;
    params[ptTregFP3] = 0.001;
    params[ftTregFP3_tDPTreg] = 0.05;
    params[out_tTregFP3] = 0.05;
    params[ptDPTregs] = 0.001;
    params[out_tDPTregs] = 0.08;
    params[in_tDPTregs] = 10000;
    params[ptTconv] = 0.001;
    params[out_tTconv] = 0.05;
    params[in_tTconv] = 10000;
    params[ptSP8] = 0.001;
    params[out_SP8] = 0.05;
    params[in_SP8] = 800;
    params[dtDN] = 0.03;
    params[dtDP] = 0.03;
    params[dtTregP25] = 0.03;
    params[dtTregFP3] = 0.03;
    params[dtDPTregs] = 0.03;
    params[dtTconv] = 0.03;
    params[dtSP8] = 0.03;
    params[hypInflowCoeffETP] = 0.3;
    params[hypDeathCoeffDP] = 10;
    params[hypDeathCoeffTconv] = 1;
    params[hypDeathCoeffProFp3] = 1;
    params[hypDeathCoeffPro25] = 1;
    params[hypDeathCoeffDPTregs] = 1;
    params[hypDeathCoeffSP8] = 1;
    params[hypOutputCoeffOutDP] = 0.2;
    params[hypOutputCoeffOutTconv] = 1;
    params[hypOutputCoeffOutDPTregs] = 1;
    params[hypOutputCoeffOutProFP3] = 1;
    params[hypOutputCoeffOutPro25] = 1;
    params[hypOutputCoeffOutSP8] = 1;
    params[hypFasterCoeffDNtoDP] = 1;
    params[hypFasterCoeffProFP3] = 5;
    params[hypFasterCoeffPro25] = 1;
    params[hypFasterCoeffTconv] = 1;
    params[hypFasterCoeffSP8] = 1;
    params[hypSpaceOutputCoeff] = 0.2;

	setBaseParametersDone();
}

void modele1ThymusOnly::initialise(long long _background){ // don't touch to parameters !
	val.clear();
    val.resize(NbVariables, 0.0);
	init.clear();
    init.resize(NbVariables, 0.0);

    // test if each possible background is in the current combination of backgrounds (stored in the field background)
    if((background != Back::WT) && (background != _background)){
        cerr << "WRN : modeleLeishmania::initialize, when the background has been changed from WT, you should not change it again, because parameters can not be retrieved. Please load parameters again" << endl;
    }

    /// PHIlippe todo change with combinations !!
    background = _background;
    if(background == Back::WT){}
    if(background == Back::B_ReducedInflow){



    }
    if(background == Back::B_MoreDeath){}
    if(background == Back::B_MoreOutputThymus){}
    if(background == Back::B_FasterDifferentiation){}
    if(background == Back::B_SpaceDependentOutput){}





    //if(background == Back::M2){}
    //if(background == Back::TCRGATA3NEGKO){   params[KTCRGATA3]   = 0;} // for different options i.e. deficiency in something


    // if the initial values depend on parameters
    /*init[IL2] = params[IL2EQ];
    init[IL4] = params[IL4EQ];*/

    init[tDN] = 3.5e7; //3e6;
    init[tDP] = 9e7; //100e6;
    init[tTconv] = 1e7; //12e6;
    init[tTRegP25] = 2.5e6; //5.8e6; //50000;
    init[tTRegPFp3] = 50e6; ///1.1e6;//50000;
    init[tDPTreg] = 1e6; //8e6;//1e6;
    init[tSP8] = 1e7; //5e6; //1.3e8; //5e6;
    //init[tSP4] = init[tTconv] + init[tTRegP25] + init[tTRegPFp3] + init[tDPTreg];

    params[ptDN] = params[ftDN_tDP] +  params[dtDN] - params[fETP_tDN] / init[tDN];
    params[ptDP] = - (init[tDN] * params[ftDN_tDP]) / init[tDP]  + params[out_tDP]  + params[ftDP_tTConv] + params[ftDP_tTregP25] + params[ftDP_tTregFP3] + params[ftDP_tSP8] + params[dtDP];
    params[ptTconv] = (- params[in_tTconv] - init[tDP] * params[ftDP_tTConv]) / init[tTconv] +
            params[out_tTconv] + params[dtTconv];
    params[ptTregP25] = - init[tDP] * params[ftDP_tTregP25] / init[tTRegP25]  + params[out_tTregP25] + params[ftTregP25_tDPTreg] + params[dtTregP25];
    params[ptTregFP3] = - init[tDP] * params[ftDP_tTregFP3] / init[tTRegPFp3] + params[out_tTregFP3] + params[ftTregFP3_tDPTreg] + params[dtTregFP3];
    params[ptDPTregs] = (- params[in_tDPTregs] - init[tTRegP25] * params[ftTregP25_tDPTreg] - init[tTRegPFp3] * params[ftTregFP3_tDPTreg]) / init[tDPTreg] +
            params[out_tDPTregs] + params[dtDPTregs];
    params[ptSP8] = (- params[in_SP8] -  init[tDP] * params[ftDP_tSP8]) / init[tSP8] +
            params[out_SP8] + params[dtSP8];

    cerr << "Initializing from new parameter values ..." << endl;
    if(params[ptDN] < 0){
        cerr << "ERR: the initial conditions + parameters don't allow the parameter [ptDN] to be positive / allow steady state" << endl;
        cerr << "     Please put params[fETP_tDN] < " << (params[ftDN_tDP] +  params[dtDN]) * init[tDN] << " instead of " << params[fETP_tDN] << endl;
        params[ptDN] = 0;
    }

    if(params[ptDP] < 0){
        cerr << "ERR: the initial conditions + parameters don't allow the parameter [ptDP] to be positive / allow steady state" << endl;
        cerr <<"     Please, put params[ftDN_tDP] < " << init[tDP] *
                (params[dtDP] + params[ptDP] + params[ftDP_tTConv] + params[ftDP_tTregP25] + params[ftDP_tTregFP3] + params[ftDP_tSP8] + params[out_tDP])
                / init[tDN] << " instead of " << params[ftDN_tDP] << endl;
        params[ptDP] = 0;
    }

    if(params[ptTconv] < 0){
        cerr << "ERR: the initial conditions + parameters don't allow the parameter [ptTconv] to be positive / allow steady state" << endl;

        cerr << "     Please, put params[ftDP_tTConv]) < " <<
                (- params[in_tTconv] + init[tTconv] * params[out_tTconv] + params[dtTconv]) / init[tDP] << " instead of " << params[ftDP_tTConv] << endl;
        params[ptTconv] = 0;
    }

    if(params[ptTregP25] < 0){
        cerr << "ERR: the initial conditions + parameters don't allow the parameter [ptTregP25] to be positive / allow steady state" << endl;
        cerr << "     Please, put params[ftDP_tTregP25] < " << init[tTRegP25] * (params[out_tTregP25] + params[ftTregP25_tDPTreg] + params[dtTregP25]) / init[tDP] << endl;
        params[ptTregP25] = 0;
    }

    if(params[ptTregFP3] < 0){
        cerr << "ERR: the initial conditions + parameters don't allow the parameter [ptTregP25] to be positive / allow steady state" << endl;
        cerr << "     Please, put params[ftDP_tTregFP3] < " << init[tTRegPFp3] * (params[out_tTregFP3] + params[ftTregFP3_tDPTreg] + params[dtTregFP3]) /  init[tDP] << endl;
        params[ptTregFP3] = 0;
    }

    if(params[ptDPTregs] < 0){
        cerr << "ERR: the initial conditions + parameters don't allow the parameter [ptDPTregs] to be positive / allow steady state" << endl;


        /*params[ptDPTregs] = (- params[in_tDPTregs] - init[tTRegP25] * params[ftTregP25_tDPTreg] - init[tTRegPFp3] * params[ftTregFP3_tDPTreg]) / init[tDPTreg] +
                params[out_tDPTregs] + params[dtDPTregs];
        params[ptSP8] = (- params[in_SP8] -  init[tDP] * params[ftDP_tSP8]) / init[tSP8] +
                params[out_SP8] + params[dtSP8];*/

        params[ptDPTregs] = 0;
    }

    if(params[ptSP8] < 0){
        cerr << "ERR: the initial conditions + parameters don't allow the parameter [ptSP8] to be positive / allow steady state" << endl;
        params[ptSP8] = 0;
    }

    for(int i = 0; i < NbVariables; ++i){
		val[i] = init[i];}
	t = 0;
	initialiseDone();
}


void modele1ThymusOnly::updateDerivedVariables(){
    val[tSP4] =  val[tTconv] + val[tTRegP25] + val[tTRegPFp3] + val[tDPTreg];
    val[pcDN] =  100 * min(1.0, val[tDN] / max(1e-8, val[tDN] + val[tDP] + val[tSP4] + val[tSP8]));
    val[pcDP] =  100 * min(1.0, val[tDP] / max(1e-8, val[tDN] + val[tDP] + val[tSP4] + val[tSP8]));
    val[pcSP4] = 100 * min(1.0, val[tSP4] / max(1e-8, val[tDN] + val[tDP] + val[tSP4] + val[tSP8]));
    val[pcSP8] = 100 * min(1.0, val[tSP8] / max(1e-8, val[tDN] + val[tDP] + val[tSP4] + val[tSP8]));
    val[pcDPTreg] =   100 * min(1.0, val[tDPTreg] / max(1e-8, val[tSP4]));
    val[pcSingerP] =  100 * min(1.0, val[pcSingerP] / max(1e-8, val[tSP4]));
    val[pcFp3P] =     100 * min(1.0, val[pcFp3P] / max(1e-8, val[tSP4]));
    val[pcTotTregs] = 100 * min(1.0, (val[tDPTreg] + val[pcSingerP] + val[pcFp3P]) / max(1e-8, val[tSP4]));
}

void modele1ThymusOnly::derivatives(const vector<double> &x, vector<double> &dxdt, const double t){

    double          InflowCoeffETP = 1;
    double          DeathCoeffDP = 1;
    double          DeathCoeffTconv = 1;
    double          DeathCoeffProFp3 = 1;
    double          DeathCoeffPro25 = 1;
    double          DeathCoeffDPTregs = 1;
    double          DeathCoeffSP8 = 1;
    double          OutputCoeffOutDP = 1;
    double          OutputCoeffOutTconv = 1;
    double          OutputCoeffOutDPTregs = 1;
    double          OutputCoeffOutProFP3 = 1;
    double          OutputCoeffOutPro25 = 1;
    double          OutputCoeffOutSP8 = 1;
    double          FasterCoeffDNtoDP = 1;
    double          FasterCoeffProFP3 = 1;
    double          FasterCoeffPro25 = 1;
    double          FasterCoeffTconv = 1;
    double          FasterCoeffSP8 = 1;
    double          SpaceOutputCoeff = 1;

    if(background == Back::B_ReducedInflow){
        InflowCoeffETP = params[hypInflowCoeffETP];
    }
    if(background == Back::B_MoreDeath){
        DeathCoeffDP         = params[hypDeathCoeffDP];
        DeathCoeffTconv      = params[hypDeathCoeffTconv];
        DeathCoeffProFp3     = params[hypDeathCoeffProFp3];
        DeathCoeffPro25      = params[hypDeathCoeffPro25];
        DeathCoeffDPTregs    = params[hypDeathCoeffDPTregs];
        DeathCoeffSP8        = params[hypDeathCoeffSP8];
    }
    if(background == Back::B_MoreOutputThymus){
        OutputCoeffOutDP	= params[	hypOutputCoeffOutDP	];
        OutputCoeffOutTconv	= params[	hypOutputCoeffOutTconv	];
        OutputCoeffOutDPTregs	= params[	hypOutputCoeffOutDPTregs	];
        OutputCoeffOutProFP3	= params[	hypOutputCoeffOutProFP3	];
        OutputCoeffOutPro25	= params[	hypOutputCoeffOutPro25	];
        OutputCoeffOutSP8	= params[	hypOutputCoeffOutSP8	];
    }
    if(background == Back::B_FasterDifferentiation){
        FasterCoeffDNtoDP	= params[	hypFasterCoeffDNtoDP	];
        FasterCoeffProFP3	= params[	hypFasterCoeffProFP3	];
        FasterCoeffPro25	= params[	hypFasterCoeffPro25	];
        FasterCoeffTconv	= params[	hypFasterCoeffTconv	];
        FasterCoeffSP8	= params[	hypFasterCoeffSP8	];
    }
    if(background == Back::B_SpaceDependentOutput){
        SpaceOutputCoeff  = params[hypSpaceOutputCoeff];
    }


   if(!over(tDN)) {
        dxdt[tDN] 	= InflowCoeffETP * params[fETP_tDN] + x[tDN] * (params[ptDN] - FasterCoeffDNtoDP * params[ftDN_tDP] - params[dtDN]);
   }
   if(!over(tDP)) {
        dxdt[tDP] 	= x[tDN] * FasterCoeffDNtoDP * params[ftDN_tDP] +  x[tDP] * (- SpaceOutputCoeff * OutputCoeffOutDP * params[out_tDP] + params[ptDP] - FasterCoeffTconv * params[ftDP_tTConv] - FasterCoeffPro25 * params[ftDP_tTregP25] - FasterCoeffProFP3 * params[ftDP_tTregFP3] - FasterCoeffSP8 * params[ftDP_tSP8] - DeathCoeffDP * params[dtDP]);
   }
   if(!over(tTconv)) {
        dxdt[tTconv] 	= params[in_tTconv]  + x[tDP] * FasterCoeffTconv * params[ftDP_tTConv] + x[tTconv] * (- SpaceOutputCoeff * OutputCoeffOutTconv * params[out_tTconv] + params[ptTconv] - DeathCoeffTconv * params[dtTconv]);
   }
   if(!over(tTRegP25)) {
        dxdt[tTRegP25] 	=   x[tDP] * FasterCoeffPro25 * params[ftDP_tTregP25] + x[tTRegP25] * (- SpaceOutputCoeff * OutputCoeffOutPro25 * params[out_tTregP25] + params[ptTregP25] - params[ftTregP25_tDPTreg] - DeathCoeffPro25 * params[dtTregP25]);
   }
   if(!over(tTRegPFp3)) {
        dxdt[tTRegPFp3] 	= x[tDP] * FasterCoeffProFP3 * params[ftDP_tTregFP3] + x[tTRegPFp3] * ( - SpaceOutputCoeff * OutputCoeffOutProFP3 * params[out_tTregFP3] + params[ptTregFP3] - params[ftTregFP3_tDPTreg] - DeathCoeffProFp3 * params[dtTregFP3]);
   }
   if(!over(tDPTreg)) {
        dxdt[tDPTreg] 	= params[in_tDPTregs] +  x[tTRegP25] * params[ftTregP25_tDPTreg] + x[tTRegPFp3] * params[ftTregFP3_tDPTreg] + x[tDPTreg] * (- SpaceOutputCoeff * OutputCoeffOutDPTregs * params[out_tDPTregs]  + params[ptDPTregs] - DeathCoeffDPTregs * params[dtDPTregs]);
   }
   if(!over(tSP8)) {
        dxdt[tSP8] 	= params[in_SP8]  + x[tDP] * FasterCoeffSP8 * params[ftDP_tSP8] + x[tSP8] * (- SpaceOutputCoeff * OutputCoeffOutSP8 * params[out_SP8] + params[ptSP8] - DeathCoeffSP8 * params[dtSP8]);
   }


}
