#ifndef SHELL_C_INCLUDED
#define SHELL_C_INCLUDED
#include <iostream>
#include "shell.hpp"
#include "ext4_estrutura.hpp"

using namespace std;

    /*
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
    */

shell::shell(std::string nome_arquivo)
{
    this->diretorio_atual = "root/";
    this->sis = new sistema_de_arquivo(nome_arquivo);
}

shell::~shell()
{
    delete this->sis;
}

short shell::getCommandNumber(std::string commandEntered)
{
    if(commandEntered == "exit")
        return 0;
    else if(commandEntered=="info")
        return 1;
    else if(commandEntered== "cat")
        return 2;
    else if(commandEntered== "attr")
        return 3;
    else if(commandEntered== "cd")
        return 4;
    else if(commandEntered=="ls")
        return 5;
    else if(commandEntered== "testi")
        return 6;
    else if(commandEntered== "testb")
        return 7;
    else if(commandEntered== "export")
        return 8;
     else if(commandEntered== "pwd")
        return 9;
    else if(commandEntered== "touch")
        return -1;
    else if(commandEntered== "mkdir")
        return -1;
    else if(commandEntered== "rm")
        return -1;
    else if(commandEntered=="cd.."|| commandEntered== "cd/..")
        return 13;
    else if(commandEntered== "rmdir")
        return -1;
    else if(commandEntered== "rename")
        return -1;
    else if(commandEntered== "help")
        return 16;
    else
        return -1;
}

int shell::executeCommand(std::string commandEntered)
{
    int int_aux;
    int int_aux2=0;
    std::string comando_aux;
    std::string comando_aux2;
    switch(getCommandNumber(commandEntered))
        {
            case 0:
                return -1;
            case 1:
                sis->info();
                break;
            case 2:
                cin >> comando_aux;
                sis->ler_arquivo(comando_aux);
                break;
            case 3:
                cin >> comando_aux;
                this -> sis -> print_info(comando_aux);
                break;
            case 4:
                cin >> comando_aux;
                //cout << comando_aux << endl;
                if(this->diretorio_atual == "root/" && comando_aux == "..")
                    break;
                int_aux = sis->procurar_por_pasta(comando_aux);
                if(int_aux){
                    sis->set_inode_atual(int_aux);
                    if(comando_aux == ".."){
                        this->diretorio_atual.pop_back();
                        while(this->diretorio_atual[this->diretorio_atual.size() - 1] != '/'){
                            this->diretorio_atual.pop_back();
                        }
                    } else {
                        this->diretorio_atual += comando_aux;
                        this->diretorio_atual += "/";
                    }

                } else {
                    cout << "Diretório não existente\n";
                }
                break;
            case 5:
                sis->list_dir();
                break;
            case 6:
                cin >> int_aux ;
                if(int_aux <= 0){
                    cout << "Inode inválido.\n";
                    break;
                }

                if(int_aux >= this->sis->get_super()->s_inodes_count){
                    cout << "Inode nao encontrado\n";
                    break;
                }
                int_aux2 = int_aux / this->sis->get_super()->s_inodes_per_group;
                cout << "->" << int_aux2 << endl;
                if(int_aux2 != this->sis->inode_do_bitmap){
                    
                    this->sis->set_bitmap_inode(int_aux2);
                }

                if(!this->sis->get_bit(this->sis->get_bitmap_inode(), 
                    (int_aux - 1 - (int_aux2*this->sis->get_super()->s_inodes_per_group)))){
                    cout << "livre!" << endl;
                } else {
                    cout << "ocupado" << endl;
                }
                
                break;
            case 7:
                cin >> int_aux ;
                if(int_aux <= -1){
                    cout << "Bloco Invalido.\n";
                    break;
                }

                if(int_aux >= this->sis->get_super()->s_blocks_count_lo){
                    cout << "Bloco nao encontrado\n";
                    break;
                }

                int_aux2 = int_aux / this->sis->get_super()->s_blocks_per_group;
                
                if(int_aux2 != this->sis->grupo_do_bitmap){

                    this->sis->set_bitmap_grupo(int_aux2);
                }
                
                if(!this->sis->get_bit(this->sis->get_bitmap_block(), 
                    (int_aux - int_aux2*this->sis->get_super()->s_blocks_per_group))){
                    cout << "livre!" << endl;
                } else {
                    cout << "ocupado" << endl;
                }
                break;
            case 8:
                cin >> comando_aux;
                cin >> comando_aux2;
                this -> sis -> exportar_arquivo(comando_aux,comando_aux2); 
                break;
            case 9:
                cout <<this->diretorio_atual << endl;
                break;
            case 10:
                break;
            case 11:
                break;
            case 12:
                break;
            case 13:
                if(this->diretorio_atual != "root/"){
                //cout << comando_aux << endl;
                    int_aux = sis->procurar_por_pasta("..");
                    if(int_aux){
                        sis->set_inode_atual(int_aux);
                        this->diretorio_atual.pop_back();
                        while(this->diretorio_atual[this->diretorio_atual.size() - 1] != '/'){
                            this->diretorio_atual.pop_back();
                        }

                    } else {
                        cout << "Diretório não existente\n";
                    }
                }
                break;
            case 14:
                break;
            case 15:
                break;
            case 16:
                printHelp();
                break;
            case -1:
                cout << "Comando invalido\n";
                break;
            default:
                cout << "Comando invalido\n";
        }
        return 0;
}

void shell::printHelp(void)
{
    cout << "**********************************HELP******************************************\n";
    cout << "info: exibe informações da imagem e do sistema de arquivos.\n";
    cout << "cat <file>: exibe o conteúdo de um arquivo no formato texto.\n";
    cout << "attr <file | dir>: exibe os atributos de um arquivo (file) ou diretório (dir)\n";
    cout << "cd <path>: altera o diretório corrente para o definido como path\n";
    cout << "ls: lista os arquivos e diretórios do diretório corrente.\n";
    cout << "testi <inode_number>: verifica se um inode está livre ou ocupado.\n";
    cout << "testb <block_number>: verifica se um bloco está livre ou ocupado.\n";
    cout << "export <source_path> <target_path>: copia arquivo da imagem (source_path)\n para destino (target_path) no sistema operacional da máquina.\n";
    cout << "pwd: exibe o diretório corrente (caminho absoluto).\n";
    //cout << "touch <file>: cria o arquivo file com conteúdo vazio.\n";
    //cout << "mkdir <dir>: cria o diretório dir vazio\n";
    //cout << "rm <file>: remove o arquivo file do sistema.\n";
    //cout << "rmdir <dir>: remove o diretório dir, se estiver vazio.\n";
    //cout << "rename <file> <newfilename> : renomeia arquivo file para newfilename.\n";
    cout << "********************************************************************************\n";
}

void shell::start_loop(){
    std::string comando;
    while(1){
        cout << this->diretorio_atual << "[$]> " ;
        cin >> comando;
        
        if(this->executeCommand(comando) == -1)
            break;
    }
}


#endif