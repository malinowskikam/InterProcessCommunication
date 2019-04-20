int main()
{
    semctl(shared_semaphores,0,IPC_RMID,0);
    shmctl(shared_memory,IPC_RMID,0);
}