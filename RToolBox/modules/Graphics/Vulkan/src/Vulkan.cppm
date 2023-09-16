module;

#include <vulkan/vulkan.h>

#include <expected>
#include <vector>

export module rmm.rtoolbox.Vulkan;

export namespace rmm::rtoolbox::vk
{

using Result = VkResult;
using Instance = VkInstance;

using AllocationCallbacks = VkAllocationCallbacks;
using ApplicationInfo = VkApplicationInfo;
using ExtensionProperties = VkExtensionProperties;
using InstanceCreateInfo = VkInstanceCreateInfo;

[[nodiscard]] Result
Initialize();

[[nodiscard]] Result
Initialize(Instance instance);

[[nodiscard]] constexpr std::uint32_t
ApiVersion10() noexcept;

[[nodiscard]] constexpr std::uint32_t
ApiVersion11() noexcept;

[[nodiscard]] constexpr std::uint32_t
MakeVersion(
  std::uint32_t major,
  std::uint32_t minor,
  std::uint32_t patch) noexcept;

[[nodiscard]] std::expected<Instance, Result>
CreateInstance(
  const InstanceCreateInfo* createInfo,
  const AllocationCallbacks* allocator = nullptr);

[[nodiscard]] void
DestroyInstance(
  Instance createInfo,
  const AllocationCallbacks* allocator = nullptr);

[[nodiscard]] std::expected<std::vector<ExtensionProperties>, Result>
EnumerateInstanceExtensionProperties();

} // namespace rmm::rtoolbox::vk

namespace rmm::rtoolbox::vk
{

void
LoadDeviceFunctionPointers(Instance instance) noexcept;

void
LoadInstanceFunctionPointers(Instance instance) noexcept;

void
LoadLoaderFunctionPointers() noexcept;

} // namespace rmm::rtoolbox::vk

namespace rmm::rtoolbox::vk
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

} // namespace rmm::rtoolbox::vk

#include "Vulkan.inc"
