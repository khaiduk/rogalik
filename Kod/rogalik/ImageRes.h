#pragma once
#include <map>
#include <SFML\Graphics.hpp>

/**
 * Zasoby graficzne do u¿ycia jako kafelki i sprites
 */
class ImageRes
{
public:
	/**
	 * £aduje do pamiêci zasoby z pliku
	 * Kafelki z pliku ³adowane s¹ od lewego górnego roguw prawo i w dó³ (podobnie jak siê czyta tekst),
	 * numerowane od idPrefix do idPrefix + size*size - 1
	 * @param filename Plik graficzny zawieraj¹cy kafelki
	 * @param size iloœæ kafelek na wiersz w pliku (tj. w sumie bêdzie size^2 obrazków)
	 * @param idPrefix wartoœæ dodawana do ka¿dego identyfikatora zasobu
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
	 * Szerokoœæ pojedynczej kafelki w pikselach
	 */
	static const int TILESIZE = 32;

	/**
	 * Rozmiary okna
	 */
	static const int WIDTH = 800;
	static const int HEIGHT = 600;

	/**
	 * Identyfikatory wygl¹du kafelków/spritów
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

