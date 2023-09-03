add_library("${PROJECT_NAME}-base" INTERFACE)
add_library("rmm::rtoolbox::base" ALIAS "${PROJECT_NAME}-base")
include("CompileDefinitions_Windows.cmake")
target_compile_features("${PROJECT_NAME}-base"
  INTERFACE
    cxx_std_23
)
target_compile_options("${PROJECT_NAME}-base"
  INTERFACE
    $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<NOT:$<CONFIG:Release>>>:/JMC>
)
