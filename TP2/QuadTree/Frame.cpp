#include "Frame.h"
#include <thread>
#include <future>

bool Frame::isEqual(Frame *frame)
{
	if (frame->isGrey())
	{
		if (this->m_grey == frame->m_grey) { return true; }
		else return false;
	}
	else
	{
		if ((this->m_red == frame->m_red) && (this->m_blue == frame->m_blue) && (this->m_green == frame->m_green)) { return true; }
		else return false; 
	}

}


static bool isMonochrome(QuadTree<Frame> * nw, QuadTree<Frame> * ne, QuadTree<Frame> * se, QuadTree<Frame> * sw) {
	return (sw->isLeaf() && nw->isLeaf() & ne->isLeaf() && se->isLeaf() && (sw->value().isEqual(&se->value())) && (sw->value().isEqual(&ne->value())) && (sw->value().isEqual(&nw->value())));
}


QuadTree<Frame>* encodeFrame(int size, int i, int j, CImg<float> image)
{
	std::cout << "encode\n";

	if (size == 1)
	{ 
		QuadLeaf<Frame> *leaf;
		if (image.spectrum() == 3)
			leaf = new QuadLeaf<Frame>(Frame(image(i, j, 0), image(i, j, 1), image(i, j, 2), size));
		else
			leaf = new QuadLeaf<Frame>(Frame(image(i, j), size));
		return leaf;
	}

	int m = size % 2;
	int s = size / 2;

	/*auto futuresw = std::thread(encodeFrame, s, i, j + s, image);
	auto futurenw = std::thread(encodeFrame, s, i, j , image);
	auto futurene = std::thread(encodeFrame, s, i+s, j , image);
	auto futurese = std::thread(encodeFrame, s, i+s, j + s, image);


	QuadTree<Frame> *sw = futuresw.get();
	QuadTree<Frame> *nw = futurenw.get();
	QuadTree<Frame> *ne = futurene.get();
	QuadTree<Frame> *se = futurese.get();*/

	QuadTree<Frame> *sw = encodeFrame(s, i, j + s, image);
	QuadTree<Frame> *nw = encodeFrame(s, i, j, image);
	QuadTree<Frame> *ne = encodeFrame(s, i+s, j , image);
	QuadTree<Frame> *se = encodeFrame(s, i + s, j + s, image);

	if (isMonochrome(nw, ne, se, sw))
	{
		Frame frameleaf = sw->value();
		frameleaf.setSize(frameleaf.getSize() + se->value().getSize());
		return new QuadLeaf<Frame>(frameleaf);
	}

	return new QuadNode<Frame>(nw, ne, se, sw);
}

CImg<float> decodeFrame(QuadTree<Frame> *quadFrame)
{
	std::cout << "decode\n";

	if (quadFrame != NULL)
	{
		if (quadFrame->isLeaf())
		{
			Frame monochromframe = quadFrame->value();
			if (monochromframe.isGrey())
			{
				CImg<float> leafimg(1, 1, 1, 1, monochromframe.getGrey());
				leafimg.resize(monochromframe.getSize(), monochromframe.getSize());
				return leafimg;
			}
			else
			{
				CImg<float> leafimg(1, 1, 1, 3, monochromframe.getRed(), monochromframe.getGreen(), monochromframe.getBlue());
				leafimg.resize(monochromframe.getSize(), monochromframe.getSize());
				return leafimg;
			}
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
	CImg<float> image("soleil.png");

	int height = image.height();
	int width = image.width();

	if (width != height)
		exit(1);

	QuadTree<Frame> *quadimage;
	quadimage = encodeFrame(width, 0, 0, image);


	float x = 5;
	
	CImg<float> newimage = decodeFrame(quadimage);

	newimage.save("newsoleil.png");

	/*CImg<float> subimage1;
	subimage1 = image.get_crop(0, 0, width / 2 -1, height - 1);

	CImg<float> subimage2;
	subimage2 = image.get_crop(width / 2, 0, width-1,  height - 1);
	subimage1.append(subimage2, 'x');
	subimage1.save_png("chatreconstruit.png");*/

	/*image.save_png("savechat.png", 24);*/	


}
