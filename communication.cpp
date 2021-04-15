#include "communication.h"
#include <malloc.h>
using namespace std;
void enable_communication(void)
{
	string folderPath = ".\\database\\communication";
	if (0 != _access(folderPath.c_str(), 0)) {
		_mkdir(folderPath.c_str());
	}

	return;
}

void communication_table(mapfile& maps, System_status& status)
{
	maps.cur_usr_tid2Talk.clear();
	read_communication_file(maps, status);
	while (1) {
		show_communications(maps, status);
		int move = get_num("1.查看邮件 2.写邮件 3.邮件星标/去星标 4.删除邮件 其他：退出信箱");
		if (move == 1)
			see_communication_content(maps, status);
		else if (move == 2)
			communicate(maps, status);
		else if (move == 3)
			Star_talk(maps, status);
		else if (move == 4)
			Delete_talk(maps, status);
		else
			break;
	}
	cout << "正在退出邮箱..." << endl;
	Sleep(1500);
}

void read_communication_file(mapfile& maps, System_status& status)
{
	maps.cur_usr_tid2Talk.clear();
	string path_prefix = ".\\database\\communication\\";
	string path = "";
	path = path_prefix + to_string(status.uid) + ".txt";
	ifstream cst;
	cst.open(path, ios::in);
	int idCount = 0;
	{
		while (!cst.eof()) {
			++idCount;
			string tmp;
			getline(cst, tmp);
			if (tmp.length() == 0)
				break;
			Talk* talk = new Talk;
			talk->tid = idCount;
			stringstream ss(tmp);
			ss >> talk->status >> talk->date >> talk->sid >> talk->title;
			getline(ss, talk->content);
			maps.cur_usr_tid2Talk.insert(pair<int, Talk*>(talk->tid, talk));
			status.tlength++;
		}
	}
	cst.close();
}

void rewrite_talk_file(mapfile& maps, System_status& status)
{
	string path_prefix = ".\\database\\communication\\";
	string path = "";
	path = path_prefix + to_string(status.uid) + ".txt";
	map<int, Talk*>::iterator it, itEnd;
	ofstream write;
	write.open(path);
	it = maps.cur_usr_tid2Talk.begin();
	itEnd = maps.cur_usr_tid2Talk.end();
	while (it != itEnd) {
		write << setw(2) << setfill(' ') << it->second->status << " " << it->second->date << " "
			<< setw(5) << setfill('0') << it->second->sid << " " << it->second->title
			<< it->second->content << endl;
		++it;
	}
}

void communicate(mapfile& maps, System_status& status)
{
	Talk* talk = new Talk;
	talk->sid = status.uid;
	talk->date = getDate();
	int id;
	string path_prefix = ".\\database\\communication\\";
	string path = "";
	id = get_num("请输入收件人ID:");
	if (id > status.ulength) {
		cout << "不存在该用户。" << endl;
		Sleep(1500);
		return;
	}
	else if (id == status.uid) {
		cout << "不能给自己发信息。" << endl;
		Sleep(1500);
		return;
	}
	path = path_prefix + to_string(id) + ".txt";
	get_str("请输入主题(2-15字，无空格）：", talk->title, Title_Check);
	get_str("请输入内容（2-50字）", talk->content, Content_Check);
	cout << "确定要发送吗？(y/n)" << endl;
	string str;
	getline(cin, str);
	while (str != "y" && str != "n" && str != "Y" && str != "N") {
		cout << "请输入y/n" << endl;
		getline(cin, str);
	}
	if (str == "n" || str == "N")
		return;
	if (status.level == 3)
		talk->status = 3;
	else
		talk->status = 1;
	ofstream write;
	write.open(path, ios::app);
	write << setw(2) << setfill(' ') << talk->status << " " << talk->date << " "
		<< setw(5) << setfill('0') << talk->sid << " " << talk->title << " " << talk->content << endl;
	cout << "发送成功。" << endl;
	Sleep(1500);
}

void show_communications(mapfile& maps, System_status& status)
{
	system("cls");
	map<int, Talk*>::iterator it, itEnd;
	int idcount = 0;
	it = maps.cur_usr_tid2Talk.begin();
	itEnd = maps.cur_usr_tid2Talk.end();
	cout << "*******收件箱*******" << endl;
	cout << " ID     状态           日期           发件人            主题" << endl;
	while (it != itEnd) {
		++idcount;
		if (it->second->status == -1) {
			++it;
			continue;
		}
		cout << setw(5) << setfill('0') << idcount << "  ";
		if (it->second->status == 0)
			cout << "【已读】" << "  ";
		else if (it->second->status == 1)
			cout << "\033[32m【未读】\033[0m" << "  ";
		else if (it->second->status == 2)
			cout << "\033[33m【星标】\033[0m" << "  ";
		else if (it->second->status == 3)
			cout << "\033[31m【管理】\033[0m" << "  ";
		cout << it->second->date << "  ";
		if (it->second->sid == 0)
			cout << setw(15) << setfill(' ') << "管理员" << "  ";
		else
			cout << setw(15) << setfill(' ') << maps.uid2usr[it->second->sid]->username << "  ";
		cout << setw(15) << setfill(' ') << it->second->title << endl;
		++it;
	}
}

