#pragma once  //防止头文件重复包含
#include"Worker.h"
#include "DBUtils.h"
#include"Employee.h"
#include"Manager.h"
#include"Boss.h"
#include<unordered_map>
#include<mysql.h>
#include<string>
#include<iostream>
#include <iomanip>//stew的头文件，设置字段宽度
using namespace std;
class WorkerManager
{
public:
	//职工数组
	Worker** worker_arr = NULL;
	//职工数目
	int worker_num = 0;
	WorkerManager();
	//判断员工是否存在
	int is_exist(int id=-1,string name="");
	//初始化员工
	void init_worker();
	//展示菜单
	void show_menu();
	//显示职工
	void show_worker();
	//添加职工
	void add_worker();
	//删除职工
	void del_worker();
	//修改职工信息
	void mod_worker();
	//查询
	void find_worker();
	//清空
	void empty();
	//退出系统
	void exit_system();
	~WorkerManager();
};

