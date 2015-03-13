// Despa Diana Alexandra 331CA

#include "House.h"


House::House()
{
	objects.clear();
	vector <Point3D*> vertices;
	vector <Face*> faces;
	vector <int> contour;

	Color color1 = Color(0.858, 0.584, 0.266),
		color2 = Color(0.98, 0.925, 0.556);

	// Corpul de jos.
	vertices.push_back(new Point3D(0, 0, 0));
	vertices.push_back(new Point3D(Tile::SIZE * 2, 0, 0));
	vertices.push_back(new Point3D(Tile::SIZE * 2, 0, Tile::SIZE));
	vertices.push_back(new Point3D(Tile::SIZE, 0, Tile::SIZE));
	vertices.push_back(new Point3D(Tile::SIZE, 0, Tile::SIZE * 3));
	vertices.push_back(new Point3D(0, 0, Tile::SIZE * 3));
	vertices.push_back(new Point3D(0, Tile::SIZE, 0));
	vertices.push_back(new Point3D(Tile::SIZE * 2, Tile::SIZE, 0));
	vertices.push_back(new Point3D(Tile::SIZE * 2, Tile::SIZE, Tile::SIZE));
	vertices.push_back(new Point3D(Tile::SIZE, Tile::SIZE, Tile::SIZE));
	vertices.push_back(new Point3D(Tile::SIZE, Tile::SIZE, Tile::SIZE * 3));
	vertices.push_back(new Point3D(0, Tile::SIZE, Tile::SIZE * 3));

	Face *face;
	contour.clear();
	contour.push_back(0);
	contour.push_back(1);
	contour.push_back(7);
	contour.push_back(6);
	faces.push_back(new Face(contour));
	
	contour.clear();
	contour.push_back(0);
	contour.push_back(5);
	contour.push_back(11);
	contour.push_back(6);
	faces.push_back(new Face(contour));
	
	contour.clear();
	contour.push_back(0);
	contour.push_back(1);
	contour.push_back(2);
	contour.push_back(3);
	contour.push_back(4);
	contour.push_back(5);
	faces.push_back(new Face(contour));
	
	contour.clear();
	contour.push_back(6);
	contour.push_back(7);
	contour.push_back(8);
	contour.push_back(9);
	contour.push_back(10);
	contour.push_back(11);
	faces.push_back(new Face(contour));
	
	contour.clear();
	contour.push_back(1);
	contour.push_back(2);
	contour.push_back(8);
	contour.push_back(7);
	faces.push_back(new Face(contour));
	
	contour.clear();
	contour.push_back(5);
	contour.push_back(4);
	contour.push_back(10);
	contour.push_back(11);
	faces.push_back(new Face(contour));
	
	contour.clear();
	contour.push_back(3);
	contour.push_back(2);
	contour.push_back(8);
	contour.push_back(9);
	faces.push_back(new Face(contour));

	contour.clear();
	contour.push_back(3);
	contour.push_back(4);
	contour.push_back(10);
	contour.push_back(9);
	faces.push_back(new Face(contour));
	
	objects.push_back(new Object3D(vertices, faces, color1, true));

	vertices.clear();
	faces.clear();

	// Fetele de deasupra corpului de jos
	vertices.push_back(new Point3D(0, Tile::SIZE, Tile::SIZE * 3));
	vertices.push_back(new Point3D(Tile::SIZE, Tile::SIZE, Tile::SIZE * 3));
	vertices.push_back(new Point3D(Tile::SIZE, Tile::SIZE, Tile::SIZE * 2));
	vertices.push_back(new Point3D(0, Tile::SIZE, Tile::SIZE * 2));

	contour.clear();
	contour.push_back(0);
	contour.push_back(1);
	contour.push_back(2);
	contour.push_back(3);
	faces.push_back(new Face(contour));

	objects.push_back(new Object3D(vertices, faces, color2, true));

	vertices.clear();
	faces.clear();

	vertices.push_back(new Point3D(Tile::SIZE, Tile::SIZE, 0));
	vertices.push_back(new Point3D(Tile::SIZE, Tile::SIZE, Tile::SIZE));
	vertices.push_back(new Point3D(Tile::SIZE * 2, Tile::SIZE, Tile::SIZE));
	vertices.push_back(new Point3D(Tile::SIZE * 2, Tile::SIZE, 0));

	contour.clear();
	contour.push_back(0);
	contour.push_back(1);
	contour.push_back(2);
	contour.push_back(3);
	faces.push_back(new Face(contour));

	objects.push_back(new Object3D(vertices, faces, color2, true));
	vertices.clear();
	faces.clear();

	// Corpul de sus
	vertices.push_back(new Point3D(0, Tile::SIZE, 0));
	vertices.push_back(new Point3D(Tile::SIZE, Tile::SIZE, 0));
	vertices.push_back(new Point3D(Tile::SIZE, Tile::SIZE, Tile::SIZE * 2));
	vertices.push_back(new Point3D(0, Tile::SIZE, Tile::SIZE * 2));
	vertices.push_back(new Point3D(0, Tile::SIZE * 2, 0));
	vertices.push_back(new Point3D(Tile::SIZE, Tile::SIZE * 2, 0));
	vertices.push_back(new Point3D(Tile::SIZE, Tile::SIZE * 2, Tile::SIZE * 2));
	vertices.push_back(new Point3D(0, Tile::SIZE * 2, Tile::SIZE * 2));

	contour.clear();
	contour.push_back(4);
	contour.push_back(5);
	contour.push_back(6);
	contour.push_back(7);
	faces.push_back(new Face(contour));

	contour.clear();
	contour.push_back(0);
	contour.push_back(1);
	contour.push_back(5);
	contour.push_back(4);
	faces.push_back(new Face(contour));

	contour.clear();
	contour.push_back(1);
	contour.push_back(2);
	contour.push_back(6);
	contour.push_back(5);
	faces.push_back(new Face(contour));

	contour.clear();
	contour.push_back(2);
	contour.push_back(3);
	contour.push_back(7);
	contour.push_back(6);
	faces.push_back(new Face(contour));

	contour.clear();
	contour.push_back(3);
	contour.push_back(0);
	contour.push_back(4);
	contour.push_back(7);
	faces.push_back(new Face(contour));

	objects.push_back(new Object3D(vertices, faces, color1, true));

	vertices.clear();
	faces.clear();

	// Fata de deasupra corpului de sus
	vertices.push_back(new Point3D(0, Tile::SIZE * 2, 0));
	vertices.push_back(new Point3D(Tile::SIZE, Tile::SIZE * 2, 0));
	vertices.push_back(new Point3D(Tile::SIZE, Tile::SIZE * 2, Tile::SIZE * 2));
	vertices.push_back(new Point3D(0, Tile::SIZE * 2, Tile::SIZE * 2));

	contour.clear();
	contour.push_back(0);
	contour.push_back(1);
	contour.push_back(2);
	contour.push_back(3);
	faces.push_back(new Face(contour));

	objects.push_back(new Object3D(vertices, faces, color2, true));

	type = HOUSE;
	size_x = 2;
	size_y = 2;
	size_z = 3;
	is_reachable = true;

	vector<bool> line;
	line.push_back(true); line.push_back(true); line.push_back(false);
	blueprint.push_back(line);
	line.clear();
	line.push_back(true); line.push_back(false); line.push_back(false);
	blueprint.push_back(line);
	blueprint.push_back(line);
}

House::~House()
{
}

void House::color_reachable()
{
	if (!is_reachable) {
		objects[0]->color = Color(0.858, 0.584, 0.266);
		objects[1]->color = Color(0.98, 0.925, 0.556);
		objects[2]->color = Color(0.98, 0.925, 0.556);
		objects[3]->color = Color(0.858, 0.584, 0.266);
		objects[4]->color = Color(0.98, 0.925, 0.556);
		is_reachable = true;
	}
}

void House::color_unreachable()
{
	if (is_reachable) {
		for (int i = 0; i < objects.size(); ++i) {
			objects[i]->color.g -= 0.5;
			objects[i]->color.b -= 0.5;
		}
		is_reachable = false;
	}
}