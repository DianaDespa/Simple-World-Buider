// Despa Diana Alexandra 331CA

#pragma once
#include "../Framework/Rectangle2d.h"
#include "Building.h"

// Clasa ce reprezinta pietele.
class Market : public Building
{
public:
	static const int COVERAGE = 6;	// Raza de acoperire.

	Market();
	~Market();
};