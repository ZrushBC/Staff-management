#include<iostream>
#include "WorkerManager.h"
#include "DBUtils.h"
using namespace std;
int main() {
	WorkerManager wm;
	char choice;
	while (true) {
		wm.show_menu();
		cout << "����������ѡ��";
		cin >> choice;
		switch (choice)
		{
		case '1':wm.show_worker(); break;
		case '2':wm.add_worker(); break;
		case '3':wm.del_worker(); break;
		case '4':wm.mod_worker(); break;
		case '5':wm.find_worker(); break;
		case '6':wm.empty(); break;
		case '7':wm.exit_system(); break;
		default:cout << "\n��������Ч��ѡ��"<<endl; break;
		}
		system("pause");
		system("cls");
	}
	return 0;
}