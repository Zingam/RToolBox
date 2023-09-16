module;

#include <vulkan/vulkan.h>

#include <expected>

module rmm.rtoolbox.Vulkan;

namespace rmm::rtoolbox::vk
{

std::expected<Instance, Result>
CreateInstance(
  const InstanceCreateInfo* createInfo,
  const AllocationCallbacks* allocator)
{
  if (Instance instance{};
      VK_SUCCESS == vkCreateInstance(createInfo, allocator, &instance))
  {
    return instance;
  }
  return std::unexpected{ VK_ERROR_UNKNOWN };
}

[[nodiscard]] std::expected<std::vector<ExtensionProperties>, Result>
EnumerateInstanceExtensionProperties()
{
  std::uint32_t extensionCount = 0;
  vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

  std::vector<VkExtensionProperties> extensions(extensionCount);
  vkEnumerateInstanceExtensionProperties(
    nullptr, &extensionCount, extensions.data());

  return extensions;
}

[[nodiscard]] void
DestroyInstance(Instance instance, const AllocationCallbacks* allocator)
{
  vkDestroyInstance(instance, allocator);
}

Result
Initialize(Instance instance)
{
  LoadInstanceFunctionPointers(instance);
  LoadDeviceFunctionPointers(instance);

  return VK_SUCCESS;
}

#if !defined(VK_LOAD_FUNCTION_POINTER)
/**
 * @brief Generates a function pointer loader.
 *
 * @param instance The `VkInstance` that the fuction pointer will be compatible
 * with.
 * @param loaderName The function which obtains function pointers.
 * @param functionName The function name to generate a loader for.
 *
 */
#  define VK_LOAD_FUNCTION_POINTER(instance, loaderName, functionName)         \
    functionName = reinterpret_cast<PFN_##functionName>(                       \
      loaderName(instance, #functionName))
#else
#  error VK_LOAD_FUNCTION_POINTER already defined!
#endif

#if !defined(VK_LOAD_INSTANCE_FUNCTION_POINTER)
/**
 * @brief Generates a function pointer loader for instance functions.
 *
 * @param functionName The function name to generate a loader for.
 *
 * @note Variable `instance` of type `VkInstance must be available, as it is
 * used by the macro internally.
 *
 */
#  define VK_LOAD_INSTANCE_FUNCTION_POINTER(functionName)                      \
    VK_LOAD_FUNCTION_POINTER(instance, vkGetInstanceProcAddr, functionName)
#else
#  error VK_LOAD_INSTANCE_FUNCTION_POINTER is already defined!
#endif

#if !defined(VK_LOAD_DEVICE_FUNCTION_POINTER)
/**
 * @brief Generates a function pointer loader for instance functions.
 *
 * @param functionName The function name to generate a loader for.
 *
 * @note Variable `instance` of type `VkInstance must be available, as it is
 * used by the macro internally.
 *
 */
#  define VK_LOAD_DEVICE_FUNCTION_POINTER(functionName)                        \
    VK_LOAD_FUNCTION_POINTER(instance, vkGetDeviceProcAddr, functionName)
#else
#  error VK_LOAD_DEVICE_FUNCTION_POINTER is already defined!
#endif

#if !defined(VK_LOAD_LOADER_FUNCTION_POINTER)
#  define VK_LOAD_LOADER_FUNCTION_POINTER(functionName)                        \
    VK_LOAD_FUNCTION_POINTER(nullptr, vkGetInstanceProcAddr, functionName)
#else
#  error VK_LOAD_LOADER_FUNCTION_POINTER is already defined!
#endif

void
LoadDeviceFunctionPointers(VkInstance instance) noexcept
{
}

void
LoadInstanceFunctionPointers(VkInstance instance) noexcept
{
  VK_LOAD_INSTANCE_FUNCTION_POINTER(vkCreateDevice);
  VK_LOAD_INSTANCE_FUNCTION_POINTER(vkDestroyInstance);
  VK_LOAD_INSTANCE_FUNCTION_POINTER(vkEnumerateDeviceExtensionProperties);
  VK_LOAD_INSTANCE_FUNCTION_POINTER(vkEnumerateDeviceLayerProperties);
  VK_LOAD_INSTANCE_FUNCTION_POINTER(vkEnumeratePhysicalDevices);
  VK_LOAD_INSTANCE_FUNCTION_POINTER(vkGetDeviceProcAddr);
}

void
LoadLoaderFunctionPointers() noexcept
{
#if 0
  // Vulkan 1.0
  vkCreateInstance = reinterpret_cast<PFN_vkCreateInstance>(
    vkGetInstanceProcAddr(nullptr, "vkCreateInstance"));
  vkEnumerateInstanceExtensionProperties =
    reinterpret_cast<PFN_vkEnumerateInstanceExtensionProperties>(
      vkGetInstanceProcAddr(nullptr, "vkEnumerateInstanceExtensionProperties"));
  vkEnumerateInstanceLayerProperties =
    reinterpret_cast<PFN_vkEnumerateInstanceLayerProperties>(
      vkGetInstanceProcAddr(nullptr, "vkEnumerateInstanceLayerProperties"));

  // Vulkan 1.1
  vkEnumerateInstanceVersion = reinterpret_cast<PFN_vkEnumerateInstanceVersion>(
    vkGetInstanceProcAddr(nullptr, "vkEnumerateInstanceVersion"));

  // Vulkan 1.0
  VK_LOAD_FUNCTION_POINTER(nullptr, vkGetInstanceProcAddr, vkCreateInstance);
  VK_LOAD_FUNCTION_POINTER(
    nullptr, vkGetInstanceProcAddr, vkEnumerateInstanceExtensionProperties);
  VK_LOAD_FUNCTION_POINTER(
    nullptr, vkGetInstanceProcAddr, vkEnumerateInstanceLayerProperties);

  // Vulkan 1.1
  VK_LOAD_FUNCTION_POINTER(
    nullptr, vkGetInstanceProcAddr, vkEnumerateInstanceVersion);
#endif

  // Vulkan 1.0
  VK_LOAD_LOADER_FUNCTION_POINTER(vkCreateInstance);
  VK_LOAD_LOADER_FUNCTION_POINTER(vkEnumerateInstanceExtensionProperties);
  VK_LOAD_LOADER_FUNCTION_POINTER(vkEnumerateInstanceLayerProperties);

  // Vulkan 1.1
  VK_LOAD_LOADER_FUNCTION_POINTER(vkEnumerateInstanceVersion);
}

} // namespace rmm::rtoolbox::vk
