// Despa Diana Alexandra 331CA

#include "Framework/DrawingWindow.h"
#include "Framework/Visual2D.h"
#include "Framework/Rectangle2d.h"
#include "Framework/Transform3D.h"
#include "Auxiliary/World.h"
#include "Auxiliary/EditPanel.h"
#include <iostream>
#include <windows.h>
#include <cmath>

#define PI 3.14159265358979323846
#define NO_SQUARES 50 // Numarul de dale de pe o latura a hartii.

using namespace std;

Visual2D *v2d_terrain,
	*v2d_grid,
	*v2d_buildings,
	*v2d_temporary,
	*v2d_edit_panel,
	*v2d_edit_choices;
bool edit_mode;
int cursor_x = 0,
	cursor_z = 0,
	edit_choice = 0;
float zoom = 1;
float upper_limit_x,
	upper_limit_y,
	displacement_x,
	displacement_y,
	new_width,
	new_height;
World *world;
EditPanel *edit_panel;

//functia care permite adaugarea de obiecte
void DrawingWindow::init()
{
	edit_mode = false;
	displacement_x = 0;
	displacement_y = 0;
	upper_limit_x = -(DrawingWindow::width + Tile::SIZE) / 2;
	upper_limit_y = -DrawingWindow::height + Tile::SIZE;
	
	// Initializez contextele vizuale pentru teren, grila, cladiri si cladiri in modul editare.
	v2d_terrain = new Visual2D(upper_limit_x, upper_limit_y,
		(float)DrawingWindow::width + upper_limit_x,
		(float)DrawingWindow::height + upper_limit_y,
		0, 0, DrawingWindow::width, DrawingWindow::height);
	v2d_grid = new Visual2D(upper_limit_x, upper_limit_y,
		(float)DrawingWindow::width + upper_limit_x,
		(float)DrawingWindow::height + upper_limit_y,
		0, 0, DrawingWindow::width, DrawingWindow::height);
	v2d_buildings = new Visual2D(upper_limit_x, upper_limit_y,
		(float)DrawingWindow::width + upper_limit_x,
		(float)DrawingWindow::height + upper_limit_y,
		0, 0, DrawingWindow::width, DrawingWindow::height);
	v2d_temporary = new Visual2D(upper_limit_x, upper_limit_y,
		(float)DrawingWindow::width + upper_limit_x,
		(float)DrawingWindow::height + upper_limit_y,
		0, 0, DrawingWindow::width, DrawingWindow::height);

	// Initializez panoul care apare in modul de editare.
	v2d_edit_panel = new Visual2D(0, 0, Tile::SIZE * 4, 600, 0, 0, Tile::SIZE * 4, 600);
	v2d_edit_choices = new Visual2D(0, 0, Tile::SIZE * 4, 600, 0, 0, Tile::SIZE * 4, 600);
	edit_panel = new EditPanel(v2d_edit_choices, v2d_edit_panel);

	// Desenez grila si terenul.
	world = new World(NO_SQUARES, edit_panel, v2d_terrain, v2d_buildings, v2d_temporary);
	world->draw(v2d_grid);

	addVisual2D(v2d_temporary);
	addVisual2D(v2d_buildings);
	addVisual2D(v2d_grid);
	addVisual2D(v2d_terrain);
}

//functia care permite animatia
void DrawingWindow::onIdle()
{
	// Redimensionez sau mut ferestrele contextelor vizuale, in functie de parametrii.
	new_width = width * zoom;
	new_height = height * zoom;
	v2d_terrain->fereastra(upper_limit_x + displacement_x, upper_limit_y + displacement_y,
		new_width + upper_limit_x + displacement_x, new_height + upper_limit_y + displacement_y);
	v2d_grid->fereastra(upper_limit_x + displacement_x, upper_limit_y + displacement_y,
		new_width + upper_limit_x + displacement_x, new_height + upper_limit_y + displacement_y);
	v2d_buildings->fereastra(upper_limit_x + displacement_x, upper_limit_y + displacement_y,
		new_width + upper_limit_x + displacement_x, new_height + upper_limit_y + displacement_y);
	v2d_temporary->fereastra(upper_limit_x + displacement_x, upper_limit_y + displacement_y,
		new_width + upper_limit_x + displacement_x, new_height + upper_limit_y + displacement_y);

	// Pentru modul editare incerc sa plasez cladirea selectata din meniu.
	if (edit_mode)
		world->try_place(cursor_x, cursor_z, edit_choice);
	// Altfel mut cursorul pe harta.
	else
		world->highlight(cursor_x, cursor_z);
}

