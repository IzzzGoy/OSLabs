#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>

int main()
{
    int iD = shmget(IPC_PRIVATE,sizeof(int)*20,0600|IPC_CREAT|IPC_EXCL);
    if(iD <= 0)
    {
        printf("error with shmget()\n");
        return -1;
    }
    int* arrey = (int *)shmat(iD,0,0);
    if (NULL == arrey)
	{
		printf("error with shmat()\n");
		return -2;
	}
    for(size_t i = 0; i < 20; i++)
    {
        arrey[i] = rand()%1000;
    }
     
    char buff[1024];
    sprintf(buff,"./next %i", iD);
    system(buff);
    return 0;
}
