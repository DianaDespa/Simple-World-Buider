// Despa Diana Alexandra 331CA

#pragma once
#include "Tile.h"
#include <cmath>

// Clasa ce reprezinta obiectele ce pot fi plasate pe harta.
class Building : public Tile
{
public:
	vector<vector<bool>> blueprint;	// "Semnatura" obiectului - 
	int rotation;					// Rotatia obiectului.
public:
	Building();
	~Building();
	
	// Creeaza o noua intanta care este copia obiectului dat ca parametru.
	static Building *copy(Building *b);

	// Formeaza transformarea necesara, astfel incat obiectul sa fie plasat pe harta la
	// coordonatele date ca parametru.
	virtual void transform(int x, int z);

	// Roteste obiectul intr-o anumita directie astfel incat el sa se afle la coordonatele
	// date ca parametru pe harta.
	void rotate(Direction dir, int x, int z);
};

