#include"slownik.h"
#include"komunikat.h"

#include<stdio.h>
#include<stdlib.h>

int main()
{
    int q_queue = get_query_queue();
    int a_queue = get_answer_queue();

    while(1)
    {
        msg* message = read_msg(q_queue,0);

        printf("%ld, %s\n",message->id,message->value);

        strcpy(message->value,translate(message->value));

        send_msg(a_queue,message);

        free(message);
    }

    return 0;
}