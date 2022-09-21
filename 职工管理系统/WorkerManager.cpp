#include "WorkerManager.h"
WorkerManager::WorkerManager() {
	DBUtils db;
	this->worker_num = db.get_num();
	this->worker_arr = new Worker * [worker_num];
	this->init_worker();
}
//�ж�Ա���Ƿ����
int WorkerManager::is_exist(int id,string name) {
	for (int i = 0; i < this->worker_num; i++) {
		if (this->worker_arr[i]->id == id|| this->worker_arr[i]->name._Equal(name)) return i;
	}
	return -1;
}
//��ʼ��Ա��
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
				//��ְͨ��
			case 1:worker = new Employee(stoi(row[0]), row[1], row[2], stoi(row[3])); break;
				//����
			case 2:worker = new Manager(stoi(row[0]), row[1], row[2], stoi(row[3])); break;
				//�ϰ�
			case 3:worker = new Boss(stoi(row[0]), row[1], row[2], stoi(row[3])); break;
			}
			this->worker_arr[index++] = worker;
		}
	}
}
//�˵�
void WorkerManager::show_menu() {
	cout << "��ӭʹ��ְ������ϵͳ" << endl;
	cout << "1.��ʾְ����Ϣ" << endl;
	cout << "2.���ְ��" << endl;
	cout << "3.ɾ��ְ��" << endl;
	cout << "4.�޸�ְ����Ϣ" << endl;
	cout << "5.����ְ��" << endl;
	cout << "6.���" << endl;
	cout << "7.�˳�" << endl;
	return;
}
//��ʾְ��
void WorkerManager::show_worker() {
	if (this->worker_num) cout << "��ְ������" << endl;
	for (int i = 0; i < this->worker_num; i++) {
		this->worker_arr[i]->show_info();
	}
}

//���ְ��
void WorkerManager::add_worker() {
	int num = 0;
	cout << "\n��������ӵ�������";
	cin >> num;
	//�µ�ְ����Ŀ
	int size = this->worker_num + num;
	//�����¿ռ�
	Worker** space = new Worker * [size];
	//ԭ������Ǩ��
	for (int i = 0; i < this->worker_num; i++) {
		space[i] = this->worker_arr[i];
	}
	//���������
	DBUtils db;
	for (int i = 0; i < num; i++) {
		string id;
		string name;
		string sex;
		string post;
		while (true) {
			cout << "����id��";
			cin >> id;
			if (id.size() == 1 && id[0] == '0')break;
			if (atoi(id.c_str())) {
				if (this->is_exist(atoi(id.c_str()))!=-1) cout << "\nְ������Ѵ���,������";
				else break;
			}
			else cout << "id�����֣�������";
		}
		cout << "����������";
		cin >> name;
		while (true) {
			string flag;
			cout << "ѡ���Ա� " << endl;
			cout << "1����" << endl;
			cout << "2��Ů" << endl;
			cin >> flag;
			if (flag._Equal("1")) { sex = "��"; break; }
			else if (flag._Equal("2")) { sex = "Ů"; break; }
			else cout << "\nѡ����Ч,������";
		}
		while (true) {
			cout << "ѡ���ְ����λ�� " << endl;
			cout << "1����ְͨ��" << endl;
			cout << "2������" << endl;
			cout << "3���ϰ�" << endl;
			cin >> post;
			if (post._Equal("1")|| post._Equal("2")|| post._Equal("3"))break;
			else cout<< "\nѡ����Ч,������";
		}
		Worker* worker = NULL;
		switch (atoi(post.c_str()))
		{
			//��ְͨ��
		case 1:worker = new Employee(atoi(id.c_str()), name, sex, atoi(post.c_str())); break;
			//����
		case 2:worker = new Manager(atoi(id.c_str()), name, sex, atoi(post.c_str())); break;
			//�ϰ�
		case 3:worker = new Boss(atoi(id.c_str()), name, sex, atoi(post.c_str())); break;
		}
		space[this->worker_num + i] = worker;
		db.add(id, name, sex, post);
	}
	delete[] this->worker_arr;
	this->worker_arr = space;
	this->worker_num = size;
	cout << "��ӳɹ�" << endl;
}

//ɾ��ְ��
void WorkerManager::del_worker() {
	string id;
	int size=0;
	while (true) {
		cout << "����id��";
		cin >> id;
		if (id.size() == 1 && id[0] == '0')break;
		if (atoi(id.c_str())) {
			size = this->is_exist(atoi(id.c_str()));
			if (size==-1) cout << "\nְ����Ų�����,������";
			else break;
		}
		else cout << "id�����֣�������";
	}
	for (int i = size; i < this->worker_num; i++){
		this->worker_arr[i] = this->worker_arr[i + 1];
	}
	this->worker_num--;
	DBUtils db;
	db.del(id);
	cout << "ɾ���ɹ�" << endl;
}

