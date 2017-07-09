#include<stdio.h>
#include<unistd.h>
#include"tysh_builtins.h"
char *builtin_str[] = {
    "cd",
    "help",
    "exit"
};
int tysh_cd(char **args){
    char *dir;
    if(args[1] == NULL) {
        fprintf(stderr, "tysh: Expected arguement.\n");
        return 1;
        /*char tmp[8] = "~";
        dir = tmp;*/
    }
    else 
        dir = args[1];
    if(chdir(dir) != 0) {
        perror("tysh");
    }
    return 1;
}
int tysh_help(char **args){
    int i;
    printf("tysh: a tiny shell written in C.\n");
    printf("this program is based on Stephen Brennan's LSH.\n");
    printf("Copyright 2016, qujiru\n");
    printf("\nbuiltin functions:\n");
    for(i=0;i<tysh_num_builtins();i++)
        printf("%s\n", builtin_str[i]);
    return 1;
}
int tysh_exit(char **args){
    printf("bye!\n");
    return 0;
}
int (*builtin_func[])(char**) = {
    &tysh_cd,
    &tysh_help,
    &tysh_exit
};
int tysh_num_builtins(){
    return sizeof(builtin_str) / sizeof(char*);
}
char *tysh_builtin_name(int num){
    return builtin_str[num];
}
int tysh_execute_builtin(int i, char **args){
    return (*builtin_func[i])(args);
}
