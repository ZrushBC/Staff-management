#include "DBUtils.h"
#include<mysql.h>
#include<iostream>
#include <iomanip>//stew��ͷ�ļ��������ֶο��
#include<string>
using namespace std;

DBUtils::DBUtils() {
	mysql = mysql_init(NULL);
	if (mysql == NULL) {
		printf("���ݿ��ʼ������");
	}
	//�����ַ�����
	mysql_options(mysql, MYSQL_SET_CHARSET_NAME, "gbk");
	//�������ݿ�
	if (mysql_real_connect(mysql, "127.0.0.1", "root", "123456", "worker", 3306, NULL, 0)) {
		//printf("���ӳɹ�!\n ");
	}
	else {
		printf("����ʧ�ܣ�����Ϊ��%s", mysql_error(mysql));
	}
}
//��
void DBUtils::add(string id,string name,string sex,string post) {
	string sql = "insert into info values("+id+",'"+name+"','"+sex+"',"+post+")";
	if (!mysql_query(mysql, sql.c_str()))//����
		printf("�������!\n");
	else printf("����ʧ��!\n");
}
//ɾ
void DBUtils::del(string id) {
	string sql = "delete from info";
	if (!id.empty())
		sql = sql + " where id=" + id;
	if (!mysql_query(mysql, sql.c_str()))//ɾ��
		printf("ɾ�����!\n");
	else printf("ɾ��ʧ��!\n");
}
//��,���ձ��ȥ��
void DBUtils::rev(string id, string str,char flag) {
	string sql = "update info set ";
	switch (flag)
	{
	case '1':sql = sql + " name=" + "'" + str + "'" + " where id = " + id; break;
	case '2':sql = sql + " sex=" + "'" + str + "'" + " where id = " + id; break;
	case '3':sql = sql + " post=" + "'" + str + "'" + " where id = " + id; break;
	}
	if (!mysql_query(mysql, sql.c_str()))//�޸�
		printf("�޸����!\n");
	else printf("�޸�ʧ��!\n");
}
//��
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
	//�鿴�������ݱ�  .c_str()��stringת����const char *
	if (mysql_query(mysql, sql.c_str()))
	{
		cout << "mysql���ִ��ʧ�ܣ�����Ϊ:" << mysql_error(mysql) << endl;
	}
	else {
		res = mysql_use_result(mysql);
		//if (res) {
		//	row = mysql_fetch_row(res);
		//	if (row != NULL) {
		//		cout << "\n��Ϣ����:" << endl;
		//		while (row != NULL) {
		//			//mysql_num_fields(res)--->����
		//			for (int i = 0; i < mysql_num_fields(res); i++)
		//				cout << setw(8) << row[i];
		//			cout << endl;
		//			row = mysql_fetch_row(res);
		//		}
		//	}
		//	else {
		//		cout << "\n���������" << endl;
		//	}
		//}
		//mysql_free_result(res);
		return res;
	}
}
//ͳ������
int DBUtils::get_num() {
	MYSQL_RES* res;
	MYSQL_ROW row;
	int num = 0;
	if (mysql_query(mysql, "select * from info"))
	{
		cout << "mysql���ִ��ʧ�ܣ�����Ϊ:" << mysql_error(mysql) << endl;
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