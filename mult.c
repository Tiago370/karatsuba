#include <stdio.h> 
#include <stdlib.h>
#include <math.h>
#include <assert.h>
typedef struct fator{
    int n;
    char* V;
}fator;
typedef struct produto{
    char d;
    char c;
}produto;
void intTocadeia(int n, fator *F);
int contarDigitos(int a);
int cadeiaToInt(fator *F);
char intToChar(int i);
void padronizar(fator *F, int n);
produto setProduto(int n, int m){
    produto P;
    int p = n*m;
    P.d = intToChar(p%10);
    P.c = intToChar(floor(p/10));
    return P;
}
fator* newFator(int n){
    fator* F = (fator*) malloc(sizeof(fator));
    F->n = n;
    F->V = (char*) malloc(n*sizeof(char));
    for(int i = 0; i < F->n; i++){
        F->V[i]= '0';
    }
    return F;
}
void liberar(fator *F){
    free(F->V);
    free(F);
}
void setV(fator* F, char* V){
    for(int i = 0; i < F->n; i++){
        F->V[i] = V[i];
    }
}
void divide(fator* F, fator* A, fator* B){
    //assert(1 == 2);
    //assert(F->n == B->n*2);
    
    if(F->n%2 == 1){
        padronizar(A, ceil(F->n/2));
        padronizar(B, floor(F->n/2));
    }else{
        padronizar(A, F->n/2);
        padronizar(B, F->n/2);
    }

    for(int i = 0; i < B->n; i++){
        B->V[i] = F->V[i];
    }
    for(int i = 0; i < A->n; i++){
        A->V[i] = F->V[i+B->n];
    }
}
char intToChar(int i){
    assert(i < 10);
    assert(i >= 0);
    return 48+i;
}
int charToInt(char c){
    int i = c-48;
    assert(i < 10);
    assert(i >= 0);
    return i;
}

void print(fator* F){
    int flag = 0;
    for(int i = 0; i < F->n; i++){
        if(F->V[i] != '0'){
            flag = 1;
        }
    }
    if(flag){
        int a = F->n-1;
        while(F->V[a] == '0') a--;
    
        for(int i = a; i >= 0; i--){
            printf("%c", F->V[i]);
        }
        printf("\n");
    
    }else{
        printf("%c\n", '0');
    }
}

void printFull(fator* F){
    printf("n = %d\n", F->n);
    for(int i = F->n - 1; i >= 0; i--){
        printf("%c", F->V[i]);
    }
    printf("\n");

}

void casoBase(fator *F,fator *G,fator *H){
    assert(F->n + G->n <= 8);
    int f = cadeiaToInt(F);
    int g = cadeiaToInt(G);
    int c = f*g;
    intTocadeia(c, H);
    return;
}
void casoBase2(fator *F,fator *G,fator *H){
    assert(F->n == 3);
    assert(G->n == 3);
    assert(H->n == 6);
    int a = charToInt(F->V[2]); // encontrar 'a'
    int b = charToInt(F->V[0])+charToInt(F->V[1])*10; // encontrar 'b'
    int c = charToInt(G->V[2]); // encontrar 'c'
    int d = charToInt(G->V[0])+charToInt(G->V[1]*10); // encontrar 'd'
    int ac = a*c; // calcular 'ac'
    int bd = b*d; // calcular 'bd'
    int x = (a+b)*(c+d); // calcular 'x'
    int e = x - ac - bd; // calcular 'e'
    assert(e >=0);
    int r = trunc(ac*1000 + bd + e*19.95262315); // calcular 'r'
    int aux = r;
    int cont = -1; //Contar zeros a esquerda
    while(aux <= 999999){
        cont++;
        aux = aux*10;
    }
    
    aux = 6 - cont;
    
    H->V[0] = intToChar(r%10);
    H->V[1] = intToChar((int)floor((r%100)/10));
    H->V[2] = intToChar((int)floor((r%1000)/100));
    H->V[3] = intToChar((int)floor(r%10000/1000));
    H->V[4] = intToChar((int)floor(r%100000/10000));
    H->V[5] = intToChar((int)floor(r/100000));
    padronizar(H, aux);
}

//faz um shift de tamanho sh para a esquerda em um fator
void shift(int sh, fator * F){
    int a = 0; //zeros à esquerda
    while(F->V[F->n-1-a] == '0') a++;
    if(sh > a){
        padronizar(F, (F->n)+sh-a);
    }
    for(int i = 0; i < sh; i++){
        for(int j = F->n-1 ; j >= 0; j--){ //009876543210
                                           //098765432110
            F->V[j] = F->V[j-1];           //987654321000
        }
    }
    for(int i = 0; i < sh; i++){
        F->V[i] = '0';
    }
}

