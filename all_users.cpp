#pragma once

//all catering to all users
using namespace std;
#include "all_users.h"

void Show_MainMenu(mapfile& maps, System_status& status)
{
	//Show_Status(maps, status);
	string large_sep("===============================================");
	string short_sep("**********");
	int move = 0;
	if (status.level == -1)
	{
		cout << large_sep << endl;
		cout << "1.�û���¼ 2.�û�ע�� 3.����Ա��¼ 4.�˳�����" << endl;
		cout << large_sep << endl << endl << endl;
		move = get_num("���������");
		if (move == 1)
			Login(1, maps, status);
		if (move == 2)
			Make_User(maps, status);
		if (move == 3)
			Login(3, maps, status);
		if (move == 4) {
			cout << "��лʹ�ã������´��ټ���" << endl;
			exit(0);
		}
	}
	else if (status.level == 0) {//�������˵�
		cout << large_sep << endl;
		cout << "1.ע���û� 2.������� 3.�������� 4.������Ϣ����" << endl;
		cout << large_sep << endl;
		move = get_num("���������");
		if (status.usr->nuked == true) {
			cout << "\033[31m�û���ban������ϵ����Ա�����ڵǳ���\033[0m" << endl;
			Logout(maps, status);
		}
		if (move == 1) {
			status.level = -1;
			status.uid = -1;
			status.usr = NULL;
			cout << "�û��ѵǳ������ڷ������˵�..." << endl;
			Show_MainMenu(maps, status);
		}
		if (move == 2) {
			status.level = 1;
			Show_MainMenu(maps, status);
		}
		if (move == 3) {
			status.level = 2;
			Show_MainMenu(maps, status);
		}
		if (move == 4) {
			while (1) {
				cout << large_sep;
				Show_self(maps, status);
				cout << "1.�����û������� 2.�鿴/�޸���Ϣ 3.��ֵ" << endl;
				cout << large_sep;
				int input;
				input = get_num("�����������");
				if (input == 1)
					return;
				if (input == 2)
					MODIFY_INFO(maps, status);
				if (input == 3)
					Recharge(maps, status);
			}
		}
	}
	else if (status.level == 1) {
		cout << large_sep << endl;
		cout << "1.�鿴��Ʒ�б� 2.������Ʒ 3.������Ʒ 4.�鿴��ʷ���� 5.�鿴��Ʒ��ϸ��Ϣ 6.�����û�������"<<endl;
		cout << large_sep << endl;
		move = get_num("���������");
		switch (move)
		{
		case 1: {
			Show_Products(maps, status);
		}break;
		case 2: {
			trade(maps, status);
		}break;
		case 3: {
			search_prod(maps, status);
		}break;
		case 4: {
			Show_Orders(maps, status);
		}break;
		case 5: {
			SEE_INFO(maps, status);
		}break;
		case 6: {
			status.level = 0;
			Show_MainMenu(maps, status);
		}break;
		default:
			cout << "���Ϸ��Ĳ�������" << endl;
			break;
		}
	}
	else if (status.level == 2) {
		cout << large_sep<<endl;
		cout << "1.������Ʒ 2.�鿴������Ʒ 3.�޸���Ʒ��Ϣ/�¼���Ʒ 4.�鿴��ʷ���� 5.�����û�������" << endl;
		cout << large_sep<<endl;
		move = get_num("���������");
		switch (move)
		{
		case 1:
			Sell_Product(maps, status);
			break;
		case 2:
			Show_Products(maps, status);
			break;
		case 3:
			Modify_Product(maps, status);
			break;
		case 4:
			Show_Orders(maps, status);
			break;
		case 5:
			status.level = 0;
			break;
		default:
			cout << "���Ϸ��Ĳ�������" << endl;
			break;
		}
	}
	else if (status.level == 3) {
		cout << large_sep<<endl;
		cout << "1.�鿴������Ʒ 2.������Ʒ 3.�鿴���ж��� 4.�鿴�����û� 5.ɾ���û� 6.�¼���Ʒ 7.ע��" << endl;
		cout << large_sep<<endl;
		move = get_num("���������");
		switch (move) {
		case 1:
			Show_Products(maps, status);
			break;
		case 2:
			search_prod(maps, status);
			break;
		case 3:
			Show_Orders(maps, status);
			break;
		case 4:
			show_users(maps, status);
			break;
		case 5:
			delete_user(maps, status);
			break;
		case 6:
			delete_product(maps, status);
			break;
		case 7:
			Logout(maps, status);
			break;
		default:
			cout << "���Ϸ��Ĳ�������" << endl;
			break;
		}
	}
}

