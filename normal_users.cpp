#pragma once
#include "normal_users.h"

using namespace std;

void trade(mapfile& maps, System_status& status)
{
	int id;
	id = get_num("请输入您购买的商品ID：");
	map<int, Product*>::iterator it;
	it = maps.id2Product.find(id);
	if (it == maps.id2Product.end()) {
		cout << "未找到该商品。请重新输入商品ID：";
		trade(maps, status);
	}
	else {
		double price = it->second->price;
		if (it->second->price > status.usr->balance)
			cout << "商品的价格高于你的余额。" << endl;
		else if (it->second->status != 1) {
			cout << "奇怪，似乎之前有个商品在这里……？" << endl;
		}
		else if (it->second->id == status.uid)
			cout << "不能购买自己的商品。" << endl;
		else {
			status.usr->balance -= it->second->price;
			it->second->status = 0;
			Order* odr = new Order;
			odr->bid = status.uid;
			odr->pid = it->second->id;
			odr->oid = ++status.olength;
			odr->price = it->second->price;
			odr->sid = it->second->sid;
			odr->date = "2021-04-02";
			maps.id2Order.insert(pair<int, Order*>(odr->oid, odr));
			cout << "交易成功！当前余额：" << status.usr->balance << endl;
			cout << "正在返回主菜单……" << endl;
			cout << "\033[31m调试者注意：本部分不确定跳转位置。\033[0m" << endl;
		}
		write_file(maps, status, "USER_DATA");
		write_file(maps, status, "PRODUCT_DATA");
		write_file(maps, status, "ORDER_DATA");
	}
}

void MODIFY_INFO(mapfile& maps, System_status& status)
{
	int move;
	move = get_num("请选择修改的属性(1.用户名 2.联系方式 3.地址)：");
	if (move == 1) {
		cout << "请输入用户名,输入原本的用户名来取消：";
		string str;
		getline(cin, str);
		while (str.length() == 0)
			getline(cin, str);
		get_str("请输入用户名,输入原本的用户名来取消：", str,Name_Check);
		if (str == status.usr->username) {
			cout << "已取消。" << endl;
			cout << "\033[31m调试者注意：本部分不确定跳转位置。\033[0m" << endl;
		}
		else if (str.find(' ')) {
			cout << "用户名中不能含有空格。" << endl;
			cout << "\033[31m调试者注意：本部分不确定跳转位置。\033[0m" << endl;
		}
		else {
			maps.uname2usr.erase(status.usr->username);
			maps.uname2usr.insert(pair<string, User*>(status.usr->username, status.usr));
			status.usr->username = str;
			write_file(maps, status, "USER_DATA.txt");
			cout << "修改成功！";
		}
		return;
	}
}

void show_self(mapfile& maps, System_status& status)
{
	string sep = "********************";
	cout << sep << endl
		<< "用户名：" << status.usr->username << endl
		<< "联系方式：" << status.usr->contact << endl
		<< "地址：" << status.usr->address << endl
		<< "钱包余额：" << status.usr->balance << endl
		<< sep << endl;
}

void Sell_Product(mapfile& maps, System_status& status)
{
	Product* prod = new Product;
	get_str("请输入商品名称（1-20字符）：", prod->name, Product_N_Check);
	prod->price = get_double("请输入商品价格：");
	cout << "请输入商品描述：";
	getline(cin, prod->discription);
	while (prod->discription.length() > 100) {
		cout << "商品的描述不应大于100！" << endl;
		cout << "请输入商品描述：";
		prod->discription.clear();
		getline(cin, prod->discription);
	}
	prod->id = ++status.olength;
	prod->date = "2020-11-11";
	prod->sid = status.uid;
	prod->status = 1;
	cout << endl << endl << "请确认商品的信息无误！";
	cout << "商品名称：" << prod->name << endl << "商品金额：" << setiosflags(ios::fixed) << setprecision(2) << prod->price << endl
		<< "商品描述：" << prod->discription << endl;
	string str;
	cout << "确认上架该商品吗？(y/n)" << endl;
	getline(cin, str);
	while (str != "y" && str != "n" && str != "Y" && str != "N") {
		cout << "请输入y/n!" << endl;
		getline(cin, str);
	}
	if (str == "n" || str == "N")
		return;
	maps.id2Product.insert(pair<int, Product*>(prod->id, prod));
	maps.name2Product.insert(pair<string, Product*>(prod->name, prod));
	write_file(maps, status, "PRODUCT_DATA.txt");
	return;
}

void Modify_Product(mapfile& maps, System_status& status)
{
	int id;
	int move;
	Product* prod = NULL;
	id = get_num("请输入要更改信息的商品ID：");
	while (id > status.plength)
		id = get_num("寻找的商品不存在。是否要返回上一级菜单？（需要请输入0）");
	if (id == 0)
		return;
	prod = maps.id2Product[id];
	move = get_num("请输入要修改的商品信息： 1.商品名称 2. 商品价格 3.商品描述 4.下架商品 5.商品重新上架");
	cout << endl;
	if (move == 1) {
		maps.name2Product.erase(prod->name);
		prod->name.clear();
		get_str("请输入新的商品名称（1-20字符）：", prod->name, Product_N_Check);
		maps.name2Product.insert(pair<string, Product*>(prod->name, prod));
		cout << "改变成功。" << endl;
	}
	else if (move == 2) {
		prod->price = get_double("请输入新的商品价格：");
		cout << "改变成功。" << endl;
	}
	else if (move == 3) {
		cout << "请输入商品描述：";
		getline(cin, prod->discription);
		while (prod->discription.length() > 100) {
			cout << "商品的描述不应大于100！" << endl;
			cout << "请输入商品描述：";
			prod->discription.clear();
			getline(cin, prod->discription);
		}
		cout << "改变成功。" << endl;
	}
	else if (move == 4) {
		string str;
		cout << "请输入商品的名称" << prod->name << "以确认下架:";
		get_str("", str, Product_N_Check);
		if (str == prod->name)
			prod->status = -1;
	}
	else if (move == 5) {
		if (prod->status == -1) {
			prod->status = 1;
			cout << "改变成功。" << endl;
		}
		if (prod->status == -2)
			cout << "商品被管理员下架，请联系管理员进行整改。" << endl;
		else
			cout << "商品不是自行下架状态。" << endl;
	}
	return;
}