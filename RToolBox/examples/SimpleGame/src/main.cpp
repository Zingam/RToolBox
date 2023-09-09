#include "Resources/Windows/resource.h"

#if _WINDOWS
#include <Windows.h>
#endif

#include <tuple>

import rmm.RToolBox;

namespace {

namespace rt = ::rmm::rtoolbox;

} // namespace

#if _WINDOWS
int WINAPI
wWinMain(
  HINSTANCE hInstance,
  HINSTANCE hPrevInstance,
  PWSTR pCmdLine,
  int nCmdShow)
#else
int
main(int argc, char** argv)
#endif
{
  std::tuple<HINSTANCE, WORD> startupParams{hInstance, nCmdShow};
  rt::Window window{ rt::Window::Description{ "SimpleGame", 0, 0, 100, 100 }, reinterpret_cast<void*>(&startupParams)};
  const auto* hwnd = window.GetHandle();
  window.SetIcon(IDI_APPICON);
  window.Show();
  window.Run();
}
