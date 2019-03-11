#pragma once
#include <vector>
using namespace std;

struct sample
{
	float x;
	float y;
};

class SGD_linear
{
public:
	SGD_linear(float lr, int bs);
	~SGD_linear();

	void load_data(vector<sample> ts);
	void release_data();
	void run(int total_iter);
	float get_weight();
	float get_bias();

private:
	float weight, bias;
	float learn_rate;
	int batch_size;
	vector<sample> train_set;

	void update(float diff_w, float diff_b);
	float loss_function(vector<sample> samples);
	void diff_function(vector<sample> samples);
	vector<sample> random_sampling();
};

class SGD_nonlinear
{
public:
	SGD_nonlinear(float lr, int bs);
	~SGD_nonlinear();

	void load_data(vector<sample> ts);
	void release_data();
	void run(int total_iter);
	float* get_weight();

private:
	float weight[3];
	float learn_rate;
	int batch_size;
	vector<sample> train_set;

	void update(float* diff_w);
	float loss_function(vector<sample> samples);
	void diff_function(vector<sample> samples);
	vector<sample> random_sampling();
};