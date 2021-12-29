add_executable(ParserTest parsertest.cpp)
add_executable(InterpreterTest interpretertest.cpp)

target_include_directories(ParserTest PUBLIC ../header)
target_include_directories(InterpreterTest PUBLIC ../header)

target_link_libraries(ParserTest Interpreter)
target_link_libraries(InterpreterTest Interpreter)

###Parser的测试
#测试1：测试正常的脚本的解析是否正确
add_test(parsertest1 ParserTest testscript1.txt truescript1.txt)

#测试2：测试Step块顺序
add_test(parsertest2 ParserTest testscript2.txt truescript2.txt)
set_tests_properties(parsertest2 PROPERTIES PASS_REGULAR_EXPRESSION "Error line 6:重复定义Branch分支")

#测试3：测试Step整体结构
add_test(parsertest3 ParserTest testscript3.txt truescript2.txt)
set_tests_properties(parsertest3 PROPERTIES PASS_REGULAR_EXPRESSION "Error line 9:Step结构错误")

#测试4：测试格式凌乱的脚本解析是否正确
add_test(parsertest4 ParserTest testscript4.txt truescript4.txt)

#测试5：测试带有变量的脚本解析
add_test(parsertest5 ParserTest testscript5.txt truescript5.txt)


###Interpreter的测试
#测试1：正常脚本 正常执行 判断执行结果是否正确
add_test(interpretertest1 InterpreterTest inter_script1.txt 1)

#测试2：异常脚本 异常执行 判断错误处理是否正确
add_test(interpretertest2 InterpreterTest inter_script2.txt 2)
set_tests_properties(interpretertest2 PROPERTIES PASS_REGULAR_EXPRESSION "Error: Branch匹配成功时，跳转Step为空")