#include "Manager.h"
Manager::Manager(int id, string name, string sex, int post_id){
	this->id = id;
	this->name = name;
	this->sex = sex;
	this->post_id = post_id;
}
//��ʾ������Ϣ
void Manager::show_info(){
	cout << "ְ����ţ� " << this->id
		<< "\tְ�������� " << this->name
		<< "\tְ���Ա� " << this->sex
		<< "\t��λ�� " << this->get_PostName()
		<< "\t��λְ������ϰ彻�������񣬲��·������Ա��" << endl;
}
//��ȡ��λ����
string Manager::get_PostName() { return "����"; }
Manager::~Manager(){}