module;

#include <vulkan/vulkan.h>

#include <cstdint>
#include <expected>
#include <functional>
#include <string>
#include <string_view>
#include <vector>

export module rmm.rtoolbox.Vulkan;

////////////////////////////////////////////////////////////////////////////////
// Public interface
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Vulkan native functions and types.
 *
 */
export namespace rmm::vk
{

// Types

#include "VulkanTypes.inc" /

// Function pointers

#include "VulkanFunctions.inc"

// Extensions

#include "VulkanExtensions.inc"

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

} // namespace rmm::vk

/**
 * @brief Vulkan wrapper and helper types.
 *
 */
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

class Instance
{
public:
  explicit Instance(
    Application&& application,
    Engine&& engine,
    const vk::AllocationCallbacks* allocator = nullptr);

  Instance(const Instance&) = delete;

  Instance& operator=(const Instance&) = delete;

  Instance(Instance&&) = default;

  Instance& operator=(Instance&&) = default;

  ~Instance();

public:
  [[nodiscard]] vk::Instance operator*() noexcept;

  [[nodiscard]] vk::Instance Get() noexcept;

public:
  [[nodiscard]] static std::expected<vk::Instance, vk::Result> Create(
    Application application,
    Engine engine,
    const vk::AllocationCallbacks* allocator = nullptr);

  [[nodiscard]] static std::
    expected<std::vector<vk::ExtensionProperties>, vk::Result>
    EnumerateInstanceExtensionProperties(std::string_view layerName = {});

  [[nodiscard]] static std::
    expected<std::vector<vk::LayerProperties>, vk::Result>
    EnumerateInstanceLayerProperties();

  [[nodiscard]] static std::vector<const char*> GetRequiredInstanceExtensions();

private:
  const vk::AllocationCallbacks* allocator;
  vk::Instance instance = nullptr;
};

class DebugUtils
{
public:
  using DebugCallback = vk::Bool32(
    vk::DebugUtilsMessageSeverityFlagBits,
    vk::DebugUtilsMessageTypeFlags,
    const vk::DebugUtilsMessengerCallbackData*,
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

  std::function<DebugCallback> debugCallback;
};

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

////////////////////////////////////////////////////////////////////////////////
// Private section
////////////////////////////////////////////////////////////////////////////////

module :private;

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
