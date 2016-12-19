// tysh_builtins.h

int tysh_num_builtins();
char *tysh_builtin_name(int);
int tysh_execute_builtin(int, char**);
