add_executable("SimpleGame")
set_property(TARGET "SimpleGame"
  PROPERTY
    $<$<AND:$<PLATFORM_ID:Windows>,$<CXX_COMPILER_ID:Clang>>:WIN32_EXECUTABLE TRUE>
)
target_include_directories("SimpleGame"
  PRIVATE
    "."
)
target_link_libraries("SimpleGame"
  PRIVATE
    "rmm::rtoolbox"
)
target_sources("SimpleGame"
  PRIVATE
    # Platform resources (Windows)
    $<$<PLATFORM_ID:Windows>:Resources/Windows/Application.manifest>
    $<$<AND:$<PLATFORM_ID:Windows>,$<CXX_COMPILER_ID:MSVC>>:Resources/Windows/resource.h>
    $<$<AND:$<PLATFORM_ID:Windows>,$<CXX_COMPILER_ID:MSVC>>:Resources/Windows/SampleGame.rc>
    # Source files
    "SimpleGame/src/main.cpp"
)

add_executable("SimpleGameMain")
set_property(TARGET "SimpleGameMain"
PROPERTY
  $<$<AND:$<PLATFORM_ID:Windows>,$<CXX_COMPILER_ID:Clang>>:WIN32_EXECUTABLE TRUE>
)
target_include_directories("SimpleGameMain"
  PRIVATE
    "."
)
target_link_libraries("SimpleGameMain"
  PRIVATE
    "rmm::rtoolbox"
    $<TARGET_OBJECTS:rmm::rtoolbox::main>
)
target_sources("SimpleGameMain"
  PRIVATE
    # Platform resources (Windows)
    $<$<PLATFORM_ID:Windows>:Resources/Windows/Application.manifest>
    $<$<AND:$<PLATFORM_ID:Windows>,$<CXX_COMPILER_ID:MSVC>>:Resources/Windows/resource.h>
    $<$<AND:$<PLATFORM_ID:Windows>,$<CXX_COMPILER_ID:MSVC>>:Resources/Windows/SampleGame.rc>
    # Source files
    "SimpleGameMain/src/main.cpp"
)

