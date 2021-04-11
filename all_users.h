#pragma once
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4786)
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <stdio.h>
#include <Windows.h>
#include <iomanip>
#include "commons.h"
#include "normal_users.h"
#include "admin.h"
#include "communication.h"

using namespace std;

void Show_MainMenu(mapfile& maps, System_status& status);

void Make_User(mapfile& maps, System_status& status);

void Show_Status(mapfile& maps, System_status status);

void Show_self(mapfile& maps, System_status& status);

void Recharge(mapfile& maps, System_status& status);

void Show_Products(mapfile& maps, System_status& status);

void Login(int mode, mapfile& maps, System_status& status);

void Logout(mapfile& maps, System_status& state);

void SEE_INFO(mapfile& maps, System_status& status);

void Show_Orders(mapfile& maps, System_status& status);

void search_prod_name(mapfile& maps, System_status& status);
