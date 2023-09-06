module;

#include <cstdint>
#include <format>

////////////////////////////////////////////////////////////////////////////////
// Module interface
////////////////////////////////////////////////////////////////////////////////

export module rmm.RToolBox:Geometry.Line;

import :Geometry.Point;

////////////////////////////////////////////////////////////////////////////////
// Public interface
////////////////////////////////////////////////////////////////////////////////

export namespace rmm::rtoolbox {

struct Line
{
  Point p1;
  Point p2;
};

Line
operator+(const Line& lhs, const Line& rhs) noexcept;

}

////////////////////////////////////////////////////////////////////////////////
// Implementation
////////////////////////////////////////////////////////////////////////////////

namespace rmm::rtoolbox {

Line
operator+(const Line& lhs, const Line& rhs) noexcept
{
  Point p1 = lhs.p1 + rhs.p1;
  Point p2 = rhs.p2 + rhs.p2;
  Line point{ p1, p2 };

  return point;
}

}

////////////////////////////////////////////////////////////////////////////////
// `std::format` support
////////////////////////////////////////////////////////////////////////////////

namespace std {

template<class CharT>
struct formatter<::rmm::rtoolbox::Line, CharT>
{
  /**
   * @brief Parse formatter args like padding, precision if you support it
   *
   * @tparam FormatParseContext
   * @param pc
   * @return The iterator to the last parsed character in the format string, in
   * this case we just swallow everything
   */
  template<typename FormatParseContext>
  auto parse(FormatParseContext& pc)
  {
    return pc.end();
  }

  template<typename FormatContext>
  auto format(::rmm::rtoolbox::Line l, FormatContext& fc)
  {
    return std::format_to(fc.out(), "[{}, {}]", l.p1, l.p2);
  }
};

}
