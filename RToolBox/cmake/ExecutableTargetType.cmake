include_guard()

function(set_executable_type target)
  if (WIN32)
    set_property(TARGET "${target}"
      PROPERTY
        WIN32_EXECUTABLE TRUE
    )
  endif()
endfunction()
