#pragma once
#include <fstream>
#include <string>
using namespace std;

class Data
{
	float x, y, z; //נאחלונû עמלמדנאללû
    int width, height, depth;
	short* data, min, max;
public:
	short getMin()
	{
		return min;
	}

	short getMax()
	{
		return max;
	}

	int getWidth()
	{
		return width;
	}

	int getHeight()
	{
		return height;
	}

	int getDepth()
	{
		return depth;
	}

void ReadFile(string fn)
	{
		ifstream istr(fn, ios::binary);
		istr.read((char*)&x, sizeof(float));
		istr.read((char*)&y, sizeof(float));
		istr.read((char*)&z, sizeof(float));
		istr.read((char*)&width, sizeof(int));
		istr.read((char*)&height, sizeof(int));
		istr.read((char*)&depth, sizeof(int));

		int size = width*height*depth;
		data = new short[size];
		min = SHRT_MAX;
		max = SHRT_MIN;
		for (int i = 0; i < size; i++)
		{
			istr.read((char*)(data + i), sizeof(short));
			if (data[i] > max)
				max = data[i];
			if (data[i] < min)
				min = data[i];
		}
	}

	short operator[](int i)
	{
		return data[i];
	}
};
