#pragma once
#include <vector>

/// <summary>
/// Essa classe representa uma amostra de chars que pode ser gerada ou carregada de um arquivo
/// </summary>
class Sample
{

public:
	std::vector <float> sample_vector;
	Sample();

	/// <summary>
	/// gera um vetor de chars aleatório com tamanho entre 32 e 512
	/// </summary>
	void GenerateSampleVector(int size);

	/// <summary>
	/// gera um vetor de chars com tamanho entre 32 e 512 na forma de uma senoide
	/// </summary>
	void GenerateSenoidalSampleVector(int size);

	/// <summary>
	/// gera um vetor de char com tamanho entre 32 e 512 na forma de 4 senoides com frequências diferentes combinadas
	/// </summary>
	/// <param name="size"></param>
	void GenerateMultiSenoidalSampleVector(int size);

	/// <summary>
	/// salva o vetor de chars em um arquivo contendo um unsigned int no inicio para identificar o número de amostras
	/// </summary>
	void SaveSample(const char* filename);

	/// <summary>
	/// lê o vetor de chars de um arquivo contendo um unsigned int no inicio para identificar o número de amostras
	/// </summary>
	void LoadSample(const char* filename);
};

