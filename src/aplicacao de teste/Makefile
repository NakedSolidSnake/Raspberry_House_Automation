# aplicação
APPS = ./apps

# .h file
H_SCR = ./scr

# .c file
C_SCR = ./scr

# all lib Project
LIBS_PROJECT = ./libs

# .o file objetos
OBJ = ./obj

# executable and libs
BIN = ./bin

#compiler
CC = gcc

FLAGS = -O3 -Wall -fPIC -std=c99

# Testar a variável de ambiente ComSpec que diz se o interpretador de comandos do Windows está presente:
ifdef COMSPEC
# .h file dependence libmysql
H_DEPENDENCE = ./dependence/include
# .dll dependence libmysql
LIB_DEPENDENCE = ./dependence/lib
MYLIB = mylib.dll 
LIBS = -lmysql -lmylib -lm -L $(LIBS_PROJECT)  -L $(LIB_DEPENDENCE)
LIB_DINAMICA = -I $(H_SCR) -I $(H_DEPENDENCE) -L $(LIB_DEPENDENCE) -llibmysql
CP = cp $(LIB_DEPENDENCE)/*  $(BIN)/

else
# .h file dependence libmysql
H_DEPENDENCE = /usr/include/mysql
MYLIB = mylib.so
LIBS = -lmysqlclient -lmylib -lm -L $(LIBS_PROJECT)  
LIB_DINAMICA = -I $(H_SCR) -I $(H_DEPENDENCE) -lmysqlclient

endif



all: mylib  mylibDinamica app

mylib: \
	$(OBJ)/menu.o \
	$(OBJ)/mylib.o 
	ar -rcs $(LIBS_PROJECT)/libmylib.a $(OBJ)/*.o


mylibDinamica:
	$(CC) -shared $(FLAGS) -o $(LIBS_PROJECT)/mylib.dll -fPIC $(OBJ)/*.o  $(LIB_DINAMICA)
	cp ./config/*  $(BIN)/
	cp $(LIBS_PROJECT)/*  $(BIN)/
	$(CP)

app: $(BIN)/main 

# Compilar os objetos da mylib
$(OBJ)/%.o: $(C_SCR)/%.c 
	$(CC) $(FLAGS) -c $< -I $(H_DEPENDENCE) -o $@

# main.exe
$(BIN)/%: $(APPS)/%.c
	$(CC) $(FLAGS) $< -I $(H_SCR) -I $(H_DEPENDENCE) $(LIBS) -o $@


run:
	$(BIN)/main

clean:
	rm $(BIN)/* rm $(OBJ)/* rm $(LIBS_PROJECT)/*
	 