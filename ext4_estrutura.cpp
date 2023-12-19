#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <vector>
#include <cstring>

#include "ext4_estrutura.hpp"

using namespace std; 

void info(super_block_t* block){
    printf("Volume name:  %s\n",block -> s_volume_name);  
    int tamanho = (block->s_blocks_count_lo * block->s_log_block_size);
    cout <<"Image size: " << tamanho << endl; 
    printf("Free space: %d KiB\n",(block -> s_free_blocks_count_lo * block -> s_log_block_size)/1024);
    printf("Free Inodes Count: %d\n",block -> s_free_inodes_count);
    printf("Free Blocks Count: %d\n",block->s_free_blocks_count_lo);
    printf("Block Size: %d Bytes\n",block -> s_log_block_size);
    printf("Inode Size: %d\n",block -> s_inode_size);
    short group_block = ( block -> s_blocks_count_lo / block -> s_blocks_per_group);
    cout <<"count groups " << group_block << endl;
    cout <<"blocks per group: " << block -> s_blocks_per_group << endl;
    cout <<"inodes per inodes: " << block -> s_inodes_per_group << endl;
    cout <<"inodetable size: " << block -> s_inode_size << endl;
    cout << endl;
}

block_group_descriptors** leitura_grupo_de_blocks(std::string caminho_relativo,int quantidades_de_grupos, int tamanho_bloco){
    block_group_descriptors** descritores=new block_group_descriptors*[quantidades_de_grupos];
    // Cria um objeto ifstream
    std::ifstream inputFile;

    // Abre um arquivo para leitura binária
    inputFile.open(caminho_relativo, std::ios::binary);
    inputFile.seekg(tamanho_bloco);
    if (!inputFile.is_open())
    {
        std::cerr << "Não foi possível abrir o arquivo." << std::endl;
        return nullptr; // Retorna um código de erro
    }
    block_group_descriptors* grupo[quantidades_de_grupos]; 
    for (int i = 0; i <quantidades_de_grupos ; i++){
        grupo[i]=new block_group_descriptors;
        inputFile.read((char*)grupo[i],sizeof(block_group_descriptors));
        descritores[i]=grupo[i];
    }
    inputFile.close();
    return descritores;
}

char* leitura_do_bitmap_blocos(block_group_descriptors*group, super_block_t* block, std::string nome_arquivo){
    std::ifstream inputFile;
    // Abre um arquivo para leitura binária
    inputFile.open(nome_arquivo, std::ios::binary);
    inputFile.seekg(group->bg_block_bitmap_lo*block->s_log_block_size);
    if (!inputFile.is_open())
    {
        std::cerr << "Não foi possível abrir o arquivo." << std::endl;
        return nullptr; // Retorna um código de erro
    }
    
    char* bitmap=new char[block->s_blocks_per_group/8];
    //memset(bitmap,'0',tamanho_de_um_bloco);
    inputFile.read((char*)bitmap, block->s_blocks_per_group/8);
    
    return bitmap;
}

char* leitura_do_bitmap_inode(block_group_descriptors*group, super_block_t* block, std::string nome_arquivo){
    std::ifstream inputFile;
    // Abre um arquivo para leitura binária
    inputFile.open(nome_arquivo, std::ios::binary);
    //cout << group->bg_inode_bitmap_lo << endl;
    inputFile.seekg(group->bg_inode_bitmap_lo*block->s_log_block_size);
    if (!inputFile.is_open())
    {
        std::cerr << "Não foi possível abrir o arquivo." << std::endl;
        return nullptr; // Retorna um código de erro
    }
    int tamanho_de_um_bloco = block -> s_log_block_size;
    char* bitmap=new char[block->s_inodes_per_group/8];
    inputFile.read((char*)bitmap,block->s_inodes_per_group/8);
    
    return bitmap;
}

super_block_t* leitura_superblock(std::string caminho_relativo){
    // Cria um objeto ifstream
    std::ifstream inputFile;

    // Abre um arquivo para leitura binária
    inputFile.open(caminho_relativo, std::ios::binary);
    inputFile.seekg(1024);
    // Verifica se o arquivo foi aberto com sucesso
    if (!inputFile.is_open())
    {
        std::cerr << "Não foi possível abrir o arquivo." << std::endl;
        return nullptr; // Retorna um código de erro
    }

    // Determina o tamanho do buffer de leitura
    super_block_t * block =new super_block_t;
    // Lê dados do arquivo
    inputFile.read((char*)block, sizeof(super_block_t));

    // Fecha o arquivo
    inputFile.close();
    int valor_bloco=10+block->s_log_block_size;
    block->s_log_block_size=pow(2,valor_bloco);
    block->s_log_cluster_size=pow(2,block->s_log_block_size);

    block->s_bit_map_length = (block -> s_blocks_count_lo / block -> s_log_block_size);

    //freeBlocksBitmap

    return block;
}


