#include "SGD.h"

SGD_linear::SGD_linear(float lr, int bs)
{
	weight = rand() % 65536 / 65536.0;
	bias = rand() % 65536 / 65536.0;
	learn_rate = lr;
	batch_size = bs;
}

SGD_linear::~SGD_linear()
{
	train_set.clear();
}

void SGD_linear::load_data(vector<sample> ts)
{
	for (int i = 0; i < ts.size(); i++)
	{
		sample s;
		s.x = ts[i].x;
		s.y = ts[i].y;
		train_set.push_back(s);
	}
}

void SGD_linear::release_data()
{
	train_set.clear();
}

void SGD_linear::run(int total_iter)
{
	int iter = 0;
	while (iter != total_iter)
	{
		vector<sample> batch = random_sampling();
		float loss = loss_function(batch);

		printf("iter=%d: loss=%f\n", iter++, loss);

		diff_function(batch);

		printf("\tw:%f b:%f\n", weight, bias);
	}
}

float SGD_linear::get_weight()
{
	return weight;
}

float SGD_linear::get_bias()
{
	return bias;
}

void SGD_linear::update(float diff_w, float diff_b)
{
	weight = weight - learn_rate * diff_w;
	bias = bias - learn_rate * diff_b;
}

float SGD_linear::loss_function(vector<sample> samples)
{
	float loss = 0;
	for (int i = 0; i < batch_size; i++)
	{
		loss += pow(samples[i].y - (bias + weight*samples[i].x), 2);
	}

	return loss / batch_size;
}

void SGD_linear::diff_function(vector<sample> samples)
{
	float diff_w = 0;
	float diff_b = 0;
	for (int i = 0; i < batch_size; i++)
	{
		diff_w += (2 * (samples[i].y - (bias + weight*samples[i].x)) * -samples[i].x);
		diff_b += (2 * (samples[i].y - (bias + weight*samples[i].x)) * -1);
	}

	update(diff_w / batch_size, diff_b / batch_size);
}

vector<sample> SGD_linear::random_sampling()
{
	vector<sample> batch;
	for (int i = 0; i < batch_size; i++)
	{
		int r = rand() % train_set.size();
		batch.push_back(train_set[r]);
	}

	return batch;
}