/********************************************************************/
/**                                                                **/
/**   Henrique Rodrigues          Número USP:7628927               **/
/**   Exercício-Programa 3 - Angry Bixos                           **/
/**   Professor: Zé Augusto                                        **/
/**   Turma:1                                                      **/
/**                                                                **/
/********************************************************************/
#include <stdio.h>
#define SIM 1
#define NAO 0
#define EPS 0.0001
#define MIN_VX 0.0001
#define PI 3.1415954
#define ARQ_ENTRADA "entrada.txt"
#define ESTI "E"
#define ALVO "A"
#define CRUZ "+"
#define HORI "-"
#define VERT "|"
#define BIXO "o"
#define NADA " "

float Sen (float x, float eps);
float Cos (float x, float eps);
float Converte (float x);
void  AtualizaPosicaoEVelocidade(float *y, float *vely, float dt, float g);
int   Arredonda (float x);
void  ImprimaCondicaoInicial(int nLin, int nCol, float nUni, float yE, float yA, float hA);
void LeiaParametros (float *yE, float *vMax,
                     float *yA, float *hA,
                     float *dist,
		     int *nBix,
                     int *nLin, int *nCol,
                     float *nUni,
		     float *g);


void LeiaParametros (float *yE, float *vMax,
                     float *yA, float *hA,
		     float *dist,
                     int *nBix,
                     int *nLin, int *nCol,
                     float *nUni,
		     float *g)
{
  FILE *arq;
  arq = fopen(ARQ_ENTRADA, "r");
  /* Estilingue */
  fscanf(arq, "%f %f", yE, vMax);
  /* Alvo */
  fscanf(arq, "%f %f", yA, hA);
  /* dist = xA - xE */
  fscanf(arq, "%f", dist);
  /* numero de bixos */
  fscanf(arq, "%d", nBix);
  /* numero de linhas do grafico */
  fscanf(arq, "%d", nLin);
  /* numero de colunas do grafico */
  fscanf(arq, "%d", nCol);
  /* unidade utilizada pelo grafico, ou numero (real) de unidades por linha */
  fscanf(arq, "%f", nUni);
  /* aceleracao da gravidade */
  fscanf(arq, "%f", g);

  fclose(arq);
  return;
}

float Sen (float x, float eps)
{
    float aux = 0.0;
    float termo;
    int k;
    k=2;
    aux=x;
    termo=x;
    while(termo>eps||-termo<eps){
        termo=-termo*x*x/(k*(k+1));
        aux=aux+termo;
        k=k+2;
    }
    return aux;
}

float Cos (float x, float eps)
{
  float aux = 0.0;
  float termo;
    int k;
    k=1;
    aux=1;
    termo=1;
    while(termo>eps||-termo<eps){
        termo=-termo*x*x/(k*(k+1));
        aux=aux+termo;
        k=k+2;
    }
    return aux;
}


float Converte (float x)
{
  float aux = 0.0;
  aux=(3.1415954/2)*x;
  return aux;
}

void AtualizaPosicaoEVelocidade(float *y, float *vely, float dt, float g)
{
    *y=*y+*vely*dt+0.5*g*dt*dt;
    *vely=*vely+g*dt;
  return;
}


int Arredonda (float f) {
  int aux = 0;
  float fn;
  int inteiro, inteiro2;
  fn=f-0.5;
  inteiro=fn;
  inteiro2=f;
  if(inteiro==inteiro2)
  aux=inteiro2+1;
  else
  aux=inteiro2;

  return aux;
}

