#include "WorkerManager.h"
WorkerManager::WorkerManager() {
	DBUtils db;
	this->worker_num = db.get_num();
	this->worker_arr = new Worker * [worker_num];
	this->init_worker();
}
//判断员工是否存在
int WorkerManager::is_exist(int id,string name) {
	for (int i = 0; i < this->worker_num; i++) {
		if (this->worker_arr[i]->id == id|| this->worker_arr[i]->name._Equal(name)) return i;
	}
	return -1;
}
//初始化员工
void WorkerManager::init_worker() {
	DBUtils db;
	MYSQL_RES* res = db.inq();
	MYSQL_ROW row;
	int index = 0;
	if (res) {
		while ((row = mysql_fetch_row(res)) != NULL) {
			Worker* worker = NULL;
			switch (stoi(row[3]))
			{
				//普通职工
			case 1:worker = new Employee(stoi(row[0]), row[1], row[2], stoi(row[3])); break;
				//经理
			case 2:worker = new Manager(stoi(row[0]), row[1], row[2], stoi(row[3])); break;
				//老板
			case 3:worker = new Boss(stoi(row[0]), row[1], row[2], stoi(row[3])); break;
			}
			this->worker_arr[index++] = worker;
		}
	}
}
//菜单
void WorkerManager::show_menu() {
	cout << "欢迎使用职工管理系统" << endl;
	cout << "1.显示职工信息" << endl;
	cout << "2.添加职工" << endl;
	cout << "3.删除职工" << endl;
	cout << "4.修改职工信息" << endl;
	cout << "5.查找职工" << endl;
	cout << "6.清空" << endl;
	cout << "7.退出" << endl;
	return;
}
//显示职工
void WorkerManager::show_worker() {
	if (this->worker_num) cout << "无职工数据" << endl;
	for (int i = 0; i < this->worker_num; i++) {
		this->worker_arr[i]->show_info();
	}
}

//添加职工
void WorkerManager::add_worker() {
	int num = 0;
	cout << "\n请输入添加的人数：";
	cin >> num;
	//新的职工数目
	int size = this->worker_num + num;
	//开辟新空间
	Worker** space = new Worker * [size];
	//原有数据迁移
	for (int i = 0; i < this->worker_num; i++) {
		space[i] = this->worker_arr[i];
	}
	//新数据添加
	DBUtils db;
	for (int i = 0; i < num; i++) {
		string id;
		string name;
		string sex;
		string post;
		while (true) {
			cout << "输入id：";
			cin >> id;
			if (id.size() == 1 && id[0] == '0')break;
			if (atoi(id.c_str())) {
				if (this->is_exist(atoi(id.c_str()))!=-1) cout << "\n职工编号已存在,请重新";
				else break;
			}
			else cout << "id非数字，请重新";
		}
		cout << "输入姓名：";
		cin >> name;
		while (true) {
			string flag;
			cout << "选择性别： " << endl;
			cout << "1、男" << endl;
			cout << "2、女" << endl;
			cin >> flag;
			if (flag._Equal("1")) { sex = "男"; break; }
			else if (flag._Equal("2")) { sex = "女"; break; }
			else cout << "\n选项无效,请重新";
		}
		while (true) {
			cout << "选择该职工岗位： " << endl;
			cout << "1、普通职工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;
			cin >> post;
			if (post._Equal("1")|| post._Equal("2")|| post._Equal("3"))break;
			else cout<< "\n选项无效,请重新";
		}
		Worker* worker = NULL;
		switch (atoi(post.c_str()))
		{
			//普通职工
		case 1:worker = new Employee(atoi(id.c_str()), name, sex, atoi(post.c_str())); break;
			//经理
		case 2:worker = new Manager(atoi(id.c_str()), name, sex, atoi(post.c_str())); break;
			//老板
		case 3:worker = new Boss(atoi(id.c_str()), name, sex, atoi(post.c_str())); break;
		}
		space[this->worker_num + i] = worker;
		db.add(id, name, sex, post);
	}
	delete[] this->worker_arr;
	this->worker_arr = space;
	this->worker_num = size;
	cout << "添加成功" << endl;
}

//删除职工
void WorkerManager::del_worker() {
	string id;
	int size=0;
	while (true) {
		cout << "输入id：";
		cin >> id;
		if (id.size() == 1 && id[0] == '0')break;
		if (atoi(id.c_str())) {
			size = this->is_exist(atoi(id.c_str()));
			if (size==-1) cout << "\n职工编号不存在,请重新";
			else break;
		}
		else cout << "id非数字，请重新";
	}
	for (int i = size; i < this->worker_num; i++){
		this->worker_arr[i] = this->worker_arr[i + 1];
	}
	this->worker_num--;
	DBUtils db;
	db.del(id);
	cout << "删除成功" << endl;
}

