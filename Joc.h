#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <iostream>
using namespace std;

#define DIM_P 40
#define DIM_SP 10 

class Joc
{
private:
	ALLEGRO_DISPLAY* display;
	ALLEGRO_BITMAP * tabla;
	ALLEGRO_BITMAP * pioni;
	bool gameOver;
	ALLEGRO_EVENT_QUEUE *event_queue;
	ALLEGRO_TIMER * timer;
	int i;
public:
	Joc();
	~Joc();
	void DeseneazaPion(int pion, int lin, int col);
	void DeseneazaTabla();
	void Arata();
	void Run();
	char Input();
	void Logic();
	void Draw();
};

