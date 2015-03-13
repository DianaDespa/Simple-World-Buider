// Despa Diana Alexandra 331CA

#pragma once
#include "../Framework/DrawingWindow.h"
#include "../Framework/Rectangle2d.h"
#include "Building.h"

class EditPanel
{
private:
	Visual2D *v2d_choices, *v2d_background;
	Rectangle2D *background, *highlight, *outline;
	int offset;	// Offset-ul pe verticala in interiorul panoului.
public:
	vector<Tile *> objects; // Obiectele din interiorul panoului.
public:
	EditPanel(Visual2D *v2d_choices, Visual2D *v2d_background);
	~EditPanel();

	// Adauga obiect la panou.
	void add(Tile *tile);
	// Intoarce numarul de obiecte din panou.
	int get_panel_size();
	// Selecteaza un anumit obiect in panou.
	void set_choice(int choice);
};

