module;

#include <Windows.h>

#include <array>
#include <iostream>
#include <ostream>
#include <sstream>
#include <streambuf>
#include <string>

export module rmm.RToolBox:OStreamRedirection;

export
{
  /**
   * @brief Setup standard streams redirection to `OutputDebugString`.
   *
   */
  void SetupOStreamRedirection();
}

/**
 * \brief This class is a derivate of `basic_stringbuf` which will output all
 * the written data using the `OutputDebugString` function.
 */
template<typename TChar, typename TTraits = std::char_traits<TChar>>
class OutputDebugStringBuf : public std::basic_stringbuf<TChar, TTraits>
{
  using BSBuff = std::basic_stringbuf<TChar, TTraits>;

public:
  OutputDebugStringBuf()
  {
    BSBuff::setg(nullptr, nullptr, nullptr);
    BSBuff::setp(
      _buffer.data(), _buffer.data(), _buffer.data() + _buffer.size());
  }

  ~OutputDebugStringBuf() {}

  static_assert(
    std::is_same<TChar, char>::value || std::is_same<TChar, wchar_t>::value,
    "OutputDebugStringBuf only supports char and wchar_t types");

  int sync()
  {
    try {
      MessageOutputer<TChar, TTraits>()(BSBuff::pbase(), BSBuff::pptr());

      BSBuff::setp(
        _buffer.data(), _buffer.data(), _buffer.data() + _buffer.size());

      return 0;
    } catch (...) {
      return -1;
    }
  }

  std::char_traits<char>::int_type overflow(
    std::char_traits<char>::int_type c = TTraits::eof())
  {
    int syncRet = sync();
    if (c != TTraits::eof()) {
      _buffer[0] = c;
      BSBuff::setp(
        _buffer.data(), _buffer.data() + 1, _buffer.data() + _buffer.size());
    }
    return (syncRet == -1) ? TTraits::eof() : 0;
  }

private:
  std::array<TChar, 1024> _buffer;

  template<typename TChar, typename TTraits>
  struct MessageOutputer;

  template<>
  struct MessageOutputer<char, std::char_traits<char>>
  {
    template<typename TIterator>
    void operator()(TIterator begin, TIterator end) const
    {
      std::string s(begin, end);
      OutputDebugStringA(s.c_str());
    }
  };

  template<>
  struct MessageOutputer<wchar_t, std::char_traits<wchar_t>>
  {
    template<typename TIterator>
    void operator()(TIterator begin, TIterator end) const
    {
      std::wstring s(begin, end);
      OutputDebugStringW(s.c_str());
    }
  };
};

void
SetupOStreamRedirection()
{
#ifndef NDEBUG
#  ifdef _WIN32
  static OutputDebugStringBuf<char> charDebugOutput;
  std::cerr.rdbuf(&charDebugOutput);
  std::clog.rdbuf(&charDebugOutput);

  static OutputDebugStringBuf<wchar_t> wcharDebugOutput;
  std::wcerr.rdbuf(&wcharDebugOutput);
  std::wclog.rdbuf(&wcharDebugOutput);
#  endif
#endif
}
