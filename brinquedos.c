 
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
    int chave, contagem;
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
 
p_no inserir_rec(p_no raiz, int chave)
{
 
    if (raiz->esq == NULL)
    {
    
        raiz->esq = raiz->dir = NULL;
        raiz->chave = chave;
        raiz->contagem = 1;
        raiz->cor = VERMELHO;

        return raiz;
    }
 
    if (chave < raiz->chave)
    {
        raiz->esq = inserir_rec(raiz->esq, chave);
    }
    else if (chave > raiz->chave)
    {
        raiz->dir = inserir_rec(raiz->dir, chave);
    }
    else if (raiz->chave == chave)
    {
        raiz->contagem += 1;
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
p_no inserir(p_no raiz, int chave)
{
    raiz = inserir_rec(raiz, chave);
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
        return maximo(raiz->esq);
    }
}
 
p_no rebalancear(p_no raiz)
{
    if (ehVermelho(raiz->esq) && ehVermelho(raiz->dir)) sobe_vermelho(raiz);
    if (ehVermelho(raiz->dir) && !ehVermelho(raiz->esq)) raiz = rotaciona_para_esquerda(raiz);
    if (ehVermelho(raiz->esq) && ehVermelho(raiz->esq->esq)) raiz = rotaciona_para_direita(raiz);
 
    return raiz;
}
 
//remove mínimo e balanceia
p_no remove_minimo(p_no raiz){
   
    if (raiz->esq == NULL) return NULL;
    if (!ehVermelho(raiz->esq) && !ehVermelho(raiz->esq->esq))
    raiz = rotaciona_para_esquerda(raiz);
    raiz->esq = remove_minimo(raiz->esq);
    return rebalancear(raiz);
}
 
 
//libera memória da árvore
void liberar_arvore(p_no raiz){
    if (raiz != NULL)
    {
        liberar_arvore(raiz->dir);
        liberar_arvore(raiz->esq);
        free(raiz);
    }
}
 
 
//devolve a diferença entre o maior e o menor elemento da árvore, todos os demais serão intermediários
int obter_menor_diferenca(p_no raiz){
    return (maximo(raiz)->chave - minimo(raiz)->chave);
 
}
 
 
//intercala do merge
void intercala(int v[], int esq, int m, int dir)
{
    int i, j, k;
    int n1 = m - esq + 1;
    int n2 = dir - m;
 
    //vetor temporário
    int Esq[n1], Dir[n2];
 
    //Copiar dados para vetores temporários da esq e da dir
    for (i = 0; i < n1; i++)
        Esq[i] = v[esq + i];
    for (j = 0; j < n2; j++)
        Dir[j] = v[m + 1 + j];
 
    //Intercala os vetores temporários de volta em v[l..r]*/
    i = 0;
    j = 0;
    k = esq;
 
    while (i < n1 && j < n2) {
        if (Esq[i] <= Dir[j]) {
            v[k] = Esq[i];
            i++;
        }
        else {
            v[k] = Dir[j];
            j++;
        }
        k++;
    }
 
    while (i < n1) {
        v[k] = Esq[i];
        i++;
        k++;
    }
 
    while (j < n2) {
        v[k] = Dir[j];
        j++;
        k++;
    }
}
 
//merge sort
void mergesort(int v[], int esq, int dir)
{
    if (esq < dir) {
       
        int m = esq + (dir - esq) / 2;
 
        mergesort(v, esq, m);
        mergesort(v, m + 1, dir);
 
        intercala(v, esq, m, dir);
    }
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

        int a, b, c, d;
        scanf("%d %d %d %d",&d, &a, &b, &c);
        //printf("%d, %d, %d, %d\n ", d, a, b, c);
        matriz[i][0] = d;


        for(int j = 1; j < N; j++){

            //di,j = (di,j−1 · ai + bi) mod ci
            matriz[i][j] = ((matriz[i][j-1] * a + b) % c);
        }
    };

    /*for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j ++){
            printf("%d ", matriz[i][j]);
        }
    }*/
    
   
    //ordernar categoria por categoria
    for(int i = 0; i < N; i++){
        mergesort(matriz[i], 0, N);
    };
 
    //criar árvore
    p_no raiz = malloc(sizeof(No));
    raiz->esq = NULL;
    raiz->dir = NULL;
 
    //inserir elementos i na árvore  
    for (int i = 0; i < N; i++){
        int chave = matriz[i][0];
        raiz = inserir(raiz, chave);
    }
 
    menor_diferenca = obter_menor_diferenca(raiz);
 
    //loop
    for (int i = 0; i < N; i++){
        for(int j = 1; j < N; j++){
           
            //remover minimo
            remove_minimo(raiz);
            raiz->cor = PRETO;
 
            //inserir no arvore chave matriz[i][j]
            inserir(raiz, matriz[i][j]);
 
            //refazer diferenca
            int nova_diferenca = obter_menor_diferenca(raiz);
            if (nova_diferenca < menor_diferenca){
                menor_diferenca = nova_diferenca;
            }
        }
    };
 
    //imprime menor diferenca  
    printf("A menor diferenca é %d\n", menor_diferenca);
 
    //libera matriz
    for (int i = 0; i < N; i++){
         free (matriz[i]) ;
    }
    free (matriz) ;
 
 
    return 0;
}

