#include "parser.h"
#include "myerror.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <stdlib.h>

using namespace ParserError;
using namespace std;

Step::Step()
{
	listenTime = 0;		//默认为0
	exit = false;		//默认不包含退出

	//其余模板容器初始化默认，均为empty
}

bool Step::operator==(const Step & _step) const
{
    bool exFlag = true, listenFlag= true, branchFlag = true,
    silenceFlag= true, defaultFlag = true, exitFlag = true;

    //对expression的判断
    if(this->expression.size() != _step.expression.size()){
        exFlag = false;
    }else{
        for(int i = 0;i<this->expression.size();i++){
            if(this->expression[i] != _step.expression[i]){
                exFlag = false;
                break;
            }
        }
    }

    //对listenTime的判断
    if(this->listenTime != _step.listenTime){
        listenFlag = false;
    }

    //对branchTable的判断
    if(this->branchTable.size() != _step.branchTable.size()){
        branchFlag = false;
    }else{
        auto iter1 = this->branchTable.begin();
        auto iter2 = this->branchTable.begin();
        for(;iter1 != this->branchTable.end();iter1++,iter2++){
            if(iter1->first != iter2->first || iter1->second != iter2->second){
                branchFlag = false;
                break;
            }
        }

    }
    
    //对silenceStepId的判断
    if(this->silenceStepId != _step.silenceStepId){
        silenceFlag = false;
    }

    //对defaultStepId的判断
    if(this->defaultStepId != _step.defaultStepId){
        defaultFlag = false;
    }

    //对exit的判断
    if(this->exit != _step.exit){
        exitFlag = false;
    }
    
    return exFlag && listenFlag && branchFlag && silenceFlag && defaultFlag && exFlag;
    
}



bool Step::operator!=(const Step & _step) const
{
    bool exFlag = true, listenFlag= true, branchFlag = true,
    silenceFlag= true, defaultFlag = true, exitFlag = true;

    //对expression的判断
    if(this->expression.size() != _step.expression.size()){
        exFlag = false;
    }else{
        for(int i = 0;i<this->expression.size();i++){
            if(this->expression[i] != _step.expression[i]){
                exFlag = false;
                break;
            }
        }
    }

    //对listenTime的判断
    if(this->listenTime != _step.listenTime){
        listenFlag = false;
    }

    //对branchTable的判断
    if(this->branchTable.size() != _step.branchTable.size()){
        branchFlag = false;
    }else{
        auto iter1 = this->branchTable.begin();
        auto iter2 = this->branchTable.begin();
        for(;iter1 != this->branchTable.end();iter1++,iter2++){
            if(iter1->first != iter2->first || iter1->second != iter2->second){
                branchFlag = false;
                break;
            }
        }

    }
    
    //对silenceStepId的判断
    if(this->silenceStepId != _step.silenceStepId){
        silenceFlag = false;
    }

    //对defaultStepId的判断
    if(this->defaultStepId != _step.defaultStepId){
        defaultFlag = false;
    }

    //对exit的判断
    if(this->exit != _step.exit){
        exitFlag = false;
    }
	return !(exFlag && listenFlag && branchFlag && silenceFlag && defaultFlag && exFlag);
}


Parser::Parser(string fileName)
{
	this->fileName = fileName;
    ParseFile();
}



void Parser::ParseFile()
{
	ifstream fin(fileName);
	if (!fin.is_open()) {	//打开文件失败
		Error(OPEN_FILE_ERROR);
	}
	string tmp;
	while (getline(fin, tmp)) {
		tmp = trim(tmp);
        if(!tmp.empty()){
            vector<string> tokens = ParseLine(tmp);
		    process.ProcessTokens(tokens,script);
        }
		tmp.clear();
	}
}

vector<string> Parser::ParseLine(string line)
{
	return split(line, " \t");
}




void Process::ProcessTokens(vector<string>& tokens, Script &script)
{
	lineNum++;
	if (tokens[0] == "Step") {
		if(tokens.size() != 2)	
			Error(STEP_ERROR,lineNum);

		Process::ProcessStep(tokens[1], script);
	}
		
	else if (tokens[0] == "Speak") {
		if (tokens.size() <= 1) 	//无表达式部分
			Error(SPEAK_ERROR, lineNum);
		
		Process::ProcessSpeak(tokens, script);
	}
		
	else if (tokens[0] == "Listen") {
		if (tokens.size() != 2)		//Listen参数个数错误
			Error(LISTEN_ERROR, lineNum);

		Process::ProcessListen(tokens[1], script);
	}
	
	else if (tokens[0] == "Branch") {
		if (tokens.size() != 3)		//Branch参数个数错误
			Error(BRANCH_ERROR, lineNum);

		Process::ProcessBranch(tokens[1], tokens[2], script);
	}

	else if (tokens[0] == "Silence") {
		if (tokens.size() != 2)		//Silence参数个数错误
			Error(SILENCE_ERROR, lineNum);

		Process::ProcessSilence(tokens[1],script);
	}

	else if (tokens[0] == "Default") {
		if (tokens.size() != 2)		//Default参数个数错误
			Error(DEFAULT_ERROR, lineNum);
		Process::ProcessDefault(tokens[1], script);
	}

	else if (tokens[0] == "Exit") {
		if (tokens.size() != 1)		//Exit参数个数错误
			Error(EXIT_ERROR, lineNum);
		Process::ProcessExit(script);
	}

	else {		//未知标志的错误
		Error(UNKNOWN_TOKEN, lineNum);
	}
}

