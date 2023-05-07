#include "DCT.h"
#include <iostream>

Sample* DCT::ApplyDCT(Sample* sample)
{
	const float pi = 3.1415926;

	std::vector<float> sample_vector = sample->sample_vector;
	int size = sample_vector.size();

	Sample* dctSample = new Sample();
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
	return dctSample;
}

Sample* DCT::ApplyIDCT(Sample* sample)
{
	const float pi = 3.1415926;

	std::vector<float> sample_vector = sample->sample_vector;
	int size = sample_vector.size();

	Sample* idctSample = new Sample();
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
	return idctSample;
}

Sample* DCT::ApplyQuantization(Sample* sample, int quantization)
{
	std::vector<float> sample_vector = sample->sample_vector;
	int size = sample_vector.size();
	Sample* quantizedSample = new Sample();
	quantizedSample->sample_vector.resize(size);
	for (int i = 0; i < size; i++)
	{
		quantizedSample->sample_vector[i] = sample_vector[i] / quantization;
	}
	return quantizedSample;
}

Sample* DCT::ApplyDequantization(Sample* sample, int quantization)
{
	std::vector<float> sample_vector = sample->sample_vector;
	int size = sample_vector.size();
	Sample* dequantizedSample = new Sample();
	dequantizedSample->sample_vector.resize(size);
	for (int i = 0; i < size; i++)
	{
		dequantizedSample->sample_vector[i] = sample_vector[i] * quantization;
	}
	return dequantizedSample;
}

Sample* DCT::CalculateError(Sample* sample1, Sample* sample2)
{
	if (sample1->sample_vector.size() != sample2->sample_vector.size())
	{
		return sample1;
	}

	std::vector<float> sample_vector = sample1->sample_vector;
	std::vector<float> sample2_vector = sample2->sample_vector;
	int size = sample_vector.size();
	Sample* errorSample = new Sample();
	errorSample->sample_vector.resize(size);
	for (int i = 0; i < size; i++)
	{
		errorSample->sample_vector[i] = sample_vector[i] - sample2_vector[i];
	}
	return errorSample;
}