#pragma once  //��ֹͷ�ļ��ظ�����
#include"Worker.h"
#include "DBUtils.h"
#include"Employee.h"
#include"Manager.h"
#include"Boss.h"
#include<unordered_map>
#include<mysql.h>
#include<string>
#include<iostream>
#include <iomanip>//stew��ͷ�ļ��������ֶο��
using namespace std;
class WorkerManager
{
public:
	//ְ������
	Worker** worker_arr = NULL;
	//ְ����Ŀ
	int worker_num = 0;
	WorkerManager();
	//�ж�Ա���Ƿ����
	int is_exist(int id=-1,string name="");
	//��ʼ��Ա��
	void init_worker();
	//չʾ�˵�
	void show_menu();
	//��ʾְ��
	void show_worker();
	//���ְ��
	void add_worker();
	//ɾ��ְ��
	void del_worker();
	//�޸�ְ����Ϣ
	void mod_worker();
	//��ѯ
	void find_worker();
	//���
	void empty();
	//�˳�ϵͳ
	void exit_system();
	~WorkerManager();
};

