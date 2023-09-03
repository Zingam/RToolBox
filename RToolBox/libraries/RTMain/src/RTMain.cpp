#include <cxxopts.hpp>
#include <print>

extern "C++"
{
  int rt_main(int argc, char** argv);
}

int
main(int argc, char** argv)
{
  std::println("Starting a SimpleGameMain...");

  cxxopts::Options options("MyProgram", "One line description of MyProgram");

  auto result = options.parse(argc, argv);

  return rt_main(argc, argv);
}
