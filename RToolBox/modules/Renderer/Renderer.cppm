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
  namespace rvk = ::rmm::rtoolbox::vk;
  auto result = rvk::Initialize();

  rvk::ApplicationInfo applicationInfo{
    .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
    .pApplicationName = "Hello Triangle",
    .applicationVersion = rvk::MakeVersion(1, 0, 0),
    .pEngineName = "No Engine",
    .engineVersion = rvk::MakeVersion(1, 0, 0),
    .apiVersion = rvk::ApiVersion11()
  };

  rvk::InstanceCreateInfo createInfo{ .sType =
                                        VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
                                      .pApplicationInfo = &applicationInfo };

  auto instanceExp = rvk::CreateInstance(&createInfo, nullptr);
  if (instanceExp.has_value())
  {
    // std::print("has instance {}", *instanceExp);
  }
  else
  {
    // std::print("has instance {}", instanceExp.error());
  }

  rvk::DestroyInstance(*instanceExp);
}

} // namespace rmm::rtoolbox::renderer
