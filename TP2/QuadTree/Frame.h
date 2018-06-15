#pragma once
#include "quadtree.h"
#include "CImg.h"
using namespace cimg_library;

class Frame
{

public:

	Frame(int red, int green, int blue, int m_size /*int width, int height*/)
	{
		m_red = red;
		m_green = green;
		m_blue = blue;

		//bool is_grey = false;

		/*m_width = width;
		m_height = height;*/

	}

	Frame(int grey, int size)
	{
		m_grey = grey;
		m_size = size;
		//is_grey = true;
	}
	
	int getRed() { return m_red; }
	int getGreen() { return m_green; }
	int getBlue() { return m_blue; }

	int getGrey() { return m_grey; }
	//bool isGrey() { return is_grey; }

	int getSize() { return m_size; }
	//int getWidth() { return m_width; }
	//int getheight() { return m_height; }

	void setSize(int size) { m_size = size; }

	inline bool isEqual(Frame *Frame);
	inline bool isEqualColor(Frame *frame);


private:

	int m_red;
	int m_blue;
	int m_green;

	int m_grey;
	//bool is_grey;

	int m_size;
	//int m_width;
	//int m_height;


};
