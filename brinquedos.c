
// Problema: recebemos uma nota que avalia N brinquedos em N categorias diferentes. Queremos encontrar a menor diferença
//de nota, escolhendo um brinquedo de cada categoria

//Entrada: inteiro N, N linhas com notas inteiras dos N brinquedos de cada tipo
//Saída: menor diferença

#include <stdio.h>
#include <stdlib.h>

//Estruturas ide árvore rubro negra


//Funções árvore rubro negra

enum Cor
{
    VERMELHO,
    PRETO
};

typedef struct No
{
    int chave, categoria, posicao;
    enum Cor cor;
    struct No *esq, *dir;
} No;

typedef No *p_no;

int ehVermelho(p_no x)
{
    if (x == NULL)
    {
        return 0;
    }
    else
    {
        return x->cor == VERMELHO;
    }
}

int ehPreto(p_no x)
{
    if (x == NULL)
    {
        return 1;
    }
    else
    {
        return x->cor == PRETO;
    }
}

void sobe_vermelho(p_no raiz)
{
    raiz->cor = VERMELHO;
    raiz->esq->cor = PRETO;
    raiz->dir->cor = PRETO;
}

p_no rotaciona_para_esquerda(p_no raiz)
{
    p_no x = raiz->dir;
    raiz->dir = x->esq;
    x->esq = raiz;
    x->cor = raiz->cor;
    raiz->cor = VERMELHO;
    return x;
}

p_no rotaciona_para_direita(p_no raiz)
{
    p_no x = raiz->esq;
    raiz->esq = x->dir;
    x->dir = raiz;
    x->cor = raiz->cor;
    raiz->cor = VERMELHO;
    return x;
}

p_no inserir_rec(p_no raiz, int chave, int categoria, int posicao)
{

    if (raiz == NULL)
    {
        p_no novo;
        novo = malloc(sizeof(No));
        novo->esq = novo->dir = NULL;
        novo->chave = chave;
        novo->categoria = categoria;
        novo->posicao = posicao;
        novo->cor = VERMELHO;

        return novo;
    }

    if (chave <= raiz->chave)
    {
        raiz->esq = inserir_rec(raiz->esq, chave, categoria, posicao);
    }
    else
    {
        raiz->dir = inserir_rec(raiz->dir, chave, categoria, posicao);
    }
    if (ehVermelho(raiz->dir) && ehPreto(raiz->esq))
    {
        raiz = rotaciona_para_esquerda(raiz);
    }
    if (ehVermelho(raiz->esq) && ehVermelho(raiz->esq->esq))
    {
        raiz = rotaciona_para_direita(raiz);
    }
    if (ehVermelho(raiz->esq) && ehVermelho(raiz->dir))
    {
        sobe_vermelho(raiz);
    }
    return raiz;
}

//insere e balanceia
p_no inserir(p_no raiz, int chave, int categoria, int posicao)
{
    raiz = inserir_rec(raiz, chave, categoria, posicao);
    raiz->cor = PRETO;
    return raiz;
}


//encontra máximo
p_no maximo(p_no raiz)
{
    if (raiz == NULL || raiz->dir == NULL)
    {
        return raiz;
    }
    else
    {
        return maximo(raiz->dir);
    }
}

//encontra minimo
p_no minimo(p_no raiz)
{
    if (raiz == NULL || raiz->esq == NULL)
    {
        return raiz;
    }
    else
    {
        return minimo(raiz->esq);
    }
}

void inverte_cor(p_no raiz){
    raiz->cor = (raiz->cor == PRETO ? VERMELHO : PRETO);
    if(raiz->esq != NULL)
        raiz->esq->cor = (raiz->esq->cor == PRETO ? VERMELHO : PRETO);
    if(raiz->dir != NULL)
        raiz->dir->cor = (raiz->dir->cor == PRETO ? VERMELHO : PRETO);
}

