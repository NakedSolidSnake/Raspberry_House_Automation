#include <stdio.h>                                                                                   
#include <stdlib.h>  
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "mylib.h"

#define BUFFER 512

MYSQL *con = NULL;

typedef enum
{
    host = 0,
    user,
    passwd,
    dbname,
    port,
    unix_socket,
    client_flag
}eCampos;

int size_eCampos = 7;

int  print_name(char name_colun[][8], int *colunas, int size_colun);
int  print_line(int *colunas, int size_colun);


int connect_dataBase()
{
	FILE *config;
	con = mysql_init(NULL);
	char msg[BUFFER];
	char *campos[11] = {"host", "user", "passwd", "dbname", "port", "unix_socket", "client_flag"};
	char *dado[7];
		
	if (con == NULL)
	{
		fprintf(stderr, "%s\n", mysql_error(con));
		exit(1);
	}
	
	config = fopen("config.txt", "r"); 
	if( config == NULL)
	{
	printf("Arquivo config nao pode ser aberto\n");
	return 0;
	}
 
	int count = 0;
	while (fgets(msg, BUFFER, config) != NULL)
	{				
		if( count != size_eCampos)
		{
			if( !(strncmp(campos[count], msg, strlen(campos[count]))))
			{
				if(msg != NULL)
				{
					int size_msg = strlen(msg);
					for(int i = 0; i < size_msg; i++)
					{
						if(msg[i] == ',')
						{
							for(int j = 0; j < (size_msg - i); j++)
							{
								if(msg[j+i] == ';')
								{
									dado[count] =  (char*)malloc( j * sizeof(char));
									strncpy(dado[count], msg+i+1, j );
									*(dado[count] + (j - 1)) = '\0';							
								}
							}							
						}
					}
				}
			}
			else
			{
			printf("Invalido Linha[%d] - [%s]",count + 1, campos[count]);
			return false;
			}
			count++;
		}
	}
	if (mysql_real_connect(con, dado[host],dado[user], dado[passwd], dado[dbname], atoi(dado[port]), 0, atoi(dado[client_flag])) == NULL)
	{
		fprintf(stderr, "%s\n", mysql_error(con));
		mysql_close(con);
		exit(1);
	} 
	
	for(int i = 0; i < size_eCampos; i++)
	{
		free(dado[i]);
	}

	fclose(config);   
	return true;
}

int create_dataBase()
{	
	char msg[BUFFER];
	char name[40];
	
	printf("Digite o nome do Banco de Dados: ");
	fgets(name, 40, stdin);

	snprintf( msg, BUFFER, "CREATE DATABASE %s", name);


	printf("\t%s\n",msg);

	if (mysql_query(con, msg))
	{
		fprintf(stderr, "%s\n", mysql_error(con));
		mysql_close(con);
		return false;
	}  

	return true;
}

int excluir_dataBase()
{	
	char msg[BUFFER];
	char name[40];
	
	printf("Digite o nome do Banco de Dados: ");
	fgets(name, 40, stdin);

	snprintf(msg, BUFFER, "DROP DATABASE %s", name);


	printf("\t%s\n",msg);

	if (mysql_query(con, msg))
	{
		fprintf(stderr, "%s\n", mysql_error(con));
		mysql_close(con);
		return false;
	}  

	return true;
}

int listar_dataBase()
{
	MYSQL_RES *res;
  	MYSQL_ROW row;
	
	printf("\tSHOW DATABASES\n");

	if (mysql_query(con,"SHOW DATABASES"))
	{
	    fprintf(stderr, "Erro: %s\n", mysql_error(con));
        mysql_close(con);
		return false;
	}
	else{
		res = mysql_store_result(con);
		while ((row = mysql_fetch_row(res)))
		{
			fprintf(stdout, "%s\t\n",row[0]);
		}
	}
	
	mysql_free_result(res);
	return true;
}

int listar_table()
{
	MYSQL_RES *res;
  	MYSQL_ROW row;
    printf("\tSHOW TABLES\n");

	if (mysql_query(con, "SHOW TABLES"))
	{
	    fprintf(stderr, "Erro: %s\n", mysql_error(con));
        mysql_close(con);;
		return false;
	}
	else{
		res = mysql_store_result(con);
		while ((row = mysql_fetch_row(res)))
		{
			fprintf(stdout, "%s\t\n",row[0]);
		}
	}
	mysql_free_result(res);
	return true;
}

