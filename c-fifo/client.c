#include<stdio.h>

#include"db.c"
#include"client_packet.c"
#include"server_packet.c"
#include"file_operations.c"

char* server_fifo = "serverfifo";
char* client_fifo;
int main(int argc, char** argv)
{
    if(argc!=3)
    {
        printf("./client [request_id] [clientfifo]\n");
        return 1;
    }
    int request_id = (int) strtol(argv[1], (char **)NULL, 10);
    client_fifo = argv[2];

    create_fifo(client_fifo);

    int fd = file_open_write(server_fifo);
    client_p kp = create_client_packet(request_id,client_fifo);
    char* bs = client_packet_to_byte_stream(kp);
    int length = client_packet_byte_stream_length(kp);
    write(fd,bs,length);
    destroy_client_packet(kp);
    close(fd);

    char buff[1024];
    int fd2 = file_open_read(client_fifo);
    read(fd2,buff,4);
    int answer_length = *((int*)buff);
    read(fd2,buff+4,answer_length);
    close(fd2);

    server_p sp = byte_stream_to_server_packet(buff);
    printf("%s\n",sp->answer);
    destroy_server_packet(sp);
    delete_file(client_fifo);

    return 0;
}