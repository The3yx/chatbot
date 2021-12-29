#include "parser.h"
#include "interpreter.h"
#include "stub.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <assert.h>

using namespace std;
using namespace TestStub;

//直白的构建trueScript
static void GetTrueScript(string trueScripName, Script & trueScript)
{
    ifstream fin(trueScripName);
	if (!fin.is_open()) {	//打开文件失败
		cout<<"打开测试脚本文件失败"<<endl;
        exit(-1);
	}
	string tmp;
	while (getline(fin, tmp)) {
        trim(tmp);
        if(!tmp.empty()){
            vector<string> tokens;
            tokens = split(tmp, " ");
            if(tokens[0] == "entry"){
                trueScript.entry = tokens[1];
            }
            else if(tokens[0] == "Listen"){
                trueScript.stepMap[tokens[1]].listenTime = atoi(tokens[2].c_str());
            }else if(tokens[0] == "Branch"){
                trueScript.stepMap[tokens[1]].branchTable[tokens[2]] = tokens[3];
            }else if(tokens[0] == "Silence"){
                trueScript.stepMap[tokens[1]].silenceStepId = tokens[2];
            }else if(tokens[0] == "Default"){
                trueScript.stepMap[tokens[1]].defaultStepId = tokens[2];
            }else if(tokens[0] == "Exit"){
                trueScript.stepMap[tokens[1]].exit = true;
            }else if(tokens[0] == "Speak"){
                vector<string> expression(tokens.begin()+2,tokens.end());
                trueScript.stepMap[tokens[1]].expression = expression;
            }
        }
		tmp.clear();
	}
}

/**
 * @brief 比较两个文件是否内容一致
 * 
 * @param fileName1 文件1
 * @param fileName2 文件2
 * @return true 一致
 * @return false 不一致
 */
static bool CompareFile(string fileName1, string fileName2)
{

    string file1;
    string file2;

    ifstream fin1(fileName1);
    if(!fin1.is_open()){
        cout<<"打开文件"<<fileName1<<"错误"<<endl;
        exit(-1);
    }
    ostringstream tmp1;
    tmp1 << fin1.rdbuf();
    file1 = tmp1.str();

    ifstream fin2(fileName2);
    if(!fin2.is_open()){
        cout<<"打开文件"<<fileName2<<"错误"<<endl;
        exit(-1);
    }
    ostringstream tmp2;
    tmp2 << fin2.rdbuf();
    file2 = tmp2.str();

    return file1 == file2;

}

int main(int argc, char *argv[])
{

    //测试文件，保证命令行输入正确
    Parser globalParser(argv[1]);   //脚本文件
    string userId = argv[2];        //用户名称

    string inputPath = userId + "_input.txt";
    string outputPath = userId + "_output.txt";
    string comparePath = userId + "_true.txt";

    //测试装启用测试模式
    enable_testing(inputPath, outputPath);

    Interpreter testInterptreter(userId,globalParser.GetScript());


    assert(CompareFile(outputPath,comparePath));
    return 0;
}