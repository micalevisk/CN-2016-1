#!/bin/bash

programa="./serieSeno_"
saida="$1"

[ $# -eq 1 ] && $($programa >> $saida)  || echo erro
