import os
import glob
import ctypes as ct
import sys
from typing import List


class _Util:

    def __init__(self):
        self._lib = self.load_lib()

    def _get_shared_library_extension(self):
        if sys.platform == "linux":
            return ".so"
        elif sys.platform == "win32":
            return ".dll"
        elif sys.platform == "darwin":
            return ".dylib"

    def _find_sres_dll(self):
        # somewhere in the subdirectory
        this_directory = os.path.join(os.path.dirname(__file__))
        one_directory_up = os.path.dirname(this_directory)

        dlls = glob.glob(os.path.join(one_directory_up, "**/*SRES*" + self._get_shared_library_extension()))
        if len(dlls) == 0:
            raise ValueError("SRES library not found")
        elif len(dlls) > 1:
            raise ValueError(f"Too may SRES libraries found: {dlls}")
        print(f"SRES library found ar {dlls[0]}")
        return dlls[0]

    def load_lib(self):
        """
        Load the libOmexMeta C API binary. This methods incorporates
        flexibility to load libOmexMeta from multiple locations and works
        from the source, binary and install trees and under site-pacakges.
        Returns:

        """
        shared_lib = self._find_sres_dll()
        lib = ct.CDLL(shared_lib)
        return lib

    def load_func(self, funcname: str, argtypes: List, return_type) -> ct.CDLL._FuncPtr:
        func = self._lib.__getattr__(funcname)
        func.restype = return_type
        func.argtypes = argtypes
        return func


# instantiate util which loads the library
util = _Util()


# now we can use Util.load_func

