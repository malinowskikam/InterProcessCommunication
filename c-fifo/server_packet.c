#include<string.h>
#include<stdlib.h>

typedef struct server_packet {
    int answer_length;
    char* answer;
}* server_p;

server_p create_server_packet(char* answer)
{
    int answer_length = strlen(answer);

    server_p sp = (server_p)malloc(sizeof(struct server_packet));

    sp->answer_length = answer_length;
    sp->answer = (char*)malloc(sizeof(char)*(answer_length+1));
    strcpy(sp->answer,answer);

    return sp;
}

void destroy_server_packet(server_p sp)
{
    free(sp->answer);
    free(sp);
}

int server_packet_byte_stream_length(server_p sp)
{
    return 4 + sp->answer_length;
}

char* server_packet_to_byte_stream(server_p sp)
{
    int bs_length = server_packet_byte_stream_length(sp);

    char* byte_stream = (char*)malloc(sizeof(char)*bs_length);

    int* int_p = (int*)byte_stream;
    *int_p = sp->answer_length;

    for(int i=0;i<sp->answer_length;i++)
    {
        *(byte_stream+4+i) = *(sp->answer+i);
    }

    return byte_stream;
}

server_p byte_stream_to_server_packet(char* bs)
{
    int answer_length = *((int*)bs);
    char* answer = (char*)malloc(sizeof(char)*(answer_length+1));

    for(int i=0;i<answer_length;i++)
    {
        *(answer+i) = *(bs+4+i);
    }

    *(answer+answer_length) = 0;

    server_p sp = create_server_packet(answer);
    free(answer);

    return sp;
}