sistema_de_arquivo::sistema_de_arquivo(std::string ext4_image){
    this -> super_block = leitura_superblock(ext4_image);
    tamanho_do_bloco = this -> super_block->s_log_block_size;
    this -> grupo = leitura_grupo_de_blocks
    (ext4_image, 
    this -> super_block -> s_blocks_count_lo / 
    this -> super_block -> s_blocks_per_group
    , this -> tamanho_do_bloco);
    //this -> tabela_inodes = leitura_tabelas_inodes(ext4_image, this -> super_block, this->grupo[0]);
    this -> grupo_do_bitmap = 0;
    this -> inode_do_bitmap = 0;
    this -> caminho_do_arquivo = ext4_image;
    this -> inode_root = 2;
    this -> inode_diretorio_atual = 2;
    this -> input_file.open(ext4_image, std::ios::binary);
    this -> bitmap_bloco = leitura_do_bitmap_blocos(this->grupo[0], this->super_block, ext4_image);
    this -> bitmap_inode = leitura_do_bitmap_inode(this->grupo[0], this->super_block, ext4_image);
}

void sistema_de_arquivo::info(){
    printf("Volume name:  %s\n",this -> super_block -> s_volume_name);  
    int tamanho = (this -> super_block->s_blocks_count_lo * this -> super_block->s_log_block_size);
    cout <<"Image size: " << tamanho << endl; 
    printf("Free space: %d KiB\n",(this -> super_block -> s_free_blocks_count_lo * this -> super_block -> s_log_block_size)/1024);
    printf("Free Inodes Count: %d\n",this -> super_block -> s_free_inodes_count);
    printf("Free Blocks Count: %d\n",this -> super_block->s_free_blocks_count_lo);
    printf("Block Size: %d Bytes\n",this -> super_block -> s_log_block_size);
    printf("Inode Size: %d\n",this -> super_block -> s_inode_size);
    short group_block = ( this -> super_block -> s_blocks_count_lo / this -> super_block -> s_blocks_per_group);
    cout <<"count groups " << group_block << endl;
    cout <<"blocks per group: " << this -> super_block -> s_blocks_per_group << endl;
    cout <<"inodes per group: " << this -> super_block -> s_inodes_per_group << endl;
    cout <<"inodetable size: " << this -> super_block -> s_inode_size << endl;
    cout << endl;
}

inode_t* sistema_de_arquivo::get_inode(int pos){
    if(pos <= 1)
        return NULL;
    
    int inode_table = this->grupo[0]->bg_inode_table_lo; 

    input_file.seekg((inode_table*this->tamanho_do_bloco) + 
        (this->super_block->s_inode_size * (pos - 1)));

    if (!input_file.good()) {
        std::cerr << "Erro ao ler o inode." << std::endl;
        return NULL;
    }    

    inode_t* inode = new inode_t;

    input_file.read((char*)inode, sizeof(inode_t));

    return inode; 
}

int sistema_de_arquivo::procurar_por_pasta(std::string nome){
    
    inode_t* inode = get_inode(this->inode_diretorio_atual);

    extent_t* extent = new extent_t;

    extent = (struct extent_t *)(&inode->i_block[3]);

    int posicao = extent -> ee_start_lo * this -> tamanho_do_bloco;

    this -> input_file.seekg(posicao);

    int dist = 0;

    dir_entry_2_t* dir;
    while(1){
        if(dist >= 2048)
            break;
        dir = new dir_entry_2_t;
        
        this -> input_file.seekg(posicao + dist);
        this -> input_file.read((char*)dir, sizeof(dir_entry_2_t));

        bool test = true;

        if(nome.length() < dir->name_len ){
            for(int i = nome.length(); i < dir->name_len; i++){
                if(dir->name[i] != ' ')
                    test = false;
            }
        }

        if(nome.length() <= dir->name_len && test && dir->file_type == 2){
            for(int i = 0; i < nome.length(); i++){
                if(nome[i] != dir->name[i]){
                    break;
                }
                if(nome.length() - 1 == i)
                    return dir->inode;
            }
        }
        
        
        dist += dir->rec_len;
    }
    return 0;
}



