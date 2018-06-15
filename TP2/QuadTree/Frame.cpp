#include "Frame.h"

bool Frame::isEqual(Frame *Frame)
{
	if ((this->m_red == Frame->m_red) && (this->m_blue == Frame->m_blue) && (this->m_green == Frame->m_green)) { return true; }
	else { return false; }

}


const char* INPUT_FILENAME = "E:/Cours UQAC/Structures de données avancées/Devoir 2/Fichiers/Exo4/Images/chat.png";

static bool isMonochrome(QuadTree<Frame> * nw, QuadTree<Frame> * ne, QuadTree<Frame> * se, QuadTree<Frame> * sw) {
	return (sw->isLeaf() && nw->isLeaf() & ne->isLeaf() && se->isLeaf() && (sw->value().isEqual(&se->value())) && (sw->value().isEqual(&ne->value())) && (sw->value().isEqual(&nw->value())));
}


QuadTree<Frame>* encodeFrame(int size, int i, int j, CImg<float> image)
{
	if (size == 1)
	{ 
		QuadLeaf<Frame> *leaf = new QuadLeaf<Frame>(Frame(image(i, j, 0), image(i, j, 1), image(i, j, 2), size));
		return leaf;
	}

	int s = size / 2;
	QuadTree<Frame> *sw = encodeFrame(s, i , j+s, image);
	QuadTree<Frame> *nw = encodeFrame(s, i, j, image);
	QuadTree<Frame> *ne = encodeFrame(s, i+s, j , image);
	QuadTree<Frame> *se = encodeFrame(s, i + s, j + s, image);

	if (isMonochrome(nw, ne, se, sw))
	{
		Frame frameleaf = sw->value();
		frameleaf.setSize(frameleaf.getSize() * 2);
		return new QuadLeaf<Frame>(frameleaf);
	}

	return new QuadNode<Frame>(nw, ne, se, sw);
}

CImg<float> decodeFrame(QuadTree<Frame> *quadFrame)
{
	if (quadFrame != NULL)
	{
		if (quadFrame->isLeaf())
		{
			Frame monochromframe = quadFrame->value();
			CImg<float> leafimg(1, 1, 1, 3, monochromframe.getRed(), monochromframe.getGreen(), monochromframe.getBlue());
			leafimg.resize(monochromframe.getSize(), monochromframe.getSize());
			return leafimg;
		}

		else
		{
			CImg<float> nw = decodeFrame(quadFrame->son(0));
			CImg<float> ne = decodeFrame(quadFrame->son(1));
			CImg<float> se = decodeFrame(quadFrame->son(2));
			CImg<float> sw = decodeFrame(quadFrame->son(3));

			nw.append(sw, 'y');
			ne.append(se, 'y');
			nw.append(ne, 'x');

			return nw;
		}
	}
}


int main()
{
	//CImg<float> image(INPUT_FILENAME);
	CImg<float> image("chat.png");

	/*
	float pixvalR = image(10, 10, 0, 0); // read red val at coord 10,10
	float pixvalG = image(10, 10, 0, 1); // read green val at coord 10,10
	float pixvalB = image(10, 10, 0, 2); // read blue val at coord 10,10
	*/

	int height = image.height();
	int width = image.width();

	if (width != height)
		exit(1);


	QuadTree<Frame> *quadimage;
	quadimage = encodeFrame(width, 0, 0, image);


	float x = 5;
	
	CImg<float> newimage = decodeFrame(quadimage);

	newimage.save("newchat.png");


	//display(quadimage);


	
	/*CImg<float> subimage1;

	subimage1 = image.get_crop(0, 0, width / 2 -1, height - 1);
	

	CImg<float> subimage2;

	subimage2 = image.get_crop(width / 2, 0, width-1,  height - 1);

	subimage2.append(subimage1, 'x');

	subimage2.save_png("chatinvers.png");

	CImg<float> subimage3(1,1, 1, 3, 255, 0, 0);

	subimage3.resize(width / 2, height);

	subimage3.append(subimage1, 'x');

	subimage3.save_png("chatrouge.png");*/

	/*for (int i = 0; i < width / 2; i++)
	for (int j = 0; j < width / 2; j++)
	{
	subimage(i, j, 0) = image(i, j, 0);
	subimage(i, j, 1) = image(i, j, 1);
	subimage(i, j, 2) = image(i, j, 2);

	}


	/*image(0, height, 0) = 255;
	image(0, height, 1) = 0;
	image(0, height, 2) = 255;*/


	/*CImgDisplay main_disp(subimage);
	subimage.save_png("chatbis.png");
	float b = 5;*/
}
