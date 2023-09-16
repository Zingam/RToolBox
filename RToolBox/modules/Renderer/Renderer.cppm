module;

#include <string>
#include <vector>

export module rmm.RToolBox:Renderer;

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
}

} // namespace rmm::rtoolbox::renderer
