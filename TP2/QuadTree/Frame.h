#pragma once
#include "quadtree.h"
#include "CImg.h"
using namespace cimg_library;

class Frame
{

public:

	Frame(float red, float green, float blue, int size)
	{
		m_red = red;
		m_green = green;
		m_blue = blue;

		m_size = size;

	}
	
	float getRed() { return m_red; }

	float getGreen() { return m_green; }
	float getBlue() { return m_blue; }
	int getSize() { return m_size; }

	void setSize(int size) { m_size = size; }

	static QuadTree<Frame>* encodeFrame(int size, int i, int j, CImg<float> image);

	bool isEqual(Frame *Frame);


private:

	float m_grey;

	float m_red;
	float m_blue;
	float m_green;

	int m_size;


};
