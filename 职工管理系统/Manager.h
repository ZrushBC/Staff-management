#pragma once
#include "Worker.h"
#include<iostream>
using namespace std;
class Manager :
    public Worker
{
public:
	Manager(int id, string name, string sex, int post_id);
	//��ʾ������Ϣ
	virtual void show_info();
	//��ȡ��λ����
	virtual string get_PostName();
	~Manager();
};