int listar_registrosTable()
{
	MYSQL_RES *res;
  	MYSQL_ROW row;

	char msg[BUFFER];
	char name[40];
	
	printf("Digite o nome da Tabela: ");
	fgets(name, 40, stdin);

	snprintf(msg, BUFFER, "SELECT * FROM %s",name);
	printf("\t%s\n",msg);


	if (mysql_query(con, msg))
	{
	    fprintf(stderr, "Erro: %s\n", mysql_error(con));
        mysql_close(con);;
		return false;
	}
	else{
		res = mysql_store_result(con);
		while ((row = mysql_fetch_row(res)))
		{
			fprintf(stdout, "%s\t%s\t%s\n",row[0], row[1], row[2]);
		}
	}
	mysql_free_result(res);
	return true;
}

int criar_tableUsuario()
{
	char msg[BUFFER];
	char name[40];
	
	char *data_table[100] = {"(id int AUTO_INCREMENT,",
							 "timestamp NUMERIC NOT NULL,",
							 "Nome VARCHAR(40) NOT NULL,",
							 "PRIMARY KEY(id))"}; 

	printf("Digite o nome para a Tabela: ");
	scanf("%40s",name);
	snprintf(msg, BUFFER, "CREATE TABLE %s",name);
	
	for (int i = 0; i < 4; i++)
	{
		strncat(msg, data_table[i], strlen(data_table[i]));
	}
	if (mysql_query(con, msg))
	{
	    fprintf(stderr, "Erro: %s\n", mysql_error(con));
        mysql_close(con);;
		return false;
	}
	printf("\t%s\n", msg);
	return true;
}

int excluir_tableUsuario()
{
	char msg[BUFFER];
	char name[40];
	
	printf("Digite o nome da Tabela a ser excluida: ");
	fgets(name, 40, stdin);

	snprintf(msg, BUFFER, "DROP TABLE %s",name);


	printf("\t%s\n",msg);

	if (mysql_query(con, msg))
	{
		fprintf(stderr, "%s\n", mysql_error(con));
		mysql_close(con);
		return false;
	}  

	return true;
}

int excluir_registroTable()
{
	int id;
	char msg[BUFFER];
	char name[40];
	char op;
	
	printf("Digite o nome da Tabela: ");
	scanf("%40s",name);
	cleanBuffer();

	printf("Deseja excluir todos os Registros da tabela ( S or N ): ");
	scanf("%c",&op);
	cleanBuffer();

	if( toupper(op) == 'S')
	{
		snprintf(msg, BUFFER, "TRUNCATE TABLE %s", name);
	}
	else
	{
		printf("Informe o Id do usuario a ser excluido: ");
		scanf("%d",&id);
		snprintf(msg, BUFFER, "DELETE FROM %s WHERE id = %d",name, id);
	}

	printf("\t%s\n", msg);

	if (mysql_query(con, msg))
	{
		fprintf(stderr, "%s\n", mysql_error(con));
		mysql_close(con);
		return false;
	}  

	return true;
}

int insert_registroTable()
{
	int id;
	unsigned short int dia,mes,ano;
	char usuario[40];
	char nome_table[40];
	char msg[BUFFER];

	printf("Nome da tabela a inserir: ");
	scanf("%40s",nome_table);
	cleanBuffer();
	
	printf("Digite o Ano: ");
	scanf("%hd",&ano);
	cleanBuffer(); 
		
	printf("Digite o Mes: ");
	scanf("%hd",&mes);
	cleanBuffer();

	printf("Digite o Dia: ");
	scanf("%hd",&dia);
	cleanBuffer();

	printf("Digite o nome do Usuario: ");
	scanf("%40s",usuario);
	cleanBuffer();

	printf("Digite o id: ");
	scanf("%i",&id);
	cleanBuffer();  
	
	snprintf(msg,BUFFER, "INSERT INTO %s VALUES (%d,%hd-%hd-%hd,'%s')",nome_table, id,ano,mes,dia, usuario);
	printf("%s\n",msg);

	mysql_autocommit(con, false);
	if (mysql_query(con, msg))
	{
	    fprintf(stderr, "Erro: %s\n", mysql_error(con));
		mysql_rollback(con);
        mysql_close(con);
		return false;
	}
	mysql_commit(con);
	return true;
}

