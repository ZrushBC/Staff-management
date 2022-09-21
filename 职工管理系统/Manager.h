#pragma once
#include "Worker.h"
#include<iostream>
using namespace std;
class Manager :
    public Worker
{
public:
	Manager(int id, string name, string sex, int post_id);
	//显示个人信息
	virtual void show_info();
	//获取岗位名称
	virtual string get_PostName();
	~Manager();
};

