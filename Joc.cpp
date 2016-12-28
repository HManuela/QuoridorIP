#include "Joc.h"



Joc::Joc()
{
	i = 0;
	tabla = al_load_bitmap("tabla.png");
	display = al_create_display(460, 460);
	pioni = al_load_bitmap("pioni.png");
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

void Joc::DeseneazaPion(int pion, int lin, int col) // deseneaza pionul in casuta x, y
{
	al_draw_bitmap_region(pioni, pion * 30, 0, 30, 30, DIM_SP + (DIM_P + DIM_SP)*col + 5, DIM_SP + (DIM_P + DIM_SP)*lin + 5, 0);
}

void Joc::DeseneazaTabla()
{
	al_draw_bitmap(tabla, 0, 0, 0);
}

void Joc::Arata()
{
	al_flip_display();
}

void Joc::Run()
{
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

			if (mx>=c1x && mx<c2x && my>=c1y && my<c2y && mx>=DIM_SP && my>=DIM_SP)
				cout << (mx - DIM_SP) / (DIM_P + DIM_SP) << ' ' << (my - DIM_SP) / (DIM_P + DIM_SP) << '\n';
			c1x = mx / (DIM_P + DIM_SP) *(DIM_P + DIM_SP);
			c1y = my / (DIM_P + DIM_SP) *(DIM_P + DIM_SP)+DIM_SP;
			if (mx >= c1x && my >= c1y && mx < c1x + DIM_SP && my < c1y + DIM_P)
				cout << "vertical" << '\n';
			c1x = mx / (DIM_P + DIM_SP)*(DIM_P + DIM_SP) +DIM_SP;
			c1y = my / (DIM_P + DIM_SP) *(DIM_P + DIM_SP);
			if (mx >= c1x && my >= c1y &&mx < c1x + DIM_P && my < c1y + DIM_SP)
				cout << "orizontal" << '\n';

			

		}
	return 0;
	
}

void Joc::Logic()
{
	i = (i + 1) % 9;
}

void Joc::Draw()
{
	DeseneazaTabla();
	DeseneazaPion(1, i, 4);
	Arata();
}