p_no rebalancear(p_no raiz){
    if(ehVermelho(raiz->dir))
        raiz = rotaciona_para_esquerda(raiz);
    if(ehVermelho(raiz->esq) && ehVermelho(raiz->esq->esq))
        raiz = rotaciona_para_direita(raiz);
    if(ehVermelho(raiz->esq) && ehVermelho(raiz->dir))
        inverte_cor(raiz);
    return raiz;
}

p_no rotaciona_vermelho_para_esquerda(p_no raiz){
    inverte_cor(raiz);
    if(raiz != NULL && raiz->dir != NULL && ehVermelho(raiz->dir->esq)){
        raiz->dir = rotaciona_para_direita(raiz->dir);
        raiz = rotaciona_para_esquerda(raiz);
        inverte_cor(raiz);
    }
    return raiz;
}

//remove mínimo e balanceia
p_no remove_minimo_rec(p_no raiz){
    if(raiz == NULL){
        return NULL;
    }
    if(raiz->esq == NULL){
        free(raiz);
        return NULL;
    }
    if(ehPreto(raiz->esq) && ehPreto(raiz->esq->esq))
        raiz = rotaciona_vermelho_para_esquerda(raiz);
    raiz->esq = remove_minimo_rec(raiz->esq);
    return rebalancear(raiz);
}

p_no remove_minimo(p_no raiz){
    raiz = remove_minimo_rec(raiz);
    if(raiz != NULL) raiz->cor = PRETO;
    return raiz;
}


//libera memória da árvore
void liberar_arvore(p_no raiz){
    if(raiz != NULL){
        if(raiz->esq != NULL){
            liberar_arvore(raiz->esq);
        }
        if(raiz->dir != NULL){
            liberar_arvore(raiz->dir);
        }
        free(raiz);
    }
}


//devolve a diferença entre o maior e o menor elemento da árvore, todos os demais serão intermediários
int obter_menor_diferenca(p_no raiz){
    return (maximo(raiz)->chave - minimo(raiz)->chave);

}

int comparador(const void *a, const void *b) {
    return ( *(int*)a - *(int*)b );
}



int main() {
    int N, menor_diferenca;
    scanf("%d", &N);

    //alocar matriz
    int **matriz;

    matriz = malloc (N * sizeof (int*)) ;

    for (int i = 0; i < N; i++)
        matriz[i] = malloc (N * sizeof (int)) ;


    //alocar matriz

    for(int i = 0; i < N; i++){
        //são dados apenas 4 valores que determinam a diversão entre todos os brinquedos

        long long int a, b, c;
        int d;
        scanf("%d %lld %lld %lld",&d, &a, &b, &c);
        matriz[i][0] = d;

        for(int j = 1; j < N; j++){

            //di,j = (di,j−1 · ai + bi) mod ci
            matriz[i][j] = ((matriz[i][j-1] * a + b) % c);
        }

        qsort(matriz[i], N, sizeof(int), comparador);  //ordernar categoria por categoria
    }

    //criar árvore
    p_no raiz = NULL;

    //inserir elementos i na árvore
    for (int i = 0; i < N; i++){
        int chave = matriz[i][0];
        raiz = inserir(raiz, chave, i, 0);
    }

    menor_diferenca = obter_menor_diferenca(raiz);

    //loop

    p_no aux;
    int aux_cat, aux_pos = 0;

    while(1){

        //obter nova diferença e avançar

        aux = minimo(raiz);
        aux_cat = aux->categoria;
        aux_pos = aux->posicao;

        if(aux_pos == N-1) break;

        raiz = remove_minimo(raiz);
        raiz = inserir(raiz, matriz[aux_cat][aux_pos+1], aux_cat, aux_pos+1);

        int nova_diferenca = obter_menor_diferenca(raiz);
        menor_diferenca = (menor_diferenca < nova_diferenca ? menor_diferenca : nova_diferenca);
    }



    //imprime menor diferenca
    printf("%d\n", menor_diferenca);

    //libera matriz
    for (int i = 0; i < N; i++){
        free (matriz[i]) ;
    }
    free (matriz) ;

    liberar_arvore(raiz);

    return 0;
}