void Make_User(mapfile& maps, System_status& status)
{
	User* user = new User;
	user->id = ++status.ulength;
	get_str( "�������û���(2-10�ַ�����������ո�)��", user->username,  Name_Check);
	get_str( "����������(6-10�ַ�����������ո�)��", user->passwd,  Passwd_Check);
	get_str( "������绰����(11λ����������ո�)��", user->contact,  Contact_Check);
	get_str( "�������ַ(2-30�ַ�����������ո�)��", user->address,  Address_Check);
	user->balance = 0;
	Show_Status(maps, status);
	cout <<  "ע��ɹ����뷵�����������µ�¼��";
	maps.uid2usr.insert(pair<int, User*>(user->id, user));
	//show_users(maps, status);
	write_file(maps, status, "USER_DATA.txt");
	//Show_MainMenu(maps, status);
}

void Show_Status(mapfile& maps, System_status status)
{
	cout <<endl<<  "��ǰ�ȼ�Ϊ��" << status.level <<  "��ǰ�û�IDΪ��" << status.uid << endl;
}

void Show_self(mapfile& maps, System_status& status)
{
	if (status.level == 3) {
		cout << endl<<"��ǰȨ�޵ȼ���3" << endl << "��ݣ�����Ա" << endl << "����ҲҪ�úù�����" << endl;
	}
	else {
		cout <<endl<< "�û�����" << status.usr->username << endl
			<< "��ϵ��ʽ��" << status.usr->contact << endl
			<< "��ַ��" << status.usr->address << endl
			<< "Ǯ����" << status.usr->balance << endl;
	}
}
void Recharge(mapfile& maps, System_status& status)
{
	double quota;
	quota = get_double("�������ֵ��ȣ�");
	cout << status.usr->balance << endl << quota << endl;
	status.usr->balance += quota;
	cout << "��ֵ�ɹ������ڵĶ��Ϊ��" << status.usr->balance << endl;
}
void Show_Products(mapfile& maps, System_status& status)
{
	map<int, Product*>::iterator it, itEnd;
	it = maps.id2Product.begin();
	itEnd = maps.id2Product.end();
	cout << "ID\t����\t�۸�\t�ϼ�ʱ��\t����ID\t��Ʒ״̬";
	while (it != itEnd) {
		if (it->second->status != 1 && status.level == 1) {
			it++;
			continue;
		}
		if (status.level == 2 && it->second->sid != status.uid) {
			it++;
			continue;
		}
		cout << endl;
		cout.setf(ios::fixed);
		cout << setw(5) << setfill('0') << it->second->id << "\t";
		cout << it->second->name << "\t" << fixed << setprecision(2) <<it->second->price << "\t"\
			<< it->second->date << "\t" << fixed << setw(5)<<setfill('0')<<it->second->sid;
		if (it->second->status == 1)
			cout << "\t\033[32m������\033[0m" << endl;
		else if (it->second->status == 0)
			cout << "���۳�" << endl;
		else if (it->second->status == -1)
			cout << "\033[33m���¼�\033[0m" << endl;
		else if (it->second->status == -2)
			cout << "\033[31m������Ա�¼�\033[0m" << endl;
		it++;
	}
}

void Login(int mode, mapfile& maps, System_status& status)
{
	if (mode == 1) { //normal user login
		string uname;
		get_str("�������û�����", uname, Name_Check);
		map<string, User*>::iterator l_it;
		l_it = maps.uname2usr.find(uname);
		if (l_it == maps.uname2usr.end())
			cout << "�����˴�����û�����" << endl;
		else {
			string passwd = l_it->second->passwd;
			string input_passwd;
			get_str("���������룺", input_passwd, Passwd_Check);
			if (input_passwd == passwd) {
				cout <<  "��¼�ɹ���" << endl;
				status.level = 0;
				status.uid = l_it->second->id;
				status.usr = l_it->second;
			}
			else {
				cout <<  "������󣡼����������˵�...";
			}
		}
		Show_MainMenu(maps, status);
	}
	if (mode == 3) {
		string uname;
		string passwd;
		get_str("���������Ա���ƣ�", uname, Defalt_check);
		get_str("���������Ա���룺",passwd,Defalt_check);
		if (uname ==  "admin" && passwd == "123456") {
			cout <<  "��¼�ɹ���" << endl;
			status.level = 3;
			status.uid = -1;
		}
		else {
			cout <<  "��¼ʧ�ܡ�" << endl;
		}
	}
}

