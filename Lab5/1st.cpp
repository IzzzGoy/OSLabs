#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <sys/ipc.h>
#include <wait.h>
#include <sys/shm.h>
#include <ctime>

int main(int argv, char* argc[])
{
    srand(time(NULL));
    char* temp = argc[1];
    int mem = atoi(temp);
    int fd[2];
    int dh[2];
    pipe(fd);
    pipe(dh);
    pid_t i = fork();
    if(i)
    {
        if(mem == 0)
        {
            std::cout<<"All is bad!"<< std::endl;
            return -1;
        }
        int memID = shmget(IPC_PRIVATE,sizeof(int)*mem, 0600|IPC_CREAT|IPC_EXCL);
        if(memID <= 0)
        {
            std::cout<<"Memory not gotcha!" <<std::endl;
            return -1;
        }
        int* mass = (int*)shmat(memID,0,0);
        if(mass == NULL)
        {
            std::cout<<"Bad mass!"<<std::endl;
        }
        std::cout<<"#################################"<<std::endl;
        for(size_t i = 0; i < mem; i++)
        {
            mass[i] = rand()%1000;
            std::cout << mass[i] << std::endl;
        }
        write(fd[1],&memID,sizeof(int));
        int trigger = 0;
        while(!read(dh[0],&trigger,sizeof(int)));
        {
            if(trigger == 1)
            {

                std::cout<<"#################################"<<std::endl;

                for(size_t i = 0; i < mem; i++)
                {
                    std::cout << mass[i] << std::endl;
                }
                std::cout<<"#################################"<<std::endl;
                close(fd[0]);
                close(fd[1]);
                shmctl(memID, IPC_RMID, 0);

                return 0;
            }

        }
    }
    else
    {
        int I;
        read(fd[0],&I, 4);
        int* arr = (int*)shmat(I,0,0);
       

        for(size_t j = 0; j < mem; j++)
        {

           
            for(size_t i = 0; i < mem - 1; i++)
            {
              
                if(arr[i] < arr[i+1])
                {
                    int a = arr[i];
                    arr[i] = arr[i+1];
                    arr[i + 1] = a;
                }

            }
        }
        int tmp = 1;
        write(dh[1],&tmp,sizeof(int));
        close(dh[0]);
        close(dh[1]);
    }
    return 0;
}



