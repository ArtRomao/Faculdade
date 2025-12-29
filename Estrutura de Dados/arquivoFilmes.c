#include <stdio.h>

typedef struct filme
{
    char nome[30];
    float nota;
    char palavra[30];
}filme;

int main()
{
    FILE *arq;
    filme filme1;
    int cont=0, n;
    printf("\nQuantos filmes serao inseridos: ");
    scanf("%d",&n);
    arq = fopen("filmes.txt","a");

    while(cont<n)
    {
        printf("\nNome do filme: ");
        scanf("%s",&filme1.nome);

        printf("\nNota do filme (0-10): ");
        scanf("%f",&filme1.nota);

        printf("\nDescreva o filme em uma palavra: ");
        scanf("%s",&filme1.palavra);

        fprintf(arq,"%s %.1f %s\n",filme1.nome,filme1.nota,filme1.palavra);
        printf("\n");
        cont++;
    }
    fclose(arq);

    arq = fopen("filmes.txt","r");
    while(!feof(arq))
    {
        fscanf(arq,"%s %f %s",filme1.nome,&filme1.nota,filme1.palavra);
        if(feof(arq)) break;
        printf("\nNome do filme: %s",filme1.nome);
        printf("\nNota do filme: %.1f",filme1.nota);
        printf("\nFilme em uma palavra: %s\n",filme1.palavra);
    }
    fclose(arq);

    return 0;
}