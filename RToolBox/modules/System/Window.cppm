module;

#include <memory>
#include <string>

export module rmm.RToolBox:System.Window;

////////////////////////////////////////////////////////////////////////////////
// Interface
////////////////////////////////////////////////////////////////////////////////

export namespace rmm::rtoolbox
{

class Window
{
public:
  struct Description
  {
    std::string title;
    std::uint32_t x;
    std::uint32_t y;
    std::uint32_t height;
    std::uint32_t width;
  };

  using Handle = void*;
  using ResourceID = unsigned int;

public:
  Window(Description&& description, void* data = nullptr);

  ~Window();

public:
  void Hide() const;
  void Show() const;

  void Run() const;

  [[nodiscard]] Handle GetHandle() const noexcept;
  void SetIcon(ResourceID icon) const noexcept;

private:
  class Implementation;

private:
  std::unique_ptr<Implementation> oPtr;
};

} // namespace rmm::rtoolbox