void Process::ProcessStep(string stepId, Script& script)
{
	map<string, Step>::iterator iter = script.stepMap.find(stepId);

	if (iter == script.stepMap.end()) {		//不存在
		if (script.stepMap.empty())		//StepMap空，建立入口stepId
			script.entry = stepId;
		else{			//stepMap非空，检测上一个Step是否结构完整
			bool hasSpeak = (!script.stepMap.at(this->StepId).expression.empty());
			bool hasListenTime = (script.stepMap.at(this->StepId).listenTime != 0);
			bool hasSilence = (!script.stepMap.at(this->StepId).silenceStepId.empty());
			bool hasDefault = (!script.stepMap.at(this->StepId).defaultStepId.empty());
			bool hasExit = (script.stepMap.at(this->StepId).exit == true);
			if(!(hasSpeak && ((hasListenTime && hasSilence && hasDefault) ^ hasExit))){
				//TODO:在这里检测上个Step结构错误
				Error(STRUCTURE_ERROR,lineNum);
			}
		}

		Step insert;
		script.stepMap[stepId] = insert;

		this->StepId = stepId;
	}
	else {		//重复定义StepId
		Error(REDEFINE_STEP, lineNum);
	}
	
}


//注：Speak内容不能含有空格
void Process::ProcessSpeak(vector<string>& tokens, Script& script)
{
	if (!script.stepMap.at(StepId).expression.empty()) {	//重复定义Speak表达式s
		Error(REDEFINE_SPEAK, lineNum);
	}
	vector<string> expression(tokens.begin()+1,tokens.end());	//抽取表达式
	script.stepMap.at(StepId).expression = expression;
	
}

void Process::ProcessListen(string timeLong, Script& script)
{
	if (script.stepMap.at(StepId).listenTime > 0) {	//重复定义ListenTime
		Error(REDEFINE_LISTEN, lineNum);
	}
	int listenTime = atoi(timeLong.c_str());
	if (listenTime <= 0) {		//时长不符合规范
		Error(LISTEN_ERROR, lineNum);
	}

	script.stepMap.at(StepId).listenTime = listenTime;
}

void Process::ProcessBranch(string userAnswer, string nextStepId, Script& script)
{
	if (script.stepMap.at(StepId).listenTime == 0) {
		//错误，未定义listen，直接定义branch
		Error(NONDEFINE_LISTEN,lineNum);
	}
	bool hasSilence = !script.stepMap.at(StepId).silenceStepId.empty();
	bool hasDefault = !script.stepMap.at(StepId).defaultStepId.empty();
	bool hasExit = script.stepMap.at(StepId).exit;
	bool hasBranch = (script.stepMap.at(StepId).branchTable.find(userAnswer) != script.stepMap.at(StepId).branchTable.end());
	if (hasSilence || hasDefault || hasExit || hasBranch) {
		//错误，重复定义Branch
		Error(REDEFINE_BRANCH,lineNum);
	}

	script.stepMap.at(StepId).branchTable[userAnswer] = nextStepId;

}

void Process::ProcessSilence(string nextStepId, Script& script)
{
	if (script.stepMap.at(StepId).listenTime == 0) {
		//错误，未定义listen，直接定义Silence
		Error(NONDEFINE_LISTEN,lineNum);
	}
	bool hasSilence = !script.stepMap.at(StepId).silenceStepId.empty();
	bool hasDefault = !script.stepMap.at(StepId).defaultStepId.empty();
	bool hasExit = script.stepMap.at(StepId).exit;
	if (hasSilence || hasDefault || hasExit) {
		//错误，重复定义Silence
		Error(REDEFINE_SILENCE,lineNum);
	}

	script.stepMap.at(StepId).silenceStepId = nextStepId;
}

void Process::ProcessDefault(string nextStepId, Script& script)
{
	if (script.stepMap.at(StepId).listenTime == 0) {
		//错误，未定义listen，直接定义Default
		Error(NONDEFINE_LISTEN,lineNum);
	}
	bool hasDefault = !script.stepMap.at(StepId).defaultStepId.empty();
	bool hasExit = script.stepMap.at(StepId).exit;
	if ( hasDefault || hasExit ) {
		//错误，重复定义Default
		Error(REDEFINE_DEFAULT,lineNum);
	}

	script.stepMap.at(StepId).defaultStepId = nextStepId;
}

void Process::ProcessExit(Script& script)
{
	if (script.stepMap.at(StepId).exit == true) {		//重复定义Exit
		Error(EXIT_ERROR, lineNum);
	}
	script.stepMap.at(StepId).exit = true;

}