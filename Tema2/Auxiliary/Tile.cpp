// Despa Diana Alexandra 331CA

#include "Tile.h"
#include "Road.h"
#include "House.h"
#include "Market.h"

Tile::Tile()
{
	vector <Point3D*> vertices;
	vector <Face*> faces;

	vertices.push_back(new Point3D(0, 0, 0));
	vertices.push_back(new Point3D(SIZE, 0, 0));
	vertices.push_back(new Point3D(SIZE, 0, SIZE));
	vertices.push_back(new Point3D(0, 0, SIZE));

	vector<int> contour;
	contour.push_back(0);
	contour.push_back(1);
	contour.push_back(2);
	contour.push_back(3);
	faces.push_back(new Face(contour));

	objects.push_back(new Object3D(vertices, faces, Color(0, 0, 0), false));
	size_x = 1;
	size_y = 0;
	size_z = 1;
	type = NONE;
	highlighted = false;
	is_placeable = false;
	is_near_market = false;
}

Tile::~Tile()
{
}

Tile *Tile::make_tile(TileType type)
{
	Tile *tile = new Tile();
	switch (type) {
	case LAND:
	case WATER:
	case GRASS:
		tile->change_type(type);
		return tile;
	case ROAD:
		return new Road();
	case HOUSE:
		return new House();
	case MARKET:
		return new Market();
	}
}

void Tile::transform(int x, int z)
{
	Transform3D::loadIdentityModelMatrix();
	Transform3D::loadIdentityProjectionMatrix();
	Transform3D::translateMatrix(SIZE * x, 0, SIZE * z);
	Transform3D::rotateMatrixOy(PI / 4);
	Transform3D::rotateMatrixOx(atan(1 / sqrt(2.0)));
	Transform3D::parallelProjectionMatrix(0, 0, 1);
	for (int i = 0; i < objects.size(); ++i)
		Transform3D::applyTransform(objects[i]);
}

void Tile::add_to_v2d(Visual2D *v2d)
{
	for (int i = objects.size() - 1; i >= 0; --i)
		DrawingWindow::addObject3D_to_Visual2D(objects[i], v2d);
}

void Tile::remove_from_v2d(Visual2D *v2d)
{
	for (int i = 0; i < objects.size(); ++i)
		DrawingWindow::removeObject3D_from_Visual2D(objects[i], v2d);
}

void Tile::apply_transform()
{
	for (int i = 0; i < objects.size(); ++i)
		Transform3D::applyTransform(objects[i]);
}

void Tile::make_red()
{
	for (int i = 0; i < objects.size(); ++i)
		objects[i]->color = Color(1, 0, 0);
}

void Tile::highlight()
{
	if (!highlighted) {
		for (int i = 0; i < objects.size(); ++i)
			objects[i]->color.g += 0.15;
		highlighted = true;
	}
}

void Tile::remove_highlight()
{
	if (highlighted) {
		for (int i = 0; i < objects.size(); ++i)
			objects[i]->color.g -= 0.15;
		highlighted = false;
	}
}

void Tile::change_type(TileType type) {
	this->type = type;
	highlighted = false;
	switch (type) {
	case LAND:
		for (int i = 0; i < objects.size(); ++i) {
			objects[i]->fill = true;
			objects[i]->color = Color(0.578, 0.464, 0.302);
		}
		break;
	case GRASS:
		for (int i = 0; i < objects.size(); ++i) {
			objects[i]->fill = true;
			objects[i]->color = Color(0.015, 0.409, 0.106);
		}
		break;
	case WATER:
		for (int i = 0; i < objects.size(); ++i) {
			objects[i]->fill = true;
			objects[i]->color = Color(0.219, 0.785, 0.722);
		}
		break;
	}
}

float Tile::get_y()
{
	return objects[0]->transf_vertices[0]->y;
}