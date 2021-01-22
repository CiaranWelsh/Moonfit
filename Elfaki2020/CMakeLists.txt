set(target Elfaki2020)
add_executable(${target} expThymus mainThymus modelsStructABC
        ../Moonfit/common
        ../Moonfit/Framework
        ../Moonfit/Interface/simuwin

        )

target_link_libraries(${target} PRIVATE
        myCommon
        optimizers
        SRES-static
        Framework
        Moonfit
        linux2win
        )

target_compile_definitions(${target} PRIVATE ModelStructureA)
target_include_directories(${target} PRIVATE ../Moonfit/Extreminator/common)
add_dependencies(${target} Moonfit)













