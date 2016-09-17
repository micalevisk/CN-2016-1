// Para ler um opção simples sem argumento.

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main (int argc, char **argv){
  int tflag = 0;
  int c;

  opterr = 0;
  while((c = getopt (argc, argv, "t:")) != -1){
    switch(c){
      case 't': tflag=1;  break;
      default:
        abort ();
      }
  }

  if(tflag) printf("TABELA ATIVADA\n");

  // LEITURA DOS ARGUMENTOS "NORMAIS":
  int index;
  for (index = optind-tflag; index < argc; index++)
    printf ("Argumento lido:|%s|\n", argv[index]);


  return 0;
}
