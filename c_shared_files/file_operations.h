#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>

typedef int file_d;

file_d open_for_write(char* file)
{
    file_d data = open(file,O_CREAT|O_RDWR|O_TRUNC);

    if(data==-1)
    {
        puts("Otwieranie pliku nie powiodło się");
        return -1;
    }
    else
    {
        return data;
    }
}

file_d open_for_read(char* file)
{
    file_d results = open(file,O_RDWR);

    if(results==-1)
    {
        puts("Otwieranie danych nie powiodło się");
        return -1;
    }
    else
    {
        return results;
    }
}

void clear_file(char* file)
{
    file_d fd = open(file,O_TRUNC);
    close(fd);
}