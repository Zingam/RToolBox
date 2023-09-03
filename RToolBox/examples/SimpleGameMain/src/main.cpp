#include <chrono>
#include <memory>
#include <print>
#include <thread>

#include "../../Resources/Windows/resource.h"

import rmm.RToolBox;

namespace {

namespace rt = ::rmm::rtoolbox;
using namespace std::chrono_literals;

} // namespace

namespace {

std::unique_ptr<rt::Point> pointPtr;

void
MakePoint(rt::Point** pointPPtr)
{
  *pointPPtr = new rt::Point{ 2, 2 };
}

} // namespace

int
rt_main(int argc, char** argv)
{
  std::println("Starting a SimpleGame...");

  std::println("Hello, World: {} v{}", rt::GetLibraryName(), rt::GetVersion());

  MakePoint(std::out_ptr(pointPtr));
  std::println("Point by 'std::out_ptr': {}", *pointPtr);

  rt::Point p1{ 1, 2 };
  rt::Point p2{ 2, 3 };

  const auto p3 = rt::operator+(p1, p2);
  const auto p4 = p3 + p2 + p1;

  std::println("Point: {}", p3);
  std::println("Point: {}", p4);

  rt::Line l1{ { 1, 2 }, { 2, 3 } };
  rt::Line l2{ { 1, 2 }, { 2, 3 } };

  const auto l3 = rt::operator+(l1, l2);
  const auto l4 = l3 + l2 + l1;

  std::println("Line: {}", l3);
  std::println("Line: {}", l4);

  rt::renderer::MakeRenderer({ "SampleGame", 1 });

  rt::Window window{rt::Window::Description{ "SimpleGame", 0, 0, 100, 100 }};
  const auto* hwnd = window.GetHandle();
  window.SetIcon(IDI_APPICON);
  window.Show();
  window.Run();

  std::println("Quitting SimpleGame!");

  std::this_thread::sleep_for(2s);

  return EXIT_SUCCESS;
}
