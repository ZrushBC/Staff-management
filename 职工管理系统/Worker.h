#pragma once
#pragma once
#include<string>
using namespace std;
class Worker
{
public:
	//ְ�����
	int id;
	//����
	string name;
	//�Ա�
	string sex;
	//���ű��
	int post_id;
	//��ʾ������Ϣ
	virtual void show_info() = 0;
	//��ȡ��λ����
	virtual string get_PostName() = 0;
};