void padronizar(fator *F, int n){
    char *C = F->V;
    F->V = (char*) malloc(n * sizeof(char));
    for(int i = 0; i < F->n; i++){
        F->V[i] = C[i];
    }
    free(C);
    for(int i = F->n; i < n; i++){
        F->V[i] = '0';    
    }
    F->n = n;
}
void subtrair(fator *F,fator *G,fator *H){ // F-G
    //deixar os fatores F, G e H com o mesmo número de dígitos
    if(F->n == G->n){
        if(H->n != F->n){
            padronizar(H, F->n);
        }
    }else{
        if(F->n > G->n){
            padronizar(G, F->n);
        }else{
            padronizar(F, G->n);
        }
        padronizar(H, F->n);
    }
        for(int i = 0; i < F->n; i++){
            int a = charToInt(F->V[i]);
            int b = charToInt(G->V[i]);
            int r = a-b;
            if(r >= 0){
                H->V[i] = intToChar(r);            
            }else{
                H->V[i] = intToChar(a+10-b);
                int ce = 1; //casas a esquerda
                while(F->V[i+ce] == '0') ce++;
                F->V[i+ce]--;
            }
        }    
}
int cadeiaToInt(fator *F){
    int acm = 0;
    for(int i = 0; i < F->n; i++){
        acm+= charToInt((int) F->V[i])*pow(10,i);
    }
    return acm;
}
void intTocadeia(int n, fator *F){
    padronizar(F, contarDigitos(n));

    for(int i = 0; i < F->n; i++){
            int d =  (n % (int)pow(10,i+1))/pow(10,i);
            F->V[i] = intToChar(d);
        }
}

int maior(int a, int b){
    if(a > b){
        return a;
    }else{
        return b;
    }
    return 0;
}
void somar(fator *F,fator *G,fator *H){
    //deixar os fatores F e G com o mesmo número de dígitos e o tamanho de H excedendo o tamanho de F em 1

    if(F->n + G->n <= 8){
        int a = cadeiaToInt(F);
        int b = cadeiaToInt(G);
        int c = a + b;
        intTocadeia(c, H);
        return;
    }
    padronizar(H, maior(F->n,G->n)+1);
    for(int i = 0; i < F->n; i++){
        
        int a = charToInt(F->V[i]);
        int b = charToInt(G->V[i]);
        int c = charToInt(H->V[i]);
        H->V[i] = intToChar((a+b+c)%10);
        H->V[i+1] = intToChar((int)floor((a+b+c)/10));
    }
}
int contarDigitos(int a){
    int count = 0;
    while(a > 0){
        a = floor(a/10);
        count++;
    }
    return count;
}
void mult_div_conq(fator *F,fator *G,fator *H){
    //getchar(); 
    //printFull(F);    
    //printFull(G);
    //printf("\n");
//deixar os fatores F e G com o mesmo número de dígitos e H com o dobro de F

    //Caso base
    if(F->n + G->n <= 8){
        casoBase(F, G, H);
        return;
    }

    if(F->n == G->n){
        padronizar(H, 2*F->n);
    }else{
        if(F->n > G->n){
            padronizar(G, F->n);
        }else{
            padronizar(F, G->n);
        }
        padronizar(H, 2*F->n);
    }
          
    fator *A = newFator(1);
    fator *B = newFator(1);
    fator *C = newFator(1);
    fator *D = newFator(1);
    divide(F, A, B);
   
    divide(G, C, D);
    printf("A\n");
    print(A);
    printf("B\n");
    print(B);
    fator *AC = newFator(1);
    // calcular 'AC'
    mult_div_conq(A, C, AC);
    fator *BD = newFator(1);
    // calcular 'BD'
    mult_div_conq(B, D, BD);
    //Soma A+B
    fator *AmaisB = newFator(1);
    somar(A, B, AmaisB);
    liberar(A);
    liberar(B);
    //Soma C+D
    fator *CmaisD = newFator(1);
    somar(C, D, CmaisD);
    liberar(C);
    liberar(D);

    // calcular 'X'
    fator *X = newFator(1);
    mult_div_conq(AmaisB, CmaisD, X);
    
    // calcular 'E1'
    fator *E1 = newFator(1);
    subtrair(X, AC, E1);
    // calcular 'E2'
    fator *E2 = newFator(1);
    subtrair(E1, BD, E2);
    // calcular 'R1'
    shift(F->n, AC);
    fator *R1 = newFator(1);
    somar(AC, BD, R1);
    // calcular 'H'
    shift(F->n/2, E2);
    somar(R1, E2, H);

    // Limpar a bagunça
    liberar(AC);
    liberar(BD);
    liberar(AmaisB);
    liberar(CmaisD);
    liberar(X);
    liberar(E1);
    liberar(E2);
    liberar(R1);
    return;
}
int main(){
    int n;
    scanf("%d",&n);
    getchar();
    fator *F, *G, *H;
    char *X = (char*) malloc(n * sizeof(char));
    char aux;
    for(int i = n-1; i >= 0; i--){
        scanf("%c", &aux);
        X[i] = aux;
    }
    getchar();
    F = newFator(n);
    setV(F, X);
    for(int i = n-1; i >= 0; i--){
        scanf("%c", &aux);
        X[i] = aux;
    }
    G = newFator(n);
    setV(G, X);
    free(X);
    H = newFator(2*n);
    mult_div_conq(F, G, H);
    //casoBase(F, G, H);
    //printFull(F);
    //padronizar(F, 4);
    //somar(F, G, H);
    //subtrair(F,G,H);
    //printFull(F);
    print(H);

    return 0;
}
