// Despa Diana Alexandra 331CA

#include "EditPanel.h"


EditPanel::EditPanel(Visual2D *v2d_choices, Visual2D *v2d_background)
{
	this->v2d_choices = v2d_choices;
	this->v2d_background = v2d_background;
	offset = 600;
}

EditPanel::~EditPanel()
{
}

void EditPanel::add(Tile *tile)
{
	objects.push_back(tile);
	float max_scale = 1,
		x = tile->size_x,
		y = tile->size_y,
		z = tile->size_z;

	max_scale = max(x, z);
	offset -= Tile::SIZE * (1 + y / max_scale);

	Transform3D::loadIdentityModelMatrix();
	Transform3D::loadIdentityProjectionMatrix();
	Transform3D::translateMatrix(-Tile::SIZE * x / 2, -Tile::SIZE * y / 2, -Tile::SIZE * z / 2);
	Transform3D::scaleMatrix(2 / max_scale, 2 / max_scale, 2 / max_scale);
	Transform3D::translateMatrix(Tile::SIZE * x / 2, Tile::SIZE * y / 2, Tile::SIZE * z / 2);
	Transform3D::rotateMatrixOy(PI / 4);
	Transform3D::rotateMatrixOx(atan(1 / sqrt(2.0)));
	Transform3D::translateMatrix(Tile::SIZE * 2, offset, 0);
	Transform3D::parallelProjectionMatrix(0, 0, 1);
	tile->apply_transform();
	tile->add_to_v2d(v2d_choices);

	offset -= Tile::SIZE * 2;
}

int EditPanel::get_panel_size()
{
	return objects.size();
}

void EditPanel::set_choice(int choice)
{
	DrawingWindow::removeObject2D_from_Visual2D(background, v2d_background);
	DrawingWindow::removeObject2D_from_Visual2D(highlight, v2d_background);
	DrawingWindow::removeObject2D_from_Visual2D(outline, v2d_background);
	
	TileType type = objects[choice]->type;
	int tile_y = objects[choice]->get_y() - 2 * Tile::SIZE;
	int max_scale = max(objects[choice]->size_x, objects[choice]->size_z);

	// Pun in evidenta obiectul.
	highlight = new Rectangle2D(Point2D(0, tile_y), Tile::SIZE * 4,
		(objects[choice]->size_y / max_scale + 3) * Tile::SIZE,
		Color(0.758, 0.733, 0.801), true);

	if (tile_y > 0)
		tile_y = 0;

	// Mut fereastra panoului daca obiectul selectat se afla in afara lui, pe verticala.
	v2d_choices->fereastra(0, tile_y, Tile::SIZE * 4, 600 + tile_y);
	v2d_background->fereastra(0, tile_y, Tile::SIZE * 4, 600 + tile_y);
	background = new Rectangle2D(Point2D(0, tile_y), Tile::SIZE * 4, 600, Color(0.839, 0.839, 0.823), true);
	outline = new Rectangle2D(Point2D(0, tile_y), Tile::SIZE * 4, 600, Color(0, 0, 0), false);

	DrawingWindow::addObject2D_to_Visual2D(outline, v2d_background);
	DrawingWindow::addObject2D_to_Visual2D(highlight, v2d_background);
	DrawingWindow::addObject2D_to_Visual2D(background, v2d_background);
}