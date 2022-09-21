#include "Boss.h"
Boss::Boss(int id,string name,string sex,int post_id){
	this->id = id;
	this->name = name;
	this->sex = sex;
	this->post_id = post_id;
}
//显示个人信息
void Boss::show_info(){
	cout << "职工编号： " << this->id
		<< "\t职工姓名： " << this->name
		<<"\t职工性别： "<<this->sex
		<< "\t岗位： " << this->get_PostName()
		<< "\t岗位职责：管理公司所有事务" << endl;
}
//获取岗位名称
string Boss::get_PostName() { return "老板"; }
Boss::~Boss(){}