void ImprimaCondicaoInicial(int nLin, int nCol, float nUni, float yE, float yA, float hA)
{
  float vMax;
  float dist;
  int nBix;
  float g;
  int nCol2, altura_estilingue, nLin2, hA2;

   LeiaParametros( &yE, &vMax,
		  &yA, &hA,
		  &dist,
		  &nBix,
		  &nLin, &nCol,
		  &nUni,
		  &g );

  printf ("\nCondicao Inicial:\n\n");
    altura_estilingue=Arredonda(yE/nUni);
    hA=Arredonda(hA/nUni);
    yA=Arredonda(yA/nUni);
    nLin2=nLin;
    hA2=hA-1;/*hA2 sera somado ao yA*/

    while(nLin2>=0){/*O programa vai construindo linha por linha*/
        nCol2=nCol;
        while(nCol2>=0){/*O programa constroi todas as colunas de uma determinada linha*/
            if(nCol2%5==0&&nLin2%5==0&&altura_estilingue!=nLin2){
            if(nCol2!=0||(nCol2==0&&yA+hA2!=nLin2))
            printf("+");
            if(nCol2==0&&yA+hA2==nLin2){
                if(hA2>0)
                hA2--;
            printf("A");
            }
            }
            if(nCol2%5==0&&nLin2%5!=0&&altura_estilingue!=nLin2){
            if(nCol2!=0||(nCol2==0&&yA+hA2!=nLin2))
            printf("|");
            if(nCol2==0&&yA+hA2==nLin2){
                if(hA2>0)
                hA2--;
            printf("A");
            }
            }
            if(nCol2%5!=0&&nLin2%5==0&&altura_estilingue!=nLin2)
            printf("-");
            if(nCol2%5!=0&&nLin2%5!=0)
            printf(" ");
            if(nCol2==nCol&&altura_estilingue==nLin2){
            printf("E");
            altura_estilingue++;
            }
            if(nCol2==0)
            printf("\n");
            nCol2--;
            }
        nLin2--;
    }
    altura_estilingue--;
  return;
}

