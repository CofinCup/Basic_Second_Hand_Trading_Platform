#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define Name_Min 2
#define Name_Max 10
#define Address_Min 2
#define Address_Max 30
#define Contact_Len 11
#define Passwd_Min 6
#define Passwd_Max 10
#define Description_Min 2
#define Description_Max 50
#define Title_Min 2
#define Title_Max 15 

#include "commons.h"
using namespace std;

void get_str(string output, string& input, bool check(string))
{
	cout << output;
	getline(cin, input);
	while (!check(input) || input.length() == 0) {
		cout << output;
		input.clear();
		getline(cin, input);
	}
	//cout << endl << "您输入的是：" << input << endl;
}

double get_double(string output)
{
	string str;
	string warning = "数字格式不正确。请重新输入。(不支持科学计数法）";
	bool ok = false;
	double num = 0;
	int suffix = 0;
	cout << output << "（数字不大于100000）" << endl;
	while (!ok) {
		ok = true;
		suffix = 0;
		str.clear();
		getline(cin, str);
		while (str.length() == 0)
			getline(cin, str);
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
				break;
			}
		}
	}
	stringstream ss(str);
	//cout << endl << "调试：输入的字符串为" << str << endl;
	ss >> num;
	if (num >= 100000) {
		cout << "金额过大。"<<endl;
		num = get_double(output);
	}
	return num;
}

int get_num(string output)
{
	string str;
	string warning = "数字格式不正确。请重新输入。\n";
	bool ok = false;
	int num = 0;
	cout << output << endl;
	while (!ok) {
		str.clear();
		ok = true;
		getline(cin, str);
		while (str.length() == 0) {
			str.clear();
			getline(cin, str);
		}
		for (auto ch : str)
			if (ch < '0' || ch>'9') {
				ok = false;
				cout << warning;
				break;
			}
	}
	stringstream ss(str);
	ss >> num;
	return num;
}

void database_ini()
{
	string databasePath = ".\\database";
	if (0 != _access(databasePath.c_str(), 0)) {
		cout << "未找到数据库。正在建立数据库。" << endl;
		_mkdir(databasePath.c_str());
	}
	string commuPath = ".\\database\\communication";
	if (0 != _access(commuPath.c_str(), 0)) {
		_mkdir(commuPath.c_str());
	}
}

void read_file_ini(mapfile& maps, System_status& state)
{
	ifstream ust;
	ust.open(".\\database\\USER_DATA.txt", ios::in);
	ifstream pst;
	pst.open(".\\database\\PRODUCT_DATA.txt", ios::in);
	ifstream ost;
	ost.open(".\\database\\ORDER_DATA.txt", ios::in);
	if (!ust.is_open())
		cout << "缺失了用户数据文件。" << endl;
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
			//cout << usr->id << usr->username << endl << usr->passwd << endl << usr->balance << endl<<usr->address;
			state.ulength++;
		}
		cout << "用户读入结束，共有" << state.ulength << "个。" << endl;
		ust.close();
	}

	if (!pst.is_open())
		cout << "缺失了商品数据文件。" << endl;
	else {
		while (!pst.eof()) {
			string tmp;
			getline(pst, tmp);
			if (tmp.length() == 0)
				break;
			Product* prdt = new Product;
			stringstream ss(tmp);
			ss >> prdt->id >> prdt->name >> prdt->price >> prdt->date >> prdt->sid >> prdt->status;
			getline(ss, prdt->discription);
			maps.id2Product.insert(pair<int, Product*>(prdt->id, prdt));
			//cout << prdt->discription << endl;
			state.plength++;
		}
		cout << "商品读入结束，共有" << state.plength << "个。" << endl;
	}

	if (!ost.is_open())
		cout << "缺少了订单数据文件。" << endl;
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
		cout << "订单数据读入结束，共有" << state.olength << "个。" << endl;
	}

	cout << endl << endl << "二手交易平台 ver 1.02" << endl << "初始化完成。" << endl << endl << endl;
	Sleep(1000);
}