int alterar_registroTable()
{
	int id, new_id;
	unsigned short int dia,mes,ano;
	char usuario[40];
	char nome_table[40];
	char msg[BUFFER];

	printf("Nome da tabela: ");
	scanf("%40s",nome_table);
	cleanBuffer();
	
	printf("Modificar Ano: ");
	scanf("%hd",&ano);
	cleanBuffer(); 
		
	printf("Modificar Mes: ");
	scanf("%hd",&mes);
	cleanBuffer();

	printf("Modificar Dia: ");
	scanf("%hd",&dia);
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
	
	
	snprintf(msg, BUFFER, "UPDATE %s SET id = %d WHERE id = %d",nome_table, new_id, id);
	printf("%s\n",msg);  

	mysql_autocommit(con, false);
	if (mysql_query(con, msg))
	{
	    fprintf(stderr, "Erro: %s\n", mysql_error(con));
		mysql_rollback(con);
        mysql_close(con);
		return false;
	}
	mysql_commit(con);

	snprintf(msg, BUFFER, "UPDATE %s SET timestamp = %hd-%hd-%hd WHERE id = %d",nome_table, ano, mes, dia, id);
	printf("%s\n",msg);  

	mysql_autocommit(con, false);
	if (mysql_query(con, msg))
	{
	    fprintf(stderr, "Erro: %s\n", mysql_error(con));
		mysql_rollback(con);
        mysql_close(con);
		return false;
	} 
	mysql_commit(con);

	snprintf(msg, BUFFER, "UPDATE %s SET Nome = '%s' WHERE id = %d",nome_table, usuario, id);
	printf("%s\n",msg);  

	mysql_autocommit(con, false);
	if (mysql_query(con, msg))
	{
	    fprintf(stderr, "Erro: %s\n", mysql_error(con));
		mysql_rollback(con);
        mysql_close(con);
		return false;
	}
	mysql_commit(con);

	return true;
}

int describe_tables()
{
	MYSQL_RES *res;
  	MYSQL_ROW row;

	int colunas[6] = {0};
	int total_colunas = 6;
	enum colun {Field = 0, Type, Null, Key, Default, Extra };
	char name_colun[][8] = {"Field", "Type", "Null", "Key", "Default", "Extra" };

	char name[40];
	char msg[BUFFER];

	printf("Nome da tabela: ");
	fgets(name, 40, stdin);

	printf("\tDESCRIBE %s",name); 
	snprintf( msg, BUFFER, "DESCRIBE %s", name);

	if (mysql_query(con, msg))
	{
	    fprintf(stderr, "Erro: %s\n", mysql_error(con));
        mysql_close(con);
		return false;
	}
	else{		
	res = mysql_store_result(con);

	for(int i = 0 ; i < total_colunas; i++)
	{ 
		colunas[i] = strlen(name_colun[i]);		
	} 

	while ((row = mysql_fetch_row(res)))
	{
		 for(int i = 0; i < total_colunas; i++)
		 {
			 if(row[i] != NULL)
			 {
				int tan =  strlen(row[i]);
				if(tan > colunas[i])
				{
					colunas[i] = tan;
				}				
			 }
		 }
	  } 		

		print_line(colunas, total_colunas);
		print_name(name_colun, colunas, total_colunas);
		print_line(colunas, total_colunas);

	if (mysql_query(con, msg))
	{
	    fprintf(stderr, "Erro: %s\n", mysql_error(con));
        mysql_close(con);
		return false;
	}	 		

	res = mysql_store_result(con);

		while ((row = mysql_fetch_row(res)))
		{
			int count = 0;
			while(count < total_colunas)
			{
				fprintf(stdout, "| %s", row[count]);
				if(row[count] != NULL)
				{
					for(int i = 0 ; i <=  abs(strlen(row[count]) - colunas[count]); i++)
					{ 
					printf(" ");
					}
					
					if( count == Extra)
						printf("|");		
				}
				else{
					for(int i = 0 ; i <= abs(strlen("(null)") - colunas[count]); i++)
					{ 
					printf(" ");
					}						
				}
			  count++;		  
			}
			printf("\n");		
		}  
		print_line(colunas, total_colunas);
	}

	mysql_free_result(res);
	return true;
}

int  print_line(int *colunas, int size_colun)
{
	static int count = 0;
	if (size_colun == 0)
	{
		printf("+");
		printf("\n");
		count = 0;
		return 1;
	}

	else
	{    
		printf("+");
		for(int i = 0 ; i < (colunas[count] + 2); i++)
		{ 
			printf("-");
		}
		
		count++; 
		return  print_line(colunas, size_colun - 1);			
	}
}

int  print_name(char name_colun[][8], int *colunas, int size_colun)
{

	static int count = 0;
	if (size_colun == 0)
	{
		printf("|");
		printf("\n");		
		count = 0;
		return 1;
	}

	else
	{    
		printf("| %s ", name_colun[count]);
		for(int i = 0 ; i < abs(strlen(name_colun[count]) - colunas[count]); i++)
		{ 
			printf(" ");
		} 
		
		count++; 
		return print_name(name_colun, colunas, size_colun - 1);		
	}
}

void cleanBuffer(void)
{
    char c;
    while ((c = getchar()) != '\n'  && c != EOF);
}

