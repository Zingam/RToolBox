module;

#include <print>
#include <string>

export module rmm.RToolBox:Renderer;

import vulkan;

////////////////////////////////////////////////////////////////////////////////
// Interface
////////////////////////////////////////////////////////////////////////////////

export namespace rmm::rtoolbox::renderer {

struct Application;

struct Engine;

void
MakeRenderer(Application&& application, Engine&& engine);

} // namespace rmm::rtoolbox::renderer

////////////////////////////////////////////////////////////////////////////////
// Implementation
////////////////////////////////////////////////////////////////////////////////

namespace rmm::rtoolbox::renderer {

struct Application
{
  const std::string app_name;
  const std::uint32_t version;
};

struct Engine
{
  const std::string name;
  const std::uint32_t version;
};

void
MakeRenderer(
  Application&& application,
  Engine&& engine = { std::string{ "RToolBox" }, 1 })
{
  // Initialize the vk::ApplicationInfo structure
  // vk::ApplicationInfo applicationInfo{};
  // applicationInfo.pApplicationName = application.app_name.data();
  // applicationInfo.applicationVersion = application.version,
  // applicationInfo.pEngineName = engine.name.data(),
  // applicationInfo.engineVersion = engine.version,
  // applicationInfo.apiVersion = vk::ApiVersion11;

  const vk::ApplicationInfo applicationInfo{
    .pApplicationName = application.app_name.c_str(),
    .applicationVersion = application.version,
    .pEngineName = engine.name.c_str(),
    .engineVersion = engine.version,
    .apiVersion = vk::ApiVersion11,
  };

  std::uint32_t instanceExtensionPropertiesCount = 0;
  auto result = vk::enumerateInstanceExtensionProperties(
    nullptr, &instanceExtensionPropertiesCount, nullptr);

  std::vector<vk::ExtensionProperties> instanceExtensionProperties(
    instanceExtensionPropertiesCount);
  result = vk::enumerateInstanceExtensionProperties(
    nullptr,
    &instanceExtensionPropertiesCount,
    instanceExtensionProperties.data());

  std::println(
    "Vulkan instance extensions: {}", instanceExtensionPropertiesCount);
  for (const auto& [extensionName, specVersion] : instanceExtensionProperties) {
    std::println("  {}, spec ver.: {}", extensionName.data(), specVersion);
  }

  // Initialize the vk::InstanceCreateInfo
  vk::InstanceCreateInfo instanceCreateInfo{};
  instanceCreateInfo.pNext = nullptr;
  instanceCreateInfo.flags = vk::InstanceCreateFlags{};
  instanceCreateInfo.pApplicationInfo = &applicationInfo,
  instanceCreateInfo.enabledLayerCount = 0;
  instanceCreateInfo.ppEnabledLayerNames = nullptr;
  instanceCreateInfo.enabledExtensionCount = 0;
  instanceCreateInfo.ppEnabledExtensionNames = nullptr;

  std::println("Creating a Vulkan instance!");

  const vk::Instance instance = vk::createInstance(instanceCreateInfo);

  instance.destroy();
}

} // namespace rmm::rtoolbox::renderer
