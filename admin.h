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

void show_users(mapfile& maps, System_status& status);

void delete_user(mapfile& maps, System_status status);

void delete_product(mapfile& maps, System_status& status);

void rivive_product(mapfile& maps, System_status& status);

void rivive_user(mapfile& maps, System_status& status);