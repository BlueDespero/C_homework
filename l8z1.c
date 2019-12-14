#include<stdio.h>
#include<stdbool.h>
#include <stdlib.h>

struct node
{
    int value;
    struct node *next;
};

typedef struct node node_t;
typedef bool predicate(int);

node_t* push_front(node_t* list, int value)
{
    node_t * new_node;
    new_node = malloc(sizeof(node_t));

    new_node->value = value;
    new_node->next = list;
    list = new_node;
    return list;
}

node_t* pop_front(node_t* list, int *value)
{
    if (list->next == NULL){
        *value = list->value;
        free(list);
        return NULL;}

    node_t * next_node = list->next;
    *value = list->value;
    free(list);

    return next_node;
}

node_t* push_back(node_t* list, int value)
{
    if (list!=NULL)
    {
        node_t * current = list;
        while (current->next != NULL) {
            current = current->next;
        }

        current->next = malloc(sizeof(node_t));
        current->next->value = value;
        current->next->next = NULL;

        return list;
    }
    else
        list = push_front(list,value);
    return list;
}

node_t* pop_back(node_t* list, int *value)
{
    if (list->next == NULL)
        pop_front(list, value);
    else
    {
        node_t* current = list;
        while (current->next->next != NULL) current = current->next;
        *value = current->next->value;
        free(current->next);
        current->next = NULL;
        return list;
    }
    return list;
}

node_t* remove_if(node_t* list, predicate p)
{
    int v = 2;
    int* val = &v;

    while (p(list->value))
    {   
        list = pop_front(list,val);
        if (list==NULL)
            return NULL;
    }

    node_t * current = list;
    node_t * temp = NULL;

    while (current->next->next != NULL)
    {
        if (p(current->next->value))
        {
            temp = current->next;
            current->next = temp->next;
            free(temp);
        }
        else if ((current->next != NULL))
            current = current->next;
        
        if (current->next == NULL)
            break;
    }

    if (current->next!=NULL)
        if (p(current->next->value))
            current = pop_back(current, val);

    return list;
}

bool if_odd(int n){
    return n%2;}

bool if_even(int n){
    return (n+1)%2;}

node_t* reverse(node_t* list)
{
    node_t * new_list = malloc(sizeof(node_t));
    node_t * current = list;

    new_list->next = NULL;
    new_list->value = current->value;
    current = current->next;

    while (current->next!=NULL)
    {
        new_list = push_front(new_list,current->value);
        current = current->next;
    }

    new_list = push_front(new_list, current->value);
    return new_list;
}


void print_list(node_t* list)
{
    if(list!=NULL)
    {
        node_t* helper = list;
        while (helper->next != NULL)
        {
            printf("\n%d", helper->value);
            helper = helper->next;
        }
        printf("\n%d\n\n", helper->value);        
    }
}

int main() {
    node_t * lista = malloc(sizeof(node_t));
    int * val = malloc(sizeof(int));

    printf("-- Po utworzueniu listy -- \n");
    print_list(lista);
    for (int i = 1; i < 30; i+=2)
        lista = push_back(lista,i*2);
    printf("-- Lista wypełniona wartościami parzystymi -- \n");
    print_list(lista);
    lista = remove_if(lista, if_even);
    printf("-- Lista po usunięciu tylko wartości parzystych -- \n");
    print_list(lista);
    printf("OUT"); fflush(stdout);

    for (int i = 1; i < 30; i+=2)
        lista = push_back(lista,i);
    printf("-- Lista wypełniona wartościami nieparzystymi -- \n");
    print_list(lista);
    lista = remove_if(lista, if_odd);
    printf("-- Lista po usunięciu tylko wartości nieparzystych -- \n");
    print_list(lista);

    for (int i = 1; i < 30; i++)
        lista = push_back(lista,i);
    printf("-- Lista wypełniona wartościami obu parzystości -- \n");
    print_list(lista);
    lista = remove_if(lista, if_odd);
    printf("-- Lista po usunięciu tylko wartości nieparzystych -- \n");
    print_list(lista);

    printf("-- Lista po odwróceniu -- \n");
    lista = reverse(lista);
    print_list(lista);

    printf("-- Lista po czyszczeniu za pomocą pop_back -- \n");

    do
    {
        lista = pop_back(lista,val);
    } while (lista->next != NULL);
    lista = pop_back(lista,val);
    

    print_list(lista);

    free(val);
    return 0;
}