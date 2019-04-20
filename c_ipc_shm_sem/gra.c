#include"plansza.h"
#include<sys/shm.h>
#include<sys/sem.h>
#include<stdio.h>

int main()
{
    int key = 9591;

    int shared_memory;
    int shared_semaphores;

    char player;
    char* map;

    shared_memory = shmget(key,9,0777|IPC_CREAT);
    if(shared_memory==-1)
    {
        printf("Pobranie pamięci nie powiodło się...\n");
        return -1;  
    }
    map = shmat(shared_memory,0,0);

    struct sembuf 
        turn_sem_open = {0,-1,0},
        turn_sem_close = {0,1,0},
        turn_sem_wait = {0,0,0};

    struct sembuf wait_for_turn[2];
    wait_for_turn[0]=turn_sem_wait;
    wait_for_turn[1]=turn_sem_close;

    shared_semaphores = semget(key,1,0777|IPC_CREAT|IPC_EXCL); // IPC_EXCL - jeśli tablica już utworzona to fail
    if(shared_semaphores != -1)
    { // gracz pierwszy
        create_map(map);
        player = 'x';
    } else
    { //gracz drugi
        player = 'o';
        shared_semaphores = semget(key,1,0777);
    }
    int input=0;
    while(input>=0)
    {
        system("clear");
        printf("Poczekaj na swój ruch...\n");
        semop(shared_semaphores,wait_for_turn,2);

        switch(check_map(map))
        {
            case -1 :
                system("clear");
                printf("Remis\n");
                semop(shared_semaphores,&turn_sem_open,1);
                input=-1;
                break;
            case 1 :
                system("clear");
                printf("Wygrał x\n");
                semop(shared_semaphores,&turn_sem_open,1);
                input=-1;
                break;
            case 2 :
                system("clear");
                printf("Wygrał o\n");
                semop(shared_semaphores,&turn_sem_open,1);
                input=-1;
                break;
            case 0 :
                printf("Gracz: %c\n", player);
                printf("Plansza:\n");
                print_map(map);
                
                printf("Twój ruch: ");
                scanf("%i",&input);
                while(input<0||input>8||!is_free(map,input))
                {
                    printf("To pole jest nieprawidłowe, wybierz inne: ");
                    scanf("%i",&input);
                }

                map[input] = player;

                printf("\n");

                semop(shared_semaphores,&turn_sem_open,1);
                break;
            default:
                printf("Błąd\n");
                return -1;
        }   
    }

    shmdt(map);
    semctl(shared_semaphores,0,IPC_RMID,0);
    shmctl(shared_memory,IPC_RMID,0);
}