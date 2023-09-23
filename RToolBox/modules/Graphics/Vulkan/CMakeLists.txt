project("Vulkan")

add_library("Vulkan" STATIC)
add_library("rmm::vulkan" ALIAS "Vulkan")
target_compile_definitions("Vulkan"
  PRIVATE
    "VK_NO_PROTOTYPES"
    $<$<PLATFORM_ID:Windows>:VK_USE_PLATFORM_WIN32_KHR>
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
    "src/VulkanExtensions.inc"
    "src/VulkanFunctions.inc"
    "src/VulkanTypes.inc"
)
