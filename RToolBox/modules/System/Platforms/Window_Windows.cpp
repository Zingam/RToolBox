module;

#include <Windows.h>

#include <cassert>
#include <codecvt>
#include <memory>
#include <string>

module rmm.RToolBox;

namespace rmm::rtoolbox
{

class Window::Implementation
{
public:
  explicit Implementation(Window::Description&& description, void* data);

  ~Implementation();

public:
  void Hide() const;
  void Show() const;

  void Run() const;

  void* GetHandle() const noexcept;
  void SetIcon(Window::ResourceID icon) const noexcept;

private:
  HWND Initialize() noexcept;

private:
  static LRESULT CALLBACK
  WindowProcedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

private:
  HWND hwnd{ NULL };
  HINSTANCE hInstance{};
  WORD nCmdShow{};
  Window::Description description;
};

Window::Implementation::Implementation(
  Window::Description&& description,
  void* data)
  : description{ std::move(description) }
{
  assert(nullptr != data && "'WinMain()' startup parameters cannot be empty!");

  auto* startupParams = reinterpret_cast<std::tuple<HINSTANCE, WORD>*>(data);
  hInstance = std::get<0>(*startupParams);
  nCmdShow = std::get<1>(*startupParams);

  if (NULL == Initialize())
  {
    ::MessageBox(
      NULL,
      L"Window Registration Failed!",
      L"Error!",
      MB_ICONEXCLAMATION | MB_OK);
  }
}

Window::Implementation::~Implementation()
{
  if (NULL != hwnd)
  {
    ::DestroyWindow(hwnd);
  }
}

void
Window::Implementation::Hide() const
{
  ::ShowWindow(hwnd, SW_HIDE);
}

void
Window::Implementation::Show() const
{
  ::ShowWindow(hwnd, nCmdShow);
  ::UpdateWindow(hwnd);
}

void
Window::Implementation::Run() const
{
  MSG msg;
  auto isRunning{ true };
  while (isRunning)
  {
    while (::PeekMessage(&msg, HWND(), 0, 0, PM_REMOVE))
    {
      if (msg.message == WM_QUIT)
      {
        isRunning = false;
        continue;
      }
      else
      {
        ::TranslateMessage(&msg);
        ::DispatchMessage(&msg);
      }
      ::Sleep(0);
    }
  }
}

void*
Window::Implementation::GetHandle() const noexcept
{
  return hwnd;
}

void
Window::Implementation::SetIcon(Window::ResourceID icon) const noexcept
{
  const HMODULE hInstance = ::GetModuleHandle(nullptr);
  const HICON hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(icon));
  SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
  SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
}

HWND
Window::Implementation::Initialize() noexcept
{
  if (nullptr != hwnd)
  {
    return hwnd;
  }

  // Register the window class.

  const auto utf8_to_wstring = [](const std::string& str)
  {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
    return myconv.from_bytes(str);
  };

  auto titleStr = utf8_to_wstring(description.title);

  WNDCLASSEXW wcex{ .cbSize = sizeof(WNDCLASSEXW),
                    .style = CS_HREDRAW | CS_VREDRAW,
                    .lpfnWndProc = &Implementation::WindowProcedure,
                    .cbClsExtra = 0,
                    .cbWndExtra = 0,
                    .hInstance = ::GetModuleHandle(nullptr),
                    .hIcon = nullptr,
                    .hCursor = LoadCursor(nullptr, IDC_CROSS),
                    .hbrBackground = (HBRUSH)(COLOR_WINDOW + 1),
                    .lpszMenuName = nullptr,
                    .lpszClassName = titleStr.c_str(),
                    .hIconSm = nullptr };

  ::RegisterClassEx(&wcex);

  // Create the window.

  hwnd = CreateWindowEx(
    0,
    titleStr.c_str(),
    titleStr.c_str(),
    WS_OVERLAPPEDWINDOW,
    CW_USEDEFAULT,
    0,
    CW_USEDEFAULT,
    0,
    nullptr,
    nullptr,
    ::GetModuleHandle(nullptr),
    nullptr);

  return hwnd;
}

LRESULT
Window::Implementation::WindowProcedure(
  HWND hwnd,
  UINT msg,
  WPARAM wParam,
  LPARAM lParam)
{
  // Process messages
  switch (msg)
  {
    case WM_CLOSE:
      ::DestroyWindow(hwnd);
      break;
    case WM_CREATE:
      break;
    case WM_DESTROY:
      ::PostQuitMessage(0);
      break;
    case WM_KEYDOWN:
      if (wParam == VK_ESCAPE)
      {
        ::DestroyWindow(hwnd);
        break;
      }
    default:
      return ::DefWindowProc(hwnd, msg, wParam, lParam);
  }

  return NULL;
}

} // namespace rmm::rtoolbox

#include "Window.inc"
