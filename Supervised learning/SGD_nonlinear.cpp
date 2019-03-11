#include "SGD.h"

SGD_nonlinear::SGD_nonlinear(float lr, int bs)
{
	for (int i = 0; i < 3; i++)
	{
		weight[i] = rand() % 65536 / 65536.0;
	}
	learn_rate = lr;
	batch_size = bs;
}

SGD_nonlinear::~SGD_nonlinear()
{
	train_set.clear();
}

void SGD_nonlinear::load_data(vector<sample> ts)
{
	for (int i = 0; i < ts.size(); i++)
	{
		sample s;
		s.x = ts[i].x;
		s.y = ts[i].y;
		train_set.push_back(s);
	}
}

void SGD_nonlinear::release_data()
{
	train_set.clear();
}

void SGD_nonlinear::run(int total_iter)
{
	int iter = 0;
	while (iter != total_iter)
	{
		vector<sample> batch = random_sampling();

		float loss = loss_function(batch);
		printf("iter=%d: loss=%f\n", iter++, loss);

		diff_function(batch);
		printf("a:%f b:%f c:%f\n", weight[0], weight[1], weight[2]);
	}
}

float* SGD_nonlinear::get_weight()
{
	return weight;
}

void SGD_nonlinear::update(float* diff_w)
{
	for (int i = 0; i < 3; i++)
	{
		weight[i] = weight[i] - learn_rate * diff_w[i];
	}
}

float SGD_nonlinear::loss_function(vector<sample> samples)
{
	float loss = 0;
	for (int i = 0; i < batch_size; i++)
	{
		loss += pow(samples[i].y - (weight[0] * samples[i].x*samples[i].x + weight[1] * samples[i].x + weight[2]), 2);
	}

	return loss / batch_size;
}

void SGD_nonlinear::diff_function(vector<sample> samples)
{
	float diff_w[3] = { 0,0,0 };
	for (int i = 0; i < batch_size; i++)
	{
		diff_w[0] += (2 * (samples[i].y - (weight[0] * samples[i].x*samples[i].x + weight[1] * samples[i].x + weight[2])) * -samples[i].x*samples[i].x);
		diff_w[1] += (2 * (samples[i].y - (weight[0] * samples[i].x*samples[i].x + weight[1] * samples[i].x + weight[2])) * -samples[i].x);
		diff_w[2] += (2 * (samples[i].y - (weight[0] * samples[i].x*samples[i].x + weight[1] * samples[i].x + weight[2])) * -1);
	}

	for (int i = 0; i < 3; i++)
	{
		diff_w[i] /= batch_size;
	}

	update(diff_w);
}

vector<sample> SGD_nonlinear::random_sampling()
{
	vector<sample> batch;
	for (int i = 0; i < batch_size; i++)
	{
		int r = rand() % train_set.size();
		batch.push_back(train_set[r]);
	}

	return batch;
}