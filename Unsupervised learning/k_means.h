#pragma once
#include <vector>
using namespace std;

class k_means
{
	int feature_lenght;
	int cluster_num;
	vector<vector<float>> cluster_center;
	vector<vector<float>> train_set;

	vector<float> get_max_feature();
	float dist(vector<float> x1, vector<float> x2);

public:
	k_means(int cn,int fl);
	~k_means();

	void load_data(vector<vector<float>> ts);
	void release_data();
	vector<vector<float>> run(int iter);
};