#include<stdio.h>

#include"db_service.h"
#include"klient_packet.h"
#include"server_packet.h"
#include"file_operations.h"

const char* server_fifo = "serverfifo";

int main()
{
    //-----------------------
    printf("db test:\n");

    db database = create_db();
    insert_test_data(database);

    const char* answer = get_by_id(database,4);
    printf("%s\n",answer);

    desroy_db(database);

    printf("\n");
    //-----------------------

    //-----------------------
    printf("klient packet serializing and deserializing test:\n");

    klient_p kp = create_klient_packet(5,"klientfifo");
    printf("%i, %i, %s\n",kp->home_length,kp->id,kp->home);

    char* bs1 = klient_packet_to_byte_stream(kp);
    int kli_bs_length = klient_packet_byte_stream_length(kp);
    printf("%i\n",kli_bs_length);
    for(int i=0;i<kli_bs_length;i++)
        printf("\\0x%2x", *(bs1+i));
    printf("\n");
    
    klient_p kp2 = byte_stream_to_klient_packet(bs1);
    printf("%i, %i, %s\n",kp2->home_length,kp2->id,kp2->home);

    free(bs1);
    destroy_klient_packet(kp);
    destroy_klient_packet(kp2);

    printf("\n");
    //-----------------------

    //-----------------------
    printf("server packet serializing and deserializing test:\n");

    server_p sp = create_server_packet("odpowiedz");
    printf("%i, %s\n",sp->answer_length,sp->answer);

    char* bs2 = server_packet_to_byte_stream(sp);
    int serv_bs_length = server_packet_byte_stream_length(sp);
    printf("%i\n",serv_bs_length);
    for(int i=0;i<serv_bs_length;i++)
        printf("%i ", *(bs2+i));
    printf("\n");
    
    server_p sp2 = byte_stream_to_server_packet(bs2);
    printf("%i, %s\n",sp2->answer_length,sp2->answer);

    free(bs2);
    destroy_server_packet(sp);
    destroy_server_packet(sp2);

    printf("\n");
    //-----------------------

    //-----------------------
    printf("fifo handling tests:\n");
    char* test_fifo = "test_fifo";

    printf("%s exists: %s\n",test_fifo,file_exists(test_fifo)?"true":"false");

    create_fifo(test_fifo);
    printf("%s exists: %s\n",test_fifo,file_exists(test_fifo)?"true":"false");

    delete_file(test_fifo);
    printf("%s exists: %s\n",test_fifo,file_exists(test_fifo)?"true":"false");
    //-----------------------
}