int sistema_de_arquivo::procurar_por_arquivo(std::string nome){
    
    inode_t* inode = get_inode(this->inode_diretorio_atual);
    extent_t* extent = new extent_t;

    extent = (struct extent_t *)(&inode->i_block[3]);

    int posicao = extent -> ee_start_lo * this -> tamanho_do_bloco;

    this -> input_file.seekg(posicao);

    int dist = 0;
    int tipo = -1;
    dir_entry_2_t* dir;
    while(1){
        if(dist >= 2048)
            break;
        dir = new dir_entry_2_t;
        
        this -> input_file.seekg(posicao + dist);
        this -> input_file.read((char*)dir, sizeof(dir_entry_2_t));

        bool test = true;

        if(nome.length() < dir->name_len){
            for(int i = nome.length(); i < dir->name_len; i++){
                if(dir->name[i] != ' ')
                    test = false;
            }
        }
        
        tipo = dir->file_type;
        if(nome.length() <= dir->name_len && test && tipo == 1){
            for(int i = 0; i < nome.length(); i++){
                if(nome[i] != dir->name[i]){
                    break;
                }
                if(nome.length() - 1 == i)
                    return dir->inode;
            }
        }

        dist += dir->rec_len;                
    }
    return 0;
}

void sistema_de_arquivo::set_inode_atual(int inode){
    this->inode_diretorio_atual = inode;
}

void sistema_de_arquivo::list_dir(){
    inode_t* inode = get_inode(this->inode_diretorio_atual);

    extent_t* extent = new extent_t;

    extent = (struct extent_t *)(&inode->i_block[3]);

    int posicao = extent -> ee_start_lo * this -> tamanho_do_bloco;

    this -> input_file.seekg(posicao);

    int dist = 0;

    dir_entry_2_t* dir;
    while(1){
        if(dist >= 2048)
            break;
        dir = new dir_entry_2_t;
        
        this -> input_file.seekg(posicao + dist);
        this -> input_file.read((char*)dir, sizeof(dir_entry_2_t));
        
        for(int i = 0; i < dir->name_len ; i++)
            printf("%c", dir->name[i]);
        
        cout << endl;
        
        dist += dir->rec_len;                
    }
    
}

std::string sistema_de_arquivo::get_dir_mount(){
    return this->super_block->s_last_mounted;
}

char* sistema_de_arquivo::get_bitmap_block(){
    return this->bitmap_bloco;
}

char* sistema_de_arquivo::get_bitmap_inode(){
    return this->bitmap_inode;
}

block_group_descriptors* sistema_de_arquivo::get_group(int pos){
    return this->grupo[pos];
}

super_block_t* sistema_de_arquivo::get_super(){
    return this->super_block;
}

void sistema_de_arquivo::set_bitmap_grupo(int n_grupo){
    delete this->bitmap_bloco;
    this->grupo_do_bitmap = n_grupo;
    this->bitmap_bloco = leitura_do_bitmap_blocos(this->grupo[n_grupo], this->super_block, this->caminho_do_arquivo);
}

void sistema_de_arquivo::set_bitmap_inode(int n_grupo){
    delete this->bitmap_inode;
    this->inode_do_bitmap = n_grupo;
    this->bitmap_inode = leitura_do_bitmap_inode(this->grupo[n_grupo], this->super_block, this->caminho_do_arquivo);
}

