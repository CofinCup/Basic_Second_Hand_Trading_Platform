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
		int move = get_num("1.�鿴�ʼ� 2.д�ʼ� 3.�˳�����");
		if (move == 1)
			see_communication_content(maps, status);
		else if (move == 2)
			communicate(maps, status);
		else if (move == 3)
			break;
	}
	cout << "�����˳�����..." << endl;
	Sleep(1500);
}

void read_communication_file(mapfile& maps, System_status& status)
{
	string path_prefix = ".\\database\\communication\\";
	string path = "";
	path = path_prefix + to_string(status.uid) + ".txt";
	ifstream cst;
	cst.open(path, ios::in);
	int idCount = 0;
	if (!cst.is_open()) {
		cout << "��������ȱʧ��" << endl;
		Sleep(1500);
	}
	else {
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
			cout << endl << talk->tid << endl;
			status.tlength++;
		}
	}
	cst.close();
}

void write_talk_file(mapfile& maps, System_status& status)
{
	string path_prefix = ".\\database\\communication\\";
	string path = "";
	path = path_prefix + to_string(status.uid) + ".txt";
	map<int, Talk*>::iterator it, itEnd;
	ofstream write;
	write.open(path, ios::app);
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
	id = get_num("�������ռ���ID:");
	if (id > status.ulength) {
		cout << "�����ڸ��û���" << endl;
		Sleep(1500);
		return;
	}
	path = path_prefix + to_string(id) + ".txt";
	get_str("����������(2-15�֣��޿ո񣩣�", talk->title, Title_Check);
	get_str("���������ݣ�2-50�֣�", talk->content, Address_Check);//͵��һ��
	cout << "ȷ��Ҫ������(y/n)" << endl;
	string str;
	getline(cin, str);
	while (str != "y" && str != "n" && str != "Y" && str != "N") {
		cout << "������y/n" << endl;
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
		<< setw(5) << setfill('0') << talk->sid << " " << talk->title <<" "<< talk->content << endl;
	cout << "���ͳɹ���" << endl;
	Sleep(1500);
}

void show_communications(mapfile& maps, System_status& status)
{
	system("cls");
	map<int, Talk*>::iterator it, itEnd;
	int idcount = 0;
	it = maps.cur_usr_tid2Talk.begin();
	itEnd = maps.cur_usr_tid2Talk.end();
	cout << "*******�ռ���*******" << endl;
	cout << " ID    ״̬   ����    ������    ����" << endl;
	while (it != itEnd) {
		++idcount;
		cout << setw(5) << setfill('0') << idcount << "  ";
		if (it->second->status == -1)
			continue;
		else if (it->second->status == 0)
			cout << "���Ѷ���" << "  ";
		else if (it->second->status == 1)
			cout << "\033[32m��δ����\033[0m" << "  ";
		else if (it->second->status == 2)
			cout << "\033[33m���Ǳ꡿\033[0m" << "  ";
		else if (it->second->status == 3)
			cout << "\033[31m������\033[0m" << "  ";
		cout << it->second->date << "  ";
		if (it->second->sid == 0)
			cout << setw(15) << setfill(' ') << "����Ա" << "  ";
		else
			cout << setw(15) << setfill(' ') << maps.uid2usr[it->second->sid]->username << "  ";
		cout << setw(15) << setfill(' ') << it->second->title<<endl;
		++it;
	}
}

void see_communication_content(mapfile& maps, System_status& status)
{
	int id;
	id = get_num("������Ҫ�鿴����ϢID��");
	map<int, Talk*>::iterator l_it = maps.cur_usr_tid2Talk.find(id);
	if (l_it == maps.cur_usr_tid2Talk.end())
		cout << "����Ϣ�����ڻ��ѱ�ɾ����" << endl;
	else {
		system("cls");
		if (l_it->second->sid == 0)
			cout << "\033[31m�����Թ���Ա����Ϣ��\033[0m" << endl;
		else
			cout << "�����ˣ�" << maps.uid2usr[l_it->second->sid]->username << endl;
		cout << "���⣺" << l_it->second->title << endl;
		cout << "���ݣ�" << l_it->second->content << endl;
		l_it->second->status = 0;
	}
	Press_Enter_to_Continue();
}

void follow(mapfile& maps, System_status& status)
{
}

void MyMarkdown_translation(string str)
{
}
