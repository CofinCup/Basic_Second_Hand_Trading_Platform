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

void trade(mapfile& maps, System_status& status);

void MODIFY_INFO(mapfile& maps, System_status& status);

void Sell_Product(mapfile& maps, System_status& status);

void Modify_Product(mapfile& maps, System_status& status);
