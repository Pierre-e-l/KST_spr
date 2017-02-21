// projet1.cpp : Defines the entry point for the console application.
//
#define MAX 16
#define MAX2 1010    ////////////////////////////////MAX2 >= 10^krmax +1.....    /!\ /!\ /!\ 
#define A1 1
#define A2 0.101000100000001
#define A 1.101000100000001
#define M 5///////////////////////////////gamma>=m+2          /!\ /!\ /!\/
#define krmax 2
#define VIDE -999999
#define RMAX 2

#define factsmul 10 
#define factsdiv 0.1 

#include <iostream>
#include <cmath>
#include <algorithm>
#include "stdafx.h"
#include <fstream>
#include <time.h>

#include "imagebmp.cpp"



using namespace std;

double PHI(int varx[MAX], int vary[MAX], int q, int r);

int tabd [MAX2][MAX];

int b_krmax=(int)pow(10.0,krmax);

double tabfr[RMAX][MAX2][MAX2];

double t_fr[3][MAX2];

double tabb[krmax+1];

int tabkr[RMAX+1];

double tabPHI[M+1][RMAX+1][MAX2][MAX2];

double t_ksi[MAX2][MAX2][M+1][krmax+1];

ImageBMP image;	
ImageBMP imageres[6][3];



//pour construction de ksi^-1
	double tabletr0[MAX2*MAX2];
	double tabletr1[MAX2*MAX2];
	double tabletr2[MAX2*MAX2];

/*
struct st_fr
{
	double tab_fr[MAX2][MAX2];
};

st_fr* t_fr[MAX];
/*
struct st_PHI_d
{
	double tab_PHI_d[MAX2][MAX2];
};

struct st_PHI_d2
{
	st_PHI_d*tab_PHI_d2[MAX][MAX];
};

st_PHI_d2 t_PHI_d;*/



//double t_fr[MAX2][MAX2][MAX];//////////////////////////////////////////////////////////////////////////////////////////////////
//double t_PHI_d[MAX2][MAX2][MAX][MAX];

double conv(int tab[MAX])
{
	double som=0;
	for (int i=1;i<MAX;i++)
		som+=tab[i]*pow(0.1,i);
	return som;	
}

   /*                                                                                     //ir scalaire
int i_s(int r, int i[MAX])
{
    if (i[r]==9)
       return 1;
    else return 0;    
}

                                                                                        //[ir]
int i_c(int r, int i[MAX])
{
    if (i[r]==9 || i[r]==8)
       return 1;
    else return 0;    
}

                                                                                        //ir tilde
int i_t(int r, int i[MAX])
{
    return i[r]-8*i_s(r,i);    
}

                                                                                        //mr
int m(int r, int i[MAX])
{   
    int res,res2=0;
    for (int s=1;s<=r-1;s++)
    {
         res=i_c(s,i);
		 for (int t=s+1;t<=r-1;t++)
			 res*=i_c(t,i);
         res2+=res;
    }         

    return i_s(r,i)*(res2+1);
}

                                                                                        //phi
double psi(int i[MAX], int kr)
{
     int mr=0;
     double somme=0;
     for (int r=1;r<MAX;r++)
	// for (int r=1;r<=kr;r++)
     {
         mr=m(r,i);
         somme+=i_t(r,i)/((pow(2.0,mr)*pow(10.0,(pow(2.0,(r-mr))-1))));
     }

	//printf ("psi %1.16f\n",somme);

    return somme;
}*/

 //addition    (pour phi0, phi1....)
void somme(int x[MAX], int q, int i[MAX], int fin=2, int debut=(MAX-1))
{

	if (fin>debut)
	{
		cerr<<"erreur somme()"<<endl;
		system("pause");
	}
/*
	cout<<"avsomme=";
	for(int w=1;w<=5;w++)
		cout<<x[w];
	cout<<endl;
*/

    int ret=0;

    for (int cpt=1;cpt<MAX;cpt++)
        i[cpt]=x[cpt];          
      
    for (int cpt=debut;cpt>=fin;cpt--)
    {
          i[cpt]=ret+x[cpt]+q;
          if (i[cpt]>9)
             {
			//i[cpt]=ret+x[cpt]+q-10;
			i[cpt]=i[cpt] % 10;
			ret=1;
		    }
          else ret=0;          
    }

	int cpt=1;


	while (ret != 0 && fin>cpt)
	{
		i[fin-cpt]=x[fin-cpt]+ret;
		if (i[fin-cpt]>9)
		{
			i[fin-cpt]=i[fin-cpt]%10;
			ret=1;
		}
		else ret=0;

		cpt++;
	}
/*
	if (ret==1)
	{
		cout<<"mess"<<endl;
		system("pause");
		for (int z=1;z<MAX;z++)
			i[z]=9;     
	}



/*

	cout<<"somme=";
	for(int w=1;w<=5;w++)
		cout<<i[w];
	cout<<endl;*/

}

