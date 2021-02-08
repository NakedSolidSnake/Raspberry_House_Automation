#include <stdio.h>                                                                                   
#include <stdlib.h>  
#include "menu.h"
#include "mylib.h"

char *opcao[SIZE_OP] = {"Connect Data Base\n",
					   "CreateDataBase\n",
					   "CreateTableUsuario\n",
					   "InsertRegistrosTable\n",
					   "AlteraRegistrosTable\n",
					   "ListarDataBase\n",
					   "ListarRegistrosTable\n",
					   "ListarTables\n",
					   "ExcluirDataBase\n",
					   "ExcluirTable\n",
					   "ExcluirRegistroTable\n",
					   "DescribleTable\n",	
					   "FECHAR APLICATIVO\n"};  
				 

int menu(void){
		
	int op;
	printf("**************************\n");
	printf("********** Menu **********\n");
	printf("**************************\n");
	
	for(int i = 0; i < SIZE_OP; i++)
	{
		printf("%d - %s",i, opcao[i]);
	}
	
	printf("***************************\n");
	printf("Opcao escolhida: ");
	scanf("%d",&op);
	cleanBuffer();
	return op;  
}



