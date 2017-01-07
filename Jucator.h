#pragma once
#include<iostream>
using namespace std;

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

	int tip;

	Jucator();
	Jucator(int fin, int culoare, int pereti_ram, int Tip);
	bool Castigat();
	~Jucator();
	char nume_culoare[15];
	
};

