extern "C++"
{
  int rt_main(int argc, char** argv, void* data);
}

#if _WINDOWS
#  include "Platform/RTMain_Windows.cpp"
#endif
