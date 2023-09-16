cmake_minimum_required(VERSION 3.26.0)

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_LIST_DIR}/cmake")

include("ExecutableTargetType")
include("CMakeCXXModules")

project("RToolBox")

add_library("${PROJECT_NAME}" STATIC)
add_library("rmm::rtoolbox" ALIAS "${PROJECT_NAME}")
target_compile_definitions("${PROJECT_NAME}"
  PUBLIC
)
target_compile_features("${PROJECT_NAME}"
  PUBLIC
    cxx_std_23
)
target_compile_options("${PROJECT_NAME}"
  PUBLIC
)
target_link_libraries("${PROJECT_NAME}"
  PUBLIC
    "rmm::rtoolbox::base"
    "rmm::vulkan"
)
target_link_options("${PROJECT_NAME}"
  PUBLIC
)
target_sources("${PROJECT_NAME}"
  PUBLIC
    FILE_SET cxx_modules TYPE CXX_MODULES
    FILES
      "modules/Application/Application.cppm"
      "modules/Config/Config.cppm"
      "modules/Geometry/Geometry.cppm"
      "modules/Geometry/Line.cppm"
      "modules/Geometry/Point.cppm"
      "modules/Renderer/Renderer.cppm"
      "modules/System/Window.cppm"
      "modules/RToolBox.cppm"
  PRIVATE
    FILE_SET cxx_modules_internal TYPE CXX_MODULES
    FILES
  PRIVATE
    "modules/Application/Application.cpp"
    $<$<PLATFORM_ID:Windows>:modules/System/Platforms/Window_Windows.cpp>
    "modules/System/Platforms/Window.inc"
)

add_subdirectory("examples")
add_subdirectory("libraries")
add_subdirectory("modules/Graphics")
