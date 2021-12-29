#pragma once

#include <string>
#include <map>
#include <list>
#include <vector>
#include <iostream>

using namespace std;

class Step
{
public:

	// speak的表达式
	vector<string> expression;

	// listen时长
	int listenTime;

	// branch分支表
	// key:branch名	value:stepId
	map<string, string> branchTable;

	// silence时跳转的分支
	string silenceStepId;

	// default（即用户意愿无法匹配）跳转的stepId
	string defaultStepId;

	//是否包含退出
	bool exit;


	/**
	 * @brief Construct a new Step object
	 * 
	 */
	Step();


	/**
	 * @brief 重载==操作符
	 * 注：显示声明为const函数，因为比较操作符，不应改变对象内容
	 * 函数被使用时，多为const对象使用
	 * 
	 * @param _step ==的右值
	 * @return true 相等
	 * @return false 不等
	 */
	bool operator==(const Step &_step) const;



	/**
	 * @brief 重载!=操作符
	 * 
	 * @param _step !=的右值
	 * @return true 不等
	 * @return false 相等
	 */
	bool operator!=(const Step &_step) const;
};

class Script
{
public:
	// step表
	// key:step的名称	value:step的内容
	map<string, Step> stepMap;

	//入口step
	string entry;

};


class Process
{
private:

	//Process当前处理的StepId
	string StepId;

	//Process当前处理的行
	int lineNum;


	/**
	 * @brief 处理该行为Step的情况
	 * 
	 * @param stepId 当前新Step的标识
	 * @param script 处理结果添加至的脚本对象
	 */
	void ProcessStep(string stepId, Script &script);


	/**
	 * @brief 处理该行 为Speak的情况
	 * 
	 * @param tokens 将Speak内容处理后的token向量
	 * @param script 处理结果添加至的脚本对象
	 */
	void ProcessSpeak(vector<string> &tokens, Script &script);

	

	/**
	 * @brief 处理该行为Listen的情况
	 * 
	 * @param timeLong listen的最大时长
	 * @param script 处理结果添加至的脚本对象
	 */
	void ProcessListen(string timeLong, Script &script);



	/**
	 * @brief 处理该行为Branch的情况
	 * 
	 * @param userAnswer 用户匹配的意愿
	 * @param nextStepId 匹配成功跳转的StepId
	 * @param script 处理结果添加至的脚本对象
	 */
	void ProcessBranch(string userAnswer, string nextStepId, Script &script);

	

	/**
	 * @brief 处理该行为Silence的情况
	 * 
	 * @param nextStepId silence时跳转的StepId
	 * @param script 处理结果添加至的脚本对象
	 */
	void ProcessSilence(string nextStepId, Script &script);



	/**
	 * @brief 处理该行为Default的情况
	 * 
	 * @param nextStepId default时跳转的StepId
	 * @param script 处理结果添加至的脚本对象
	 */
	void ProcessDefault(string nextStepId, Script &script);



	/**
	 * @brief 处理该行为Exit的情况
	 * 
	 * @param script 处理结果添加至的脚本对象
	 */
	void ProcessExit(Script &script);

public:

	/**
	 * @brief Construct a new Process object
	 * 
	 */
	Process() { lineNum = 0; };


	/**
	 * @brief 对脚本中的一行按单词解析，根据Token选择下列中的函数
	 * 		  注：只对外暴露该接口，防止外层调用该类的成员函数时出错
	 * 
	 * @param tokens tokens向量
	 * @param script 脚本对象
	 */
	void ProcessTokens(vector<string> &tokens, Script &script);

};

class Parser
{
private:
	string fileName; //脚本文件路径

	Script script; //脚本对象

	Process process; //解析脚本内容的对象

public:

	/**
	 * @brief Construct a new Parser object
	 * 
	 */
	Parser(){};

	/**
	 * @brief Construct a new Parser object
	 * 
	 * @param fileName 脚本文件名
	 */
	Parser(string fileName);



	/**
	 * @brief 解析脚本文件
	 * 
	 */
	void ParseFile();



	/**
	 * @brief 解析脚本中的一行，将string line转化为vector<string> line，调用ProcessTokens
	 * 
	 * @param line 脚本中一行的内容
	 * @return vector<string> vector<string>:将脚本中的一行解析为多个token
	 */
	vector<string> ParseLine(string line);



	/**
	 * @brief script为Parser类私有成员，给外界提供接口使用脚本的引用
	 * 
	 * @return const Script& 脚本的const引用，保证外界不能改变script
	 */
	const Script &GetScript() { return this->script; }
};



/**
 * @brief 截断string的前后空格与制表符
 * 
 * @param str 需要处理的字符串
 * @return string 处理后的字符串
 */
static string trim(string &str)
{
	const string delim = " \t";
	string trimStr = str.erase(str.find_last_not_of(delim) + 1);
	trimStr.erase(0, trimStr.find_first_not_of(delim));

	return trimStr;
}



/**
 * @brief 将字符串按delimiter分割
 * 
 * @param s 需要处理的字符串
 * @param seperator 分隔符
 * @return vector<string> 分隔后的字符串向量
 */
static vector<string> split(const string &s, const string &seperator)
{
	vector<string> result;
	if(s.empty()){
		return result;
	}
	typedef string::size_type string_size;
	string_size i = 0;

	while (i != s.size())
	{
		//找到字符串中首个不等于分隔符的字母；
		int flag = 0;
		while (i != s.size() && flag == 0)
		{
			flag = 1;
			for (string_size x = 0; x < seperator.size(); ++x)
				if (s[i] == seperator[x])
				{
					++i;
					flag = 0;
					break;
				}
		}

		//找到又一个分隔符，将两个分隔符之间的字符串取出；
		flag = 0;
		string_size j = i;
		while (j != s.size() && flag == 0)
		{
			for (string_size x = 0; x < seperator.size(); ++x)
				if (s[j] == seperator[x])
				{
					flag = 1;
					break;
				}
			if (flag == 0)
				++j;
		}
		if (i != j)
		{
			result.push_back(s.substr(i, j - i));
			i = j;
		}
	}
	return result;
}