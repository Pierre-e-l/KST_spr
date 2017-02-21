#ifndef DEF_IMAGEBMP
#define DEF_IMAGEBMP

#define MAAX 1024

class ImageBMP
{
	protected:
		std::string Type;
		int Bites;
		unsigned char HeaderFile [0x0E];
		unsigned char HeaderBMP [0x29];
		unsigned char *PaletteBMP;
		unsigned long taillepalette;
		int largeur;
		int hauteur;
		int tabpxl[MAAX][MAAX];
		unsigned char * ImageToData();

public :
		int GetPixel(int lig, int col){return tabpxl[lig][col];};
		void SetPixel(int lig, int col, int val){tabpxl[lig][col]=val;};
		ImageBMP();		
		int chargerFichier(char *);
		void ImageBMP::sauverFichier (char *fichier);
		void info();
		unsigned long donnetaillefichier();

} ;


#endif 