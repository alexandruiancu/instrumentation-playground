# Copyright The OpenTelemetry Authors
# SPDX-License-Identifier: Apache-2.0

# downloads booksbyus/zguide
# 1. Use FetchContent to fetch zguilde from GitHub

# Including the CMakeFindDependencyMacro resolves an error from
include(CMakeFindDependencyMacro)

#find_package(zmqcpp CONFIG QUIET)
#set(zguide_PROVIDER "find_package")

#if(NOT zguide_FOUND)
  FetchContent_Declare(
      "zguide"
      GIT_REPOSITORY  "https://github.com/booksbyus/zguide.git"
      GIT_TAG "${zguide_GIT_TAG}"
      )
  set(zguide_PROVIDER "fetch_repository")

  FetchContent_MakeAvailable(zguide)

  # Set the zguide_VERSION variable from the git tag.
  string(REGEX REPLACE "^v([0-9]+\\.[0-9]+\\.[0-9]+)$" "\\1" zguide_VERSION "${zguide_GIT_TAG}")

#  endif()

#if(NOT TARGET zguide)
#  message(FATAL_ERROR "A required zguide target was not imported")
#endif()
