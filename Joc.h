#pragma once
#include "Jucator.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <iostream>
using namespace std;

#define DIM_P 40
#define DIM_SP 10 
#define WIDTH 460
#define HEIGHT 460
class Joc
{
private:
	ALLEGRO_FONT * font;
	ALLEGRO_FONT * font_mare;
	ALLEGRO_DISPLAY* display;
	ALLEGRO_BITMAP * tabla;
	ALLEGRO_BITMAP * pioni;
	ALLEGRO_BITMAP * mutari;
	ALLEGRO_BITMAP * meniu;
	ALLEGRO_BITMAP * sel_pioni;
	ALLEGRO_BITMAP * jucatori_png;
	ALLEGRO_BITMAP * help;
	bool gameOver;
	ALLEGRO_EVENT_QUEUE *event_queue;
	ALLEGRO_TIMER * timer;
	int tura;
	Jucator* jucatori[4];
	int nrjucatori;
	int frame;
	enum {
		PERETE, CASUTA
	};
	enum {
		VERTICAL, ORIZONTAL
	};
	enum {
		M_LIBER, M_PERETE, M_JUCATOR
	};
	enum {
		JOC, MENIU, EXIT, PREGAME, HELP
	};
	int stare;
	int set_pion[4];
	enum TipJucator{
		JUCATOR, CALCULATOR, LIBER
	};
	struct InputJucator {
		int x, y;
		int valid;
		int orientare;
		int tip;
	};
	struct punct {
		int x, y;
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
	void Init();
	Joc();
	~Joc();
	void DeseneazaPion(int x, int y, int pion);
	void DeseneazaJucator(int x, int y, int jucator);
	void DeseneazaCasuta(int x, int y, int valid);
	void DeseneazaTabla();
	void DeseneazaMeniu();
	void DeseneazaPregame();
	void DeseneazaHelp();
	void DeseneazaPerete(int x, int y, int orientare, int permanent, int valid);
	void Arata();
	void Run();
	char Input();
	int DistantaFinish(int jx, int jy, int fx, int fy);
	bool MiscareValida(int jx, int jy, int destx, int desty);
	int TesteazaPerete(int x, int y, int orientare);
	bool PereteValid(int pereti_ramasi, int x, int y, int orientare);
	void PunePerete(int x, int y, int orientare);
	void ScoatePerete(int x, int y, int orientare);
	void Logic();
	void Draw();
	void Draw_Meniu();
	void Logic_Meniu();
	void Draw_Pregame();
	void Draw_Help();
	void Logic_Pregame();
	void MiscareCalculator();
	bool PereteCalculator();
	int DistantaFinishJ(int Tura);
	void Calculator();
};

