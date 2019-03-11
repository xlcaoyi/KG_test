#include "k_means.h"

k_means::k_means(int cn,int fl)
{
	feature_lenght = fl;
	cluster_num = cn;
}

k_means::~k_means()
{
	train_set.clear();
	cluster_center.clear();
}

void k_means::load_data(vector<vector<float>> ts)
{
	for (int i = 0; i < ts.size(); i++)
	{
		vector<float> feature;
		for (int j = 0; j < feature_lenght; j++)
		{
			feature.push_back(ts[i][j]);
		}
		train_set.push_back(feature);
	}
}

void k_means::release_data()
{
	train_set.clear();
	cluster_center.clear();
}

vector<float> k_means::get_max_feature()
{
	vector<float> max_feature;
	for (int i = 0; i < feature_lenght; i++)
	{
		max_feature.push_back(0);
	}

	for (int i = 0; i < train_set.size(); i++)
	{
		for (int j = 0; j < feature_lenght; j++)
		{
			if (max_feature[j] < train_set[i][j])
			{
				max_feature[j] = train_set[i][j];
			}
		}
	}

	return max_feature;
}

float k_means::dist(vector<float> x1, vector<float> x2)
{
	float dist = 0;
	for (int i = 0; i < feature_lenght; i++)
	{
		dist += abs(x1[i] - x2[i]);
	}
	return dist / feature_lenght;
}

vector<vector<float>> k_means::run(int iter_num)
{
	vector<float> max_feature = get_max_feature();
	for (int i = 0; i < cluster_num; i++)
	{
		vector<float> feature;
		for (int j = 0; j < feature_lenght; j++)
		{
			feature.push_back(rand()%(int(max_feature[j])+1));
		}
		cluster_center.push_back(feature);
	}

	for (int iter = 0; iter < iter_num; iter++)
	{
		for (int i = 0; i < train_set.size(); i++)
		{
			vector<float> feature = train_set[i];

			int min_id = 0;
			float min_dist = dist(feature, cluster_center[0]);
			for (int k = 0; k < cluster_num; k++)
			{
				float d = dist(feature, cluster_center[k]);
				if (d < min_dist)
				{
					min_id = k;
					min_dist = d;
				}
			}

			for (int j = 0; j < feature_lenght; j++)
			{
				cluster_center[min_id][j] = (cluster_center[min_id][j] + feature[j]) / 2;
			}
		}
		
		printf("-----------------------------------\n");
		for (int i = 0; i < cluster_num; i++)
		{
			for (int j = 0; j < feature_lenght; j++)
			{
				printf("%f\t", cluster_center[i][j]);
			}
			printf("\n");
		}
	}

	return cluster_center;
}