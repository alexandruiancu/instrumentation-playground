find_package(cppzmq)

if(cppzmq_FOUND)
   include_directories(${cppzmq_INCLUDE_DIR})

  if(zguide_FOUND)
    include_directories(${zguide_DIR}/examples/C++)
  endif()
endif()

foreach(_target test2 lbbroker)

  add_executable(${_target} "${_target}.cpp")

  if(cppzmq_FOUND)
    target_link_libraries(${_target} cppzmq)
  endif()
endforeach()
