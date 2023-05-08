#pragma once
#include "Sample.h"
#include "GameEvents.h"
#include "Vector2.h"
/// <summary>
/// Desenha um grafico na tela a partir de um sample
/// </summary>
class Graph : IRenderable
{
private:
	Sample* sample;
	Vector2 position;
	Vector2 size;
	float range;
	const char* label;

	float CalculateRange();

public:
	Graph(Vector2 position, Vector2 size, Sample* sample, const char* label);
	Graph(Vector2 position, Vector2 size, Sample* sample, Vector2 range, const char* label);
	void OnRender(OnRenderEvent* args) override;
	void Update();
	friend class GraphDisplay;
};

