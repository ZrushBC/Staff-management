#include "Employee.h"
//��ʾ������Ϣ
Employee::Employee(int id, string name, string sex, int post_id){
	this->id = id;
	this->name = name;
	this->sex = sex;
	this->post_id = post_id;
}
void Employee::show_info() {
	cout << "ְ����ţ� " << this->id
		<< "\tְ�������� " << this->name
		<< "\tְ���Ա� " << this->sex
		<< "\t��λ�� " << this->get_PostName()
		<< "\t��λְ����ɾ�����������" << endl;
}
//��ȡ��λ����
string Employee::get_PostName() { return "��ְͨ��"; }
Employee::~Employee(){}