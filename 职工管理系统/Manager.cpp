#include "Manager.h"
Manager::Manager(int id, string name, string sex, int post_id){
	this->id = id;
	this->name = name;
	this->sex = sex;
	this->post_id = post_id;
}
//显示个人信息
void Manager::show_info(){
	cout << "职工编号： " << this->id
		<< "\t职工姓名： " << this->name
		<< "\t职工性别： " << this->sex
		<< "\t岗位： " << this->get_PostName()
		<< "\t岗位职责：完成老板交给的任务，并下发任务给员工" << endl;
}
//获取岗位名称
string Manager::get_PostName() { return "经理"; }
Manager::~Manager(){}