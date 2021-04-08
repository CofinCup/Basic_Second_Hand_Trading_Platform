#pragma once

#include "admin.h"

using namespace std;
void show_users(mapfile& maps, System_status& status)
{
	map<int, User*>::iterator it, itEnd;
	it = maps.uid2usr.begin();
	itEnd = maps.uid2usr.end();
	cout << "�û�ID" << setfill(' ') << setw(15) << "�û���" << setw(15) << "��ϵ��ʽ" << setw(30)
		<< "��ַ" << setw(10) << "���" << setw(3) << "    �˻�״̬" << endl;
	while (it != itEnd) {
		cout << " " << setfill('0') << setw(5) << it->second->id;
		cout << setfill(' ') << setw(15) << it->second->username \
			<< setw(15) << it->second->contact << setw(30) << it->second->address\
			<< setw(10) << setiosflags(ios::fixed) << setprecision(2) \
			<< it->second->balance;
		if (it->second->nuked == true)
			cout << "    \033[31m�����\033[0m" << endl;
		else
			cout << "    ����" << endl;
		++it;
	}

	Press_Enter_to_Continue();
}


void delete_user(mapfile& maps, System_status status)
{
	int id;
	id = get_num("������Ҫɾ�����û�ID��");
	map<int, User*>::iterator l_it;
	l_it = maps.uid2usr.find(id);
	if (l_it == maps.uid2usr.end())
		cout << "���û������ڡ�" << endl;
	else if (l_it->second->nuked == 1)
		cout << "���û��ѱ�ɾ����" << endl;
	else {
		l_it->second->nuked = 1;
		write_file(maps, status, "USER_DATA.txt");
		cout << "�ɹ�ɾ�����û���" << endl;
	}
}

void delete_product(mapfile& maps, System_status& status)
{
	int id;
	id = get_num("������Ҫ�¼ܵ���ƷID��");
	map<int, Product*>::iterator l_it;
	l_it = maps.id2Product.find(id);
	if (l_it == maps.id2Product.end())
		cout << "����Ʒ�����ڡ�" << endl;
	else if (l_it->second->status != 1)
		cout << "����Ʒ��������״̬��" << endl;
	else {
		l_it->second->status = -2;
		write_file(maps, status, "PRODUCT_DATA.txt");
		cout << "�ɹ��¼ܸ���Ʒ��" << endl;
	}
	Press_Enter_to_Continue();
}

void rivive_product(mapfile& maps, System_status& status)
{
	int id;
	id = get_num("������Ҫ�ָ�����ƷID��");
	map<int, Product*>::iterator l_it;
	l_it = maps.id2Product.find(id);
	if (l_it == maps.id2Product.end())
		cout << "����Ʒ�����ڡ�" << endl;
	else if (l_it->second->status != -2)
		cout << "����Ʒ���Ǳ�����Ա�¼�״̬��" << endl;
	else {
		l_it->second->status = -2;
		write_file(maps, status, "PRODUCT_DATA.txt");
		cout << "�ɹ��ָ�����Ʒ��" << endl;
	}
	Press_Enter_to_Continue();
}