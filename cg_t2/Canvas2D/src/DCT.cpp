#include "DCT.h"

Sample* DCT::ApplyDCT(Sample* sample)
{
	const float pi = 3.1415926;

	std::vector<char> sample_vector = sample->sample_vector;
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

DCT::DCT(Vector2 position, Vector2 size, Sample* sample, int offset)
{
	this->position = position;
	this->size = size;
	this->sample = sample;

	float x = position.x;
	float y = position.y;

	float w = size.x / 2;
	float h = size.y / 2;

	original = new Graph(Vector2(x,y), Vector2(w - offset,h - offset), sample);

	x += w;

	dct = new Graph(Vector2(x, y), Vector2(w, h), ApplyDCT(sample));
}

DCT::~DCT()
{
	free(original);
	free(dct);
}
