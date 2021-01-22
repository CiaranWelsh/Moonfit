#include "fitteInterface.h"

Fitte::Fitte(Experiment* _Exp) : GeneralImplementation(_Exp->m->getNbParams()), ExpToOpt(_Exp) {
    #ifndef WITHOUT_QT
    window = new simuWin(_Exp);
    std::cerr << " Is this called ?? " << std::endl;
    #endif
}

double Fitte::getCost(){
    int nbParamsModel = ExpToOpt->m->getNbParams();
    std::cout << "\tParams:";
    for(int i = 0; i < nbParamsModel; ++i){
        if(parameters[i] != 0.0) ExpToOpt->m->setParam(i, parameters[i]);
        std::cout << "\t" << parameters[i];
    }
    #ifndef WITHOUT_QT
    window->updateParmsFromModel();     /// to display on the screen the new values.
    #endif
    double v2 = ExpToOpt->costVariableInModel();
    std::cout << "\nCost: " << v2 + ExpToOpt->m->penalities;
    std::cout << "\tDont_Penalty:\t" << ExpToOpt->m->penalities << std::endl;
    return v2 + ExpToOpt->m->penalities;
}

void Optimize(string optimizerFile, Experiment* _Exp)
{

    std::cerr << "Starting fitting\n";
    // std::string optimizerFile = string("Opt.txt"); //argv[1];
    myRandom::Randomize();
    myTimes::getTime();
    BaseOptimizationProblem *E = new Fitte(_Exp);
    BaseOptimizer *Opt = BaseOptimizer::createOptimizer(E, optimizerFile);
    //mySignal::addOptimizer(Opt);
    Opt->optimize();
    Opt->bestGlobal.print();
    //delete E; // program destructor first...
    delete Opt;
}






// =============== Old pieces of code and tries to make multiple threads ====================

/*Model2 m2;
m2.initialise();
m2.setBaseParameters();
vector<double> reconstitute(m2.NBPARAM, 0.0);
for(int i = 0; i < m2.NBPARAM; ++i){
    reconstitute[i] = m2.params[i];
    std::cerr << i << "\t" << m2.params[i]<< std::endl;
}
std::cerr << "--------------------------\n";
//sleep(1);
for(int i = 0; i < Opt->bestGlobal.size(); ++i){
    std::cerr << Opt->indexVector_[i] << "\t" << Opt->bestGlobal.gene(i) << std::endl;
    reconstitute[Opt->indexVector_[i]] = Opt->bestGlobal.gene(i);
}
//std::cerr << "Fini1" << std::endl;
//sleep(2);
std::cerr << "Best individual, initial problem scale\n";
for(int i =0; i < m2.NBPARAM; ++i){
    std::cerr << reconstitute[i] << std::endl;
    //sleep(1);
}*/

//Delete simulator and optimizer


/*class Worker : public QObject {
    Q_OBJECT

public:
    Worker();
    ~Worker();

public slots:
    void process();

signals:
    void finished();
    void error(QString err);

private:
    // add your variables here
};


// --- CONSTRUCTOR ---
Worker::Worker() {
    // you could copy data from constructor arguments to internal variables here.
}

// --- DECONSTRUCTOR ---
Worker::~Worker() {
    // free resources
}

// --- PROCESS ---
// Start processing data.
void Worker::process() {
    // allocate resources using new here
    qDebug("Hello World!");
    emit finished();
}*/
