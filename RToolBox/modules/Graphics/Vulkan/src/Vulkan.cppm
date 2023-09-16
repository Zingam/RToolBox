module;

#include <vulkan/vulkan.h>

#include <expected>
#include <string>
#include <vector>

export module rmm.rtoolbox.Vulkan;

////////////////////////////////////////////////////////////////////////////////
// Public interface
////////////////////////////////////////////////////////////////////////////////

export namespace rmm::vk
{

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

// Vulkan types

using Result = VkResult;
using Instance = VkInstance;

using AllocationCallbacks = VkAllocationCallbacks;
using ApplicationInfo = VkApplicationInfo;
using ExtensionProperties = VkExtensionProperties;
using InstanceCreateInfo = VkInstanceCreateInfo;

// Vulkan helper functions

[[nodiscard]] constexpr std::uint32_t
ApiVersion10() noexcept;

[[nodiscard]] constexpr std::uint32_t
ApiVersion11() noexcept;

[[nodiscard]] constexpr std::uint32_t
MakeVersion(
  std::uint32_t major,
  std::uint32_t minor,
  std::uint32_t patch) noexcept;

// Vulkan functions

[[nodiscard]] std::expected<Instance, Result>
CreateInstance(
  Application application,
  Engine engine,
  const AllocationCallbacks* allocator = nullptr);

[[nodiscard]] void
DestroyInstance(
  Instance createInfo,
  const AllocationCallbacks* allocator = nullptr);

[[nodiscard]] std::expected<std::vector<ExtensionProperties>, Result>
EnumerateInstanceExtensionProperties();

} // namespace rmm::vk

////////////////////////////////////////////////////////////////////////////////
// Internal declarations
////////////////////////////////////////////////////////////////////////////////

namespace rmm::vk
{

[[nodiscard]] Result
Initialize();

void
LoadDeviceFunctionPointers(Instance instance) noexcept;

void
LoadInstanceFunctionPointers(Instance instance) noexcept;

void
LoadLoaderFunctionPointers() noexcept;

} // namespace rmm::vk

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

////////////////////////////////////////////////////////////////////////////////
// Function pointers
////////////////////////////////////////////////////////////////////////////////

#include "Vulkan.inc"
