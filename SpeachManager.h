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


class speaker  // 选手类
{
public:
	string s_name;
	double s_score[2]; // 2轮得分，double使不会出现同分的情况
};

class Manager // 管理类
{
public:
	// 构造函数
	Manager();
	// 析构函数
	~Manager();

	// 菜单功能
	void show_menu();

	// 退出功能
	void exit_m();

	// 开始比赛：

	// 初始化属性
	void initSpeaker();

	// 创建选手
	void createSpeaker();

	// 开始比赛
	void startSpeach();

	// 抽签
	void DrawSpeach();

	// 进行比赛
	void Speach();
	
	// 显示比赛结果
	void showSpeach();

	// 保存数据到文件
	void saveSpeach();

	// 读取记录分数
	void loadSpeach();

	// 查看记录分数
	void showRecord();

	// 清空文件
	void destoryRecord();

	// 各种属性
	vector<int> v1; // 存放第1轮比赛的选手，共12人
	vector<int> v2; // 存放第2轮比赛的选手，共6人
	vector<int> v3; // 存放比赛胜出的选手，共3人

	map<int, speaker> m_speaker; // 存放编号以及对应的选手 容器
	int index; // 记录比赛的轮数

	// 记录文件为空与否的标志
	bool fileISempty;

	// 存放往届记录的容器
	map<int, vector<string>>s_Load;

};