class _SRES:
    """
    """

    """
    /**
     * @brief (CW) Create a pointer to the ESParameter struct. Variables within the
     * ESParameter struct remain uninitialized (see SRES.cc, optimize). A pointer to
     * ESParameter* is used as input to ESInitial, which (presumably) populates it.
     * @details It seems that we cannot export a struct like we can a class so instead
     * we (CW) create a quick constructor to create a pointer for ESParameter. The @return
     * ESparameter* type is dynamically allocated and must be free'd with freeESParameter()
     * @author (CW)
     */
    """

    # ESParameter *makeESParameter();
    makeESParameter = util.load_func(
        funcname="makeESParameter",
        argtypes=[],  # void
        return_type=ct.c_uint64  # return type: ESParameter*
    )

    # ESParameter ** makeESParameterPtrPtr();
    freeESParameter = util.load_func(
        funcname="freeESParameter",
        argtypes=[],  # void
        return_type=ct.c_uint64  # return type: ESParameter**
    )

    # ESfcnFG * getCostFunPtr()
    getCostFunPtr = util.load_func(
        funcname="getCostFunPtr",
        argtypes=[],
        return_type=ct.c_uint64
    )

    # void freeCostFunPtr(ESfcnFG * f)
    freeCostFunPtr = util.load_func(
        funcname="getCostFunPtr",
        argtypes=[ct.c_uint64],
        return_type=None
    )

    # ESfcnTrsfm * getTransformFun()
    getTransformFun = util.load_func(
        funcname="getTransformFun",
        argtypes=[],
        return_type=ct.c_uint64
    )

    # void freeTransformFun(ESfcnTrsfm * fun)

    freeTransformFun = util.load_func(
        funcname="freeTransformFun",
        argtypes=[ct.c_uint64],
        return_type=None
    )
    """
    /*********************************************************************
     ** initialize: parameters,populations and random seed              **
     ** ESInitial(seed, param,trsfm, fg,es,constraint,dim,ub,lb,miu,    **
     **            lambda,gen, gamma, alpha, varphi, retry,             **
     **             population, stats)                                  **
     ** seed: random seed, usually esDefSeed=0 (pid*time)               **
     ** outseed: seed value assigned , for next use                     **
     ** param: point to parameter                                       **
     ** fg: functions of fitness and constraints                        **
     ** trsfm: to transform sp/op                                       **
     ** es: ES process, esDefESPlus/esDefESSlash                        **
     ** constraint: number of constraints                               **
     ** dim: dimension/number of genes in genome                        **
     ** ub[dim]: up bounds                                              **
     ** lb[dim]: low bounds                                             **
     ** miu: parent/population size                                     **
     ** lambda: offsping/population size                                **
     ** gen: number of generations                                      **
     ** gamma: usually esDefGamma=0.85                                  **
     ** alpha: usually esDefAlpha=0.2                                   **
     ** chi: chi = 1/2n +1/2sqrt(n)                                     **
     ** varphi: = sqrt((2/chi)*log((1/alpha)*(exp(varphi^2*chi/2)       **
     **                  -(1-alpha))))                                  **
     **         expected rate of convergence                            **
     ** retry: retry times to check bounds                              **
     ** tau: learning rates: tau = varphi/(sqrt(2*sqrt(dim)))           **
     ** tar_: learning rates: tau_ = varphi((sqrt(2*dim)                **
     ** population: point to this population                            **
     ** stats: point to statistics                                      **
     **                                                                 **
     ** ESDeInitial(param,populationi,stats)                            **
     ** free param and population                                       **
     *********************************************************************/
    """
    # void ESInitial(unsigned int, ESParameter **, ESfcnTrsfm *, \
    #                   ESfcnFG, int, int, int, double *, double *, int, int, int, \
    #                double, double, double, int, \
    #                ESPopulation **, ESStatistics **);

    # note: ESInitial is not ported to Python on account of the ESFcnFG parameter
    # which is a function, but not a pointer. Instead, we implement a new function
    # that `ESInitialWithPtrFitnessFcn` that instead takes a pointer. All else is the same as ESInit

    # void ESInitial(unsigned int, ESParameter **, ESfcnTrsfm *, \
    #                ESfcnFG*, int, int, int, double *, double *, int, int, int, \
    #                double, double, double, int, \
    #                ESPopulation **, ESStatistics **);

    ESInitialWithPtrFitnessFcn = util.load_func(
        funcname="ESInitialWithPtrFitnessFcn",
        argtypes=[
            ct.c_int64,  # unsigned int seed,
            ct.c_int64,  # ESParameter **param,
            ct.c_int64,  # ESfcnTrsfm *trsfm,
            ct.c_int64,  # ESfcnFG* fg,
            ct.c_int64,  # int es,
            ct.c_int64,  # int constraint,
            ct.c_int64,  # int dim,
            ct.c_int64,  # double *ub,
            ct.c_int64,  # double *lb,
            ct.c_int64,  # int miu,
            ct.c_int64,  # int lambda,
            ct.c_int64,  # int gen,
            ct.c_int64,  # double gamma,
            ct.c_int64,  # double alpha,
            ct.c_int64,  # double varphi,
            ct.c_int64,  # int retry,
            ct.c_int64,  # ESPopulation **population
            ct.c_int64,  # ESStatistics **stats
        ],
        return_type=None)

    """
    /**
     * @brief (CW) create a pointer to an ESIndividual
     * @details Heap allocated. Free with freeIndividual
     */
    """
    # ESIndividual *makeIndividual();
    makeIndividual = util.load_func(
        funcname="makeIndividual",
        argtypes=[],  # ESIndividual *
        return_type=ct.c_uint64
    )

    """"/**
     * @brief (CW) free an ESIndividual
     */
    """
    # void freeIndividual(ESIndividual *individual);
    freeIndividual = util.load_func(
        funcname="freeIndividual",
        argtypes=[
            ct.c_uint64,  # ESIndividual *individual
        ],
        return_type=None
    )

    """/**
     * @brief Create a ESPopulation 
     * @details heap allocated. User free's with freeESPopulation
     */
     """
    # ESPopulation *makePopulation();
    makeESPopulation = util.load_func(
        funcname="makePopulation",
        argtypes=[],
        return_type=ct.c_uint64  # ESPopulation *
    )

    """/**
     * @brief free a ESPopulation* allocated by ESPopulation
     */
    """
    # void freePopulation(ESPopulation* population);
    freeESPopulation = util.load_func(
        funcname="freePopulation",
        argtypes=[
            ct.c_uint64,  # ESPopulation *
        ],
        return_type=None
    )

    """/**
     * @brief Create a ESPopulation 
     * @details heap allocated. User free's with freeESPopulation
     */
     """
    # ESPopulation *makePopulation();
    makeESStatistics = util.load_func(
        funcname="makeESStatistics",
        argtypes=[],
        return_type=ct.c_uint64  # ESPopulation *
    )

    """/**
     * @brief free a ESPopulation* allocated by ESPopulation
     */
    """
    # void freeESStatistics(ESStatistics* statistics);
    freeESStatistics = util.load_func(
        funcname="freeESStatistics",
        argtypes=[
            ct.c_uint64,  # ESStatistics*
        ],
        return_type=None
    )

    """
    /**
     * @brief A "do nothing" transform function that conforms
     * to the interface dictated by ESFcnTrsfm
     * @author (CW)
     */
    """
    # double do_nothing_transform(double x);
    do_nothing_transform = util.load_func(
        funcname="do_nothing_transform",
        argtypes=[
            ct.c_double
        ],
        return_type=ct.c_double
    )

    # void ESDeInitial(ESParameter *, ESPopulation *, ESStatistics *);
    ESDeInitial = util.load_func(
        funcname="ESDeInitial",
        argtypes=[
            ct.c_uint64,  # ESParameter *,
            ct.c_uint64,  # ESPopulation *,
            ct.c_uint64,  # ESStatistics *
        ],
        return_type=None
    )
    """
    /*********************************************************************
     ** initialize parameters                                           **
     ** ESInitialParam(param,trsfm,fg,es,constraint,                    **
     **                dim,ub,lb,miu,lambda,gen)                        **
     ** param: point to parameter                                       **
     ** fg: functions of fitness and constraints                        **
     ** trsfm: to transform sp/op                                       **
     ** es: ES process, esDefESPlus/esDefESSlash                        **
     ** seed: reserve seed for next use                                 **
     ** constraint: number of constraints                               **
     ** dim: dimension/number of genes in genome                        **
     ** ub[dim]: up bounds                                              **
     ** lb[dim]: low bounds                                             **
     ** spb[dim]: bounds on sp , spb = (ub-lb)/sqrt(dim)                **
     ** miu: parent/population size                                     **
     ** lambda: offsping/population size                                **
     ** gen: number of generations                                      **
     ** gamma: usually esDefGamma=0.85                                  **
     ** alpha: usually esDefAlpha=0.2                                   **
     ** chi: chi = 1/2n +1/2sqrt(n)                                     **
     ** varphi: = sqrt((2/chi)*log((1/alpha)*(exp(varphi^2*chi/2)       **
     **                  -(1-alpha))))                                  **
     **         expected rate of convergence                            **
     ** retry: retry times to check bounds                              **
     ** tau: learning rates: tau = varphi/(sqrt(2*sqrt(dim)))           **
     ** tar_: learning rates: tau_ = varphi((sqrt(2*dim)                **
     **                                                                 **
     ** ESDeInitialParam(param)                                         **
     ** free param                                                      **
     *********************************************************************/
    """
    # void ESInitialParam(ESParameter **, ESfcnTrsfm *, ESfcnFG, int, \
    #                        unsigned int, \
    #                     int, int, double *, double *, int, int, int, \
    #                     double, double, double, int);

    # ESInitialParam not loaded into Python since ESInit already invokes this method
    # Note, if we need it we'll have to implement another method that takes ESfcnFG*, not ESfcnFG.

    # void ESDeInitialParam(ESParameter *);
    # Note: Note ESDeInitialParam not implemented for same reason as ESInitialParam
    # util.load_func(
    #     funcname="ESDeInitialParam",
    #     argtypes=[
    #         ct.c_uint64 #ESParameter*
    #     ],
    #     return_type=None)

    """
    /*********************************************************************
     ** initialize population                                           **
     ** ESInitialPopulation(population,param)                           **
     ** population: point to this population                            **
     ** param: point to this parameter                                  **
     **   -> index: 0->lambda-1                                         **
     **   -> individual[lambda]                                         **
     **   -> fg(individual)                                             **
     **   -> f,phi                                                      **
     ** the initialization is looked as first generation                **
     **                                                                 **
     ** ESDeInitialPopulation(population, param)                        **
     ** free population                                                 **
     ESInitialPopulation = *********************************************************************/
    """
    # void ESInitialPopulation(ESPopulation **, ESParameter *);
    ESDeInitialPopulation = util.load_func(
        funcname="ESInitialPopulation",
        argtypes=[
            ct.c_uint64,  # ESPopulation**
            ct.c_uint64,  # ESParameter*
        ],
        return_type=None
    )

    # void ESDeInitialPopulation(ESPopulation *, ESParameter *);
    util.load_func(
        funcname="ESDeInitialPopulation",
        argtypes=[
            ct.c_uint64,  # ESPopulation *,
            ct.c_uint64,  # ESParameter *
        ],
        return_type=None)

    """
    /*********************************************************************
     ** initialize individual                                           **
     ** ESInitialIndividual(indvdl, param)                              **
     ** to calculate f,g,and phi                                        **
     ** to initialize op and sp                                         **
     ** phi=sum{(g>0)^2}                                                **
     ** op = rand(lb, ub)                                               **
     ** sp = (ub - lb)/sqrt(dim)                                        **
     **                                                                 **
     **                                                                 **
     ** ESDeInitialIndividual(indvdl, param)                            **
     ** free individual                                                 **
     **                                                                 **
     ** ESPrintOp(indvdl, param)                                        **
     ** print individual information, indvdl->op                        **
     ** ESPrintSp(indvdl, param)                                        **
     ** print individual information, indvdl->sp                        **
     *********************************************************************/
    """
    # void ESInitialIndividual(ESIndividual **, ESParameter *);
    ESInitialIndividual = util.load_func(
        funcname="ESInitialIndividual",
        argtypes=[
            ct.c_uint64,  # ESIndividual **,
            ct.c_uint64,  # ESParameter *
        ],
        return_type=None)

    # void ESDeInitialIndividual(ESIndividual *);
    ESDeInitialIndividual = util.load_func(
        funcname="ESDeInitialIndividual",
        argtypes=[
            ct.c_uint64,  # ESIndividual *,
        ],
        return_type=None)

    # void ESPrintIndividual(ESIndividual *, ESParameter *);
    ESPrintIndividual = util.load_func(
        funcname="ESPrintIndividual",
        argtypes=[
            ct.c_uint64,  # ESIndividual *,
            ct.c_uint64,  # ESParameter *
        ],
        return_type=None)
    # void ESPrintOp(ESIndividual *, ESParameter *);
    ESPrintOp = util.load_func(
        funcname="ESPrintOp",
        argtypes=[
            ct.c_uint64,  # ESIndividual *,
            ct.c_uint64,  # ESParameter *
        ],
        return_type=None)
    # void ESPrintSp(ESIndividual *, ESParameter *);
    ESPrintSp = util.load_func(
        funcname="ESPrintSp",
        argtypes=[
            ct.c_uint64,  # ESIndividual *,
            ct.c_uint64,  # ESParameter *
        ],
        return_type=None)

    """
    /*********************************************************************
     ** copy a individual                                               **
     ** ESCopyIndividual(from, to, param)                               **
     *********************************************************************/
    """
    # void ESCopyIndividual(ESIndividual *, ESIndividual *, ESParameter *);
    ESCopyIndividual = util.load_func(
        funcname="ESCopyIndividual",
        argtypes=[
            ct.c_uint64,  # ESIndividual *,
            ct.c_uint64,  # ESIndividual *,
            ct.c_uint64,  # ESParameter *
        ],
        return_type=None)
    """
    /*********************************************************************
     ** initialize statistics                                           **
     ** ESInitialStat(stats, population, param)                         **
     ** to intialize time, curgen, bestindvdl,thisbestindvdl            **
     ** not to do the first statistics                                  **
     ** to set dt, bestgen                                              **
     **                                                                 **
     ** ESDeInitialStat(stats)                                          **
     ** free statistics                                                 **
     *********************************************************************/
    """
    # void ESInitialStat(ESStatistics **, ESPopulation *, ESParameter *);
    ESInitialStat = util.load_func(
        funcname="ESInitialStat",
        argtypes=[
            ct.c_uint64,  # ESStatistics **,
            ct.c_uint64,  # ESPopulation *,
            ct.c_uint64,  # ESParameter *
        ],
        return_type=None)

    # void ESDeInitialStat(ESStatistics *);
    ESDeInitialStat = util.load_func(
        funcname="ESDeInitialStat",
        argtypes=[
            ct.c_uint64,  # ESStatistics *
        ],
        return_type=None)
    """
    /*********************************************************************
     ** do statistics                                                   **
     ** ESDoStat(stats, population, param)                              **
     ** to set nowtime, dt, curgen, bestgen, (this)bestindvdl           **
     ** to do statistics                                                **
     ** if there's no feasible best, do nothing                         **
     ** the initialization is looked as zero generation                 **
     **                                                                 **
     ** ESPrintStat(stats, param)                                       **
     ** print statistics information                                    **
     ** gen=,time=,dt=,bestgen=,bestfitness=,bestindividual=,           **
     *********************************************************************/
    """
    # void ESDoStat(ESStatistics *, ESPopulation *, ESParameter *);
    ESDoStat = util.load_func(
        funcname="ESDoStat",
        argtypes=[
            ct.c_uint64,  # ESStatistics *,
            ct.c_uint64,  # ESPopulation *,
            ct.c_uint64,  # ESParameter *
        ],
        return_type=None)

    # void ESPrintStat(ESStatistics *, ESParameter *);
    ESPrintStat = util.load_func(
        funcname="ESPrintStat",
        argtypes=[
            ct.c_uint64,  # ESStatistics *,
            ct.c_uint64,  # ESParameter *
        ],
        return_type=None)
    """
    /*********************************************************************
     ** stepwise evolution                                              **
     ** ESStep(population, param, stats, pf)                            **
     **                                                                 **
     ** -> Stochastic ranking -> sort population based on ranking index **
     ** -> Mutate (recalculate f/g/phi) -> do statistics analysis on    **
     ** this generation -> print statistics information                 **
     *********************************************************************/
    """
    # void ESStep(ESPopulation *, ESParameter *, ESStatistics *, double);
    ESStep = util.load_func(
        funcname="ESStep",
        argtypes=[
            ct.c_uint64,  # ESPopulation *,
            ct.c_uint64,  # ESParameter *,
            ct.c_uint64,  # ESStatistics *,
            ct.c_double,  # double
        ],
        return_type=None)
    """
    /*********************************************************************
     ** sort population based on Index by ESSRSort                      **
     ** ESSortPopulation(population, param)                             **
     *********************************************************************/
    """
    # void ESSortPopulation(ESPopulation *, ESParameter *);
    ESSortPopulation = util.load_func(
        funcname="ESSortPopulation",
        argtypes=[
            ct.c_uint64,  # ESPopulation *,
            ct.c_uint64,  # ESParameter *
        ],
        return_type=None)
    """
    /*********************************************************************
     ** select the next generation                                      **
     ** ESSelectPopulation(population, param)                           **
     ** select first miu offsprings to fill up the next generation      **
     ** miu -> lambda : 1..miu,1..miu,..,lambda                         **
     *********************************************************************/
    """
    # void ESSelectPopulation(ESPopulation *, ESParameter *);
    ESSelectPopulation = util.load_func(
        funcname="ESSelectPopulation",
        argtypes=[
            ct.c_uint64,  # ESPopulation *,
            ct.c_uint64,  # ESParameter *
        ],
        return_type=None)
    """
    /*********************************************************************
     ** mutate                                                          **
     ** ESMutate(population, param)                                     **
     **                                                                 **
     ** sp_ : copy of sp                                                **
     ** op_ : copy of op                                                **
     ** update sp                                                       **
     ** traditional technique using exponential smoothing               **
     ** sp(1->miu-1) : unchanged                                        **
     ** sp(miu->lambda): sp = sp_*exp(tau_*N(0,1) + tau*Nj(0,1))        **
     **                  Nj : random number generated for each j        **
     ** check sp bound                                                  **
     ** if(sp > bound) then sp = bound                                  **
     ** differential variation                                          **
     ** op(1->miu-1) = op_ + gamma*(op_[1] - op_[i+1])                  **
     ** mutation                                                        **
     ** op(miu->lambda): op = op_ +sp * N(0,1)                          **
     ** check op bound                                                  **
     ** if(op > ub || op < lb) then try retry times                     **
     **                        op = op_ + sp * N(0,1)                   **
     ** if still not in bound then op = op_                             **
     ** exponential smoothing                                           **
     ** sp(miu->lambda): sp = sp_ + alpha * (sp - sp_)                  **
     **                                                                 **
     ** re-calculate f/g/phi                                            **
     *********************************************************************/
    """
    # void ESMutate(ESPopulation *, ESParameter *);
    ESMutate = util.load_func(
        funcname="ESMutate",
        argtypes=[
            ct.c_uint64,  # ESPopulation *,
            ct.c_uint64,  # ESParameter *
        ],
        return_type=None)
