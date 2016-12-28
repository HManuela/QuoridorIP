#include "Joc.h"

int main()
{
	al_init();
	al_init_image_addon();
	al_install_keyboard();
	al_install_mouse();
	al_init_primitives_addon();
	Joc* joc = new Joc();

	joc->Run();

	
	return 0;
}