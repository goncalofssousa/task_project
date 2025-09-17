#include <stdio.h>
#include <stdlib.h>
#include "tasks.h"
#include "console.h"

int main() {
    Lista array;
    array.size = 0; 
    array.capacity = 100; 
    array.tarefas = malloc(sizeof(struct tarefa) * 100); 
    readCommand(&array);
    return 0;
}
