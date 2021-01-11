## Dependência do Projeto:

1. C API (libmysqlclient) is a client library for C development
[link](https://dev.mysql.com/downloads/c-api/)

2. Estrutura do Diretório:
    >**/include**

    > **libmysql.dll**

    > **main.c**

    > **Makefile**

3. Build:
    >**gcc -I./include main.c  -L. -llibmysql**

