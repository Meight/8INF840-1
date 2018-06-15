#include "Frame.h"
bool Frame::isEqual(Frame *frame)
{
	if (this->m_grey == frame->m_grey) { return true; }
	else return false;
}

bool Frame::isEqualColor(Frame *frame)
{
	if ((this->m_red == frame->m_red) && (this->m_blue == frame->m_blue) && (this->m_green == frame->m_green)) { return true; }
	else return false;

}


static bool isMonochrome(QuadTree<Frame> * nw, QuadTree<Frame> * ne, QuadTree<Frame> * se, QuadTree<Frame> * sw) {
	return (sw->isLeaf() && nw->isLeaf() && ne->isLeaf() && se->isLeaf() && (sw->value().isEqual(&se->value())) && (sw->value().isEqual(&ne->value())) && (sw->value().isEqual(&nw->value())));
}

static bool isMonochromeColor(QuadTree<Frame> * nw, QuadTree<Frame> * ne, QuadTree<Frame> * se, QuadTree<Frame> * sw) {
	return (sw->isLeaf() && nw->isLeaf() && ne->isLeaf() && se->isLeaf() && (sw->value().isEqualColor(&se->value())) && (sw->value().isEqualColor(&ne->value())) && (sw->value().isEqualColor(&nw->value())));
}

CImg<int> imagecon("soleil.png");

QuadTree<Frame>* encodeFrame(int size, int i, int j)
{
	//std::cout << "encode\n";

	if (size == 1)
		return new QuadLeaf<Frame>(Frame(imagecon(i, j), size));

	int s = size / 2;

	int js = j + s;
	int is = i + s;

	QuadTree<Frame> *sw = encodeFrame(s, i, js);
	QuadTree<Frame> *nw = encodeFrame(s, i, j);
	QuadTree<Frame> *ne = encodeFrame(s, is, j);
	QuadTree<Frame> *se = encodeFrame(s, is, js);

	if (isMonochrome(nw, ne, se, sw))
	{
		Frame frameleaf = sw->value();
		frameleaf.setSize(size);
		return new QuadLeaf<Frame>(frameleaf);
		//return new QuadLeaf<Frame>(sw->value().setSize(sw->value().getSize()));
	}

	return new QuadNode<Frame>(nw, ne, se, sw);
}


QuadTree<Frame>* encodeFrameColor(int size, int i, int j)
{
	//std::cout << "encode\n";

	if (size == 1)
	{
		return new QuadLeaf<Frame>(Frame(imagecon(i, j, 0), imagecon(i, j, 1), imagecon(i, j, 2), size));
	}

	int s = size / 2;
	int is = i + s;
	int js = j + s;

	QuadTree<Frame> *sw = encodeFrameColor(s, i, js);
	QuadTree<Frame> *nw = encodeFrameColor(s, i, j);
	QuadTree<Frame> *ne = encodeFrameColor(s, is, j);
	QuadTree<Frame> *se = encodeFrameColor(s, is, js);

	if (isMonochromeColor(nw, ne, se, sw))
	{
		Frame frameleaf = sw->value();
		frameleaf.setSize(size);
		return new QuadLeaf<Frame>(frameleaf);
		//return new QuadLeaf<Frame>(sw->value().setSize(s));
	}

	return new QuadNode<Frame>(nw, ne, se, sw);
}

CImg<int> decodeFrame(QuadTree<Frame> *quadFrame)
{
	//std::cout << "decode\n";

	if (quadFrame != NULL)
	{
		if (quadFrame->isLeaf())
		{
			Frame monochromframe = quadFrame->value();
			//utiliser fill a la place de resize?
			CImg<int> leafimg(1, 1, 1, 1, monochromframe.getGrey());
			leafimg.resize(monochromframe.getSize(), monochromframe.getSize());
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

CImg<int> decodeFrameColor(QuadTree<Frame> *quadFrame)
{
	//std::cout << "decode\n";

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



int main()
{
	//CImg<int> image(INPUT_FILENAME);
	/*CImg<int> image("tableau.png");

	int height = image.height();
	int width = image.width();

	if (width != height)
		exit(1);


	if (log2(height) != floor(log2(height)))
		exit(2);*/

	//ajouter demande de fichier
	//ajouter demande de nom de fichier de sauvegarde
	//gerer images non puissance de 2

	int width = imagecon.width();

	if (imagecon.spectrum() == 1)
	{
		QuadTree<Frame> *quadimage;
		quadimage = encodeFrame(width, 0, 0);

		CImg<int> newimage = decodeFrame(quadimage);
		newimage.save("newtableau.png");
	}

	else
	{
		QuadTree<Frame> *quadimage;
		std::cout << "starting encode\n";
		quadimage = encodeFrameColor(width, 0, 0);


		std::cout << "starting decode\n";
		CImg<int> newimage = decodeFrameColor(quadimage);
		newimage.save("newsoleil.png");
	}


	int x = 4;

	/*CImg<int> subimage1;
	subimage1 = image.get_crop(0, 0, width / 2 -1, height - 1);

	CImg<int> subimage2;
	subimage2 = image.get_crop(width / 2, 0, width-1,  height - 1);
	subimage1.append(subimage2, 'x');
	subimage1.save_png("chatreconstruit.png");*/

	/*image.save_png("savechat.png", 24);*/	


}
