#include "parser.h"
#include <assert.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

using namespace std;

/*
*Function:
*比较两个map是否相等的模板函数（由于map中key值有序，简化的比较方法）
*对于mapValue为自定义类型的，需要重载== 与!=
*
*Args:
*map1:比较者1
*map2:比较者2
*
*Returns:
*是否相等，相等true；否则false
*/
template<typename K, typename V>
bool CompareMap(const map<K, V>& map1, const map<K, V>& map2)
{
    if (map1.size() != map2.size())
    {
        return false;
    }

    auto iter1 = map1.begin();
    auto iter2 = map2.begin();
    for (; iter1 != map1.end(); ++iter1, ++iter2)
    {   
        if (iter1->first != iter2->first || iter1->second != iter2->second)
        {
            return false;
        }
    }

    return true;
}


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

/*
*Args:srcipt.txt    truescript.txt
*/
int main(int argc, char *argv[]){

    //测试文件，不做命令行处理，默认命令行输入正确
    Parser testParser(argv[1]);

    Script trueScript;
    GetTrueScript(argv[2], trueScript);
    bool testFlag1 = false;
    bool testFlag2 = false;
    const Script &testScript = testParser.GetScript();
    if(testScript.entry == trueScript.entry)
        testFlag1 = true;
    if(CompareMap<string, Step>(trueScript.stepMap, testScript.stepMap) == true)
        testFlag2 = true;

    assert(testFlag1 && testFlag2);

    return 0;
}