#pragma once
#include <map>
#include <SFML\Graphics.hpp>

/**
 * Zasoby graficzne do u�ycia jako kafelki i sprites
 */
class ImageRes
{
public:
	/**
	 * �aduje do pami�ci zasoby z pliku
	 * Kafelki z pliku �adowane s� od lewego g�rnego roguw prawo i w d� (podobnie jak si� czyta tekst),
	 * numerowane od idPrefix do idPrefix + size*size - 1
	 * @param filename Plik graficzny zawieraj�cy kafelki
	 * @param size ilo�� kafelek na wiersz w pliku (tj. w sumie b�dzie size^2 obrazk�w)
	 * @param idPrefix warto�� dodawana do ka�dego identyfikatora zasobu
	 */
	void loadImages(const std::string& filename, int size = 8, int idPrefix = 0);
	/**
	 * Pobiera obrazek o zadanym identyfikatorze
	 */
	sf::Image& getImage(int id);
	/**
	 * Pobranie instancji tej klasy (singleton)
	 */
	static ImageRes& getInstance();
	/**
	 * Szeroko�� pojedynczej kafelki w pikselach
	 */
	static const int TILESIZE = 32;

	/**
	 * Rozmiary okna
	 */
	static const int WIDTH = 800;
	static const int HEIGHT = 600;

	/**
	 * Identyfikatory wygl�du kafelk�w/sprit�w
	 */
	enum Tileset {
		EMPTY = 0,
		HERO,
		GRASS,
		BRICK,
		WOOD,
		ROAD,
		FURNITURE,
		DESK,
		WALL,
		STAR,
		DARK_WALL,
		SAND,
		TREE,
		GRZYBY,
		GORY,
		FRUIT,
		ROAD2,
		STONE,
		MONSTER,
		DEALER,
		GOLD
	};
private:
	ImageRes(void){}
	ImageRes(const ImageRes& x){}
	ImageRes& operator=(const ImageRes& x){}

	std::map<int, sf::Image> images;
};

