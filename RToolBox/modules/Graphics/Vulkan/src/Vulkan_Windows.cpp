module;

#include <Windows.h>

#include <vulkan/vulkan.h>

#include <expected>
#include <vector>

module rmm.rtoolbox.Vulkan;

namespace rmm::vkw
{

vk::Result
Initialize()
{
  HMODULE module = LoadLibrary(L"vulkan-1.dll");
  if (!module)
  {
    return VK_ERROR_INITIALIZATION_FAILED;
  }

  vk::GetInstanceProcAddr = reinterpret_cast<PFN_vkGetInstanceProcAddr>(
    GetProcAddress(module, "vkGetInstanceProcAddr"));

  LoadLoaderFunctionPointers();

  return VK_SUCCESS;
}

std::vector<const char*>
GetRequiredInstanceExtensions()
{
  std::vector extensions{
    VK_KHR_SURFACE_EXTENSION_NAME,
    VK_KHR_WIN32_SURFACE_EXTENSION_NAME,
  };

  return extensions;
}

} // namespace rmm::vkw
