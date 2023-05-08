#include "GraphDisplay.h"
#include "gl_canvas2d.h"
#include <math.h>

GraphDisplay::GraphDisplay(Vector2 position, Vector2 size, int padding)
{
	this->position = position;
	this->size = size;
	this->padding = padding;
}

Graph* GraphDisplay::AddGraph(Sample* sample, const char* label)
{
    Graph* graph = new Graph(Vector2(0, 0), Vector2(0, 0), sample, label);
	graphsVector.push_back(graph);
    CalculateGraphs();
    return graph;
}

Graph* GraphDisplay::AddGraph(Sample* sample, Vector2 range, const char* label)
{
	Graph* graph = new Graph(Vector2(0, 0), Vector2(0, 0), sample, range, label);
	graphsVector.push_back(graph);
	CalculateGraphs();
	return graph;
}

void GraphDisplay::Clear()
{
	graphsVector.clear();
    CalculateGraphs();
}

void GraphDisplay::CalculateGraphs()
{
    if (graphsVector.size() == 0)
    {
        return;
    }

    int x = position.x;
    int y = position.y;
    int w = size.x;
    int h = size.y;
    CV::color(0, 0, 0);
    CV::rectFill(x, y, w + x, h + y);

    int graphCount = graphsVector.size();
    int rows = sqrt(graphCount);
    int cols = (graphCount + rows - 1) / rows;
    int graphWidth = (w - (padding * (cols + 1))) / cols;
    int graphHeight = (h - (padding * (rows + 1))) / rows;

    int graphX = x + padding;
    int graphY = y + padding;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int index = i * cols + j;
            if (index >= graphCount) break;

            Graph* graph = graphsVector[index];
            graph->position = Vector2(graphX, graphY);
            graph->size = Vector2(graphWidth, graphHeight);

            graphX += graphWidth + padding;
        }
        graphX = x + padding;
        graphY += graphHeight + padding;
    }
}


