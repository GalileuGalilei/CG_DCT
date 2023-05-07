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

public:
	Graph(Vector2 position, Vector2 size, Sample* sample);

	void OnRender(OnRenderEvent* args) override;
};

