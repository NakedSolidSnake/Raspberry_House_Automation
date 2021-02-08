#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "menu.h"
#include "mylib.h"

int main(int argc, char **argv)
{			
    int ret; 
    do
    {
        ret = menu();       
    }while(ret != true); 

	return 0; 
}

