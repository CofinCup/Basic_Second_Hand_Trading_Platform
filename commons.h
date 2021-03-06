#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <stdio.h>
#include <Windows.h>
#include <iomanip>
#include <time.h>
#include <direct.h>
#include <io.h>

using namespace std;
struct User {
	int id;
	string username;//need to check when making new
	string passwd;//must follow a safety scale
	string contact;
	string address;//hard(?): saving chinese characters
	double balance;
	bool nuked;
};

struct Order {
	int oid;
	int sid;
	int bid;
	int pid;
	double price;
	string date;
};

struct Product {
	int id;
	int sid;
	double price;
	string name;
	int status;//-2，-1，0，1分别为被管理员下架、被卖家下架、已售出、在售
	string date;
	string discription;
};

struct Talk {
	int tid;
	int sid;//sender id;
	int status;
	string date;
	string title;
	string content;
};

struct mapfile
{
	map<int, User*> uid2usr;
	map<string, User*> uname2usr;
	map<int, Product*> id2Product;
	map<int, Order*> id2Order;
	map<int, Talk*> cur_usr_tid2Talk;
};

struct System_status {
	int level;//权限强度，-1，0，1，2,3排列表示未登录用户，身份不确定用户，买家，卖家，管理员
	int uid;//当前用户的id
	int ulength;//当前用户表长度
	int plength;//当前商品数量
	int olength;//当前订单数量
	int tlength;//邮件数量
	User* usr;
};


void get_str(string output, string& input, bool check(string));

double get_double(string output);

int get_num(string output);

void database_ini();

void read_file_ini(mapfile& maps, System_status& state);

void write_file(mapfile& maps, System_status& status, string where);

bool Name_Check(string name);

bool Address_Check(string address);

bool Contact_Check(string contact);

bool Passwd_Check(string passwd);

bool Description_Check(string descri);

bool Title_Check(string title);

bool Product_N_Check(string N);

bool Content_Check(string content);

bool Defalt_check(string str);

void Press_Enter_to_Continue(void);

string getDate();

int subreplace(string& resource_str, string sub_str, string new_str);

int subreplace_gapped(string& resource_str, string sub_str, string new_str);
