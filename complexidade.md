# Análise de Complexidade 

## Problema: Brinqudos da SBC

Nicolau é um grande inventor e artesão de brinquedos. Ele é o criador de N tipos de brinquedos, e para cada tipo ele possui N brinquedos fabricados. Cada brinquedo pertence a somente um tipo. Nicolau também se atenta com o quão divertido seus brinquedos são, e por isso ele atribui para cada brinquedo j um valor de diversão dj com base nos feedbacks que recebe.

Um dia, ele recebeu um pedido especial da Sociedade de Brinquedos para Crianças (SBC). A SBC está em busca de novos brinquedos para seu próximo evento, e deseja adquirir N brinquedos de Nicolau. Porém, a SBC quer uma boa variedade de brinquedos, e por isso ela deseja um brinquedo de cada tipo. Além disso, é muito importante que um brinquedo não seja muito mais divertido do que os outros, pois faria com que as crianças brigassem por esse brinquedo e perdessem o interesse nos outros. 

Com isso, Nicolau precisa entregar N brinquedos, um de cada tipo, de forma que a diferença entre os valores de diversão do brinquedo mais divertido e do menos divertido seja a menor possível. Como Nicolau possui muitos brinquedos e o evento da SBC está próximo, ele pede a sua ajuda para determinar rapidamente qual é essa diferença.

### Entrada 

A primeira linha contém o inteiro N. As N linhas seguintes descrevem os valores dos brinquedos de cada tipo. A i-ésima linha possui quatro inteiros: di,1, ai, bi e ci, respectivamente. O inteiro di,1 representa o valor de diversão do primeiro brinquedo, e o valor do j-ésimo brinquedo para 2 ≤ j ≤ N  ́e dado por di,j = (di,j−1 · ai + bi) mod ci. 


### Saída 

A **menor diferença possível** entre os valores de diversão dos brinquedos, respeitando as condições da SBC. 

## Resumo da Solução 

Em primeiro lugar, alocamos uma matriz NxN para comportar as notas de diversão de todos os brinquedos. Lendo entrada Nx4 com os valores d, a, b e c de cada categoria, cada linha foi montada de acordo com a fórmula dada e logo em seguida ordenada.

A partir daqui, foi usada a estrutura de dados da **árvore rubro negra**. Importante ressaltar que como trata-se de uma árvore balanceada, ela realiza as oprações $inserir$ e $remover$ em ordem de **log n**. 

Assim, inserimos os primeiros elementos de cada categoria na árvore, cujo nó é dado pela struct: 

```C
typedef struct No
{
    int chave, categoria, posicao;
    enum Cor cor;
    struct No *esq, *dir;
} No;

typedef No *p_no;
```

Para a chave, passamos a nota de diversão do brinquedos; para a categoria, a linha i da matriz NxN; e para a posição, a coluna j da matriz NxN. 

Depois disso, calculamos a menor diferença até então usando

```C
int obter_menor_diferenca(p_no raiz){
    return (maximo(raiz)->chave - minimo(raiz)->chave);
}
```

Depois, seguimos removendo o mínimo da árvore e adicionando o próximo elemento de sua categoria, até chegar ao final de uma das categorias, obtendo a menor diferença calculada até então. 

## Complexidade 

As principais funções, de maior complexidade no algoritmo, são o a ordenação das notas dos brinquedos e o loop que calcula a menor diferença entre os brinquedos na árvore. 

### Parte 1 
```C
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
```

O qsort tem complexidade **n*logn**. Assim, como a operação de ordenação é repetida para cada uma das N linhas, temos que esse trecho do código tem a complexidade 

$$C_1 * N^2 * logn$$

### Parte 2 

```C
while(1){
        aux = minimo(raiz); //log n
        aux_cat = aux->categoria;
        aux_pos = aux->posicao;

        if(aux_pos == N-1) break;

        raiz = remove_minimo(raiz); //log n 
        raiz = inserir(raiz, matriz[aux_cat][aux_pos+1], aux_cat, aux_pos+1); //log n

        int nova_diferenca = obter_menor_diferenca(raiz);   //c*log n
        menor_diferenca = (menor_diferenca < nova_diferenca ? menor_diferenca : nova_diferenca);
    }
```

Sabendo que, no pior caso, os últimos elementos de cada categoria vão compor a combinação onde existe a menor diferença entre eles, temos um algoritmo que repete todas as instruções dentro do loop $N^2$ vezes. 

Considerando que há algumas atribuições de váriaveis, ou seja, operações de tempo constante c e algumas operações de ordem de log n, no pior caso temos 

$$C_2 * N^2 * log n + C_3 * N^2 * c$$


Dessa forma, , juntando as partes 1 e 2, temos 

$$C_1 * N^2 * logn + C_2 * N^2 * log n + C_3 * N^2 * c$$ 


Como $O(N^2 * log n) > O(N^2 * c)$, concluí-se que a complexidade dessa solução é 

$$ O(N^2 log n)$$




