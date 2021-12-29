#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

namespace TestStub {

	//是否开启test的标志
	extern int testMode;

	//输入输出流
	extern ifstream input;
	extern ofstream output;


	
	/**
	 * @brief 启用测试，将testMode置为1，且重定向输入输出
	 * 
	 * @param inputPath 用户名ID，对应着用户文件
	 * @param outputPath 模拟用户输入的文件的文件路径
	 */
	void enable_testing(string inputPath, string outputPath);




	/**
	 * @brief 获取输入，testMode==0从终端获取  testMode==1从文件获取
	 * 
	 * @param listenTime 获取输入的最大时间，由于是测试桩，可以不需要完全实现这个功能，模拟返回值即可
	 * @return string 获取的用户输入
	 * 				  超时时默认为string ;istenContent = " "
	 */
	string GetListen(int listenTime);




	/**
	 * @brief 输出解释器执行时的输出	testMode==1输出到文件，testMode==0输出到终端
	 * 
	 * @param speakContent 输出的内容
	 */
	void SpeakOut(string speakContent);




	/**
	 * @brief 加载变量的值
	 * 
	 * @param userData 用户数据文件,获取对应文件
	 * @param varName 需要获取值的变量名
	 * @return string 变量的值
	 */
	string LoadValue(string userData, string varName);


}

