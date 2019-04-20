#include<stdio.h>

#include"db_service.h"
#include"klient_packet.h"
#include"server_packet.h"
#include"file_operations.h"

char* server_fifo = "serverfifo";

int main()
{
    if(file_exists(server_fifo))
        delete_file(server_fifo);

    create_fifo(server_fifo);

    db database = create_db();
    insert_test_data(database);

    char buff[1024];

    while(1)
    {
        int server_fifo_fd = file_open_read(server_fifo);

        read(server_fifo_fd,buff,4);
        int home_length = *((int*)buff);
        read(server_fifo_fd,buff+4,4+home_length);
        close(server_fifo_fd);

        klient_p kp = byte_stream_to_klient_packet(buff);

        if(!file_exists(kp->home))
        {
            printf("Klient's fifo not exists!");
        }
        else
        {
            int klient_fifo_fd = file_open_write(kp->home);

            char* db_answer = get_by_id(database,kp->id);
            server_p sp = create_server_packet(db_answer);
            int sp_length = server_packet_byte_stream_length(sp);
            char* bs = server_packet_to_byte_stream(sp);

            write(klient_fifo_fd,bs,sp_length);
            close(klient_fifo_fd);

            destroy_server_packet(sp);
        }
        destroy_klient_packet(kp);
    }

    desroy_db(database);
}