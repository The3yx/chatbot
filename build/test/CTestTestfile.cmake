# CMake generated Testfile for 
# Source directory: /home/shanmu/chatbot/test
# Build directory: /home/shanmu/chatbot/build/test
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(parsertest1 "ParserTest" "testscript1.txt" "truescript1.txt")
set_tests_properties(parsertest1 PROPERTIES  _BACKTRACE_TRIPLES "/home/shanmu/chatbot/test/CMakeLists.txt;12;add_test;/home/shanmu/chatbot/test/CMakeLists.txt;0;")
add_test(parsertest2 "ParserTest" "testscript2.txt" "truescript2.txt")
set_tests_properties(parsertest2 PROPERTIES  PASS_REGULAR_EXPRESSION "Error line 6:重复定义Branch分支" _BACKTRACE_TRIPLES "/home/shanmu/chatbot/test/CMakeLists.txt;15;add_test;/home/shanmu/chatbot/test/CMakeLists.txt;0;")
add_test(parsertest3 "ParserTest" "testscript3.txt" "truescript2.txt")
set_tests_properties(parsertest3 PROPERTIES  PASS_REGULAR_EXPRESSION "Error line 9:Step结构错误" _BACKTRACE_TRIPLES "/home/shanmu/chatbot/test/CMakeLists.txt;19;add_test;/home/shanmu/chatbot/test/CMakeLists.txt;0;")
add_test(parsertest4 "ParserTest" "testscript4.txt" "truescript4.txt")
set_tests_properties(parsertest4 PROPERTIES  _BACKTRACE_TRIPLES "/home/shanmu/chatbot/test/CMakeLists.txt;23;add_test;/home/shanmu/chatbot/test/CMakeLists.txt;0;")
add_test(parsertest5 "ParserTest" "testscript5.txt" "truescript5.txt")
set_tests_properties(parsertest5 PROPERTIES  _BACKTRACE_TRIPLES "/home/shanmu/chatbot/test/CMakeLists.txt;26;add_test;/home/shanmu/chatbot/test/CMakeLists.txt;0;")
add_test(interpretertest1 "InterpreterTest" "inter_script1.txt" "1")
set_tests_properties(interpretertest1 PROPERTIES  _BACKTRACE_TRIPLES "/home/shanmu/chatbot/test/CMakeLists.txt;31;add_test;/home/shanmu/chatbot/test/CMakeLists.txt;0;")
add_test(interpretertest2 "InterpreterTest" "inter_script2.txt" "2")
set_tests_properties(interpretertest2 PROPERTIES  PASS_REGULAR_EXPRESSION "Error: Branch匹配成功时，跳转Step为空" _BACKTRACE_TRIPLES "/home/shanmu/chatbot/test/CMakeLists.txt;34;add_test;/home/shanmu/chatbot/test/CMakeLists.txt;0;")
