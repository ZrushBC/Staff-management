#pragma once
#include"Worker.h"
#include<iostream>
using namespace std;
class Employee :
    public Worker
{
public:
	Employee(int id, string name, string sex, int post_id);
	//显示个人信息
	virtual void show_info();
	//获取岗位名称
	virtual string get_PostName();
	~Employee();
};

