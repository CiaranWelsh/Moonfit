add_subdirectory(Extreminator)
add_subdirectory(Framework)

set(target Moonfit)
add_library(${target} STATIC moonfit.h common)
target_link_libraries(${target} PUBLIC
        myCommon
        optimizers
        SRES-static
        Framework
        linux2win
        )

if (UNIX AND NOT APPLE)
    target_link_libraries(${target} PUBLIC stdc++fs)
endif ()

add_dependencies(
        ${target}
        myCommon
        optimizers
        SRES-static
        Framework
        linux2win
)


install(
        TARGETS ${target}
        EXPORT ${target}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)







