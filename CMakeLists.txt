cmake_minimum_required( VERSION 3.20 )
project( instrumentation-playground )

# Place CXX flags here or later ?
set( CMAKE_CXX_FLAGS "-g3 -Wall" )
set( CMAKE_CXX_STANDARD 20 )

include("${instrumentation-playground_SOURCE_DIR}/cmake/curl.cmake")
include("${instrumentation-playground_SOURCE_DIR}/cmake/opentelemetry-cpp.cmake")
include("${instrumentation-playground_SOURCE_DIR}/cmake/grpc.cmake")
include("${instrumentation-playground_SOURCE_DIR}/cmake/protobuf.cmake")

set(include_DIR "${instrumentation-playground_SOURCE_DIR}/include")

########################################
# zguide 
#include C/zhelpers/h 
#include C++/zhelpers/hpp)

set(zguide_DIR "${instrumentation-playground_SOURCE_DIR}/../zguide")
if(EXISTS "${zguide_DIR}")
  set(zguide_FOUND 1)
else()
  set(zguide_FOUND 0)
endif()
########################################

add_subdirectory(src)
