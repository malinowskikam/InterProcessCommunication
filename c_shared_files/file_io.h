#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>

int write_line(file_d fd,char* text)
{
    write(fd,text,strlen(text));
    //write(fd,"\n",1);
}

int read_byte(file_d fd)
{
    static char buff[2];
    
    int status = read(fd,buff,1);

    if(status == 1)
    {
        return (int)buff[0];
    }
    else
    {
        if(status==0)
            return -1; //EOF
        else
            return -2; //Błąd
    }
}