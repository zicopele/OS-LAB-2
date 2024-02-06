/*Fernando Chan Qui 100844946
  Hamzi Farhat      100831450*/
  
#include "myshell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

//Function to print current directory
void printCurrentDirectory() {
    char cwd[1024];
    printf("myshell: %s > ", getcwd(cwd, 1024));
}

//Function to change current directory to another one needs an argument to function
void cdCommand(char* directory) {
    if (directory == NULL) {
        // If there is no argument, it will print the current directory
        printCurrentDirectory();
    } else {
        // Change directory otherwise handle error if unsuccessful
        if (chdir(directory) != 0) {
            perror("chdir");
        }
    }
}

//Function to clean the command prompt
void clrCommand() {
    system("clear");
}

// Function to list all the contents in a directory 
void dirCommand(char* directory) {
    if (directory == NULL) {
        //Show an error message if there is no directory specified
        printf("dir: missing argument\n");
    } else {
        // Execute 'ls' command on the specified directory
        char command[1024];
        snprintf(command, sizeof(command), "ls %s", directory);
        system(command);
    }
}
//Function to display the environment variables
void environCommand() {
    extern char** environ;
    // Iterate through environment variables and print each one
    for (int i = 0; environ[i] != NULL; i++) {
        printf("%s\n", environ[i]);
    }
}

//Function to print a comment to the command prompt 
void echoCommand(char* comment) {
    printf("%s\n", comment);
}

//Function to display the readme file 
void helpCommand() {
    system("more readme");
}

//Function to invoke an external program 
void executeExternalProgram(char* command, char* argument) {
    pid_t child_pid = fork();

    if (child_pid == -1) {
        perror("fork");

    } else if (child_pid == 0) {
        // Child process
        char parent_env[1024];
        snprintf(parent_env, sizeof(parent_env), "parent=%s", getenv("shell"));
        setenv("parent", parent_env, 1);

        // Execute the external program
        execlp(command, command, argument, NULL);

        // If execlp fails
        perror("execlp");
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        int status;
        waitpid(child_pid, &status, 0);
    }
}
