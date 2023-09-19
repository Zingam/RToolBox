module;

#include <vulkan/vulkan.h>

#include <expected>
#include <functional>
#include <string>
#include <string_view>
#include <vector>

export module rmm.rtoolbox.Vulkan;

////////////////////////////////////////////////////////////////////////////////
// Public interface
////////////////////////////////////////////////////////////////////////////////

export namespace rmm::vk
{

// Types

#include "VulkanTypes.inc"

// Helper functions

[[nodiscard]] constexpr std::uint32_t
ApiVersion10() noexcept;

[[nodiscard]] constexpr std::uint32_t
ApiVersion11() noexcept;

[[nodiscard]] constexpr std::uint32_t
MakeVersion(
  std::uint32_t major,
  std::uint32_t minor,
  std::uint32_t patch) noexcept;

// Function pointers

#include "VulkanFunctions.inc"

} // namespace rmm::vk

export namespace rmm::vkw
{

// Application types

struct Application
{
  const std::string name;
  const std::uint32_t version;
};

struct Engine
{
  const std::string name;
  const std::uint32_t version;
};

// Vulkan wrapper functions

[[nodiscard]] std::expected<vk::Instance, vk::Result>
CreateInstance(
  Application application,
  Engine engine,
  const vk::AllocationCallbacks* allocator = nullptr);

class DebugUtils
{
public:
  VkBool32 (*debugCallbackFunctionPointer)(
    VkDebugUtilsMessageSeverityFlagBitsEXT,
    VkDebugUtilsMessageTypeFlagsEXT,
    const VkDebugUtilsMessengerCallbackDataEXT*,
    void*);
  VkBool32(debugCallbackFunctionType)(
    VkDebugUtilsMessageSeverityFlagBitsEXT,
    VkDebugUtilsMessageTypeFlagsEXT,
    const VkDebugUtilsMessengerCallbackDataEXT*,
    void*);
  using CallbackFunctionPointer = VkBool32 (*)(
    VkDebugUtilsMessageSeverityFlagBitsEXT,
    VkDebugUtilsMessageTypeFlagsEXT,
    const VkDebugUtilsMessengerCallbackDataEXT*,
    void*);
  using CallbackFunctionType = VkBool32(
    VkDebugUtilsMessageSeverityFlagBitsEXT,
    VkDebugUtilsMessageTypeFlagsEXT,
    const VkDebugUtilsMessengerCallbackDataEXT*,
    void*);
  using DebugCallback = VkBool32(
    VkDebugUtilsMessageSeverityFlagBitsEXT,
    VkDebugUtilsMessageTypeFlagsEXT,
    const VkDebugUtilsMessengerCallbackDataEXT*,
    void*);

public:
  DebugUtils(vk::Instance instance);

  ~DebugUtils();

public:
  vk::Result CreateMessanger();

  vk::Result DestroyMessanger();

  void SetCallback(std::function<DebugCallback>);

private:
  const vk::Instance instance;
  std::function<VkBool32()> debugCallback1;
  std::function<VkBool32(
    VkDebugUtilsMessageSeverityFlagBitsEXT,
    VkDebugUtilsMessageTypeFlagsEXT,
    const VkDebugUtilsMessengerCallbackDataEXT*,
    void*)>
    debugCallback2;
  std::function<DebugCallback> debugCallback;
};

[[nodiscard]] std::expected<std::vector<vk::ExtensionProperties>, vk::Result>
EnumerateInstanceExtensionProperties(std::string_view layerName = {});

[[nodiscard]] std::expected<std::vector<vk::LayerProperties>, vk::Result>
EnumerateInstanceLayerProperties();

} // namespace rmm::vkw

////////////////////////////////////////////////////////////////////////////////
// Internal declarations
////////////////////////////////////////////////////////////////////////////////

namespace rmm::vkw
{

vk::Result
Initialize();

vk::Result
LoadDeviceFunctionPointers(vk::Instance instance) noexcept;

vk::Result
LoadInstanceFunctionPointers(vk::Instance instance) noexcept;

vk::Result
LoadLoaderFunctionPointers() noexcept;

} // namespace rmm::vkw

////////////////////////////////////////////////////////////////////////////////
// Implementation
////////////////////////////////////////////////////////////////////////////////

namespace rmm::vk
{

[[nodiscard]] constexpr std::uint32_t
ApiVersion10() noexcept
{
  return VK_API_VERSION_1_0;
}

[[nodiscard]] constexpr std::uint32_t
ApiVersion11() noexcept
{
  return VK_API_VERSION_1_1;
}

[[nodiscard]] constexpr std::uint32_t
MakeVersion(
  std::uint32_t major,
  std::uint32_t minor,
  std::uint32_t patch) noexcept
{
  return VK_MAKE_VERSION(major, minor, patch);
}

} // namespace rmm::vk
