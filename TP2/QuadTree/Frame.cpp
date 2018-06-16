#include "Frame.h"

#define MAX_LENGTH 128

bool Frame::isEqualDicho(Frame *frame)
{
	if (this->m_grey == frame->m_grey) { return true; }
	else return false;
}

bool Frame::isEqualColorDicho(Frame *frame)
{
	if ((this->m_red == frame->m_red) && (this->m_blue == frame->m_blue) && (this->m_green == frame->m_green)) { return true; }
	else return false;

}

bool Frame::isEqual(Frame *frame)
{
	if ((this->m_size == 0) || frame->m_size == 0) { return true; }
	else return this->isEqualDicho(frame);
}

bool Frame::isEqualColor(Frame *frame)
{
	if ((this->m_size == 0) || frame->m_size == 0) { return true; }
	else return this->isEqualColorDicho(frame);
}


static bool isMonochrome(QuadTree<Frame> * nw, QuadTree<Frame> * ne, QuadTree<Frame> * se, QuadTree<Frame> * sw) {
	return (sw->isLeaf() && nw->isLeaf() && ne->isLeaf() && se->isLeaf() && (nw->value().isEqual(&se->value())) && (nw->value().isEqual(&ne->value())) && (nw->value().isEqual(&sw->value())));
}

static bool isMonochromeColor(QuadTree<Frame> * nw, QuadTree<Frame> * ne, QuadTree<Frame> * se, QuadTree<Frame> * sw) {
	return (sw->isLeaf() && nw->isLeaf() && ne->isLeaf() && se->isLeaf() && (nw->value().isEqualColor(&se->value())) && (nw->value().isEqualColor(&ne->value())) && (nw->value().isEqualColor(&sw->value())));
}

static bool isMonochromeDicho(QuadTree<Frame> * nw, QuadTree<Frame> * ne, QuadTree<Frame> * se, QuadTree<Frame> * sw) {
	return (sw->isLeaf() && nw->isLeaf() && ne->isLeaf() && se->isLeaf() && (sw->value().isEqualDicho(&se->value())) && (sw->value().isEqualDicho(&ne->value())) && (sw->value().isEqualDicho(&nw->value())));
}

static bool isMonochromeColorDicho(QuadTree<Frame> * nw, QuadTree<Frame> * ne, QuadTree<Frame> * se, QuadTree<Frame> * sw) {
	return (sw->isLeaf() && nw->isLeaf() && ne->isLeaf() && se->isLeaf() && (sw->value().isEqualColorDicho(&se->value())) && (sw->value().isEqualColorDicho(&ne->value())) && (sw->value().isEqualColorDicho(&nw->value())));
}

CImg<int> imagecon;

QuadTree<Frame>* encodeFrameDicho(int size, int i, int j)
{
	if (size == 1)
		return new QuadLeaf<Frame>(Frame(imagecon(i, j)));

	int s = size / 2;

	int js = j + s;
	int is = i + s;

	QuadTree<Frame> *sw = encodeFrameDicho(s, i, js);
	QuadTree<Frame> *nw = encodeFrameDicho(s, i, j);
	QuadTree<Frame> *ne = encodeFrameDicho(s, is, j);
	QuadTree<Frame> *se = encodeFrameDicho(s, is, js);

	if (isMonochromeDicho(nw, ne, se, sw))
	{
		Frame frameleaf = sw->value();
		frameleaf.setSize(size);
		return new QuadLeaf<Frame>(frameleaf);
	}

	return new QuadNode<Frame>(nw, ne, se, sw);
}


QuadTree<Frame>* encodeFrameColorDicho(int size, int i, int j)
{
	if (size == 1)
	{
		return new QuadLeaf<Frame>(Frame(imagecon(i, j, 0), imagecon(i, j, 1), imagecon(i, j, 2)));
	}

	int s = size / 2;
	int is = i + s;
	int js = j + s;

	QuadTree<Frame> *sw = encodeFrameColorDicho(s, i, js);
	QuadTree<Frame> *nw = encodeFrameColorDicho(s, i, j);
	QuadTree<Frame> *ne = encodeFrameColorDicho(s, is, j);
	QuadTree<Frame> *se = encodeFrameColorDicho(s, is, js);

	if (isMonochromeColorDicho(nw, ne, se, sw))
	{
		Frame frameleaf = sw->value();
		frameleaf.setSize(size);
		return new QuadLeaf<Frame>(frameleaf);
	}

	return new QuadNode<Frame>(nw, ne, se, sw);
}

