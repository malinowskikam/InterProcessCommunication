#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/stat.h>
#include<string.h>

int file_exists(char* filename)
{
    if(!access(filename, F_OK )){
        return 1;
    }else{
        return 0;
    }
}

int file_open_read(char* filename)
{
    int fd = open(filename,O_RDWR);

    if (fd==-1)
    {
        printf("Otwarcie pliku %s nie powiodło się",filename);
        exit(1);
    }
    return fd;
}

int file_open_write(char* filename)
{
    int fd = open(filename,O_CREAT|O_RDWR|O_TRUNC);

    if (fd==-1)
    {
        printf("Otwarcie pliku %s nie powiodło się",filename);
        exit(1);
    }
    return fd;
}

void create_fifo(char* filename)
{
    mkfifo(filename,0666);
}

void delete_file(char* filename)
{
    remove(filename);
}