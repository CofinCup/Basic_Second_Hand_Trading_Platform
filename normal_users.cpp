#pragma once
#include "normal_users.h"

using namespace std;

void trade(mapfile& maps, System_status& status)
{
	int id;
	id = get_num("���������������ƷID,����0��ȡ����");
	if (id == 0)
		return;
	map<int, Product*>::iterator it;
	it = maps.id2Product.find(id);
	if (it == maps.id2Product.end()) {
		cout << "δ�ҵ�����Ʒ��" << endl;
		trade(maps, status);
	}
	else {
		cout << "��ƷID��" << it->second->id << endl;
		cout << "��Ʒ���ƣ�" << it->second->name << endl;
		cout << "��Ʒ�۸�" << it->second->price << endl;
		cout << "��Ʒ������" << it->second->discription << endl;
		cout << "������ID��" << it->second->sid << endl;
		double price = it->second->price;
		if (it->second->price > status.usr->balance)
			cout << "��Ʒ�ļ۸���������" << endl;
		else if (it->second->status != 1) {
			cout << "��֣��ƺ�֮ǰ�и���Ʒ���������" << endl;
			Press_Enter_to_Continue();
		}
		else if (it->second->sid == status.uid) {
			cout << "���ܹ����Լ�����Ʒ��" << endl;
			Press_Enter_to_Continue();
		}
		else {
			cout << "ȷ��Ҫ������(y/n)" << endl;
			string str;
			getline(cin, str);
			while (str != "y" && str != "n" && str != "Y" && str != "N") {
				cout << "������y/n" << endl;
				getline(cin, str);
			}
			if (str == "n" || str == "N")
				return;
			status.usr->balance -= it->second->price;
			it->second->status = 0;
			Order* odr = new Order;
			odr->bid = status.uid;
			odr->pid = it->second->id;
			odr->oid = ++status.olength;
			odr->price = it->second->price;
			odr->sid = it->second->sid;
			odr->date = getTime();
			maps.id2Order.insert(pair<int, Order*>(odr->oid, odr));
			cout << endl << "���׳ɹ�����ǰ��" << status.usr->balance << endl;
			cout << "���ڷ������˵�����" << endl;
			Sleep(1500);
		}
		write_file(maps, status, "USER_DATA.txt");
		write_file(maps, status, "PRODUCT_DATA.txt");
		write_file(maps, status, "ORDER_DATA.txt");
	}
}

void MODIFY_INFO(mapfile& maps, System_status& status)
{
	int move;
	move = get_num("��ѡ���޸ĵ�����(1.�û��� 2.��ϵ��ʽ 3.��ַ �������֣�����)");
	if (move == 1) {
		string str;
		get_str("�������û���,����ԭ�����û�����ȡ����", str, Name_Check);
		if (str == status.usr->username) {
			cout << "��ȡ����" << endl;
		}
		else if (str.find(' ')) {
			cout << "�û����в��ܺ��пո�" << endl;
		}
		else if (maps.uname2usr.find(str) != maps.uname2usr.end()) {
			cout << "�޸�ʧ�ܣ��û�����ռ�á�";
			get_str("�������û���,����ԭ�����û�����ȡ����", str, Name_Check);
		}
		else {
			maps.uname2usr.erase(status.usr->username);
			maps.uname2usr.insert(pair<string, User*>(status.usr->username, status.usr));
			status.usr->username = str;
			write_file(maps, status, "USER_DATA.txt");
			cout << "�޸ĳɹ���";
		}
		return;
	}
	else if (move == 2) {
		string str;
		get_str("��������ϵ��ʽ,����ԭ������ϵ��ʽ��ȡ����", str, Contact_Check);
		if (str == status.usr->contact) {
			cout << "��ȡ����" << endl;
			return;
		}
		else {
			status.usr->contact = str;
			write_file(maps, status, "USER_DATA.txt");
			cout << "�޸ĳɹ���";
		}
		return;
	}
	else if (move == 3) {
		string str;
		get_str("�������ַ,����ԭ���ĵ�ַ��ȡ����", str, Address_Check);
		if (str == status.usr->address) {
			cout << "��ȡ����" << endl;
			return;
		}
		else {
			status.usr->address = str;
			write_file(maps, status, "USER_DATA.txt");
			cout << "�޸ĳɹ���";
		}
		return;
	}
}

