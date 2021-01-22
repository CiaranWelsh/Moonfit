/**
 * Written by Ciaran welsh in attempt to get the optimizer code working
 */

#include "moonfit.h"

/// Example of a minimalistic model :
/// for simulating : Creation: --(KF)--> A --(K12)--> B --(K23)--> C --(KFB)--| A,
///                  with respecitve death/degradation rates KD1, KD2, KD3 for A,B and C
///                  and with a mutant where K12 is modified into K12m
///
/*
 * This example is taken from the comments in modele.h (with minor adjustments) to get it to work
 */
struct ModelA1 : public Model {
    enum {
        A, B, C, NBVAR
    };                            // List of variables
    enum {
        KF, KD1, KD2, KD3, K12, K23, KFB, K12m, NBPARAM
    };    // List of parameters
    enum {
        WT, MUT, NBBACK
    };                         // List of backgrounds
    long long background;
    std::vector<double> valTemp;

    ModelA1() : Model(NBVAR, NBPARAM), background(WT) {
        names[A] = string("PopA");
        names[B] = string("PopB");
        names[C] = string("PopC");
    }


    void initialise(long long _background) override {
        background = _background;
        val.clear();
        val.resize(NBVAR, 0.0);        // to erase previous values
        valTemp.clear();
        valTemp.resize(NBVAR, 0.0);
        init.clear();
        init.resize(NBVAR, 0.0);
        for (int i = 0; i < NBVAR; ++i) { val[i] = init[i]; }
        t = 0;
        initialiseDone();
    }

    void setBaseParameters() override {
        params.clear();
        params.resize(NBPARAM);     // to erase previous values
        params[KF] = 1e-3;
        params[KD1] = 1e-4;
        params[KD2] = 1e-6;
        params[KD3] = 1e-6;
        params[K12] = 1e-6;
        params[K23] = 1e-5;
        params[KFB] = 0.1;
        params[K12m] = 1e-4;
        setBaseParametersDone();
    }

    void derivatives(const vector<double> &x, vector<double> &dxdt, double t) override{
        // pK12 encodes model variants
        double pK12 = (background == WT) ? params[K12] : params[K12m];
        dxdt[A] = (params[KF] * (1 - x[C] / params[KFB]) - (params[KD1] + pK12) * x[A]);
        dxdt[B] = (pK12 * x[A] - (params[KD2] + params[K23]) * x[B]);
        dxdt[C] = (params[K23] * x[B] - params[KD3] * x[C]);
    }

    static int main (){
        // To perform simulations with this model (see below for 'simulate'):
        Evaluator evaluator;
        ModelA1 A1;
        A1.setBaseParameters();
        // or : A.loadParameters(string("Params.txt"));, where Params.txt contains "8\t1e-3\t1e-4\t1e-6\t1e-6\t1e-6\t1e-5\t0.1\t1e-4\n"
        A1.initialise(ModelA1::WT);
        A1.simulate(100, &evaluator);
        A1.initialise(ModelA1::MUT);
        A1.simulate(100, &evaluator);

        // work out how to view the data

        std::cout << A1.print() << std::endl;
        return 0;
    }
};


int main() {

    ModelA1::main();


}



















