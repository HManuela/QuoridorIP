#pragma once
class Jucator
{
private:
	int finish;
public:
	enum {
		N, S, E, V
	};
	enum {
		G, P, M, R
	};
	int x, y;
	int pereti_ramasi;
	int pion;
	Jucator();
	Jucator(int fin, int culoare, int pereti_ram);
	bool Castigat();
	~Jucator();
};

