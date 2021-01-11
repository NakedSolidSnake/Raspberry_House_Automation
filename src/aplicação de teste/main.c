#include <stdio.h>                                                                                   
#include <stdlib.h>  
#include <stdbool.h>
#include <string.h>

#include "mysql.h"

int menu(void);
void cleanBuffer(void);

bool connect_dataBase(MYSQL *con);
bool create_dataBase(MYSQL *con);
bool excluir_dataBase(MYSQL *con);
bool listar_dataBase(MYSQL *con);
bool listar_table(MYSQL *con);
bool listar_registrosTable(MYSQL *con);
bool criar_tableUsuario(MYSQL *con);
bool excluir_tableUsuario(MYSQL *con);
bool insert_registroTable(MYSQL *con);
bool excluir_registroTable(MYSQL *con);
bool alterar_registroTable(MYSQL *con);


enum cmd_query
{
	CREATE_DATABASE,
	DROP_DATABASE,
	DROP_TABLE,
	DELETE_FROM,
	SELECT_FROM,
	SHOW_DATABASES,
	SHOW_TABLES,
	CREATE_TABLE,
	INSERT_INTO
};

char cmd[][100] = {{"CREATE DATABASE"},
				   {"DROP DATABASE"},
				   {"DROP TABLE"},
				   {"DELETE FROM"},
				   {"SELECT * FROM"},
				   {"SHOW DATABASES"},
				   {"SHOW TABLES"},
				   {"CREATE TABLE"},
				   {"INSERT INTO"}};

char *host = "localhost";
char *user = "root";
char *passwd = "1234";
char *dbname = "registros";

int port = 3306;
char *unix_socket = NULL;
unsigned long client_flagg = 0;


int main(int argc, char **argv)
{
	int ret;
	MYSQL *con = mysql_init(NULL);

	do{
		ret = menu();

		if(ret == 0)
		{
			printf("%s\n", false < connect_dataBase(con) ? "CONECTADO" : "ERRO" );
		}

		else if (ret == 1)
		{		
			printf("%s\n", false < create_dataBase(con) ? "SUCESSO" : "ERRO" );
		}

		else if (ret == 2)
		{		
			printf("%s\n", false < criar_tableUsuario(con) ? "SUCESSO" : "ERRO" );
		}
		else if (ret == 3)
		{
			printf("%s\n", false < insert_registroTable(con) ? "SUCESSO" : "ERRO" );
		}

		else if (ret == 4)
		{
			printf("%s\n", false < alterar_registroTable(con) ? "SUCESSO" : "ERRO" );
		}	

		else if (ret == 5)
		{
			printf("%s\n", false < listar_dataBase(con) ? "SUCESSO" : "ERRO" );
		}

		else if(ret == 6)
		{
			printf("%s\n", false <  listar_registrosTable(con) ? "SUCESSO" : "ERRO" );
		}

		else if(ret == 7)
		{
			printf("%s\n", false < listar_table(con) ? "SUCESSO" : "ERRO" ); 
		}
		
		else if (ret == 8)
		{		
			printf("%s\n", false < excluir_dataBase(con) ? "SUCESSO" : "ERRO" );
		}

		else if (ret == 9)
		{		
			printf("%s\n", false < excluir_tableUsuario(con) ? "SUCESSO" : "ERRO" );
		}
		
		else if (ret == 10)
		{		
			printf("%s\n", false < excluir_registroTable(con) ? "SUCESSO" : "ERRO" );
		}

	}while ( ret != 100);
	
	return 0;
}


int menu(void){
	int opcao;
	
	printf("\n");
	printf("**************************\n");
	printf("********** Menu **********\n");
	printf("**************************\n");
	printf("0 - Connect Data Base\n");
	printf("1 - CreateDataBase\n");
	printf("2 - CreateTableUsuario\n");
	printf("3 - InsertRegistrosTable\n");
	printf("4 - AlteraRegistrosTable\n");
	printf("5 - ListarDataBase\n");
	printf("6 - ListarRegistrosTable\n");
	printf("7 - ListarTables\n");
	printf("8 - ExcluirDataBase\n");
	printf("9 - ExcluirTable\n");
	printf("10 - ExcluirRegistroTable\n");
	printf("100 - FECHAR APLICATIVO\n");
	printf("***************************\n");
	printf("Opcao escolhida: ");
	scanf(" %d", &opcao);
	cleanBuffer();
	printf("\n");

	return opcao;
}

void cleanBuffer(void)
{
    char c;
    while ((c = getchar()) != '\n'  && c != EOF);
}

