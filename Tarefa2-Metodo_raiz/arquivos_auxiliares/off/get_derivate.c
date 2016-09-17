/* DEVE ESTAR NO FORMATO: <sinal><coeficiente><variavel>^<expoente><espaço>... */
#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

#define delimiter "x^ "
#define STRING  argv[1]
unsigned args=0;

#define foreach(v, n) { unsigned i; for(i=0; i < n; i+=2) printf("%+dx^%d ", v[i], v[i+1]); }

int* parserSimples(char* string){
    char *salvo = malloc(sizeof(char)*(strlen(string)+1));
    strcpy(salvo, string);
    char* bff;
    unsigned qtdCapturados=0, i;

    bff = strtok(string, delimiter);
    while(bff!=NULL){
        ++qtdCapturados;
        bff = strtok(NULL, delimiter);
    }

    if(qtdCapturados%2) qtdCapturados--;
    int* valores = malloc(sizeof(int)*qtdCapturados);
    bff = strtok(salvo, delimiter);
    for(i=0; (bff!=NULL) && (i < qtdCapturados); ++i){
        valores[i] = atoi(bff);
        // printf(">> %s\n", bff);
        bff = strtok(NULL, delimiter);
    }
    
	args = qtdCapturados;
    free(salvo);     
    return valores;
}

// [an,n, ...] onde n é o grau 
void derivar(int* funcao){
	unsigned i;
	for(i=0; i < args; i+=2){
		funcao[i] *= funcao[i+1];
		funcao[i+1]--;
	}

}

int main (int argc, char** argv){
	if(argc!=2){ fprintf(stderr, "o polinômio deve ser passado!\n"); return 1; }
    // char string[] = "-12x^-3 -6x^-2 +0x^-1 +9";
    char* string = malloc(sizeof(char)*(strlen(STRING)+1));
    strcpy(string, STRING);
    int i;

    printf("\nP(X) = ");
    int* valoresSalvos = parserSimples(string); // ==> [-12,-3, -6,-2, 0,-1]
    foreach(valoresSalvos, args);
    // for(i=0; i < args; i+=2) printf("%+dx^%d ", valoresSalvos[i], valoresSalvos[i+1]);

    printf("\nP'(X) = ");
    derivar(valoresSalvos);
    foreach(valoresSalvos, args);


 
    return 0;
}