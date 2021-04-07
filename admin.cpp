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
		cout << "用户ID\t用户名\t联系方式\t地址\t钱包余额" << endl;
		cout.setf(ios::fixed);
		cout << setw(5) << setfill('0') << it->second->id << "\t";
		cout << it->second->username << "\t" << it->second->contact << "\t"\
			<< it->second->address << "\t\t" << fixed << setprecision(2) << it->second->balance << endl;
		it++;
	}
	cout << "\033[31m调试者注意：本部分不确定跳转位置。\033[0m" << endl;
	//Show_MainMenu(maps, status);
}


void delete_user(mapfile& maps, System_status status)
{
	int id;
	id = get_num("请输入要删除的用户ID：");
	map<int, User*>::iterator l_it;
	l_it = maps.uid2usr.find(id);
	if (l_it == maps.uid2usr.end())
		cout << "该用户不存在。" << endl;
	else if (l_it->second->nuked == 1)
		cout << "该用户已被删除。" << endl;
	else {
		l_it->second->nuked = 1;
		write_file(maps, status, "USER_DATA.txt");
		cout << "成功删除该用户。" << endl;
	}
	cout << "\033[31m调试者注意：本部分不确定跳转位置。\033[0m" << endl;
	//Show_MainMenu(maps, status);
}

void delete_product(mapfile& maps, System_status& status)
{
	int id;
	id = get_num("请输入要下架的商品ID：");
	map<int, Product*>::iterator l_it;
	l_it = maps.id2Product.find(id);
	if (l_it == maps.id2Product.end())
		cout << "该商品不存在。" << endl;
	else if (l_it->second->status != 1)
		cout << "该商品已被下架。" << endl;
	else {
		l_it->second->status = -2;
		write_file(maps, status, "PRODUCT_DATA.txt");
		cout << "成功下架该商品。" << endl;
	}
	cout << "\033[31m调试者注意：本部分不确定跳转位置。\033[0m" << endl;
	//Show_MainMenu(maps, status);
}