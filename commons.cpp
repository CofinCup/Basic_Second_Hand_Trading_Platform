#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "commons.h"
using namespace std;

void get_str(string output, string& input, string warning, unsigned int min_length, unsigned int max_length)
{
	cout << output << endl;
	cin >> input;
	bool findSpace = false;
	while (input.length() < min_length || input.length() > max_length || input.find(' ')!=string::npos) {
		cout << warning << endl;
		input.clear();
		cin >> input;
	}
	cout << endl << "您输入的是：" << input << endl;
	cout <<  "输入成功。" << endl;
}

double get_double(string output)
{
	string str;
	string warning =  "数字格式不正确。请重新输入。(不支持科学计数法）";
	bool ok = false;
	double num = 0;
	int suffix = 0;
	cout << output << endl;
	while (!ok) {
		ok = true;
		suffix = 0;
		cin >> str;
		bool foundDot = false;
		for (auto ch : str) {
			if (ch == '.' && !foundDot)
				foundDot = true;
			else if (ch == '.' && foundDot) {
				cout << warning;
				ok = false;
			}
			else if (ch < '0' || ch>'9') {
				cout << warning;
				ok = false;
			}
			else if (foundDot)
				++suffix;
			if (suffix > 2) {
				cout << warning << endl;
				ok = false;
			}
		}
		
		str.erase();
	}
	stringstream ss(str);
	ss >> num;
	return num;
}

int get_num(string output)
{
	string str;
	string warning = "数字格式不正确。请重新输入。";
	bool ok = false;
	int num = 0;
	cout << output << endl;
	while (!ok) {
		ok = true;
		cin >> str;
		bool foundDot = false;
		for (auto ch : str) {
			if (ch < '0' || ch>'9') {
				cout << warning;
				ok = false;
			}
		}
	}
	stringstream ss(str);
	ss >> num;
	return num;
}

void read_file_ini(mapfile& maps, System_status& state)
{
	ifstream ust;
	ust.open("USER_DATA.txt", ios::in);
	ifstream pst;
	pst.open("PRODUCT_DATA.txt", ios::in);
	ifstream ost;
	ost.open("ORDER_DATA.txt", ios::in);
	if (!ust.is_open())
		cout <<  "缺失了用户数据文件。" << endl;
	else {
		while (!ust.eof()) {
			string tmp;
			getline(ust, tmp);
			if (tmp.length() == 0)
				break;
			User* usr = new User;
			stringstream ss(tmp);
			ss >> usr->id >> usr->username >> usr->passwd >> usr->contact >> \
				usr->address >> usr->balance >> usr->nuked;
			maps.uid2usr.insert(pair<int, User*>(usr->id, usr));
			maps.uname2usr.insert(pair<string, User*>(usr->username, usr));
			cout << usr->id << usr->username << endl << usr->passwd << endl << usr->balance << endl<<usr->address;
			state.ulength++;
		}
		cout <<  "用户读入结束，共有" << state.ulength <<  "个。" << endl;
		ust.close();
	}

	if (!pst.is_open())
		cout <<  "缺失了商品数据文件。" << endl;
	else {
		while (!pst.eof()) {
			string tmp;
			getline(pst, tmp);
			Product* prdt = new Product;
			stringstream ss(tmp);
			ss >> prdt->id >> prdt->name>> prdt->price  >> prdt->date >> prdt->sid>>prdt->status;
			getline(ss, prdt->discription);
			maps.id2Product.insert(pair<int, Product*>(prdt->id, prdt));
			maps.name2Product.insert(pair<string, Product*>(prdt->name, prdt));
			cout << prdt->discription << endl;
			state.plength++;
		}
		cout <<  "商品读入结束，共有" << state.plength <<  "个。" << endl;
	}

	if (!ost.is_open())
		cout <<  "缺少了订单数据文件。" << endl;
	else {
		while (!ost.eof()) {
			string tmp;
			getline(ost, tmp);
			if (tmp.empty())
				continue;
			Order* odr = new Order;
			stringstream ss(tmp);
			ss >> odr->oid >> odr->pid >> odr->price >> odr->date >> odr->sid >> odr->bid;
			state.olength++;
		}
		cout <<  "订单数据读入结束，共有" << state.olength <<  "个。" << endl;
	}
}

void write_file(mapfile& maps, System_status& status, string where)
{
	ofstream st;
	if (where == "USER_DATA.txt") {
		st.open(where, ios::out);
		if (!st)
			cout << "不能打开。" << endl;
		else {
			map<int, User*>::iterator it, itEnd;
			it = maps.uid2usr.begin();
			itEnd = maps.uid2usr.end();
			while (it != itEnd) {
				st << setfill('0') << setw(5) << it->second->id<<" ";
				st << it->second->username << " " << it->second->passwd\
					<< " " << it->second->contact << " " << it->second->address\
					<< " " << setiosflags(ios::fixed) << setprecision(2)<< it->second->balance << " " << it->second->nuked << endl;
				++it;
			}
			st.close();
		}
	}
	if (where == "PRODUCT_DATA.txt") {
		st.open(where, ios::out);
		if (!st)
			cout << where << "不能打开。" << endl;
		else {
			map<int, Product*>::iterator it, itEnd;
			it = maps.id2Product.begin();
			itEnd = maps.id2Product.end();
			while (it != itEnd) {
				st << setfill('0') << setw(5) << it->second->id;
				st << " " << setiosflags(ios::fixed) << setprecision(2)<< it->second->price << " " << it->second->name << " " << it->second->date\
					<< " " << it->second->status << " " << it->second->discription;
				++it;
			}
			st.close();
		}
	}
	if (where == "ORDER_DATA.txt") {
		st.open(where, ios::out);
		if (!st)
			cout << where << "不能打开。" << endl;
		else {
			map<int, Order*>::iterator it, itEnd;
			it = maps.id2Order.begin();
			itEnd = maps.id2Order.end();
			while (it != itEnd) {
				st << setfill('0') << setw(5) << it->second->oid;
				st << " " << it->second->pid << " " << it->second->price << " " << it->second->date << " " << it->second->sid << " " << it->second->bid;
				++it;
			}
			st.close();
		}
	}
}

