# Copyright The OpenTelemetry Authors
# SPDX-License-Identifier: Apache-2.0

# Import Crow targets
# 1. Find an installed Crow package
# 2. Use FetchContent to fetch and build Crow (and its submodules) from GitHub

# Including the CMakeFindDependencyMacro resolves an error from
include(CMakeFindDependencyMacro)

find_package(Crow::Crow CONFIG QUIET)
set(Crow_PROVIDER "find_package")

if(NOT Crow_FOUND)
  FetchContent_Declare(
      "Crow"
      GIT_REPOSITORY  "https://github.com/CrowCpp/Crow.git"
      GIT_TAG "${crow_GIT_TAG}"
      )
  set(Crow_PROVIDER "fetch_repository")

  FetchContent_MakeAvailable(Crow)

  # Set the Crow_VERSION variable from the git tag.
  string(REGEX REPLACE "^v([0-9]+\\.[0-9]+\\.[0-9]+)$" "\\1" Crow_VERSION "${crow_GIT_TAG}")

endif()

if(NOT TARGET Crow::Crow)
	message(FATAL_ERROR "A required Crow target (Crow::Crow) was not imported")
endif()

#if(CMAKE_CROSSCOMPILING)
#  find_program(gRPC_CPP_PLUGIN_EXECUTABLE grpc_cpp_plugin)
#else()
#  if(NOT TARGET gRPC::grpc_cpp_plugin)
#    message(FATAL_ERROR "A required gRPC target (gRPC::grpc_cpp_plugin) was not imported")
#  endif()
#  set(gRPC_CPP_PLUGIN_EXECUTABLE "$<TARGET_FILE:gRPC::grpc_cpp_plugin>")
#endif()

message(STATUS "Crow_CPP_PLUGIN_EXECUTABLE=${Crow_CPP_PLUGIN_EXECUTABLE}")
