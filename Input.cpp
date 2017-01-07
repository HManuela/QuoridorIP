#include "Joc.h"
char Joc::Input()
{
	ALLEGRO_EVENT ev;
	al_wait_for_event(event_queue, &ev);
	
	if (ev.type == ALLEGRO_EVENT_TIMER) {
		while (al_peek_next_event(event_queue, &ev))
			if (ev.type == ALLEGRO_EVENT_TIMER)
				al_drop_next_event(event_queue);
			else
				break;
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
				c1x = (mx - DIM_SP) / (DIM_P + DIM_SP)*(DIM_P + DIM_SP) + DIM_SP;
				c1y = (my - DIM_SP) / (DIM_P + DIM_SP)*(DIM_P + DIM_SP) + DIM_SP;
				c2x = c1x + DIM_P;
				c2y = c1y + DIM_P;

				if (mx >= c1x && mx < c2x && my >= c1y && my < c2y && mx >= DIM_SP && my >= DIM_SP)
				{

					input.x = c1x / (DIM_P + DIM_SP);
					input.y = c1y / (DIM_P + DIM_SP);
					input.valid = 0;
					input.tip = CASUTA;
					return 1;
				}
				c1x = mx / (DIM_P + DIM_SP) *(DIM_P + DIM_SP);
				c1y = my / (DIM_P + DIM_SP) *(DIM_P + DIM_SP) + DIM_SP;
				if (mx >= c1x && my >= c1y && mx < c1x + DIM_SP && my < c1y + DIM_P && mx>DIM_SP && mx < WIDTH - DIM_SP)
				{
					input.x = c1x / (DIM_P + DIM_SP);
					input.y = c1y / (DIM_P + DIM_SP);
					input.orientare = VERTICAL;
					input.tip = PERETE;
					return 1;
				}
				c1x = mx / (DIM_P + DIM_SP)*(DIM_P + DIM_SP) + DIM_SP;
				c1y = my / (DIM_P + DIM_SP) *(DIM_P + DIM_SP);
				if (mx >= c1x && my >= c1y &&mx < c1x + DIM_P && my < c1y + DIM_SP  && my>DIM_SP && my < HEIGHT - DIM_SP)
				{
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
						stare = EXIT;

	return 0;

}
