#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#define DIM_P 40
#define DIM_SP 10 

ALLEGRO_DISPLAY* display;

ALLEGRO_BITMAP * tabla;
ALLEGRO_BITMAP * pioni;

void deseneaza_pion(int pion, int lin, int col) // deseneaza pionul in casuta x, y
{
	al_draw_bitmap_region(pioni, pion*30, 0, 30, 30,DIM_SP+(DIM_P+DIM_SP)*col+5, DIM_SP + (DIM_P + DIM_SP)*lin +5, 0);
}


int main()
{
	al_init();
	al_init_image_addon();

	display = al_create_display(460, 460);
	tabla = al_load_bitmap("tabla.png");
	pioni = al_load_bitmap("pioni.png");


	for (int i = 0; i < 9; i++)
	{
		al_draw_bitmap(tabla, 0, 0, 0);
		deseneaza_pion(1, i, 4);
		al_flip_display();
		al_rest(0.5);
	}


	
	return 0;
}