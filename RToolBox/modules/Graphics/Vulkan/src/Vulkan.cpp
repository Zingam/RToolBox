module;

#include <vulkan/vulkan.h>

#include <expected>

module rmm.rtoolbox.Vulkan;

namespace rmm::vk
{

std::expected<Instance, Result>
CreateInstance(
  Application application,
  Engine engine,
  const AllocationCallbacks* allocator)
{
  if (auto result = Initialize(); VK_SUCCESS != result)
  {
    return std::unexpected{ result };
  }

  ApplicationInfo applicationInfo{ .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
                                   .pApplicationName = application.name.c_str(),
                                   .applicationVersion = application.version,
                                   .pEngineName = engine.name.c_str(),
                                   .engineVersion = engine.version,
                                   .apiVersion = ApiVersion11() };

  InstanceCreateInfo createInfo{ .sType =
                                   VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
                                 .pApplicationInfo = &applicationInfo };
  Instance instance{};
  if (auto result = vkCreateInstance(&createInfo, allocator, &instance);
      VK_SUCCESS != result)
  {
    return std::unexpected{ result };
  }

  LoadInstanceFunctionPointers(instance);
  LoadDeviceFunctionPointers(instance);

  return instance;
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
  // Vulkan 1.0
  VK_LOAD_LOADER_FUNCTION_POINTER(vkCreateInstance);
  VK_LOAD_LOADER_FUNCTION_POINTER(vkEnumerateInstanceExtensionProperties);
  VK_LOAD_LOADER_FUNCTION_POINTER(vkEnumerateInstanceLayerProperties);

  // Vulkan 1.1
  VK_LOAD_LOADER_FUNCTION_POINTER(vkEnumerateInstanceVersion);
}

} // namespace rmm::vk
