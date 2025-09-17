#include "tasks.h"
#include "console.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void printTask(Tarefa tarefa){
    printf("=== Tarefa %d ===\n", tarefa->id); 
    printf("Titulo: %s\n", (tarefa)->title);
    if((tarefa)->str[0] == '\0'){
        printf("Sem descrição\n"); 
    } else {
            printf("Descrição: %s\n", (tarefa)->str);
    }
    printf("Prioridade: %s\n", (tarefa)->prioridadeStr);
    char state[10] = ""; 
    if(tarefa->taskState == 1) strcpy(state, "Pendente"); 
    else strcpy(state,"Concluida");
    printf("Estado: %s\n", state);   
    printf("\n"); 
}

// void printFile(FILE *fptr, Tarefas tmp){
//     fprintf(fptr,"start\n"); 
//     fprintf(fptr,"%s\n", (tmp)->title);
//     if((tmp)->str[0] == '\0'){
//         fprintf(fptr,"NULL\n"); 
//     } else {
//             fprintf(fptr,"%s\n", (tmp)->str);
//     }
//     fprintf(fptr,"%s\n", (tmp)->prioridadeStr);
//     char state[10] = ""; 
//     if(tmp->taskState == 1) strcpy(state, "Pendente"); 
//     else strcpy(state,"Concluida");
//     fprintf(fptr, "%s\n", state); 
//     fprintf(fptr,"end\n");    
// }


void handleNewTask(Lista *tarefas) {
    char str[101] = ""; 
    char title[51] = ""; 
    char prioridadeStr[10] = ""; 
    int prioridade =0 ; 
    int flagError = 0; 
    int times = 0; 

    do {
        flagError = 0; 
        if (times > 0) {
            consoleMessage("Tarefa invalida, tenta de novo");
        } 

        system("clear"); 
        printf("=== Adicionar Tarefas (ESC+ENTER para cancelar) ===\n"); 

        printf("Titulo da tarefa (max: 50 chars): ");  
        fgets(title, sizeof(title), stdin); 
        title[strcspn(title, "\n")] = '\0';
        if (title[0] == 27) {  
            consoleMessage("Operação cancelada");
            return; 
        }

        printf("\nDescrição da tarefa (opcional, max: 100 chars): ");  
        fgets(str, sizeof(str), stdin); 
        str[strcspn(str, "\n")] = '\0'; 
        if (str[0] == 27) {  
            consoleMessage("Operação cancelada");
            return; 
        }

        printf("\nDefina a prioridade (Baixa, Media, Alta): ");  
        fgets(prioridadeStr, sizeof(prioridadeStr), stdin);
        prioridadeStr[strcspn(prioridadeStr, "\n")] = '\0';    
        if(prioridadeStr[0] == 27){  
            consoleMessage("Operação cancelada");
            return; 
        }

        if(strcasecmp(prioridadeStr, "Alta") == 0) {
            strcpy(prioridadeStr, "Alta"); 
            prioridade = 3; 
        }
        else if(strcasecmp(prioridadeStr, "Media") == 0) {
            strcpy(prioridadeStr, "Media"); 
            prioridade = 2;
        }
        else if(strcasecmp(prioridadeStr, "Baixa") == 0) {
            strcpy(prioridadeStr, "Baixa"); 
            prioridade = 1; 
        }
        else flagError = 1; 

        printf("\nClica Enter para concluir");
        getchar();

        times++; 
    }
    while (*title == '\0' || flagError);
    newTask(tarefas, prioridadeStr, prioridade, title, str, 1); 
    consoleMessage("Tarefa adicionada com sucesso"); 
}


// void newTask(Lista *array, char *prioridadeStr, int prioridade,char *title, char *descr, int state){ 
//     if(array->size == array->capacity){
//         int novaCapacidade; 
//         if(array->capacity == 0) novaCapacidade = 1; 
//         else novaCapacidade = array->capacity * 2; 
//         array->tarefas = realloc(array->tarefas, novaCapacidade * sizeof(struct tarefa)); 
//         array->capacity = novaCapacidade; 
        