void show_self(mapfile& maps, System_status& status)
{
	string sep = "********************";
	cout << sep << endl
		<< "�û�����" << status.usr->username << endl
		<< "��ϵ��ʽ��" << status.usr->contact << endl
		<< "��ַ��" << status.usr->address << endl
		<< "Ǯ����" << status.usr->balance << endl
		<< sep << endl;
}

void Sell_Product(mapfile& maps, System_status& status)
{
	Product* prod = new Product;
	get_str("��������Ʒ���ƣ�1-20�ַ�����", prod->name, Product_N_Check);
	prod->price = get_double("��������Ʒ�۸�");
	cout << "��������Ʒ������";
	getline(cin, prod->discription);
	while (prod->discription.length() > 100) {
		cout << "��Ʒ��������Ӧ����100��" << endl;
		cout << "��������Ʒ������";
		prod->discription.clear();
		getline(cin, prod->discription);
	}
	prod->id = ++status.olength;
	prod->date = getTime();
	prod->sid = status.uid;
	prod->status = 1;
	cout << endl << endl << "��ȷ����Ʒ����Ϣ����";
	cout << "��Ʒ���ƣ�" << prod->name << endl << "��Ʒ��" << setiosflags(ios::fixed) << setprecision(2) << prod->price << endl
		<< "��Ʒ������" << prod->discription << endl;
	string str;
	cout << "ȷ���ϼܸ���Ʒ��(y/n)" << endl;
	getline(cin, str);
	while (str != "y" && str != "n" && str != "Y" && str != "N") {
		cout << "������y/n" << endl;
		getline(cin, str);
	}
	if (str == "n" || str == "N")
		return;
	maps.id2Product.insert(pair<int, Product*>(prod->id, prod));
	write_file(maps, status, "PRODUCT_DATA.txt");
	++status.plength;
	return;
}

void Modify_Product(mapfile& maps, System_status& status)
{
	int id;
	int move;
	Product* prod = NULL;
	id = get_num("������Ҫ������Ϣ����ƷID��");
	while (id > status.plength)
		id = get_num("Ѱ�ҵ���Ʒ�����ڡ��Ƿ�Ҫ������һ���˵���������ID�Լ�������Ҫ����������0��");
	if (id == 0)
		return;
	prod = maps.id2Product[id];
	if (prod->sid != status.uid)
		cout << "�����޸ı��˵���Ʒ��" << endl;
	cout << "��ƷID��" << prod->id << endl;
	cout << "��Ʒ���ƣ�" << prod->name << endl;
	cout << "��Ʒ�۸�" << prod->price << endl;
	cout << "��Ʒ������" << prod->discription << endl;
	cout << "��Ʒ״̬��" << prod->sid << endl;
	move = get_num("������Ҫ�޸ĵ���Ʒ��Ϣ�� 1.��Ʒ���� 2. ��Ʒ�۸� 3.��Ʒ���� 4.�¼���Ʒ 5.��Ʒ�����ϼ� �������֣�����");
	cout << endl;
	if (move == 1) {
		prod->name.clear();
		get_str("�������µ���Ʒ���ƣ�1-20�ַ�����", prod->name, Product_N_Check);
		cout << "�ı�ɹ���" << endl;
	}
	else if (move == 2) {
		prod->price = get_double("�������µ���Ʒ�۸�");
		cout << "�ı�ɹ���" << endl;
	}
	else if (move == 3) {
		cout << "��������Ʒ������";
		getline(cin, prod->discription);
		while (prod->discription.length() > 100) {
			cout << "��Ʒ��������Ӧ����100��" << endl;
			cout << "��������Ʒ������";
			prod->discription.clear();
			getline(cin, prod->discription);
		}
		cout << "�ı�ɹ���" << endl;
	}
	else if (move == 4) {
		string str;
		cout << "��������Ʒ������" << prod->name << "��ȷ���¼�:";
		get_str("", str, Product_N_Check);
		if (str == prod->name)
			prod->status = -1;
	}
	else if (move == 5) {
		if (prod->status == -1) {
			prod->status = 1;
			cout << "�ı�ɹ���" << endl;
		}
		if (prod->status == -2)
			cout << "��Ʒ������Ա�¼ܣ�����ϵ����Ա�������ġ�" << endl;
		else
			cout << "��Ʒ���������¼�״̬��" << endl;
	}
	write_file(maps, status, "PRODUCT_DATA.txt");
	return;
}