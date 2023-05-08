#include "Graph.h"
#include "gl_canvas2d.h"
#include <vector>

Graph::Graph(Vector2 position, Vector2 size, Sample* sample, const char* label)
{
	this->position = position;
	this->size = size;
	this->sample = sample;
	this->label = label;
	this->range = CalculateRange();
}

Graph::Graph(Vector2 position, Vector2 size, Sample* sample, Vector2 range, const char* label)
{
	this->position = position;
	this->size = size;
	this->sample = sample;
	this->label = label;
	this->range = range.y - range.x;
}

void Graph::Update()
{
	this->range = CalculateRange();
}

float Graph::CalculateRange()
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

void Graph::OnRender(OnRenderEvent* args)
{
	if (sample == nullptr)
	{
		return;
	}

	int x = position.x;
	int y = position.y;
	int w = size.x;
	int h = size.y;

	int sampleSize = sample->sample_vector.size();
	float* sample_vector = sample->sample_vector.data();
	CV::color(0, 0, 0);
	CV::text(x, y + h + 20, label);
	CV::rectFill(x, y - 5, w + x, h + y + 5);

	if (sampleSize == 0)
	{
		return;
	}

	float sampleOffset = (float)w / sampleSize;
	Vector2 oldSamplePosition = Vector2(x, y + h / 2);

	for (int i = 0; i < sampleSize; i++)
	{
		float sampleValue = sample_vector[i];
		float normValue;
		if (range != 0.f)
		{
			normValue = (float)sampleValue / range + 0.5f;
		}
		else
		{
			normValue = 0.5f;
		}
		int sampleX = x + (i * sampleOffset) + sampleOffset;
		int sampleY = y + (h * normValue);
		
		CV::color(1, 1, 1);
		CV::line(oldSamplePosition.x, oldSamplePosition.y, sampleX, sampleY);
		oldSamplePosition = Vector2(sampleX, sampleY);
	}
}
