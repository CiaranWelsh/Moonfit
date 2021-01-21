add_subdirectory(Extreminator)
add_subdirectory(Framework)

set(target Moonfit)
add_library(${target} STATIC moonfit.h common)
target_link_libraries(${target} PUBLIC myCommon optimizers ESES Framework)