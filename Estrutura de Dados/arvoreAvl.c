///////////////////////////////////////////////////////////////////////////
///                                                                     ///
///                    Árvore de Busca Binária (BST)                    ///
///                         Atividade Prática 1                         ///
///                 Arthur Romão Barreto | RA: 2474050                  ///
///                                                                     ///
///////////////////////////////////////////////////////////////////////////

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct contato{
    char nome[20];
    char numero[12];
    char email[20];
    struct contato *direita;
    struct contato *esquerda;
}TContato;

TContato *criar(TContato *raiz, char nome[20], char numero[12], char email[20]); //Cria um nodo
TContato *inserir(TContato *raiz, char nome[20], char numero[12], char email[20]); //Insere um nodo criado na árvore
TContato *buscar(TContato *raiz, char nome[20]); //Busca um nodo
void alterar(TContato *raiz, char nome[20]); //Altera os dados de um nodo buscado
void remover(TContato **raiz, char nome[20]); //Remove um nodo buscado
TContato *buscarPai(TContato *raiz, TContato *contato); //Busca o pai de um nodo
TContato *buscarMenorDireita(TContato *contato); //Busca o sucessor de um nodo

int main(){
    TContato *raiz = NULL;
    short int op = 0, c;
    char nome[20];
    char numero[12];
    char email[20];

    while(op!=5){
        printf("\nEscolha uma opcao:\n");
        printf("1 - Inserir\n");
        printf("2 - Buscar\n");
        printf("3 - Alterar\n");
        printf("4 - Remover\n");
        printf("5 - Sair\n"); //Percorre o loop e o finaliza
        scanf("%hd",&op);

        while ((c = getchar()) != '\n' && c != EOF); //Limpa o buffer para os fgets() após o scanf

        switch(op){
            case 1: //Pede todos os dados para o usuário para serem inseridos na árvore
            printf("Insira o nome: ");
            fgets(nome,20,stdin);
            printf("Insira o numero: ");
            fgets(numero,12,stdin);
            printf("Insira o email: ");
            fgets(email,20,stdin);
            raiz = inserir(raiz, nome, numero, email);
            break;
            
            case 2: //Busca pelo contato usando o nome e imprime seu endereço caso seja encontrado, e caso a função retorne NULL o programa informa o usuário que a busca não teve sucesso
            printf("Insira o nome do contato que deve ser buscado: ");
            fgets(nome,20,stdin);
            if(buscar(raiz,nome))
                printf("Contato encontrado: %d\n",buscar(raiz,nome));
            else
                printf("Contato nao encontrado.\n");
            break;

            case 3: //Busca pelo contato usando o nome e abre um menu para o usuário alterar os dados de um contato
            printf("Insira o nome do contato que deve ter algum dado alterado: ");
            fgets(nome,20,stdin);
            alterar(raiz,nome);
            break;

            case 4: //Busca pelo contato usando o nome e faz o processo de remoção de nodo
            printf("Insira o nome do contato que deve ser removido: ");
            fgets(nome,20,stdin);
            remover(&raiz,nome);
            break;
        }
    }

    return 0;
}

TContato *buscarMenorDireita(TContato *contato){ //Recebe o nodo da direita do contato
    while(contato->esquerda)
        contato = contato->esquerda; //Avança para a esquerda até não poder mais
    
    return contato; //Retorna o menor nodo da direita
}

TContato *buscarPai(TContato *raiz, TContato *contato){
    //Caso não haja nodos na árvore ou caso o contato não tenha pai, a função retornará NULL
    if(!raiz || raiz == contato){
        return NULL;
    }
    //Caso um dos ponteiros do nodo atualmente lido aponte para o contato inserido, ele é retornado pela função
    if(strcmp(raiz->esquerda->nome, contato->nome) == 0 || strcmp(raiz->direita->nome, contato->nome) == 0){
        return raiz;
    }
    //Caso o nome do pai do contato inserido venha antes do nome do contato lido atualmente, em ordem alfabética, a função o procurará na sub-árvore da esquerda
    if(strcmp(contato->nome,raiz->nome) < 0){
        return buscarPai(raiz->esquerda,contato);
    //Caso o nome do pai do contato inserido venha depois do nome do contato lido atualmente, em ordem alfabética, a função o procurará na sub-árvore da direita
    } else if(strcmp(contato->nome,raiz->nome) > 0){
        return buscarPai(raiz->direita,contato);
    }
}

