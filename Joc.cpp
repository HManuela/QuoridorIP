#include "Joc.h"



Joc::Joc()
{
	jx = 4;
	jy = 1;
	tabla = al_load_bitmap("tabla.png");
	display = al_create_display(WIDTH, HEIGHT);
	pioni = al_load_bitmap("pioni.png");
	mutari = al_load_bitmap("moves.png");

	gameOver = false;
	timer = al_create_timer(1.0 / 20);
	event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_start_timer(timer);


}


Joc::~Joc()
{
}

void Joc::DeseneazaPion(int x, int y, int pion) // deseneaza pionul in casuta x, y
{
	al_draw_bitmap_region(pioni, pion * 30, 0, 30, 30, DIM_SP + (DIM_P + DIM_SP)*x + 5, DIM_SP + (DIM_P + DIM_SP)*y + 5, 0);
}

void Joc::DeseneazaCasuta(int x, int y, int valid)
{
	al_draw_bitmap_region(mutari,(1- valid) * 40, 0, 40, 40, DIM_SP + (DIM_P + DIM_SP)*x, DIM_SP + (DIM_P + DIM_SP)*y, 0);
}

void Joc::DeseneazaTabla()
{
	al_draw_bitmap(tabla, 0, 0, 0);
}


/*
1 pentru orizontal
0 pentru vertical
*/
void Joc::DeseneazaPerete(int x, int y, int orientare, int permanent)
{
	if (x == -1 && y == -1) return;
	if ( orientare==1 && x >= 8) x = 7;
	if (orientare==0 && y >= 8) y = 7;
	x = (DIM_P+DIM_SP)*x + DIM_SP*orientare;
	y = (DIM_P+DIM_SP)*y + DIM_SP*(1 - orientare);
	if (!permanent)
	al_draw_filled_rectangle(x, y,
		x + DIM_SP + DIM_P * 2 * orientare, 
		y + DIM_SP + DIM_P * 2 * (1 - orientare),
		al_map_rgb(120,120,120));
		//al_map_rgb(200,160,116));
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
	Draw();
	while (!gameOver)
	{
		if (Input())
		{
			Logic();
			Draw();
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
				cout << (mx - DIM_SP) / (DIM_P + DIM_SP) << ' ' << (my - DIM_SP) / (DIM_P + DIM_SP) << '\n';
				input.x = c1x / (DIM_P + DIM_SP);
				input.y = c1y / (DIM_P + DIM_SP);
				input.specific = 0;
				input.tip = CASUTA;
			}
			c1x = mx / (DIM_P + DIM_SP) *(DIM_P + DIM_SP);
			c1y = my / (DIM_P + DIM_SP) *(DIM_P + DIM_SP)+DIM_SP;
			if (mx >= c1x && my >= c1y && mx < c1x + DIM_SP && my < c1y + DIM_P && mx>DIM_SP && mx < WIDTH - DIM_SP)
			{
				cout << "vertical" << '\n';
				input.x = c1x / (DIM_P + DIM_SP);
				input.y = c1y / (DIM_P + DIM_SP);
				input.specific = 0;
				input.tip = PERETE;
			}
			c1x = mx / (DIM_P + DIM_SP)*(DIM_P + DIM_SP) +DIM_SP;
			c1y = my / (DIM_P + DIM_SP) *(DIM_P + DIM_SP);
			if (mx >= c1x && my >= c1y &&mx < c1x + DIM_P && my < c1y + DIM_SP  && my>DIM_SP && my < HEIGHT - DIM_SP)
			{
				cout << "orizontal" << '\n';
				input.x = c1x / (DIM_P + DIM_SP);
				input.y = c1y / (DIM_P + DIM_SP);
				input.specific = 1;
				input.tip = PERETE;
			}
			return 1;
		}
		else
			if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
				gameOver = true;

	return 0;
	
}

void Joc::Logic()
{
	int i;
	for (i = 0; i < 4; i++)
		if (input.x + dx[i] == jx && input.y + dy[i] == jy)
		{
			input.specific = 1;
			break;
		}
	
}

void Joc::Draw()
{
	DeseneazaTabla();
	DeseneazaPion(jx, jy, 1);
	if (input.tip == PERETE)
		DeseneazaPerete(input.x, input.y, input.specific, 0);
	else
		DeseneazaCasuta(input.x, input.y, input.specific);
	
	Arata();
}
