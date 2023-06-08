#include"SpeachManager.h"

// 构造函数
Manager::Manager()
{
	this->initSpeaker(); // 初始化
	this->createSpeaker(); // 创建选手
	this->loadSpeach(); // 获取往届记录
}
// 析构函数
Manager::~Manager()
{
	;
}

// 菜单功能
void Manager::show_menu()
{
	cout << "******************************************" << endl;
	cout << "********** 欢迎使用演讲比赛系统 **********" << endl;
	cout << "**********    1、开始演讲比赛   **********" << endl;
	cout << "**********    2、查看往届记录   **********" << endl;
	cout << "**********    3、清空比赛记录   **********" << endl;
	cout << "**********    0、退出比赛系统   **********" << endl;
	cout << "******************************************" << endl;
}

// 退出功能
void Manager::exit_m()
{
	cout << "欢迎下次使用！" << endl;
	exit(0);
}

// 初始化属性
void Manager::initSpeaker()
{
	// 全部清空并置1
	this->v1.clear();
	this->v2.clear();
	this->v3.clear();
	this->m_speaker.clear();
	this->index = 1;

	this->s_Load.clear(); // 初始化记录容器
}

// 创建选手
void Manager::createSpeaker()
{
	string nameSeed = "ABCDEFJHIJKL";
	for (int i = 0; i < nameSeed.size(); i++)
	{
		string name = "选手";
		name += nameSeed[i];

		speaker sp; // 创建一位选手
		sp.s_name = name; // 选手名字初始化
		for (int j = 0; j < 2; j++)
		{
			sp.s_score[j] = 0; // 选手分数初始化
		}
		// 为选手编号
		this->v1.push_back(i + 10001);
		// 将选手编号以及对应选手插入到map容器中，编号10001-100012
		this->m_speaker.insert(make_pair(i + 10001, sp));
	}
}

// 抽签
void Manager::DrawSpeach()
{
	cout << "------------第" << this->index << "轮抽签正在进行-------------" << endl;
	cout << "------------------------------------------" << endl;
	Sleep(500);
	cout << "抽签后演讲顺序如下：" << endl;
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
// 开始比赛
void Manager::startSpeach()
{
	// 第一轮比赛
	//	1、抽签
	this->DrawSpeach();
	//	2、比赛
	this->Speach();
	//	3、显示比赛结果
	this->showSpeach();
	
	// 第二轮比赛
	this->index++;
	//	1、抽签
	this->DrawSpeach();
	//	2、比赛
	this->Speach();
	//	3、显示比赛结果
	this->showSpeach();
	//  4、保存比赛前三名
	this->saveSpeach();

	this->initSpeaker(); // 初始化
	this->createSpeaker(); // 创建选手
	this->loadSpeach(); // 获取往届记录

	cout << "本届比赛正式结束！" << endl;
	Sleep(500);
	system("pause");
	system("cls");
}

void Manager::Speach()
{
	cout << "------------" << "第" << this->index << "组比赛正式开始" << "-------------" << endl;
	multimap<double, int, greater<double>> Group; // 存储分数与选手编号，降序排列，放在最外面，防止进入循环创建不同的容器

	//	1、创建比赛的人员的容器v_person，并根据不同轮数将对应容器赋给v_person
	vector<int>v_person;
	if (this->index == 1)
	{
		v_person = v1;
	}
	else
	{
		v_person = v2;
	}

	//	2、创建人数的计数num，遍历v_person里所有选手，创建deque容器，每个选手进行10名评委的打分
	//	   排序后去除最高分和最低分，最后获取总分和平均分
	int num = 0;
	for (vector<int>::iterator it = v_person.begin(); it != v_person.end(); it++)
	{
		// 评委打分
		deque<double>d;
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600) / 10.f; // 随机数600-1000，除以10后保留1位小数，是60.0-100.0
			d.push_back(score); // 将分数插入到d中
		}
		sort(d.begin(), d.end(),greater<double>()); // 降序 排序
		d.pop_back();	// 去除最低分
		d.pop_front();	// 去除最高分

		double sum = accumulate(d.begin(), d.end(),0); // 获取总分
		double avg = sum / d.size();	// 获取均值
		this->m_speaker[*it].s_score[this->index - 1] = avg; // 将均分存入到选手对应轮数的score里

		//	3、创建小组容器，以平均分和编号创建对组，每6个选手为一组，输出这6名选手的姓名编号与成绩
		Group.insert(make_pair(avg, *it)); // 将每位选手的均分和编号插入到Group容器中
		num++;	// 插入后人数++
		if (num % 6 == 0) // 每插入6个人，进入一次遍历输出，此时输出的已经排序
		{
			cout <<"第" << num / 6 << "组选手比赛名次：" << endl;
			for (multimap<double, int, greater<double>>::iterator it = Group.begin(); it != Group.end(); it++)
			{
				cout << "编号：" << it->second << "\t姓名："
					<< this->m_speaker[it->second].s_name << "\t平均分："
					<< this->m_speaker[it->second].s_score[this->index - 1] << endl;
			}

			//	4、取出前3名，如果是第1场比赛，则将前三名插入到v2容器，如果是第2场比赛，则插入到v3中，每6个清空一次
			int count = 0; // 使我们可以取出前三名：0、1、2
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
			Group.clear(); // 如果不清空，则下次会有上次遍历的值
			cout << endl;
		}
	}
	cout << "--------------"<<"第" << this->index << "轮比赛结束" <<"---------------" << endl;	 
}