//     } 
//     Tarefa novaTarefa = malloc(sizeof(struct tarefa)); 
//     if(novaTarefa == NULL){ 
//         consoleMessage("erro alloc"); 
//         return; 
//     } 
//     novaTarefa->prioridade = prioridade; 
//     novaTarefa->taskState = state; 
//     strcpy(novaTarefa->prioridadeStr, prioridadeStr); 
//     strcpy(novaTarefa->title, title); 
//     strcpy(novaTarefa->str, descr);  
//     int i; 
//     for(i = 0; i < array->size; i++) {
//         if (novaTarefa->prioridade > array->tarefas[i]->prioridade) break;
//     }
//     novaTarefa->id = i + 1;
//     if(i != 0 && i != array->size){
//         for(int j = i; j < array->size; j++) {
//             array->tarefas[j + 1] = array->tarefas[j]; 
//             array->tarefas[j + 1]->id = j + 2;
//         }
//     }
//     array->tarefas[i] = novaTarefa; 
//     (array->size)++; 
// }

void newTask(Lista *array, char *prioridadeStr, int prioridade, char *title, char *descr, int state){ 
    if(array->size == array->capacity){
        int novaCapacidade = (array->capacity == 0) ? 1 : array->capacity * 2; 
        array->tarefas = realloc(array->tarefas, novaCapacidade * sizeof(Tarefa)); 
        array->capacity = novaCapacidade; 
    } 

    Tarefa novaTarefa = malloc(sizeof(struct tarefa)); 
    if(novaTarefa == NULL){
        consoleMessage("erro alloc"); 
        return; 
    } 

    novaTarefa->prioridade = prioridade; 
    novaTarefa->taskState = state; 
    strcpy(novaTarefa->prioridadeStr, prioridadeStr); 
    strcpy(novaTarefa->title, title); 
    strcpy(novaTarefa->str, descr);  

    int i; 
    for(i = 0; i < array->size; i++) {
        if (novaTarefa->prioridade > array->tarefas[i]->prioridade) break;
    }

    for(int j = array->size; j > i; j--) {
        array->tarefas[j] = array->tarefas[j - 1]; 
        array->tarefas[j]->id = j + 1;
    }

    novaTarefa->id = i + 1;
    array->tarefas[i] = novaTarefa; 
    (array->size)++; 
}

void showTasks(Lista *array) {
    if (array == NULL || array->size == 0) {
        consoleMessage("Lista de tarefas vazia");
        return;
    }

    printf("=== Lista de Tarefas ===\n\n");

    for (int i = 0; i < array->size; i++) {
        if (array->tarefas[i] != NULL) {
            printTask(array->tarefas[i]);
        }
    }
    printf("\nPressione Enter para continuar...\n");
    while (getchar() != '\n');
}


void removeTask(Lista *array){
    if(array->tarefas == NULL || array->size == 0) {
        consoleMessage("Nao ha tarefas a remover");
        return;
    }
    int num = -1;

    int flag = 0; 
    do{
    
        system("clear");
        printf("=== Remover Tarefa ===\n"); 
        printf("Digite o numero da tarefa a remover(-1 para sair): "); 
        scanf("%d", &num); 
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        if(num != -1 && num <= array->size){
            free(array->tarefas[num - 1]);
            for(int i = num - 1; i < array->size - 1; i++) {
                array->tarefas[i] = array->tarefas[i + 1]; 
                array->tarefas[i]->id = i + 1; 
            }
            array->tarefas[array->size - 1] = NULL;
            (array->size)--; 
            flag = 1; 
        }
        else if(num != -1 && num >= array->size){
            consoleMessage("Numero invalido");
        }
        else{
            consoleMessage("Operacao cancelada"); 
            return; 
        }
    } 
    while(!flag);  
    consoleMessage("Tarefa removida com sucesso");
}

