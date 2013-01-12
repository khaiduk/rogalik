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

sf::Color ImageRes::imgColor(int id)
{
	switch(id)
	{
		case EMPTY: return sf::Color::Black;
		case GRASS: return sf::Color::Green;
		case BRICK:
		case WOOD: return sf::Color::Red;
		case ROAD:
		case ROADHOUSE:
		case DESK:
		case WALL: return sf::Color(130, 130, 130);
		case STAR: return sf::Color::Yellow;
		case DARK_WALL: return sf::Color::Blue;
		case SAND: return sf::Color::Yellow;
		case TREE: return sf::Color::Red;
		case GRZYBY: return sf::Color::Yellow;
		case GORY: return sf::Color(130, 130, 130);
		case FRUIT:  return sf::Color::Green;
		case ROAD2: return sf::Color(130, 130, 130);
		case STONE: return sf::Color(130, 130, 130);
		case GOLD: return sf::Color::Yellow;
		default: return sf::Color::Red;
	}
}

ImageRes& ImageRes::getInstance()
{
	static ImageRes instance;
	return instance;
}