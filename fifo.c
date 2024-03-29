#include <stdio.h>
#include <stdlib.h>
int inserir(int *, int, int *, const int, int *);
int remover(int *, int *, int *);
int isVazia(int *, int *);
int inserir(int *fila, int info, int *tail, const int size, int *isCreate)
{
    if (*tail == size)
    {
        return 0;
    }
    if (*isCreate == 0)
    {
        fila[*tail] = info;
        *isCreate = 1;
        return 1;
    }
    fila[*tail] = info;
    *tail = *tail + 1;
    return 1;
}
int remover(int *fila, int *tail, int *head)
{
    if (!isVazia(head,tail))
    {
        return 0;
    }
    int temp = fila[*head];
    *head = *head + 1;
    return temp;
}
int isVazia(int *head, int *tail)
{
    if (*head == *tail)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}
int main()
{
    const int size = 8;
    int fila[size];
    int tail_ = 0;
    int head_ = 0;
    int isCreate_ = 0;
    int temp;
    int *isCreate;
    int *tail;
    int *head;
    tail = &tail_;
    head = &head_;
    isCreate = &isCreate_;
    for (int i = 0; i < size; i++)
    {
        //PARA INSERIR OS ITEMS NO ARRAY É SÓ TROCAR "i" PELO VALOR QUE VOCE QUISER
        inserir(fila, i, tail, size, isCreate);
    }
    while(isVazia(head,tail)){ //AQUI ELE REMOVE TODOS OS ITEMS, SÓ PARA DEMOSRAÇÃO
       temp= remover(fila,tail,head);
       printf("%d",temp);
    }

    return 0;
}
