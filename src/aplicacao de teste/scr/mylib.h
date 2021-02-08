#ifndef MYLIB__H_INCLUDE
#define MYLIB__H_INCLUDE

#ifdef _WIN32 
    #include "mysql.h"
#elif __unix__ || __linux__ 
	#include <mysql.h>
#endif


int connect_dataBase();
int create_dataBase();
int excluir_dataBase();
int listar_dataBase();  
int listar_table();
int listar_registrosTable();
int criar_tableUsuario();
int excluir_tableUsuario();
int insert_registroTable();
int excluir_registroTable();
int alterar_registroTable(); 
int describe_tables();

void cleanBuffer(void);

#endif // MYLIB__H_INCLUDE