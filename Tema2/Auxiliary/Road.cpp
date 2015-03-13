// Despa Diana Alexandra 331CA

#include "Road.h"


Road::Road()
{
	objects.clear();
	vector <Point3D*> vertices;
	vector <Face*> faces;
	vector<int> contour;

	vertices.push_back(new Point3D(0, 0, 0));
	vertices.push_back(new Point3D(SIZE, 0, 0));
	vertices.push_back(new Point3D(SIZE, 0, SIZE));
	vertices.push_back(new Point3D(0, 0, SIZE));
	contour.push_back(0);
	contour.push_back(1);
	contour.push_back(2);
	contour.push_back(3);
	faces.push_back(new Face(contour));
	objects.push_back(new Object3D(vertices, faces, Color(0.3, 0.3, 0.3), true));

	vertices.clear();
	vertices.push_back(new Point3D(SIZE / 2 - 5, 0, 5));
	vertices.push_back(new Point3D(SIZE / 2 + 5, 0, 5));
	vertices.push_back(new Point3D(SIZE / 2 + 5, 0, SIZE - 5));
	vertices.push_back(new Point3D(SIZE / 2 - 5, 0, SIZE - 5));
	objects.push_back(new Object3D(vertices, faces, Color(1, 1, 1), true));

	size_x = 1;
	size_y = 0;
	size_z = 1;
	type = ROAD;

	vector<bool> line;
	line.push_back(true);
	blueprint.push_back(line);
}

Road::~Road()
{
}
