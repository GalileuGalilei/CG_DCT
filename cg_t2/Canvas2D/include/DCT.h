#pragma once
#include "Graph.h"

/// <summary>
/// recebe uma sample e retorna uma sample com a DCT aplicada e plota os devidos graficos
/// </summary>
class DCT
{
private:
	Vector2 position;
	Vector2 size;
	Sample* sample;

	Graph* original;
	Graph* dct;

public:
	DCT(Vector2 position, Vector2 size, Sample* sample, int offset);
	~DCT();
	static Sample* ApplyDCT(Sample* sample);



};