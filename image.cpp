#include "image.h"
#include<iostream>
#include<fstream>
#include<algorithm>

 using namespace std;

bool Cimage::ChargerImage(char* Fichier,int Larg,int Haut)
{
	 ifstream f;
	 unsigned char** MatAux;

	 MatAux=new unsigned char*[Haut];

	 for(int i=0;i<Haut;++i)
		 MatAux[i]=new unsigned char[Larg];

	 f.open(Fichier,ios::in | ios::binary );
	 if( !f )
		 return false;

	 if( Larg==0 || Haut==0 )
	 {
		if( NbColonne==0 )
		return false;
	 }
	 else
	 {
		 NbLigne = Larg;
		 NbColonne = Haut;
		 Img.reserve(NbLigne*NbColonne);
	 }

	 for(int iii=0;iii<NbColonne;++iii)
		 f.read((char*)MatAux[iii], NbLigne);

	 for(int ii=0;ii<NbLigne;++ii)
	 {
		 for(int j=0;j<NbColonne;++j)
		 Img[ii*NbLigne+j]=MatAux[ii][j];
		 //copy(Mt[ii],Mt[ii]+m_nWidth,m_ppImage.begin()+ii*m_nWidth);
	 }
	 //copy(Mt+0,Mt+m_nWidth*m_nHeight,m_ppImage.begin());
	 f.close();
	 return true;
}


bool Cimage::SauverImage( char* Fichier )
{
	if( NbColonne==0 || NbLigne==0 )
		return false;

	 ofstream f;
	 unsigned char** MatAx;
	 MatAx=new unsigned char*[NbColonne];

	 for(int i=0;i<NbColonne;++i)
		 MatAx[i]=new unsigned char[NbLigne];

	 // Ouverture en écriture
	 f.open(Fichier, ios::out | ios::binary );

	 if( !f )
		 return false;

	 for(int ii=0;ii<NbColonne;++ii)
	 {
		 for(int j=0;j<NbLigne;++j)
			MatAx[j][ii]=Img[j*NbColonne+ii];
	 }

	 // lecture de toute l'image, d'un bloc
	 for(int iii=0;iii<NbLigne;++iii)
		 f.write((char*)MatAx[iii], NbColonne);
	 //copy(Mt,Mt+(m_nWidth*m_nHeight),m_ppImage.begin());
	 f.close();

	 return true;
}
/*
void Cimage::Binarisation(MonType S)
{
	 for(int i=0;i<NbColonne;++i)
	 {
		 for(int j=0;j<NbLigne;++j)
		 {
			 MonType x=GetPixel(i,j);
			 if(S<x)
				 SetPixel(i,j,255);
			 else
				SetPixel(i,j,0);
		}

	}
}*/
/*
void Cimage::recadrage()
{
 unsigned char minn,maxx,a=1;

 minn=(unsigned char)min_element(Img.begin(),Img.end());
 maxx=(unsigned char)max_element(Img.begin(),Img.end());
 if(maxx!=minn) a=(maxx)-(minn);
 for(int k=0;k<NbColonne*NbLigne;++k)
 Img[k]=(255*(Img[k]-(minn))/a);
}*/

Cimage& Cimage::operator=(const Cimage& m)
{
	 if(&m!=this)
	 {
		 NbLigne=m.NbLigne;
		 NbColonne=m.NbColonne;
		 Img.reserve(NbLigne*NbColonne);
		 copy(m.Img.begin(),m.Img.end(),Img.begin());
	 }
	 return *this;
}

Cimage::Cimage(const Cimage& MatAux)
{
	 Img.clear();
	 NbLigne=MatAux.NbLigne;
	 NbColonne=MatAux.NbColonne;
	 Img.reserve(NbColonne*NbLigne);
	 //copy(m.Img.begin(),m.Img.end(),Img.begin());
	 for(int ii=0;ii<NbLigne*NbColonne;++ii)
	 {
		 Img[ii]=MatAux.Img[ii];
		 //copy(Mt[ii],Mt[ii]+m_nWidth,m_ppImage.begin()+ii*m_nWidth);
	 }

}
/*
void Cimage::Moy()
{
	 for(int i=0;i<NbLigne;++i)
	 {
		 for(int j=0;j<NbColonne;++j)
		 {
			Img[i*NbColonne+j]=-(Img[((i-1)*NbColonne+j-1)]+Img[((i-1)*NbColonne+j)]+Img[((i-1)*NbColonne+j+1)]+Img[(i*NbColonne+j-1)]-8*Img[(i*NbColonne+j)]+Img[(i*NbColonne+j+1)]+Img[((i+1)*NbColonne+j+1)]+Img[((i+1)*NbColonne+j)]+Img[((i+1)*NbColonne+j-1)]);
		 }
	 }
} */