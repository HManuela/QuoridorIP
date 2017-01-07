#include "Joc.h"

void Joc::Init()
{

	int nr_pt_pereti = 0;

	for (int i = 0; i < 4; i++)
		if (set_pion[i] == JUCATOR || set_pion[i]==CALCULATOR)
			nr_pt_pereti ++;


	nrjucatori = 0;

	for (int i=0;i<4;i++)
		if (set_pion[i]==JUCATOR || set_pion[i]==CALCULATOR)
			jucatori[nrjucatori++]= new Jucator(i, i, 20 / nr_pt_pereti, set_pion[i]);
	
	tura = 0;
	frame = 0;
	for (int i = 0; i < 20; i++)
		pereti[i].x = pereti[i].y = -1;
	nrpereti = 0;

	input.x = input.y = -1;
	doaction = 0;
	gameOver = false;
}

Joc::Joc()
{
	display = al_create_display(WIDTH, HEIGHT);

	meniu = al_load_bitmap("meniu.png");
	tabla = al_load_bitmap("tabla.png");
	sel_pioni = al_load_bitmap("sel_pioni.png");
	jucatori_png = al_load_bitmap("jucatori.png");
	help = al_load_bitmap("help.png");
	al_convert_mask_to_alpha(jucatori_png, al_map_rgb(255, 0, 255));
	pioni = al_load_bitmap("pioni.png");
	al_convert_mask_to_alpha(pioni, al_map_rgb(176, 71, 44));
	mutari = al_load_bitmap("moves.png");

	font = al_load_font("arial.ttf", 15, ALLEGRO_ALIGN_LEFT);
	font_mare= al_load_font("arial.ttf", 20, ALLEGRO_ALIGN_RIGHT);

	timer = al_create_timer(1.0 / 20);
	event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_start_timer(timer);

	input.x = input.y = -1;
	doaction = 0;
	gameOver = false;
	stare = MENIU;
}


Joc::~Joc()
{
}

void Joc::Run()
{
	while (stare!=EXIT)
	{
		if (stare == MENIU)
		{
			Draw_Meniu();
			gameOver = 0;
			while (stare == MENIU && !gameOver)
			{
				bool input_result = Input();
				Logic_Meniu();
				if (input_result)
				{
					Draw_Meniu();
					
				}
			}
			if (gameOver)
				break;
		}

		if (stare == PREGAME)
		{
			Draw_Pregame();
			gameOver = 0;
			while (stare == PREGAME && !gameOver)
			{
				bool input_result = Input();
				Logic_Pregame();
				if (input_result)
					Draw_Pregame();
			}
		}

		if (stare == HELP)
		{
			Draw_Help();
			gameOver = 0;
			while (stare == HELP && !gameOver)
			{
				bool input_result = Input();
				if (input_result)
					Draw_Help();
			}
		}

		if (stare == JOC)
		{
			Init();
			Draw();
			gameOver = 0;
			while (!gameOver)
			{
				if (jucatori[tura]->tip == CALCULATOR)
				{
					Input();
					Calculator();
					Draw();
				}
				else
				{
					bool input_result = Input();
					Logic();
					if (input_result)
						Draw();
				}
			}
		}
	}
}

void Joc::PunePerete(int x, int y, int orientare)
{
	pereti[nrpereti].x = x;
	pereti[nrpereti].y = y;
	pereti[nrpereti].orientare = orientare;
	if (orientare == VERTICAL)
	{
		matrice_pereti[2 * x][2 * y + 3] = M_PERETE;
		matrice_pereti[2 * x][2 * y + 1] = M_PERETE;
	}
	else
	{
		matrice_pereti[2 * x + 1][2 * y] = M_PERETE;
		matrice_pereti[2 * x + 3][2 * y] = M_PERETE;
	}
	nrpereti++;
	
}

void Joc::ScoatePerete(int x, int y, int orientare)
{
	if (orientare == VERTICAL)
	{
		matrice_pereti[2 * x][2 * y + 3] = M_LIBER;
		matrice_pereti[2 * x][2 * y + 1] = M_LIBER;
	}
	else
	{
		matrice_pereti[2 * x + 1][2 * y] = M_LIBER;
		matrice_pereti[2 * x + 3][2 * y] = M_LIBER;
	}
	nrpereti--;

}