double psi(int i[MAX], int k)
{
//cout<<"convi"<<conv(i)<<endl;

	int tab[MAX];

	for (int h=1;h<MAX;h++)
		tab[h]=i[h];

	if (k==1)
		return conv(i);
	else
		if (k>1 && tab[k]<9)
		{
			tab[k]=0;
			return psi(tab,k-1)+i[k]/(pow(10.0,pow(2.0,k)-1));
		}
		else 
			if( k>1 && tab[k]==9)
			{
				tab[k]=tab[k]-1;
				int tab2[MAX];
				somme(i,1,tab2,k,k);
				if(conv(i)>conv(tab2))//cas où tab2=0.99...9
					return (psi(tab,k)+1)/2;
				else
				return (psi(tab,k)+psi(tab2,k-1))/2;
			}
			else cerr<<"erreur"<<endl;
}

                                                                      

                                                                                                //ksiq(x,y)....
double ksiq2(int q, int tx[MAX], int ty[MAX], int kr, bool isx)
{
	int res[MAX];
	double a;
	
	if (isx)//+aq pour un x
	{
		somme(tx,q,res);
		a=psi(res,MAX-1);
	}
	else//+q pour un dk
	{
		somme(tx,q,res,2,kr);
		a=psi(res,kr);
	}

	double b;
	if (isx)
	{
		somme(ty,q,res);
		b=psi(res,MAX-1);
	}
	else
	{
		somme(ty,q,res,2,kr);
		b=psi(res,kr);
	}

	//printf("q=%i, phiq(x+%i/90)=%1.16f, phiq(y+%i/90)=%1.16f\n",q,q,a,q,b);

	return(a+A2*b);	
}


double sigma(double ent)
{/*
	if (ent>=1) 
		return 1;
	else 
		if (ent<=0)
			return 0;
		else
			return ent;
/*
if (1/(1+exp(-ent))!=0 && 1/(1+exp(-ent))!=1 )
	cout<<"sig"<<ent<<" "<<1/(1+exp(-ent))<<endl;//*/
	return 1/(1+exp(-ent*8+3));//*7+2 sinon
}

double theta (int varx[MAX], int vary[MAX], int q, int colx, int coly, int kr)
{
	int tabx[MAX];
	int taby[MAX];
	for (int k=0;k<MAX;k++)
	{
		tabx[k]=tabd[colx][k];						
		taby[k]=tabd[coly][k];
	}

	int GB=(int)pow(10.0,pow(2.0,kr+1)-1);
//	int GB=(int)pow(5.0,pow(2.0,kr+1)-1);
	double ksi=t_ksi[colx][coly][q][kr];
	//double ksi=ksiq2(q,tabx,taby,kr,false);
	double y=ksiq2(q,varx,vary,kr,true);

	//cout<<"th "<<y<<" "<<ksi<<endl;
/*
printf("xix(%1.8f,%1.8f)=%1.8f",conv(varx),conv(vary),y);
printf("xidk(%1.8f,%1.8f)=%1.8f\n",conv(tabx),conv(taby),ksi);
*//*
	if (sigma(GB*(y-ksi)+1)-sigma(GB*(y-ksi-8*tabb[kr]))>=0.2)
	{
		cout<<"1er bout : "<<GB*(y-ksi)+1<<" 2eme bout "<<GB*(y-ksi-8*tabb[kr])<<endl;
		//system("pause");
		//cout<<"th "<<y<<" "<<ksi<<endl;
	}

*/


	return sigma(GB*(y-ksi)+1)-sigma(GB*(y-ksi-8*tabb[kr]));
}



double f(int xx[MAX], int yy[MAX])
{
	double x=conv(xx);
	double y=conv(yy);
	
	//return x*y;

	return image.GetPixel((int)(x*factsmul+0.5f),(int)(y*factsmul+0.5f));
	
}