//修改职工信息
void WorkerManager::mod_worker() {
	string id;
	string name;
	string sex;
	string post;
	string str;
	string flag;
	while (true) {
		cout << "输入id：";
		cin >> id;
		if (id.size() == 1 && id[0] == '0')break;
		if (atoi(id.c_str())) {
			if (this->is_exist(atoi(id.c_str())) == -1) cout << "\n职工编号不存在,请重新";
			else break;
		}
		else cout << "id非数字，请重新";
	}
	while (true) {
		cout << "\n修改内容如下：" << endl;
		cout << "1.姓名" << endl;
		cout << "2.性别" << endl;
		cout << "3.岗位" << endl;
		cout << "请输入选项:";
		cin >> flag;
		if (flag._Equal("1") || flag._Equal("2")|| flag._Equal("3")) {
			switch (flag[0])
			{
			case '1':
				cout << "新的姓名：";
				cin >> str;
				name = str;
				sex = this->worker_arr[this->is_exist(atoi(id.c_str()))]->sex;
				post = to_string(this->worker_arr[this->is_exist(atoi(id.c_str()))]->post_id);
				break;
			case '2':
				while (true) {
					string flag1;
					cout << "选择性别： " << endl;
					cout << "1、男" << endl;
					cout << "2、女" << endl;
					cin >> flag1;
					if (flag1._Equal("1")) { str = "男"; break; }
					else if (flag1._Equal("2")) { str = "女"; break; }
					else cout << "\n选项无效,请重新";
				}
				name = this->worker_arr[this->is_exist(atoi(id.c_str()))]->name;
				sex = str;
				post = to_string(this->worker_arr[this->is_exist(atoi(id.c_str()))]->post_id);
				break;
			case '3':
				while (true) {
					cout << "选择该职工岗位： " << endl;
					cout << "1、普通职工" << endl;
					cout << "2、经理" << endl;
					cout << "3、老板" << endl;
					cin >> str;
					if (str._Equal("1") || str._Equal("2") || str._Equal("3"))break;
					else cout << "\n选项无效,请重新";
				}
				name = this->worker_arr[this->is_exist(atoi(id.c_str()))]->name;
				sex = this->worker_arr[this->is_exist(atoi(id.c_str()))]->sex;
				post = str;
				break;
			}
			break;
		}
		else cout << "\n请输入有效的选项:\n";
	}
	Worker* worker = NULL;
	switch (atoi(post.c_str()))
	{
		//普通职工
	case 1:worker = new Employee(atoi(id.c_str()), name, sex, atoi(post.c_str())); break;
		//经理
	case 2:worker = new Manager(atoi(id.c_str()), name, sex, atoi(post.c_str())); break;
		//老板
	case 3:worker = new Boss(atoi(id.c_str()), name, sex, atoi(post.c_str())); break;
	}
	this->worker_arr[this->is_exist(atoi(id.c_str()))] = worker;	
	DBUtils db;
	db.rev(id, str, flag[0]);
	cout << "修改成功" << endl;
}

//查询
void WorkerManager::find_worker() {
	string flag = "";
	string str = "";
	while (true) {
		cout << "\n查找方式有：" << endl;
		cout << "1.按职工编号查询" << endl;
		cout << "2.按职工姓名查询" << endl;
		cout << "请输入选项:";
		cin >> flag;
		if (flag._Equal("1") || flag._Equal("2")) {
			if (flag._Equal("1")) {
				cout << "请输入编号：";
				cin >> str;
				if (this->is_exist(atoi(str.c_str()))!=-1)
					this->worker_arr[this->is_exist(atoi(str.c_str()))]->show_info();
				else cout << "\n无相关数据" << endl;
			}
			else {
				cout << "请输入姓名：";
				cin >> str;
				if (this->is_exist(-1,str) != -1)
					this->worker_arr[this->is_exist(-1,str)]->show_info();
				else cout << "\n无相关数据" << endl;
			}
			break;
		}
		else cout << "\n请输入有效的选项\n:";
	}

}

//清空
void WorkerManager::empty() {
	string flag;
	while (true) {
		cout << "确定清空？" << endl;
		cout << "1、确定" << endl;
		cout << "2、返回" << endl;
		cin >> flag;
		if (flag._Equal("1")) break;
		if (flag._Equal("2")) return;
		cout << "\n选项无效,";
	}
	if (this->worker_arr != NULL)
	{
		for (int i = 0; i < this->worker_num; i++)
		{
			if (this->worker_arr[i] != NULL)
			{
				delete this->worker_arr[i];
			}
		}

		delete[] this->worker_arr;
		this->worker_arr = NULL;
	}
	this->worker_num = 0;
	DBUtils db;
	db.del();
}

//退出
void WorkerManager::exit_system() {
	cout << "期待您的下次使用" << endl;
	exit(0);
}

WorkerManager::~WorkerManager() {
	if (this->worker_arr != NULL)
	{
		for (int i = 0; i < this->worker_num; i++)
		{
			if (this->worker_arr[i] != NULL)
			{
				delete this->worker_arr[i];
			}
		}

		delete[] this->worker_arr;
		this->worker_arr = NULL;
	}
}