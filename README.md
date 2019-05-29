# 2019-1-grupo19
[![Build Status](https://travis-ci.com/pds2-dcc-ufmg/2019-1-grupo19.svg?token=Mnxg5DUtyLmLApyc8NAT&branch=master)](https://travis-ci.com/pds2-dcc-ufmg/2019-1-grupo19)

## Como instalar as dependências?
Um script simples para Ubuntu 18.04+
```bash
sudo add-apt-repository ppa:texus/tgui-0.8
sudo apt-get update
sudo apt-get install libsfml-dev libtgui-dev
```

## Como desenvolver localmente?
```bash
# Gere os scripts de compilação para sua plataforma
cmake CMakeLists.txt
# Compile
make
# Execute
./graphODA
```

## Como usar o REPL
O REPL possui dois tipos de comando: atribuição e operação.

### Atribuição

#### Atribuição de variável
```
>>> var1 = var2
```
A variável *var1* passa a representar o grafo representado por *var2*.

#### import
```
>>> var = import file_name
```
A variável *var* passa a representar o grafo armazenado em *file_name*. Se a leitura do arquivo falhar, *var* passa a representar um grafo vazio.

#### mst
```
>>> var1 = mst var2
```
A variável *var1* passa a representar a **árvore geradora mínima** do grafo representado por *var2*.

### Operação

#### describe
```
>>> var > describe
```
Exibe informações sobre o grafo representado por *var*.

#### show
```
>>> var > show
```
Exibe o grafo representado por *var*.

#### edit
```
>>> var > edit
```
Exibe o grafo representado por *var*, salvando as modificações efetuadas.

#### reaches
```
>>> var > reaches a b
```
Verifica se o vértice *a* alcança o vértice *b* no grafo representado por *var*.

#### scc
```
>>> var > scc
```
Exibe as componentes fortemente conexas do grafo representado por *var*.

#### shortestPath
```
>>> var > shortestPath a b
```
Computa o peso do caminho mínimo do vértice *a* para o vértice *b* no grafo representado por *var*.
