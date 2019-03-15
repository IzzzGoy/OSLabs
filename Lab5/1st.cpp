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
        int* mass = new int[mem];
        std::cout<<"#################################"<<std::endl;
        for(size_t i = 0; i < mem; i++)
        {
            mass[i] = rand()%1000;
            std::cout << mass[i] << std::endl;
        }
        write(fd[1],mass,sizeof(int)*mem);
        while(!read(dh[0],mass,sizeof(int)*mem));
        std::cout<<"#################################"<<std::endl;

        for(size_t i = 0; i < mem; i++)
        {
            std::cout << mass[i] << std::endl;
        }
        std::cout<<"#################################"<<std::endl;
        close(fd[0]);
        close(fd[1]);
        delete[] mass;
        return 0;


    }
    else
    {
        int* arr = new int;
        read(fd[0],arr, sizeof(int)*mem);
        for(int i = 1; i < mem; ++i)
        {
            for(int r = 0; r < mem-i; r++)
            {
                if(arr[r] < arr[r+1])
                {
                    int temp = arr[r];
                    arr[r] = arr[r+1];
                    arr[r+1] = temp;
                }
            }
        }
        write(dh[1],arr,sizeof(int)*mem);

        close(dh[0]);
        close(dh[1]);
        delete[] arr;
    }
    return 0;
}




