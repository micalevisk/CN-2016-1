Para compilar e executar o programa
==============================

> **Usando o comando *make* na linha de comandos (no diretório em que o arquivo _makefile_ está):**
> - Para exibir as instruções durante o uso do programa:
```bash
$ make # gerar o executável.
$ make all # idem.
$ make clean # apagar arquivos gerados pelo make.
$ make mostlyclean # deixar apenas o executável (apagando os demais arquivos gerados).
```

>- Para não exibir as instruções, i.e., caso um arquivo seja direcionado para a entrada padrão do programa:
```bash
## Basta acrescentar _AUTO=1_ nos comandos anteriores. Por exemplo,
$ make AUTO=1
```
