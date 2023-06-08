#include<iostream>
using namespace std;
#include"SpeachManager.h"

int main()
{
	srand((unsigned int)time(NULL));
	Manager m;

	int input;
	while (true)
	{
		m.show_menu();
		cout << "请选择：" << endl;
		cin >> input;
		switch (input)
		{
			case 1:	// 开始比赛
				m.startSpeach();
				break;
			case 2: // 显示往届记录
				m.showRecord();
				break;
			case 3: // 清空所有记录 
				m.destoryRecord();
				break;
			case 0: // 退出系统
				m.exit_m();
			default:
				system("cls"); // 清屏
				break;
		}
	}
	return 0;
}
