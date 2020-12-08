/*============================================================================
| (c) Copyright Arthur L. Corcoran, 1992, 1993.  All rights reserved.
|
| Genetic Algorithm Test Program 
============================================================================*/
#include "ga.h"

int obj_fun();    /*--- Forward declaration ---*/

/* Global Variables*/
char graph[500][500];  // se podría optimizar usando malloc...
int nnodes, nedges;

/* function prototypes */
int obj_fun(Chrom_Ptr);
int read_instance();

char* select_instancia(int n);
int max_clique(int n);

/*----------------------------------------------------------------------------
| main()
----------------------------------------------------------------------------*/
int main() 
{
   GA_Info_Ptr ga_info;
   int i;

 	
   	int k=9;
   	/*--- Initialize the genetic algorithm ---*/
   	ga_info = GA_config("GAconfig.txt", obj_fun);

   		    // Rellena la matriz "graph" con los datos del fichero
	// Tb. inicializa nnodes y nedges
	read_instance(select_instancia(k));  //  Nombre de la instancia
  
	// IMPORTANTE: se puede cambiar la longitud del chromosoma con la
	//             info del fichero (despues de llamar GA_config(...)  )
	ga_info->chrom_len = nnodes;

   	/*--- Run the GA ---*/
   	GA_run(ga_info);

   	double A = 0;
   	printf("\nBest chrom:  ");
   	for(i=0;i<ga_info->chrom_len;i++)
   	{
	     	printf("%5.4f  ",ga_info->best->gene[i]);
	     	A+=ga_info->best->gene[i];

   	}
   
   printf("   (fitness: %g)\n\n",ga_info->best->fitness);

   if(ga_info->best->fitness >= 0.5)
   {
   	printf("------------------- ¡CLIQUE ENCONTRADO DE %g! :) ------------------- \n\n",A);
   	if(max_clique(k)<=A)
   		printf("------------------- ¡Y ES EL MAXIMO CLIQUE! :) ------------------- \n\n");
   }
   else
   	printf("--------------------- ¡CLIQUE NO ENCONTRADO! :( -------------------- \n\n");

	}

/*----------------------------------------------------------------------------
| obj_fun() - user specified objective function
----------------------------------------------------------------------------*/
int obj_fun(Chrom_Ptr chrom) 
{
  int i; 
  int j;
  double A = 0.0;
  double B = 0.0;
  double C = 0.0;
  double Cl = 0.0;
  double s = 0.0;
  double P = 0.0;
  double val = 0.0;
  double val_aux = 0.0;

  // CALCULO DE A
  for(i = 0; i < chrom->length; i++)
    {        
      val_aux =  chrom->gene[i];
      if(val_aux != 0)
      	A += 1;
    }


  // CALCULO DE VERTICES (B)
  for(i = 0; i < nnodes-1; i++)
  {
  	for(j = i+1; j < nnodes; j++)
  	{
  		if(chrom->gene[i] == 1 && chrom->gene[j] == 1 && graph[i][j] == 1)
  		{
  			B+=1;
  		}
  	}
  }


  // CALCULO DEL FITNESS
 C = A*(A-1)/2;
   if(C == B || A==0)
  {
  	Cl = 1;
  } 


 //chrom->fitness = 0.5 * (B/C + Cl*A/nnodes);
 chrom->fitness = 0.5 * (B/C + Cl*A/nnodes);
  
  return 0;
  
}


// read DIMACS format
int read_instance(char *filename)
{
  char dummy1;
  char dummy2[100];
  int dummy3;
  int n1,n2;
  FILE *inputf;
  int i,j;
  
  
  nnodes = 0;
  nedges = 0;
  
  if( (inputf=fopen(filename,"rf")) == NULL )
    {
      printf( "Cannot open file %s\n",filename);
      exit(-1);
    }

  // lee la cabecera
  fscanf(inputf,"%c %s %d %d\n",&dummy1,dummy2,&nnodes,&nedges);
  
  printf("Opening %s (%d nodes, %d edges)\n",filename,nnodes,nedges);
   
  for(i=0;i<nnodes;i++)
    for(j=0;j<nnodes;j++)
      graph[i][j] = 0;

  // salta la lista de nodos
  for(i=0;i<nnodes;i++)
    fscanf(inputf,"%c  %d %d\n",&dummy1,&dummy3,&dummy3);

  // lee los edges
  for(i=0;i<nedges;i++)
    {
      fscanf(inputf,"%c %d %d\n",&dummy1,&n1,&n2);
      graph[n1-1][n2-1] = 1;  // ojo que los vectores en C empiezan desde 0
      graph[n2-1][n1-1] = 1;
    }
  
  fclose(inputf);
  
}


char* select_instancia(int n)
{
	char* instancia;

	switch (n)
	{
		case 1:
			instancia = "instancias/MANN_a9.clq.txt";
			break;
		case 2:
			instancia = "instancias/Toy4.clq.txt";
			break;
		case 3:
			instancia = "instancias/Toy6.clq.txt";
			break;
		case 4:
			instancia = "instancias/Toy8.clq.txt";
			break;
		case 5:
			instancia = "instancias/hamming6-2.clq.txt";
			break;
		case 6:
			instancia = "instancias/hamming6-4.clq.txt";
			break;
		case 7:
			instancia = "instancias/johnson8-2-4.clq.txt";
			break;
		case 8:
			instancia = "instancias/johnson8-4-4.clq.txt";
			break;
		case 9:
			instancia = "instancias/keller4.clq.txt";
			break;
		case 10:
			instancia = "instancias/p_hat300-1.clq.txt";
			break;
		case 11:
			instancia = "instancias/p_hat300-2.clq.txt";
			break;
		case 12:
			instancia = "instancias/p_hat500-1.clq.txt";
			break;
		case 13:
			instancia = "instancias/p_hat500-2.clq.txt";
			break;
		case 14:
			instancia = "instancias/san200_0.7_1.clq.txt";
			break;
	}
	return instancia;
}

int max_clique(int n)
{
	int clique;

	switch (n)
	{
		case 1:
			clique = 16;
			break;
		case 2:
			clique = 3;
			break;
		case 3:
			clique = 4;
			break;
		case 4:
			clique = 5;
			break;
		case 5:
			clique = 32;
			break;
		case 6:
			clique = 4;
			break;
		case 7:
			clique = 4;
			break;
		case 8:
			clique = 14;
			break;
		case 9:
			clique = 11;
			break;
		case 10:
			clique = 8;
			break;
		case 11:
			clique = 25;
			break;
		case 12:
			clique = 9;
			break;
		case 13:
			clique = 36;
			break;
		case 14:
			clique = 18;
			break;
	}
	return clique;
}

