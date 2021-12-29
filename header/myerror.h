#pragma once



// 错误处理部
// 由于可能各个模块间均有各自的错误处理
// 所以使用命名空间
namespace ParserError {

	//错误码列表，对应错误处理函数列表
	const int OPEN_FILE_ERROR = 0;
	const int STEP_ERROR = 1;
	const int SPEAK_ERROR = 2;
	const int LISTEN_ERROR = 3;
	const int BRANCH_ERROR = 4;
	const int SILENCE_ERROR = 5;
	const int DEFAULT_ERROR = 6;
	const int EXIT_ERROR = 7;
	const int UNKNOWN_TOKEN = 8;

	const int REDEFINE_STEP = 9;
	const int REDEFINE_SPEAK = 10;
	const int REDEFINE_BRANCH = 11;
	const int REDEFINE_SILENCE = 12;
	const int REDEFINE_DEFAULT = 13;
	const int REDEFINE_EXIT =14;
	const int REDEFINE_LISTEN = 15;

	const int INVALID_LISTENTIME = 16;
	const int NONDEFINE_LISTEN = 17;

	const int STRUCTURE_ERROR = 18;

	//错误处理函数,函数名自解释
	void OpenFileError();
	void StepError();
	void SpeakError();
	void ListenError();
	void BranchError();
	void SilenceError();
	void DefaultError();
	void ExitError();
	void UnknownToken();
	void RedefineStep();
	void RedefineSpeak();
	void RedefineBranch();
	void RedefineSilence();
	void RedefineDefault();
	void RedefineExit();
	void RedefineListen();
	void InvalidListenTime();
	void NonDefineListen();
	void StructureError();

	//错误处理函数数组，方便调用错误处理函数
	//不用写if_else处理
	extern void (*ErrorList[])(void);


	void Error(int errorCode, int lineNum = 0);

}

namespace InterpreterError{
	const int NON_BRANCH_NAME = 0;
	

	void NonBranchName();

	extern void (*ErrorList[])(void);

	void Error(int errorCode);

}
