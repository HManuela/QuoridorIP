#pragma once
#include "Jucator.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
using namespace std;

#define DIM_P 40
#define DIM_SP 10 
#define WIDTH 460
#define HEIGHT 460
class Joc
{
private:
	ALLEGRO_DISPLAY* display;
	ALLEGRO_BITMAP * tabla;
	ALLEGRO_BITMAP * pioni;
	ALLEGRO_BITMAP * mutari;
	bool gameOver;
	ALLEGRO_EVENT_QUEUE *event_queue;
	ALLEGRO_TIMER * timer;
	int tura;
	Jucator* jucatori[4];
	int nrjucatori;
	enum {
		PERETE, CASUTA
	};
	enum {
		VERTICAL, ORIZONTAL
	};
	enum {
		M_LIBER, M_PERETE, M_JUCATOR
	};
	struct InputJucator {
		int x, y;
		int specific;
		int tip;
	};
	InputJucator input;
	int dx[4] = { -1,0,1,0 };
	int dy[4] = { 0,1,0,-1 };
	struct perete {
		int x, y;
		int orientare;
	};
	int nrpereti;
	perete pereti[20];
	bool  doaction;
	int matrice_pereti[20][20];

public:
	Joc();
	~Joc();
	void DeseneazaPion(int x, int y, int pion);
	void DeseneazaCasuta(int x, int y, int valid);
	void DeseneazaTabla();
	void DeseneazaPerete(int x, int y, int orientare, int permanent=0);
	void Arata();
	void Run();
	char Input();
	void Logic();
	void Draw();
	bool PereteValid();
};

