module;

#include <Windows.h>

#include <codecvt>
#include <memory>
#include <print>
#include <string>

// Should match the icon number defined in `resource.h`.
#define IDI_APPICON 101

module rmm.RToolBox;

namespace rmm::rtoolbox {

class Window::Window_Implementation
{
public:
  Window_Implementation(Window::Description&& description);

  ~Window_Implementation();

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
  Window::Description description;
};

Window::Window_Implementation::Window_Implementation(
  Window::Description&& description)
  : description{ std::move(description) }
{
  if (NULL == Initialize()) {
    ::MessageBox(
      NULL,
      L"Window Registration Failed!",
      L"Error!",
      MB_ICONEXCLAMATION | MB_OK);
  }
}

Window::Window_Implementation::~Window_Implementation()
{
  if (NULL != hwnd) {
    ::DestroyWindow(hwnd);
  }
}

void
Window::Window_Implementation::Hide() const
{
  ::ShowWindow(hwnd, SW_HIDE);
}

void
Window::Window_Implementation::Show() const
{
  ::STARTUPINFO si;
  ::GetStartupInfo(&si);
  int nCmdShow = si.wShowWindow;

  ::ShowWindow(hwnd, nCmdShow);
  ::UpdateWindow(hwnd);
}

void
Window::Window_Implementation::Run() const
{
  //---- Message Loop ----------//
  MSG msg;
  auto isRunning{ true };
  while (isRunning) {
    while (::PeekMessage(&msg, HWND(), 0, 0, PM_REMOVE)) {
      if (msg.message == WM_QUIT) {
        isRunning = false;
        continue;
      } else {
        ::TranslateMessage(&msg);
        ::DispatchMessage(&msg);
      }
      ::Sleep(0);
    }
  }
}

void*
Window::Window_Implementation::GetHandle() const noexcept
{
  return hwnd;
}

void
Window::Window_Implementation::SetIcon(Window::ResourceID icon) const noexcept
{
  const HMODULE hInstance = ::GetModuleHandle(nullptr);
  const HICON hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(icon));
  SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
  SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
}

HWND
Window::Window_Implementation::Initialize() noexcept
{
  if (NULL != hwnd) {
    return hwnd;
  }

  // Register the window class.
  WNDCLASS wc = {};

  const auto utf8_to_wstring = [](const std::string& str) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
    return myconv.from_bytes(str);
  };

  auto titleStr = utf8_to_wstring(description.title);

  wc.lpfnWndProc = &Window_Implementation::WindowProcedure;
  wc.hInstance = ::GetModuleHandle(nullptr);
  // wc.hIcon = LoadIcon(wc.hInstance, MAKEINTRESOURCE(IDI_APPICON));
  wc.lpszClassName = titleStr.c_str();

  ::RegisterClass(&wc);

  // Create the window.

  hwnd = ::CreateWindowEx(
    0,                   // Optional window styles
    titleStr.c_str(),    // Window class
    titleStr.c_str(),    // Window text
    WS_OVERLAPPEDWINDOW, // Window style

    // Size and position
    CW_USEDEFAULT,
    CW_USEDEFAULT,
    CW_USEDEFAULT,
    CW_USEDEFAULT,

    NULL,         // Parent window
    NULL,         // Menu
    wc.hInstance, // Instance handle
    NULL          // Additional application data
  );
}

LRESULT
Window::Window_Implementation::WindowProcedure(
  HWND hwnd,
  UINT msg,
  WPARAM wParam,
  LPARAM lParam)
{
  // Process messages
  switch (msg) {
    case WM_CLOSE:
      ::DestroyWindow(hwnd);
      break;
    case WM_CREATE:
      break;
    case WM_DESTROY:
      ::PostQuitMessage(0);
      break;
    case WM_KEYDOWN:
      if (wParam == VK_ESCAPE) {
        ::DestroyWindow(hwnd);
        break;
      }
      ::MessageBox(
        NULL,
        L"Button pressed",
        L"Button pressed!",
        // `MB_DEFAULT_DESKTOP_ONLY` is needed if the program handles
        // `WM_PAINT`.
        MB_ICONEXCLAMATION | MB_OK | MB_DEFAULT_DESKTOP_ONLY);
      std::println("Button pressed: {}", wParam);
    case WM_MOVE:
      break;
    case WM_PAINT: {
      // In case of `WM_PAINT` add `MB_DEFAULT_DESKTOP_ONLY` to `MessageBox`
    } break;
    default:
      return ::DefWindowProc(hwnd, msg, wParam, lParam);
  }

  return NULL;
}

} // namespace rmm::rtoolbox

#include "Window.inc"
