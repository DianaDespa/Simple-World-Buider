// Despa Diana Alexandra 331CA

#include "World.h"


World::World(int size, EditPanel *edit_panel, Visual2D *v2d_terrain, Visual2D *v2d_buildings, Visual2D *v2d_temp)
{
	this->size = size;
	this->edit_panel = edit_panel;
	this->v2d_terrain = v2d_terrain;
	this->v2d_buildings = v2d_buildings;
	this->v2d_temp = v2d_temp;
	last_highlighted_x = 0;
	last_highlighted_z = 0;
	last_placed = new Tile();
	last_placed_x = -1;
	last_placed_z = -1;
	grid = vector<vector<Tile *>>(size, vector<Tile *>(size));

	edit_panel->add(Tile::make_tile(LAND));
	edit_panel->add(Tile::make_tile(GRASS));
	edit_panel->add(Tile::make_tile(WATER));
	edit_panel->add(Tile::make_tile(ROAD));
	edit_panel->add(Tile::make_tile(HOUSE));
	edit_panel->add(Tile::make_tile(MARKET));
	rotated = false;
}


World::~World()
{
}

void World::draw(Visual2D *v2d_grid)
{
	Tile *tile;

	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			tile = new Tile();
			tile->start_x = j;
			tile->start_z = i;
			tile->add_to_v2d(v2d_grid);
			tile->transform(j, i);
			tile = Tile::make_tile(GRASS);
			tile->add_to_v2d(v2d_terrain);
			tile->transform(j, i);
			grid[i][j] = tile;
		}
	}
	grid[0][0]->highlight();
}

void World::highlight(int x, int z)
{
	if (x != last_highlighted_x || z != last_highlighted_z) {
		grid[z][x]->highlight();
		if (last_highlighted_x >= 0 && last_highlighted_z >= 0) 
			grid[last_highlighted_z][last_highlighted_x]->remove_highlight();
		last_highlighted_x = x;
		last_highlighted_z = z;
	}
}

void World::remove_highlight(int x, int z)
{
	if (!grid[z][x]->is_near_market)
		grid[z][x]->remove_highlight();
	last_highlighted_x = -1;
	last_highlighted_z = -1;
}

// Functia intoarce tipul obiectului sters pentru a putea fi folosita si la editarea unui obiect
// deja plasat.
TileType World::erase(int j, int i)
{
	// Pot sterge doar case, piete si drumuri.
	if (grid[i][j]->type == HOUSE || grid[i][j]->type == MARKET || grid[i][j]->type == ROAD) {
		int max_size = max(grid[i][j]->size_z, grid[i][j]->size_x),
			x = grid[i][j]->start_x,
			z = grid[i][j]->start_z;
		Building *b = (Building *)grid[i][j];

		// Inlocuiesc toate dalele care formau obiectul cu teren, in functie de blueprint(semnatura),
		// sterg obiectul din contextul vizual si adaug noile dale.
		for (int i = 0; i < max_size; ++i)
			for (int j = 0; j < max_size; ++j)
				if (b->blueprint[i][j])
					if (i + z >= 0 && j + x >= 0 && i + z < size && j + x < size) {
						grid[i + z][j + x]->remove_from_v2d(v2d_buildings);
						grid[i + z][j + x] = Tile::make_tile(LAND);
						grid[i + z][j + x]->transform(j + x, i + z);
						grid[i + z][j + x]->add_to_v2d(v2d_terrain);
					}

		// Sterg obiectul din colectiile de care apartine.
		int n = 0;
		if (!object_container.empty()) {
			while (n < object_container.size() && object_container[n] != b)
				n++;
			object_container.erase(object_container.begin() + n);
		}
		if (b->type == HOUSE && !houses.empty()) {
			n = 0;
			while (n < houses.size() && houses[n] != (House *)b)
				n++;
			houses.erase(houses.begin() + n);
		}
		if (b->type == MARKET && !markets.empty()) {
			n = 0;
			while (n < markets.size() && markets[n] != (Market *)b)
				n++;
			markets.erase(markets.begin() + n);
		}
		update_houses();
		last_placed_x = -1;
		last_placed_z = -1;
		last_placed = b;
		return b->type;
	}
	return NONE;
}

