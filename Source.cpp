#include "Joc.h"

int main()
{
	al_init();
	al_init_image_addon();
	al_install_keyboard();
	al_install_mouse();

	Joc* joc = new Joc();

	joc->Run();

	
	return 0;
}