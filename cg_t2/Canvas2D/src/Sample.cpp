#include "Sample.h"

Sample::Sample()
{
	sample_vector = std::vector<float>();
}

bool CheckRange(int value, int min, int max)
{
	return (value >= min && value <= max);
}

void Sample::GenerateSampleVector(int size)
{
	if (!CheckRange(size, 32, 512))
	{
		return;
	}

	sample_vector.clear();

	for (int i = 0; i < size; i++)
	{
		sample_vector.push_back(rand() % 255 - 128);
	}
}

void Sample::GenerateSenoidalSampleVector(int size)
{
	if (!CheckRange(size, 32, 512))
	{
		return;
	}

	sample_vector.clear();
	float offset = (float) 16 / size;

	for (int i = 0; i < size; i++)
	{
		sample_vector.push_back((int)(sin(i * offset) * 127));
	}
}

void Sample::GenerateMultiSenoidalSampleVector(int size)
{
	if (!CheckRange(size, 32, 512))
	{
		return;
	}

	sample_vector.clear();

	int f1 = rand() % 8 + 1;
	int f2 = rand() % 8 + 1;
	int f3 = rand() % 8 + 1;
	int f4 = rand() % 8 + 1;

	float offset = (float)4 / size;

	for (int i = 0; i < size; i++)
	{
		int value = (int)(sin(i * f1 * offset + f1) * 127) +
					(int)(sin(i * f2 * offset + f2) * 127) +
					(int)(sin(i * f3 * offset + f3) * 127) +
					(int)(sin(i * f4 * offset + f4) * 127);

		value /= 4;
		sample_vector.push_back(value);
	}
}

void Sample::SaveSample(const char* filename)
{
	FILE* file;
	fopen_s(&file, filename, "wb");
	if (file == NULL)
	{
		return;
	}
	unsigned int size = sample_vector.size();
	fwrite(&size, sizeof(unsigned int), 1, file);
	for (float f : sample_vector)
	{
		char c = (char)f;
		fwrite(&c, sizeof(char), 1, file);
	}
	fclose(file);
}

void Sample::LoadSample(const char* filename)
{
	FILE* file;
	fopen_s(&file, filename, "rb");

	if (file == NULL)
	{
		return;
	}
	unsigned int size;
	fread(&size, sizeof(unsigned int), 1, file);

	if (!CheckRange(size, 32, 512))
	{
		return;
	}

	sample_vector.clear();
	sample_vector.resize(size);

	for (int i = 0; i < size; i++)
	{
		char c;
		fread(&c, sizeof(char), 1, file);
		sample_vector[i] = c;
	}

	fclose(file);
}