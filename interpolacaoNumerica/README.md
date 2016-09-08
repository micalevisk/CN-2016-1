Para compilar o código
======================

> **Usando o comando *make* na linha de comandos (no diretório em que o arquivo *makefile* está):**
> - Para exibir as instruções durante o uso do programa:
```bash
$ make # gerar o executável.
$ make all # idem.
$ make clean # apagar arquivos gerados pelo make.
$ make mostlyclean # deixar apenas o executável (apagando os demais arquivos gerados).
```

>- Para não exibir as instruções, i.e., caso um arquivo seja direcionado para a entrada padrão do programa:
```bash
## Basta acrescentar "AUTO=1" (sem aspas) nos comandos anteriores. Por exemplo,
$ make AUTO=1
```
