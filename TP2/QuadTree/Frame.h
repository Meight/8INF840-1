#pragma once
#include "quadtree.h"
#include "CImg.h"
using namespace cimg_library;

class Frame
{

public:

	Frame(float red, float green, float blue, int m_size /*int width, int height*/)
	{
		m_red = red;
		m_green = green;
		m_blue = blue;

		bool is_grey = false;

		/*m_width = width;
		m_height = height;*/

	}

	Frame(float grey, int size)
	{
		m_grey = grey;
		m_size = size;
		is_grey = true;
	}
	
	float getRed() { return m_red; }
	float getGreen() { return m_green; }
	float getBlue() { return m_blue; }

	float getGrey() { return m_grey; }
	bool isGrey() { return is_grey; }

	int getSize() { return m_size; }
	int getWidth() { return m_width; }
	int getheight() { return m_height; }

	void setSize(int size) { m_size = size; }

	bool isEqual(Frame *Frame);


private:

	float m_red;
	float m_blue;
	float m_green;

	float m_grey;
	bool is_grey;

	int m_size;
	int m_width;
	int m_height;


};
