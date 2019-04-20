#include<stdio.h>

#include"db_service.h"
#include"klient_packet.h"
#include"server_packet.h"
#include"file_operations.h"

char* server_fifo = "serverfifo";
char* klient_fifo;
int main(int argc, char** argv)
{
    if(argc!=3)
    {
        printf("./klient [request_id] [klientfifo]\n");
        return 1;
    }
    int request_id = (int) strtol(argv[1], (char **)NULL, 10);
    klient_fifo = argv[2];

    create_fifo(klient_fifo);

    int fd = file_open_write(server_fifo);
    klient_p kp = create_klient_packet(request_id,klient_fifo);
    char* bs = klient_packet_to_byte_stream(kp);
    int length = klient_packet_byte_stream_length(kp);
    write(fd,bs,length);
    destroy_klient_packet(kp);
    close(fd);

    char buff[1024];
    int fd2 = file_open_read(klient_fifo);
    read(fd2,buff,4);
    int answer_length = *((int*)buff);
    read(fd2,buff+4,answer_length);
    close(fd2);

    server_p sp = byte_stream_to_server_packet(buff);
    printf("%s\n",sp->answer);
    destroy_server_packet(sp);
    delete_file(klient_fifo);

    return 0;
}