void remover(TContato **raiz, char nome[20]){
    if(!*raiz){ // Árvore vazia ou fim da busca
        printf("Contato invalido.\n");
        return;
    }

    TContato *contato = buscar(*raiz, nome); // Busca o nodo a ser removido

    if(!contato){ // Contato não encontrado
        printf("Contato invalido.\n");
        return;
    }

    TContato *pai = buscarPai(*raiz, contato); // Busca o pai do nodo a ser removido

    // Primeiro caso: remoção de um nodo sem filhos
    if(!contato->esquerda && !contato->direita){
        if (pai) {
            if (pai->esquerda == contato)
                pai->esquerda = NULL;
            else
                pai->direita = NULL;
        } else { // Remoção da raiz
            free(*raiz);
            *raiz = NULL;
        }
        free(contato);
    }
    // Segundo caso: remoção de um nodo com um filho
    else if(!contato->esquerda || !contato->direita){
        TContato *filho = contato->esquerda ? contato->esquerda : contato->direita;
        if (pai) {
            if (pai->esquerda == contato)
                pai->esquerda = filho;
            else
                pai->direita = filho;
        } else { // Remoção da raiz
            *raiz = filho;
        }
        free(contato);
    }
    // Terceiro caso: remoção de um nodo com dois filhos
    else {
        TContato *sucessor = buscarMenorDireita(contato->direita);
        strcpy(contato->nome, sucessor->nome);
        strcpy(contato->numero, sucessor->numero);
        strcpy(contato->email, sucessor->email);
        // Remover o sucessor da subárvore correta
        remover(&contato->direita, sucessor->nome);
    }
}


void alterar(TContato *raiz, char nome[20]){
    //Aproveita da função buscar para ter acesso ao nodo que será alterado
    TContato *contato = buscar(raiz, nome);
    short int op = 0, c;

    if(!contato){ //Aborta a função caso o contato não esteja na árvore e informa o usuário
        printf("Contato invalido.");
        return;
    }

    while(op!=4){
        //Exibe um menu para o usuário escolher o que será alterado e informa os dados atuais
        printf("\nO que deve ser alterado?\n");
        printf("1 - Nome   | Atual: %s",contato->nome);
        printf("2 - Numero | Atual: %s",contato->numero);
        printf("3 - Email  | Atual: %s",contato->email);
        printf("4 - Fim\n"); //Percorre o loop e o finaliza
        scanf("%hd",&op);

        while ((c = getchar()) != '\n' && c != EOF); //Limpa o buffer para os fgets() após o scanf

        switch(op){
            case 1:
            printf("Novo nome: ");
            fgets(contato->nome,20,stdin);
            break;

            case 2:
            printf("Novo numero: ");
            fgets(contato->numero,12,stdin);
            break;

            case 3:
            printf("Novo email: ");
            fgets(contato->email,20,stdin);
            break;
        }
    }
}

TContato *buscar(TContato *raiz, char nome[20]){
    //Caso a função encontre um espaço vazio, ela retornará NULL
    if(!raiz)
        return NULL;
    //Caso o nome do contato procurado venha antes do nome do contato lido atualmente, em ordem alfabética, a função o procurará na sub-árvore da esquerda
    else if(strcmp(nome,raiz->nome) < 0)
        return buscar(raiz->esquerda, nome);
    //Caso o nome do contato procurado venha depois do nome do contato lido atualmente, em ordem alfabética, a função o procurará na sub-árvore da direita
    else if(strcmp(nome,raiz->nome) > 0)
        return buscar(raiz->direita, nome);

    //Se a função ignorar os casos acima é porque ela encontrou um contato com o nome inserido, e então ela retornará o endereço do mesmo
    return raiz;
}

TContato *inserir(TContato *raiz, char nome[20], char numero[12], char email[20]){
    if(!raiz)
    //Caso a função encontre um espaço vazio, ele será ocupado pelo contato inserido
        raiz = criar(raiz,nome,numero,email);
    else if(strcmp(nome,raiz->nome) < 0)
    //Caso o nome do contato inserido venha antes do nome do contato lido atualmente, em ordem alfabética, a função o procurará na sub-árvore da esquerda
        raiz->esquerda = inserir(raiz->esquerda,nome,numero,email);
    else if(strcmp(nome,raiz->nome) > 0)
    //Caso o nome do contato inserido venha depois do nome do contato lido atualmente, em ordem alfabética, a função o procurará na sub-árvore da direita
        raiz->direita = inserir(raiz->direita,nome,numero,email);
    else if(strcmp(nome,raiz->nome) == 0){
    //Caso a função encontre um nodo com os mesmos dados na string nome, ela avisará o usuário e não irá inserir o novo contato
        printf("Ja existe um contato com o nome inserido, a insercao nao sera feita.\n");
    }

    return raiz;
}

TContato *criar(TContato *raiz, char nome[20], char numero[12], char email[20]){
    //Aloca a memória necessária
    TContato *novo = (TContato*)malloc(sizeof(TContato));
    //Insere as informações fornecidas
    strcpy(novo->nome, nome);
    strcpy(novo->numero, numero);
    strcpy(novo->email, email);
    novo->direita = NULL;
    novo->esquerda = NULL;
    //Retorna o novo nodo
    return novo;
}

