#include <fstream>
#include <iostream>
#include "ImageBMP.h"


#define exp_huit 256 //2^8
#define exp_seize 65536 //2^16
#define exp_vingtquatre 16777216 //2^24

using namespace std;

ImageBMP::ImageBMP ()
{
	Type="Null";
	Bites=0;
	taillepalette=0;
	hauteur=largeur=0;
}


unsigned long ImageBMP::donnetaillefichier()
{
	unsigned long taille;

	if (Bites==8)
		taille =hauteur*largeur+36+taillepalette+2;
	else 
		if (Bites==24)
			taille =hauteur*largeur*3+36+taillepalette+2;

	return taille;
}



int ImageBMP::chargerFichier (char * fichier)
{
	//variable à implenter
	ifstream fichier_in; //Pour ouvrir un fichier
	int i,k=1,x,y,ok=1;
	fichier_in.open (fichier,ios::in | ios::binary);

	//On récupère l'entête du fichier
	for (i=0;i<=13;i++)
	{
		HeaderFile[k]=fichier_in.get();
		k++;
	}

	//On récupère l'entête du bmp
	if (HeaderFile[1]=='B' && HeaderFile[2]=='M')
	{
		Type="BMP";
		k=1;
		for (i=14;i<=35;i++)
		{
			HeaderBMP[k]=fichier_in.get();
			k++;
		}

		Bites=HeaderBMP[15] ; //Sur quel code
		//On recupère les dimensions de l'image
		largeur = HeaderBMP[5]+HeaderBMP[6]*exp_huit+ HeaderBMP[7]*exp_seize+HeaderBMP[8]*exp_vingtquatre;
		hauteur = HeaderBMP[9]+HeaderBMP[10]*exp_huit+ HeaderBMP[11]*exp_seize+HeaderBMP[12]*exp_vingtquatre;

		if (largeur%2!=0)
		{
			largeur++;//pour gerer les fichiers aux largeurs impaires (Un fichier aux largeur impaire à en plus un dernier pixel codé 00 donc a un nombre paire de pixel)
			ok=2;//on indique qu'on a une largeur impaire
		}

		//calcule de la taille de la palette
		taillepalette=(HeaderFile[11] +HeaderFile[12]*exp_huit+ HeaderFile[13]*exp_seize+ HeaderFile[14]* exp_vingtquatre)-36;
		//Pour creer la pallete de l'image si elle existe
		if (taillepalette!=0)
		{
		PaletteBMP= new unsigned char[taillepalette+1];
		k=1;
		for (i=1;i<taillepalette+1;i++)
		{
		PaletteBMP[k]=fichier_in.get();
		k++;
		}
		}
		if (Bites==8)//Le programme ne gere à l'heure actuel
		{

			//Creation du tableau de pixels
			//L'image dans le fichier binaire est codé à partir du premier pixel sur la dernière ligne
			x=0;
			y=hauteur;
			for (y=hauteur;y>0;y--)
			{
				for (x=0;x<largeur;x++)
					tabpxl[x][y]=fichier_in.get();

			}


		}
		else
		{
			return -2;//Si Codage n'est pas non géré
		}
	}
	else
		return -1; //Ce n'est pas un bmp

fichier_in.close();
return ok;
}


void ImageBMP::sauverFichier (char *fichier)
{
	unsigned long x;
	unsigned long taille;
	unsigned char*data= new unsigned char;
	data=ImageToData();
	ofstream image_out;
	image_out.open(fichier, ios::out | ios::binary | ios::trunc);

	taille=donnetaillefichier();

	for (x=0;x<taille-2;x++)
		image_out<<data[x];

	image_out.close();
}


unsigned char * ImageBMP::ImageToData()
{

int i,k=1;
int x,y;
unsigned char *DataImage;

if (Bites==8)
{
	DataImage = new unsigned char [taillepalette + 36 + hauteur*largeur + 2];
}
else 
	if (Bites==24)
	{
		DataImage=new unsigned char [taillepalette + 36 + hauteur*largeur*3 + 2];
	}

//On recopie le HEADERFILE
for (i=0;i<=0x0D;i++)
{
	DataImage[i] = HeaderFile[k];
	k++;
}

k=1;
//On recopie le HEADBMP
for (i=14;i<=35;i++)
{
	DataImage[i] = HeaderBMP[k];
	k++;
}

//On recopie la pallete si elle existe
if (taillepalette!=0)
{
	k=1;
	for (i=36;i<taillepalette+36;i++)
	{
		DataImage[i] = PaletteBMP[k];
		k++;
	}
}

//On recopie l'image
for (y=hauteur; y>0 ;y--)
	for (x=0; x<largeur ;x++)
	{
		DataImage[i] = tabpxl[x][y]; 
		i++;
	}

//On rajoute les 2 octets de fin
DataImage[i] = 0;
DataImage[i+1] = 0;
return DataImage;

} 