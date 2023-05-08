#pragma once
#include "Graph.h"
#include "Vector2.h"
#include <vector>
/// <summary>
/// Essa classe permite plotar graficos igualmente distribuidos dentro de uma janela
/// </summary>
class GraphDisplay
{
	Vector2 position;
	Vector2 size;
	int padding;
	std::vector<Graph*> graphsVector;

public:
	GraphDisplay(Vector2 position, Vector2 size, int padding);
	Graph* AddGraph(Sample* sample, const char* label);
	Graph* AddGraph(Sample* sample, Vector2 range, const char* label);
	void Clear();
	void CalculateGraphs();
};

