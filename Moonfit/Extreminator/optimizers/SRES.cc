#include "SRES.h" 

SRES::SRES(BaseOptimizationProblem *S, const std::string &file) :BaseOptimizer(S,file) {
	if (numArguments() !=  1) { std::cerr << "Bad argument number (" << numArguments() << ")\n"; exit(-1);};
	num_tries = (int) argument(0);
}

SRES::SRES(BaseOptimizationProblem *S, std::ifstream &F_IN) : BaseOptimizer(S,F_IN) {
	if (numArguments() !=  1) { std::cerr << "Bad argument number (" << numArguments() << ")\n"; exit(-1);};
	num_tries = (int) argument(0);
}

SRES* CurrentClass = nullptr;
individual* CurrentIndividual = nullptr;

void cost(double *x, double *f, double *g){
	for(size_t i = 0; i < CurrentClass->numIndex(); ++i){
		CurrentIndividual->setGene(i, x[i]); 
        //std::cerr << "SRES gave " << i << ", " << x[i] << std::endl;
	}
	CurrentClass->updateCost(CurrentIndividual);
	*f = CurrentIndividual->cost();	
}

double doNothingTransform(double x){
	return x;
}

void SRES::optimize(){
	CurrentClass = this;
	CurrentIndividual = new individual();
	CurrentIndividual->resize(numIndex());
	//std::cerr << setiosflags(std::ios::fixed);
	resetCostCalls();
	
	int i;
	ESParameter *param;
	ESPopulation *population;
	ESStatistics *stats;
	ESfcnTrsfm *trsfm;
	unsigned int seed;
	int es;
	int constraint, dim;
	double *ub, *lb;
	int miu, lambda, gen;
	double gamma, alpha, varphi;
	int retry;
	double pf;

	seed = shareDefSeed;
	gamma = esDefGamma;
	alpha = esDefAlpha;
	varphi = esDefVarphi;
	retry = esDefRetry;
	pf = essrDefPf;
	es = esDefESPlus;//ou esDefESPlus
	
	constraint = 0;
	dim = numIndex();
	miu = 30;
	lambda = 200;
	gen = 1750;
	ub = NULL;
	lb = NULL;
	ub = ShareMallocM1d(dim);
	lb = ShareMallocM1d(dim);
	trsfm = (ESfcnTrsfm *)ShareMallocM1c(dim*sizeof(ESfcnTrsfm));

	for(int j = 0; j < dim; ++j){
		lb[j] = paraLowVector(j); 
		ub[j] = paraHighVector(j);
	}
	
	for(i=0;i<dim;i++)
		trsfm[i] = doNothingTransform;

	ESInitial(seed, &param, trsfm, cost, es,constraint, dim, ub, lb,  \
		miu, lambda, gen, gamma, alpha, varphi,  \
		retry, &population, &stats);

	while(stats->curgen < param->gen)
	{
	    //(CW) multithreading opportunity
        ESStep(&population, &param, &stats, pf);
        if(nbCostCalls() > num_tries) break;
	}

	ESDeInitial(param, population, stats);

	ShareFreeM1d(ub);
	ub = NULL;
	ShareFreeM1d(lb);
	lb = NULL;
	ShareFreeM1c((char*)trsfm);
	trsfm = NULL;

	delete CurrentIndividual;
	return;
}
