#include <stdlib.h> //for atoi()
#include <unistd.h> //for pipe
#include <wait.h> //for wait()
#include <string.h> //for strcpy()
#define SIZE 10 //pipe buffer size
#include <stdio.h>

int main() {
    int pfd[2];
    //storing (pipe) file descriptor
    //returned from pipe()
    int nread;
    int pid; //pid_t is actually an int
    char buf[SIZE];
    char inbuf[SIZE*2];
    pipe(pfd); //q1.1
    //if (pipe(pfd) == -1)
    //{perror("pipe failed\n"); exit(-1);}
    printf("write pipe id = %d " , pfd[1]);
    printf(" read file id = %d\n", pfd[0]);

    pid = fork(); //q1.2
    if (pid == 0) { //child
        close( pfd[1]/* q1.3 */ ); //tidy unused end
        //read until end of stream
        while ((nread = read(pfd[0], buf/* q1.4 */, SIZE)) != 0)
            if (nread > 11)
                printf("avoid overflow no conversion %s.\n",buf);
            else printf("child received %s. + 5 = %d\n",
                        buf,atoi(buf)+5);
            close( pfd[0]/* q1.5 */ ); //properly close unused resource
    } else {
        close( pfd[0]/* q1.6 */ ); //tidy unused end
        
        //strcpy(inbuf,"1200"); //equiv "1200\0"
        sprintf(inbuf,"%ld",123456789012); //no worry on \0

        write( pfd[1], inbuf, strlen(inbuf) + 1/* q1.7 */ ); // sending 12 digit string
        //+1 for padding end of string character (\0)

        close( pfd[1]/* q1.8 */ ); wait(NULL);
        //close and wait for child to complete
    }
    return 0;
} //main Lab8b_q1.c
