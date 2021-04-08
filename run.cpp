#pragma once
#include "run.h"

using namespace std;

void run(void)
{
	mapfile maps;
	map<int, User*> uid2usr;
	map<string, User*> uname2usr;
	map<int, Order*> id2Order;
	map<int, Product*> id2Product;
	map<string, Product*> name2Product;
	maps.uid2usr = uid2usr;
	maps.uname2usr = uname2usr;
	maps.id2Order = id2Order;
	maps.id2Product = id2Product;
	maps.name2Product = name2Product;
	System_status status;
	status.level = -1;
	status.olength = 0;
	status.plength = 0;
	status.ulength = 0;
	status.uid = 0;
	status.usr = NULL;
	read_file_ini(maps, status);
	write_file(maps, status, "USER_DATA.txt");
	while (1) {
		Show_MainMenu(maps, status);
	}
	return;
}