void see_communication_content(mapfile& maps, System_status& status)
{
	int id;
	id = get_num("请输入要查看的信息ID：");
	map<int, Talk*>::iterator l_it = maps.cur_usr_tid2Talk.find(id);
	if (l_it == maps.cur_usr_tid2Talk.end())
		cout << "该信息不存在或已被删除。" << endl;
	else {
		system("cls");
		if (l_it->second->sid == 0)
			cout << "\033[31m【来自管理员的消息】\033[0m" << endl;
		else
			cout << "发件人：" << maps.uid2usr[l_it->second->sid]->username << endl;
		cout << "主题：" << l_it->second->title << endl;
		cout << "内容：" << MyMarkdown_translation(l_it->second->content) << endl;
		if (l_it->second->status != 2)
			l_it->second->status = 0;
		rewrite_talk_file(maps, status);
	}
	int move = get_num("1.星标邮件 2.快速回复 其他数字：退出详情页面");
	if (move == 1) {
		if (l_it->second->status != 2) {
			l_it->second->status = 2;
			rewrite_talk_file(maps, status);
		}
		else
			cout << "已是星标邮件。" << endl;
		Sleep(1500);
	}
	if (move == 2) {
		Talk* talk = new Talk;
		talk->sid = status.uid;
		talk->date = getDate();
		talk->title = "re:" + l_it->second->title;
		int id = l_it->second->sid;
		string path_prefix = ".\\database\\communication\\";
		string path = "";
		path = path_prefix + to_string(id) + ".txt";
		get_str("请输入内容（2-50字）", talk->content, Content_Check);
		cout << "确定要发送吗？(y/n)" << endl;
		string str;
		getline(cin, str);
		while (str != "y" && str != "n" && str != "Y" && str != "N") {
			cout << "请输入y/n" << endl;
			getline(cin, str);
		}
		if (str == "n" || str == "N")
			return;
		if (status.level == 3)
			talk->status = 3;
		else
			talk->status = 1;
		ofstream write;
		write.open(path, ios::app);
		write << setw(2) << setfill(' ') << talk->status << " " << talk->date << " "
			<< setw(5) << setfill('0') << talk->sid << " " << talk->title << " " << talk->content << endl;
		cout << "发送成功。" << endl;
		Sleep(1500);
	}

}

void Delete_talk(mapfile& maps, System_status& status)
{
	int id;
	id = get_num("请输入要删除的信息ID：");
	map<int, Talk*>::iterator l_it = maps.cur_usr_tid2Talk.find(id);
	if (l_it == maps.cur_usr_tid2Talk.end())
		cout << "该信息不存在或已被删除。" << endl;
	else {
		l_it->second->status = -1;
		cout << "已删除。" << endl;
	}
	rewrite_talk_file(maps, status);
	Sleep(1500);
}

void Star_talk(mapfile& maps, System_status& status)
{
	int id = get_num("请输入要星标或去星标的邮件ID：");
	map<int, Talk*>::iterator l_it = maps.cur_usr_tid2Talk.find(id);
	if (l_it == maps.cur_usr_tid2Talk.end())
		cout << "该信息不存在或已被删除。" << endl;
	else {
		if (l_it->second->status != 2) {
			l_it->second->status = 2;
			cout << "已加星标。" << endl;
		}
		else {
			l_it->second->status = 0;
			cout << "已去星标。" << endl;
		}
		rewrite_talk_file(maps, status);
	}
	Sleep(1500);
}

string MyMarkdown_translation(string str)
{
	string ret;
	bool isRED = false;//1
	bool isYELLOW = false;//2
	bool isGreen = false;//3
	bool isUnder = false;//4
	int status = 0;
	subreplace(str, "\\n", "\n");
	subreplace(str, "[Y]", "\2");
	subreplace(str, "[R]", "\1");
	subreplace(str, "[G]", "\3");
	subreplace(str, "[U]", "\033[0m");
	subreplace(str, "<u>", "\4");
	subreplace(str, "</u>", "\033[0m");
	for (unsigned int i = 0; i < str.length(); ++i) {
		if (str[i] == '\1') {
			if (!isRED)
				ret += "\033[31m";
			else
				ret += "\033[0m";
			isRED = !isRED;
		}
		else if (str[i] == '\2') {
			if (!isYELLOW)
				ret += "\033[33m";
			else
				ret += "\033[0m";
			isYELLOW = !isYELLOW;
		}
		else if (str[i] == '\3') {
			if (!isGreen)
				ret += "\033[32m";
			else
				ret += "\033[0m";
			isGreen = !isGreen;
		}
		else if (str[i] == '\4') {
			if (!isUnder)
				ret += "\033[4m";
			else
				ret += "\033[0m";
			isUnder = !isUnder;
		}
		else 
			ret += str[i];
	}
	ret += "\033[0m";
	return ret;
}

string giveChange(bool isRED, bool isYELLOW, bool isGreen, bool isUnder)
{
	string ret = "\033[0m";
	if (isRED)
		ret += "\033[3m";
	if (isYELLOW)
		ret += "\033[1m";
	if (isGreen)
		ret += "\033[9m";
	if (isUnder)
		ret += "\033[4m";
	return ret;
}