//functia care se apeleaza la redimensionarea ferestrei
void DrawingWindow::onReshape(int width,int height)
{
	v2d_terrain->poarta(0, 0, width, height);
	v2d_grid->poarta(0, 0, width, height);
	v2d_buildings->poarta(0, 0, width, height);
	v2d_temporary->poarta(0, 0, width, height);

	upper_limit_x = -(width + Tile::SIZE) / 2;
	upper_limit_y = -height + Tile::SIZE;
}

// Afiseaza meniul si face trecerea in modul de editare.
void switch_edit(int choice)
{
		edit_choice = choice;
		edit_panel->set_choice(choice);
		edit_mode = true;
		world->highlight_markets();
		world->remove_highlight(cursor_x, cursor_z);
		DrawingWindow::removeVisual2D(v2d_grid);
		DrawingWindow::removeVisual2D(v2d_terrain);
		DrawingWindow::removeVisual2D(v2d_buildings);
		DrawingWindow::removeVisual2D(v2d_temporary);

		DrawingWindow::addVisual2D(v2d_edit_choices);
		DrawingWindow::addVisual2D(v2d_edit_panel);
		DrawingWindow::addVisual2D(v2d_temporary);
		DrawingWindow::addVisual2D(v2d_buildings);
		DrawingWindow::addVisual2D(v2d_grid);
		DrawingWindow::addVisual2D(v2d_terrain);
}

//functia care defineste ce se intampla cand se apasa pe tastatura
void DrawingWindow::onKey(unsigned char key)
{
	TileType selected;
	switch(key)	{
		case 27:
			exit(0);
			break;
		case 'W': // Scroll sus
			displacement_y += Tile::SIZE;
			break;
		case 'A': // Scroll stanga
			displacement_x -= Tile::SIZE;
			break;
		case 'S': // Scroll jos
			displacement_y -= Tile::SIZE;
			break;
		case 'D': // Scroll dreapta
			displacement_x += Tile::SIZE;
			break;
		case 'e': // Mode editare
			if (!edit_mode) {
				switch_edit(0);
			}
			else {
				edit_mode = false;
				world->last_placed->remove_from_v2d(v2d_temporary);
				world->remove_highlight_markets();
				removeVisual2D(v2d_edit_choices);
				removeVisual2D(v2d_edit_panel);
			}
			break;
		case 'q': // Editare cladire si trecere in mod editare
			if (!edit_mode) {
				// Sterge obiectul de editat.
				selected = world->erase(cursor_x, cursor_z);
				if (selected != NONE)
					//  Plaseaza unul nou in acceasi pozitie spre a fi mutat sau rotit.
					switch_edit(selected);
			}
			break;
		case 'j': // Selectie 
			if (edit_mode && edit_choice < edit_panel->get_panel_size() - 1) {
				edit_choice++;
				edit_panel->set_choice(edit_choice);
				world->last_placed_x = -1;
				world->last_placed_z = -1;
			}
			break;
		case 'u': // edit up
			if (edit_mode && edit_choice > 0) {
				edit_choice--;
				edit_panel->set_choice(edit_choice);
				world->last_placed_x = -1;
				world->last_placed_z = -1;
			}
			break;
		case 'a': // Muta cursor la stanga
			if (cursor_x > 0)
				cursor_x -= 1;
			break;
		case 'w': // Muta cursor in sus
			if (cursor_z > 0)
				cursor_z -= 1;
			break;
		case 'd': /// Muta cursor la dreapta
			if (cursor_x < NO_SQUARES - 1)
				cursor_x += 1;
			break;
		case 's': // Muta cursor in jos
			if (cursor_z < NO_SQUARES - 1)
				cursor_z += 1;
			break;
		case 'x': // Zoom out
			zoom += 0.1;
			break;
		case 'z': // Zoom in
			if (zoom > 0.1)
				zoom -= 0.1;
			break;
		case 13: // Finalizare asezare cladire sau drum / modificare teren.
			if (edit_mode)
				world->place(v2d_temporary);
			break;
		case 127: // Stergere cladire sau drum.
			if (!edit_mode)
				world->erase(cursor_x, cursor_z);
			break;
		case ',':
		case '<': // Rotatie stanga
			if (edit_mode)
				world->rotate(LEFT, cursor_x, cursor_z);
			break;
		case '.':
		case '>': // Rotatie dreapta
			if (edit_mode)
				world->rotate(RIGHT, cursor_x, cursor_z);
			break;
	}
}

//functia care defineste ce se intampla cand se da click pe mouse
void DrawingWindow::onMouse(int button, int state, int x, int y)
{
}

int main(int argc, char** argv)
{
	//creare fereastra
	DrawingWindow dw(argc, argv, 800, 600, 200, 0, "World Builder");
	//se apeleaza functia init() - in care s-au adaugat obiecte
	dw.init();
	//se intra in bucla principala de desenare - care face posibila desenarea, animatia si procesarea evenimentelor
	dw.run();
	return 0;
}