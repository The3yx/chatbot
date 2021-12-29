add_library(Interpreter myerror.cpp interpreter.cpp parser.cpp stub.cpp)

target_include_directories(Interpreter PUBLIC ../header)