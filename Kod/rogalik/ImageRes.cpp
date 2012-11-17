#include "ImageRes.h"

void ImageRes::loadImages(const std::string& filename, int size, int idPrefix)
{
	sf::Image img;
	img.LoadFromFile(filename);

	for(int h=0;h<size;h++)
		for(int w=0;w<size;w++)
		{
			images[idPrefix + w + h*size] = sf::Image(TILESIZE, TILESIZE);
			images[idPrefix + w + h*size].Copy(img, 0, 0, sf::IntRect(w*TILESIZE, h*TILESIZE, (w+1)*TILESIZE, (h+1)*TILESIZE));
			images[idPrefix + w + h*size].SetSmooth(false);
		}
}

sf::Image& ImageRes::getImage(int id)
{
	return images[id];
}

ImageRes& ImageRes::getInstance()
{
	static ImageRes instance;
	return instance;
}