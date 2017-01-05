#include "Joc.h"

void Joc::Init()
{

	int nr_pt_pereti = 0;

	for (int i = 0; i < 4; i++)
		if (set_pion[i] == 0)
			nr_pt_pereti ++;

	nrjucatori = 0;

	for (int i=0;i<4;i++)
		if (set_pion[i]==0)
			jucatori[nrjucatori++]= new Jucator(i, i, 20 / nr_pt_pereti);
	
	tura = 0;
	frame = 0;
	/*jucatori[0] = new Jucator(Jucator::S, Jucator::G, 20 / nrjucatori);
	jucatori[1] = new Jucator(Jucator::N, Jucator::R, 20 / nrjucatori);
	jucatori[2] = new Jucator(Jucator::E, Jucator::M, 20 / nrjucatori);
	jucatori[3] = new Jucator(Jucator::V, Jucator::P, 20 / nrjucatori);*/
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
	al_convert_mask_to_alpha(jucatori_png, al_map_rgb(255, 0, 255));
	pioni = al_load_bitmap("pioni.png");
	al_convert_mask_to_alpha(pioni, al_map_rgb(176, 71, 44));
	mutari = al_load_bitmap("moves.png");

	font_left = al_load_font("arial.ttf", 15, ALLEGRO_ALIGN_LEFT);
	font_right= al_load_font("arial.ttf", 15, ALLEGRO_ALIGN_RIGHT);

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

void Joc::DeseneazaPion(int x, int y, int pion) // deseneaza pionul in casuta x, y
{
	if (pion == tura)
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
	al_draw_bitmap_region(mutari,(1- valid) * 40, 0, 40, 40, DIM_SP + (DIM_P + DIM_SP)*x, DIM_SP + (DIM_P + DIM_SP)*y, 0);
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

void Joc::DeseneazaPerete(int x, int y, int orientare, int permanent,int valid)
{
	if ((x == -1 && y == -1) || !valid) return;
	//cout << "desenez" << orientare;
	x = (DIM_P+DIM_SP)*x + DIM_SP*orientare;
	y = (DIM_P+DIM_SP)*y + DIM_SP*(1 - orientare);

	if (!permanent)
	{
		char text_pereti[20]; 
		sprintf_s(text_pereti, "Pereti ramasi:%d", jucatori[tura]->pereti_ramasi);
		if (input.x>=6 && orientare==VERTICAL)
			al_draw_text(font_right, al_map_rgb(250, 200, 150), x - 100, y + 10, 0, text_pereti);
		else
			if (orientare==ORIZONTAL)
				al_draw_text(font_left, al_map_rgb(250, 200, 150), x - 5, y + 10, 0, text_pereti);
			else
				al_draw_text(font_left, al_map_rgb(250, 200, 150), x + 10, y + 10, 0, text_pereti);

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
				{
					Draw_Pregame();

				}
			}
		

		}

		if (stare == JOC)
		{
			Init();
			Draw();
			gameOver = 0;
			while (!gameOver)
			{
				bool input_result = Input();
				Logic();
				if (input_result)
				{
					Draw();
				}
			}
		}
	}
}

