module;

#include <Windows.h>

#include <vulkan/vulkan.h>

#include <expected>

module rmm.rtoolbox.Vulkan;

namespace rmm::vk
{

VkResult
Initialize()
{
  HMODULE module = LoadLibrary(L"vulkan-1.dll");
  if (!module)
  {
    return VK_ERROR_INITIALIZATION_FAILED;
  }

  vkGetInstanceProcAddr = reinterpret_cast<PFN_vkGetInstanceProcAddr>(
    GetProcAddress(module, "vkGetInstanceProcAddr"));

  LoadLoaderFunctionPointers();

  return VK_SUCCESS;
}

} // namespace rmm::vk
