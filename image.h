typedef int MonType;

#include<vector>

using namespace std;

class Cimage
{
	int NbLigne;
	int NbColonne;
	vector<MonType> Img;

 public:
	Cimage():NbLigne(0),NbColonne(0){};
	Cimage(int l,int c):NbLigne(l),NbColonne(c),Img(NbColonne*NbLigne){}
	Cimage(const Cimage&);

	int Largueur( ){return NbColonne;}; // largeur de l'image
	int Hauteur( ){return NbLigne;}; // hauteur de l'image

	 // Accès au pixel en écriture/lecture
	 void SetPixel( int,int,MonType);
	 MonType GetPixel(int,int);

	 // Récupération d'une ligne
	 MonType* GetLine(int);

	 // Récupération de l'image entière
	 Cimage& operator=(const Cimage&);
	 MonType* GetImage( );
	 void Reserver(int x,int y);
	// void Binarisation(MonType S);
	 bool ChargerImage(char*,int,int);
	 bool SauverImage(char*);
	// void recadrage();
	 //void Moy();
};

 // -------------------------------------------
 //*********** Méthodes "inline"***************
 // -------------------------------------------

inline void Cimage::Reserver(int x,int y)
{
	NbLigne=x;
	NbColonne=y;
	Img.reserve(NbColonne*NbLigne);
}

inline void Cimage::SetPixel( int i, int j,MonType Val)
{
	 // Tests de cohérence
	 if( i<0 ||i>=NbLigne || j<0 || j>=NbColonne )
	 return ;
	 Img[j*NbLigne+i]=Val;
}

// Accès au pixel en lecture
inline MonType Cimage::GetPixel( int i, int j )
{
	 // Tests de cohérence
	 if( i<0 ||i>=NbLigne || j<0 || j>=NbColonne )
	 return 0;
	 return Img[j*NbLigne+i];
} 