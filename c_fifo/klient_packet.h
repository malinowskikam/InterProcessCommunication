#include"string.h"
#include"stdlib.h"

typedef struct klient_packet {
    int home_length;
    int id;
    char* home;
}* klient_p;

klient_p create_klient_packet(int id,char* home)
{
    int home_length = strlen(home);

    klient_p kp = (klient_p)malloc(sizeof(struct klient_packet));

    kp->id=id;
    kp->home_length=home_length;
    kp->home = (char*)malloc(sizeof(char)*(home_length+1));
    strcpy(kp->home,home);

    return kp;
}

void destroy_klient_packet(klient_p kp)
{
    free(kp->home);
    free(kp);
}

int klient_packet_byte_stream_length(klient_p kp)
{
    return 8 + kp->home_length;
}

char* klient_packet_to_byte_stream(klient_p kp)
{
    int bs_length = klient_packet_byte_stream_length(kp);

    char* byte_stream = (char*)malloc(sizeof(char)*bs_length);

    int* int_p = (int*)byte_stream;
    *int_p = kp->home_length;
    *(int_p+1) = kp->id;

    for(int i=0;i<kp->home_length;i++)
    {
        *(byte_stream+8+i) = *(kp->home+i);
    }

    return byte_stream;
}

klient_p byte_stream_to_klient_packet(char* bs)
{
    int home_length = *((int*)bs);
    int id = *((int*)(bs+4));
    char* home = (char*)malloc(sizeof(char)*(home_length+1));

    for(int i=0;i<home_length;i++)
    {
        *(home+i) = *(bs+8+i);
    }

    *(home+home_length) = 0;

    klient_p kp = create_klient_packet(id,home);
    free(home);

    return kp;
}