void markAsDone(Lista *array){
    if(array->size == 0) {
        consoleMessage("Nao ha tarefas para concluir");
        return;
    }
    int num = -2;
    int flag = 0; 
    do{
        system("clear");
        printf("=== Marcar como concluida ===\n"); 
        printf("Digite o numero da tarefa a marcar com concluida (-1 para sair): "); 
        scanf("%d", &num); 
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        if(num != -1){
            if(num <= array->size && num > 0){
                array->tarefas[num - 1]->taskState = 2; 
                flag = 1; 
            }
            else{
                consoleMessage("Numero invalido");
            }
        }
        else{
            consoleMessage("Operacao cancelada"); 
            return; 
        }
    } 
    while(num == -2 || !flag);  
    consoleMessage("Tarefa marcada como concluida"); 
}


void handleFilterStatus(Lista *array){
    int statusFilter = 0; 
    int flag = 0; 
    do{
        printf("Digite o Status desejado (1- pendente, 2-concluida): ");
        scanf("%d", &statusFilter);
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        if(statusFilter == 1 || statusFilter == 2) flag = 1;
        else{
            consoleMessage("Status errado, escolha 1 ou 2");
            system("clear"); 
        } 
    }
    while(!flag);
    system("clear");
    printf("=== Lista de Tarefas ===\n"); 
    printf("\n");
    int count = 0; 
    int i; 
    for(i = 0; i < array->size; i++) {
        if(array->tarefas[i]->taskState == statusFilter){
            printTask(array->tarefas[i]); 
            printf("\n");
            count++; 
        }
    }
    if(count == 0){
        consoleMessage("Nenhuma tarefa nestas condicoes"); 
    }
    else getchar(); 
}

void handleFilterPriority(Lista *array){
    char prioridadeStr[10] = ""; 
    int prioridade = 0; 
    int valida = 0; 
    do{
        printf("Digite a Prioridade desejada (Alta, Media ou Baixa): ");
        fgets(prioridadeStr, sizeof(prioridadeStr), stdin); 
        prioridadeStr[strcspn(prioridadeStr, "\n")] = '\0'; 
        if(strcasecmp(prioridadeStr, "Alta") == 0) {
            valida = 1; 
            prioridade = 3; 
        }
        else if(strcasecmp(prioridadeStr, "Media") == 0){
            valida = 1; 
            prioridade = 2; 
        }
        else if (strcasecmp(prioridadeStr, "Baixa") == 0){
            valida = 1; 
            prioridade = 1; 
        }
        else{
            consoleMessage("Prioridade errada, escolha Alta, Media ou Baixa");
            system("clear");
        }
    }
    while(!valida); 
    system("clear");
    printf("=== Lista de Tarefas ===\n"); 
    printf("\n");
    int count = 0; 
    int i; 
    for(i = 0; i < array->size; i++) {
        if(array->tarefas[i]->prioridade == prioridade){
            printTask(array->tarefas[i]);
            printf("\n"); 
            count++; 
        }
    }
    if(count == 0){
        consoleMessage("Nenhuma tarefa nestas condicoes"); 
    }
    else getchar(); 
}


