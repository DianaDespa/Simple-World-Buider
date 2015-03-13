// Despa Diana Alexandra 331CA

#pragma once
#include "../Framework/Visual2D.h"
#include "../Framework/Transform3D.h"
#include "../Framework/DrawingWindow.h"

#define PI 3.14159265358979323846

// Tipuri de obiecte ce pot fi plasate pe harta.
enum TileType {
	LAND,
	GRASS,
	WATER,
	ROAD,
	HOUSE,
	MARKET,
	NONE
};

enum Direction {
	LEFT,
	RIGHT
};


// Clasa de baza ce reprezinta elementele hartii(dale).
class Tile
{
protected:
	vector<Object3D *> objects;		// Obiectele ce compun o dala complexa.
public:
	static const int SIZE = 40;		// Dimensiunea unei dale.
	float size_x, size_y, size_z,	// Dimensiunile unui obiect de pa harta.
		start_x, start_z;			// Coordonatele din stanga sus ale obiectului de pus pe harta.
	bool is_near_market,			// Indica daca dala este in aria unei piete.
		is_placeable,				// Indica daca obiectul poate fi plasat.
		highlighted;				// Indica daca obiectul este evidentiat.
	TileType type;					// Tipul obiectului.

public:
	Tile();
	~Tile();

	// Intoarce o instanta a unui obiect avand tipul dat ca parametru.
	static Tile *make_tile(TileType type);	

	// Formeaza transformarea necesara, astfel incat obiectul sa fie plasat pe harta la
	// coordonatele date ca parametru.
	virtual void transform(int x, int z);

	// Adauga obiectele componentele la contextul vizual.
	void add_to_v2d(Visual2D *v2d);

	// Sterge obiectele componente din contextul vizual.
	void remove_from_v2d(Visual2D *v2d);

	// Aplica ultima transformare asupra obiectelor componente.
	void apply_transform();

	// Coloreaza obiectul in rosu.
	void make_red();

	// Evidentiaza obiectul.
	void highlight();

	// Face ca obiectul sa fie afisat fara a fi pus in evidenta.
	void remove_highlight();

	// Schimba tipul terenului.
	void change_type(TileType type);

	// Intoarce coordonata y a obiectului.
	float get_y();
};

