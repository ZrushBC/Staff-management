#pragma once
#include"Worker.h"
#include<iostream>
using namespace std;
class Employee :
    public Worker
{
public:
	Employee(int id, string name, string sex, int post_id);
	//��ʾ������Ϣ
	virtual void show_info();
	//��ȡ��λ����
	virtual string get_PostName();
	~Employee();
};

