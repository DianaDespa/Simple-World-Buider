// Despa Diana Alexandra 331CA

#pragma once
#include "../Framework/Rectangle2d.h"
#include "EditPanel.h"
#include "House.h"
#include "Market.h"
#include "Road.h"
#include <algorithm>
#include <set>

// Clasa folosita pentru a compara obiectele in functie de pozitia lor pe harta: cele care au suma
// coordonatelor pe harta mai mare sunt plasate ultimele in contextul vizual, adica mai in fata.
class TileComparator
{
	int size;
public:
	TileComparator(const int& size_param = 0)
	{
		size = size_param;
	}
	bool operator() (Tile *lhs, Tile *rhs)
	{
		int xl = lhs->start_x, zl = lhs->start_z,
			xr = rhs->start_x, zr = rhs->start_z;
		if (lhs->type == HOUSE || lhs->type == MARKET) {
			int max_size = max(lhs->size_x, lhs->size_z);
			for (int i = 0; i < max_size; ++i)
				for (int j = 0; j < max_size; ++j)
					if (((Building *)lhs)->blueprint[i][j]) {
						xl = j + lhs->start_x;
						zl = i + lhs->start_z;
					}
		}

		if (rhs->type == HOUSE || rhs->type == MARKET) {
			int max_size = max(rhs->size_x, rhs->size_z);
			for (int i = 0; i < max_size; ++i)
				for (int j = 0; j < max_size; ++j)
					if (((Building *)rhs)->blueprint[i][j]) {
						xr = j + rhs->start_x;
						zr = i + rhs->start_z;
					}
		}
		return (xr + zr) < (xl + zl);
	}
};

class World
{
private:
	EditPanel *edit_panel;								// Panou editare.
	Visual2D *v2d_terrain, *v2d_buildings, *v2d_temp;	// Contexte vizuale.
	int size,											// Dimensiune harta.
		last_highlighted_x, last_highlighted_z;			// Coordonatele ultimei dale evidentiate.
	vector<vector<Tile *>> grid;						// Matricea de obiecte ce reprezinta harta.
	vector<House *> houses;								// Casele de pe harta.
	vector<Market *> markets;							// Pietele de pe harta.
	vector<Tile *> object_container;					// Toate obiectele de pe harta.
	vector<vector<bool>> visited_roads;					// Matrice ce tine evidenta drumurilor vizitate.
	bool rotated;										// Indica daca ultimul obiect de pe harta a fost rotit.

public:
	int last_placed_x, last_placed_z;					// Coordonate ultimului obiect selectat.
	Tile *last_placed;									// Ultimul obiect selectat.

	World(int size, EditPanel *edit_panel, Visual2D *v2d_terrain, Visual2D *v2d_buildings, Visual2D *v2d_temp);
	~World();

	// Deseneaza terenul initial.
	void draw(Visual2D *v2d_grid);
	// Evidentiaza dala de la coordonatele date ca parametru de pe harta, simuland cursorul.
	void highlight(int x, int z);
	// Inlatura efectul de cursor.
	void remove_highlight(int x, int z);
	// Sterge obiectul de la coordonatele date ca parametrii de pe harta.
	TileType erase(int x, int z);
	// Plaseaza ultimul obiect selectat pe harta.
	void place(Visual2D *v2d_temp);
	// Determina daca obiectul tile poate fi plasat la coordonatele x, z.
	void determine_placeable(int x, int z, Building *tile);
	// Muta obiectul cu indicele choice din panou pe harta, cu scopul de a fi plasat.
	void try_place(int x, int z, int choice);
	// Roteste obiectul de la coordonatele x, z in directia dir.
	void rotate(Direction dir, int x, int z);
	// Pune in evidenta zona de acoperire a pietei m.
	void highlight_market(Market *m);
	// Pune in evidenta ariile de acoperire ale tuturor pietelor.
	void highlight_markets();
	// Nu pune in evidenta ariile de acoperire ale tuturor pietelor.
	void remove_highlight_markets();
	// Verifica daca casa h este conectata de piata.
	bool has_road(House *h);
	// Verifica daca exista drum de la pozitia x, z la o piata.
	bool check_road(int z, int x);
	// Verifica toate casele daca sunt conectate de piete.
	void update_houses();
};