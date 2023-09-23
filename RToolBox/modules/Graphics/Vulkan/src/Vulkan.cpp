module;

#include <vulkan/vulkan.h>

#include <cassert>
#include <expected>
#include <string_view>

module rmm.rtoolbox.Vulkan;

namespace rmm::vkw
{

// Constructors & Destructors

Instance::Instance(
  Application&& application,
  Engine&& engine,
  const vk::AllocationCallbacks* allocator)
  : allocator{ allocator }
{
  const auto instanceExp =
    Create(std::move(application), std::move(engine), allocator);
  if (!instanceExp.has_value())
  {
    return;
  }

  instance = instanceExp.value();
}

Instance::~Instance()
{
  if (nullptr != instance)
  {
    vk::DestroyInstance(instance, allocator);
    instance = nullptr;
  }
}

// Methods

vk::Instance
Instance::operator*() noexcept
{
  return instance;
}

vk::Instance
Instance::Get() noexcept
{
  return instance;
}

// Static methods

std::expected<vk::Instance, vk::Result>
Instance::Create(
  Application application,
  Engine engine,
  const vk::AllocationCallbacks* allocator)
{
  if (const auto result = Initialize(); VK_SUCCESS != result)
  {
    return std::unexpected{ result };
  }

  const vk::ApplicationInfo applicationInfo{
    .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
    .pApplicationName = application.name.c_str(),
    .applicationVersion = application.version,
    .pEngineName = engine.name.c_str(),
    .engineVersion = engine.version,
    .apiVersion = vk::ApiVersion11()
  };

  const vk::InstanceCreateInfo createInfo{
    .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
    .pNext = nullptr,
    .flags{},
    .pApplicationInfo = &applicationInfo,
    .enabledLayerCount{},
    .ppEnabledLayerNames{},
    .enabledExtensionCount{},
    .ppEnabledExtensionNames{}
  };

  vk::Instance instance{};
  if (const auto result = vk::CreateInstance(&createInfo, allocator, &instance);
      VK_SUCCESS != result)
  {
    return std::unexpected{ result };
  }

  if (const auto result = LoadInstanceFunctionPointers(instance);
      VK_SUCCESS == result)
  {
    std::unexpected{ result };
  }
  if (const auto result = LoadDeviceFunctionPointers(instance);
      VK_SUCCESS != result)
  {
    std::unexpected{ result };
  }

  return instance;
}

std::expected<std::vector<vk::ExtensionProperties>, vk::Result>
Instance::EnumerateInstanceExtensionProperties(std::string_view layerName)
{
  assert(layerName.data() == nullptr);
  std::uint32_t extensionCount = 0;
  if (const auto result = vk::EnumerateInstanceExtensionProperties(
        layerName.data(), &extensionCount, nullptr);
      VK_SUCCESS != result)
  {
    return std::unexpected{ result };
  }

  std::vector<vk::ExtensionProperties> extensions(extensionCount);
  if (const auto result = vk::EnumerateInstanceExtensionProperties(
        layerName.data(), &extensionCount, extensions.data());
      VK_SUCCESS != result)
  {
    return std::unexpected{ result };
  }

  return extensions;
}

std::expected<std::vector<vk::LayerProperties>, vk::Result>
Instance::EnumerateInstanceLayerProperties()
{
  std::uint32_t layerCount = 0;
  if (const auto result =
        vk::EnumerateInstanceLayerProperties(&layerCount, nullptr);
      VK_SUCCESS != result)
  {
    return std::unexpected{ result };
  }

  std::vector<vk::LayerProperties> layers(layerCount);
  if (const auto result =
        vk::EnumerateInstanceLayerProperties(&layerCount, layers.data());
      VK_SUCCESS != result)
  {
    return std::unexpected{ result };
  }

  return layers;
}

} // namespace rmm::vkw

////////////////////////////////////////////////////////////////////////////////
// Function pointer loaders
////////////////////////////////////////////////////////////////////////////////

#if !defined(VK_STRINGIFY)
#  define VK_STRINGIFY(token) #token
#else
#  error 'VK_STRINGIFY' is already defined
#endif

#if !defined(VK_CONCAT)
#  define VK_CONCAT(lhs, rhs) VK_STRINGIFY(lhs##rhs)
#else
#  error 'VK_CONCAT' is already defined
#endif

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
    do                                                                         \
    {                                                                          \
      vk::##functionName = reinterpret_cast<PFN_vk##functionName>(             \
        loaderName(instance, VK_CONCAT(vk, functionName)));                    \
      if (nullptr == vk::##functionName)                                       \
      {                                                                        \
        return VK_ERROR_INITIALIZATION_FAILED;                                 \
      }                                                                        \
    } while (false)
#else
#  error 'VK_LOAD_FUNCTION_POINTER' already defined!
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
    VK_LOAD_FUNCTION_POINTER(instance, vk::GetInstanceProcAddr, functionName)
#else
#  error 'VK_LOAD_INSTANCE_FUNCTION_POINTER' is already defined!
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
    VK_LOAD_FUNCTION_POINTER(instance, vk::GetDeviceProcAddr, functionName)
#else
#  error 'VK_LOAD_DEVICE_FUNCTION_POINTER' is already defined!
#endif

#if !defined(VK_LOAD_LOADER_FUNCTION_POINTER)
#  define VK_LOAD_LOADER_FUNCTION_POINTER(functionName)                        \
    VK_LOAD_FUNCTION_POINTER(nullptr, vk::GetInstanceProcAddr, functionName)
#else
#  error 'VK_LOAD_LOADER_FUNCTION_POINTER' is already defined!
#endif

namespace rmm::vkw
{

vk::Result
LoadDeviceFunctionPointers(vk::Instance instance) noexcept
{
  return VK_SUCCESS;
}

vk::Result
LoadInstanceFunctionPointers(vk::Instance instance) noexcept
{
  VK_LOAD_INSTANCE_FUNCTION_POINTER(CreateDevice);
  VK_LOAD_INSTANCE_FUNCTION_POINTER(DestroyInstance);
  VK_LOAD_INSTANCE_FUNCTION_POINTER(EnumerateDeviceExtensionProperties);
  VK_LOAD_INSTANCE_FUNCTION_POINTER(EnumerateDeviceLayerProperties);
  VK_LOAD_INSTANCE_FUNCTION_POINTER(EnumeratePhysicalDevices);
  VK_LOAD_INSTANCE_FUNCTION_POINTER(GetDeviceProcAddr);

  return VK_SUCCESS;
}

vk::Result
LoadLoaderFunctionPointers() noexcept
{
  // Vulkan 1.0
  VK_LOAD_LOADER_FUNCTION_POINTER(CreateInstance);
  VK_LOAD_LOADER_FUNCTION_POINTER(EnumerateInstanceExtensionProperties);
  VK_LOAD_LOADER_FUNCTION_POINTER(EnumerateInstanceLayerProperties);

  // Vulkan 1.1
  VK_LOAD_LOADER_FUNCTION_POINTER(EnumerateInstanceVersion);

  return VK_SUCCESS;
}

} // namespace rmm::vkw
