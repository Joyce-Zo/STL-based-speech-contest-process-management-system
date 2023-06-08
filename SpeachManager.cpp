#include"SpeachManager.h"

// ���캯��
Manager::Manager()
{
	this->initSpeaker(); // ��ʼ��
	this->createSpeaker(); // ����ѡ��
	this->loadSpeach(); // ��ȡ�����¼
}
// ��������
Manager::~Manager()
{
	;
}

// �˵�����
void Manager::show_menu()
{
	cout << "******************************************" << endl;
	cout << "********** ��ӭʹ���ݽ�����ϵͳ **********" << endl;
	cout << "**********    1����ʼ�ݽ�����   **********" << endl;
	cout << "**********    2���鿴�����¼   **********" << endl;
	cout << "**********    3����ձ�����¼   **********" << endl;
	cout << "**********    0���˳�����ϵͳ   **********" << endl;
	cout << "******************************************" << endl;
}

// �˳�����
void Manager::exit_m()
{
	cout << "��ӭ�´�ʹ�ã�" << endl;
	exit(0);
}

// ��ʼ������
void Manager::initSpeaker()
{
	// ȫ����ղ���1
	this->v1.clear();
	this->v2.clear();
	this->v3.clear();
	this->m_speaker.clear();
	this->index = 1;

	this->s_Load.clear(); // ��ʼ����¼����
}

// ����ѡ��
void Manager::createSpeaker()
{
	string nameSeed = "ABCDEFJHIJKL";
	for (int i = 0; i < nameSeed.size(); i++)
	{
		string name = "ѡ��";
		name += nameSeed[i];

		speaker sp; // ����һλѡ��
		sp.s_name = name; // ѡ�����ֳ�ʼ��
		for (int j = 0; j < 2; j++)
		{
			sp.s_score[j] = 0; // ѡ�ַ�����ʼ��
		}
		// Ϊѡ�ֱ��
		this->v1.push_back(i + 10001);
		// ��ѡ�ֱ���Լ���Ӧѡ�ֲ��뵽map�����У����10001-100012
		this->m_speaker.insert(make_pair(i + 10001, sp));
	}
}

// ��ǩ
void Manager::DrawSpeach()
{
	cout << "------------��" << this->index << "�ֳ�ǩ���ڽ���-------------" << endl;
	cout << "------------------------------------------" << endl;
	Sleep(500);
	cout << "��ǩ���ݽ�˳�����£�" << endl;
	if (this->index == 1)
	{
		random_shuffle(v1.begin(), v1.end());
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	else
	{
		random_shuffle(v2.begin(), v2.end());
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	cout << "------------------------------------------" << endl;
	system("pause");
	cout << endl;
}
// ��ʼ����
void Manager::startSpeach()
{
	// ��һ�ֱ���
	//	1����ǩ
	this->DrawSpeach();
	//	2������
	this->Speach();
	//	3����ʾ�������
	this->showSpeach();
	
	// �ڶ��ֱ���
	this->index++;
	//	1����ǩ
	this->DrawSpeach();
	//	2������
	this->Speach();
	//	3����ʾ�������
	this->showSpeach();
	//  4���������ǰ����
	this->saveSpeach();

	this->initSpeaker(); // ��ʼ��
	this->createSpeaker(); // ����ѡ��
	this->loadSpeach(); // ��ȡ�����¼

	cout << "���������ʽ������" << endl;
	Sleep(500);
	system("pause");
	system("cls");
}

void Manager::Speach()
{
	cout << "------------" << "��" << this->index << "�������ʽ��ʼ" << "-------------" << endl;
	multimap<double, int, greater<double>> Group; // �洢������ѡ�ֱ�ţ��������У����������棬��ֹ����ѭ��������ͬ������

	//	1��������������Ա������v_person�������ݲ�ͬ��������Ӧ��������v_person
	vector<int>v_person;
	if (this->index == 1)
	{
		v_person = v1;
	}
	else
	{
		v_person = v2;
	}

	//	2�����������ļ���num������v_person������ѡ�֣�����deque������ÿ��ѡ�ֽ���10����ί�Ĵ��
	//	   �����ȥ����߷ֺ���ͷ֣�����ȡ�ֺܷ�ƽ����
	int num = 0;
	for (vector<int>::iterator it = v_person.begin(); it != v_person.end(); it++)
	{
		// ��ί���
		deque<double>d;
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600) / 10.f; // �����600-1000������10����1λС������60.0-100.0
			d.push_back(score); // ���������뵽d��
		}
		sort(d.begin(), d.end(),greater<double>()); // ���� ����
		d.pop_back();	// ȥ����ͷ�
		d.pop_front();	// ȥ����߷�

		double sum = accumulate(d.begin(), d.end(),0); // ��ȡ�ܷ�
		double avg = sum / d.size();	// ��ȡ��ֵ
		this->m_speaker[*it].s_score[this->index - 1] = avg; // �����ִ��뵽ѡ�ֶ�Ӧ������score��

		//	3������С����������ƽ���ֺͱ�Ŵ������飬ÿ6��ѡ��Ϊһ�飬�����6��ѡ�ֵ����������ɼ�
		Group.insert(make_pair(avg, *it)); // ��ÿλѡ�ֵľ��ֺͱ�Ų��뵽Group������
		num++;	// ���������++
		if (num % 6 == 0) // ÿ����6���ˣ�����һ�α����������ʱ������Ѿ�����
		{
			cout <<"��" << num / 6 << "��ѡ�ֱ������Σ�" << endl;
			for (multimap<double, int, greater<double>>::iterator it = Group.begin(); it != Group.end(); it++)
			{
				cout << "��ţ�" << it->second << "\t������"
					<< this->m_speaker[it->second].s_name << "\tƽ���֣�"
					<< this->m_speaker[it->second].s_score[this->index - 1] << endl;
			}

			//	4��ȡ��ǰ3��������ǵ�1����������ǰ�������뵽v2����������ǵ�2������������뵽v3�У�ÿ6�����һ��
			int count = 0; // ʹ���ǿ���ȡ��ǰ������0��1��2
			for (multimap<double, int, greater<double>>::iterator it = Group.begin(); it != Group.end() && count < 3; it++, count++)
			{
				if (this->index == 1)
				{
					v2.push_back((*it).second);
				}
				else
				{
					v3.push_back((*it).second);
				}
			}
			Group.clear(); // �������գ����´λ����ϴα�����ֵ
			cout << endl;
		}
	}
	cout << "--------------"<<"��" << this->index << "�ֱ�������" <<"---------------" << endl;	 
}

