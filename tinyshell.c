#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"tysh_builtins.h"
#define TYSH_BUF_SIZE 32
char *tysh_read(){
    char *line = NULL;
    size_t bufsize = 0;
    getline(&line, &bufsize, stdin);
    return line;
}
char **tysh_parse(char *line){
    int position = 0;
    char *token;
    char **tokens = malloc(TYSH_BUF_SIZE * sizeof(char*));
    if(!tokens){
        fprintf(stderr, "tysh: Failed to allocate memory.");
        exit(-1);
    }
    token = strtok(line, " \t\r\n\a");
    while(token != NULL){
        tokens[position] = token;
        position++;
        token = strtok(NULL, " \t\r\n\a");
    }
    tokens[position] = NULL;
    return tokens;
}
int tysh_launch(char **args){
    pid_t pid, wpid;
    int status;
    pid = fork();
    if(pid == 0){   // child process
        if(execvp(args[0], args) == -1)
            perror("tysh");
        exit(0);
    } else if(pid < 0){
        perror("tysh");
    } else {    // parent process
        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while(!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    return 1;
}
int tysh_execute(char **args){
    int i;
    if (args[0] == NULL)
        return 1;
    for (i=0; i<tysh_num_builtins(); i++){
        if (strcmp(args[0], tysh_builtin_name(i)) == 0){
            return tysh_execute_builtin(i, args);
        }
    }
    return tysh_launch(args);
}
void tysh_main(){
    char *line;
    char **args;
    int status;
    do{
        printf("> ");
        line = tysh_read();
        args = tysh_parse(line);
        status = tysh_execute(args);
        free(line);
        free(args);
    } while(status);
    return;
}
int main(int argc, char *argv[]){
    //puts("This is tysh, a tiny shell written in C!");
    tysh_main();
    return 0;
}
