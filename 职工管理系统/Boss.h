#pragma once
#include "Worker.h"
#include<iostream>
using namespace std;
class Boss :
    public Worker
{
public:
	Boss(int id, string name, string sex, int post_id);
	//��ʾ������Ϣ
	virtual void show_info();
	//��ȡ��λ����
	virtual string get_PostName();
	~Boss();
};

