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
  auto instanceExp = rvk::CreateInstance(
    { application.name,
      rvk::MakeVersion(
        application.version.major,
        application.version.minor,
        application.version.patch) },
    { engine.name,
      rvk::MakeVersion(
        engine.version.major, engine.version.minor, engine.version.patch) });
  if (instanceExp.has_value())
  {
    // std::print("has instance {}", *instanceExp);
  }
  else
  {
    // std::print("has instance {}", instanceExp.error());
  }

  rvk::DestroyInstance(*instanceExp);
  rvk::vkDestroyInstance(*instanceExp, nullptr);
}

} // namespace rmm::rtoolbox::renderer
