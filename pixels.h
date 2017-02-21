#include <iostream>

#ifndef DEF_PIXEL
#define DEF_PIXEL
class Pixel{
protected:
int largeur;
int hauteur;
unsigned char **tabpxl;

public :
	unsigned char GetPixel(int lig, int col){return tabpxl[lig][col];};
	void SetPixel(int lig, int col, unsigned char val){tabpxl[lig][col]=val;};
	Pixel(){largeur=0;hauteur=0;};
	//int GetLargeur(){return largeur;};
	//int GetHauteur(){return hauteur;};
	//void SetLargeur(Pixel &temp){temp.largeur=largeur;};
	//void SetHauteur(Pixel &temp){temp.hauteur=hauteur;};
	//void SetHauteur(int val){hauteur=val;};
	//void SetLargeur(int val){largeur=val;};
};


#endif 