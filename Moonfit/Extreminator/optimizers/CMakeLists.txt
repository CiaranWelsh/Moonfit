add_subdirectory(SRES)

set(target optimizers)
add_library(
        ${target} STATIC
        baseOptimizer
        CMAES
        Config
        Genetic
        GeneticGeneral
        GradientDescent
        individual
        MultipleGradientDescent.h
        Orthogonalise
        population
        scalingFunctions
        simulatedAnnealing
        SRES.h
        SRES.cc
)


target_include_directories(${target} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ../include ../common ../../../Moonfit)
target_link_libraries(${target} PUBLIC SRES-static)

target_compile_definitions(${target} PUBLIC WITHOUT_QT)












