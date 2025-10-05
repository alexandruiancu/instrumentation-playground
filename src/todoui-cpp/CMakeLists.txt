
add_executable(todoui-cpp "driver.cpp")
target_link_libraries(todoui-cpp PRIVATE Crow::Crow cpr::cpr)
