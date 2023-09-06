add_executable("SimpleGameMain")
set_executable_type("SimpleGameMain")
target_include_directories("SimpleGameMain"
  PRIVATE
    "../"
)
target_link_libraries("SimpleGameMain"
  PRIVATE
    "rmm::rtoolbox"
    $<TARGET_OBJECTS:rmm::rtoolbox::main>
)
target_sources("SimpleGameMain"
  PRIVATE
    # Platform resources (Windows)
    $<$<PLATFORM_ID:Windows>:../Resources/Windows/Application.manifest>
    $<$<AND:$<PLATFORM_ID:Windows>,$<CXX_COMPILER_ID:MSVC>>:../Resources/Windows/resource.h>
    $<$<AND:$<PLATFORM_ID:Windows>,$<CXX_COMPILER_ID:MSVC>>:../Resources/Windows/SampleGame.rc>
    # Source files
    "src/main.cpp"
)
