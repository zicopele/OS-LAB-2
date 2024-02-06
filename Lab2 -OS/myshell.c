/*Fernando Chan Qui 100844946
  Hamzi Farhat      100831450*/
  
#include "myshell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stddef.h>
#include <unistd.h>

int main() {

    char input[1024];
    char* s;

    //Fetch the path of the shell executable
    char shellPath[1024];
    if ((s = getenv("_")) != NULL) {
        strcpy(shellPath, s);
        setenv("shell", shellPath, 1);
    }
    //Check if the input is coming from the terminal or a file
    if (isatty(fileno(stdin))) {
        //Takes input from the user
        while (1) {
            
            printCurrentDirectory();
            fgets(input, sizeof(input), stdin);
            input[strcspn(input, "\n")] = '\0';

            char* command = strtok(input, " ");
            char* argument = strtok(NULL, " ");

                if (strcmp(command, "cd") == 0) {
                    cdCommand(argument);
                } else if (strcmp(command, "clr") == 0) {
                    clrCommand();
                } else if (strcmp(command, "dir") == 0) {
                    dirCommand(argument);
                } else if (strcmp(command, "environ") == 0) {
                    environCommand();
                } else if (strcmp(command, "echo") == 0) {
                    echoCommand(argument);
                } else if (strcmp(command, "help") == 0) {
                    helpCommand();
                } else if (strcmp(command, "pause") == 0) {
                    printf("Press Enter to continue...");
                    getchar();
                } else if (strcmp(command, "quit") == 0) {
                    break;
                } else {
                // External program invocation
                executeExternalProgram(command, argument);
                }  
        }
    } 
    //Input is not coming from the terminal it will enter Batch mode and will read commands from the file
    else {
        while (fgets(input, sizeof(input), stdin) != NULL) {
            input[strcspn(input, "\n")] = '\0';
            printf("Executing command from file: %s\n", input);

            char* command = strtok(input, " ");
            char* argument = strtok(NULL, " ");

           if (strcmp(command, "cd") == 0) {
                    cdCommand(argument);
                } else if (strcmp(command, "clr") == 0) {
                    clrCommand();
                } else if (strcmp(command, "dir") == 0) {
                    dirCommand(argument);
                } else if (strcmp(command, "environ") == 0) {
                    environCommand();
                } else if (strcmp(command, "echo") == 0) {
                    echoCommand(argument);
                } else if (strcmp(command, "help") == 0) {
                    helpCommand();
                } else if (strcmp(command, "pause") == 0) {
                    printf("Press Enter to continue...");
                    getchar();
                } else if (strcmp(command, "quit") == 0) {
                    break;
                } else {
                // External program invocation
                executeExternalProgram(command, argument);
                }  
        }
        return 0;
    }
    
}