char Joc::Input()
{
	ALLEGRO_EVENT ev;
	al_wait_for_event(event_queue, &ev);
	if (ev.type == ALLEGRO_EVENT_TIMER) {
		return 0;
	}
	else
	if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
	{
		switch (ev.keyboard.keycode) {
		case ALLEGRO_KEY_ESCAPE:
			gameOver = true;
			stare = MENIU;
			break;
		}
		return 1;
	}
	else
		if (ev.type == ALLEGRO_EVENT_MOUSE_AXES)
		{
			int mx = ev.mouse.x;
			int my = ev.mouse.y;
			int c1x, c1y, c2x, c2y;
			c1x = (mx - DIM_SP) / (DIM_P + DIM_SP)*(DIM_P + DIM_SP)+DIM_SP;
			c1y = (my - DIM_SP) / (DIM_P + DIM_SP)*(DIM_P + DIM_SP)+DIM_SP;
			c2x = c1x + DIM_P;
			c2y = c1y + DIM_P;

			if (mx >= c1x && mx < c2x && my >= c1y && my < c2y && mx >= DIM_SP && my >= DIM_SP)
			{

				//cout << (mx - DIM_SP) / (DIM_P + DIM_SP) << ' ' << (my - DIM_SP) / (DIM_P + DIM_SP) << '\n';
				input.x = c1x / (DIM_P + DIM_SP);
				input.y = c1y / (DIM_P + DIM_SP);
				input.valid = 0;
				input.tip = CASUTA;
				return 1;
			}
			c1x = mx / (DIM_P + DIM_SP) *(DIM_P + DIM_SP);
			c1y = my / (DIM_P + DIM_SP) *(DIM_P + DIM_SP)+DIM_SP;
			if (mx >= c1x && my >= c1y && mx < c1x + DIM_SP && my < c1y + DIM_P && mx>DIM_SP && mx < WIDTH - DIM_SP)
			{
				//cout << "vertical" << '\n';
				input.x = c1x / (DIM_P + DIM_SP);
				input.y = c1y / (DIM_P + DIM_SP);
				input.orientare = VERTICAL;
				input.tip = PERETE;
				return 1;
			}
			c1x = mx / (DIM_P + DIM_SP)*(DIM_P + DIM_SP) +DIM_SP;
			c1y = my / (DIM_P + DIM_SP) *(DIM_P + DIM_SP);
			if (mx >= c1x && my >= c1y &&mx < c1x + DIM_P && my < c1y + DIM_SP  && my>DIM_SP && my < HEIGHT - DIM_SP)
			{
				//cout << "orizontal" << '\n';
				input.x = c1x / (DIM_P + DIM_SP);
				input.y = c1y / (DIM_P + DIM_SP);
				input.orientare = ORIZONTAL;
				input.tip = PERETE;
				return 1;
			}
			return 1;
		}
		else 
			if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
			{
				doaction = 1;
				return 1;
			}
		else
			if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
				gameOver = true,
				stare=EXIT;

	return 0;
	
}

int Joc::DistantaFinish(int jx, int jy, int fx, int fy)
{
	int diagx[4] = { -1, 1, 1,-1 };
	int diagy[4] = { -1,-1, 1, 1 };
	int path[10][10];

	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			path[i][j] = -1;

	punct coada[90];
	int start, fin;
	start = 0;
	
	coada[start].x = jx;
	coada[start].y = jy;
	path[jx][jy] = 0;
	fin = 0;
	while (start <= fin)
	{
		for (int i = 0; i < 4; i++)
		{

			if (path[coada[start].x + diagx[i]][coada[start].y + diagy[i]] == -1)
			if (MiscareValida(coada[start].x, coada[start].y, coada[start].x + diagx[i], coada[start].y + diagy[i]))
			{
				fin++;
				coada[fin].x = coada[start].x + diagx[i];
				coada[fin].y = coada[start].y + diagy[i];
				path[coada[fin].x][coada[fin].y] = path[coada[start].x][coada[start].y]+1;
			}

			if (path[coada[start].x + dx[i]][coada[start].y + dy[i]] == -1)
			if (MiscareValida(coada[start].x, coada[start].y, coada[start].x + dx[i], coada[start].y + dy[i]))
			{
				fin++;
				coada[fin].x = coada[start].x + dx[i];
				coada[fin].y = coada[start].y + dy[i];
				path[coada[fin].x][coada[fin].y] = path[coada[start].x][coada[start].y]+1;
			}

			if (path[coada[start].x + dx[i] * 2][coada[start].y + dy[i] * 2]==-1)
			if (MiscareValida(coada[start].x, coada[start].y, coada[start].x + dx[i]*2, coada[start].y + dy[i]*2))
			{
				fin++;
				coada[fin].x = coada[start].x + dx[i]*2;
				coada[fin].y = coada[start].y + dy[i]*2;
				path[coada[fin].x][coada[fin].y] = path[coada[start].x][coada[start].y]+1;
			}
		}
		start++;
	}
	int min = 100;

	if (fx == -1)
		for (int i = 0; i < 9; i++)
			if (path[i][fy] != -1)
				if (path[i][fy] < min)
					min = path[i][fy];
	if (fy == -1)
		for (int i = 0; i < 9; i++)
			if (path[fx][i]!=-1)
				if (path[fx][i] < min)
					min = path[fx][i];
	return min;
}

