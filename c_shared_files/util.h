#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>

int get_esc_position(char* text)
{
    int esc_pos = -1;
    int length = strlen(text);

    for(int i=0;i<length;i++) 
        if(text[i]==27)
            esc_pos = i;

    return esc_pos;
}

void lock_server()
{
    while (open("serverlock",O_CREAT|O_EXCL,0)==-1) {
        printf("Serwer zajety, prosze czekac\n");
        sleep(2);
    }
}

void wait_for_client()
{
    file_d desc;
    while (desc = open("dane",O_RDONLY)==-1)
    {
        sleep(2);
    }
    close(desc);

}