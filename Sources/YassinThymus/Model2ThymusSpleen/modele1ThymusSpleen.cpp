// ------- Automatically generated model -------- //
#include "modele1ThymusSpleen.h"

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

modele1ThymusSpleen::modele1ThymusSpleen() : Model(NbVariables, NbParameters), background(Back::WT) {
    name = string("modele1ThymusSpleen");
    dt = 0.001; // initial time step -> then it is adaptive
    print_every_dt = 1200; //every how many seconds it is plotting
    // Name of variables
    names[flu] = string("flu");
    names[ttotal] = string("total thymocytes");
    names[tDN] = string("thymic DN");
    names[tDP] = string("thymic DP");
    names[tSP8] = string("thymic SP CD8");
    names[tSP4] = string("Thymic SP CD4");
    names[tTconv] = string("thymic Tconv");
    names[tTRegP25] = string("thymic 25+ progenitors (P1)");
    names[tTRegPFp3] = string("thymic Foxp3+ progenitors (P2)");
    names[tTreg] = string("thymic mature Tregs");
    names[tSP8RagN] = string("thymic SP8 Rag-");
    names[tSP4RagN] = string("thymic SP4 Rag-");
    names[tTconvRagN] = string("thymic Tconv Rag-");
    names[tTregP1RagN] = string("thymic Treg Progenitor 1 Rag- (CD25+)");
    names[tTregP2RagN] = string("thymic Treg Progenitor 2 Rag- (Fp3+)");
    names[tTregRagN] = string("thymic mature Treg Rag-");
    names[pctDN] =       string("% tDN / tot cells");
    names[pctDP] =       string("% tDP / tot cells");
    names[pctSP8] =      string("% tSP8 / tot cells");
    names[pctSP4] =      string("% tSP4 / tot cells");
    names[pctTconv] =   string("% tTconv / CD4");
    names[pctTRegP1] =  string("% tSinger Precursors (1) / CD4");
    names[pctTRegP2] =  string("% tFoxp3+ Precutsors (2) / CD4");
    names[pctTreg] = string("% mature tTregs / CD4");
    names[pctSP8RagN] = string("% Rag- in tSP8");
    names[pctSP4RagN] = string("% Rag- in tSP4");
    names[pctTconvRagN] = string("% Rag- in Tconv");
    names[pctTRegP1RagN] = string("% Rag- in tSinger Prec (1)");
    names[pctTRegP2RagN] = string("% Rag- in tFoxp3+ Prec (2)");
    names[pctTregRagN] = string("% Rag- in mature tTreg ");
    names[stotal] = string("total splenocytes");
    names[sTconv] = string("splenic Tconv");
    names[sTreg] = string("splenic Treg");
    names[sCD8] = string("splenic CD8");
    names[sBcells] = string("splenic B cells");
    names[sTconvRagN] = string("splenic Tconv Rag-");
    names[sTregRagN] = string("splenic Treg Rag-");
    names[sCD8RagN] = string("splenic CD8 Rag-");
    names[pcsTconv] = string("% Tconv in spleen");
    names[pcsTreg] = string("% Treg in spleen");
    names[pcsCD8] = string("% CD8 in spleen");
    names[pcsBcells] = string("% B cells in spleen");
    names[pcsTconvRagN] = string("% Rag- in splenic Tconv");
    names[pcsTregRagN] = string("% Rag- in splenic Treg");
    names[pcsCD8RagN] = string("% Rag- in CD8");


	// the names of variables that can be accessed by outside (global name-space)
    extNames[ttotal] = GlobalName(N::ttotal);
    extNames[tDN] = GlobalName(N::tDN);
    extNames[tDP] = GlobalName(N::tDP);
    extNames[tSP8] = GlobalName(N::tSP8P);
    extNames[tSP4] = GlobalName(N::tSP4P);
    extNames[tTconv] = GlobalName(N::tTconvP);
    extNames[tTRegP25] = GlobalName(N::tTRegP1P);
    extNames[tTRegPFp3] = GlobalName(N::tTRegP2P);
    extNames[tTreg] = GlobalName(N::tTregP);
    extNames[tSP8RagN] = GlobalName(N::tSP8RagN);
    extNames[tSP4RagN] = GlobalName(N::tSP4RagN);
    extNames[tTconvRagN] = GlobalName(N::tTconvRagN);
    extNames[tTregP1RagN] = GlobalName(N::tTregP1RagN);
    extNames[tTregP2RagN] = GlobalName(N::tTregP2RagN);
    extNames[tTregRagN] = GlobalName(N::tTregRagN);
    extNames[pctDN] =     GlobalName(N::pctDN);
    extNames[pctDP] =  GlobalName(N::pctDP);
    extNames[pctSP8] =  GlobalName(N::pctSP8);
    extNames[pctSP4] =   GlobalName(N::pctSP4);
    extNames[pctTconv] =   GlobalName(N::pctTconvP);
    extNames[pctTRegP1] =  GlobalName(N::pctTRegP1P);
    extNames[pctTRegP2] =  GlobalName(N::pctTRegP2P);
    extNames[pctTreg] = GlobalName(N::pctTregP);
    extNames[pctSP8RagN] =GlobalName(N::pctSP8RagN);
    extNames[pctSP4RagN] = GlobalName(N::pctSP4RagN);
    extNames[pctTconvRagN] = GlobalName(N::pctTconvRagN);
    extNames[pctTRegP1RagN] = GlobalName(N::pctTRegP1RagN);
    extNames[pctTRegP2RagN] = GlobalName(N::pctTRegP2RagN);
    extNames[pctTregRagN] =GlobalName(N::pctTregRagN);
    extNames[stotal] = GlobalName(N::stotal);
    extNames[sTconv] = GlobalName(N::sTconv);
    extNames[sTreg] = GlobalName(N::sTreg);
    extNames[sCD8] = GlobalName(N::sCD8);
    extNames[sBcells] = GlobalName(N::sBcells);
    extNames[sTconvRagN] = GlobalName(N::sTconvRagN);
    extNames[sTregRagN] = GlobalName(N::sTregRagN);
    extNames[sCD8RagN] = GlobalName(N::sCD8RagN);
    extNames[pcsTconv] = GlobalName(N::pcsTconv);
    extNames[pcsTreg] = GlobalName(N::pcsTreg);
    extNames[pcsCD8] = GlobalName(N::pcsCD8);
    extNames[pcsBcells] = GlobalName(N::pcsBcells);
    extNames[pcsTconvRagN] = GlobalName(N::pcsTconvRagN);
    extNames[pcsTregRagN] = GlobalName(N::pcsTregRagN);
    extNames[pcsCD8RagN] = GlobalName(N::pcsCD8RagN);

    // Name of parameters
    paramNames[flu_peak] = "flu_peak / peak of flu effect in days";
    paramNames[flu_std] = "flu_std / width of flu effect (stddev)";
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
    paramNames[in_tTregPFp3] = "in_tTregPFP3 / inflow singer precursors";
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
    paramNames[fracTtoS] = "fracTtoS / frac. of thym out reaching SPL";
    paramNames[dsTconv] = "dsTconv / death splenic Tconv";
    paramNames[dsTreg] = "dsTreg / death splenic Tregs";
    paramNames[dsCD8] = "dsCD8 / death splenic CD8";
    paramNames[dsBcells] = "dsBcells / death splenic B cells";
    paramNames[decayRag] = "decayRag / decay of Rag-GFP";
    paramNames[	hypInflowCoeffETP	]="	hypInflowCoeffETP	";
    paramNames[	hypDeathCoeffDN ]="hypDeathCoeffDN",
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
    paramNames[	hypLessDivDN	]="CoeffDivDN";
    paramNames[	hypLessDivDP	]="CoeffDivDP";
    paramNames[	hypLessDivTregPro25	]="CoeffDivTregPro25";
    paramNames[	hypLessDivTregProFP3	]="CoeffDivTregProFP3";
    paramNames[	hypLessDivDPTreg ] = "CoeffDivDPTreg";
    paramNames[	hypLessDivTconv	]="CoeffDivTconv";
    paramNames[	hypLessDivCD8	]="CoeffDivCD8";
    paramNames[ logisticThymus] = "logisticSizeThymus";
    paramNames[ logisticStrength] = "logisticStrength";



    paramLowBounds[	flu_peak	] = 	5	;				paramUpBounds[	flu_peak	] = 	15	;
    paramLowBounds[	flu_std	] = 	0.5	;				paramUpBounds[	flu_std	] = 	10	;
    paramLowBounds[	fETP_tDN	] = 	0.001	;				paramUpBounds[	fETP_tDN	] = 	1	;
    paramLowBounds[	ptDN	] = 	0.01	;				paramUpBounds[	ptDN	] = 	10	;
    paramLowBounds[	ftDN_tDP	] = 	0.001	;				paramUpBounds[	ftDN_tDP	] = 	10	;
    paramLowBounds[	ptDP	] = 	0.01	;				paramUpBounds[	ptDP	] = 	10	;
    paramLowBounds[	ftDP_tTConv	] = 	0.001	;				paramUpBounds[	ftDP_tTConv	] = 	10	;
    paramLowBounds[	ftDP_tTregP25	] = 	0.001	;				paramUpBounds[	ftDP_tTregP25	] = 	10	;
    paramLowBounds[	ftDP_tTregFP3	] = 	0.001	;				paramUpBounds[	ftDP_tTregFP3	] = 	10	;
    paramLowBounds[	ftDP_tSP8	] = 	0.001	;				paramUpBounds[	ftDP_tSP8	] = 	10	;
    paramLowBounds[	out_tDP	] = 	0.001	;				paramUpBounds[	out_tDP	] = 	10	;
    //paramLowBounds[	in_tDP	] = 	0.0001	;				paramUpBounds[	in_tDP	] = 	1	;
    paramLowBounds[	ptTregP25	] = 	0.01	;				paramUpBounds[	ptTregP25	] = 	10	;
    paramLowBounds[	ftTregP25_tDPTreg	] = 	0.001	;				paramUpBounds[	ftTregP25_tDPTreg	] = 	1	;
    paramLowBounds[	out_tTregP25	] = 	0.001	;				paramUpBounds[	out_tTregP25	] = 	1	;
    paramLowBounds[	ptTregFP3	] = 	0.01	;				paramUpBounds[	ptTregFP3	] = 	10	;
    paramLowBounds[	ftTregFP3_tDPTreg	] = 	0.001	;				paramUpBounds[	ftTregFP3_tDPTreg	] = 	10	;
    paramLowBounds[	out_tTregFP3	] = 	0.001	;				paramUpBounds[	out_tTregFP3	] = 	10	;
    paramLowBounds[	in_tTregPFp3	] = 	0.0001	;				paramUpBounds[	in_tTregPFp3	] = 	1	;
    paramLowBounds[	ptDPTregs	] = 	0.01	;				paramUpBounds[	ptDPTregs	] = 	10	;
    paramLowBounds[	out_tDPTregs	] = 	0.001	;				paramUpBounds[	out_tDPTregs	] = 	10	;
    paramLowBounds[	in_tDPTregs	] = 	0.0001	;				paramUpBounds[	in_tDPTregs	] = 	1	;
    paramLowBounds[	ptTconv	] = 	0.01	;				paramUpBounds[	ptTconv	] = 	10	;
    paramLowBounds[	out_tTconv	] = 	0.001	;				paramUpBounds[	out_tTconv	] = 	10	;
    paramLowBounds[	in_tTconv	] = 	0.0001	;				paramUpBounds[	in_tTconv	] = 	1	;
    paramLowBounds[	ptSP8	] = 	0.01	;				paramUpBounds[	ptSP8	] = 	10	;
    paramLowBounds[	out_SP8	] = 	0.001	;				paramUpBounds[	out_SP8	] = 	10	;
    paramLowBounds[	in_SP8	] = 	0.0001	;				paramUpBounds[	in_SP8	] = 	1	;
    paramLowBounds[	dtDN	] = 	0.001	;				paramUpBounds[	dtDN	] = 	10	;
    paramLowBounds[	dtDP	] = 	0.001	;				paramUpBounds[	dtDP	] = 	10	;
    paramLowBounds[	dtTregP25	] = 	0.001	;				paramUpBounds[	dtTregP25	] = 	10	;
    paramLowBounds[	dtTregFP3	] = 	0.001	;				paramUpBounds[	dtTregFP3	] = 	10	;
    paramLowBounds[	dtDPTregs	] = 	0.001	;				paramUpBounds[	dtDPTregs	] = 	10	;
    paramLowBounds[	dtTconv	] = 	0.001	;				paramUpBounds[	dtTconv	] = 	10	;
    paramLowBounds[	dtSP8	] = 	0.001	;				paramUpBounds[	dtSP8	] = 	10	;
    paramLowBounds[ fracTtoS ]=     0.0001  ;               paramUpBounds[  fracTtoS] =     1.0 ;
    paramLowBounds[	dsTconv	] = 	0.001	;				paramUpBounds[	dsTconv	] = 	10	;
    paramLowBounds[	dsTreg	] = 	0.001	;				paramUpBounds[	dsTreg	] = 	10	;
    paramLowBounds[	dsCD8	] = 	0.001	;				paramUpBounds[	dsCD8	] = 	10	;
    paramLowBounds[	dsBcells	] = 	0.001	;				paramUpBounds[	dsBcells	] = 	10	;
    paramLowBounds[	decayRag	] = 	0.001	;				paramUpBounds[	decayRag	] = 	10	;
    paramLowBounds[	hypInflowCoeffETP	] = 	0.05	;				paramUpBounds[	hypInflowCoeffETP	] = 	20	;
    paramLowBounds[	hypDeathCoeffDN  ] = 0.05;                      paramUpBounds[	hypDeathCoeffDN	] = 	20	;
    paramLowBounds[	hypDeathCoeffDP	] = 	0.05	;				paramUpBounds[	hypDeathCoeffDP	] = 	20	;
    paramLowBounds[	hypDeathCoeffTconv	] = 	0.05	;				paramUpBounds[	hypDeathCoeffTconv	] = 	20	;
    paramLowBounds[	hypDeathCoeffProFp3	] = 	0.05	;				paramUpBounds[	hypDeathCoeffProFp3	] = 	20	;
    paramLowBounds[	hypDeathCoeffPro25	] = 	0.05	;				paramUpBounds[	hypDeathCoeffPro25	] = 	20	;
    paramLowBounds[	hypDeathCoeffDPTregs	] = 	0.05	;				paramUpBounds[	hypDeathCoeffDPTregs	] = 	20	;
    paramLowBounds[	hypDeathCoeffSP8	] = 	0.05	;				paramUpBounds[	hypDeathCoeffSP8	] = 	20	;
    paramLowBounds[	hypOutputCoeffOutDP	] = 	0.05	;				paramUpBounds[	hypOutputCoeffOutDP	] = 	20	;
    paramLowBounds[	hypOutputCoeffOutTconv	] = 	0.05	;				paramUpBounds[	hypOutputCoeffOutTconv	] = 	20	;
    paramLowBounds[	hypOutputCoeffOutDPTregs	] = 	0.05	;				paramUpBounds[	hypOutputCoeffOutDPTregs	] = 	20	;
    paramLowBounds[	hypOutputCoeffOutProFP3	] = 	0.05	;				paramUpBounds[	hypOutputCoeffOutProFP3	] = 	20	;
    paramLowBounds[	hypOutputCoeffOutPro25	] = 	0.05	;				paramUpBounds[	hypOutputCoeffOutPro25	] = 	20	;
    paramLowBounds[	hypOutputCoeffOutSP8	] = 	0.05	;				paramUpBounds[	hypOutputCoeffOutSP8	] = 	20	;
    paramLowBounds[	hypFasterCoeffDNtoDP	] = 	0.05	;				paramUpBounds[	hypFasterCoeffDNtoDP	] = 	20	;
    paramLowBounds[	hypFasterCoeffProFP3	] = 	0.05	;				paramUpBounds[	hypFasterCoeffProFP3	] = 	20	;
    paramLowBounds[	hypFasterCoeffPro25	] = 	0.05	;				paramUpBounds[	hypFasterCoeffPro25	] = 	20	;
    paramLowBounds[	hypFasterCoeffTconv	] = 	0.05	;				paramUpBounds[	hypFasterCoeffTconv	] = 	20	;
    paramLowBounds[	hypFasterCoeffSP8	] = 	0.05	;				paramUpBounds[	hypFasterCoeffSP8	] = 	20	;
    paramLowBounds[	hypSpaceOutputCoeff	] = 	0.05	;				paramUpBounds[	hypSpaceOutputCoeff	] = 	20	;
    paramLowBounds[	hypLessDivDN	] = 	0.01	;				paramUpBounds[hypLessDivDN	] = 	20	;
    paramLowBounds[	hypLessDivDP	] = 	0.01	;				paramUpBounds[hypLessDivDP] = 	20	;
    paramLowBounds[	hypLessDivTregPro25	] = 	0.01	;				paramUpBounds[hypLessDivTregPro25] = 	20	;
    paramLowBounds[	hypLessDivTregProFP3	] = 	0.01	;				paramUpBounds[hypLessDivTregProFP3] = 	20	;
    paramLowBounds[	hypLessDivDPTreg	] = 	0.01	;				paramUpBounds[hypLessDivDPTreg] = 20;
    paramLowBounds[	hypLessDivTconv	] = 	0.01	;				paramUpBounds[hypLessDivTconv] = 	20	;
    paramLowBounds[	hypLessDivCD8	] = 	0.01	;				paramUpBounds[hypLessDivCD8] = 	20	;
    paramLowBounds[ logisticThymus ] = 0.1;                         paramUpBounds[logisticThymus] = 500;
    paramLowBounds[ logisticStrength] = 0.1;                        paramUpBounds[logisticStrength] = 10;
}

