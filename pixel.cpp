#include <string>
#include <iostream>
#include "Pixels.h"

using namespace std;

//constructeur
Pixel::Pixel()
{
	largeur=0;
	hauteur=0;
}

//destructeur
Pixel::~Pixel()
{
	//On libere l'espace prit par le tableau à deux dimensions
	for(int i=0; i<hauteur ;++i)
	{
		delete []tabPxl[i];
	}
	delete []tabPxl;
}


// **** largeur *****
unsigned long Pixel::donneLargeur()
{
	return largeur;
}

void Pixel::copieLargeur(Pixel &temp)
{
temp.largeur=largeur;
}


// **** hauteur *****
unsigned long Pixel::donneHauteur()
{
	return hauteur;
}

void Pixel::copieHauteur(Pixel &temp)
{
	temp.hauteur=hauteur;
} 