void World::place(Visual2D *v2d_temp)
{
	if (last_placed->is_placeable) {
		// Daca este un tip de teren, doar schimb culoarea dalei.
		if (last_placed->type == LAND || last_placed->type == GRASS || 	last_placed->type == WATER) {
			last_placed->remove_from_v2d(v2d_temp);
			grid[last_placed_z][last_placed_x]->change_type(last_placed->type);
		}
		else {
			int max_size = max(last_placed->size_z, last_placed->size_x),
				x = last_placed->start_x,
				z = last_placed->start_z;

			Building *copy = Building::copy((Building *)last_placed);

			for (int i = 0; i < max_size; ++i)
				for (int j = 0; j < max_size; ++j)
					if (copy->blueprint[i][j])
						if (i + z >= 0 && j + x >= 0 && i + z < size && j + x < size) {
							grid[i + z][j + x]->remove_from_v2d(v2d_terrain);
							grid[i + z][j + x] = copy;
					}

			if (copy->type == MARKET)
				markets.push_back((Market *)copy);

			if (copy->type == HOUSE) {
				if (!has_road((House *)copy))
					((House *)copy)->color_unreachable();
				houses.push_back((House *)copy);
			}

			update_houses();
			object_container.push_back(copy);
			// Reordoneaza obiectele in functie de pozitia lor pe grila, pentru a putea fi afisate
			// corespunzator.
			sort(object_container.begin(), object_container.end(), TileComparator(size));
			for (int i = 0; i < object_container.size(); ++i) {
				object_container[i]->remove_from_v2d(v2d_buildings);
				object_container[i]->add_to_v2d(v2d_buildings);
			}
			last_placed->type = NONE;
		}
	}
}

void World::try_place(int x, int z, int choice)
{
	// Actualizeaz obiectul de pus pe harta doar daca acesta si-a schimbat pozitia sau a fost rotit.
	if (last_placed_x != x || last_placed_z != z || rotated) {
		rotated = false;
		last_placed->remove_from_v2d(v2d_temp);
		
		TileType type = edit_panel->objects[choice]->type;
		
		Tile *tile;
		tile = Tile::make_tile(type);
		last_placed_x = x;
		last_placed_z = z;

		if (type == last_placed->type) {
			if (type == HOUSE || type == MARKET || type == ROAD) {
				((Building *)tile)->rotation = ((Building *)last_placed)->rotation;
				((Building *)tile)->blueprint = ((Building *)last_placed)->blueprint;
			}
		}
		tile->transform(x, z);
		// Vreau sa pun un tip de teren
		if (type == LAND || type == GRASS || type == WATER)
			// peste alt tip de teren.
			if (grid[z][x]->type == LAND || grid[z][x]->type == GRASS || grid[z][x]->type == WATER)
				tile->is_placeable = true;
			// Nu se poate peste cladiri sau drum.
			else
				tile->make_red();
		else
			determine_placeable(x, z, (Building *)tile);

		tile->add_to_v2d(v2d_temp);
		last_placed = tile;

		if (type == MARKET)
			markets.push_back((Market *)tile);
		highlight_markets();
		if (type == MARKET)
			markets.pop_back();
	}
}

void World::determine_placeable(int x, int z, Building *tile)
{
	int i, j, max_size = max(tile->size_x, tile->size_z);

	// Modific coordonatele varfului obiectului pe grid in functie de rotatie.
	switch (tile->rotation) {
	case 1:
	case -3:
		x -= max_size - 1;
		break;
	case 2:
	case -2:
		x -= max_size - 1;
		z -= max_size - 1;
		break;
	case 3:
	case -1:
		z -= max_size - 1;
		break;
	}
	tile->start_x = x;
	tile->start_z = z;

	bool near_market = false;

	// Vreau sa plasez cladire
	for (i = x; i < x + max_size; ++i) {
		for (j = z; j < z + max_size; ++j) {
			if (tile->blueprint[j - z][i - x]) {
				// in limitele hartii
				if (j < 0 || i < 0 || j >= size || i >= size) {
					break;
				}
				else {
					// doar peste pamant sau iarba.
					if (grid[j][i]->type != LAND && grid[j][i]->type != GRASS)
						break;
					if (grid[j][i]->is_near_market)
						near_market = true;
				}
			}
		}
		if (j < z + max_size)
			break;
	}

	// Daca nu pot sa pun, colorez cu rosu.
	if (i < x + max_size || (tile->type == HOUSE && !near_market)) {
		tile->make_red();
		return;
	}

	tile->is_placeable = true;
}

