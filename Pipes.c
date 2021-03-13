#include<stdio.h>
#include<unistd.h>

int main() {
   int pipe_fd_s[5];
   int returnstatus;
   int i;
   int pid;
   char writemessages[5][20]={"Hi", "I'm Mounvi", "This is lab cat", "Ohh, Alright!", "Moodle Upload"};
   char readmessage[20];
   returnstatus = pipe(pipe_fd_s);
   if (returnstatus == -1) {
      printf("Unable to create pipe\n");
      return 1;
   }
   pid = fork();
   for(i=0;i<5;i++)
   {
   if (pid == 0)
    {
      read(pipe_fd_s[0], readmessage, sizeof(readmessage));
      printf("Process1 – Message %d is %s\n", i + 1, readmessage);
   }
    else
    { 
      printf("Process2 - Message %d is %s\n", i + 1, writemessages[i]);
      write(pipe_fd_s[1], writemessages[i], sizeof(writemessages[i]));
   }
}
   return 0;
}
