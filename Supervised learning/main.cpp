#include <stdio.h>
#include <fstream>
#include <vector>
#include "SGD.h"
using namespace std;

struct wz_data
{
	int dw;//段位
	int cs;//对战场数
	int bz;//被赞
	int yx;//英雄个数
	int pf;//皮肤个数
	int s;//上
	int z;//中
	int x;//下
	int f;//辅
	int y;//野
	int vip;//VIP等级
};

wz_data get_feature(char* buf)
{
	vector<int> feature;

	int len = strlen(buf);
	int n = 0;
	char tmp[10];
	for (int i = 0; i < len; i++,n++)
	{
		tmp[n] = buf[i];

		if (tmp[n] == ',')
		{
			tmp[n] = 0;
			feature.push_back(atoi(tmp));
			n = -1;
		}
	}

	n++;
	tmp[n] = 0;
	feature.push_back(atoi(tmp));

	wz_data data;
	data.dw = feature[0];
	data.cs = feature[1];
	data.bz = feature[2];
	data.yx = feature[3];
	data.pf = feature[4];
	data.s = feature[5];
	data.z = feature[6];
	data.x = feature[7];
	data.f = feature[8];
	data.y = feature[9];
	data.vip = feature[10];

	return data;
}

int main()
{
	ifstream in("E:\\课程\\模式识别\\data.txt");

	//load data
	vector<wz_data> feature_set;
	while (!in.eof())
	{
		char buf[256];
		in.getline(buf, 256);

		feature_set.push_back(get_feature(buf));
	}

	//create train set
	vector<sample> train_set;
	for (int i = 0; i < feature_set.size(); i++)
	{
		sample s;
		s.x = i + 1;
		s.y = feature_set[i].cs;
		train_set.push_back(s);
	}

	//sgd

	SGD_nonlinear proc(0.000000001, 1);
	proc.load_data(train_set);
	proc.run(10000);

	/*SGD_linear proc(0.00001, 1);
	proc.load_data(train_set);
	proc.run(10000);*/

	return 0;
}