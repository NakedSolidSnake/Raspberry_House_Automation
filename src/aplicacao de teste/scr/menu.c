#include <stdio.h>                                                                                   
#include <stdlib.h>  
#include <stdbool.h>

#include "menu.h"
#include "mylib.h"

typedef int (*Op)(void);

typedef struct
{
	int op;
	const char *str;
    Op operation;
}Operations;

typedef enum{
    CONNECT_DATABASE = 0,
    CREATE_DATABASE,
    CRIAR_TABLEUSUARIO,
    INSERT_REGISTROTABLE,
    ALTERAR_REGISTROTABLE,
    LISTAR_DATABASE,
    LISTAR_REGISTROSTABLE,
    LISTAR_TABLE,
    EXCLUIR_DATABASE,
    EXCLUIR_TABLEUSUARIO,
    EXCLUIR_REGISTROTABLE,
    DESCRIBE_TABLES,
	SAIR = 100,
} Defines;

Operations opcao[] = 
{
    { CONNECT_DATABASE, 	 "Connect Data Base\n",     connect_dataBase},
    { CREATE_DATABASE, 		 "CreateDataBase\n",        create_dataBase},
	{ CRIAR_TABLEUSUARIO, 	 "CreateTableUsuario\n",    criar_tableUsuario},
    { INSERT_REGISTROTABLE,  "InsertRegistrosTable\n",  insert_registroTable},
    { ALTERAR_REGISTROTABLE, "AlteraRegistrosTable\n",  alterar_registroTable},
	{ LISTAR_DATABASE, 		 "ListarDataBase\n",        listar_dataBase},
	{ LISTAR_REGISTROSTABLE, "ListarRegistrosTable\n",  listar_registrosTable},
    { LISTAR_TABLE, 		 "ListarTables\n",          listar_table},
    { EXCLUIR_DATABASE, 	 "ExcluirDataBase\n",       excluir_dataBase},
    { EXCLUIR_TABLEUSUARIO,  "ExcluirTable\n",          excluir_tableUsuario},
    { EXCLUIR_REGISTROTABLE, "ExcluirRegistroTable\n",  excluir_registroTable},
    { DESCRIBE_TABLES, 		 "DescribleTable\n",        describe_tables},
	{ SAIR,				 	 "FECHAR APLICATIVO\n",   	NULL},
};

const int size_opcao = sizeof(opcao) / sizeof(opcao[0]);

int menu(void){
		
	int op;
	
		printf("**************************\n");
		printf("********** Menu **********\n");
		printf("**************************\n");
		
		for(int i = 0; i < size_opcao; i++)
		{
			printf("%d - %s",opcao[i].op, opcao[i].str);
		}
		
		printf("***************************\n");
		printf("Opcao escolhida: ");
		scanf("%d",&op);
		cleanBuffer();

		for(int i = 0; i < size_opcao; i++)
		{
			if( op == i )
			{
				printf("%s\n", false < opcao[i].operation() ? "SUCESSO" : "ERRO" );
				break;
			}
			else if( op == SAIR)
			{
				return true;
			}
			if( i >= ( size_opcao - 1) )
			{
				printf("Opcao Invalida !!!\n");
			}
		}	
	return false;
}