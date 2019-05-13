#include<string.h>
#include<stdlib.h>

typedef struct client_packet {
    int home_length;
    int id;
    char* home;
}* client_p;

client_p create_client_packet(int id,char* home)
{
    int home_length = strlen(home);

    client_p cp = (client_p)malloc(sizeof(struct client_packet));

    cp->id=id;
    cp->home_length=home_length;
    cp->home = (char*)malloc(sizeof(char)*(home_length+1));
    strcpy(cp->home,home);

    return cp;
}

void destroy_klient_packet(client_p cp)
{
    free(cp->home);
    free(cp);
}

int client_packet_byte_stream_length(client_p cp)
{
    return 8 + cp->home_length;
}

char* client_packet_to_byte_stream(client_p cp)
{
    int bs_length = client_packet_byte_stream_length(cp);

    char* byte_stream = (char*)malloc(sizeof(char)*bs_length);

    int* int_p = (int*)byte_stream;
    *int_p = cp->home_length;
    *(int_p+1) = cp->id;

    for(int i=0;i<cp->home_length;i++)
    {
        *(byte_stream+8+i) = *(cp->home+i);
    }

    return byte_stream;
}

client_p byte_stream_to_client_packet(char* bs)
{
    int home_length = *((int*)bs);
    int id = *((int*)(bs+4));
    char* home = (char*)malloc(sizeof(char)*(home_length+1));

    for(int i=0;i<home_length;i++)
    {
        *(home+i) = *(bs+8+i);
    }

    *(home+home_length) = 0;

    client_p cp = create_client_packet(id,home);
    free(home);

    return cp;
}