void modele1ThymusSpleen::setBaseParameters(){
    background = Back::WT;
	params.clear();     // to make sure they are all put to zero
    params.resize(NbParameters, 0.0);

    params[flu_peak] = 9;
    params[flu_std] = 2.5;
    params[	fETP_tDN	] = 	0.05	;
    params[	ptDN	] = 	0.05	;
    params[	ftDN_tDP	] = 	0.1	;
    params[	ptDP	] = 	0.01	;
    params[	ftDP_tTConv	] = 	0.1	;
    params[	ftDP_tTregP25	] = 	0.005	;
    params[	ftDP_tTregFP3	] = 	0.005	;
    params[	ftDP_tSP8	] = 	0.05	;
    params[	out_tDP	] = 	0.005	;
    //params[	in_tDP	] = 	0.005	;
    params[	ptTregP25	] = 	0.01	;
    params[	ftTregP25_tDPTreg	] = 	0.05	;
    params[	out_tTregP25	] = 	0.05	;
    params[	ptTregFP3	] = 	0.001	;
    params[	ftTregFP3_tDPTreg	] = 	0.05	;
    params[	out_tTregFP3	] = 	0.05	;
    params[	in_tTregPFp3	] = 	0.05	;
    params[	ptDPTregs	] = 	0.001	;
    params[	out_tDPTregs	] = 	0.08	;
    params[	in_tDPTregs	] = 	0.01	;
    params[	ptTconv	] = 	0.001	;
    params[	out_tTconv	] = 	0.05	;
    params[	in_tTconv	] = 	0.01	;
    params[	ptSP8	] = 	0.001	;
    params[	out_SP8	] = 	0.05	;
    params[	in_SP8	] = 	0.0008	;
    params[	dtDN	] = 	0.03	;
    params[	dtDP	] = 	0.03	;
    params[	dtTregP25	] = 	0.03	;
    params[	dtTregFP3	] = 	0.03	;
    params[	dtDPTregs	] = 	0.03	;
    params[	dtTconv	] = 	0.03	;
    params[	dtSP8	] = 	0.03	;
    params[ fracTtoS] =     0.5;
    params[	dsTconv	] = 	0.03	;
    params[	dsTreg	] = 	0.03	;
    params[	dsCD8	] = 	0.03	;
    params[	dsBcells	] = 	0.03	;
    params[	decayRag	] = 	0.01	;
    params[	hypInflowCoeffETP	] = 	0.3	;
    params[	hypDeathCoeffDN ] = 5;
    params[	hypDeathCoeffDP	] = 	10	;
    params[	hypDeathCoeffTconv	] = 	1	;
    params[	hypDeathCoeffProFp3	] = 	1	;
    params[	hypDeathCoeffPro25	] = 	1	;
    params[	hypDeathCoeffDPTregs	] = 	1	;
    params[	hypDeathCoeffSP8	] = 	1	;
    params[	hypOutputCoeffOutDP	] = 	0.2	;
    params[	hypOutputCoeffOutTconv	] = 	1	;
    params[	hypOutputCoeffOutDPTregs	] = 	1	;
    params[	hypOutputCoeffOutProFP3	] = 	1	;
    params[	hypOutputCoeffOutPro25	] = 	1	;
    params[	hypOutputCoeffOutSP8	] = 	1	;
    params[	hypFasterCoeffDNtoDP	] = 	1	;
    params[	hypFasterCoeffProFP3	] = 	5	;
    params[	hypFasterCoeffPro25	] = 	1	;
    params[	hypFasterCoeffTconv	] = 	1	;
    params[	hypFasterCoeffSP8	] = 	1	;
    params[	hypSpaceOutputCoeff	] = 	0.2	;
    params[	hypLessDivDN	] = 	0.2	;
    params[	hypLessDivDP	] = 	0.2	;
    params[	hypLessDivTregPro25	] = 	1	;
    params[	hypLessDivTregProFP3	] = 	1	;
    params[	hypLessDivDPTreg] = 1;
    params[	hypLessDivTconv	] = 	0.35	;
    params[	hypLessDivCD8	] = 	0.35	;
    params[ logisticThymus ] = 90;
    params[ logisticStrength] = 2.0;

	setBaseParametersDone();
}