void sistema_de_arquivo::print_info(std::string nome_arquivo){
    //cout << this->inode_diretorio_atual << endl;
    char pasta = 1;
    int pos = this->procurar_por_pasta(nome_arquivo);
    if(pos == 0){
        pos = this->procurar_por_arquivo(nome_arquivo);
        pasta = 0;
    }
    if(pos == 0){
        cout << "Nao há arquivo ou diretorio com o nome informado." << endl;
        return;
    }

    inode_t* inode_arquivo = this->get_inode(pos);

    cout <<"Nome do arquivo:   " << nome_arquivo << endl;
    //cout <<"Nome do arquivo:   " << inode_arquivo->i_size_lo << endl;

    cout <<"Permissoes:        -";
    if(inode_arquivo->i_mode & 0x100 ){
        cout << "r";
    } else {
        cout << "-";
    }
    if(inode_arquivo->i_mode & 0x80 ){
        cout << "w";
    } else {
        cout << "-";
    }
    if(inode_arquivo->i_mode & 0x40 ){
        cout << "x";
    } else {
        cout << "-";
    }
    if(inode_arquivo->i_mode & 0x20 ){
        cout << "r";
    } else {
        cout << "-";
    }
    if(inode_arquivo->i_mode & 0x10 ){
        cout << "w";
    } else {
        cout << "-";
    }
    if(inode_arquivo->i_mode & 0x8 ){
        cout << "x";
    } else {
        cout << "-";
    }
    if(inode_arquivo->i_mode & 0x4 ){
        cout << "r";
    } else {
        cout << "-";
    }
    if(inode_arquivo->i_mode & 0x2 ){
        cout << "w";
    } else {
        cout << "-";
    }
    if(inode_arquivo->i_mode & 0x1 ){
        cout << "x\n";
    } else {
        cout << "-\n";
    }

    printf("Tamanho:           %d bytes\n", inode_arquivo->i_size_lo);
    printf("acessado em:       %02d/%02d/%02d  %02d:%02d\n"
        ,(inode_arquivo->i_atime/86400)%31
        ,(inode_arquivo->i_atime/2592000)%13 
        ,(inode_arquivo->i_atime/31536000)+1970
        ,(inode_arquivo->i_atime/3600)%24
        ,(inode_arquivo->i_atime/60)%61
        );
        printf("Criado em:         %02d/%02d/%02d  %02d:%02d\n"
        ,(inode_arquivo->i_crtime/86400)%31
        ,(inode_arquivo->i_crtime/2592000)%13 
        ,(inode_arquivo->i_crtime/31536000)+1970
        ,(inode_arquivo->i_crtime/3600)%24
        ,(inode_arquivo->i_crtime/60)%61
        );
        printf("Modificado em:     %02d/%02d/%02d  %02d:%02d\n"
        ,(inode_arquivo->i_mtime/86400)%31
        ,(inode_arquivo->i_mtime/2592000)%13 
        ,(inode_arquivo->i_mtime/31536000)+1970
        ,(inode_arquivo->i_mtime/3600)%24
        ,(inode_arquivo->i_mtime/60)%61
        );
}

void sistema_de_arquivo::ler_arquivo(std::string nome_arquivo){
    int pos_inode = this->procurar_por_arquivo(nome_arquivo);
    if (pos_inode == 0){
        cout << "Arquivo nao existe.\n";
        return;
    }

    inode_t* inode = this->get_inode(pos_inode);


    extent_header_t* header;
    extent_t* extent;
    extent_idx_t* idx;
    
    header = (struct extent_header_t *)(&inode->i_block[0]);
    if(header->eh_depth >= 1){

        extent = new extent_t;
        idx = (struct extent_idx_t*)(&inode->i_block[3]);
        
        int pos = idx->ei_leaf_lo * this->tamanho_do_bloco;        

        for(int i = 1 ; i < header->eh_depth ; i++){
            
            this->input_file.seekg(pos);
            header = new extent_header_t;
            this->input_file.read((char*)header, sizeof(extent_header_t));
            
            idx = new extent_idx_t;
            this->input_file.read((char*)idx, sizeof(extent_idx_t));

            pos = idx->ei_leaf_lo * this->tamanho_do_bloco;
            cout << "endereço: " << idx->ei_leaf_lo << endl;

            delete idx;
            delete header;
        }

        header = new extent_header_t;
        this->input_file.seekg(pos);
        this->input_file.read((char*)header, sizeof(extent_header_t));    

        cout << "cheuei aqui" << endl;
        cout << header->eh_entries << endl;
        cout << header->eh_magic << endl;

        for(int i = 0 ; i <= header->eh_entries ; i++){

            extent = new extent_t;

            this->input_file.seekg(pos + (12 * (i + 1)));
            this->input_file.read((char*)extent, sizeof(extent_t));    

            int pos_aux = extent->ee_start_lo * this -> tamanho_do_bloco;

            char* buffer = new char[extent->ee_len * this->tamanho_do_bloco];

            this->input_file.seekg(pos_aux);
            this->input_file.read((char*)buffer, extent->ee_len * this->tamanho_do_bloco); 

            for(int i = 0; i < extent->ee_len * this->tamanho_do_bloco; i++)
                printf("%c", buffer[i]);
            
            delete buffer;
            delete extent;
        }
        //cout << "Não foi possivel ler o arquivo.\n";
        delete header;
        
    } else {
        
        for(int i = 0 ; i <= header->eh_entries ; i++){
            
            extent = (struct extent_t *)(&inode->i_block[(i+1)*3]);
            int pos = (extent->ee_start_lo * this->tamanho_do_bloco);
            char* buffer = new char[extent->ee_len * this->tamanho_do_bloco];

            //cout << extent->ee_len << endl;
            this->input_file.seekg(pos);
            this->input_file.read((char*)buffer, extent->ee_len * this->tamanho_do_bloco);

            for(int i = 0; i < extent->ee_len * this->tamanho_do_bloco; i++)
                printf("%c", buffer[i]);
        }

    }

    

    cout << endl;
    
}

