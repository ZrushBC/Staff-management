#pragma once
#pragma once
#include<string>
using namespace std;
class Worker
{
public:
	//职工编号
	int id;
	//姓名
	string name;
	//性别
	string sex;
	//部门编号
	int post_id;
	//显示个人信息
	virtual void show_info() = 0;
	//获取岗位名称
	virtual string get_PostName() = 0;
};

