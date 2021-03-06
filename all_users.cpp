#pragma once

//all catering to all users
using namespace std;
#include "all_users.h"

void Show_MainMenu(mapfile& maps, System_status& status)
{
	system("cls");
	//Show_Status(maps, status);
	string large_sep("================================================================================");
	string short_sep("**********");
	int move = 0;
	if (status.level == -1)
	{
		cout << large_sep << endl;
		cout << "1.用户登录 2.用户注册 3.管理员登录 4.退出程序" << endl;
		cout << large_sep << endl << endl << endl;
		move = get_num("输入操作：");
		if (move == 1)
			Login(1, maps, status);
		if (move == 2)
			Make_User(maps, status);
		if (move == 3)
			Login(3, maps, status);
		if (move == 4) {
			cout << "感谢使用，我们下次再见。" << endl;
			exit(0);
		}
	}
	else if (status.level == 0) {//个人主菜单
		cout << large_sep << endl;
		cout << "1.注销用户 2.我是买家 3.我是卖家 4.个人信息管理 5.我的信箱" << endl;
		cout << large_sep << endl;
		if (status.usr->nuked == true) {
			cout << "\033[31m用户被ban，请联系管理员。正在登出。\033[0m" << endl;
			Logout(maps, status);
			return;
		}
		move = get_num("输入操作：");
		if (move == 1) {
			Logout(maps, status);
		}
		else if (move == 2)
			status.level = 1;
		else if (move == 3)
			status.level = 2;
		else if (move == 4) {
			while (1) {
				system("cls");
				cout << large_sep;
				Show_self(maps, status);
				cout << "1.返回用户主界面 2.修改信息 3.充值" << endl;
				cout << large_sep << endl;
				int input;
				input = get_num("请输入操作：");
				if (input == 1)
					return;
				else if (input == 2)
					MODIFY_INFO(maps, status);
				else if (input == 3)
					Recharge(maps, status);
				else
					cout << "不合法的操作数。" << endl;
			}
		}
		else if (move == 5) {
			system("cls");
			communication_table(maps, status);
		}
	}
	else if (status.level == 1) {
		cout << large_sep << endl;
		cout << "1.查看商品列表 2.购买商品 3.搜索商品 4.查看历史订单 5.查看商品详细信息 6.返回用户主界面" << endl;
		cout << large_sep << endl;
		move = get_num("输入操作：");
		switch (move)
		{
		case 1: {
			Show_Products(maps, status);
		}break;
		case 2: {
			trade(maps, status);
		}break;
		case 3: {
			search_prod_name(maps, status);
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
			cout << "不合法的操作数。" << endl;
			break;
		}
	}
	else if (status.level == 2) {
		cout << large_sep << endl;
		cout << "1.发布商品 2.查看发布商品 3.修改商品信息/下架商品 4.查看历史订单 5.返回用户主界面" << endl;
		cout << large_sep << endl;
		move = get_num("输入操作：");
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
			cout << "不合法的操作数。" << endl;
			break;
		}
	}
	else if (status.level == 3) {
		cout << large_sep << endl;
		cout << "1.查看所有商品 2.搜索商品 3.查看所有订单 4.查看所有用户 5.删除用户 6.下架商品 7.刷新所有数据文件 8.我的信箱 9.注销" << endl;
		cout << large_sep << endl;
		move = get_num("输入操作：");
		switch (move) {
		case 1:
			Show_Products(maps, status);
			break;
		case 2:
			SEE_INFO(maps, status);
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
			write_file(maps, status, "USER_DATA.txt");
			write_file(maps, status, "PRODUCT_DATA.txt");
			write_file(maps, status, "ORDER_DATA.txt");
			break;
		case 8:
			system("cls");
			communication_table(maps, status);
			break;
		case 9:
			Logout(maps, status);
			break;
		default:
			cout << "不合法的操作数。" << endl;
			break;
		}
	}
}