double fr(int colx, int coly, int r,int varx[MAX], int vary[MAX])
{
	int tabx[MAX], taby[MAX];
	for (int k=0;k<MAX;k++)
	{
		tabx[k]=tabd[colx][k];						
		taby[k]=tabd[coly][k];
	}

	//cout<<"fr"<<r;
	if (r==0)
		return f(tabx,taby);
		//return f(varx,vary);
	else
	{	
		double som=0;
			
		for (int q=0;q<=M;q++)
			for (int j=1;j<=r;j++)
			{ 
				//cout<<"phidansfr"<<PHI(varx,vary,q,j,kr)<<endl;			
		//		som+=PHI(tabx,taby,q,j,tabkr[j]);//////////////precedent
				if(tabPHI[q][j][colx][coly]==VIDE)
					//tabPHI[q][j][colx][coly]=PHI(tabx,taby,q,j);
					tabPHI[q][j][colx][coly]=PHI(varx,vary,q,j);
				som+=tabPHI[q][j][colx][coly];//*/
				//som+=t_PHI_d.tab_PHI_d2[q][j]->tab_PHI_d[colx][coly];
				//som+=t_PHI_d[j]->tab_PHI_d3[q]->tab_PHI_d2[colx]->tab_PHI_d[coly];
			}
	
	//cout<<"somme phi dans fr "<<som<<" pour "<<colx<<";"<<coly<<endl;


	//	return f(tabx,taby)-som;			

		return f(varx,vary)-som;

	}

}
/*
double fr(int varx[MAX], int vary[MAX], int r, int kr)
{

	//cout<<"fr"<<r;
	if (r==0)
		return f(varx,vary);
	else
	{	
		double som=0;
			
		for (int q=0;q<=M;q++)
			for (int j=1;j<=r;j++)
			{ 
				//cout<<"phidansfr"<<PHI(varx,vary,q,j,kr)<<endl;
				som+=PHI(varx,vary,q,j,kr);
				//som+=t_PHI_d.tab_PHI_d2[q][j]->tab_PHI_d[colx][coly];
				//som+=t_PHI_d[j]->tab_PHI_d3[q]->tab_PHI_d2[colx]->tab_PHI_d[coly];
			}
		return f(varx,vary)-som;
	}

}
*/
double PHI(int varx[MAX], int vary[MAX], int q, int r)
{
	//cout<<"PHI "<<conv(varx)<<" " <<conv(vary)<<" "<<q<<" "<<r<<" "<<endl;

	double som=0,tmp=0;
	bool ok=false;
	int kr=tabkr[r];
	int pas=(int)pow(10.0,(krmax-kr));
	for (int colx=1; colx<=b_krmax; colx+=pas)
		for (int coly=1; coly<=b_krmax; coly+=pas)
		{		

			//cout<<"th "<<theta(ksiq2(q, varx, vary,kr,true),q,colx,coly,kr)<<endl;

			//som+=t_fr[colx][coly][r-1]*theta(ksiq2(q, varx, vary),q,colx,coly,kr);
			//cout<<"ds PHI, fr="<<t_fr[colx][coly][r-1]<<" th="<<theta(ksiq2(q, varx, vary),q,colx,coly,kr)<<endl;

			tmp=theta(varx,vary,q,colx,coly,kr);

			if(tmp!=0)			
			{
				//som+=t_fr[r-1]->tab_fr[colx][coly]*tmp;
				//cout<<"som dans phi"<<som<<endl;

				//cout<<"th="<<tmp<<" pour "<<colx<<" "<<coly<<endl;

				//double resf=fr(colx,coly,r-1,kr,varx,vary);
				//som+=resf*tmp;

				//cout<<"f"<<r-1<<"="<<resf<<" entre ("<<conv(varx)<<";"<<conv(vary)<<") et ("<<conv(tabd[colx])<<";"<<conv(tabd[coly])<<") th("<<colx<<";"<<coly<<")="<<tmp<<endl;
				
				//som+=fr(colx,coly,r-1)*tmp;    ////////////////// precedent


				//cout<<"dk dans phi "<<conv(tabd[colx])<<" "<<conv(tabd[coly])<<endl;


				if(tabfr[r-1][colx][coly]==VIDE)
					tabfr[r-1][colx][coly]=fr(colx,coly,r-1,varx,vary);
				som+=tabfr[r-1][colx][coly]*tmp;//*/
				//som+=t_fr[r-1]->tab2_fr[colx]->tab_fr[coly]*tmp;

				ok=true;

			}

		}
	//cout<<"fphi";
	//	if ( !ok ) {cout <<"theta == 0, PHI="<<som/(M+1)<<" q="<<q<<", r="<<r<<endl;}////////////////////////////////////////////theta = 0
	//cout<<"somPHI"<<som/(M+1)<<endl;
	

	return som/(M+1);
	
}