bool connect_dataBase(MYSQL *con)
{
	if (con == NULL)
	{
		fprintf(stderr, "%s\n", mysql_error(con));
		exit(1);
	}

	if (mysql_real_connect(con, host, user, passwd, dbname, port, unix_socket, client_flagg) == NULL)
	{
		fprintf(stderr, "%s\n", mysql_error(con));
		mysql_close(con);
		exit(1);
	}
	return true;
}

bool create_dataBase(MYSQL *con)
{	
	char buffer[140];
	char nome[40];
	
	printf("Digite o nome do Banco de Dados: ");
	fgets(nome, 40, stdin);

	snprintf(buffer, 140, "%s %s", cmd[CREATE_DATABASE],nome);


	printf("\t%s\n",buffer);

	if (mysql_query(con, buffer))
	{
		fprintf(stderr, "%s\n", mysql_error(con));
		mysql_close(con);
		return false;
	}  

	return true;
}

bool excluir_dataBase(MYSQL *con)
{	
	char buffer[140];
	char nome[40];
	
	printf("Digite o nome do Banco de Dados: ");
	fgets(nome, 40, stdin);

	snprintf(buffer, 140, "%s %s", cmd[DROP_DATABASE],nome);


	printf("\t%s\n",buffer);

	if (mysql_query(con, buffer))
	{
		fprintf(stderr, "%s\n", mysql_error(con));
		mysql_close(con);
		return false;
	}  

	return true;
}

bool listar_dataBase(MYSQL *con)
{
	MYSQL_RES *res;
  	MYSQL_ROW row;
	
	if (mysql_query(con,cmd[SHOW_DATABASES]))
	{
	    fprintf(stderr, "Erro: %s\n", mysql_error(con));
        mysql_close(con);
		return false;
	}
	else{
		fprintf(stdout, "SUCESSO !!!\n");
		res = mysql_store_result(con);
		while (row = mysql_fetch_row(res))
		{
			fprintf(stdout, "%s\t\n",row[0]);
		}
	}
	
	mysql_free_result(res);
	return true;
}

bool listar_table(MYSQL *con)
{
	MYSQL_RES *res;
  	MYSQL_ROW row;
    printf("%s\n",cmd[SHOW_TABLES]);

	if (mysql_query(con, cmd[SHOW_TABLES]))
	{
	    fprintf(stderr, "Erro: %s\n", mysql_error(con));
        mysql_close(con);;
		return false;
	}
	else{
		res = mysql_store_result(con);
		while (row = mysql_fetch_row(res))
		{
			fprintf(stdout, "%s\t\n",row[0]);
		}
	}
	mysql_free_result(res);
	return true;
}

bool listar_registrosTable(MYSQL *con)
{
	MYSQL_RES *res;
  	MYSQL_ROW row;

	char buffer[140];
	char nome[40];
	
	printf("Digite o nome da Tabela: ");
	fgets(nome, 40, stdin);

	snprintf(buffer, 140, "%s %s", cmd[SELECT_FROM],nome);
	printf("\t%s\n",buffer);


	if (mysql_query(con, buffer))
	{
	    fprintf(stderr, "Erro: %s\n", mysql_error(con));
        mysql_close(con);;
		return false;
	}
	else{
		fprintf(stdout, "SUCESSO !!!\n");
		res = mysql_store_result(con);
		while (row = mysql_fetch_row(res))
		{
			fprintf(stdout, "%s\t%s\t%s\n",row[0], row[1], row[2]);
		}
	}
	mysql_free_result(res);
	return true;
}

bool criar_tableUsuario(MYSQL *con)
{
	char buffer[1024];
	char nome[40];

	char data_table [][100] = {{"(id int AUTO_INCREMENT,"},
						       {"timestamp NUMERIC NOT NULL,"},
					    	   {"Nome VARCHAR(40) NOT NULL,"},
					 	       {"PRIMARY KEY(id))"}};
	
	printf("Digite o nome para a Tabela: ");
	scanf("%40s",nome);
	snprintf(buffer,140, "%s %s", cmd[CREATE_TABLE],nome);

	for (int i = 0; i < 4; i++)
	{
		strncat(buffer,data_table[i], sizeof(data_table[i]));
	}

	if (mysql_query(con, buffer))
	{
	    fprintf(stderr, "Erro: %s\n", mysql_error(con));
        mysql_close(con);;
		return false;
	}
	return true;
}

