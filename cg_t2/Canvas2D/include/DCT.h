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
	static Sample* ApplyDCT(Sample* sample);
	static Sample* ApplyIDCT(Sample* sample);
	static Sample* ApplyQuantization(Sample* sample, int quantization);
	static Sample* ApplyDequantization(Sample* sample, int quantization);
	static Sample* CalculateError(Sample* sample1, Sample* sample2);
};