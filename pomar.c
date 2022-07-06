/* Problema: recebemos uma toxicidade e um peso que avalia N^2 árvores dispostas no espaço em uma matriz NxN
 Queremos encontrar o menor caminho, coletando no máximo C amostras, mas maximizando a toxicidade 
//de nota, escolhendo um brinquedo de cada categoria
*/



#include <stdio.h>
#include <stdlib.h>



int max(int a, int b, int c, int d){

    if(a > b && a > c  && a > d)
        return a;
    else if (b > a && b > c && b> d ) 
        return b; 
    else if(c > a && c > b && c > d) 
        return c;
    else
        return d;

}

int mochilacaminho(int i, int j, int c, int ** p, int ** t, int *** m){
    //caso base 
    //i e j menor que 0, sai da matrizs, ou capacidade negativa
    if((i < 0 && j < 0) || (c < 0) ){
        return NULL; 
    }

    //i e j erem iguais a zero -> voltar recursao
    if(i == 0 && j == 0){
        return t[0][0];
    }

    //recursão 

    if (m[i][j][c] != -1){
        return m[i][j][c];
    }
    
    int npd, npb, pd, pb;
    //qdo pega -> C = C - peso 
    //qdo pega 

    //i mantem, j + 1
    npd = mochilacaminho(i, j +1, c, p, t, m); 
    pd = mochilacaminho(i, j+1, c + p[i][j], p, t, m) + t[i][j];

    //j mnatem, i aumenta 
    npb = mochilacaminho(i+1, j, c, p, t, m);
    pb = mochilacaminho(i+1, j, c, p, t, m) + t[i][j];

    int maximo =  max(npd, npb, pd, pb);

    if(maximo == npd){
        m[i][j][c] = npd; 
    }
    else if (maximo == npb){
        m[i][j][c] = npb;
    }
    else if (maximo == pd){
        m[i][j][c] = pd;
    }
    else{
        m[i][j][c] = pb;
    }

    return maximo;

}

void imprimeCaminho(int i, int j, int c, int **p, int **t, int ***m){
    
    if((i < 0 && j < 0) || (c < 0) ){
        return NULL; 
    }

    //i e j erem iguais a zero -> voltar recursao
    if(i == 0 && j == 0){
        printf("x"); 
    }



    int npd, npb, pd, pb, atual; 

    //calcula atual na mochilacaminho 
    atual = mochilacaminho(i, j, c, p, t, m);

    //calcula 4 casos de cima e achar igual ao atual e chamar recursao p o anterior

    npd = mochilacaminho(i, j +1, c, p, t, m); 
    pd = mochilacaminho(i, j+1, c + p[i][j], p, t, m) + t[i][j];
    npb = mochilacaminho(i+1, j, c, p, t, m);
    pb = mochilacaminho(i+1, j, c, p, t, m) + t[i][j];


    if(pd == atual){
        imprimeCaminho(i, j-1, c - p[i][j], p, t, m);
        //passo antetior foi coletar e direita, CD
        printf("CD");
    }
    else if(npd == atual ){
        imprimeCaminho(i, j-1, c, p, t, m);
        //D
         printf("D");
    }
    else if(pb == atual){
        imprimeCaminho(i+1, j, c - p[i][j], p, t, m);
        //CB
         printf("CB");
    }
    else if (npb == atual){
        imprimeCaminho(i+1, j, c, p, t, m);
        //B
         printf("B");
    }

}


int main() {
    
    //n é dimensão da matriz
    //c é capacidade da mochila 
    int n, c;
    scanf("%d %d", &n, &c);
    
    //aloca matrizes
    int **t, **p;
    t = (int **) malloc(n * sizeof(int *));
    p = (int **) malloc(n * sizeof(int *));
    for(int i = 0; i <n; ++i) {
        t[i] = (int *) malloc(n * sizeof(int));
        p[i] = (int *) malloc(n * sizeof(int));
    }

    // lê t, matriz de toxicidade 
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j)
            scanf("%d", &t[i][j]);

    //lê p, matriz de peso
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j)
            scanf("%d", &p[i][j]);

    //aloca uma mem nxnxc de valores já calculados, evitar algoritmo guloso
    int ***m; 
    m = (int ***) malloc(n * sizeof(int **));

    for(int i = 0; i <n; ++i) {
        m[i] = (int **) malloc(n * sizeof(int *));
        for (int j = 0; j < n; ++j){
             m[i][j] = (int *) malloc(c * sizeof(int));  
             for(int k = 0; k < c; k++){
                m[i][j][k] = -1;
             }   
        }
    }
    

    printf("%d\n", mochilacaminho(n-1, n-1, c, p, t, m));

    imprimeCaminho(n-1, n-1, c, p, t, m); 
    printf("\n"); 
    return 0;

}