#include "DCT.h"
#include <iostream>

float CalculateRange(Sample* sample)
{
	int sampleSize = sample->sample_vector.size();
	float* sample_vector = sample_vector = sample->sample_vector.data();
	float max = sample_vector[0];
	float min = sample_vector[0];
	for (int i = 0; i < sampleSize; i++)
	{
		float sampleValue = sample_vector[i];
		if (sampleValue > max)
		{
			max = sampleValue;
		}
		if (sampleValue < min)
		{
			min = sampleValue;
		}
	}
	return max - min;
}

float CalculateMax(Sample* sample)
{
	int sampleSize = sample->sample_vector.size();
	float* sample_vector = sample_vector = sample->sample_vector.data();
	float max = sample_vector[0];
	for (int i = 0; i < sampleSize; i++)
	{
		float sampleValue = sample_vector[i];
		if (sampleValue > max)
		{
			max = sampleValue;
		}
	}
	return max;
}

void DCT::ApplyDCT(Sample* sample, Sample* dctSample)
{
	const float pi = 3.1415926;

	std::vector<float> sample_vector = sample->sample_vector;
	int size = sample_vector.size();
	dctSample->sample_vector.resize(size);

	for (int i = 0; i < size; i++)
	{
		float sum = 0;
		for (int j = 0; j <  size; j++)
		{
			float value = sample_vector[j];
			float cosine = cos((pi * (2 * j + 1) * i) / (2 * size));
			sum += value * cosine;
		}

		dctSample->sample_vector[i] = sum;
	}
}

void DCT::ApplyIDCT(Sample* sample, Sample* idctSample)
{
	const float pi = 3.1415926;
	float max = 0;

	std::vector<float> sample_vector = sample->sample_vector;
	int size = sample_vector.size();
	idctSample->sample_vector.resize(size);

	for (int i = 0; i < size; i++)
	{
		float sum = 0;
		for (int j = 0; j < size; j++)
		{
			float value = sample_vector[j];
			float cosine = cos((pi * (2 * i + 1) * j) / (2 * size));
			sum += value * cosine;
		}

		idctSample->sample_vector[i] = sum;
	}
}

void DCT::BaseCossineFunction(Sample* baseFuction, int u)
{
	const float pi = 3.1415926;
	const int resolution = 200;

	baseFuction->sample_vector.clear();
	baseFuction->sample_vector.resize(resolution);

	for (int i = 0; i < resolution; i++)
	{
		float cossine = cos((pi * (2.f * i + 1) * u) / (2.f * resolution));
		baseFuction->sample_vector[i] = cossine;
	}
}

void DCT::ApplyQuantization(Sample* sample, Sample* quantizedSample, int quantization)
{
	std::vector<float> sample_vector = sample->sample_vector;
	int size = sample_vector.size();
	quantizedSample->sample_vector.resize(size);

	for (int i = 0; i < size; i++)
	{
		quantizedSample->sample_vector[i] = (int)(sample_vector[i] / quantization);
	}
}

void DCT::ApplyDequantization(Sample* sample, Sample* dequantizedSample, int quantization)
{
	std::vector<float> sample_vector = sample->sample_vector;
	int size = sample_vector.size();
	dequantizedSample->sample_vector.resize(size);

	for (int i = 0; i < size; i++)
	{
		dequantizedSample->sample_vector[i] = sample_vector[i] * quantization;
	}
}

void DCT::CalculateError(Sample* sample1, Sample* sample2, Sample* errorSample)
{
	if (sample1->sample_vector.size() != sample2->sample_vector.size())
	{
		return;
	}

	std::vector<float> sample1_vector = sample1->sample_vector;
	std::vector<float> sample2_vector = sample2->sample_vector;
	float range1 = CalculateRange(sample1);
	float range2 = CalculateRange(sample2);

	int size = sample1_vector.size();
	errorSample->sample_vector.resize(size);

	for (int i = 0; i < size; i++)
	{
		errorSample->sample_vector[i] = (((sample1_vector[i]) - (sample2_vector[i] / range2)*range1));
	}
}