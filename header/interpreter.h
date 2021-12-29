#pragma once

#include <string>
#include <map>
#include <iostream>
#include "parser.h"

using namespace std;

//用于Interpreter类的默认构造函数的初始化列表
static Script defScript;
static string defUserId;


class Interpreter {
private:

    //用户名ID
    const string& userId;

	//脚本的const引用
	const Script& script;

    //当前执行到的StepId
	string stepId;

	/**
	 * @brief Speak函数
	 * 
	 * @param expression 需要输出的表达式
	 */
	void Speak(vector<string> expression);

	/**
	 * @brief Listen函数
	 * 
	 */
	void Listen();



public:

	/**
	 * @brief Construct a new Interpreter object
	 * 
	 * @param userId 
	 * @param script 
	 */
	Interpreter(const string& userId = defUserId, const Script& script = defScript);



	/**
	 * @brief 执行解释的函数
	 * 
	 */
	void Exec();

};