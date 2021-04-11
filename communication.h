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
#include <io.h>
#include <direct.h>
#include <malloc.h>
#include "commons.h"

void enable_communication(void);

void communication_table(mapfile& maps, System_status& status);

void read_communication_file(mapfile& maps, System_status& status);

void write_talk_file(mapfile& maps, System_status& status);

void communicate(mapfile& maps, System_status& status);

void show_communications(mapfile& maps, System_status& status);

void see_communication_content(mapfile& maps, System_status& status);

void follow(mapfile& maps, System_status& status);

void MyMarkdown_translation(string str);

//void cart_ini()