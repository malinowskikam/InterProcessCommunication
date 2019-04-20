#include"komunikat.h"

#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include <sys/types.h>
#include <unistd.h>


int main(int argc,char** argv)
{
    if(argc!=2)
    {
        printf("./klient [slowo]");
        return 1;
    }
    
    msg message;

    int pid = getpid();
    message.id= pid;
    strcpy(message.value,argv[1]);

    int q_queue = get_query_queue();
    send_msg(q_queue,&message);

    int a_queue = get_answer_queue();
    msg* message2 = read_msg(a_queue,pid);

    printf("%s\n",message2->value);
    free(message2);

    return 0;
}