QuadTree<Frame>* encodeFrame(int width, int i, int j, int widthheightdiff)
{
	if ((width == 0) || (width - widthheightdiff == 0))
	{
		return new QuadLeaf<Frame>(Frame());
	}

	if ((width == 1) && (widthheightdiff == 0))
	{
		return new QuadLeaf<Frame>(Frame(imagecon(i, j)));
	}

	QuadTree<Frame> *sw;
	QuadTree<Frame> *nw;
	QuadTree<Frame> *ne;
	QuadTree<Frame> *se;

	if (width == 1)
	{
		sw = encodeFrame(1, i, j + 1, 0);
		nw = encodeFrame(1, i, j, 0);
		ne = encodeFrame(0, i + 1, j, 0);
		se = encodeFrame(0, i + 1, j + 1, 0);
	}
	else
	{
		if (width - widthheightdiff == 1)
		{
			sw = encodeFrame(0, i, j + 1, 0);
			nw = encodeFrame(1, i, j, 0);
			ne = encodeFrame(1, i + 1, j, 0);
			se = encodeFrame(0, i + 1, j + 1, 0);
		}
		else
		{
			int height = width - widthheightdiff;
			int w = width / 2;
			int h = height / 2;
			int m = width % 2;
			int n = height % 2;
			int wm = w + m;
			int hn = h + n;

			sw = encodeFrame(wm, i, j + hn, wm - h);
			nw = encodeFrame(wm, i, j, wm - hn);
			ne = encodeFrame(w, i + wm, j, w - hn);
			se = encodeFrame(w, i + wm, j + hn, w - h);
		}
	}

	if (isMonochrome(nw, ne, se, sw))
	{
		Frame frameleaf = nw->value();
		frameleaf.setDims(width, width - widthheightdiff);
		return new QuadLeaf<Frame>(frameleaf);
	}

	return new QuadNode<Frame>(nw, ne, se, sw);
}


QuadTree<Frame>* encodeFrameColor(int width, int i, int j, int widthheightdiff)
{
	if ((width == 0) || (width-widthheightdiff == 0) )
	{
		return new QuadLeaf<Frame>(Frame());
	}

	if ((width == 1) && (widthheightdiff==0) )
	{
		return new QuadLeaf<Frame>(Frame(imagecon(i, j, 0), imagecon(i, j, 1), imagecon(i, j, 2)));
	}

	QuadTree<Frame> *sw;
	QuadTree<Frame> *nw;
	QuadTree<Frame> *ne;
	QuadTree<Frame> *se;

	if (width == 1)
	{
		sw = encodeFrameColor(1, i, j + 1, 0);
		nw = encodeFrameColor(1, i, j, 0);
		ne = encodeFrameColor(0, i + 1, j, 0);
		se = encodeFrameColor(0, i + 1, j + 1, 0);
	}
	else
	{
		if (width - widthheightdiff == 1)
		{
			sw = encodeFrameColor(0, i, j + 1, 0);
			nw = encodeFrameColor(1, i, j, 0);
			ne = encodeFrameColor(1, i + 1, j, 0);
			se = encodeFrameColor(0, i + 1, j + 1, 0);
		}
		else
		{
			int height = width - widthheightdiff;
			int w = width / 2;
			int h = height / 2;
			int m = width % 2;
			int n = height % 2;
			int wm = w + m;
			int hn = h + n;

			sw = encodeFrameColor(wm, i, j + hn, wm - h);
			nw = encodeFrameColor(wm, i, j, wm - hn);
			ne = encodeFrameColor(w, i + wm, j, w - hn);
			se = encodeFrameColor(w, i + wm, j + hn, w - h);
		}
	}

	if (isMonochromeColor(nw, ne, se, sw))
	{
		Frame frameleaf = nw->value();
		frameleaf.setDims(width, width-widthheightdiff);
		return new QuadLeaf<Frame>(frameleaf);
	}

	return new QuadNode<Frame>(nw, ne, se, sw);
}

CImg<int> decodeFrameDicho(QuadTree<Frame> *quadFrame)
{
	if (quadFrame != NULL)
	{
		if (quadFrame->isLeaf())
		{
			Frame monochromframe = quadFrame->value();
			int size = monochromframe.getSize();
			CImg<int> leafimg(1, 1, 1, 1, monochromframe.getGrey());
			for (int k = 0; k < log2(size); k++)
			{
				leafimg.resize_doubleXY();
			}
			return leafimg;
		}

		else
		{
			CImg<int> nw = decodeFrameDicho(quadFrame->son(0));
			CImg<int> ne = decodeFrameDicho(quadFrame->son(1));
			CImg<int> se = decodeFrameDicho(quadFrame->son(2));
			CImg<int> sw = decodeFrameDicho(quadFrame->son(3));

			nw.append(sw, 'y');
			ne.append(se, 'y');
			nw.append(ne, 'x');

			return nw;
		}
	}
}