void handleBoth(Lista *array){
    char prioridadeStr[10] = ""; 
    int prioridade = 0; 
    int valida = 0; 
    int statusFilter = 0;  
    do{
        printf("Digite a Prioridade desejada (Alta, Media ou Baixa): ");
        fgets(prioridadeStr, sizeof(prioridadeStr), stdin); 
        prioridadeStr[strcspn(prioridadeStr, "\n")] = '\0'; 
        if(strcasecmp(prioridadeStr, "Alta") == 0) {
            valida = 1; 
            prioridade = 3; 
        }
        else if(strcasecmp(prioridadeStr, "Media") == 0){
            valida = 1; 
            prioridade = 2; 
       }
        else if (strcasecmp(prioridadeStr, "Baixa") == 0){
            valida = 1; 
            prioridade = 1; 
        }
        else{
            consoleMessage("Prioridade errada"); 
            system("clear"); 
        } 

        if(valida){
            printf("\nDigite o Status desejado (1 - Pendente ou 2 - Concluida): ");
            scanf("%d", &statusFilter);
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            if(statusFilter != 1 && statusFilter != 2){
                consoleMessage("Status errado, escolha 1 ou 2");
                valida = 0; 
                system("clear");
            }
        }
    }
    while(!valida); 
    system("clear");
    printf("=== Lista de Tarefas ===\n"); 
    printf("\n");
    int i; 
    int count = 0; 
    for(i = 0; i < array->size; i++) {
        if(array->tarefas[i]->taskState == statusFilter && array->tarefas[i]->prioridade ==  prioridade){
            printTask(array->tarefas[i]); 
            count++; 
            printf("\n"); 
        }
    }
    if(count == 0){
        consoleMessage("Nenhuma tarefa nestas condicoes"); 
    }
    else getchar(); 
}


void filterTasks(Lista *array){
    if(array == NULL || array->size == 0){
        consoleMessage("Nao ha tarefas"); 
        return; 

    }
    char filterStr[20] = ""; 
    int flagApply = 0; 
    do{
        system("clear"); 
        printf("Qual categoria deseja usar para filtrar(Prioridade, Status ou Ambos (-1 para sair)): "); 
        fgets(filterStr, sizeof(filterStr), stdin); 
        filterStr[strcspn(filterStr, "\n")] = '\0'; 
        if(strcasecmp(filterStr, "Status") == 0){
            handleFilterStatus(array); 
        }
        else if (strcasecmp(filterStr, "Prioridade") == 0){
            handleFilterPriority(array);
        }
        else if(strcasecmp(filterStr, "Ambos") == 0){
            handleBoth(array);
        }
        else if(strcasecmp(filterStr, "-1") == 0){
            flagApply = 1; 
        }
        else{
            consoleMessage("Categoria invalida, escolha Prioridade, Status ou Ambos");
        }
    }
    while(!flagApply); 
}

// void saveFile(Lista *array){
//     char fileName[50];
//     char fullPath[200]; 
//     int flag = -1; 
//     int flagCancel = 0; 
//     char ans[10];  

//     do {
//         system("clear");
//         printf("Digite o nome do ficheiro sem .txt(q para cancelar): "); 
//         fgets(fileName, sizeof(fileName), stdin);
//         fileName[strcspn(fileName, "\n")] = '\0';  
//         if(strcasecmp(fileName, "q") == 0) flagCancel = 1;
//         else{
//             snprintf(fullPath, sizeof(fullPath), 
//                     "/Users/goncalosousa/Documents/projects/tarefas_project/files/%s.txt", 
//                     fileName);

//             FILE *f = fopen(fullPath, "r");
//             if (f != NULL) {
//                 fclose(f);
//                 system("clear");
//                 printf("Esse ficheiro já existe, pretende sobrescrever? (Sim/Nao): ");
//                 fgets(ans, sizeof(ans), stdin); 
//                 ans[strcspn(ans, "\n")] = '\0'; 

//                 if (strcasecmp(ans, "Sim") == 0) 
//                     flag = 1; 
//                 else 
//                     flag = 0;  
//             } else {
//                 flag = 1; 
//             }
//         }
//     } while(flag != 1 && !flagCancel); 
//     if(!flagCancel){
//         FILE *fptr = fopen(fullPath, "w");
//         if (fptr == NULL) {
//             perror("Erro ao abrir ficheiro");
//             return;
//         }   
//         Tarefas tmp = *tarefas; 
//         while(tmp != NULL){
//             printFile(fptr, tmp);
//             tmp = tmp->prox; 
//         }

//         fclose(fptr);
//         consoleMessage("Tarefas guardadas com sucesso!");
//     }
//     else{
//         consoleMessage("Operacao cancelado"); 
//     }
// }