bool excluir_tableUsuario(MYSQL *con)
{
	char buffer[140];
	char nome[40];
	
	printf("Digite o nome da Tabela a ser excluida: ");
	fgets(nome, 40, stdin);

	snprintf(buffer, 140, "%s %s", cmd[DROP_TABLE],nome);


	printf("\t%s\n",buffer);

	if (mysql_query(con, buffer))
	{
		fprintf(stderr, "%s\n", mysql_error(con));
		mysql_close(con);
		return false;
	}  

	return true;
}

bool excluir_registroTable(MYSQL *con)
{
	int id;
	char buffer[140];
	char nome[40];
	char op;
	
	printf("Digite o nome da Tabela: ");
	scanf("%40s",nome);
	cleanBuffer();

	printf("Deseja excluir todos os Registros da tabela ( S or N ): ");
	scanf("%c",&op);
	cleanBuffer();

	if( toupper(op) == 'S')
	{
		snprintf(buffer, 140, "TRUNCATE TABLE %s", nome);
	}
	else
	{
		printf("Informe o Id do usuario a ser excluido: ");
		scanf("%d",&id);
		snprintf(buffer, 140, "%s %s WHERE id = %d", cmd[DELETE_FROM], nome, id);
	}

	printf("\t%s\n",buffer);

	if (mysql_query(con, buffer))
	{
		fprintf(stderr, "%s\n", mysql_error(con));
		mysql_close(con);
		return false;
	}  

	return true;
}

bool insert_registroTable(MYSQL *con)
{
	int id;
	unsigned short int dia,mes,ano;
	char usuario[40];
	char nome_table[40];
	char buffer[1024];

	printf("Nome da tabela a inserir: ");
	scanf("%40s",nome_table);
	cleanBuffer();
	
	printf("Digite o Ano: ");
	scanf("%d",&ano);
	cleanBuffer(); 
		
	printf("Digite o Mes: ");
	scanf("%d",&mes);
	cleanBuffer();

	printf("Digite o Dia: ");
	scanf("%d",&dia);
	cleanBuffer();

	printf("Digite o nome do Usuario: ");
	scanf("%40s",usuario);
	cleanBuffer();

	printf("Digite o id: ");
	scanf("%i",&id);
	cleanBuffer();  
	
	snprintf(buffer,1024, "%s %s VALUES (%d,%d-%d-%d,'%s')", cmd[INSERT_INTO], nome_table, id,ano,mes,dia, usuario);
	printf("%s\n",buffer);

	if (mysql_query(con, buffer))
	{
	    fprintf(stderr, "Erro: %s\n", mysql_error(con));
        mysql_close(con);;
		return false;
	}
	return true;
}

bool alterar_registroTable(MYSQL *con)
{
	int id, new_id;
	unsigned short int dia,mes,ano;
	char usuario[40];
	char nome_table[40];
	char buffer[1024];

	printf("Nome da tabela: ");
	scanf("%40s",nome_table);
	cleanBuffer();
	
	printf("Modificar Ano: ");
	scanf("%d",&ano);
	cleanBuffer(); 
		
	printf("Modificar Mes: ");
	scanf("%d",&mes);
	cleanBuffer();

	printf("Modificar Dia: ");
	scanf("%d",&dia);
	cleanBuffer();

	printf("Modificar nome do Usuario: ");
	scanf("%40s",usuario);
	cleanBuffer();

	printf("Modificar o id: ");
	scanf("%i",&new_id);
	cleanBuffer();

	printf("Informe o id que receberar as alteracoes: ");
	scanf("%i",&id);
	cleanBuffer();
	
	
	snprintf(buffer,1024, "UPDATE %s SET id = %d WHERE id = %d",nome_table, new_id, id);
	printf("%s\n",buffer);  

	if (mysql_query(con, buffer))
	{
	    fprintf(stderr, "Erro: %s\n", mysql_error(con));
        mysql_close(con);
		return false;
	}
	
	snprintf(buffer,1024, "UPDATE %s SET timestamp = %d-%d-%d WHERE id = %d",nome_table, ano, mes, dia, id);
	printf("%s\n",buffer);  

	if (mysql_query(con, buffer))
	{
	    fprintf(stderr, "Erro: %s\n", mysql_error(con));
        mysql_close(con);
		return false;
	} 

	snprintf(buffer,1024, "UPDATE %s SET Nome = '%s' WHERE id = %d",nome_table, usuario, id);
	printf("%s\n",buffer);  

	if (mysql_query(con, buffer))
	{
	    fprintf(stderr, "Erro: %s\n", mysql_error(con));
        mysql_close(con);
		return false;
	}

	return true;
}

