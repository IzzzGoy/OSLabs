#include <stdio.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
void *print_message_function1(void *ptr)
{
    int retval = 4;
    char *message = (char *) ptr;
    for(int i = 0;i<=10;i++)
    {
        printf("%s%i)\n", message,i);
        sleep(1);
    }
    return (void *)(++retval);
}
void *print_message_function2(void *ptr)
{

    int reval = 4;
    char *message = (char *) ptr;
    for(int i = 0;i<=12;i++)
    {
        printf("%s %i\n", message,i);
        sleep(2);
    }
    return (void *)(++reval);
}

int main()
{
    pthread_t thread1, thread2;
    const char *message1 = "Hello Threads (";
    const char *message2 = "This is iteration ";
    int res1 = pthread_create(&thread1, NULL, print_message_function1, (void*) message1);
    int res2 = pthread_create(&thread2, NULL, print_message_function2, (void*) message2);
    int iret1 = 0;
    int iret2;
    pthread_join(thread1, (void **)&iret1);
    pthread_join(thread2, (void **)&iret2);

    return 0;
}
