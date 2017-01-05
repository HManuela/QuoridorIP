#pragma once
class Jucator
{
private:
	
public:
	enum {
		S, V, E, N
	};
	enum {
		G, P, M, R
	};
	enum {
		SUS, DREAPTA, STANGA, JOS
	};
	int x, y;
	int pereti_ramasi;
	int pion;
	int finish;
	Jucator();
	Jucator(int fin, int culoare, int pereti_ram);
	bool Castigat();
	~Jucator();
};

