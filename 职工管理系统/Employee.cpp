#include "Employee.h"
//显示个人信息
Employee::Employee(int id, string name, string sex, int post_id){
	this->id = id;
	this->name = name;
	this->sex = sex;
	this->post_id = post_id;
}
void Employee::show_info() {
	cout << "职工编号： " << this->id
		<< "\t职工姓名： " << this->name
		<< "\t职工性别： " << this->sex
		<< "\t岗位： " << this->get_PostName()
		<< "\t岗位职责：完成经理交给的任务" << endl;
}
//获取岗位名称
string Employee::get_PostName() { return "普通职工"; }
Employee::~Employee(){}