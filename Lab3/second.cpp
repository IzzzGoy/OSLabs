#include <stdio.h>
#include <sys/shm.h>
#include <stdlib.h>
int main(int argv, char *argc[])
{
    if (argv <= 1)
    {
        printf("not enough params\n");
        return -1;
    }
    char* params = argc[1];
    int ID = atoi(params);
    if (ID == 0)
    {
        printf("incorrect parameter string: %s\n", params);
        return -2;
    }
    int* arrey = (int*)shmat(ID,0,0);
    for(size_t i = 0; i < 20; i++)
    {
        printf("%d",arrey[i]);
        printf(" ");
    }
    printf("\n");
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
    char buff[100];
    sprintf(buff,"ipcrm -m %i",ID);
    system(buff);
    return 0;
}
