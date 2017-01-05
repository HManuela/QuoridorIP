#pragma once
class Jucator
{
private:
	int finish;
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
	Jucator();
	Jucator(int fin, int culoare, int pereti_ram);
	bool Castigat();
	~Jucator();
};

