#pragma once
#include "Sample.h"

/// <summary>
/// classe auxiliar para aplicar a transformada discreta de cosseno dentre outras operacoes
/// </summary>
class DCT
{
private:
	DCT() {};

public:
	static void ApplyDCT(Sample* sample, Sample* dctSample);
	static void ApplyIDCT(Sample* sample, Sample* idctSample);
	static void BaseCossineFunction(Sample* baseCossineSample, int u);
	static void ApplyQuantization(Sample* sample, Sample* quantizedSample, int quantization);
	static void ApplyDequantization(Sample* sample, Sample* quantizedSample, int quantization);
	static void CalculateError(Sample* sample1, Sample* sample2, Sample* errorSample);
};