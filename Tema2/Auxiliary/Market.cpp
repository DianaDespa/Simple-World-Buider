// Despa Diana Alexandra 331CA

#include "Market.h"


Market::Market()
{
	objects.clear();
	vector <Point3D*> vertices;
	vector <Face*> faces;
	vector <int> contour;

	// Baza
	vertices.push_back(new Point3D(Tile::SIZE, 0, Tile::SIZE));
	vertices.push_back(new Point3D(0, 0, Tile::SIZE));
	vertices.push_back(new Point3D(0, 0, Tile::SIZE * 2));
	vertices.push_back(new Point3D(Tile::SIZE, 0, Tile::SIZE * 2));
	vertices.push_back(new Point3D(Tile::SIZE, 0, Tile::SIZE * 3));
	vertices.push_back(new Point3D(0, 0, Tile::SIZE * 3));
	vertices.push_back(new Point3D(0, 0, Tile::SIZE * 4));
	vertices.push_back(new Point3D(Tile::SIZE, 0, Tile::SIZE * 4));
	vertices.push_back(new Point3D(Tile::SIZE, 0, Tile::SIZE * 5));
	vertices.push_back(new Point3D(0, 0, Tile::SIZE * 5));
	vertices.push_back(new Point3D(0, 0, Tile::SIZE * 6));

	vertices.push_back(new Point3D(Tile::SIZE, 0, Tile::SIZE * 6));
	vertices.push_back(new Point3D(Tile::SIZE, 0, Tile::SIZE * 7));
	vertices.push_back(new Point3D(Tile::SIZE * 2, 0, Tile::SIZE * 7));
	vertices.push_back(new Point3D(Tile::SIZE * 2, 0, Tile::SIZE * 6));
	vertices.push_back(new Point3D(Tile::SIZE * 3, 0, Tile::SIZE * 6));
	vertices.push_back(new Point3D(Tile::SIZE * 3, 0, Tile::SIZE * 7));
	vertices.push_back(new Point3D(Tile::SIZE * 4, 0, Tile::SIZE * 7));
	vertices.push_back(new Point3D(Tile::SIZE * 4, 0, Tile::SIZE * 6));
	vertices.push_back(new Point3D(Tile::SIZE * 5, 0, Tile::SIZE * 6));
	vertices.push_back(new Point3D(Tile::SIZE * 5, 0, Tile::SIZE * 7));
	vertices.push_back(new Point3D(Tile::SIZE * 6, 0, Tile::SIZE * 7));

	vertices.push_back(new Point3D(Tile::SIZE * 6, 0, Tile::SIZE * 6));
	vertices.push_back(new Point3D(Tile::SIZE * 7, 0, Tile::SIZE * 6));
	vertices.push_back(new Point3D(Tile::SIZE * 7, 0, Tile::SIZE * 5));
	vertices.push_back(new Point3D(Tile::SIZE * 6, 0, Tile::SIZE * 5));
	vertices.push_back(new Point3D(Tile::SIZE * 6, 0, Tile::SIZE * 4));
	vertices.push_back(new Point3D(Tile::SIZE * 7, 0, Tile::SIZE * 4));
	vertices.push_back(new Point3D(Tile::SIZE * 7, 0, Tile::SIZE * 3));
	vertices.push_back(new Point3D(Tile::SIZE * 6, 0, Tile::SIZE * 3));
	vertices.push_back(new Point3D(Tile::SIZE * 6, 0, Tile::SIZE * 2));
	vertices.push_back(new Point3D(Tile::SIZE * 7, 0, Tile::SIZE * 2));
	vertices.push_back(new Point3D(Tile::SIZE * 7, 0, Tile::SIZE));

	vertices.push_back(new Point3D(Tile::SIZE * 6, 0, Tile::SIZE));
	vertices.push_back(new Point3D(Tile::SIZE * 6, 0, 0));
	vertices.push_back(new Point3D(Tile::SIZE * 5, 0, 0));
	vertices.push_back(new Point3D(Tile::SIZE * 5, 0, Tile::SIZE));
	vertices.push_back(new Point3D(Tile::SIZE * 4, 0, Tile::SIZE));
	vertices.push_back(new Point3D(Tile::SIZE * 4, 0, 0));
	vertices.push_back(new Point3D(Tile::SIZE * 3, 0, 0));
	vertices.push_back(new Point3D(Tile::SIZE * 3, 0, Tile::SIZE));
	vertices.push_back(new Point3D(Tile::SIZE * 2, 0, Tile::SIZE));
	vertices.push_back(new Point3D(Tile::SIZE * 2, 0, 0));
	vertices.push_back(new Point3D(Tile::SIZE, 0, 0));

	contour.clear();
	contour.push_back(0);
	contour.push_back(1);
	contour.push_back(2);
	contour.push_back(3);
	contour.push_back(4);
	contour.push_back(5);
	contour.push_back(6);
	contour.push_back(7);
	contour.push_back(8);
	contour.push_back(9);
	contour.push_back(10);
	contour.push_back(11);
	contour.push_back(12);
	contour.push_back(13);
	contour.push_back(14);
	contour.push_back(15);
	contour.push_back(16);
	contour.push_back(17);
	contour.push_back(18);
	contour.push_back(19);
	contour.push_back(20);
	contour.push_back(21);
	contour.push_back(22);
	contour.push_back(23);
	contour.push_back(24);
	contour.push_back(25);
	contour.push_back(26);
	contour.push_back(27);
	contour.push_back(28);
	contour.push_back(29);
	contour.push_back(30);
	contour.push_back(31);
	contour.push_back(32);
	contour.push_back(33);
	contour.push_back(34);
	contour.push_back(35);
	contour.push_back(36);
	contour.push_back(37);
	contour.push_back(38);
	contour.push_back(39);
	contour.push_back(40);
	contour.push_back(41);
	contour.push_back(42);
	contour.push_back(43);
	faces.push_back(new Face(contour));

	objects.push_back(new Object3D(vertices, faces, Color(0.7, 0.7, 0.7), true));

	vertices.clear();
	faces.clear();

	// Corp baza
	vertices.push_back(new Point3D(Tile::SIZE * 2, 0, Tile::SIZE * 2));
	vertices.push_back(new Point3D(Tile::SIZE * 5, 0, Tile::SIZE * 2));
	vertices.push_back(new Point3D(Tile::SIZE * 5, 0, Tile::SIZE * 5));
	vertices.push_back(new Point3D(Tile::SIZE * 2, 0, Tile::SIZE * 5));
	vertices.push_back(new Point3D(Tile::SIZE * 2, Tile::SIZE, Tile::SIZE * 2));
	vertices.push_back(new Point3D(Tile::SIZE * 5, Tile::SIZE, Tile::SIZE * 2));
	vertices.push_back(new Point3D(Tile::SIZE * 5, Tile::SIZE, Tile::SIZE * 5));
	vertices.push_back(new Point3D(Tile::SIZE * 2, Tile::SIZE, Tile::SIZE * 5));

	contour.clear();
	contour.push_back(0);
	contour.push_back(1);
	contour.push_back(2);
	contour.push_back(3);
	faces.push_back(new Face(contour));

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

	objects.push_back(new Object3D(vertices, faces, Color(0.4, 0.4, 0.4), true));

	vertices.clear();
	faces.clear();

	// Fata deasupra corp baza
	vertices.push_back(new Point3D(Tile::SIZE * 2, Tile::SIZE, Tile::SIZE * 2));
	vertices.push_back(new Point3D(Tile::SIZE * 5, Tile::SIZE, Tile::SIZE * 2));
	vertices.push_back(new Point3D(Tile::SIZE * 5, Tile::SIZE, Tile::SIZE * 5));
	vertices.push_back(new Point3D(Tile::SIZE * 2, Tile::SIZE, Tile::SIZE * 5));

	contour.clear();
	contour.push_back(0);
	contour.push_back(1);
	contour.push_back(2);
	contour.push_back(3);
	faces.push_back(new Face(contour));

	objects.push_back(new Object3D(vertices, faces, Color(0.85, 0.85, 0.85), true));

	vertices.clear();
	faces.clear();

	// Corp suprapus
	vertices.push_back(new Point3D(Tile::SIZE * 3, Tile::SIZE, Tile::SIZE * 3));
	vertices.push_back(new Point3D(Tile::SIZE * 4, Tile::SIZE, Tile::SIZE * 3));
	vertices.push_back(new Point3D(Tile::SIZE * 4, Tile::SIZE, Tile::SIZE * 4));
	vertices.push_back(new Point3D(Tile::SIZE * 3, Tile::SIZE, Tile::SIZE * 4));
	vertices.push_back(new Point3D(Tile::SIZE * 3, Tile::SIZE * 2, Tile::SIZE * 3));
	vertices.push_back(new Point3D(Tile::SIZE * 4, Tile::SIZE * 2, Tile::SIZE * 3));
	vertices.push_back(new Point3D(Tile::SIZE * 4, Tile::SIZE * 2, Tile::SIZE * 4));
	vertices.push_back(new Point3D(Tile::SIZE * 3, Tile::SIZE * 2, Tile::SIZE * 4));

	contour.clear();
	contour.push_back(0);
	contour.push_back(1);
	contour.push_back(2);
	contour.push_back(3);
	faces.push_back(new Face(contour));

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

	objects.push_back(new Object3D(vertices, faces, Color(0.4, 0.4, 0.4), true));

	vertices.clear();
	faces.clear();

	// Fata deasupra corp suprapus
	vertices.push_back(new Point3D(Tile::SIZE * 3, Tile::SIZE * 2, Tile::SIZE * 3));
	vertices.push_back(new Point3D(Tile::SIZE * 4, Tile::SIZE * 2, Tile::SIZE * 3));
	vertices.push_back(new Point3D(Tile::SIZE * 4, Tile::SIZE * 2, Tile::SIZE * 4));
	vertices.push_back(new Point3D(Tile::SIZE * 3, Tile::SIZE * 2, Tile::SIZE * 4));

	contour.clear();
	contour.push_back(0);
	contour.push_back(1);
	contour.push_back(2);
	contour.push_back(3);
	faces.push_back(new Face(contour));

	objects.push_back(new Object3D(vertices, faces, Color(0.85, 0.85, 0.85), true));

	type = MARKET;
	size_x = 7;
	size_y = 2;
	size_z = 7;

	vector<bool> line;
	line.push_back(true); line.push_back(true); line.push_back(true); line.push_back(true);
	line.push_back(true); line.push_back(true); line.push_back(true);
	blueprint.push_back(line);
	blueprint.push_back(line);
	blueprint.push_back(line);
	blueprint.push_back(line);
	blueprint.push_back(line);
	blueprint.push_back(line);
	blueprint.push_back(line);
	blueprint[0][0] = false;
	blueprint[0][2] = false;
	blueprint[0][4] = false;
	blueprint[0][6] = false;
	blueprint[6][0] = false;
	blueprint[6][2] = false;
	blueprint[6][4] = false;
	blueprint[6][6] = false;
	blueprint[2][0] = false;
	blueprint[4][0] = false;
	blueprint[2][6] = false;
	blueprint[4][6] = false;
}

Market::~Market()
{
}