void modele1ThymusSpleen::initialise(long long _background){ // don't touch to parameters !
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
    if(background == Back::WT){}
    if(background == Back::B_ReducedInflow){}
    if(background == Back::B_MoreDeath){}
    if(background == Back::B_MoreOutputThymus){}
    if(background == Back::B_FasterDifferentiation){}
    if(background == Back::B_SpaceDependentOutput){}
    if(background == Back::B_DivisionReduced){}
    if(background == Back::B_AllCombined){}





    //if(background == Back::M2){}
    //if(background == Back::TCRGATA3NEGKO){   params[KTCRGATA3]   = 0;} // for different options i.e. deficiency in something


    // if the initial values depend on parameters
    /*init[IL2] = params[IL2EQ];
    init[IL4] = params[IL4EQ];*/

    init[tDN] = 3.7; //3.5e7; //3e6;
    init[tDP] = 60; //100e6;
    init[tTconv] = 8.5; //12e6;
    init[tTRegP25] = 0.046; //5.8e6; //50000;
    init[tTRegPFp3] = 0.18; ///1.1e6;//50000; // changed
    init[tTreg] = 0.22; //8e6;//1e6;
    init[tSP8] = 3.3; //5e6; //1.3e8; //5e6;
    init[sTreg] = 1.3;
    init[sTconv] = 10;
    init[sCD8] = 7.5;
    init[sBcells] = 25;

    init[tSP8RagN] = 0.250;
    init[tSP4RagN] = 0.600;
    init[tTconvRagN] = 0.45; // useless, will be the sum
    init[tTregP1RagN] = 0.0025;
    init[tTregP2RagN] = 0.035;
    init[tTregRagN] = 0.088;
    init[sTconvRagN] = 3.6;
    init[sTregRagN] = 1;
    init[sCD8RagN] = 4;
    //init[tSP4] = init[tTconv] + init[tTRegP25] + init[tTRegPFp3] + init[tDPTreg];

    params[ptDN] = params[ftDN_tDP] +  params[dtDN] - params[fETP_tDN] / init[tDN];
    params[ptDP] = - (init[tDN] * params[ftDN_tDP]) / init[tDP]  + params[out_tDP]  + params[ftDP_tTConv] + params[ftDP_tTregP25] + params[ftDP_tTregFP3] + params[ftDP_tSP8] + params[dtDP];
    params[ptTconv] = -(params[in_tTconv] * init[sTconv]  + init[tDP]  * params[ftDP_tTConv]) / init[tTconv] + params[out_tTconv]  + params[dtTconv];



    params[ptTregP25] = - init[tDP] * params[ftDP_tTregP25] / init[tTRegP25]  + params[out_tTregP25] + params[ftTregP25_tDPTreg] + params[dtTregP25];
    params[ptTregFP3] = (- params[in_tTregPFp3] - init[tDP] * params[ftDP_tTregFP3]) / init[tTRegPFp3] + params[out_tTregFP3] + params[ftTregFP3_tDPTreg] + params[dtTregFP3];
    params[ptDPTregs] = (- params[in_tDPTregs] - init[tTRegP25] * params[ftTregP25_tDPTreg] - init[tTRegPFp3] * params[ftTregFP3_tDPTreg]) / init[tTreg] +
            params[out_tDPTregs] + params[dtDPTregs];
    params[ptSP8] = (- params[in_SP8] * init[sCD8] -  init[tDP] * params[ftDP_tSP8]) / init[tSP8] +
            params[out_SP8] + params[dtSP8];

    //cerr << "Initializing from new parameter values ..." << endl;
    if(params[ptDN] < 0){
        //cerr << "ERR: the initial conditions + parameters don't allow the parameter [ptDN] to be positive / allow steady state" << endl;
        //cerr << "     Please put params[fETP_tDN] < " << (params[ftDN_tDP] +  params[dtDN]) * init[tDN] << " instead of " << params[fETP_tDN] << endl;
        params[ptDN] = 0;
    }

    if(params[ptDP] < 0){
        //cerr << "ERR: the initial conditions + parameters don't allow the parameter [ptDP] to be positive / allow steady state" << endl;
        //cerr <<"     Please, put params[ftDN_tDP] < " << init[tDP] *
        //        (params[dtDP] + params[ptDP] + params[ftDP_tTConv] + params[ftDP_tTregP25] + params[ftDP_tTregFP3] + params[ftDP_tSP8] + params[out_tDP])
        //        / init[tDN] << " instead of " << params[ftDN_tDP] << endl;
        params[ptDP] = 0;
    }

    if(params[ptTconv] < 0){
        //cerr << "ERR: the initial conditions + parameters don't allow the parameter [ptTconv] to be positive / allow steady state" << endl;
        //
        //cerr << "     Please, put params[ftDP_tTConv]) < " <<
        //        (- params[in_tTconv] + init[tTconv] * params[out_tTconv] + params[dtTconv]) / init[tDP] << " instead of " << params[ftDP_tTConv] << endl;
        params[ptTconv] = 0;
    }

    if(params[ptTregP25] < 0){
        //cerr << "ERR: the initial conditions + parameters don't allow the parameter [ptTregP25] to be positive / allow steady state" << endl;
        //cerr << "     Please, put params[ftDP_tTregP25] < " << init[tTRegP25] * (params[out_tTregP25] + params[ftTregP25_tDPTreg] + params[dtTregP25]) / init[tDP] << endl;
        params[ptTregP25] = 0;
    }

    if(params[ptTregFP3] < 0){
        //cerr << "ERR: the initial conditions + parameters don't allow the parameter [ptTregP25] to be positive / allow steady state" << endl;
        //cerr << "     Please, put params[ftDP_tTregFP3] < " << init[tTRegPFp3] * (params[out_tTregFP3] + params[ftTregFP3_tDPTreg] + params[dtTregFP3]) /  init[tDP] << endl;
        params[ptTregFP3] = 0;
    }

    if(params[ptDPTregs] < 0){
        //cerr << "ERR: the initial conditions + parameters don't allow the parameter [ptDPTregs] to be positive / allow steady state" << endl;


        /*params[ptDPTregs] = (- params[in_tDPTregs] - init[tTRegP25] * params[ftTregP25_tDPTreg] - init[tTRegPFp3] * params[ftTregFP3_tDPTreg]) / init[tDPTreg] +
                params[out_tDPTregs] + params[dtDPTregs];
        params[ptSP8] = (- params[in_SP8] -  init[tDP] * params[ftDP_tSP8]) / init[tSP8] +
                params[out_SP8] + params[dtSP8];*/

        params[ptDPTregs] = 0;
    }

    if(params[ptSP8] < 0){
        //cerr << "ERR: the initial conditions + parameters don't allow the parameter [ptSP8] to be positive / allow steady state" << endl;
        params[ptSP8] = 0;
    }

    for(int i = 0; i < NbVariables; ++i){
		val[i] = init[i];}
    //val[tDP] = 0;
	t = 0;
	initialiseDone();
}


