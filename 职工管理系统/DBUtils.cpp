#include "DBUtils.h"
#include<mysql.h>
#include<iostream>
#include <iomanip>//stew的头文件，设置字段宽度
#include<string>
using namespace std;

DBUtils::DBUtils() {
	mysql = mysql_init(NULL);
	if (mysql == NULL) {
		printf("数据库初始化错误！");
	}
	//设置字符编码
	mysql_options(mysql, MYSQL_SET_CHARSET_NAME, "gbk");
	//连接数据库
	if (mysql_real_connect(mysql, "127.0.0.1", "root", "123456", "worker", 3306, NULL, 0)) {
		//printf("连接成功!\n ");
	}
	else {
		printf("连接失败！错误为：%s", mysql_error(mysql));
	}
}
//增
void DBUtils::add(string id,string name,string sex,string post) {
	string sql = "insert into info values("+id+",'"+name+"','"+sex+"',"+post+")";
	if (!mysql_query(mysql, sql.c_str()))//插入
		printf("插入完成!\n");
	else printf("插入失败!\n");
}
//删
void DBUtils::del(string id) {
	string sql = "delete from info";
	if (!id.empty())
		sql = sql + " where id=" + id;
	if (!mysql_query(mysql, sql.c_str()))//删除
		printf("删除完成!\n");
	else printf("删除失败!\n");
}
//改,按照编号去改
void DBUtils::rev(string id, string str,char flag) {
	string sql = "update info set ";
	switch (flag)
	{
	case '1':sql = sql + " name=" + "'" + str + "'" + " where id = " + id; break;
	case '2':sql = sql + " sex=" + "'" + str + "'" + " where id = " + id; break;
	case '3':sql = sql + " post=" + "'" + str + "'" + " where id = " + id; break;
	}
	if (!mysql_query(mysql, sql.c_str()))//修改
		printf("修改完成!\n");
	else printf("修改失败!\n");
}
//查
MYSQL_RES* DBUtils::inq(string str, char flag) {
	MYSQL_RES* res;
	//MYSQL_ROW row;
	string sql = "select * from info";
	switch (flag)
	{
	case '0':break;
	case '1':sql = sql + " where id = " + str; break;
	case '2':sql = sql + " where name = '" + str + "'"; break;
	}
	//查看整个数据表  .c_str()将string转换到const char *
	if (mysql_query(mysql, sql.c_str()))
	{
		cout << "mysql语句执行失败！错误为:" << mysql_error(mysql) << endl;
	}
	else {
		res = mysql_use_result(mysql);
		//if (res) {
		//	row = mysql_fetch_row(res);
		//	if (row != NULL) {
		//		cout << "\n信息如下:" << endl;
		//		while (row != NULL) {
		//			//mysql_num_fields(res)--->列数
		//			for (int i = 0; i < mysql_num_fields(res); i++)
		//				cout << setw(8) << row[i];
		//			cout << endl;
		//			row = mysql_fetch_row(res);
		//		}
		//	}
		//	else {
		//		cout << "\n无相关数据" << endl;
		//	}
		//}
		//mysql_free_result(res);
		return res;
	}
}
//统计总数
int DBUtils::get_num() {
	MYSQL_RES* res;
	MYSQL_ROW row;
	int num = 0;
	if (mysql_query(mysql, "select * from info"))
	{
		cout << "mysql语句执行失败！错误为:" << mysql_error(mysql) << endl;
	}
	else {
		res = mysql_use_result(mysql);
		if (res) {
			while ((row = mysql_fetch_row(res)) != NULL) {
				++num;
			}

		}
	}
	return num;
}

DBUtils::~DBUtils() {
	mysql_close(mysql);
}