#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>


#define QUE_LENGTH 6
#define QUE_WAIT_INTERVAL 4

void getPIN(char pin[QUE_LENGTH + 1]){
        srand(getpid() + getppid());

                pin[0] = 51 + rand() % 8;

                for(int i = 1; i< QUE_LENGTH; i++){
                                pin[i] = 50 + rand() % 7;

                }

               pin[QUE_LENGTH] = '\0';
                  }

int main(void){
        while(1){

                        int pipefds[2];
               char pin[QUE_LENGTH +1];
                        char buffer[QUE_LENGTH +1];
               void sigint_handler(int sig);
               char s[300];
               char name[300];

                        if(signal(SIGINT,sigint_handler)==SIG_ERR){
                        perror("signal");

                        exit(1);
               }


               pipe(pipefds);

                        pid_t pid = fork();

                        if(pid == 0){
                        getPIN(pin);
                        close(pipefds[0]);
                        write(pipefds[1], pin, QUE_LENGTH + 1);

                        printf("Processing order number... \n");
                        printf("Your customer's name: ");
                        fgets(name, 300, stdin);
                        printf("Order number for %s>",name);


                        sleep(QUE_WAIT_INTERVAL);

                        exit(EXIT_SUCCESS);


                }

                if(pid > 0){
                                wait(NULL);




                                close(pipefds[1]);
                                read(pipefds[0], buffer, QUE_LENGTH + 1);
                                close(pipefds[0]);

                                printf("%s\n\n", buffer);

                        }
                }
                return 0;
          return EXIT_SUCCESS;
}

 void sigint_handler(int sig){
         printf("\nNETWORK DISTRUPTION\n");
}


