#include <iostream>
#include <stdlib.h>
#include "myerror.h"

using namespace std;

namespace ParserError {
	void OpenFileError()	{	cout << "打开文件错误" << endl;	}
	void StepError()		{	cout << "Step 参数错误" << endl;	}
	void SpeakError()		{	cout << "Speak 参数错误" << endl; }
	void ListenError()		{	cout << "Listen 参数错误" << endl; }
	void BranchError()		{	cout << "Branch 参数错误" << endl; }
	void SilenceError()		{	cout << "Silence 参数错误" << endl; }
	void DefaultError()		{	cout << "Default 参数错误" << endl; }
	void ExitError()		{	cout << "Exit 参数错误" << endl; }
	void UnknownToken()		{	cout << "未知标识符" << endl; }

	void RedefineStep()		{	cout << "重复定义相同StepId" << endl; }
	void RedefineSpeak()	{	cout << "Step内重复定义Speak内容" << endl; }
	void RedefineBranch()	{	cout << "重复定义Branch分支" << endl; }
	void RedefineSilence()	{	cout << "重复定义Silence跳转" << endl; }
	void RedefineDefault()	{	cout << "重复定义Default跳转" << endl; }
	void RedefineExit()		{	cout << "重复定义Exit" << endl; }
	void RedefineListen()	{	cout << "重复定义Listen结构" << endl; }

	void InvalidListenTime(){	cout << "不合法的Listen时长，Listen时长需要大于等于0" << endl; }
	void NonDefineListen()	{	cout << "未定义Listen，则定义了Listen的分支" << endl; }
	void StructureError()	{	cout << "Step结构错误"<<endl;	}

	void (*ErrorList[])(void) = {
		OpenFileError,
		StepError,
		SpeakError,
		ListenError,
		BranchError,
		SilenceError,
		DefaultError,
		ExitError,
		UnknownToken,
		RedefineStep,
		RedefineSpeak,
		RedefineBranch,
		RedefineSilence,
		RedefineDefault,
		RedefineExit,
		RedefineListen,
		InvalidListenTime,
		NonDefineListen,
		StructureError

	};

	void Error(int errorCode, int lineNum)
	{
		if(lineNum > 0)
			cout << "Error line " << lineNum << ":";

		(*ErrorList[errorCode])();
		
		//注:由于暂时所有错误的处理最终都采用终止
		//所以写在公共的调用处
		exit(-1);
	}
}

namespace InterpreterError{

	void NonBranchName()	{	cout<<"Branch匹配成功时，跳转Step为空"<<endl;	}

	void (*ErrorList[])(void) = {
		NonBranchName
	};
	
	void Error(int errorCode)
	{
		cout<<"Error: ";
		
		(*ErrorList[errorCode])();

		exit(-1);
	}
}