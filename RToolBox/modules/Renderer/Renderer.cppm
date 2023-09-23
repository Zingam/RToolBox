module;

#include <print>
#include <string>
#include <vector>

export module rmm.RToolBox:Renderer;

import rmm.rtoolbox.Vulkan;

////////////////////////////////////////////////////////////////////////////////
// Interface
////////////////////////////////////////////////////////////////////////////////

export namespace rmm::rtoolbox::renderer
{

struct Application;

struct Engine;

void
MakeRenderer(Application&& application, Engine&& engine);

} // namespace rmm::rtoolbox::renderer

////////////////////////////////////////////////////////////////////////////////
// Implementation
////////////////////////////////////////////////////////////////////////////////

namespace rmm::rtoolbox::renderer
{

namespace
{

namespace rvk = ::rmm::vk;
namespace rvkw = ::rmm::vkw;

} // namespace

struct Version
{
  std::uint32_t major;
  std::uint32_t minor;
  std::uint32_t patch;
};

struct Application
{
  const std::string name;
  const Version version;
};

struct Engine
{
  const std::string name;
  const Version version;
};

void
MakeRenderer(
  Application&& application,
  Engine&& engine = { std::string{ "RToolBox" }, 1 })
{
  const auto MakeVersion = [](const Version& version)
  { return rvk::MakeVersion(version.major, version.minor, version.patch); };

  rvkw::Instance instance{ { application.name,
                             MakeVersion(application.version) },
                           { engine.name, MakeVersion(engine.version) } };
  if (nullptr == *instance)
  {
    return;
  }

  const auto extensionsExp =
    rvkw::Instance::EnumerateInstanceExtensionProperties();
  if (!extensionsExp.has_value())
  {
    return;
  }

  for (const auto& extension : *extensionsExp)
  {
    std::print("Extension: {}", extension.extensionName);
  }
}

} // namespace rmm::rtoolbox::renderer