bool Joc::MiscareValida(int jx, int jy, int destx, int desty)
{
	if (!(jx <= 8 && jy <= 8 && destx <= 8 && desty <= 8 &&
		jx >= 0 && jy >= 0 && destx >= 0 && desty >= 0))
		return 0;
	int m_jx = 2 * jx + 1;
	int m_jy = 2 * jy + 1;
	int m_dx = 2 * destx + 1;
	int m_dy = 2 * desty + 1;
	if (matrice_pereti[(m_jx + m_dx) / 2][(m_jy + m_dy) / 2] != 0)
		return 0;
	//----------------------------------------

	//verific daca pot face o miscare mai complicata (salt dublu / in laterala)
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < nrjucatori; j++)
		{
			if (jx + dx[i] == jucatori[j]->x &&
				jy + dy[i] == jucatori[j]->y)
			{
				if (destx == jx + dx[i] + dx[i] &&
					desty == jy + dy[i] + dy[i])
				{
					if (matrice_pereti[jx * 2 + 1 + dx[i]][jy * 2 + 1 + dy[i]] == M_LIBER
						&& matrice_pereti[jx * 2 + 1 + dx[i] * 3][jy * 2 + 1 + dy[i] * 3] == M_LIBER)
						if (matrice_pereti[destx * 2 + 1][desty * 2 + 1] == M_LIBER)
							return 1;
				}
			}
		}
		for (int j = 0; j < nrjucatori; j++)
		{
			if (matrice_pereti[jx * 2 + 1 + dx[i]][jy * 2 + 1 + dy[i]] == M_LIBER
				&& matrice_pereti[jx * 2 + 1 + dx[i] * 3][jy * 2 + 1 + dy[i] * 3] == M_PERETE)
			{
				if (jx + dx[i] == jucatori[j]->x &&
					jy + dy[i] == jucatori[j]->y)
				{
					for (int d = 0; d < 4; d++)
						if (matrice_pereti[(jx + dx[i] + dx[d]) * 2 + 1][(jy + dy[i] + dy[d]) * 2 + 1] == M_LIBER &&
							destx == jx + dx[i] + dx[d] &&
							desty == jy + dy[i] + dy[d]) //destinatia e libera si cea dorita
							if (matrice_pereti[(jx + dx[i]) * 2 + 1 + dx[d]][(jy + dy[i]) * 2 + 1 + dy[d]] == M_LIBER) // daca nu e perete
								return 1;
				}
			}
		}
	}

	for (int j = 0; j < nrjucatori; j++)
		if (destx == jucatori[j]->x && desty == jucatori[j]->y)
			return 0;
	for (int i = 0; i < 4; i++)
		if (destx + dx[i] == jx && desty + dy[i] == jy)
			return 1;

	return 0;
}

