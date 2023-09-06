module;

#include <string>

export module rmm.RToolBox:Config;

////////////////////////////////////////////////////////////////////////////////
// Interface
////////////////////////////////////////////////////////////////////////////////

export namespace rmm::rtoolbox {

/**
 * @brief Get the library name as a string.
 *
 * @return std::string
 */
constexpr std::string
GetLibraryName();

/**
 * @brief Get the library version as a string.
 *
 * @return constexpr std::string
 */
constexpr std::string
GetVersion();

} // namespace rmm::rtoolbox

////////////////////////////////////////////////////////////////////////////////
// Implementation
////////////////////////////////////////////////////////////////////////////////

namespace rmm::rtoolbox {

namespace {

using namespace std::string_literals;

} // namespace

constexpr std::string
GetLibraryName()
{
  return "RToolBox"s;
}

constexpr std::string
GetVersion()
{
  return "1.0.0"s;
}

} // namespace rmm::rtoolbox
