#include "Resources/Windows/resource.h"

#include <cstdlib>
#include <string>

import rmm.RToolBox;

namespace {

namespace rt = ::rmm::rtoolbox;

} // namespace

int
rt_main(int argc, char** argv)
{
  rt::Window window{ rt::Window::Description{ "SimpleGame", 0, 0, 100, 100 } };
  const auto* hwnd = window.GetHandle();
  window.SetIcon(IDI_APPICON);
  window.Show();
  window.Run();

  return EXIT_SUCCESS;
}