void generated()//on genere les dk une fois pour toute pour krmax...
{
	int nb;

	int puis;

	/*for (int col=1; col<=krmax; col++)
	{ 
		nb=1;
		for (int lig=1; lig<=b_krmax; lig++)
		{						
			tabd[lig][col]=nb%10;			
			if (lig>nb*pow(10.0,krmax-col))
				nb++;
		}
	}*/

	//generated reloaded (ordre croissant)
	for (int col=1; col<=krmax; col++)
	{ 
		nb=0;
		puis=(int)pow(10.0,krmax-col);
		for (int lig=1; lig<=b_krmax; lig++)
		{						
			tabd[lig][col]=nb%10;			
			if (lig+1>(nb+1)*puis)
				nb++;
		}
	}
/*
	//affich de generated
		for (int i=1; i<=b_krmax; i++)
		{
			for (int j=1; j<=5; j++)
				cout<<tabd[i][j];
			cout<<endl;
		}
*/	
}

int detkr(int rr, ofstream &outfile)
{
	int kr=2;

	int r=rr-1;

	double E=(double)(1-(double)2/(M-1))/20;/////////////////////////////////////////////////////////////fixe epsilon

	cout<<"entree dans detkr"<<endl;
	outfile<<"entree dans detkr"<<endl;

	double nor=0;
	double tmp=0;

	//on recup la norme...

	for (int colx=1; colx<=b_krmax; colx++)
	{
		tmp=fabs(t_fr[0][colx]);
		if (tmp>nor && tmp!=abs(VIDE))
			nor=tmp;
	}

	cout<<"norme="<<nor<<endl;
	outfile<<"norme="<<nor<<endl;

	bool oups=true;

	for (kr=2;kr<=krmax;kr++)
	{
		oups=true;
		for (int colx=1; colx<=7; colx++)
			for (int coly=1; coly<=7; coly++)
				if(t_fr[0][colx]!=VIDE && t_fr[0][coly]!=VIDE && colx!=coly)
					if(fabs(t_fr[1][colx]-t_fr[1][coly])<=pow(0.1,kr) && fabs(t_fr[2][colx]-t_fr[2][coly])<=pow(0.1,kr))
					{
						oups=false;
						if(fabs(t_fr[0][colx]-t_fr[0][coly])>E*nor)
						{
							cout<<"kr="<<max(kr-1,2)<<endl;
							outfile<<"kr="<<max(kr-1,2)<<endl  ;
							return max(kr-1,2);
						}
					}
	}

	if (oups)
	{
		cout<<"erreur detkr"<<endl; 
		system("pause");
	}

	if (kr>krmax)
		kr=krmax;

	cout<<"krfin="<<kr<<endl;
	outfile<<"krfin="<<kr<<endl;

	return kr;
}

                                                                                                //main
