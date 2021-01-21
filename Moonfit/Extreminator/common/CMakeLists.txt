set(target myCommon)

add_library(${target} OBJECT myFiles myRandom myTimes)
target_include_directories(${target} PUBLIC ../../../Moonfit)
target_compile_definitions(${target} PUBLIC WITHOUT_QT)