// void loadFile(Tarefas *tarefas){
//     char fileName[50];
//     char fullPath[200]; 
//     char myString[100];
//     int count = 0; 
//     char str[101] = "";
//     char title[51] = ""; 
//     char prioridadeStr[10] = ""; 
//     int prioridade =0 ; 
//     int state = 0; 
//     int done = 0; 
//     do {
//         system("clear"); 
//         printf("Digite o nome do ficheiro a carregar: "); 
//         fgets(fileName, sizeof(fileName), stdin); 
//         fileName[strcspn(fileName, "\n")] = '\0'; 
//         snprintf(fullPath, sizeof(fullPath), 
//                 "/Users/goncalosousa/Documents/projects/tarefas_project/files/%s.txt", 
//                 fileName);
//         FILE *fptr = fopen(fullPath,"r"); 
//         if(fptr != NULL){
//             while(fgets(myString, sizeof(myString), fptr)) {
//                 myString[strcspn(myString, "\n")] = '\0';
//                 switch (count)
//                 {
//                 case 0:
//                     title[0] = '\0'; 
//                     str[0] = '\0'; 
//                     prioridadeStr[0] = '\0'; 
//                     count++; 
//                     break;
//                 case 1:
//                     strcpy(title, myString);
//                     count++; 
//                     break; 
//                 case 2: 
//                     strcpy(str, myString); 
//                     count++; 
//                     break; 
//                 case 3: 
//                     if(strcmp(myString, "Alta") == 0) prioridade = 3; 
//                     else if (strcmp(myString, "Media") == 0) prioridade = 2; 
//                     else prioridade = 1; 
//                     strcpy(prioridadeStr, myString);
//                     count++; 
//                     break; 
//                 case 4: 
//                     if(strcmp(myString, "Pendente") == 0) {
//                         state = 1; 
//                     }
//                     else state = 0; 
//                     count++; 
//                     break; 
//                 case 5:
//                     newTask(tarefas, prioridadeStr,  prioridade,  title,  str, state);
//                     count = 0; 
//                     break; 
//                 default: 
//                     break; 
//                 }
//             }
//             done = 1; 
//         }
//         else consoleMessage("O ficheiro nao existe, tente novamente"); 
//     }
//     while(!done); 
//     consoleMessage("Ficheiro carregado com sucesso"); 
// }



void handleCommand(char *command, Lista *tarefas){
    switch (command[0])
    {
        case '1':
            handleNewTask(tarefas); 
            break;
        case '2':
            system("clear"); 
            showTasks(tarefas); 
            break;
        case '3':
            removeTask(tarefas); 
            break;
        case '4':
            markAsDone(tarefas); 
            break;
        case '5':
            filterTasks(tarefas);
            break;
        case '6':
            // saveFile(tarefas); 
            break;
        case '7':
            // loadFile(tarefas); 
            break;
        case '8':  
            break; 
        default:
            command[strcspn(command, "\n")] = '\0';
            consoleMessage("Comando inválido"); 
            break;
        
    }
}
 


void readCommand(Lista *tarefas){
    char command[100] = "0";
    while (command[0] != '8') {
        system("clear"); 
        printf("=== Lista de Tarefas ===\n"); 
        printf("1. Adicionar tarefa\n");
        printf("2. Listar tarefas\n");
        printf("3. Remover tarefa\n");
        printf("4. Marcar tarefa como concluída\n");
        printf("5. Filtrar tarefas\n");
        printf("6. Guardar lista em ficheiro\n");
        printf("7. Carregar lista de ficheiro\n");
        printf("8. Sair\n");
        printf("Escolhe uma opção: "); 

        if (fgets(command, sizeof(command), stdin) == NULL) {
            continue; 
        }
        command[strcspn(command, "\n")] = '\0';

        int len = strlen(command); 
        if (len != 1) {
            consoleMessage("Comando inválido"); 
            command[0] = '0'; 
        } else {
            handleCommand(command, tarefas);  
        }
    }
}