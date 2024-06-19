#!/bin/bash

# Limpa o cache do Nix para remover derivativos não utilizados
nix-collect-garbage -d

# Reconstrói o projeto usando nix-build
nix-build

# Executa o programa compilado após a reconstrução
./result/bin/main

