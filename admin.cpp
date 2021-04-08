#pragma once

#include "admin.h"

using namespace std;
void show_users(mapfile& maps, System_status& status)
{
	map<int, User*>::iterator it, itEnd;
	it = maps.uid2usr.begin();
	itEnd = maps.uid2usr.end();
	cout << "用户ID" << setfill(' ') << setw(15) << "用户名" << setw(15) << "联系方式" << setw(30)
		<< "地址" << setw(10) << "余额" << setw(3) << "    账户状态" << endl;
	while (it != itEnd) {
		cout << " " << setfill('0') << setw(5) << it->second->id;
		cout << setfill(' ') << setw(15) << it->second->username \
			<< setw(15) << it->second->contact << setw(30) << it->second->address\
			<< setw(10) << setiosflags(ios::fixed) << setprecision(2) \
			<< it->second->balance;
		if (it->second->nuked == true)
			cout << "    \033[31m封禁中\033[0m" << endl;
		else
			cout << "    正常" << endl;
		++it;
	}

	Press_Enter_to_Continue();
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
		cout << "该商品不是在售状态。" << endl;
	else {
		l_it->second->status = -2;
		write_file(maps, status, "PRODUCT_DATA.txt");
		cout << "成功下架该商品。" << endl;
	}
	Press_Enter_to_Continue();
}

void rivive_product(mapfile& maps, System_status& status)
{
	int id;
	id = get_num("请输入要恢复的商品ID：");
	map<int, Product*>::iterator l_it;
	l_it = maps.id2Product.find(id);
	if (l_it == maps.id2Product.end())
		cout << "该商品不存在。" << endl;
	else if (l_it->second->status != -2)
		cout << "该商品不是被管理员下架状态。" << endl;
	else {
		l_it->second->status = -2;
		write_file(maps, status, "PRODUCT_DATA.txt");
		cout << "成功恢复该商品。" << endl;
	}
	Press_Enter_to_Continue();
}