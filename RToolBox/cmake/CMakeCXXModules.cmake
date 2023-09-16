include_guard()

# These must be normal variables
if("${CMAKE_VERSION}" VERSION_GREATER_EQUAL "3.28")
  message(FATAL_ERROR
    "C++20 modules are currently not supported for CMake version ${CMAKE_VERSION}!"
    "To add support inform yourself about the state of the feature at "
    "https://github.com/Kitware/CMake/blob/master/Help/dev/experimental.rst "
    "and add the corresponding value of CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API"
  )
elseif("${CMAKE_VERSION}" VERSION_GREATER_EQUAL "3.27")
  # CMake 3.27/3.27.1
  set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API "aa1f7df0-828a-4fcd-9afc-2dc80491aca7")
elseif( ${CMAKE_VERSION} VERSION_GREATER_EQUAL "3.26")
# CMake 3.26
  set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API "2182bf5c-ef0d-489a-91da-49dbc3090d2a")
else()
# CMake 3.25
  set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API "3c375311-a3c9-4396-a187-3227ef642046")
endif()

