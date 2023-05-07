#include "Graph.h"
#include "gl_canvas2d.h"
#include <vector>

Graph::Graph(Vector2 position, Vector2 size, Sample* sample)
{
	this->position = position;
	this->size = size;
	this->sample = sample;
}

void Graph::OnRender(OnRenderEvent* args)
{


	int x = position.x;
	int y = position.y;
	int w = size.x;
	int h = size.y;

	int sampleSize = sample->sample_vector.size();
	char* sample_vector = sample_vector = sample->sample_vector.data();
	CV::color(0, 0, 0);
	CV::rectFill(x, y, w + x, h + y);

	if (sampleSize == 0)
	{
		return;
	}

	float sampleOffset = (float)w / sampleSize;
	Vector2 oldSamplePosition = Vector2(x,y);

	for (int i = 0; i < sampleSize; i++)
	{
		int sampleValue = sample_vector[i];
		float normValue = (float)sampleValue / 255.0f + 0.5f;
		int sampleX = x + (i * sampleOffset) + sampleOffset;
		int sampleY = y + (h * normValue);
		
		CV::color(1, 1, 1);
		CV::line(oldSamplePosition.x, oldSamplePosition.y, sampleX, sampleY);
		oldSamplePosition = Vector2(sampleX, sampleY);
	}
}