void modele1ThymusSpleen::updateDerivedVariables(){
        //val[pctSP8RagN] = 100 * min(1.0, val[] / max(1e-8, val[]));
    val[tSP4] =  val[tTconv] + val[tTRegP25] + val[tTRegPFp3] + val[tTreg];
    val[ttotal] = val[tDN] + val[tDP] + val[tSP8] + val[tSP4];
    val[tSP4RagN] = val[tTregRagN] + val[tTregP2RagN] + val[tTconvRagN];
    val[pctDN] =  100 * min(1.0, val[tDN] / max(1e-8, val[ttotal]));
    val[pctDP] =  100 * min(1.0, val[tDP] / max(1e-8, val[ttotal]));
    val[pctSP8] = 100 * min(1.0, val[tSP8] / max(1e-8, val[ttotal]));
    val[pctSP4] = 100 * min(1.0, val[tSP4] / max(1e-8, val[ttotal]));
    val[pctTconv] = 100 * min(1.0, val[tTconv] / max(1e-8, val[tSP4]));
    val[pctTRegP1] = 100 * min(1.0, val[tTRegP25] / max(1e-8, val[tSP4]));
    val[pctTRegP2] = 100 * min(1.0, val[tTRegPFp3] / max(1e-8, val[tSP4]));
    val[pctTreg] = 100 * min(1.0, val[tTreg] / max(1e-8, val[tSP4]));
    val[pctSP8RagN] = 100 * min(1.0, val[tSP8RagN] / max(1e-8, val[tSP8]));
    val[pctSP4RagN] = 100 * min(1.0, val[tSP4RagN] / max(1e-8, val[tSP4]));
    val[pctTconvRagN] = 100 * min(1.0, val[tTconvRagN] / max(1e-8, val[tTconv]));
    val[pctTRegP1RagN] = 100 * min(1.0, val[tTregP1RagN] / max(1e-8, val[tTRegP25]));
    val[pctTRegP2RagN] = 100 * min(1.0, val[tTregP2RagN] / max(1e-8, val[tTRegPFp3]));
    val[pctTregRagN] = 100 * min(1.0, val[tTregRagN] / max(1e-8, val[tTreg]));
    val[stotal] = val[sTconv] + val[sTreg] + val[sCD8] + val[sBcells];
    val[pcsTconv] = 100 * min(1.0, val[sTconv] / max(1e-8, val[stotal]));
    val[pcsTreg] = 100 * min(1.0, val[sTreg] / max(1e-8, val[stotal]));
    val[pcsCD8] = 100 * min(1.0, val[sCD8] / max(1e-8, val[stotal]));
    val[pcsBcells] = 100 * min(1.0, val[sBcells] / max(1e-8, val[stotal]));
    val[pcsCD8RagN] = 100 * min(1.0, val[sCD8RagN] / max(1e-8, val[sCD8]));
    val[pcsTregRagN] = 100 * min(1.0, val[sTregRagN] / max(1e-8, val[sTreg]));
    val[pcsTconvRagN] = 100 * min(1.0, val[sTconvRagN] / max(1e-8, val[sTconv]));

    val[flu] = exp(-(t - params[flu_peak]) * (t - params[flu_peak]) / (params[flu_std] * params[flu_std]));
}

