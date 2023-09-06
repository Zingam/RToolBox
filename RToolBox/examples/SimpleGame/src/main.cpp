#include "../../Resources/Windows/resource.h"

import rmm.RToolBox;

namespace {

namespace rt = ::rmm::rtoolbox;

} // namespace

int
main(int argc, char** argv)
{
  rt::Window window{ rt::Window::Description{ "SimpleGame", 0, 0, 100, 100 } };
  const auto* hwnd = window.GetHandle();
  window.SetIcon(IDI_APPICON);
  window.Show();
  window.Run();
}
