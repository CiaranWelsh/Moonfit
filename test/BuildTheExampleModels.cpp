
#include "moonfit.h"

int main() {
    struct ModelA1 : public Model {
        ModelA1();

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

        void initialise(long long _background = WT);

        void setBaseParameters();

        void one_step(double _t, double _delta_t);
    };

}



















