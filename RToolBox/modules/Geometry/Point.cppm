module;

#include <cstdint>
#include <format>
#include <string>

export module rmm.RToolBox:Geometry.Point;
// export module rmm.RToolBox.Geometry:Point;

////////////////////////////////////////////////////////////////////////////////
// Public interface
////////////////////////////////////////////////////////////////////////////////

export namespace rmm::rtoolbox {

struct Point
{
  std::int64_t x;
  std::int64_t y;
};

Point
operator+(const Point& lhs, const Point& rhs) noexcept;

}

////////////////////////////////////////////////////////////////////////////////
// Implementation
////////////////////////////////////////////////////////////////////////////////

namespace rmm::rtoolbox {

Point
operator+(const Point& lhs, const Point& rhs) noexcept
{
  Point point{ .x = lhs.x + rhs.y, .y = lhs.y + rhs.y };

  return point;
}

}

////////////////////////////////////////////////////////////////////////////////
// `std::format` support
////////////////////////////////////////////////////////////////////////////////

namespace std {

template<class CharT>
struct formatter<::rmm::rtoolbox::Point, CharT>
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
  auto format(::rmm::rtoolbox::Point p, FormatContext& fc)
  {
    return std::format_to(fc.out(), "[{}, {}]", p.x, p.y);
  }
};

}