void Joc::MiscareCalculator()
{
	int diagx[4] = { -1, 1, 1,-1 };
	int diagy[4] = { -1,-1, 1, 1 };
	int jx = jucatori[tura]->x;
	int jy = jucatori[tura]->y;
	int rezultat = 100;
	int rdx, rdy;
	for (int i = 0; i < 4; i++)
	{
		if (MiscareValida(jx, jy, jx + diagx[i], jy + diagy[i]))
		{
			int fx, fy;
			if (jucatori[tura]->finish == Jucator::N)
				fx = -1, fy = 0;
			if (jucatori[tura]->finish == Jucator::S)
				fx = -1, fy = 8;
			if (jucatori[tura]->finish == Jucator::E)
				fx = 8, fy = -1;
			if (jucatori[tura]->finish == Jucator::V)
				fx = 0, fy = -1;
			int rez = DistantaFinish(jucatori[tura]->x + diagx[i], jucatori[tura]->y + diagy[i], fx, fy);
			if (rez < rezultat)
			{
				rezultat = rez;
				rdx = diagx[i];
				rdy = diagy[i];
			}
		}
		if (MiscareValida(jx, jy, jx + dx[i], jy + dy[i]))
		{
			int fx, fy;
			if (jucatori[tura]->finish == Jucator::N)
				fx = -1, fy = 0;
			if (jucatori[tura]->finish == Jucator::S)
				fx = -1, fy = 8;
			if (jucatori[tura]->finish == Jucator::E)
				fx = 8, fy = -1;
			if (jucatori[tura]->finish == Jucator::V)
				fx = 0, fy = -1;
			int rez = DistantaFinish(jucatori[tura]->x + dx[i], jucatori[tura]->y + dy[i], fx, fy);
			if (rez < rezultat)
			{
				rezultat = rez;
				rdx = dx[i];
				rdy = dy[i];
			}
		}
		if (MiscareValida(jx, jy, jx + dx[i] * 2, jy + dy[i] * 2))
		{
			int fx, fy;
			if (jucatori[tura]->finish == Jucator::N)
				fx = -1, fy = 0;
			if (jucatori[tura]->finish == Jucator::S)
				fx = -1, fy = 8;
			if (jucatori[tura]->finish == Jucator::E)
				fx = 8, fy = -1;
			if (jucatori[tura]->finish == Jucator::V)
				fx = 0, fy = -1;
			int rez = DistantaFinish(jucatori[tura]->x + dx[i] * 2, jucatori[tura]->y + dy[i] * 2, fx, fy);
			if (rez < rezultat)
			{
				rezultat = rez;
				rdx = dx[i] * 2;
				rdy = dy[i] * 2;
			}
		}

	}

	jucatori[tura]->x = jx + rdx;
	jucatori[tura]->y = jy + rdy;

}

bool Joc::PereteCalculator()
{
	int bestx, besty, besto, raul_cel_mai_mare = 0;// vrem sa marim cat de mult putem cel mai scurt drum pentru ceilalti jucatori
	for (int x = 0; x < 8; x++)
		for (int y = 0; y < 8; y++)
			for (int orientare = VERTICAL; orientare <= ORIZONTAL; orientare++)
				if (PereteValid(jucatori[tura]->pereti_ramasi,x,y,orientare))
				{
					int rezt = TesteazaPerete(x, y, orientare);
					
					if (raul_cel_mai_mare < rezt)
					{
						cout << "rezt:" << rezt << "\n";
						raul_cel_mai_mare = rezt;
						bestx = x;
						besty = y;
						besto = orientare;
					}
				}
	if (bestx == 0 && besty == 0 && besto == 0)
		return 0;
	PunePerete(bestx, besty, besto);
	jucatori[tura]->pereti_ramasi--;
	return 1;
}

int Joc::DistantaFinishJ(int Tura)
{
	int fx, fy;
	if (jucatori[Tura]->finish == Jucator::N)
		fx = -1, fy = 0;
	if (jucatori[Tura]->finish == Jucator::S)
		fx = -1, fy = 8;
	if (jucatori[Tura]->finish == Jucator::E)
		fx = 8, fy = -1;
	if (jucatori[Tura]->finish == Jucator::V)
		fx = 0, fy = -1;
	return DistantaFinish(jucatori[Tura]->x, jucatori[Tura]->y, fx, fy);

}

void Joc::Calculator()
{
	al_rest(0.5);
	if (jucatori[tura]->pereti_ramasi > 0)
	{
		int mindist = DistantaFinishJ(tura);
		cout << "calculator:" << mindist << ' ';
		for (int i = 0; i < nrjucatori; i++)
		{
			int dist = DistantaFinishJ(i);
			cout << "jucator" << i << " " << dist << ' ';
			if (dist < mindist)
			{
				cout << '\n';
				if (PereteCalculator())
				{
					tura = (tura + 1) % nrjucatori;
					return;
				}
			}
		}
		cout << '\n';
	}
	MiscareCalculator();
	tura = (tura + 1) % nrjucatori;
}

