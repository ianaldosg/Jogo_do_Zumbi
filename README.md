# Jogo do Zumbi 🧟‍♂️

Este projeto é um jogo top-down desenvolvido em C++ utilizando a biblioteca SDL2. O repositório foi criado para fins acadêmicos e de aprendizado prático em desenvolvimento de engines e jogos na matéria de **Introdução ao Desenvolvimento de Jogos (IDJ)** da **Universidade de Brasília (UnB)**.

---

## 🎮 Sobre o Jogo

O projeto consiste em um jogo de sobrevivência onde o jogador deve enfrentar hordas progressivas de inimigos através de um sistema de gerenciamento de ondas (*WaveSpawner*). O motor do jogo foi construído do zero seguindo o padrão de arquitetura baseada em Componentes e GameObjects.

---

## 🛠️ Requisitos do Sistema e Dependências

Para compilar e executar este projeto, o seu ambiente precisa contar com ferramentas de compilação C++ modernas e as bibliotecas de desenvolvimento da **SDL2** e do **Valgrind/Cppcheck** instaladas.

### 1. Ferramentas de Compilação
* **Compilador C++:** GCC (g++) versão 11 ou superior, Clang versão 12 ou superior (com suporte a C++11).
* **Gerenciador de Build:** GNU Make.

### 2. Bibliotecas SDL2 (Pacotes de Desenvolvimento `-dev` ou `-devel`)
* **SDL2** (Core da biblioteca gráfica)
* **SDL2_image** (Carregamento de texturas PNG)
* **SDL2_mixer** (Gerenciamento de efeitos sonoros e músicas)
* **SDL2_ttf** (Renderização de fontes de texto)

### 3. Ferramentas de Diagnóstico
* **Valgrind:** Para análise de vazamento de memória em tempo de execução (*Memory Leaks*).
* **GDB:** Para depuração de falhas de segmentação (*Segmentation Faults*).
* **Cppcheck:** Para análise estática de qualidade de código.

---

## 🚀 Como Compilar e Rodar

O projeto utiliza um arquivo `makefile` para automatizar o processo de compilação dos binários e gerenciamento das flags de debug.

### 1. Limpar compilações antigas (Recomendado)
Antes de compilar pela primeira vez ou após grandes mudanças estruturais, limpe o cache de objetos binários antigos:
```bash
make clean
```

### 2. Compilar o Projeto
Para gerar o executável final do jogo, execute o comando make na raiz do diretório:
```bash
make
```

### 3. Rodar o Jogo
Após a compilação finalizar com sucesso, execute o binário gerado:
```bash
./JOGO
```

---

## 🔬 Debug, Análise de Memória e Análise Estática (Valgrind & GDB & Cppcheck)

Para fins de avaliação de arquitetura, o projeto foi validado contra vazamentos usando ferramentas de análise dinâmica.

### Executar Varredura de Memory Leaks:
```bash
valgrind --leak-check=full --show-leak-kinds=all ./JOGO
```

### Executar em Modo de Depuração (GDB):
```bash
gdb ./JOGO
```

#### Para rodar a análise completa no projeto:
```bash
cppcheck --enable=all --suppress=missingIncludeSystem src/ include/
```

---

## 🕹️ Controles do Jogo

* **W, A, S, D:** Movimentação do personagem principal.
* **Mouse:** Mira e direção dos disparos.
* **Clique Esquerdo:** Atirar.
* **ESC:** Sair do jogo imediatamente.