void sistema_de_arquivo::exportar_arquivo(std::string nome_arquivo, std::string caminho){
    int pos_inode = this->procurar_por_arquivo(nome_arquivo);
    if (pos_inode == 0){
        cout << "Arquivo nao existe.\n";
        return;
    }

    inode_t* inode = this->get_inode(pos_inode);


    extent_header_t* header;
    extent_t* extent;
    extent_idx_t* idx;
    
    std::ofstream f_out(caminho);
    if(!f_out.good()){
        cout << "Erro ao abrir arquivo!\n";
        return;
    }

    header = (struct extent_header_t *)(&inode->i_block[0]);
    if(header->eh_depth >= 1){

        extent = new extent_t;
        idx = (struct extent_idx_t*)(&inode->i_block[3]);
        
        int pos = idx->ei_leaf_lo * this->tamanho_do_bloco;        

        for(int i = 1 ; i < header->eh_depth ; i++){
            
            this->input_file.seekg(pos);
            header = new extent_header_t;
            this->input_file.read((char*)header, sizeof(extent_header_t));
            
            idx = new extent_idx_t;
            this->input_file.read((char*)idx, sizeof(extent_idx_t));

            pos = idx->ei_leaf_lo * this->tamanho_do_bloco;
            //cout << "endereço: " << idx->ei_leaf_lo << endl;

            delete idx;
            delete header;
        }

        header = new extent_header_t;
        this->input_file.seekg(pos);
        this->input_file.read((char*)header, sizeof(extent_header_t));    

        
        for(int i = 0 ; i <= header->eh_entries ; i++){

            extent = new extent_t;

            this->input_file.seekg(pos + (12 * (i + 1)));
            this->input_file.read((char*)extent, sizeof(extent_t));    

            int pos_aux = extent->ee_start_lo * this -> tamanho_do_bloco;

            char* buffer = new char[extent->ee_len * this->tamanho_do_bloco];

            this->input_file.seekg(pos_aux);
            this->input_file.read((char*)buffer, extent->ee_len * this->tamanho_do_bloco); 

            for(int i = 0; i < extent->ee_len * this->tamanho_do_bloco ; i++)
                f_out << buffer[i];

            
            delete buffer;
            delete extent;
        }
        //cout << "Não foi possivel ler o arquivo.\n";
        delete header;
        
    } else {
        
        for(int i = 0 ; i <= header->eh_entries ; i++){
            
            extent = (struct extent_t *)(&inode->i_block[(i+1)*3]);
            int pos = (extent->ee_start_lo * this->tamanho_do_bloco);
            char* buffer = new char[extent->ee_len * this->tamanho_do_bloco];

            //cout << extent->ee_len << endl;
            this->input_file.seekg(pos);
            this->input_file.read((char*)buffer, extent->ee_len * this->tamanho_do_bloco);

            for(int i = 0; i < extent->ee_len * this->tamanho_do_bloco ; i++)
                f_out << buffer[i];

        }

    }

    

    cout << endl;
    
}

bool sistema_de_arquivo::get_bit(char* bitmap, int pos){
    int index = pos / 8;
    int offset = pos % 8;
    unsigned char byte = bitmap[index];
    return (byte >> offset) & 0x1;
}

sistema_de_arquivo::~sistema_de_arquivo(){
    for(int i = 0; i < (this->super_block->s_blocks_count_lo / this -> super_block -> s_blocks_per_group); i++)
        delete this->grupo[i];

    delete this->super_block;
    delete this->bitmap_bloco;
    delete this->bitmap_inode; 
}

