#pragma once
#include "gl_canvas2d.h"
#include "GameEvents.h"
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

	Sample* originalSample = new Sample();
	Sample* DCTSample = new Sample();
	Sample* IDCTSample = new Sample();
	Sample* diffSample = new Sample();
	Sample* quantizedSample = new Sample();
	Sample* dequantizedSample = new Sample();
	Sample* baseCossineSample = new Sample();

	GraphDisplay* graphDisplay;

	Vector2 position;
	Vector2 size;

	Vector2 buttonSize;

	const int offset;
	const char* outFilename = "output.dct";
	const char* inFilename = "input.dct";

public :
	ToolBar(GraphDisplay* graphDisplay, Vector2 position, Vector2 size, int buttonOffset) : offset(buttonOffset)
	{
		this->position = position;
		this->size = size;
		this->graphDisplay = graphDisplay;
		
		buttonSize = Vector2(size.x - offset, (size.x / 2) - offset);
		SetButtonsAndSliders();

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
				originalSample->SaveSample(inFilename);
				IDCTSample->SaveSample(outFilename);
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
			}, Vector2(32, 512), "Samples");

		AddSlider([this](int value)
			{
				quantization = value;
				return value;
			}, Vector2(1, 128), "Quantz.");

		AddSlider([this](int value)
			{
				if (value < sampleSize)
				{
					baseFunction = value;
					DCT::BaseCossineFunction(baseCossineSample, baseFunction);
					UpdateGraphs();
					return value;
				}
				
				return sampleSize;
			}, Vector2(0, 512), "Base Func");
	}

	void CalculateSamples()
	{
		if (originalSample->sample_vector.size() == 0)
		{
			return;
		}

		DCT::ApplyDCT(originalSample, DCTSample);
		DCT::ApplyQuantization(DCTSample, quantizedSample, quantization);
		DCT::ApplyDequantization(quantizedSample, dequantizedSample, quantization);
		DCT::ApplyIDCT(dequantizedSample, IDCTSample);
		DCT::CalculateError(originalSample, IDCTSample, diffSample);
		DCT::BaseCossineFunction(baseCossineSample, baseFunction);
		UpdateGraphs();
	}

	void UpdateGraphs()
	{
		graphDisplay->Clear();
		graphDisplay->AddGraph(originalSample, "Original");
		graphDisplay->AddGraph(DCTSample, "DCT");
		graphDisplay->AddGraph(quantizedSample, "Quantized DCT");
		graphDisplay->AddGraph(IDCTSample, "IDCT (Reconstructed)");
		graphDisplay->AddGraph(diffSample, "Difference (ERROR)");
		graphDisplay->AddGraph(baseCossineSample, "Base Cossine Function");
	}
};