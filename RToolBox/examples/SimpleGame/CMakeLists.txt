add_executable("SimpleGame" WIN32)
set_property(TARGET "SimpleGame"
  PROPERTY
    $<$<AND:$<PLATFORM_ID:Windows>,$<CXX_COMPILER_ID:MSVC>>:WIN32_EXECUTABLE TRUE>
)
target_include_directories("SimpleGame"
  PRIVATE
    "../"
)
target_link_libraries("SimpleGame"
  PRIVATE
    "rmm::rtoolbox"
)
target_sources("SimpleGame"
  PRIVATE
    # Platform resources (Windows)
    $<$<PLATFORM_ID:Windows>:../Resources/Windows/Application.manifest>
    $<$<AND:$<PLATFORM_ID:Windows>,$<CXX_COMPILER_ID:MSVC>>:../Resources/Windows/resource.h>
    $<$<AND:$<PLATFORM_ID:Windows>,$<CXX_COMPILER_ID:MSVC>>:../Resources/Windows/SampleGame.rc>
    # Source files
    "src/main.cpp"
)
