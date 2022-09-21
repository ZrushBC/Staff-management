//数据库工具类
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
	//增
	void add(string id, string name, string sex, string post);
	//删
	void del(string id="");
	//改
	void rev(string id,string str, char flag);
	//查
	MYSQL_RES* inq(string str="", char flag='0');
	//统计总数
	int get_num();
	~DBUtils();
};

