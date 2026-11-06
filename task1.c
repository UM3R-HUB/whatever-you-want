#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
//create a process
pid_t pid = fork();

if (pid<0){
//fork returns neg if fail
perror("Fork failed");
exit(EXIT_FAILURE);
}

else if (pid==0){
//fork returns 0 to child
printf("Chilld Process: Executing %s...\n\n", argv[1]);

char *path = argv[1];
//argv array must be NULL -terminated
//first arg is name of first prog
//more. arguments addable before NULL
char *commands[10];
for (int i = 1; i < argc; i++){
commands[i-1] = argv[i];
}
commands[argc-1] = NULL;
//execv replaces current cp with new p
pid_t cpid = fork();
if (cpid < 0) { perror("Fork failed"); exit(EXIT_FAILURE); }
  else if (cpid == 0){
  printf("Chilld's child Process: Executing %s...\n\n", argv[1]);

  char *path1 = argv[1];
  //argv array must be NULL -terminated
  //first arg is name of first prog
  //more. arguments addable before NULL
  char *commands1[10];
  for (int i = 1; i < argc; i++)
  {
  commands1[i-1] = argv[i];
  }
  execv(path1, commands1);
  //should execv return, error has occured
  perror("execv failed");
  exit(EXIT_FAILURE);
  }
  else {
  int status;waitpid(cpid, &status, 0);
  printf("\nParent Process: Child (PID %d) has finished executing.\n", pid);
  }
}

else {
//fork() return cpid to pp
int status;
//parent wait for cp to complete
waitpid(pid, &status, 0);
 printf("\nParent Process: Child (PID %d) has finished executing.\n", pid);
}

return 0;

}
