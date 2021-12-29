#include "interpreter.h"
#include "myerror.h"
#include "stub.h"

using namespace InterpreterError;
using namespace std;

Interpreter::Interpreter(const string& userId, const Script& script) :script(script),userId(userId)
{	    
    Exec();
}

void Interpreter::Exec()
{
	stepId = script.entry;
    do{
		auto iter = script.stepMap.find(stepId);
		if(iter == script.stepMap.end()){
			Error(NON_BRANCH_NAME);
		}
        Speak(script.stepMap.at(stepId).expression);

        if(script.stepMap.at(stepId).exit){
            break;
        }
        Listen();

    }while(true);

}


void Interpreter::Speak(vector<string> expression)
{
	//c++11 size()函数保证O(1)返回
    string speakContent;

	for (int i = 0; i < expression.size(); i++) {
		string tmp = expression[i];
		if (!tmp.empty()) {
			if (tmp[0] == '$') {	//变量
				//TODO:获取变量值后然后speakOutput
                tmp = tmp.substr(1);
                tmp = TestStub::LoadValue(userId+".txt",tmp);

			}
            speakContent += tmp;
		}
	}
    TestStub::SpeakOut(speakContent);
}

void Interpreter::Listen()
{

	//注:这个听多少秒不应该由解释器实现，解释器只负责处理输入与返回输出
	//获取输入与打印输出（或其他方式）不是解释器的范围
	
    
	//注:对于const map不能使用[]索引，因为[]是非const成员函数，如果未找到索引，则会创建
	//而at函数有const与非const两个版本
    string listenContent = TestStub::GetListen(script.stepMap.at(stepId).listenTime);

	map<string,	string>::const_iterator iter;
    if(listenContent == " "){
        stepId = script.stepMap.at(stepId).silenceStepId;
        return ;
    }

	iter = script.stepMap.at(stepId).branchTable.find(listenContent);

	if (iter == script.stepMap.at(stepId).branchTable.end())
		stepId = script.stepMap.at(stepId).defaultStepId;
	else
		stepId = iter->second;

}