// Despa Diana Alexandra 331CA

#pragma once
#include "Building.h"

// Clasa ce reprezinta casele.
class House : public Building
{
public:
	bool is_reachable;	// Indica daca o casa este conectata de o piata.
public:
	House();
	~House();

	// Schimba culoarea casei daca este sau nu conectata la piata.
	void color_reachable();
	void color_unreachable();
};