void Logout(mapfile& maps, System_status& state)
{
	state.level = -1;
	state.uid = 0;
	state.usr = NULL;
	cout <<  "�ǳ��ɹ�" << endl;
	cout <<  "���ڷ������˵�����" << endl;
}

void SEE_INFO(mapfile& maps, System_status& status)
{
	int id;
	id = get_num("��������Ҫ���ҵ���ƷID��");
	map<int, Product*>::iterator it;
	it = maps.id2Product.find(id);
	if (it == maps.id2Product.end()) {
		cout << "δ�ҵ�����Ʒ��������������ƷID��";
		search_prod(maps, status);
	}
	else if (it->second->status != 1 && status.level != 3) {
		cout << "��֣��ƺ�֮ǰ�и���Ʒ�������";
		search_prod(maps, status);
	}
	else {
		cout << "��ƷID��" << it->second->id << endl;
		cout << "��Ʒ���ƣ�" << it->second->name << endl;
		cout << "��Ʒ�۸�" << it->second->price << endl;
		cout << "��Ʒ������" << it->second->discription << endl;
		cout << "������ID��" << it->second->sid;
	}

}


void Show_Orders(mapfile& maps, System_status& status)
{
	map<int, Order*>::iterator it, itEnd;
	switch (status.level) {
	case 1:
	case 2:
		it = maps.id2Order.begin();
		itEnd = maps.id2Order.end();
		while (it != itEnd) {
			if (it->second->bid == status.uid)
				cout << "������" << " " << it->second->pid << " " << it->second->price << " " << it->second->date << " " << it->second->sid << " " << it->second->bid;
			else if (it->second->sid == status.uid)
				cout << "��������" << " " << it->second->pid << " " << it->second->price << " " << it->second->date << " " << it->second->sid << " " << it->second->bid;
		}
		break;
	case 3:
		it = maps.id2Order.begin();
		itEnd = maps.id2Order.end();
		while (it != itEnd) {
			cout << "ID\t��ƷID\t���׽��\t����ʱ��\t���ID\t����ID" << endl;
			cout << setw(5) << setfill('0') << it->second->oid;
			cout << "\t" << setw(5) << setfill('0') << it->second->pid << "\t";
			cout << fixed << setprecision(2) << it->second->price << "\t";
			cout << it->second->date << "\t" << setw(5) << setfill('0') << it->second->bid;
			cout << setw(5) << setfill('0') << it->second->sid << endl;
			it++;
		}
		break;
	}
	cout << "\033[31m������ע�⣺�����ֲ�ȷ����תλ�á�\033[0m" << endl;
}

void search_prod(mapfile& maps, System_status& status)
{
	cout << "������ע�⣺��ģ�黹δ���ƣ�ֻ��ȫ��ƥ�䡣" << endl;
	cout << "��������Ҫ���ҵ���Ʒ���ƣ�";
	string str;
	get_str("��������Ҫ���ҵ���Ʒ���ƣ�",str,Product_N_Check);
	map<string, Product*>::iterator it;
	it = maps.name2Product.find(str);
	if (it == maps.name2Product.end()) {
		cout << "δ�ҵ�����Ʒ��������������Ʒ���ƣ�";
		search_prod(maps, status);
	}
	else {
		if (it->second->status != 1 && status.level != 3) {
			cout << "��֣��ƺ�֮ǰ�и���Ʒ�������";
			search_prod(maps, status);
		}
		else {

			cout << "��ƷID��" << it->second->id << endl;
			cout << "��Ʒ���ƣ�" << it->second->name << endl;
			cout << "��Ʒ�۸�" << it->second->price << endl;
			cout << "��Ʒ������" << it->second->discription << endl;
			cout << "������ID��" << it->second->sid;
		}
	}
	cout << "\033[31m������ע�⣺�����ֲ�ȷ����תλ�á�\033[0m" << endl;
}

