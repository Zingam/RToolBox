#include <Windows.h>
#include <shellapi.h>

#include <codecvt>
#include <cstdlib>
#include <string>
#include <tuple>

int WINAPI
wWinMain(
  HINSTANCE hInstance,
  HINSTANCE hPrevInstance,
  PWSTR pCmdLine,
  int nCmdShow)
{
  int nArgc;
  LPWSTR* szArgList = CommandLineToArgvW(GetCommandLineW(), &nArgc);

  if (nullptr == szArgList) {
    return EXIT_FAILURE;
  }

  std::wstring wArgvStr{ szArgList[0] };

  const auto utf8_from_wstring = [](const std::wstring& str) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
    return myconv.to_bytes(str);
  };

  std::string argvStr = utf8_from_wstring(wArgvStr);
  auto* argvCStr = const_cast<char*>(argvStr.c_str());
  char** argv = &argvCStr;

  std::tuple<HINSTANCE, WORD> startupParams{ hInstance, nCmdShow };

  return rt_main(nArgc, argv, reinterpret_cast<void*>(&startupParams));
}