int main ()
{
  int modoDepuracao;

  float yE, vMax;
  float yA, hA;
  float dist;
  int nBix, nLin, nCol;
  float nUni, g;
  float des, ori;
  float yb, v, velX, velY, dt, yb2, velY2, primeiro, segundo;
  int contb, nCol2, nLin2, altura_inteira, altura_estilingue, nInters, altura_estilingue2, acertou, hA2; /*indica qual bixo será lançado*/
  printf ("Voce deseja ligar o modo de depuracao?\n");
  printf ("Digite 1 (sim) ou 0 (nao): ");
  scanf("%d", &modoDepuracao);

  LeiaParametros( &yE, &vMax,
		  &yA, &hA,
		  &dist,
		  &nBix,
		  &nLin, &nCol,
		  &nUni,
		  &g );

  if (modoDepuracao == SIM) {
    printf ("\n\nModo de depuracao ligado!\n");
    printf ("Dados de entrada:\n");
    printf ("yE   = %9.4f  vMax = %9.4f \n", yE, vMax);
    printf ("yA   = %9.4f  hA   = %9.4f\n",  yA, hA);
    printf ("dist = %9.4f\n",  dist);
    printf ("nBix = %4d\n", nBix);
    printf ("nLin = %4d       nCol = %4d\n", nLin, nCol);
    printf ("nUni = %9.4f\n", nUni);
    printf ("g    = %9.4f\n", g);
    printf ("\n");


  printf ("\nPara fazer um lancamento, digite um deslocamento (no intervalo [0,1])\n");
  printf ("e uma orientacao (no intervalo [-1, 1])\n");
    scanf("%f %f", &des, &ori);
    altura_estilingue=Arredonda(yE/nUni);
    altura_estilingue2=altura_estilingue;
    yb=yE;
    yA=Arredonda(yA/nUni);
    v=des*vMax;
    /*angulo de lancamento*/ ori=Converte(ori);
    velX=v*Cos(ori, EPS);
    if(velX<0.0001)
    velY=0.0001;
    velY=v*Sen(ori, EPS);
    dt=(dist/velX)/nCol;
    hA=Arredonda(hA/nUni);
    hA2=hA-1;
    contb=1;/*conta numero de bixos a serem lancados*/

  ImprimaCondicaoInicial(nLin, nCol, nUni, yE, yA, hA);

  while(contb<=nBix){
  printf("====> Faca o lancamento %d / %d:", contb, nBix);
  yb2=yb;
  contb++;
  scanf("%f %f", &des, &ori);
    /*angulo de lancamento*/ ori=Converte(ori);
    nLin2=nLin;
    v=des*vMax;
    velX=v*Cos(ori, EPS);
    if(velX<0.0001)
    velX=0.0001;
    velY=v*Sen(ori, EPS);
    velY2=velY;
    dt=(dist/velX)/nCol;
    hA2=hA-1;
    printf("Grafico do lancamento com deslocamento/orientacao = [ %.4f, %.4f]\n\n", des, ori);
    printf("Condicoes iniciais desse lancamento:\n");
    printf("ang(rad) = %.4f    Cos = %.4f  Sin = %.4f\n", ori, Cos(ori, EPS), Sen(ori, EPS));
    printf("Velocidade = %.4f VelX = %.4f VelY = %.4f\n", v, velX, velY);
    printf("tempo total = %.4f incremento temporal = %.4f entre colunas\n", dist/velX, dt);
    nCol2=nCol;
    while(nCol2>=-2){
        printf(" ");
        nCol2--;
        if(nCol2==-3)
        printf("lin nInters    y1     y2\n");
    }

    acertou=NAO;
  while(nLin2>=0){
        nCol2=nCol;
        primeiro=-1;
        segundo=-1;
        nInters=0;
        while(nCol2>=0){
            AtualizaPosicaoEVelocidade(&yb2, &velY2, dt, g);
            altura_inteira=Arredonda(yb2/nUni);
            if(altura_inteira<0)
            altura_inteira=0;
            if(altura_inteira==nLin2&&altura_estilingue2!=nLin2){
            printf("o");
            nInters++;
            if(nInters==1&&altura_inteira!=0)/*associa ao primeiro yb da linha*/
            primeiro=yb2;
            if(nInters==1&&altura_inteira==0)
            primeiro=0;
            if(nInters==2&&altura_inteira!=0)/*associa ao segundo yb da linha*/
            segundo=yb2;
            if(nInters==2&&altura_inteira==0)
            segundo=0;
            if(nCol2==0&&yA<=altura_inteira&&altura_inteira<=yA+hA2)
            acertou=SIM;
            }
            if(nCol2%5==0&&nLin2%5==0&&altura_estilingue2!=nLin2&&altura_inteira!=nLin2){
            if(nCol2!=0||(nCol2==0&&yA+hA2!=nLin2))
            printf("+");
            if(nCol2==0&&yA+hA2==nLin2){
                if(hA2>0)
                hA2--;
            printf("A");
            }
            }
            if(nCol2%5==0&&nLin2%5!=0&&altura_estilingue2!=nLin2&&altura_inteira!=nLin2){
            if(nCol2!=0||(nCol2==0&&yA+hA2!=nLin2))
            printf("|");
            if(nCol2==0&&yA+hA2==nLin2){
                if(hA2>0)
                hA2--;
            printf("A");
            }
            }
            if(nCol2%5!=0&&nLin2%5==0&&altura_estilingue2!=nLin2&&altura_inteira!=nLin2)
            printf("-");
            if(nCol2%5!=0&&nLin2%5!=0&&altura_inteira!=nLin2)
            printf(" ");
            if(nCol2==nCol&&altura_estilingue2==nLin2){
            printf("E");
            altura_estilingue2=-1;/*Isso eh feito para que todo o restante da linha nao seja perdido, e imprima os | e os + corretamente*/
            }
            if(nCol2==0)
            printf("   %d   %d   %.4f   %.4f\n", nLin2, nInters, primeiro, segundo);
            nCol2--;
            }
            yb2=yb;
            velY2=velY;
        nLin2--;
    }
    altura_estilingue2=altura_estilingue;
    if(acertou==SIM){
    printf("Parabens! Voce acertou o alvo nessa jogada.\nO jogo terminou.");
    return 0;
    }
    else
    printf("Voce nao acertou o alvo nessa jogada.\n");
    }
  }

   if (modoDepuracao == NAO){
    printf ("\nPara fazer um lancamento, digite um deslocamento (no intervalo [0,1])\n");
    printf ("e uma orientacao (no intervalo [-1, 1])\n");
    scanf("%f %f", &des, &ori);
    altura_estilingue=Arredonda(yE/nUni);
    altura_estilingue2=altura_estilingue;
    yb=yE;
    yA=Arredonda(yA/nUni);
    v=des*vMax;
    /*angulo de lancamento*/ ori=Converte(ori);
    velX=v*Cos(ori, EPS);
    if(velX<0.0001)
    velY=0.0001;
    velY=v*Sen(ori, EPS);
    dt=(dist/velX)/nCol;
    hA=Arredonda(hA/nUni);
    hA2=hA-1;
    contb=1;

  ImprimaCondicaoInicial(nLin, nCol, nUni, yE, yA, hA);

  while(contb<=nBix){
  printf("====> Faca o lancamento %d / %d:", contb, nBix);
  yb2=yb;
  contb++;
  scanf("%f %f", &des, &ori);
    /*angulo de lancamento*/ ori=Converte(ori);
    nLin2=nLin;
    v=des*vMax;
    velX=v*Cos(ori, EPS);
    if(velX<0.0001)
    velX=0.0001;
    velY=v*Sen(ori, EPS);
    velY2=velY;
    dt=(dist/velX)/nCol;
    hA2=hA-1;
    nCol2=nCol;
    acertou=NAO;
  while(nLin2>=0){
        nCol2=nCol;
        primeiro=-1;
        segundo=-1;
        nInters=0;
        while(nCol2>=0){
            AtualizaPosicaoEVelocidade(&yb2, &velY2, dt, g);
            altura_inteira=Arredonda(yb2/nUni);
            if(altura_inteira<0)
            altura_inteira=0;
            if(altura_inteira==nLin2&&altura_estilingue2!=nLin2){
            printf("o");
            if(nCol2==0&&yA<=altura_inteira&&altura_inteira<=yA+hA2)
            acertou=SIM;
            }
            if(nCol2%5==0&&nLin2%5==0&&altura_estilingue2!=nLin2&&altura_inteira!=nLin2){
            if(nCol2!=0||(nCol2==0&&yA+hA2!=nLin2))
            printf("+");
            if(nCol2==0&&yA+hA2==nLin2){
                if(hA2>0)
                hA2--;
            printf("A");
            }
            }
            if(nCol2%5==0&&nLin2%5!=0&&altura_estilingue2!=nLin2&&altura_inteira!=nLin2){
            if(nCol2!=0||(nCol2==0&&yA+hA2!=nLin2))
            printf("|");
            if(nCol2==0&&yA+hA2==nLin2){
                if(hA2>0)
                hA2--;
            printf("A");
            }
            }
            if(nCol2%5!=0&&nLin2%5==0&&altura_estilingue2!=nLin2&&altura_inteira!=nLin2)
            printf("-");
            if(nCol2%5!=0&&nLin2%5!=0&&altura_inteira!=nLin2)
            printf(" ");
            if(nCol2==nCol&&altura_estilingue2==nLin2){
            printf("E");
            altura_estilingue2=-1;
            }
            if(nCol2==0)
            printf("\n");
            nCol2--;
            }
            yb2=yb;
            velY2=velY;
        nLin2--;
    }
    altura_estilingue2=altura_estilingue;
    if(acertou==SIM){
    printf("Parabens! Voce acertou o alvo nessa jogada.\nO jogo terminou.");
    return 0;
    }
    else
    printf("Voce nao acertou o alvo nessa jogada.\n");
    }
  }
return 0;
}

