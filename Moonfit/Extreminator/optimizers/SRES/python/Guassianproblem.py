import pandas as pd
import numpy as np
from sres import _SRES, _lib
import ctypes as ct
import tellurium as te
from math import pi as PI
import unittest

sres = _SRES()


def generateData(mu, sigma):
    return np.random.normal(mu, sigma, 10)


EXP_DATA = generateData(0.1, 0.1)


class Test(unittest.TestCase):

    def setUp(self) -> None:
        pass

    def test_ctypes_callback_fn_example(self):
        from ctypes import cdll

        libc = cdll.msvcrt

        IntArray5 = ct.c_int * 5
        ia = IntArray5(5, 1, 7, 33, 99)
        qsort = libc.qsort
        qsort.restype = None

        CALLBACK_FN = ct.CFUNCTYPE(ct.c_int, ct.POINTER(ct.c_int), ct.POINTER(ct.c_int))

        def py_cb(a, b):
            print("Pycb", a[0], b[0])
            return 0

        qsort(ia, len(ia), ct.sizeof(ct.c_int), CALLBACK_FN(py_cb))

    def testPassingDoubleArray(self):
        lb = ct.pointer(sres.DoubleArrayLen2(0.1, 0.1))  # double *lb,
        sres.fakeFun(lb)

    def testPassingDoubleArrayUsingWrapperFn(self):
        lb = sres._makeDoubleArrayPtr([0.1, 0.1])  # double *lb,
        sres.fakeFun(lb)

    def testFunctionPointerInIsolation(self):
        import ctypes as ct

        lib = ct.CDLL("SRES")

        F1_CALLBACK = ct.CFUNCTYPE(None, ct.POINTER(ct.c_double * 2), ct.POINTER(ct.c_double), ct.POINTER(ct.c_double))
        function_that_takes_a_function = lib.function_that_takes_a_function
        function_that_takes_a_function.argtypes = [F1_CALLBACK, ct.POINTER(ct.c_double * 2), ct.POINTER(ct.c_double),
                                                   ct.POINTER(ct.c_double)]
        function_that_takes_a_function.restype = None

        # @F1_CALLBACK
        def func_to_pass_in(d1, d2, d3):
            print("hello from Python: ")

        # function_that_takes_a_function(func_to_pass_in, sres._makeDoubleArrayPtr([0.1, 0.1]))
        function_that_takes_a_function(F1_CALLBACK(func_to_pass_in), sres._makeDoubleArrayPtr([0.1, 1.2]),
                                       ct.pointer(ct.c_double(4.0)), ct.pointer(ct.c_double(6.0)))

    def testFunctionPointerInIsolationAndUpdateAValue(self):
        import ctypes as ct

        lib = ct.CDLL("SRES")

        F1_FUNCTION_PTR = ct.CFUNCTYPE(None, ct.POINTER(ct.c_double), ct.POINTER(ct.c_double))

        lib.function_that_takes_a_function.argtypes = [
            F1_FUNCTION_PTR, ct.POINTER(ct.c_double), ct.POINTER(ct.c_double)
        ]
        lib.function_that_takes_a_function.restype = None

        def func_to_pass_in(x, y):
            print("hello from Python: ")
            print("x, y: ", x.contents, y.contents)
            new_value = x.contents.value + y.contents.value
            new_value_double_ptr = ct.pointer(ct.c_double(new_value))

            ct.memmove(ct.cast(y, ct.c_void_p).value, ct.cast(new_value_double_ptr, ct.c_void_p).value, ct.sizeof(ct.c_double))

        # function_that_takes_a_function(func_to_pass_in, sres._makeDoubleArrayPtr([0.1, 0.1]))
        input = ct.c_double(4.0)
        output = ct.c_double(1.0)
        input_ptr = ct.pointer(input)
        output_ptr = ct.pointer(output)
        lib.function_that_takes_a_function(F1_FUNCTION_PTR(func_to_pass_in), input_ptr, output_ptr)

    def test_do_sres(self):
        sres = _SRES()
        param = sres.makeESParameter()
        stats = sres.makeESStatistics()
        population = sres.makeESPopulation()
        trsfm = sres.getTransformFun(2)

        # https://stackoverflow.com/questions/51131433/how-to-pass-lists-into-a-ctypes-function-on-python/51132594

        Popsize = ct.c_int32(5)
        Generation = ct.c_int32(20)
        seed = ct.c_int32(0)
        gamma = ct.c_double(0.85)
        alpha = ct.c_double(0.2)
        retry = ct.c_int32(10)
        es = ct.c_int32(1)
        constraint = ct.c_int32(0)
        dim = ct.c_int32(2)
        varphi = ct.c_double(1.0)
        ngen = ct.c_int32(50)

        miu = 30
        lambda_ = 200

        # How to verify that this works?
        ub = ct.pointer(sres.DoubleArrayLen2(10.0, 10.0))  # double *ub,
        lb = ct.pointer(sres.DoubleArrayLen2(0.1, 0.1))  # double *lb,

        ESfcnFG_TYPE = ct.CFUNCTYPE(None, ct.POINTER(ct.c_double*2), ct.POINTER(ct.c_double), ct.POINTER(ct.c_double))

        def cost_fun(x, f, g):
            sim = generateData(x.contents[0], x.contents[1])
            cost = 0
            for i in range(10):
                cost += (EXP_DATA[i] - sim[i]) ** 2
            cost_dbl_ptr = ct.pointer(ct.c_double(cost))

            # copy the value from Python to C. If we don't do this, the value gets deleted.
            ct.memmove(ct.cast(f, ct.c_void_p).value, ct.cast(cost_dbl_ptr, ct.c_void_p).value, ct.sizeof(ct.c_double))


        sres.ESInitial(
            seed,
            param,
            trsfm,
            ESfcnFG_TYPE(cost_fun),
            es,
            constraint,
            dim,
            ub,
            lb,
            miu,
            lambda_,
            ngen,
            gamma,
            alpha,
            varphi,
            retry,
            population,
            stats
        )

        curgen = 0
        while curgen < 10:
            print("Current gen: ", curgen)
            sres.ESStep(
                sres.derefESPopulation(population),
                sres.derefESParameter(param),
                sres.derefESStatistics(stats),
                ct.c_double(0.45)
            )
            curgen += 1

        # sres.ESDeInitial(
        #     sres.derefESParameter(esparam),
        #     sres.derefESPopulation(pop),
        #     sres.derefESStatistics(stats)
        # )

        # sres.freeCostFunPtr(costFun)
        # sres.freeTransformFun(trsf)


if __name__ == "__main__":
    pass
    # check that passing in double array works
    # testPassingDoubleArray()

    # y = ct.POINTER(ct.c_double)
    # print(y, y())

    # do_sres()

    # ct callback example from docs
    # Use qsort from python:
    # void qsort (void* base, size_t num, size_t size, int (*compar)(const void*,const void*));
