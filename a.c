#include <stdio.h>
#include <math.h>


void create_function();
void menu();
void newton_raphson();
void regula_false();


typedef struct Eleman{
	int derece;
	int katsayi;
}Eleman;

typedef struct Polinom{
	int eleman_sayisi;
	struct Eleman eleman[16];
}Polinom;
struct Polinom turevPol;

struct Polinom pol;
float fonkHesapla(float x,struct Polinom polinom);
void yariya_bolme(void);

int main (int argc, char *argv[]) {
        
        menu();
        char x;
		scanf("%c",&x);
    
		switch(x)
		{
			case '1':
            printf("regular false\n");
			regula_false();
            break;            
			
            case '2':
            printf("Yariya bolme");
            yariya_bolme();
            break;            

			case '3':
            printf("newton raphson");
			newton_raphson();
			
            
        }
   return 0;
}


void menu(void)
{
	printf(
				"\t1.Regula False Yöntemi\n"
				"\t2.Yarıya Bölme Yöntemi\n"
				"\t3.Newton Raphson Yöntemi\n");

}





void create_function(){
    int sayi,i;
	printf("Polinomdaki eleman sayisini giriniz:");
	scanf("%d",&sayi);
	pol.eleman_sayisi=sayi;
	for(i=0;i<pol.eleman_sayisi;i++)
	{
		printf("\n%d.ci elemanin derecesini giriniz:",i+1);
		scanf("%d",&sayi);
		(pol.eleman[i]).derece=sayi;
		printf("%d.ci elemanin katsayisini giriniz:",i+1);
		scanf("%d",&sayi);
		(pol.eleman[i]).katsayi=sayi;
	}
}






float fonkHesapla(float x, struct Polinom polinom)
{
	int i,j;
	float y=0,y0=1;
	for(i=0;i<polinom.eleman_sayisi;i++)
	{
		for(j=0;j<(polinom.eleman[i]).derece;j++)
		{
			y0*=x;
		}
		y0*=polinom.eleman[i].katsayi;
		y+=y0;
		y0=1;
	}
	return y;
}

void newton_raphson(void)
{
	float x0,y0,yT0,x1=0,epsilon;
	int i,j=0;
	create_function();
	printf("Baslamak x0 degerini giriniz:");
	scanf("%f",&x0);
	printf("Epsilon degerini giriniz:");
	scanf("%f",&epsilon);

	turevPol.eleman_sayisi=pol.eleman_sayisi;
	for(i=0;i<pol.eleman_sayisi;i++)
	{
		if((pol.eleman[i]).derece!=0)
		{
			(turevPol.eleman[j]).derece=(pol.eleman[i]).derece-1;
			(turevPol.eleman[j]).katsayi=(pol.eleman[i]).derece*(pol.eleman[i]).katsayi;
			j++;
		}
		else
		{
			turevPol.eleman_sayisi-=1;
		}
	}
	printf("%-12s%-12s%-12s%-12s\n","x1","x0","y0","y0Turev");

	printf("\neleman:%d\n 1.derece %d\t1.katsayi %d\n2.derece %d\t2.katsayi %d\n",turevPol.eleman_sayisi,
	turevPol.eleman[0].derece,turevPol.eleman[0].katsayi,
	turevPol.eleman[1].derece,turevPol.eleman[1].katsayi);
	getchar();
	getchar();
	y0=fonkHesapla(x0,pol);
	yT0=fonkHesapla(x0,turevPol);
	while(y0>0?(y0>=epsilon):((-1)*y0>=epsilon)){
		x1=x0-y0/yT0;		
		printf("%-12f%-12f%-12f%-12f\n",x1,x0,y0,yT0);
		x0=x1;
		y0=fonkHesapla(x0,pol);
		yT0=fonkHesapla(x0,turevPol);
	}
}

void yariya_bolme(void)
{
	float xl,xr,xm,yl,yr,ym,epsilon;

	create_function();

	printf("xL(xleft) degerini giriniz:");
	scanf("%f",&xl);
	printf("xR(xright) degerini giriniz:");
	scanf("%f",&xr);
	printf("Epsilon degerini giriniz:");
	scanf("%f",&epsilon);	

	yl=fonkHesapla(xl,pol);
	yr=fonkHesapla(xr,pol);
	
	if((yl<0 && yr>0 ) || (yl>0 && yr<0) )
	{
		printf("Bu aralikta kok vardir.\n");
		printf("%-10s%-10s%-10s%-10s%-10s%-10s\n","xl","xr","yl","yr","xm","ym");
		do
		{
			xm=(xl+xr)/2;
			ym=fonkHesapla(xm,pol);
			yl=fonkHesapla(xl,pol);
			yr=fonkHesapla(xr,pol);
			printf("%-10f%-10f%-10f%-10f%-10f%-10f\n",xl,xr,yl,yr,xm,ym);

			if((yl<0 && ym>0 ) || (yl>0 && ym<0))
			{
				xr=xm;
			}

			if((yr<0 && ym>0 ) || (yr>0 && ym<0))
			{
				xl=xm;
			}
		}while(ym>0?(ym>=epsilon):((-1)*ym>=epsilon));
		printf("%-10f%-10f%-10f%-10f%-10f%-10f\n",xl,xr,yl,yr,xm,ym);
	}
	else
	{
		printf("Bu aralikta kok yoktur ve ya bu yontemle bulunamaz.");
	}
}

void regula_false(void)
{
	float xl,xr,xm,yl,yr,ym,epsilon;

	create_function();

	printf("xL(xleft) degerini giriniz:");
	scanf("%f",&xl);
	printf("xR(xright) degerini giriniz:");
	scanf("%f",&xr);
	printf("Epsilon degerini giriniz:");
	scanf("%f",&epsilon);	

	yl=fonkHesapla(xl,pol);
	yr=fonkHesapla(xr,pol);
	
	if((yl<0 && yr>0 ) || (yl>0 && yr<0) )
	{
		printf("Bu aralikta kok vardir.\n");
		printf("%-10s%-10s%-10s%-10s%-10s%-10s\n","xl","xr","yl","yr","xm","ym");
		do
		{
			xm=(xl*yr-xr*yl)/(yr-yl);
			ym=fonkHesapla(xm,pol);
			yl=fonkHesapla(xl,pol);
			yr=fonkHesapla(xr,pol);
			printf("%-10f%-10f%-10f%-10f%-10f%-10f\n",xl,xr,yl,yr,xm,ym);

			if((yl<0 && ym>0 ) || (yl>0 && ym<0))
			{
				xr=xm;
			}

			if((yr<0 && ym>0 ) || (yr>0 && ym<0))
			{
				xl=xm;
			}
		}while(ym>0?(ym>=epsilon):((-1)*ym>=epsilon));
		printf("%-10f%-10f%-10f%-10f%-10f%-10f\n",xl,xr,yl,yr,xm,ym);
	}
	else
	{
		printf("Bu aralikta kok yoktur ve ya bu yontemle bulunamaz.");
	}
	
}