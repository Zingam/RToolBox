project("Vulkan")

# find Vulkan SDK
find_package("Vulkan" REQUIRED)

# set up Vulkan C++ module
add_library("${PROJECT_NAME}")
add_library("vulkan::cppm" ALIAS "${PROJECT_NAME}")

target_compile_definitions("${PROJECT_NAME}"
  PUBLIC
    # Disable exceptions
    # "VULKAN_HPP_NO_EXCEPTIONS"
    # Enable designated initializers
    "VULKAN_HPP_NO_STRUCT_CONSTRUCTORS"
    # Enable dynamic dispatch
    # "VULKAN_HPP_DISPATCH_LOADER_DYNAMIC=1"
)
target_compile_features("${PROJECT_NAME}"
  PUBLIC
    cxx_std_23
)
target_include_directories("${PROJECT_NAME}"
  PRIVATE
    "${Vulkan_INCLUDE_DIR}"
)
target_link_libraries("${PROJECT_NAME}"
  PUBLIC
    "rmm::rtoolbox"
    "Vulkan::Vulkan"
)

target_sources("${PROJECT_NAME}"
  PUBLIC
    FILE_SET cxx_modules TYPE CXX_MODULES
    BASE_DIRS
      "${Vulkan_INCLUDE_DIR}"
    FILES
      "${Vulkan_INCLUDE_DIR}/vulkan/vulkan.cppm"
)
