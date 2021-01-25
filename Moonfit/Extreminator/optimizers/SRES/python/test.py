import unittest

from sres_capi import _Util, _SRES
import ctypes as ct


class Test(unittest.TestCase):

    def setUp(self) -> None:
        self.sres = _SRES()

    def test_makeESParameter(self):
        cptr = self.sres.makeESParameter()
        self.assertIsNotNone(cptr)
        # free the pointer
        self.sres.freeESParameter(cptr)

    def test_makeESStatistics(self):
        cptr = self.sres.makeESStatistics()
        self.assertIsNotNone(cptr)
        self.sres.freeESStatistics(cptr)

    def test_makeESPopulation(self):
        cptr = self.sres.makeESPopulation()
        self.assertIsNotNone(cptr)
        self.sres.freeESPopulation(cptr)

    def test_ESInitialWithPtrFitnessFcn(self):
        # Allocate space for **ESParameter
        esparam = self.sres.makeESParameter()

        stats = self.sres.makeESStatistics()

        pop = self.sres.makeESPopulation()

        # https://stackoverflow.com/questions/51131433/how-to-pass-lists-into-a-ctypes-function-on-python/51132594
        DoubleArrayLen2 = ct.c_double*2


        seed = 0
        gamma = 0.85
        alpha = 0.2
        varalphi = 1
        retry = 10
        pf = 0.45
        es = 0
        miu = 30
        lamb = 200
        gen = 1750


        @ct.CFUNCTYPE(None, ct.c_double, ct.c_double)
        def ESfcnTrsfm(x):
            return x

        ptr = self.sres.ESInitialWithPtrFitnessFcn(
            seed,                                      # unsigned int seed,
            esparam,                                # ESParameter **param,
            0,                                      # ESfcnTrsfm *trsfm,
            0,                                      # ESfcnFG* fg,
            es,                                      # int es,
            0,                                      # int constraint,
            2,                                      # int dim,
            DoubleArrayLen2([10.0]*2),                  # double *ub,
            DoubleArrayLen2([0.1]*2),                   # double *lb,
            miu,                                     # int miu,
            lamb,                                      # int lambda,
            gen,                                      # int gen,
            gamma,                                      # double gamma,
            alpha,                                      # double alpha,
            varalphi,                                      # double varphi,
            retry,                                      # int retry,
            stats,                                      # ESPopulation **population
            pop,                                      # ESStatistics **stats
        )
        print(ptr)

        self.sres.freeESParameter(esparam)
        self.sres.freeESStatistics(stats)
        self.sres.freeESPopulation(pop)














    # def test_makeIndividual(self):
    #     self.sres.makeIndividual()
    #
    # def test_freeIndividual(self):
    #     self.sres.freeIndividual()
    #
    # def test_makePopulation(self):
    #     self.sres.makePopulation()
    #
    # def test_freePopulation(self):
    #     self.sres.freePopulation()
    #
    # def test_do_nothing_transform(self):
    #     self.sres.do_nothing_transform()
    #
    # def test_rss_cost(self):
    #     self.sres.rss_cost()
    #
    # def test_ESDeInitial(self):
    #     self.sres.ESDeInitial()
    #
    # def test_ESDeInitialPopulation(self):
    #     self.sres.ESDeInitialPopulation()
    #
    # def test_ESInitialIndividual(self):
    #     self.sres.ESInitialIndividual()
    #
    # def test_ESDeInitialIndividual(self):
    #     self.sres.ESDeInitialIndividual()
    #
    # def test_ESPrintIndividual(self):
    #     self.sres.ESPrintIndividual()
    #
    # def test_ESPrintOp(self):
    #     self.sres.ESPrintOp()
    #
    # def test_ESPrintSp(self):
    #     self.sres.ESPrintSp()
    #
    # def test_ESCopyIndividual(self):
    #     self.sres.ESCopyIndividual()
    #
    # def test_ESInitialStat(self):
    #     self.sres.ESInitialStat()
    #
    # def test_ESDeInitialStat(self):
    #     self.sres.ESDeInitialStat()
    #
    # def test_ESDoStat(self):
    #     self.sres.ESDoStat()
    #
    # def test_ESPrintStat(self):
    #     self.sres.ESPrintStat()
    #
    # def test_ESStep(self):
    #     self.sres.ESStep()
    #
    # def test_ESSortPopulation(self):
    #     self.sres.ESSortPopulation()
    #
    # def test_ESSelectPopulation(self):
    #     self.sres.ESSelectPopulation()
    #
    # def test_ESMutate(self):
    #     self.sres.ESMutate()
    #
    #
    #





































