add_executable(Example main.cpp)

target_include_directories(Example PUBLIC ../header)

target_link_libraries(Example Interpreter)