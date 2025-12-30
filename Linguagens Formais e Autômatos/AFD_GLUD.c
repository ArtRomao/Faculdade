#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ESTADOS 100
#define MAX_SIMBOLOS 100
#define MAX_CADEIA 1000
#define TAM_PRODUCAO 10
#define MAX_PRODUCOES 10

// Estrutura para representar um AFD
typedef struct {
    int num_estados; // Número de estados
    int num_simbolos; // Número de símbolos no alfabeto
    int num_aceitacao; // Número de estados de aceitação
    char alfabeto[MAX_SIMBOLOS]; // Alfabeto
    int estado_inicial; // Estado inicial
    int estados_aceitacao[MAX_ESTADOS]; // Conjunto de estados de aceitação
    int transicao[MAX_ESTADOS][MAX_SIMBOLOS]; // Tabela de transição
} AFD;

typedef struct {
    char simbolo; // Identificação da variável
    char producoes[MAX_PRODUCOES][TAM_PRODUCAO]; // Matriz de produções por variável
} Variavel;

typedef struct {
    int num_variaveis; // Número de variáveis
    int num_terminais; // Número de terminais
    Variavel variaveis[MAX_ESTADOS + 1]; // Estados do AFD + S
    char terminais[MAX_SIMBOLOS]; // Alfabeto do AFD
} GLUD;

void afdGlud(AFD *afd, GLUD *glud){
    glud->num_variaveis = afd->num_estados + 1; // V = Estados do AFD + S
    glud->num_terminais = afd->num_simbolos; 
    strcpy(glud->terminais, afd->alfabeto); // T = Alfabeto do AFD

    glud->variaveis[0].simbolo = 'S';
    sprintf(glud->variaveis[0].producoes[0], "%c", '0' + afd->estado_inicial); // S -> Estado inicial

    for(int i = 0; i < afd->num_estados; i++){
        glud->variaveis[i + 1].simbolo = '0' + i; // Adiciona cada estado do AFD como símbolo da GLUD
    }

    for(int i = 0; i < afd->num_estados; i++){ //Percorre todos os estados do AFD
        for (int j = 0; j < afd->num_simbolos; j++){ //Adiciona as produções de cada símbolo da GLUD
            int proximo = afd->transicao[i][j];
            if(proximo != -1){
                sprintf(glud->variaveis[i + 1].producoes[j], "%c%c", afd->alfabeto[j], '0' + proximo);
            }else{
                strcpy(glud->variaveis[i + 1].producoes[j], "");
            }
        }
    }
}

void imprimirGlud(AFD *afd, GLUD *glud){
    printf("G = ({");
        for(int i = 0; i < glud->num_variaveis; i++){
            if(i + 1 < glud->num_variaveis)
                printf("%c, ", glud->variaveis[i].simbolo);
            else
                printf("%c", glud->variaveis[i].simbolo);
        }
    printf("}, {");
        for(int i = 0; i < glud->num_terminais; i++){
            if(i + 1 < glud->num_terminais)
                printf("%c, ", glud->terminais[i]);
            else
                printf("%c", glud->terminais[i]);
        }
    printf("}, P, S), onde:\n");
    printf("P = {\n");
    for (int i = 0; i < glud->num_variaveis; i++){
        printf("%c -> ", glud->variaveis[i].simbolo);
        for (int j = 0; j < MAX_PRODUCOES; j++){
            if (strlen(glud->variaveis[i].producoes[j]) > 0){
                printf("%s", glud->variaveis[i].producoes[j]);

                // Verifica se o símbolo atual é o último
                int ultimo = 1;
                for (int k = j + 1; k < MAX_PRODUCOES; k++){
                    if (strlen(glud->variaveis[i].producoes[k]) > 0){
                        ultimo = 0;
                        break;
                    }
                }

                if (!ultimo){
                    printf(" | ");
                }
            }
        }

        // Adiciona a produção de epsilon se o símbolo representa um estado final
        if (i > 0){
            int estado_afd = glud->variaveis[i].simbolo - '0';
            if (afd->estados_aceitacao[estado_afd]){
                printf(" | (EPSILON)");
            }
        }

        if(i + 1 != glud->num_variaveis)
            printf(",\n");
        else
        printf("}\n");
    }
}

// Função para criar um AFD
void criarAfd(AFD *afd){
    printf("Número de estados: ");
    scanf("%d", &afd->num_estados);

    printf("Número de símbolos no alfabeto: ");
    scanf("%d", &afd->num_simbolos);

    printf("Digite os símbolos do alfabeto (sem espaços): ");
    scanf("%s", afd->alfabeto);

    printf("Estado inicial (0 a %d): ", afd->num_estados - 1);
    scanf("%d", &afd->estado_inicial);

    printf("Número de estados de aceitação: ");
    scanf("%d", &afd->num_aceitacao);

    printf("Digite os estados de aceitação (separados por espaço): ");
    for (int i = 0; i < afd->num_aceitacao; i++){
        int estado;
        scanf("%d", &estado);
        afd->estados_aceitacao[estado] = 1; // Marca como estado de aceitação
    }

    // Preenchendo a tabela de transição
    printf("Defina a função de transição:\n");
    for (int i = 0; i < afd->num_estados; i++){
        for (int j = 0; j < afd->num_simbolos; j++){
            printf("Transição do estado %d com símbolo %c: ", i, afd->alfabeto[j]);
            scanf("%d", &afd->transicao[i][j]);
        }
    }
}

int main(){
    AFD afd;
    GLUD glud;

    criarAfd(&afd);
    afdGlud(&afd, &glud);
    imprimirGlud(&afd, &glud);

    return 0;
}