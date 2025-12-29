#include <stdio.h>
#include <stdlib.h>

typedef struct disco
{
    int num;
    struct disco *prox;
}TDisco;

typedef struct pino
{
    TDisco *inicio;
    int qtde;
}TPino;

TPino *Cabeca();
int conferir(int d, int n);
void inserir(TPino *p, int k);
void mover(TPino *p1, TPino *p2);
void comecar(TPino *pa, int n);
void imprimir(TPino *p);

int main()
{
    TPino *pa=Cabeca(), *pb=Cabeca(), *pc=Cabeca();
    int n, op1=1, op2=1;
    printf("=============================== Torres de Hanoi ================================\n");
    printf("Objetivo: Posicionar todos os discos no pino B sendo apenas capaz\n");
    printf("de colocar um disco encima de outro se ele tiver um valor menor.\n");
    printf("================================================================================\n");
    do
    {
        printf("Insira a quantidade de discos: ");
        scanf("%d",&n);
        if(n<1)
            printf("Opcao invalida!\n");
    }while(n<1);
    comecar(pa, n);
    while(conferir(pb->qtde,n)==0)
    {
        printf("================================================================================\n");
        printf("1 - Pino A:\n");
        imprimir(pa);
        printf("2 - Pino B:\n");
        imprimir(pb);
        printf("3 - Pino C:\n");
        imprimir(pc);
        printf("================================================================================\n");
        do
        {
            printf("Insira o numero do pino que deve ter o disco do topo removido: ");
            scanf("%d",&op1);
            if(op1<1||op1>3)
                printf("Opcao invalida!\n");
        }while(op1<1||op1>3);
        do
        {
            printf("Insira o numero do pino que deve ter o disco colocado no topo: ");
            scanf("%d",&op2);
            if(op2<1||op2>3)
                printf("Opcao invalida!\n");
        }while(op2<1||op2>3);
        if(op1==1&&op2==2)
            mover(pa,pb);
        if(op1==1&&op2==3)
            mover(pa,pc);
        if(op1==2&&op2==1)
            mover(pb,pa);
        if(op1==2&&op2==3)
            mover(pb,pc);
        if(op1==3&&op2==1)
            mover(pc,pa);
        if(op1==3&&op2==2)
            mover(pc,pb);
    }
    printf("Voce venceu!\n");
    printf("Pino B:\n");
    imprimir(pb);
}

void imprimir(TPino *p)
{
    if(p->inicio)
    {
        TDisco *aux = p->inicio;
        while(aux)
        {
            printf("  - %d\n", aux->num);
            aux = aux->prox;
        }
    }
}

void mover(TPino *p1, TPino *p2)
{
    if(p1->inicio)
    {
        if(p2->inicio)
        {
            if(p2->inicio->num < p1->inicio->num)
            {
                printf("================================================================================\n");
                printf("O disco do topo possui um valor menor do que o disco que voce tentou posicionar.\n");
                return;
            }
        }
        inserir(p2,(p1->inicio->num));
        TDisco *aux = p1->inicio;
        p1->inicio = p1->inicio->prox;
        free(aux);
        p1->qtde--;
        return;
    }
    printf("================================================================================\n");
    printf("Nao existe um disco para ser movido do pino selecionado.\n");
}

int conferir(int d, int n)
{
    if(d==n)
    {
        return 1;
    }
    return 0;
}

void comecar(TPino *pa, int n)
{
    if(pa)
    {
        while(n>0)
        {
            inserir(pa,n);
            n--;
        }
    }
}

void inserir(TPino *p, int k)
{
    TDisco *novo = (TDisco *)malloc(sizeof(TDisco));
    if(novo)
    {
        novo->num = k;
        novo->prox = p->inicio;
        p->inicio = novo;
        p->qtde++;
        return;
    }
    printf("Erro de alocacao!\n");
}

TPino *Cabeca()
{
    TPino *novo = (TPino *)malloc(sizeof(TPino));
    if(novo)
    {
        novo->qtde=0;
        novo->inicio=NULL;
        return novo;
    }
    printf("Erro de alocacao!\n");
    return NULL;
}