void Manager::showSpeach()
{
	cout << "------------" << "��" << this->index << "��ѡ�ֽ�����Ϣ��" << "-------------" << endl;
	vector<int>v;
	if (this->index == 1)
	{
		v = v2;
	}
	else
	{
		v = v3;
	}
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << "��ţ�" << *it << "\t������"
			<< this->m_speaker[*it].s_name << "\tƽ���֣�"
			<< this->m_speaker[*it].s_score[this->index - 1] << endl;
	}
	v.clear();
	cout << endl;
	system("pause");
	system("cls");
}

void Manager::saveSpeach()
{
	ofstream ofs;
	ofs.open("Speach.csv", ios::out | ios::app);
	// �������׷�ӷ�ʽ���ļ�����׺����Ϊcsv
	// �����ջ�ʤ��3������д���ļ�
	for (vector<int>::iterator it = v3.begin(); it != v3.end(); it++)
	{
		ofs << *it <<"," <<this->m_speaker[*it].s_score[1] << ",";
	}
	ofs << endl;
	ofs.close();
	cout << "�ļ��ѱ��棡" << endl;
	this->fileISempty = false;
}

// ��ȡ�ļ�
void Manager::loadSpeach()
{
	ifstream ifs("Speach.csv", ios::in); // ����ʽ���ļ�

	// 1���ļ�������
	if (!ifs.is_open())
	{
		this->fileISempty = true;
		cout << "�ļ������ڣ�" << endl;
		ifs.close();
		return;
	}
	// 2���ļ�Ϊ�գ�����գ�
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "�ļ�Ϊ�գ�" << endl;
		this->fileISempty = true;
		ifs.close();
		return;
	}
	// 3���ļ���Ϊ��
	this->fileISempty = false;
	ifs.putback(ch);// �������ȡ��1���ַ��Ż�
	string data; // �洢�ļ��ж�ȡ������Ϣ
	int session = 1; // �����Ľ���	
	while (ifs >> data)
	{
		vector<string>v; // �洢ѡ�ֱ���Լ�������������ֱ�Ӷ���string����
		int pos = -1; // �鵽,���ŵ�λ�ã���λ�ô洢��pos
		int start = 0;// ��ʼλ��
		while (true)
		{
			pos = data.find(",", start);// ��start 0��ʼ���� ������ 
		// 10003,80.375,10004,80,10007,79.375
		//  start 1  pos ,�������ڵ�λ�ã��м�Ҫ��ȡ�ľ���pos-start
			if (pos == -1)
			{
				// û�ҵ�
				break;
			}
			string tmp = data.substr(start, pos - start);
			v.push_back(tmp);
			start = pos + 1; // ��start�Ƶ�pos+1��λ��
		}
		this->s_Load.insert(make_pair(session, v)); // ��������ѡ����Ϣ���뵽s_Load��
		session++;
	}
	ifs.close();
}

void Manager::showRecord()
{
	if (this->fileISempty)
	{
		cout << "�ļ�Ϊ�ջ򲻴��ڣ�" << endl;
	}
	else
	{
		for (map<int, vector<string>>::iterator it = s_Load.begin(); it != s_Load.end(); it++)
		{
			cout << "��" << it->first << "�� "
				<< "\t�ھ����Ϊ��" << it->second[0] << "\t����Ϊ��" << it->second[1] << endl
				<< "\t�Ǿ����Ϊ��" << it->second[2] << "\t����Ϊ��" << it->second[3] << endl
				<< "\t�������Ϊ��" << it->second[4] << "\t����Ϊ��" << it->second[5] << endl;
			Sleep(40);
		}
	}
	Sleep(500);
	system("pause");
	system("cls");
}

void Manager:: destoryRecord()
{
	cout << "�Ƿ�ȷ����գ�" << endl;
	cout << "ȷ�ϣ�1" << endl;
	cout << "ȡ����0" << endl;
	cout << "�����룺" << endl;
	int input;
	cin >> input;

	if (input == 1)
	{
		ofstream ofs("Speach.csv", ios::trunc);
		// trunc������ļ����ڣ�ɾ�������´���
		ofs.close();

		// Ȼ�����Գ�ʼ��
		this->initSpeaker(); // ��ʼ��
		this->createSpeaker(); // ����ѡ��
		this->loadSpeach(); // ��ȡ�����¼
		cout << "��ճɹ���" << endl;
	}
	system("pause");
	system("cls");
}