void World::rotate(Direction dir, int x, int z)
{
	if (last_placed->type == HOUSE || last_placed->type == MARKET || last_placed->type == ROAD) {
		rotated = true;
		((Building *)last_placed)->rotate(dir, x, z);
	}
}

void World::highlight_market(Market *m)
{
	int max_size = max(m->size_x, m->size_z);

	for (int i = m->start_x - Market::COVERAGE; i < m->start_x + Market::COVERAGE + max_size; ++i)
		for (int j = m->start_z - Market::COVERAGE; j < m->start_z + Market::COVERAGE + max_size; ++j)
			if (i >= 0 && j >= 0 && i < size && j < size &&
				(grid[j][i]->type == LAND || grid[j][i]->type == GRASS))
				grid[j][i]->is_near_market = true;
}

void World::highlight_markets()
{
	for (int i = 0; i < size; ++i)
		for (int j = 0; j < size; ++j)
			grid[i][j]->is_near_market = false;

	for (int i = 0; i < markets.size(); ++i)
		highlight_market(markets[i]);

	for (int i = 0; i < size; ++i)
		for (int j = 0; j < size; ++j)
			if (grid[i][j]->is_near_market)
				grid[i][j]->highlight();
			else
				grid[i][j]->remove_highlight();
}

void World::remove_highlight_markets()
{
	for (int i = 0; i < size; ++i)
		for (int j = 0; j < size; ++j)
			if (grid[i][j]->is_near_market)
				grid[i][j]->remove_highlight();
}

bool World::has_road(House *h)
{
	set<pair<int, int>> starting_points;
	int max_size = max(h->size_z, h->size_x),
		x = h->start_x,
		z = h->start_z;
	visited_roads = vector<vector<bool>>(size, vector<bool>(size, false));

	// Ia in calcul toate drumurile adiacente casei h.
	for (int i = z; i < max_size + z; ++i) {
		for (int j = x; j < max_size + x; ++j) {
			if (h->blueprint[i - z][j - x]) {
				if (i >= 0 && j >= 0 && i < size && j < size) {
					if (i > 0) {
						if (grid[i - 1][j]->type == ROAD)
							starting_points.insert(make_pair(i - 1, j));
						if (grid[i - 1][j]->type == MARKET)
							return true;
					}
					if (j > 0) {
						if (grid[i][j - 1]->type == ROAD)
							starting_points.insert(make_pair(i, j - 1));
						if (grid[i][j - 1]->type == MARKET)
							return true;
					}
					if (i < size - 1) {
						if (grid[i + 1][j]->type == ROAD)
							starting_points.insert(make_pair(i + 1, j));
						if (grid[i + 1][j]->type == MARKET)
							return true;
					}
					if (j < size - 1) {
						if (grid[i][j + 1]->type == ROAD)
							starting_points.insert(make_pair(i, j + 1));
						if (grid[i][j + 1]->type == MARKET)
							return true;
					}
				}
			}
		}
	}

	// Porneste DFS pe harta incepand de la drumurile adicente unei case.
	for (set<pair<int, int>>::iterator it = starting_points.begin(); it != starting_points.end(); ++it) {
		if (check_road((*it).first, (*it).second))
			return true;
	}
	
	return false;
}

bool World::check_road(int z, int x)
{
	visited_roads[z][x] = true;
	if (z > 0 && ((!visited_roads[z - 1][x] && grid[z - 1][x]->type == ROAD && check_road(z - 1, x)) ||
		grid[z - 1][x]->type == MARKET))
			return true;
	if (x > 0 && ((!visited_roads[z][x - 1] && grid[z][x - 1]->type == ROAD && check_road(z, x - 1)) ||
		grid[z][x - 1]->type == MARKET))
			return true;
	if (z < size - 1 && ((!visited_roads[z + 1][x] && grid[z + 1][x]->type == ROAD && check_road(z + 1, x)) ||
		grid[z + 1][x]->type == MARKET))
			return true;
	if (x < size - 1 && ((!visited_roads[z][x + 1] && grid[z][x + 1]->type == ROAD && check_road(z, x + 1)) ||
		grid[z][x + 1]->type == MARKET))
			return true;
	return false;
}

void World::update_houses()
{
	for (int i = 0; i < houses.size(); ++i)
		if (has_road(houses[i]))
			houses[i]->color_reachable();
		else
			houses[i]->color_unreachable();
}