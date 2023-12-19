DESCRIÇÃO:

        Implementação de estruturas de dados e operações para manipular a imagem (.iso) de um sistema de arquivos EXT4. 
        As operações deverão ser invocadas a partir de um prompt (shell).

    AUTORES:
        RAFAEL MACHADO WANNER
        DANILO BALMAN GARCIA
        LUIZ FELIPE CORUMBA SILVA

    DATA DE CRIAÇÃO:
        06/12/2023

    DATA DE ATUALIZAÇÃO:
        14/12/2023

Para compilar e Executar:

    Para compilar
        make compile

    Para executar com arquivo 1k
        make exec1k

    Para executar com arquivo 2k
        make exec2k
            ou 
        make

    Para executar com arquivo 4k
        make exec4k

    Para excutar com outro arquivo
        ./ext_4_estrutura nome_do_arquivo

Comandos implementados:

    (1) info: exibe informações da imagem e do sistema de arquivos.
    (2) cat <file>: exibe o conteúdo de um arquivo no formato texto.
    (3) attr <file | dir>: exibe os atributos de um arquivo (file) ou diretório (dir).
    (4) cd <path>: altera o diretório corrente para o definido como path.
    (5) ls: lista os arquivos e diretórios do diretório corrente.
    (6) testi <inode_number>: verifica se um inode está livre ou ocupado.
    (7) testb <block_number>: verifica se um bloco está livre ou ocupado.
    (8) export <source_path> <target_path>: copia arquivo da imagem (source_path) para destino (target_path) no
    sistema operacional da máquina.
    (9) pwd: exibe o diretório corrente (caminho absoluto).

<iostream>
    
        Descrição: Fornece funcionalidades básicas de entrada e saída em C++. Possibilita a leitura de dados do usuário através do teclado (std::cin) e a exibição de dados na tela (std::cout).

<fstream>
    
        Descrição: Oferece funcionalidades para operações de entrada e saída em arquivos. Permite a abertura, leitura, escrita e fechamento de arquivos.

<cmath>
    
        Descrição: Biblioteca padrão de matemática em C++. Oferece funções matemáticas comuns, como cálculo de raiz quadrada, exponenciação, funções trigonométricas, entre outras.

<iomanip>
    
        Descrição: Fornece manipuladores que controlam a formatação de saída em C++. Permite controlar a formatação de números, alinhamento de saída, precisão decimal, entre outros.

<vector>
    
        Descrição: Implementa uma estrutura de dados de vetor dinâmico em C++. Permite criar arrays dinâmicos que podem crescer em tamanho automaticamente conforme necessário.

<cstring>
    
        Descrição: Fornece funções para manipulação de strings em estilo C. Oferece operações comuns, como cópia, concatenação, comparação e busca em strings.

<cstdint>
    
        Descrição: Fornece definições de tipos inteiros com tamanhos específicos em C++. Oferece tipos de inteiros com precisão conhecida, como inteiros de 8, 16, 32 e 64 bits.
