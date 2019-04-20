#include<stdlib.h>
#include<stdio.h>

void create_map(char* map) // tworzy pustą mapę
{
    for(int i=0;i<9;i++)
        map[i]=' ';
}


void print_map(char* map) //wypisuje mapę
{
    printf("%c|%c|%c\n",map[0],map[1],map[2]);
    printf("-+-+-\n");
    printf("%c|%c|%c\n",map[3],map[4],map[5]);
    printf("-+-+-\n");
    printf("%c|%c|%c\n",map[6],map[7],map[8]);
}

int is_free(char* map, int field)
{
    return map[field]==' ';
}

int check_map(char* map) //sprawdza, czy ktoś wygrał
/*
*   -1 - remis
*    0 - nikt
*    1 - x
*    0 - o
*/
{
    int xflags = 0;
    int oflags = 0;

    
    
    for(int i=0;i<9;i++)
    {
        if(map[i]=='x')
            xflags = xflags | 1<<i;

        if(map[i]=='o')
            oflags = oflags | 1<<i;
    }

    /*
    * int first_row=7;
    * int second_row=56;
    * int third_row=448;
    * int first_column=73;
    * int second_column=146;
    * int third_row=292;
    * int diagonal=273;w
    * int antidiagonal=84;
    */

    int win_flags[] = {7,56,448,73,146,292,273,84};

    for(int i=0;i<8;i++)
    {
        if((xflags & win_flags[i]) == win_flags[i])
            return 1;
        if((oflags & win_flags[i]) == win_flags[i])
            return 2;
        
    }

    if((xflags | oflags) == 511)
        return -1;

    return 0;
}
