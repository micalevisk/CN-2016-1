##
##	[makefile]
##	Created by Micael Levi on 09/08/2016
##	Copyright (c) 2016 mllc@icomp.ufam.edu.br; All rights reserved.
##

#
# (em relacao ao arquivo makefile)
# MAIN		= nome do programa executavel
# CC		= comando para compilar (o arroba faz sumprimir a saida do make)
# CFLAGS	= flags para exibir as instrucoes
# SRCS		= nome dos arquivos de codigo-fonte com extensao .c
# OBJS		= nome dos objetos que serao gerados (extensao .o)
# $ make AUTO=1	[para nao exibir as instrucoes]
#

MAIN = formaDeNewton
CC = @gcc
CFLAGS = -w -g
SRCS = main.c
OBJS = $(SRCS:.c=.o)

AUTO = 0
MSGUSO1 = "USO: execute o programa \"$(MAIN)\" e siga as instrucoes."
MSGUSO2 = "USO: crie um arquivo texto com o formato:\n\
\nN\
\nX0 Y0\
\nX1 Y1\
\n...\
\nXn-1 Yn-1\
\n\nonde, N = quantidade de pontos.\
\nE execute na linha de comando: ./$(MAIN) < [arquivo criado]"

ifeq (0,${AUTO})
	MSGUSO = ${MSGUSO1}
else
	MSGUSO = ${MSGUSO2}
	CFLAGS += -D AUTO
endif

.PHONY: clean


$(MAIN): $(OBJS)
	$(CC) $(CFLAGS) -o  $@ $^
	@echo $(MSGUSO)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJS) $(MAIN)
	@echo "ARQUIVOS REMOVIDOS:\n$(OBJS) $(MAIN)"

clean-objs:
	@$(RM) $(OBJS)
	@echo "OBJETOS REMOVIDOS:\n$(OBJS)"