int _tmain(int argc, _TCHAR* argv[])
{	
	image.chargerFichier("lena100.bmp");


/*
	for (int col=0;col<100;col++)
	{
		for (int lig=0;lig<100;lig++)
			cout<<image.GetPixel(lig,col)<<" ";
		cout<<endl;
	}	

*/


for (int i=0;i<6;i++)
	imageres[i][0]=imageres[i][1]=imageres[i][2]=image;


/*
imageres[0][0].chargerFichier("res01.bmp");
imageres[1][0].chargerFichier("res11.bmp");
imageres[2][0].chargerFichier("res21.bmp");
imageres[3][0].chargerFichier("res31.bmp");
imageres[4][0].chargerFichier("res41.bmp");
imageres[5][0].chargerFichier("res51.bmp");

imageres[0][1]=imageres[0][0];

for (int i=1;i<6;i++)
	for (int lig=0;lig<1000;lig++)
		for (int col=0;col<1000;col++)
			imageres[0][1].SetPixel(lig,col,min(imageres[0][1].GetPixel(lig,col)+imageres[i][0].GetPixel(lig,col),255));
			//imageres[0][1].SetPixel(lig,col,imageres[0][1].GetPixel(lig,col)+imageres[i][0].GetPixel(lig,col));

/*
for (int lig=0;lig<1000;lig++)
		for (int col=0;col<1000;col++)
			if(imageres[0][0].GetPixel(lig,col)>10 && imageres[0][0].GetPixel(lig,col)<252)
				imageres[0][1].SetPixel(lig,col,255);
			else imageres[0][1].SetPixel(lig,col,0);
*/

/*
imageres[0][1].sauverFichier("somme.bmp");



for (int lig=0;lig<1000;lig++)
	for (int col=0;col<1000;col++)
		imageres[0][2].SetPixel(lig,col,image.GetPixel(lig,col)-imageres[0][1].GetPixel(lig,col));

imageres[0][2].sauverFichier("diff.bmp");

return EXIT_SUCCESS;

//*/


	//init de tabb
	for (int k=0;k<=krmax;k++)
	{	
		double som=0;
		for (int r=k+1;r<10000;r++)
			som+=pow(0.1,pow(2.0,r)-1);

		tabb[k]=som*A;

		//printf("b%i=%1.16f\n",k,tabb[k]);
	}


	time_t rawtime;
	time (&rawtime);

	char buf[50], buf2[50];  
  
    ctime_s( buf, 50, &rawtime );	

	buf2[0]='T';
	buf2[1]='S';
	buf2[2]='K';
	buf2[3]='-';

	for (int m=0;m<50;m++)
	{
		if(buf[m]!='\n')
			buf2[m+4]=buf[m];
		else {buf2[m+4]='\0';m=500;}
		if(buf[m]==':')
			buf2[m+4]='-';
	}

	strcat_s(buf2,".txt");

	ofstream outfile (buf2, ios::app);


	cout<<"-------------------Debut exec : "<< buf<<endl;
	outfile<<endl<<"-------------------Debut exec : "<< buf<<endl;

    //passage d'un (float en chaine de caracteres) en (un tableau d'entiers)

    char ent[MAX+3];
    char ent2[MAX+3];

	int varx[MAX];
	int vary[MAX]; 

	for (int v=0;v<MAX;v++)
		varx[v]=vary[v]=0;


	//int kr=0;

	double tmp2;

	generated();


	for (int tmpk=2;tmpk<=krmax;tmpk++)
		for (int colx=1;colx<=b_krmax;colx++)
			for (int coly=1;coly<=b_krmax;coly++)
				for (int q=0;q<=M;q++)
					t_ksi[colx][coly][q][tmpk]=ksiq2(q,tabd[colx],tabd[coly],tmpk,false);
/*

	for (int colx=1;colx<=b_krmax;colx++)
		for (int coly=1;coly<=b_krmax;coly++)
		{
			tabletr0[(colx-1)*b_krmax+coly]=t_ksi[colx][coly][0][2];
			tabletr1[(colx-1)*b_krmax+coly]=colx;
			tabletr2[(colx-1)*b_krmax+coly]=coly;
		}


	bool permut=true;
	double ex1;
	int ex2;
	int ex3;

	while (permut)
	{
		permut=false;
		for (int colx=1;colx<b_krmax*b_krmax;colx++)
			if(tabletr0[colx]>tabletr0[colx+1])
			{
				ex1=tabletr0[colx];
				ex2=tabletr1[colx];
				ex3=tabletr2[colx];
				tabletr0[colx]=tabletr0[colx+1];
				tabletr1[colx]=tabletr1[colx+1];
				tabletr2[colx]=tabletr2[colx+1];
				tabletr0[colx+1]=ex1;
				tabletr1[colx+1]=ex2;
				tabletr2[colx+1]=ex3;
				permut=true;
			}
	}
	
for (int colx=1;colx<=b_krmax*b_krmax;colx++)
	cout<<"("<<tabletr1[colx]<<";"<<tabletr2[colx]<<") ";

system("pause");
exit(0);

*/
/*

	for (int colx=1;colx<=b_krmax;colx++)
		for (int coly=1;coly<=b_krmax;coly++)
			imageres[1][0].SetPixel(colx-1,coly-1,t_ksi[colx][coly][5][2]*255);


imageres[1][0].sauverFichier("ksi5.bmp");


exit(0);
*/

	for (int hg=1;hg<=(int)(0.8*factsmul);hg++){////////////////////////////////////////////////////////////////////////////////////boucle infinie main
for (int hg2=1;hg2<=(int)(0.8*factsmul);hg2++){

    //saisie provisoire 0<entree<1
 /*   cout<<"? (0<x1<1) ";
    cin>>ent;    
    
    cout<<"? (0<x2<1) ";
    cin>>ent2; 
	*/
//605
//3771
	//strcpy_s(ent,"0.156");/////////////////max=0.94 (a cause des translations)//////////////////////resolu?? on dirait :) 
	//strcpy_s(ent2,"0.551");

//	strcpy_s(ent,"0.605");/////////////////max=0.94 (a cause des translations)//////////////////////resolu??   
//	strcpy_s(ent2,"0.3771");


sprintf_s(ent,"%1.16f",0.1+hg*factsdiv);

sprintf_s(ent2,"%1.16f",0.1+hg2*factsdiv);	

    char*tmp;

    for (int cpt=1;cpt<MAX;cpt++)
    {                       
        tmp=new char(ent[cpt+1]);            
        varx[cpt]=atoi(tmp);  
        tmp=NULL;delete tmp;       
        tmp=new char(ent2[cpt+1]);            
        vary[cpt]=atoi(tmp);        
        tmp=NULL;delete tmp;            
    } 

	cout<<"f="<<f(varx,vary)<<endl;
	outfile<<"f="<<f(varx,vary)<<endl;

	cout<<"x="<<ent<<endl;
	outfile<<"x="<<ent<<endl;
	cout<<"y="<<ent2<<endl;
	outfile<<"y="<<ent2<<endl;




	double somme=0;
	
	
	
	

/*
int bl[MAX];

double result;

for (int h=0;h<MAX;h++)
	bl[h]=0;

bl[1]=5;
bl[2]=8;
for (int h=3;h<MAX;h++)
	bl[h]=1;
result=psi(bl,MAX-1);

printf("psi(0.58111111111111111111)%1.16f\n",result);

	int res[MAX];	

	::somme(bl,0,res);

	double a=psi(res,MAX-1);

printf("psi(0.58111111111111111111)%1.16f\n",a);


printf("psi(0.58111111111111111111)%1.16f\n",result+0.101*result);
double result2=ksiq2(0,bl,bl,2,true);
printf("xi(0.58111111111111111111^2)%1.16f\n",result2);

for (int h=0;h<MAX;h++)
	bl[h]=0;

bl[1]=5;
bl[2]=8;

result=psi(bl,MAX-1);

printf("psi(0.58)%1.16f\n",result);
printf("psi(0.58)%1.16f\n",result+pow(0.1,pow(2.0,3)-1)*8);
printf("xi(0.58^2)%1.16f\n",ksiq2(0,bl,bl,2,true));
printf("xi(0.58^2)%1.16f\n",ksiq2(0,bl,bl,2,true)+pow(0.1,pow(2.0,3)-1)*8+0.101*pow(0.1,pow(2.0,3)-1)*8);
printf("xi(0.58^2+8*b2)%1.16f\n",ksiq2(0,bl,bl,2,true)+8*tabb[2]);
printf("diff%1.16f\n",result2-ksiq2(0,bl,bl,2,true));

system("pause");
*/
/*


int bl[MAX];

for (int h=0;h<MAX;h++)
	bl[h]=9;

//void somme(int x[MAX], int q, int i[MAX], int fin=2, int debut=(MAX-1))

printf("psi,%1.16f\n",psi(bl,MAX-1));
*/
/*

int bl[MAX];

for (int h=0;h<MAX;h++)
	bl[h]=0;

bl[1]=9;
bl[2]=5;
bl[3]=8;
double result=theta(bl,bl,0,96,96,2);

printf("th %1.16f\n",result);

*/

//initialisation
tabkr[0]=krmax;
for (int lig=0;lig<=b_krmax;lig++)
	for (int col=0;col<=b_krmax;col++)
		for (int z=1;z<=RMAX;z++)
		{
			tabfr[z-1][lig][col]=VIDE;
			for (int q=0;q<=M;q++)
				tabPHI[q][z][lig][col]=VIDE;
		}


/*

int bl[MAX],bl2[MAX];
for (int h=0;h<MAX;h++)
	bl[h]=bl2[h]=0;
bl[1]=2;
bl[2]=8;
bl[3]=2;
bl2[1]=8;
bl2[2]=1;

cout<<"f2="<<fr(29,82,2,2,bl, bl2)<<endl;
cout<<"f="<<f(bl,bl2)<<endl;

double sssom=0;
for (int q=0;q<=M;q++)
	for (int j=1;j<=2;j++)
		sssom+=PHI(bl,bl2,q,j,2);
cout<<"somme"<<sssom<<endl;
system("pause");
*/



	for (int j=1; j<=RMAX;j++)//r
	{
		cout<<endl<<"*************r="<<j<<"*************"<<endl;
		outfile<<endl<<"*************r="<<j<<"*************"<<endl;







		//determiner kr....	


	/*	//echantillonnage
		cout<<"echantillonnage"<<endl;
		outfile<<"echantillonnage"<<endl;
		
		
		for (int i=1;i<b_krmax;i++)
			t_fr[0][i]=VIDE;



		int bl[MAX],bl2[MAX];
		for (int h=0;h<MAX;h++)
			bl[h]=bl2[h]=0;
		bl[1]=0;
		bl[2]=5;
		bl[3]=1;
		bl2[1]=0;
		bl2[2]=5;
		bl2[3]=1;
	

		t_fr[1][1]=0.051;
		t_fr[2][1]=0.051;
		t_fr[0][1]=fr(50,50,j-1,bl,bl2);
		cout<<"fr("<<t_fr[1][1]<<";"<<t_fr[1][1]<<")="<<t_fr[0][1]<<endl;
	/*	outfile<<"fr("<<t_fr[1][1]<<";"<<t_fr[1][1]<<")="<<t_fr[0][1]<<endl;
		t_fr[1][2]=conv(tabd[6]);
		t_fr[2][2]=conv(tabd[6]);
		t_fr[0][2]=fr(6,6,j-1,varx,vary);
		cout<<"fr("<<t_fr[1][2]<<";"<<t_fr[2][2]<<")="<<t_fr[0][2]<<endl;
		outfile<<"fr("<<t_fr[1][2]<<";"<<t_fr[1][2]<<")="<<t_fr[0][2]<<endl;
		t_fr[1][3]=conv(tabd[50*mult]);
		t_fr[2][3]=conv(tabd[50*mult]);
		t_fr[0][3]=fr(50*mult,50*mult,j-1,varx,vary);
		cout<<"fr("<<t_fr[1][3]<<";"<<t_fr[1][3]<<")="<<t_fr[0][3]<<endl;
		outfile<<"fr("<<t_fr[1][3]<<";"<<t_fr[1][3]<<")="<<t_fr[0][3]<<endl;
		t_fr[1][4]=conv(tabd[50*mult+1]);
		t_fr[2][4]=conv(tabd[50*mult+1]);
		t_fr[0][4]=fr(50*mult+1,50*mult+1,j-1,varx,vary);
		cout<<"fr("<<t_fr[1][4]<<";"<<t_fr[1][4]<<")="<<t_fr[0][4]<<endl;
		outfile<<"fr("<<t_fr[1][4]<<";"<<t_fr[1][4]<<")="<<t_fr[0][4]<<endl;
		t_fr[1][5]=conv(tabd[93*mult]);
		t_fr[2][5]=conv(tabd[93*mult]);
		t_fr[0][5]=fr(93*mult,93*mult,j-1,varx,vary);					
		cout<<"fr("<<t_fr[1][5]<<";"<<t_fr[1][5]<<")="<<t_fr[0][5]<<endl;
		outfile<<"fr("<<t_fr[1][5]<<";"<<t_fr[1][5]<<")="<<t_fr[0][5]<<endl;
		t_fr[1][6]=conv(tabd[93*mult+1]);
		t_fr[2][6]=conv(tabd[93*mult+1]);
		t_fr[0][6]=fr(93*mult+1,93*mult+1,j-1,varx,vary);
		cout<<"fr("<<t_fr[1][6]<<";"<<t_fr[1][6]<<")="<<t_fr[0][6]<<endl;
		outfile<<"fr("<<t_fr[1][6]<<";"<<t_fr[1][6]<<")="<<t_fr[0][6]<<endl;




		tabkr[j]=detkr(j, outfile);

	/*	if (tabkr[j]!=tabkr[j-1])//kr a change, il faut recalculer tous les fr
			for (int lig=0;lig<=b_krmax;lig++)
				for (int col=0;col<=b_krmax;col++)
					for (int z=1;z<=j;z++)
						tabfr[z-1][lig][col]=VIDE;	
		*/



		tabkr[j]=krmax;////////////////////////////////////tmp si pas echantillonnage




		/*if(j==1)
			for (int q=0;q<=M;q++)
				cout<<"y"<<q<<"="<<ksiq2(q,varx,vary,tabkr[j],true)<<endl;
				*/

			for (int q=0;q<=M;q++)
			{	
				tmp2=PHI(varx,vary,q,j);
				somme+=tmp2;

				cout<<"PHI="<<tmp2;
				outfile<<"PHI="<<tmp2;	
				if(j==1)
					imageres[q][0].SetPixel((int)(conv(varx)*factsmul+0.5f),(int)(conv(vary)*factsmul+0.5f),(int)(tmp2+0.5f));
				else
					{
						imageres[q][1].SetPixel((int)(conv(varx)*factsmul+0.5f),(int)(conv(vary)*factsmul+0.5f),max((int)(imageres[q][0].GetPixel((int)(conv(varx)*factsmul+0.5f),(int)(conv(vary)*factsmul+0.5f))+tmp2+0.5f),0));
						imageres[q][2].SetPixel((int)(conv(varx)*factsmul+0.5f),(int)(conv(vary)*factsmul+0.5f),(int)(tmp2+0.5f));
					}

				cout<<"(q="<<q<<";r="<<j<<")"<<"so="<<somme<<endl;
				outfile<<"(q="<<q<<";r="<<j<<")"<<"so="<<somme<<endl;
			}

	}	

	if((hg%5)==0 && (hg2%80)==0)
	{
		imageres[0][0].sauverFichier("res00.bmp");
		imageres[1][0].sauverFichier("res10.bmp");
		imageres[2][0].sauverFichier("res20.bmp");
		imageres[3][0].sauverFichier("res30.bmp");
		imageres[4][0].sauverFichier("res40.bmp");
		imageres[5][0].sauverFichier("res50.bmp");
		imageres[0][1].sauverFichier("res01.bmp");
		imageres[1][1].sauverFichier("res11.bmp");
		imageres[2][1].sauverFichier("res21.bmp");
		imageres[3][1].sauverFichier("res31.bmp");
		imageres[4][1].sauverFichier("res41.bmp");
		imageres[5][1].sauverFichier("res51.bmp");
		imageres[0][2].sauverFichier("res02.bmp");
		imageres[1][2].sauverFichier("res12.bmp");
		imageres[2][2].sauverFichier("res22.bmp");
		imageres[3][2].sauverFichier("res32.bmp");
		imageres[4][2].sauverFichier("res42.bmp");
		imageres[5][2].sauverFichier("res52.bmp");
		
	}

  
}///////////////////////////////////////////////////////////////////////////////////////////////////////////////////fin for boucle inf
}

	imageres[0][0].sauverFichier("res00.bmp");
	imageres[1][0].sauverFichier("res10.bmp");
	imageres[2][0].sauverFichier("res20.bmp");
	imageres[3][0].sauverFichier("res30.bmp");
	imageres[4][0].sauverFichier("res40.bmp");
	imageres[5][0].sauverFichier("res50.bmp");
	imageres[0][1].sauverFichier("res01.bmp");
	imageres[1][1].sauverFichier("res11.bmp");
	imageres[2][1].sauverFichier("res21.bmp");
	imageres[3][1].sauverFichier("res31.bmp");
	imageres[4][1].sauverFichier("res41.bmp");
	imageres[5][1].sauverFichier("res51.bmp");
	imageres[0][2].sauverFichier("res02.bmp");
	imageres[1][2].sauverFichier("res12.bmp");
	imageres[2][2].sauverFichier("res22.bmp");
	imageres[3][2].sauverFichier("res32.bmp");
	imageres[4][2].sauverFichier("res42.bmp");
	imageres[5][2].sauverFichier("res52.bmp");


	time ( &rawtime );

	ctime_s( buf, 50, &rawtime );

	cout<<"Fin exec : "<< buf<<endl;
	outfile<<"Fin exec : "<< buf<<endl;

	outfile.close();


                                                    
    system("PAUSE");
    return EXIT_SUCCESS;
}