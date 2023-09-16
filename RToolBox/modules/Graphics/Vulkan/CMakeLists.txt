project("Vulkan")

add_library("Vulkan" STATIC)
add_library("rmm::vulkan" ALIAS "Vulkan")
target_compile_definitions("Vulkan"
  PRIVATE
    "VK_NO_PROTOTYPES"
)
find_package("Vulkan")
target_link_libraries("Vulkan"
  PUBLIC
    "rmm::rtoolbox::base"
  PRIVATE
    "Vulkan::Headers"
)

################################################################################

target_sources("Vulkan"
  PUBLIC
    FILE_SET cxx_modules TYPE CXX_MODULES
    # BASE_DIRS
    #   "${Vulkan_INCLUDE_DIR}"
    FILES
      "src/Vulkan.cppm"
  PRIVATE
    $<$<PLATFORM_ID:Windows>:src/Vulkan_Windows.cpp>
    "src/Vulkan.cpp"
    "src/Vulkan.inc"
)
