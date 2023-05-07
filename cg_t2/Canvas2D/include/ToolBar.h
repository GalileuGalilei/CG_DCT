#pragma once
#include "gl_canvas2d.h"
#include "GameEvents.h"
#include "Tools.h"
#include "Vector2.h"
#include "Botao.h"
#include "Sample.h"
#include "Slider.h"
#include <functional>
#include <list>

class ToolBar : IRenderable
{
private :
	std::list<Button*> buttonList;
	std::list<Slider*> sliderList;
	Sample* sample;
	Slider* tamSlider = NULL;

	Vector2 position;
	Vector2 size;

	Vector2 buttonSize;

	const int offset;
	const char* filename = "output.dct";

public :
	ToolBar(Sample* sample, Vector2 position, Vector2 size, int buttonOffset) : offset(buttonOffset)
	{
		this->position = position;
		this->size = size;
		this->sample = sample;
		
		buttonSize = Vector2(size.x - offset, (size.x / 2) - offset);
		SetButtonsAndSliders();

		EventManager::Instance()->AddListener<OnToolEvent>(ITool::OnTool);
		SetColorDisplay();
	}

	~ToolBar()
	{
		for (Button* b : buttonList)
		{
			delete b;
		}

		buttonList.clear();

		for (Slider* s : sliderList)
		{
			delete s;
		}

		sliderList.clear();
	}

	void AddButton(std::function<void()> callback, Color color, const char label[])
	{
		int y = (buttonSize.y + offset) * buttonList.size() + offset;
		int x = position.x + offset;
		Button* b = new Button(Vector2(x, y), buttonSize, color, label, callback);
		buttonList.push_back(b);
	}

	Slider* AddSlider(const char label[], float width, float min, float max)
	{
		int y = (buttonSize.y + offset) * buttonList.size() + offset * 2;
		int x = position.x + offset;
		Slider* s = new Slider(x, y, width, min, max, label);

		if (tamSlider == NULL)
		{
			tamSlider = s;
		}

		return s;
	}

private:

	void OnRender(OnRenderEvent* args) override
	{
		Color c = Colors::yellow;
		CV::color(c.r, c.g, c.b);
		CV::rectFill(position.x, position.y, size.x + offset, size.y);
	}

	GameLayer GetLayer() override
	{
		return GameLayer::UI;
	}

	void SetColorDisplay()
	{
		Vector2 pos;
		pos.x = offset;
		pos.y = (buttonSize.y + offset) * buttonList.size() + offset;
	}

	void SetButtonsAndSliders()
	{
		AddButton([this]() 
			{
				sample->LoadSample(filename);
			}, Colors::orange, "Load");

		AddButton([this]() 
			{
				sample->SaveSample(filename);
			}, Colors::orange, "Save");


		AddButton([this]()
			{
				sample->GenerateMultiSenoidalSampleVector(tamSlider->GetValue());
			}, Colors::orange, "R.Senoid");

		AddButton([this]()
			{
				sample->GenerateSenoidalSampleVector(tamSlider->GetValue());
			}, Colors::orange, "Senoid");

		AddButton([this]()
			{
				sample->GenerateSampleVector(tamSlider->GetValue());
			}, Colors::orange, "Random");

		AddSlider("Tamanho", buttonSize.x, 32, 512);
	}
};