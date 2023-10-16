#ifndef SHELL_H
#define SHELL_H

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int ac, char **av, char **env);
void prompt(void);
void handle(int signals);
void _EOF(char *buffer);
void shell_exit(char **command);

int _strcmp(char *s1, char *s2);
unsigned int _strlen(char *s);
char *_strcpy(char *dest, char *src);
int _atoi(char *s);
char *_strcat(char *dest, char *src);
void create_child_process(char **command, char *name, char **env, int rounds);
int change_dir(const char *path);
void exe(char **command, char *name, char **env, int rounds);
void print_env(char **env);
char **_getpth(char **env);
void msg_error(char *name, char **command, int rounds);
char **tokenize(char *buffer, const char *s);
void mem_free(char **command);
void mem_free_exit(char **command);

#endif
