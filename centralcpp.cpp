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
		cout << "��ѡ��" << endl;
		cin >> input;
		switch (input)
		{
			case 1:	// ��ʼ����
				m.startSpeach();
				break;
			case 2: // ��ʾ�����¼
				m.showRecord();
				break;
			case 3: // ������м�¼ 
				m.destoryRecord();
				break;
			case 0: // �˳�ϵͳ
				m.exit_m();
			default:
				system("cls"); // ����
				break;
		}
	}
	return 0;
}