//�޸�ְ����Ϣ
void WorkerManager::mod_worker() {
	string id;
	string name;
	string sex;
	string post;
	string str;
	string flag;
	while (true) {
		cout << "����id��";
		cin >> id;
		if (id.size() == 1 && id[0] == '0')break;
		if (atoi(id.c_str())) {
			if (this->is_exist(atoi(id.c_str())) == -1) cout << "\nְ����Ų�����,������";
			else break;
		}
		else cout << "id�����֣�������";
	}
	while (true) {
		cout << "\n�޸��������£�" << endl;
		cout << "1.����" << endl;
		cout << "2.�Ա�" << endl;
		cout << "3.��λ" << endl;
		cout << "������ѡ��:";
		cin >> flag;
		if (flag._Equal("1") || flag._Equal("2")|| flag._Equal("3")) {
			switch (flag[0])
			{
			case '1':
				cout << "�µ�������";
				cin >> str;
				name = str;
				sex = this->worker_arr[this->is_exist(atoi(id.c_str()))]->sex;
				post = to_string(this->worker_arr[this->is_exist(atoi(id.c_str()))]->post_id);
				break;
			case '2':
				while (true) {
					string flag1;
					cout << "ѡ���Ա� " << endl;
					cout << "1����" << endl;
					cout << "2��Ů" << endl;
					cin >> flag1;
					if (flag1._Equal("1")) { str = "��"; break; }
					else if (flag1._Equal("2")) { str = "Ů"; break; }
					else cout << "\nѡ����Ч,������";
				}
				name = this->worker_arr[this->is_exist(atoi(id.c_str()))]->name;
				sex = str;
				post = to_string(this->worker_arr[this->is_exist(atoi(id.c_str()))]->post_id);
				break;
			case '3':
				while (true) {
					cout << "ѡ���ְ����λ�� " << endl;
					cout << "1����ְͨ��" << endl;
					cout << "2������" << endl;
					cout << "3���ϰ�" << endl;
					cin >> str;
					if (str._Equal("1") || str._Equal("2") || str._Equal("3"))break;
					else cout << "\nѡ����Ч,������";
				}
				name = this->worker_arr[this->is_exist(atoi(id.c_str()))]->name;
				sex = this->worker_arr[this->is_exist(atoi(id.c_str()))]->sex;
				post = str;
				break;
			}
			break;
		}
		else cout << "\n��������Ч��ѡ��:\n";
	}
	Worker* worker = NULL;
	switch (atoi(post.c_str()))
	{
		//��ְͨ��
	case 1:worker = new Employee(atoi(id.c_str()), name, sex, atoi(post.c_str())); break;
		//����
	case 2:worker = new Manager(atoi(id.c_str()), name, sex, atoi(post.c_str())); break;
		//�ϰ�
	case 3:worker = new Boss(atoi(id.c_str()), name, sex, atoi(post.c_str())); break;
	}
	this->worker_arr[this->is_exist(atoi(id.c_str()))] = worker;	
	DBUtils db;
	db.rev(id, str, flag[0]);
	cout << "�޸ĳɹ�" << endl;
}

//��ѯ
void WorkerManager::find_worker() {
	string flag = "";
	string str = "";
	while (true) {
		cout << "\n���ҷ�ʽ�У�" << endl;
		cout << "1.��ְ����Ų�ѯ" << endl;
		cout << "2.��ְ��������ѯ" << endl;
		cout << "������ѡ��:";
		cin >> flag;
		if (flag._Equal("1") || flag._Equal("2")) {
			if (flag._Equal("1")) {
				cout << "�������ţ�";
				cin >> str;
				if (this->is_exist(atoi(str.c_str()))!=-1)
					this->worker_arr[this->is_exist(atoi(str.c_str()))]->show_info();
				else cout << "\n���������" << endl;
			}
			else {
				cout << "������������";
				cin >> str;
				if (this->is_exist(-1,str) != -1)
					this->worker_arr[this->is_exist(-1,str)]->show_info();
				else cout << "\n���������" << endl;
			}
			break;
		}
		else cout << "\n��������Ч��ѡ��\n:";
	}

}

//���
void WorkerManager::empty() {
	string flag;
	while (true) {
		cout << "ȷ����գ�" << endl;
		cout << "1��ȷ��" << endl;
		cout << "2������" << endl;
		cin >> flag;
		if (flag._Equal("1")) break;
		if (flag._Equal("2")) return;
		cout << "\nѡ����Ч,";
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

//�˳�
void WorkerManager::exit_system() {
	cout << "�ڴ������´�ʹ��" << endl;
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