void Make_User(mapfile& maps, System_status& status)
{
	User* user = new User;
	user->id = ++status.ulength;
	get_str("请输入用户名(2-10字符，不可输入空格)：", user->username, Name_Check);
	while (maps.uname2usr.find(user->username) != maps.uname2usr.end()) {
		if (maps.uname2usr[user->username]->nuked == true)
			get_str("用户名已存在，请重新输入用户名(2-10字符，不可输入空格)：", user->username, Name_Check);
		else
			continue;
	}
	get_str("请输入密码(6-10字符，不可输入空格)：", user->passwd, Passwd_Check);
	get_str("请输入电话号码(11位，不可输入空格)：", user->contact, Contact_Check);
	get_str("请输入地址(2-30字符，不可输入空格)：", user->address, Address_Check);
	user->balance = 0;
	user->nuked = false;
	cout << "注册成功！请返回主界面重新登录。";
	Sleep(1500);
	maps.uid2usr.insert(pair<int, User*>(user->id, user));
	maps.uname2usr.insert(pair<string, User*>(user->username, user));
	//show_users(maps, status);
	write_file(maps, status, "USER_DATA.txt");
	//Show_MainMenu(maps, status);
}

void Show_Status(mapfile& maps, System_status status)
{
	cout << endl << "当前等级为：" << status.level << "当前用户ID为：" << status.uid << endl;
	Press_Enter_to_Continue();
}

void Show_self(mapfile& maps, System_status& status)
{
	if (status.level == 3) {
		cout << endl << "当前权限等级：3" << endl << "身份：管理员" << endl << "今天也要好好工作！" << endl;
	}
	else {
		cout << endl << "用户名：" << status.usr->username << endl
			<< "联系方式：" << status.usr->contact << endl
			<< "地址：" << status.usr->address << endl
			<< "钱包余额：" << status.usr->balance << endl;
	}
}
void Recharge(mapfile& maps, System_status& status)
{
	double quota;
	quota = get_double("请输入充值额度：");
	if (status.usr->balance + quota > 100000) {
		cout << "不能太贪心！" << endl;
		return;
	}
	status.usr->balance += quota;
	cout << "充值成功。现在的额度为：" << status.usr->balance << endl;
	write_file(maps, status, "USER_DATA.txt");
	Press_Enter_to_Continue();
}
void Show_Products(mapfile& maps, System_status& status)
{
	map<int, Product*>::iterator it, itEnd;
	it = maps.id2Product.begin();
	itEnd = maps.id2Product.end();
	cout << "ID\t  名称\t价格\t上架时间\t卖家ID\t  商品状态";
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
		cout << setw(5) << setfill('0') << it->second->id;
		cout << setw(10) << setfill(' ') << it->second->name << "\t" << fixed << setprecision(2) << it->second->price << "\t"\
			<< it->second->date << "\t" << fixed << setw(5) << setfill('0') << it->second->sid;
		if (it->second->status == 1)
			cout << "    \033[32m销售中\033[0m" << endl;
		else if (it->second->status == 0)
			cout << "    已售出" << endl;
		else if (it->second->status == -1)
			cout << "    \033[33m已下架\033[0m" << endl;
		else if (it->second->status == -2)
			cout << "    \033[31m被管理员下架\033[0m" << endl;
		it++;
	}
	Press_Enter_to_Continue();
}

void Login(int mode, mapfile& maps, System_status& status)
{
	if (mode == 1) { //normal user login
		string uname;
		get_str("请输入用户名，输入0以返回：", uname, Defalt_check);
		if (uname == "0") {
			cout << "正在返回主菜单。" << endl;
			return;
		}
		map<string, User*>::iterator l_it;
		l_it = maps.uname2usr.find(uname);
		if (l_it == maps.uname2usr.end())
			cout << "输入了错误的用户名。" << endl;
		else {
			string passwd = l_it->second->passwd;
			string input_passwd;
			get_str("请输入密码：", input_passwd, Defalt_check);
			if (input_passwd == passwd) {
				cout << "登录成功！" << endl;
				status.level = 0;
				status.uid = l_it->second->id;
				status.usr = l_it->second;
			}
			else {
				cout << "密码错误！";
			}
		}
	}
	if (mode == 3) {
		string uname;
		string passwd;
		get_str("请输入管理员名称：", uname, Defalt_check);
		get_str("请输入管理员密码：", passwd, Defalt_check);
		if (uname == "admin" && passwd == "123456") {
			cout << "登录成功！" << endl;
			status.level = 3;
			status.uid = 0;
		}
		else {
			cout << "登录失败。" << endl;
		}
	}
	cout << "正在返回主菜单……" << endl;
	Sleep(1500);
}

