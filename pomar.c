/* Problema: recebemos uma toxicidade e um peso que avalia N^2 árvores dispostas no espaço em uma matriz NxN
 Queremos encontrar o menor caminho, coletando no máximo C amostras, mas maximizando a toxicidade 
//de nota, escolhendo um brinquedo de cada categoria
*/



#include <stdio.h>
#include <stdlib.h>




int main() {
    
    int n, c;
    scanf("%d %d", &n, &c);

    int **t, **p;
    t = (int **) malloc(n * sizeof(int *));
    p = (int **) malloc(n * sizeof(int *));
    for(int i = 0; i <n; ++i) {
        t[i] = (int *) malloc(n * sizeof(int));
        p[i] = (int *) malloc(n * sizeof(int));
    }

    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j)
            scanf("%d", &t[i][j]);

    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j)
            scanf("%d", &p[i][j]);


    
    // para exemplificar a saida
    int value = 42;
    char *solution = "CDDCBCBC";

    printf("%d\n%s\n", value, solution);

    return 0;
}