bool Joc::PereteValid(int pereti_ramasi, int x, int y, int orientare)
{
	int i;
	if (pereti_ramasi <= 0)
		return 0;
	for (i = 0; i < nrpereti; i++)
	{
		if (pereti[i].orientare == orientare) // peretii sa nu se suprapuna
			if (orientare == VERTICAL)
			{
				if (abs(pereti[i].y - y) < 2 && x == pereti[i].x)
					return 0;
			}
			else
			{
				if (abs(pereti[i].x - x) < 2 && y == pereti[i].y)
					return 0;
			}

		if (orientare == VERTICAL && pereti[i].orientare == ORIZONTAL) //sa nu se incruciseze (exista un singur caz de incrucisare - pct de inceput al fiecarui perete sa fie in diagonala)
		{
			if (pereti[i].y - y == 1 && x - pereti[i].x == 1)
				return 0;
		}
		if (orientare == ORIZONTAL && pereti[i].orientare == VERTICAL)
		{
			if (pereti[i].x - x == 1 && y - pereti[i].y == 1)
				return 0;
		}
	}
	//return 1;
	PunePerete(x, y, orientare);
	for (int i = 0; i < nrjucatori; i++)
	{
		int fx, fy;
		if (jucatori[i]->finish == Jucator::N)
			fx = -1, fy = 0;
		if (jucatori[i]->finish == Jucator::S)
			fx = -1, fy = 8;
		if (jucatori[i]->finish == Jucator::E)
			fx = 8, fy = -1;
		if (jucatori[i]->finish == Jucator::V)
			fx = 0, fy = -1;

		int rez = DistantaFinish(jucatori[i]->x, jucatori[i]->y, fx, fy);
		cout <<i<<' '<< rez << '\n';
		if (rez == 100)
		{
			ScoatePerete(x, y, orientare);
			return 0;
		}
	}
	ScoatePerete(x, y, orientare);
	return 1;
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



void Joc::Logic()
{	
	if (input.tip == PERETE)
	{
		if (input.orientare == ORIZONTAL && input.x >= 8) input.x = 7;
		if (input.orientare == VERTICAL && input.y >= 8) input.y = 7;
		input.valid = PereteValid(jucatori[tura]->pereti_ramasi, input.x, input.y, input.orientare);
	}
	if (input.tip == CASUTA)
		input.valid = MiscareValida(jucatori[tura]->x,jucatori[tura]->y,input.x, input.y);

		


	if (doaction == 1)
	{
		if (input.tip == PERETE)
		{
			if (input.valid)
			{
				PunePerete(input.x, input.y, input.orientare);

				jucatori[tura]->pereti_ramasi--;
				tura = (tura + 1) % nrjucatori;
			}
		}
		if (input.tip == CASUTA)
		{
			if (input.valid)
			{
				matrice_pereti[jucatori[tura]->x][jucatori[tura]->y] = M_LIBER;
				jucatori[tura]->x = input.x;
				jucatori[tura]->y = input.y;
				matrice_pereti[jucatori[tura]->x][jucatori[tura]->y] = M_JUCATOR;
				tura = (tura + 1) % nrjucatori;
				input.valid = 0;
			}

		}
		//cout << "este tura lui " << tura << "\n";
		//verific daca e gata jocul
		for (int j = 0; j < nrjucatori; j++)
		{
			if (jucatori[j]->Castigat())
			{
				cout << "A castigat " << j<<'\n';
			}
		}
		doaction = 0;
	}
	
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

	Arata();
}


void Joc::Draw_Meniu()
{
	DeseneazaMeniu();
	Arata();
}

void Joc::Logic_Meniu()
{
	//cout << input.x << ' ' << input.y << '\n';
	if (doaction == 1)
	{
		if (input.y == 3 && input.x >= 3 && input.x <= 5)
		{
			//play
			stare = PREGAME;
		}
		if (input.y == 4 && input.x >= 3 && input.x <= 5)
		{
			//help
		}
		if (input.y == 5 && input.x >= 3 && input.x <= 5)
		{
			stare = EXIT;
		}
		doaction = 0;
	}
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

void Joc::Logic_Pregame()
{
	//cout << input.x << ' ' << input.y << '\n';
	if (doaction == 1)
	{
		if (input.y == 4 && input.x == 4 )
		{
			//play
			stare = JOC;
		}
		if (input.y == 1 && input.x == 4 ) // galben sus 
			set_pion[Jucator::G] = (set_pion[Jucator::G] + 1) % 3;
	
		if (input.y == 3 && input.x == 4 ) // galben jos
			set_pion[Jucator::G] = (set_pion[Jucator::G] + 2) % 3;
		
		if (input.y == 5 && input.x == 4 ) //rosu sus 
			set_pion[Jucator::R] = (set_pion[Jucator::R] + 1) % 3;
		
		if (input.y == 7 && input.x == 4 ) // rosu jos 
			set_pion[Jucator::R] = (set_pion[Jucator::R] + 2) % 3;
		
		if (input.y == 4 && input.x == 1 ) // maro stanga 
			set_pion[Jucator::M] = (set_pion[Jucator::M] + 1) % 3;
		
		if (input.y == 4 && input.x == 3 ) // maro dreapta
			set_pion[Jucator::M] = (set_pion[Jucator::M] + 2) % 3;
		
		if (input.y == 4 && input.x == 5 ) // portocaliu stanga
			set_pion[Jucator::P] = (set_pion[Jucator::P] + 1) % 3;
		
		if (input.y == 4 && input.x == 7 ) // portocaliu dreapta
			set_pion[Jucator::P] = (set_pion[Jucator::P] + 2) % 3;
	
		doaction = 0;
	}
	
}