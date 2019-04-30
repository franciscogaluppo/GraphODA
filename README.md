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
