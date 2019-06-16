#include<string.h>
#include<stdlib.h>

char* x_conn_sting(char* address, char* terminal_number, char* screen_number );

// domyślnie (ip,"0",NULL)
char* x_conn_sting(char* address, char* terminal_number, char* screen_number )
{
    char* res;

    if(screen_number==NULL)
    {
        int length = strlen(address) + strlen(terminal_number);
        res = (char*)malloc(sizeof(char)*length+2);
        res[0]=0;

        strcat(res,address);
        strcat(res,":");
        strcat(res,terminal_number);
    } else
    {
        int length = strlen(address) + strlen(terminal_number) + strlen(screen_number);
        res = (char*)malloc(sizeof(char)*length+3);
        res[0]=0;

        strcat(res,address);
        strcat(res,":");
        strcat(res,terminal_number);
        strcat(res,".");
        strcat(res,screen_number);
    }

    return res;
}