void modele1ThymusSpleen::derivatives(const vector<double> &x, vector<double> &dxdt, const double t){

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
    double          DeathCoeffDN = 1;
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

    double          LessDivCoeffDN = 1;
    double          LessDivCoeffDP = 1;
    double          LessDivCoeffTregPro25 = 1;
    double          LessDivCoeffTregProFP3 = 1;
    double          LessDivCoeffDPTreg = 1;
    double          LessDivCoeffTconv = 1;
    double          LessDivCoeffCD8 = 1;

            // Change: put a logical or/and
    if(background & Back::B_ReducedInflow){
        InflowCoeffETP = 1 * (1 - x[flu]) + x[flu] * params[hypInflowCoeffETP];
    }
    if(background & Back::B_MoreDeath){
        DeathCoeffDN         = 1 * (1 - x[flu]) + x[flu] * params[hypDeathCoeffDN];
        DeathCoeffDP         = 1 * (1 - x[flu]) + x[flu] * params[hypDeathCoeffDP];
        DeathCoeffTconv      = 1 * (1 - x[flu]) + x[flu] * params[hypDeathCoeffTconv];
        DeathCoeffProFp3     = 1 * (1 - x[flu]) + x[flu] * params[hypDeathCoeffProFp3];
        DeathCoeffPro25      = 1 * (1 - x[flu]) + x[flu] * params[hypDeathCoeffPro25];
        DeathCoeffDPTregs    = 1 * (1 - x[flu]) + x[flu] * params[hypDeathCoeffDPTregs];
        DeathCoeffSP8        = 1 * (1 - x[flu]) + x[flu] * params[hypDeathCoeffSP8];
    }
    if(background & Back::B_MoreOutputThymus){
        OutputCoeffOutDP	= 1 * (1 - x[flu]) + x[flu] * params[	hypOutputCoeffOutDP	];
        OutputCoeffOutTconv	= 1 * (1 - x[flu]) + x[flu] * params[	hypOutputCoeffOutTconv	];
        OutputCoeffOutDPTregs	= 1 * (1 - x[flu]) + x[flu] * params[	hypOutputCoeffOutDPTregs	];
        OutputCoeffOutProFP3	= 1 * (1 - x[flu]) + x[flu] * params[	hypOutputCoeffOutProFP3	];
        OutputCoeffOutPro25	= 1 * (1 - x[flu]) + x[flu] * params[	hypOutputCoeffOutPro25	];
        OutputCoeffOutSP8	= 1 * (1 - x[flu]) + x[flu] * params[	hypOutputCoeffOutSP8	];
    }
    if(background & Back::B_FasterDifferentiation){
        FasterCoeffDNtoDP	= 1 * (1 - x[flu]) + x[flu] * params[	hypFasterCoeffDNtoDP	];
        FasterCoeffProFP3	= 1 * (1 - x[flu]) + x[flu] * params[	hypFasterCoeffProFP3	];
        FasterCoeffPro25	= 1 * (1 - x[flu]) + x[flu] * params[	hypFasterCoeffPro25	];
        FasterCoeffTconv	= 1 * (1 - x[flu]) + x[flu] * params[	hypFasterCoeffTconv	];
        FasterCoeffSP8	= 1 * (1 - x[flu]) + x[flu] * params[	hypFasterCoeffSP8	];
    }
    if(background & Back::B_SpaceDependentOutput){
        SpaceOutputCoeff  = 1 * (1 - x[flu]) + x[flu] * params[hypSpaceOutputCoeff];
    }
    if(background & Back::B_DivisionReduced){
        LessDivCoeffDN = 1 * (1 - x[flu]) + x[flu] * params[hypLessDivDN];
        LessDivCoeffDP = 1 * (1 - x[flu]) + x[flu] * params[hypLessDivDP];
        LessDivCoeffTregPro25 = 1 * (1 - x[flu]) + x[flu] * params[hypLessDivTregPro25];
        LessDivCoeffTregProFP3 = 1 * (1 - x[flu]) + x[flu] * params[hypLessDivTregProFP3];
        LessDivCoeffDPTreg = 1 * (1 - x[flu]) + x[flu] * params[hypLessDivDPTreg],
        LessDivCoeffTconv = 1 * (1 - x[flu]) + x[flu] * params[hypLessDivTconv];
        LessDivCoeffCD8 = 1 * (1 - x[flu]) + x[flu] * params[hypLessDivCD8];
    }

//    double coeff = 2*(1 - (0.5*x[ttotal] / (init[tDN] + init[tDP] + init[tTconv] + init[tTRegP25] + init[tTRegPFp3] + init[tTreg] + init[tSP8] + 1e-9)));
    double coeff = (1/(1 - 1 / (params[logisticStrength]+1e-9)))*(1 - ((1/(params[logisticStrength] + 1e-9))*x[ttotal] / (params[logisticThymus] + 1e-9)));
    //cout << coeff << endl;
    if(background & Back::B_LogisticTotalProlif){
        LessDivCoeffDN *= coeff;
        LessDivCoeffDP *= coeff;
        LessDivCoeffTregPro25 *= coeff;
        LessDivCoeffTregProFP3 *= coeff;
        LessDivCoeffDPTreg *= coeff;
        LessDivCoeffTconv *= coeff;
        LessDivCoeffCD8 *= coeff;
    }


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

}
