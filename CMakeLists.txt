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
add_subdirectory(src)
