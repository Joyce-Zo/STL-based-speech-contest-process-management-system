#pragma once
#include<iostream>
using namespace std;
#include<vector>
#include<map>
#include<string>
#include<algorithm>
#include<Windows.h>
#include<deque>
#include<numeric>
#include<functional>
#include<fstream>
#include<ctime>


class speaker  // ѡ����
{
public:
	string s_name;
	double s_score[2]; // 2�ֵ÷֣�doubleʹ�������ͬ�ֵ����
};

class Manager // ������
{
public:
	// ���캯��
	Manager();
	// ��������
	~Manager();

	// �˵�����
	void show_menu();

	// �˳�����
	void exit_m();

	// ��ʼ������

	// ��ʼ������
	void initSpeaker();

	// ����ѡ��
	void createSpeaker();

	// ��ʼ����
	void startSpeach();

	// ��ǩ
	void DrawSpeach();

	// ���б���
	void Speach();
	
	// ��ʾ�������
	void showSpeach();

	// �������ݵ��ļ�
	void saveSpeach();

	// ��ȡ��¼����
	void loadSpeach();

	// �鿴��¼����
	void showRecord();

	// ����ļ�
	void destoryRecord();

	// ��������
	vector<int> v1; // ��ŵ�1�ֱ�����ѡ�֣���12��
	vector<int> v2; // ��ŵ�2�ֱ�����ѡ�֣���6��
	vector<int> v3; // ��ű���ʤ����ѡ�֣���3��

	map<int, speaker> m_speaker; // ��ű���Լ���Ӧ��ѡ�� ����
	int index; // ��¼����������

	// ��¼�ļ�Ϊ�����ı�־
	bool fileISempty;

	// ��������¼������
	map<int, vector<string>>s_Load;

};