void Logout(mapfile& maps, System_status& state)
{
	state.level = -1;
	state.uid = 0;
	state.usr = NULL;
	cout << "登出成功" << endl;
	cout << "正在返回主菜单……" << endl;
	Sleep(1500);
}

void SEE_INFO(mapfile& maps, System_status& status)
{
	int id;
	id = get_num("请输入想要查找的商品ID：");
	map<int, Product*>::iterator it;
	it = maps.id2Product.find(id);
	if (it == maps.id2Product.end()) {
		cout << "未找到该商品。";
	}
	else if (it->second->status != 1 && status.level != 3) {
		cout << "奇怪，似乎之前有个商品在这里……";
	}
	else {
		cout << "商品ID：" << it->second->id << endl;
		cout << "商品名称：" << it->second->name << endl;
		cout << "商品价格：" << it->second->price << endl;
		cout << "商品描述：" << it->second->discription << endl;
		cout << "销售者ID：" << it->second->sid << endl;
	}
	Press_Enter_to_Continue();
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
				cout << "【购买】" << " " << setw(5) << setfill('0') << it->second->pid
				<< " " << it->second->price << " " << it->second->date << " "
				<< setw(5) << setfill('0') << it->second->sid << " " << setw(5)
				<< setfill('0') << it->second->bid;
			else if (it->second->sid == status.uid)
				cout << "【卖出】" << " " << setw(5) << setfill('0') << it->second->pid
				<< " " << it->second->price << " " << it->second->date << " "
				<< setw(5) << setfill('0') << it->second->sid << " " << setw(5)
				<< setfill('0') << it->second->bid;
			++it;
		}
		break;
	case 3:
		it = maps.id2Order.begin();
		itEnd = maps.id2Order.end();
		while (it != itEnd) {
			cout << "ID\t商品ID\t交易金额\t交易时间\t买家ID\t卖家ID" << endl;
			cout << setw(5) << setfill('0') << it->second->oid;
			cout << "\t" << setw(5) << setfill('0') << it->second->pid << "\t";
			cout << fixed << setprecision(2) << it->second->price << "\t";
			cout << it->second->date << "\t" << setw(5) << setfill('0') << it->second->bid;
			cout << setw(5) << setfill('0') << it->second->sid << endl;
			it++;
		}
		break;
	}
	Press_Enter_to_Continue();
}

void search_prod_name(mapfile& maps, System_status& status)
{
	string str;
	get_str("请输入想要查找的商品名称：", str, Product_N_Check);
	map<int, Product*>::iterator it;
	map<int, Product*>::iterator itEnd;
	it = maps.id2Product.begin();
	itEnd = maps.id2Product.end();
	cout << "ID\t  名称\t价格\t上架时间\t卖家ID\t  商品状态";
	while (it != itEnd) {
		if (it->second->name.find(str) != string::npos) {
			if (it->second->status != 1 && status.level != 3)
				continue;
			else {
				cout << endl;
				cout.setf(ios::fixed);
				cout << setw(5) << setfill('0') << it->second->id;
				cout << setw(10) << setfill(' ') << it->second->name << "\t" << fixed << setprecision(2) << it->second->price << "\t"\
					<< it->second->date << "\t" << fixed << setw(5) << setfill('0') << it->second->sid;
				if (it->second->status == 1)
					cout << "    \033[32m销售中\033[0m" << endl;
				else if (it->second->status == 0)
					cout << "    已售出" << endl;
				else if (it->second->status == -1)
					cout << "    \033[33m已下架\033[0m" << endl;
				else if (it->second->status == -2)
					cout << "    \033[31m被管理员下架\033[0m" << endl;
			}
		}

		it++;
	}
	Press_Enter_to_Continue();
}

