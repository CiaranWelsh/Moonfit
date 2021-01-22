set(target SRES)

add_library(${target}-static STATIC ESES ESSRSort sharefunc)
target_compile_definitions(${target}-static PUBLIC SRES_STATIC_DEFINE)

add_library(${target} SHARED ESES ESSRSort sharefunc)
target_compile_definitions(${target}-static PUBLIC SRES_EXPORT)

include(GenerateExportHeader)
generate_export_header(${target})

install(
        TARGETS ${target} ${target}-static
        EXPORT ${target}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)