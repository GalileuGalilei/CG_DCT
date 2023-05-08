#pragma once
#include "gl_canvas2d.h"
#include "GameEvents.h"
#include "Tools.h"
#include "Vector2.h"
#include "Botao.h"
#include "Sample.h"
#include "Slider.h"
#include "GraphDisplay.h"
#include <functional>
#include <list>
#include <DCT.h>

class ToolBar : IRenderable
{
private :
	std::list<Button*> buttonList;
	std::list<Slider*> sliderList;

	int sampleSize = 32;
	int quantization = 1;
	int baseFunction = 0;

	Sample* originalSample = nullptr;
	Sample* DCTSample = nullptr;
	Sample* IDCTSample = nullptr;
	Sample* diffSample = nullptr;
	Sample* quantizedSample = nullptr;
	Sample* baseCossineSample = nullptr;

	GraphDisplay* graphDisplay;

	Vector2 position;
	Vector2 size;

	Vector2 buttonSize;

	const int offset;
	const char* outFilename = "output.dct";
	const char* inFilename = "input.dct";
	
	Graph* baseCossineGraph;

public :
	ToolBar(GraphDisplay* graphDisplay, Vector2 position, Vector2 size, int buttonOffset) : offset(buttonOffset)
	{
		this->originalSample = new Sample();
		this->baseCossineSample = new Sample();
		this->position = position;
		this->size = size;
		this->graphDisplay = graphDisplay;
		
		buttonSize = Vector2(size.x - offset, (size.x / 2) - offset);
		SetButtonsAndSliders();

		EventManager::Instance()->AddListener<OnToolEvent>(ITool::OnTool);
		SetColorDisplay();

		originalSample->GenerateMultiSenoidalSampleVector(sampleSize);
		CalculateSamples();
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

	void AddSlider(std::function<int(int)> OnChange, Vector2 valueRange, const char label[])
	{
		int y = (buttonSize.y + offset) * (buttonList.size() + sliderList.size()) + offset * 2;
		int x = position.x + offset;
		Slider* s = new Slider(OnChange, Vector2(x,y), buttonSize, valueRange, label);
		sliderList.push_back(s);
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
				originalSample->LoadSample(outFilename);
			}, Colors::orange, "Load");

		AddButton([this]() 
			{
				originalSample->SaveSample(outFilename);
			}, Colors::orange, "Save");

		AddButton([this]()
			{
				originalSample->GenerateMultiSenoidalSampleVector(sampleSize);
				CalculateSamples();
			}, Colors::orange, "R.Senoid");

		AddButton([this]()
			{
				originalSample->GenerateSenoidalSampleVector(sampleSize);
				CalculateSamples();
			}, Colors::orange, "Senoid");

		AddButton([this]()
			{
				originalSample->GenerateSampleVector(sampleSize);
				CalculateSamples();
			}, Colors::orange, "Random");

		AddSlider([this](int value)
			{
				sampleSize = value;
				baseFunction = 0;
				return value;
			}, Vector2(32, 512), "Sample Size");

		AddSlider([this](int value)
			{
				quantization = value;
				return value;
			}, Vector2(1, 32), "Quantization");

		AddSlider([this](int value)
			{
				if (originalSample == nullptr)
				{
					return sampleSize;
				}

				if (value < sampleSize)
				{
					baseFunction = value;
				//	char strValue[5];
				//	snprintf(strValue, 5, "%i", value);
				//	char aux[32];
				//	std::strcpy(aux, baseFunctionPreLabel);
				////std::strcpy(baseFunctionLabel, strcat(aux, strValue));
					DCT::BaseCossineFunction(baseCossineSample, baseFunction);
					baseCossineGraph->Update();
					return value;
				}
				
				return sampleSize;
			}, Vector2(0, 512), "Base Function");
	}

	void CalculateSamples()
	{
		if (originalSample->sample_vector.size() == 0)
		{
			return;
		}

		if (originalSample->sample_vector.size() > 512)
		{
			int a = 2;
		}

		DCT::BaseCossineFunction(baseCossineSample, baseFunction);
		delete(DCTSample);
		DCTSample = DCT::ApplyDCT(originalSample);
		delete(quantizedSample);
		quantizedSample = DCT::ApplyQuantization(DCTSample, quantization);

		delete(IDCTSample);
		Sample* desquantized = DCT::ApplyDequantization(quantizedSample, quantization);
		IDCTSample = DCT::ApplyIDCT(desquantized);

		delete(diffSample);
		diffSample = DCT::CalculateError(originalSample, IDCTSample);
		AddGraphs();

		delete(desquantized);
	}

	void AddGraphs()
	{
		graphDisplay->Clear();
		graphDisplay->AddGraph(originalSample, "Original");
		graphDisplay->AddGraph(DCTSample, "DCT");
		graphDisplay->AddGraph(quantizedSample, "Quantized DCT");
		graphDisplay->AddGraph(IDCTSample, "IDCT");
		graphDisplay->AddGraph(diffSample, "Diff");
		baseCossineGraph = graphDisplay->AddGraph(baseCossineSample, "Base Cossine Function");
	}
};