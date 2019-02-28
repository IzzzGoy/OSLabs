#include <stdio.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctime>

#include <sys/types.h>
#include <sys/wait.h>

void SetRandom(int arreyID)
{
    srand(time(NULL));
    int* arrey = (int*)shmat(arreyID,0,0);
    for(size_t i = 0; i < 20 ; i++ )
    {
        arrey[i] = rand() % 1000;
    }
    for(size_t i = 0; i < 20;i++)
    {
        printf("%i ",arrey[i]);
    }
    printf("\n");
    return;
}

void SortNumb(int arreyID)
{
    int* arrey = (int*)shmat(arreyID,0,0);

    for(size_t j = 0; j < 20; j++)
    {
        for(size_t i = 0; i < 19; i++)
        {
            if(arrey[i] > arrey[i+1])
            {
                int a = arrey[i];
                arrey[i] = arrey[i+1];
                arrey[i + 1] = a;
            }

        }
    }

    for(size_t i = 0; i < 20; i++)
    {
        printf("%d",arrey[i]);
        printf(" ");
    }
    printf("\n");

    return;

}

int main()
{

    int IDm = shmget(IPC_PRIVATE,20*sizeof(int),0600|IPC_CREAT|IPC_EXCL);

    if(IDm<0)
    {
        printf("Bad shmget!");
        return -1;
    }
    pid_t childId = fork();
    //now both processes have common pointer for shared memory. And also each of them has copy individual memory buffer.
    if (childId < 0)
    {
        perror("error with fork()\n");
    }
    else if (childId > 0)
    {
        SetRandom(IDm);
        waitpid(childId, NULL, 0);
    }
    else
    {
        SortNumb(IDm);
    }
 
    return 0;
}