CImg<int> decodeFrameColorDicho(QuadTree<Frame> *quadFrame)
{
	if (quadFrame != NULL)
	{
		if (quadFrame->isLeaf())
		{
			Frame monochromframe = quadFrame->value();
			int size = monochromframe.getSize();
			CImg<int> leafimg(1, 1, 1, 3, monochromframe.getRed(), monochromframe.getGreen(), monochromframe.getBlue());
			for (int k = 0; k < log2(size); k++)
			{
				leafimg.resize_doubleXY();
			}
			return leafimg;
		}

		else
		{
			CImg<int> nw = decodeFrameColorDicho(quadFrame->son(0));
			CImg<int> ne = decodeFrameColorDicho(quadFrame->son(1));
			CImg<int> se = decodeFrameColorDicho(quadFrame->son(2));
			CImg<int> sw = decodeFrameColorDicho(quadFrame->son(3));

			nw.append(sw, 'y');
			ne.append(se, 'y');
			nw.append(ne, 'x');

			return nw;
		}
	}
}


CImg<int> decodeFrameColor(QuadTree<Frame> *quadFrame)
{
	if (quadFrame != NULL)
	{
		if (quadFrame->isLeaf())
		{
			Frame monochromframe = quadFrame->value();
			int width = monochromframe.getWidth();
			int height = monochromframe.getHeight();
			if (width == 0)
			{
				CImg<int> leafimg;
				return leafimg;
			}
			CImg<int> leafimg(1, 1, 1, 3, monochromframe.getRed(), monochromframe.getGreen(), monochromframe.getBlue());
			for (int k = 0; k < std::ceil(log2(std::max(width, height))); k++)
			{
				leafimg.resize_doubleXY();
			}
			leafimg.crop(0, 0, width-1, height-1);
			return leafimg;
		}

		else
		{
			CImg<int> nw = decodeFrameColor(quadFrame->son(0));
			CImg<int> ne = decodeFrameColor(quadFrame->son(1));
			CImg<int> se = decodeFrameColor(quadFrame->son(2));
			CImg<int> sw = decodeFrameColor(quadFrame->son(3));

			nw.append(sw, 'y');
			ne.append(se, 'y');
			nw.append(ne, 'x');

			return nw;
		}
	}
}


CImg<int> decodeFrame(QuadTree<Frame> *quadFrame)
{
	if (quadFrame != NULL)
	{
		if (quadFrame->isLeaf())
		{
			Frame monochromframe = quadFrame->value();
			int width = monochromframe.getWidth();
			int height = monochromframe.getHeight();
			if (width == 0)
			{
				CImg<int> leafimg;
				return leafimg;
			}
			CImg<int> leafimg(1, 1, 1, 1, monochromframe.getGrey());
			for (int k = 0; k < std::ceil(log2(std::max(width, height))); k++)
			{
				leafimg.resize_doubleXY();
			}
			leafimg.crop(0, 0, width - 1, height - 1);
			return leafimg;
		}

		else
		{
			CImg<int> nw = decodeFrame(quadFrame->son(0));
			CImg<int> ne = decodeFrame(quadFrame->son(1));
			CImg<int> se = decodeFrame(quadFrame->son(2));
			CImg<int> sw = decodeFrame(quadFrame->son(3));

			nw.append(sw, 'y');
			ne.append(se, 'y');
			nw.append(ne, 'x');

			return nw;
		}
	}
}

//CImg<int> imagecon("chat.png");


int main(int argc, char* argv[])
{
	std::cout << "Specify the name of the image to encode:";
	char* filename = new char[MAX_LENGTH];
	std::cin >> filename;

	imagecon = CImg<int>(filename);

	std::cout << "Specify the name of the file where the decoded image will be saved:";
	char* filesave = new char[MAX_LENGTH];
	std::cin >> filesave;


	int height = imagecon.height();
	int width = imagecon.width();

	QuadTree<Frame> *quadimage;
	CImg<int> newimage;

	if ((width == height) && (log2(height) == floor(log2(height))))
	{
		if (imagecon.spectrum() == 1)
		{
			std::cout << "starting encode grey dicho\n";
			quadimage = encodeFrameDicho(width, 0, 0);
			std::cout << "finished encode grey dicho\n";

			std::cout << "starting decode grey dicho\n";
			newimage = decodeFrameDicho(quadimage);
			std::cout << "finished decode grey dicho\n";
		}

		else
		{
			std::cout << "starting encode color dicho\n";
			quadimage = encodeFrameColorDicho(width, 0, 0);
			std::cout << "finished encode color dicho\n";

			std::cout << "starting decode color dicho\n";
			newimage = decodeFrameColorDicho(quadimage);
			std::cout << "finished decode color dicho\n";
		}
	}
	else
	{
		if (imagecon.spectrum() == 1)
		{
			std::cout << "starting encode\n";
			quadimage = encodeFrame(width, 0, 0, width - height);
			std::cout << "finished encode\n";

			std::cout << "starting decode\n";
			newimage = decodeFrame(quadimage);
			std::cout << "finished decode\n";
		}
		else
		{
			std::cout << "starting encode color\n";
			quadimage = encodeFrameColor(width, 0, 0, width - height);
			std::cout << "finished encode color\n";

			std::cout << "starting decode color\n";
			newimage = decodeFrameColor(quadimage);
			std::cout << "finished decode color\n";
		}
	}

	newimage.save(filesave);
	std::cout << "Decoded image saved.";

}
