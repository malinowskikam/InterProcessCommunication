#include <stdlib.h>
#include <sys/msg.h>
#include <sys/ipc.h>

const int message_len = 256;

const int query_queue_id = 1111;
const int answer_queue_id = 1112;

typedef struct message
{
    long id;
    char value[256];
} msg;

int get_query_queue()
{
    return msgget(query_queue_id,0777|IPC_CREAT);
}

int get_answer_queue()
{
    return msgget(answer_queue_id,0777|IPC_CREAT);
}

msg* read_msg(int id,long message_id)
{
    msg* message = (msg*)malloc(sizeof(struct message));
    msgrcv(id,message,message_len,message_id,0);
    return message;  
}

void send_msg(int id, msg* message)
{
    msgsnd(id,message,message_len,0);
}



