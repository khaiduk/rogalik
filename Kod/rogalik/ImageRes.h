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
	 * Kolor obrazka do minimapy
	 */
	sf::Color imgColor(int id);
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
		ROADHOUSE,
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
		CHAR,//MONSTER,
		CHAR0,//DEALER,
		GOLD,
		DEAD,
		ROOF,
		ROOFN,
		WINDOW,
		FURN1A,
		FURN1B,
		FURN2A,
		FURN2B,
		ROOF2,
		ROOFN2,
		WINDOW2,
		TOMB,
		BARREL,
		TREE1,
		DEAD1,
		TREE2,
		DEAD2,
		TREE3,
		BOX,
		WOOD1,
		ROOT,
		STONE1,
		GRASS1,
		FLOWER1,
		FLOWER2,
		NEED,
		TREE4,
		BARREL1,
		FLOOR2,
		FLOOR3,
		FLOOR4,
		WINTER,
		WATER,
		BED,
		NEED1,
		CHAR1,
		CHAR2,
		CHAR3,
		SIT1,
		SIT2,
		NEED3,
		TABLE,

	};
private:
	ImageRes(void){}
	ImageRes(const ImageRes& x){}
	ImageRes& operator=(const ImageRes& x){}

	std::map<int, sf::Image> images;
};

