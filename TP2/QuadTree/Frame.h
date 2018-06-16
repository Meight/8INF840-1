#pragma once
#include "quadtree.h"
#include "CImg.h"
using namespace cimg_library;

class Frame
{

public:

	Frame(int red, int green, int blue)
	{
		m_red = red;
		m_green = green;
		m_blue = blue;

		m_size = 1;
		m_width = 1;
		m_height = 1;

	}


	Frame(int grey)
	{
		m_grey = grey;

		m_size = 1;
		m_width = 1;
		m_height = 1;
	}

	Frame()
	{
		m_size = 0;
		m_width = 0;
		m_height = 0;
	}



	
	int getRed() { return m_red; }
	int getGreen() { return m_green; }
	int getBlue() { return m_blue; }

	int getGrey() { return m_grey; }

	int getSize() { return m_size; }
	int getWidth() { return m_width; }
	int getHeight() { return m_height; }

	void setSize(int size) { m_size = size; }
	void setDims(int width, int height) { m_width = width; m_height = height; }

	inline bool isEqual(Frame *Frame);
	inline bool isEqualColor(Frame *frame);
	inline bool isEqualDicho(Frame *frame);
	inline bool isEqualColorDicho(Frame *frame);


private:

	int m_red;
	int m_blue;
	int m_green;

	int m_grey;

	int m_size;
	int m_width;
	int m_height;
};