void write_file(mapfile& maps, System_status& status, string where)
{
	string filePath = ".\\database\\";
	ofstream st;
	if (where == "USER_DATA.txt") {
		st.open(filePath+where, ios::out);
		if (!st)
			cout << "无法打开用户数据文件。" << endl;
		else {
			map<int, User*>::iterator it, itEnd;
			it = maps.uid2usr.begin();
			itEnd = maps.uid2usr.end();
			while (it != itEnd) {
				st << setfill('0') << setw(5) << it->second->id;
				st << setfill(' ') << setw(15) << it->second->username << setw(15) << it->second->passwd\
					<< setw(15) << it->second->contact << setw(30) << it->second->address\
					<< setw(10) << setiosflags(ios::fixed) << setprecision(2) << it->second->balance << setw(5) << it->second->nuked << endl;
				++it;
			}
			st.close();
		}
	}
	if (where == "PRODUCT_DATA.txt") {
		st.open(filePath + where, ios::out);
		if (!st)
			cout << where << "不能打开。" << endl;
		else {
			map<int, Product*>::iterator it, itEnd;
			it = maps.id2Product.begin();
			itEnd = maps.id2Product.end();
			while (it != itEnd) {
				st << setfill('0') << setw(5) << it->second->id;
				st << setfill(' ') << setw(15) << it->second->name
					<< setw(10) << setiosflags(ios::fixed) << setprecision(2) << it->second->price\
					<< setw(15) << it->second->date << "   " << setw(5) << setfill('0') << it->second->sid << setfill(' ')
					<< setw(5) << it->second->status << "    " << it->second->discription << endl;
				++it;
			}
			st.close();
		}
	}
	if (where == "ORDER_DATA.txt") {
		st.open(filePath + where, ios::out);
		if (!st)
			cout << where << "不能打开。" << endl;
		else {
			map<int, Order*>::iterator it, itEnd;
			it = maps.id2Order.begin();
			itEnd = maps.id2Order.end();
			while (it != itEnd) {
				st << setfill('0') << setw(5) << it->second->oid;
				st << "\t\t" << it->second->pid << "\t\t" << it->second->price << "\t\t" << it->second->date << "\t\t" << it->second->sid << "\t\t" << it->second->bid;
				++it;
			}
			st.close();
		}
	}
}

bool Name_Check(string name)
{
	if (name.length() < Name_Min || name.length() > Name_Max)
		return false;
	if (name.find(' ') != string::npos)
		return false;
	return true;
}

bool Address_Check(string address)
{
	if (address.length() < Address_Min || address.length() > Address_Max)
		return false;
	if (address.find(' ') != string::npos)
		return false;
	return true;
}

bool Contact_Check(string contact)
{
	if (contact.length() != Contact_Len)
		return false;
	for (auto ch : contact)
		if (ch < '0' || ch>'9')
			return false;
	return true;
}

bool Passwd_Check(string passwd)
{
	bool ret = true;
	if (passwd.length() < Passwd_Min || passwd.length() > Passwd_Max)
		return false;
	for (auto ch : passwd)
		if ((ch < '0' || ch>'9') && (ch < 'A' || ch>'z'))
			return  false;
	return true;
}

bool Description_Check(string descri)
{
	if (descri.length() < Description_Min || descri.length() > Description_Max)
		return false;
	return true;
}

bool Title_Check(string title)
{
	if (title.length() < Title_Min || title.length() > Title_Max)
		return false;
	if (title.find(' ') != string::npos)
		return false;
	return true;
}

bool Product_N_Check(string N)
{
	if (N.length() < 2 || N.length() > 10)
		return false;
	if (N.find(' ') != string::npos)
		return false;
	return true;
}

bool Content_Check(string content)
{
	if (content.length() < 2 || content.length() > 300)
		return false;
	return true;
}

bool Defalt_check(string str)
{
	return true;
}

void Press_Enter_to_Continue(void)
{
	cout << endl << "按回车以继续……";
	char input;
	input = getchar();
	while (input != '\n')
		input = getchar();
}

string getDate()
{
	time_t rawtime;
	struct tm* timeinfo;
	char buffer[80];
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	strftime(buffer, sizeof(buffer), "%Y-%m-%d", timeinfo);
	string str(buffer);
	return str;
}

int subreplace(string& resource_str, string sub_str, string new_str)
{
    int count = 0;
	string::size_type pos = 0;
    while((pos = resource_str.find(sub_str)) != string::npos)
    {
        resource_str.replace(pos, sub_str.length(), new_str);
		++count;
    }
    return count;
}

int subreplace_gapped(string& resource_str, string sub_str, string new_str)
{
    int count = 0;
	string::size_type pos = 0;
    while((pos = resource_str.find(sub_str)) != string::npos)
    {
		++count;
        if (count % 2)
			resource_str.replace(pos, sub_str.length(), new_str);
    }
    return count;
}