# Copyright The OpenTelemetry Authors
# SPDX-License-Identifier: Apache-2.0

foreach(_target client_grpc server_grpc)
  add_executable(${_target} "${_target}.cc")

  target_include_directories(
    ${_target} PUBLIC "$<BUILD_INTERFACE:${include_DIR}>")

  target_link_libraries(
    ${_target} PRIVATE example_grpc_proto
                       opentelemetry-cpp::ostream_span_exporter
                       opentelemetry-cpp::api
                       opentelemetry-cpp::sdk
                       opentelemetry-cpp::otlp_http_exporter
                       opentelemetry-cpp::otlp_grpc_exporter)
endforeach()
