#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#include "menu.h"
#include "mylib.h"

typedef int (*Interface)(void);

int call (Interface func)
{
    return func();
}

Interface ini[] =
{
    connect_dataBase,
    create_dataBase,
    criar_tableUsuario,
    insert_registroTable,
    alterar_registroTable,
    listar_dataBase,
    listar_registrosTable,
    listar_table,
    excluir_dataBase,
    excluir_tableUsuario,
    excluir_registroTable,
    describe_tables
};   

const int size_ini = sizeof(ini) / sizeof(ini[0]);  

int main(int argc, char **argv)
{			
	int ret; 
    do
    {
        ret = menu();
        for(int i = 0; i < size_ini; i++)
        {
            if( ret == i )
            {
                printf("%s\n", false < call(ini[i]) ? "SUCESSO" : "ERRO" );
                break;
            }
            else if( i >= (size_ini - 1) && ret != SAIR)
            {
                printf("Opcao Invalida !!!\n");
            }
        }

    } while(ret != SAIR);
  
	return 0; 
}

