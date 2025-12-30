//Murilo Lusvarghi Garcia     RA: 2459671
//Arthur Romão Barreto     RA: 2474050

#include <stdio.h>
#include <stdlib.h>


typedef struct pixel {
    int linha;
    int coluna;
    unsigned char valor;
    struct pixel *prox;
} Pixel;


typedef struct imagem {
    int largura;
    int altura;
    Pixel *pixels;
} Imagem;


Imagem* ler_pgm(char *arquivo);
void histograma(Imagem *img);


Imagem* ler_pgm(char *arquivo) {
    FILE *pArq = NULL;
    pArq = fopen(arquivo, "rb");
    if (!pArq) {
        printf("Erro ao abrir arquivo!\n");
        exit(1);
    }


    // Lendo o cabeçalho e verificando se esta em p2
    char formato[3];
    fscanf(pArq, "%2s", formato);
    if (formato[0] != 'P' || formato[1] != '2') {
        printf("Formato de imagem inválido!\n");
        exit(1);
    }


    int largura, altura, valor_max;
    fscanf(pArq, "%d %d %d", &largura, &altura, &valor_max);


    // Criando a nova matriz esparsa
    Imagem *img = (Imagem*) malloc(sizeof(Imagem));
    img->largura = largura;
    img->altura = altura;
    img->pixels = NULL;


    // Ignorando o restante do cabeçalho
    fgetc(pArq);


    // Lendo os valores da imagem e armazenando na matriz esparsa
    int linha = 0, coluna = 0;
    unsigned char valor;
    while (fscanf(pArq, "%hhu", &valor) != EOF) {
        if (coluna == 0) {
            linha++;
        }
        coluna = (coluna + 1) % largura;
        if (valor != 0 && valor != 255) {
            Pixel *novo_pixel = (Pixel*) malloc(sizeof(Pixel));
            novo_pixel->linha = linha;
            novo_pixel->coluna = coluna;
            novo_pixel->valor = valor;
            novo_pixel->prox = img->pixels;
            img->pixels = novo_pixel;
        }
    }


    fclose(pArq);


    return img;
}


void histograma(Imagem *img) {
    // Alocando a matriz que guardara os valores da frequencia de cada tom de cinza
    unsigned char *freq = (unsigned char*) calloc(256, sizeof(unsigned char));
    if (!freq) {
        printf("Erro na alocacao de memoria!\n");
        exit(1);
    }


    // Percorrendo a matriz e atualizando o vetor de frequencia
    Pixel *p = img->pixels;
    while (p != NULL) {
        freq[p->valor]++;
        p = p->prox;
    }


    // Imprimimos o vetor de histograma para o usuario
    printf("Histograma:\n");
    for (int i = 1; i <= 254; i++) {
        printf("%d: %d\n", i, freq[i]);
    }


    // libera memoria alocada para frequencia
    free(freq);
}


int main() {
    Imagem *img = ler_pgm("rato.pgm");


    // Imprimindo os valores da matriz esparsa
    Pixel *p = img->pixels;
    while (p != NULL) {
        printf("(%d,%d) = %hhu\n", p->linha, p->coluna, p->valor);
        p = p->prox;
    }


    histograma(img);
   
    // Liberando a memória
    while (img->pixels != NULL) {
        Pixel *p = img->pixels;
        img->pixels = p->prox;
        free(p);
    }
   


    free(img);


    return 0;
}
