// Despa Diana Alexandra 331CA

#include "Building.h"
#include "Road.h"
#include "House.h"
#include "Market.h"

Building::Building()
{
	rotation = 0;
}

Building::~Building()
{
}

void Building::transform(int x, int z)
{
	Transform3D::loadIdentityModelMatrix();
	Transform3D::loadIdentityProjectionMatrix();
	Transform3D::translateMatrix(-Tile::SIZE / 2, -Tile::SIZE / 2, -Tile::SIZE / 2);
	Transform3D::rotateMatrixOy(rotation * PI / 2);
	Transform3D::translateMatrix(Tile::SIZE / 2, Tile::SIZE / 2, Tile::SIZE / 2);
	Transform3D::translateMatrix(Tile::SIZE * x, 0, Tile::SIZE * z);
	Transform3D::rotateMatrixOy(PI / 4);
	Transform3D::rotateMatrixOx(atan(1 / sqrt(2.0)));
	Transform3D::parallelProjectionMatrix(0, 0, 1);
	for (int i = 0; i < objects.size(); ++i)
		Transform3D::applyTransform(objects[i]);
}

// Transpune o matrice m, avand n linii si n coloane. 
vector<vector<bool>> rotate_matrix(vector<vector<bool>> m, int n)
{
	for (int i = 0; i < n / 2; i++) {
		for (int j = 0; j < (n + 1) / 2; j++) {
			bool temp = m[i][j];
			m[i][j] = m[n - 1 - j][i];
			m[n - 1 - j][i] = m[n - 1 - i][n - 1 - j];
			m[n - 1 - i][n - 1 - j] = m[j][n - 1 - i];
			m[j][n - 1 - i] = temp;
		}
	}

	return m;
}

void Building::rotate(Direction dir, int x, int z)
{
	int max_size = max(size_x, size_z);
	if (dir == LEFT) {
		rotation--;
		blueprint = rotate_matrix(blueprint, max_size);
		blueprint = rotate_matrix(blueprint, max_size);
		blueprint = rotate_matrix(blueprint, max_size);
	}
	else {
		rotation++;
		blueprint = rotate_matrix(blueprint, max_size);
	}
	if (rotation == 4 || rotation == -4) {
		rotation = 0;
	}

	transform(x, z);
}

Building *Building::copy(Building *b)
{
	Building *result;
	switch (b->type) {
	case ROAD:
		result = new Road();
		break;
	case HOUSE:
		result = new House();
		((House *)result)->is_reachable = ((House *)b)->is_reachable;
		break;
	case MARKET:
		result = new Market();
		break;
	default:
		result = new Building();
		break;
	}
	result->rotation = b->rotation;
	result->blueprint = b->blueprint;
	result->size_x = b->size_x;
	result->size_y = b->size_y;
	result->size_z = b->size_z;
	result->start_x = b->start_x;
	result->start_z = b->start_z;
	result->is_near_market = b->is_near_market;
	result->is_placeable = b->is_placeable;
	result->highlighted = b->highlighted;
	result->objects = b->objects;
	return result;
}