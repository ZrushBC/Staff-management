//���ݿ⹤����
#pragma once
#include<mysql.h>
#include<string>
using namespace std;
class DBUtils
{
private:
	MYSQL* mysql;
public:
	DBUtils();
	//��
	void add(string id, string name, string sex, string post);
	//ɾ
	void del(string id="");
	//��
	void rev(string id,string str, char flag);
	//��
	MYSQL_RES* inq(string str="", char flag='0');
	//ͳ������
	int get_num();
	~DBUtils();
};

