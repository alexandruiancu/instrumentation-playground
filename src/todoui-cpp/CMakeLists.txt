
if(crow_FOUND)
   include_directories(${crow_INCLUDE_DIR})
endif()

add_executable(todoui-cpp "driver.cpp")
target_link_libraries(todoui-cpp Crow::Crow)
