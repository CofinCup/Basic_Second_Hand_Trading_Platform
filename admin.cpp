#pragma once

#include "admin.h"

using namespace std;
void show_users(mapfile& maps, System_status& status)
{
	map<int, User*>::iterator it, itEnd;
	it = maps.uid2usr.begin();
	itEnd = maps.uid2usr.end();
	while (it != itEnd) {
		string sep = "********************";
		cout << "�û�ID\t�û���\t��ϵ��ʽ\t��ַ\tǮ�����" << endl;
		cout.setf(ios::fixed);
		cout << setw(5) << setfill('0') << it->second->id << "\t";
		cout << it->second->username << "\t" << it->second->contact << "\t"\
			<< it->second->address << "\t\t" << fixed << setprecision(2) << it->second->balance << endl;
		it++;
	}
	cout << "\033[31m������ע�⣺�����ֲ�ȷ����תλ�á�\033[0m" << endl;
	//Show_MainMenu(maps, status);
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
	cout << "\033[31m������ע�⣺�����ֲ�ȷ����תλ�á�\033[0m" << endl;
	//Show_MainMenu(maps, status);
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
		cout << "����Ʒ�ѱ��¼ܡ�" << endl;
	else {
		l_it->second->status = -2;
		write_file(maps, status, "PRODUCT_DATA.txt");
		cout << "�ɹ��¼ܸ���Ʒ��" << endl;
	}
	cout << "\033[31m������ע�⣺�����ֲ�ȷ����תλ�á�\033[0m" << endl;
	//Show_MainMenu(maps, status);
}