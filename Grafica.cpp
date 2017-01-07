#include "Joc.h"


void Joc::DeseneazaPion(int x, int y, int pion) // deseneaza pionul in casuta x, y
{
	if (pion == jucatori[tura]->pion)
		al_draw_circle(DIM_SP + (DIM_P + DIM_SP)*x + 5 + 15, DIM_SP + (DIM_P + DIM_SP)*y + 5 + 15, 20, al_map_rgb(200, 160, 116), 2);
	al_draw_bitmap_region(pioni, pion * 30, 0, 30, 30, DIM_SP + (DIM_P + DIM_SP)*x + 5, DIM_SP + (DIM_P + DIM_SP)*y + 5, 0);
}

void Joc::DeseneazaJucator(int x, int y, int jucator)
{
	al_draw_bitmap_region(jucatori_png, jucator * 30, 0, 30, 30, DIM_SP + (DIM_P + DIM_SP)*x + 5, DIM_SP + (DIM_P + DIM_SP)*y + 5, 0);
}
void Joc::DeseneazaCasuta(int x, int y, int valid)
{
	//valid = valid - 2;
	al_draw_bitmap_region(mutari, (1 - valid) * 40, 0, 40, 40, DIM_SP + (DIM_P + DIM_SP)*x, DIM_SP + (DIM_P + DIM_SP)*y, 0);
}

void Joc::DeseneazaTabla()
{
	al_draw_bitmap(tabla, 0, 0, 0);
}

void Joc::DeseneazaMeniu()
{
	al_draw_bitmap(meniu, 0, 0, 0);
}

void Joc::DeseneazaPregame()
{
	al_draw_bitmap(sel_pioni, 0, 0, 0);
}

void Joc::DeseneazaHelp()
{
	al_draw_bitmap(help, 0, 0, 0);
}

void Joc::DeseneazaPerete(int x, int y, int orientare, int permanent, int valid)
{
	if ((x == -1 && y == -1) || !valid) return;
	x = (DIM_P + DIM_SP)*x + DIM_SP*orientare;
	y = (DIM_P + DIM_SP)*y + DIM_SP*(1 - orientare);

	if (!permanent)
	{
		char text_pereti[20];
		sprintf_s(text_pereti, "Pereti ramasi:%d", jucatori[tura]->pereti_ramasi);
		if (input.x >= 6 && orientare == VERTICAL)
			al_draw_text(font, al_map_rgb(250, 200, 150), x - 110, y + 10, 0, text_pereti);
		else
			if (orientare == ORIZONTAL)
				al_draw_text(font, al_map_rgb(250, 200, 150), x - 15, y + 10, 0, text_pereti);
			else
				al_draw_text(font, al_map_rgb(250, 200, 150), x + 10, y + 10, 0, text_pereti);

		al_draw_filled_rectangle(x, y,
			x + DIM_SP + DIM_P * 2 * orientare,
			y + DIM_SP + DIM_P * 2 * (1 - orientare),
			//al_map_rgb(120,120,120));
			al_map_rgb(200, 160, 116));
	}
	else
		al_draw_filled_rectangle(x, y,
			x + DIM_SP + DIM_P * 2 * orientare,
			y + DIM_SP + DIM_P * 2 * (1 - orientare),
			al_map_rgb(255, 226, 159));

}

void Joc::Arata()
{
	al_flip_display();
}


void Joc::Draw()
{
	int i;

	DeseneazaTabla();

	for (i = 0; i < nrjucatori; i++)
	{
		int jx, jy;
		jx = jucatori[i]->x;
		jy = jucatori[i]->y;
		DeseneazaPion(jx, jy, jucatori[i]->pion);
	}
	for (i = 0; i < nrpereti; i++)
		DeseneazaPerete(pereti[i].x, pereti[i].y, pereti[i].orientare, 1, 1);

	if (input.tip == PERETE)
		DeseneazaPerete(input.x, input.y, input.orientare, 0, input.valid);
	else
	{
		bool suprapunere = 0;
		for (i = 0; i < nrjucatori; i++)
		{
			int jx, jy;
			jx = jucatori[i]->x;
			jy = jucatori[i]->y;
			if ((input.x == jx && input.y == jy))
				suprapunere = 1;
		}

		if (!suprapunere)
			DeseneazaCasuta(input.x, input.y, input.valid);
	}

	for (int j = 0; j < nrjucatori; j++)
	{
		if (jucatori[j]->Castigat())
		{
			al_draw_filled_rectangle(2 * DIM_P + 3 * DIM_SP, 2 * DIM_P + 3 * DIM_SP,
				7 * DIM_P + 7 * DIM_SP, 5 * DIM_P + 5 * DIM_SP,
				al_map_rgb(200, 160, 116));
			al_draw_textf(font_mare, al_map_rgb(104, 42, 41), 2 * DIM_P + 4 * DIM_SP, 3 * DIM_P + 4 * DIM_SP, 0, "A castigat %s", jucatori[j]->nume_culoare);
			Arata();
			al_rest(2);
			gameOver = 1;

		}
	}

	Arata();
}


void Joc::Draw_Meniu()
{
	DeseneazaMeniu();
	Arata();
}


void Joc::Draw_Pregame()
{
	DeseneazaPregame();
	DeseneazaJucator(2, 4, set_pion[Jucator::STANGA]);
	DeseneazaJucator(6, 4, set_pion[Jucator::DREAPTA]);
	DeseneazaJucator(4, 2, set_pion[Jucator::SUS]);
	DeseneazaJucator(4, 6, set_pion[Jucator::JOS]);
	Arata();
}

void Joc::Draw_Help()
{
	DeseneazaHelp();
	Arata();
}

