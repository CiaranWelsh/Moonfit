set(target Elfaki2020)
add_executable(${target} expThymus mainThymus modelsStructABC
        ../Moonfit/common
        ../Moonfit/Framework
        ../Moonfit/Interface/simuwin

        )

target_link_libraries(${target} PRIVATE
        SRES-static
        optimizers
        Framework
        myCommon
        )

target_compile_definitions(${target} PRIVATE ModelStructureA)
target_include_directories(${target} PRIVATE ../Moonfit/Extreminator/common)














