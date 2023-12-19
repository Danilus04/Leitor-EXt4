#ifndef SHELL_H_INCLUDED
#define SHELL_H_INCLUDED

#include <iostream>
#include "ext4_estrutura.hpp"

class shell
{
private:
    std::string diretorio_atual;
    sistema_de_arquivo* sis;

public:
    /*
    DESCRIÇÃO:
        Inicializa uma instância da classe 'shell', configurando o diretório atual como "root/" e 
        criando um objeto 'sistema_de_arquivo' utilizando o arquivo especificado.

    PARAMETROS DE ENTRADA:
        nome_arquivo - Nome do arquivo a ser utilizado para inicializar o sistema de arquivos.

    PARÂMETROS DE SAÍDA:
        Cria uma instância da classe 'shell' com o diretório atual definido como "root/" e um objeto 
        'sistema_de_arquivo' inicializado com o arquivo fornecido.
    */
    shell(std::string);
    /*
    DESCRIÇÃO:
        Destrutor da classe 'shell' responsável por liberar a memória alocada para o objeto 'sistema_de_arquivo'
        quando uma instância da classe 'shell' é destruída.

    PARÂMETROS DE ENTRADA:
        Não há parâmetros de entrada explícitos.

    PARÂMETROS DE SAÍDA:
        Libera a memória alocada para o objeto 'sistema_de_arquivo' associado à instância da classe 'shell'
        quando a instância é destruída.
    */
    ~shell();
    /*
    DESCRIÇÃO:
        Mapeia um comando de texto digitado pelo usuário para um número inteiro, facilitando seu uso em uma estrutura de controle.

    PARAMETROS DE ENTRADA:
        commandEntered - Comando digitado pelo usuário em formato de string.

    PARÂMETROS DE SAÍDA:
        Retorna um número inteiro correspondente ao comando digitado. Caso o comando não seja reconhecido, retorna -1.
        Os comandos reconhecidos estão mapeados da seguinte forma:
        0: "exit", 1: "info", 2: "cat", 3: "attr", 4: "cd", 5: "ls", 6: "testi", 
        7: "testb", 8: "export", 9: "pwd", 10: "touch", 11: "mkdir", 12: "rm", 
        13: "cd.." ou "cd/..", 14: "rmdir", 15: "rename", 16: "help"
    */
    short getCommandNumber(std::string commandEntered);
    /*
    DESCRIÇÃO:
        Executa comandos específicos fornecidos pelo usuário.

    PARAMETROS DE ENTRADA:
        commandEntered - Comando digitado pelo usuário em formato de string.

    PARÂMETROS DE SAÍDA:
        Retorna 0 ao finalizar a execução do comando.

    COMANDOS IMPLEMENTADOS:
        - "exit": Retorna -1 indicando o término da execução.
        - "info": Chama o método 'info' do objeto 'sis' (sistema_de_arquivo).
        - "cat": Lê um nome de arquivo da entrada padrão (cin) e chama o método 'ler_arquivo' do objeto 'sis'.
        - "attr": Lê um nome de arquivo da entrada padrão (cin) e chama o método 'print_info' do objeto 'sis'.
        - "cd": Lê um diretório da entrada padrão (cin), realiza a navegação no sistema de arquivos e atualiza o diretório atual.
        - "ls": Chama o método 'list_dir' do objeto 'sis'.
        - "testi" e "testb": Realiza testes nos bits de inodes e blocos, respectivamente.
        - "export": Lê dois nomes de arquivos da entrada padrão (cin) e chama o método 'exportar_arquivo' do objeto 'sis'.
        - "pwd": Exibe o diretório de montagem atual combinado com o diretório atual da shell.
        - "cd.." ou "cd/..": Navega para o diretório pai (um nível acima) no sistema de arquivos.
        - "help": Exibe informações de ajuda.
    */
    int executeCommand(std::string commandEntered);
    /*
    DESCRIÇÃO:
        Exibe informações de ajuda, fornecendo detalhes sobre os comandos disponíveis na shell.

    PARÂMETROS DE ENTRADA:
        Não há parâmetros de entrada explícitos.

    PARÂMETROS DE SAÍDA:
        Não há parâmetros de saída explícitos.

    COMANDOS DISPONÍVEIS NA SHELL (EXEMPLOS):
        - "info": Exibe informações da imagem e do sistema de arquivos.
        - "cat <file>": Exibe o conteúdo de um arquivo no formato texto.
        - "attr <file | dir>": Exibe os atributos de um arquivo ou diretório.
        - "cd <path>": Altera o diretório corrente para o definido como path.
        - "ls": Lista os arquivos e diretórios do diretório corrente.
        - "testi <inode_number>": Verifica se um inode está livre ou ocupado.
        - "testb <block_number>": Verifica se um bloco está livre ou ocupado.
        - "export <source_path> <target_path>": Copia arquivo da imagem para o sistema operacional da máquina.
        - "pwd": Exibe o diretório corrente (caminho absoluto).

        (Comandos comentados não estão atualmente disponíveis na shell.)
    */
    void printHelp(void);
    /*
    DESCRIÇÃO:
        Inicia o loop principal da shell, aguardando comandos do usuário.

    FUNCIONAMENTO:
        - Exibe o diretório atual seguido por um prompt de comando ([$]>).
        - Lê o comando inserido pelo usuário na entrada padrão (cin).
        - Executa o comando inserido utilizando o método 'executeCommand'.
        - Se o comando for "exit" (retorna -1), encerra o loop e a execução da shell.

    OBSERVAÇÃO:
        - Este loop mantém a execução da shell ativa, aguardando comandos do usuário continuamente.
    */
    void start_loop();
};

#endif 