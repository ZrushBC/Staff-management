#include "Boss.h"
Boss::Boss(int id,string name,string sex,int post_id){
	this->id = id;
	this->name = name;
	this->sex = sex;
	this->post_id = post_id;
}
//��ʾ������Ϣ
void Boss::show_info(){
	cout << "ְ����ţ� " << this->id
		<< "\tְ�������� " << this->name
		<<"\tְ���Ա� "<<this->sex
		<< "\t��λ�� " << this->get_PostName()
		<< "\t��λְ�𣺹���˾��������" << endl;
}
//��ȡ��λ����
string Boss::get_PostName() { return "�ϰ�"; }
Boss::~Boss(){}