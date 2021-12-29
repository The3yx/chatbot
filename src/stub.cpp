#include "stub.h"
#include "parser.h"
#include <stdlib.h>


namespace TestStub 
{	
	int testMode = 0;

	ifstream input;
	
	ofstream output; 

	void enable_testing(string inputPath, string outputPath)
	{
		//启用测试模式，将输入输出改为文件
		testMode = 1;

		//重定向输入到input流
		input.open(inputPath);
		if(!input.is_open()){
        	cout<<"打开文件"<< inputPath <<"错误"<<endl;
			exit(-1);    	
		}



		//重定向输出到output流
		output.open(outputPath);
		if(!output.is_open()){
        	cout<<"打开文件"<< outputPath <<"错误"<<endl;
			exit(-1);    	
		}

	}

	

	string GetListen(int listenTime)
	{
		string listenContent;
		if(!testMode){
			getline(cin,listenContent);
		}else{
			getline(input,listenContent);
		}
		
		return listenContent;
	}


	void SpeakOut(string speakContent)
	{
		if(!testMode){
			cout << speakContent<<endl;
		}else{
			output<<speakContent<<endl;
		}
		
	}


	string LoadValue(string userData, string varName)
	{
		ifstream fin(userData);
		if(!fin.is_open()){
			cout<<"打开文件"<<userData<<"错误"<<endl;
			exit(-1);
		}
		string tmp;
		int line = 0;
		while(getline(fin,tmp)){
			line++;
			trim(tmp);
			if(!tmp.empty()){
				vector<string> strs = split(tmp, " ");
				if(strs.size()!=2){
					cout<<"数据文件"<<userData<<"line: "<<line<<"错误"<<endl;
				}
				if(strs[0] == varName)
					return strs[1];
			}
		}

		return "unknown";
	}
}