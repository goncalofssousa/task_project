#ifndef TASKS_H
#define TASKS_H
#include<stdlib.h>


typedef enum{
    UNDONE = 1, 
    DONE = 2,
} State; 


typedef struct tarefa {
    int id;
    char title[51];
    char str[101];
    char prioridadeStr[10];
    State taskState; 
    int prioridade; 
} *Tarefa;

typedef struct array{
    Tarefa *tarefas; 
    int size; 
    int capacity; 
} Lista;



void newTask(Lista *array, char *prioridadeStr, int prioridade, char *title, char *descr, int state); 
void handleNewTask(Lista *array);
void showTasks(Lista *array);
void handleCommand(char *command, Lista *array);
void readCommand(Lista *array); 

#endif
