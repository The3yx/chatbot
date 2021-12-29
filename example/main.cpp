#include "parser.h"
#include "interpreter.h"
#include "stub.h"
#include <iostream>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

int main()
{
    const char* scriptName = "script.txt";
    const char* userName = "userdata";

    //解析给定脚本文件
    Parser golbalParser(scriptName);

    //执行解析后的脚本
    Interpreter example(userName,golbalParser.GetScript());

    return 0;
}