void Manager::showSpeach()
{
	cout << "------------" << "第" << this->index << "轮选手晋级信息：" << "-------------" << endl;
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
		cout << "编号：" << *it << "\t姓名："
			<< this->m_speaker[*it].s_name << "\t平均分："
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
	// 以输出和追加方式打开文件，后缀命名为csv
	// 将最终获胜的3人数据写入文件
	for (vector<int>::iterator it = v3.begin(); it != v3.end(); it++)
	{
		ofs << *it <<"," <<this->m_speaker[*it].s_score[1] << ",";
	}
	ofs << endl;
	ofs.close();
	cout << "文件已保存！" << endl;
	this->fileISempty = false;
}

// 读取文件
void Manager::loadSpeach()
{
	ifstream ifs("Speach.csv", ios::in); // 读方式打开文件

	// 1、文件不存在
	if (!ifs.is_open())
	{
		this->fileISempty = true;
		cout << "文件不存在！" << endl;
		ifs.close();
		return;
	}
	// 2、文件为空（被清空）
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "文件为空！" << endl;
		this->fileISempty = true;
		ifs.close();
		return;
	}
	// 3、文件不为空
	this->fileISempty = false;
	ifs.putback(ch);// 将上面截取的1个字符放回
	string data; // 存储文件中读取到的信息
	int session = 1; // 比赛的届数	
	while (ifs >> data)
	{
		vector<string>v; // 存储选手编号以及分数的容器，直接都用string类型
		int pos = -1; // 查到,逗号的位置，将位置存储在pos
		int start = 0;// 起始位置
		while (true)
		{
			pos = data.find(",", start);// 从start 0开始查找 ，逗号 
		// 10003,80.375,10004,80,10007,79.375
		//  start 1  pos ,逗号所在的位置，中间要截取的就是pos-start
			if (pos == -1)
			{
				// 没找到
				break;
			}
			string tmp = data.substr(start, pos - start);
			v.push_back(tmp);
			start = pos + 1; // 让start移到pos+1的位置
		}
		this->s_Load.insert(make_pair(session, v)); // 将届数和选手信息插入到s_Load里
		session++;
	}
	ifs.close();
}

void Manager::showRecord()
{
	if (this->fileISempty)
	{
		cout << "文件为空或不存在！" << endl;
	}
	else
	{
		for (map<int, vector<string>>::iterator it = s_Load.begin(); it != s_Load.end(); it++)
		{
			cout << "第" << it->first << "届 "
				<< "\t冠军编号为：" << it->second[0] << "\t分数为：" << it->second[1] << endl
				<< "\t亚军编号为：" << it->second[2] << "\t分数为：" << it->second[3] << endl
				<< "\t季军编号为：" << it->second[4] << "\t分数为：" << it->second[5] << endl;
			Sleep(40);
		}
	}
	Sleep(500);
	system("pause");
	system("cls");
}

void Manager:: destoryRecord()
{
	cout << "是否确认清空？" << endl;
	cout << "确认：1" << endl;
	cout << "取消：0" << endl;
	cout << "请输入：" << endl;
	int input;
	cin >> input;

	if (input == 1)
	{
		ofstream ofs("Speach.csv", ios::trunc);
		// trunc：如果文件存在，删除并重新创建
		ofs.close();

		// 然后将属性初始化
		this->initSpeaker(); // 初始化
		this->createSpeaker(); // 创建选手
		this->loadSpeach(); // 获取往届记录
		cout << "清空成功！" << endl;
	}
	system("pause");
	system("cls");
}