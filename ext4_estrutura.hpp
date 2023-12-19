#ifndef EXT_4_ESTRUTURA_H
#define EXT_4_ESTRUTURA_H

#include <cstdint>
#include <iostream>
#include <fstream>

#define EXT4_N_BLOCKS 15
#define EXT4_NAME_LEN 255
#define EXT4_S_ERR_START offsetof(struct ext4_super_block, s_error_count)
#define EXT4_S_ERR_END offsetof(struct ext4_super_block, s_mount_opts)
#define POINTERS_PER_INODE 5


struct super_block_t {
/*00*/  int32_t  s_inodes_count;         /* Inodes count */
        int32_t  s_blocks_count_lo;      /* Blocks count */
        int32_t  s_r_blocks_count_lo;    /* Reserved blocks count */
        int32_t  s_free_blocks_count_lo; /* Free blocks count */
/*10*/  int32_t  s_free_inodes_count;    /* Free inodes count */
        int32_t  s_first_data_block;     /* First Data Block */
        int32_t  s_log_block_size;       /* Block size */
        int32_t  s_log_cluster_size;     /* Allocation cluster size */
/*20*/  int32_t  s_blocks_per_group;     /* # Blocks per group */
        int32_t  s_clusters_per_group;   /* # Clusters per group */
        int32_t  s_inodes_per_group;     /* # Inodes per group */
        int32_t  s_mtime;                /* Mount time */
/*30*/  int32_t  s_wtime;                /* Write time */
        int16_t  s_mnt_count;            /* Mount count */
        int16_t  s_max_mnt_count;        /* Maximal mount count */
        int16_t  s_magic;                /* Magic signature */
        int16_t  s_state;                /* File system state */
        int16_t  s_errors;               /* Behaviour when detecting errors */
        int16_t  s_minor_rev_level;      /* minor revision level */
/*40*/  int32_t  s_lastcheck;            /* time of last check */
        int32_t  s_checkinterval;        /* max. time between checks */
        int32_t  s_creator_os;           /* OS */
        int32_t  s_rev_level;            /* Revision level */
/*50*/  int16_t  s_def_resuid;           /* Default uid for reserved blocks */
        int16_t  s_def_resgid;           /* Default gid for reserved blocks */
        /*
         * These fields are for EXT4_DYNAMIC_REV Superblocks only.
         *
         * Note: the difference between the compatible feature set and
         * the incompatible feature set is that if there is a bit set
         * in the incompatible feature set that the kernel doesn't
         * know about, it should refuse to mount the filesystem.
         *
         * e2fsck's requirements are more strict; if it doesn't know
         * about a feature in either the compatible or incompatible
         * feature set, it must abort and not try to meddle with
         * things it doesn't understand...
         */
        int32_t  s_first_ino;            /* First non-reserved inode */
        int16_t  s_inode_size;           /* size of inode structure */
        int16_t  s_block_group_nr;       /* block group # of this Superblock */
        int32_t  s_feature_compat;       /* compatible feature set */
/*60*/  int32_t  s_feature_incompat;     /* incompatible feature set */
        int32_t  s_feature_ro_compat;    /* readonly-compatible feature set */
/*68*/  uint8_t    s_uuid[16];             /* 128-bit uuid for volume */
/*78*/  char    s_volume_name[16];      /* volume name */
/*88*/  char     s_last_mounted[64]; /* directory where last mounted */
/*C8*/  int32_t  s_algorithm_usage_bitmap; /* For compression */
        /*
         * Performance hints.  Directory preallocation should only
         * happen if the EXT4_FEATURE_COMPAT_DIR_PREALLOC flag is on.
         */
        uint8_t  s_prealloc_blocks;      /* Nr of blocks to try to preallocate*/
        uint8_t  s_prealloc_dir_blocks;  /* Nr to preallocate for dirs */
        int16_t  s_reserved_gdt_blocks;  /* Per group desc for online growth */
        /*
         * Journaling support valid if EXT4_FEATURE_COMPAT_HAS_JOURNAL set.
         */
/*D0*/  uint8_t  s_journal_uuid[16];     /* uuid of journal Superblock */
/*E0*/  int32_t  s_journal_inum;         /* inode number of journal file */
        int32_t  s_journal_dev;          /* device number of journal file */
        int32_t  s_last_orphan;          /* start of list of inodes to delete */
        int32_t  s_hash_seed[4];         /* HTREE hash seed */
        uint8_t  s_def_hash_version;     /* Default hash version to use */
        uint8_t  s_jnl_backup_type;
        int16_t  s_desc_size;            /* size of group descriptor */
/*100*/ int32_t  s_default_mount_opts;
        int32_t  s_first_meta_bg;        /* First metablock block group */
        int32_t  s_mkfs_time;            /* When the filesystem was created */
        int32_t  s_jnl_blocks[17];       /* Backup of the journal inode */
        /* 64bit support valid if EXT4_FEATURE_COMPAT_64BIT */
/*150*/ int32_t  s_blocks_count_hi;      /* Blocks count */
        int32_t  s_r_blocks_count_hi;    /* Reserved blocks count */
        int32_t  s_free_blocks_count_hi; /* Free blocks count */
        int16_t  s_min_extra_isize;      /* All inodes have at least # bytes */
        int16_t  s_want_extra_isize;     /* New inodes should reserve # bytes */
        int32_t  s_flags;                /* Miscellaneous flags */
        int16_t  s_raid_stride;          /* RAID stride */
        int16_t  s_mmp_update_interval;  /* # seconds to wait in MMP checking */
        int64_t  s_mmp_block;            /* Block for multi-mount protection */
        int32_t  s_raid_stripe_width;    /* blocks on all data disks (N*stride)*/
        uint8_t  s_log_groups_per_flex;  /* FLEX_BG group size */
        uint8_t  s_checksum_type;        /* metadata checksum algorithm used */
        uint8_t  s_encryption_level;     /* versioning level for encryption */
        uint8_t  s_reserved_pad;         /* Padding to next 32bits */
        int64_t  s_kbytes_written;       /* nr of lifetime kilobytes written */
        int32_t  s_snapshot_inum;        /* Inode number of active snapshot */
        int32_t  s_snapshot_id;          /* sequential ID of active snapshot */
        int64_t  s_snapshot_r_blocks_count; /* reserved blocks for active
                                              snapshot's future use */
        int32_t  s_snapshot_list;        /* inode number of the head of the
                                           on-disk snapshot list */
        int32_t  s_error_count;          /* number of fs errors */
        int32_t  s_first_error_time;     /* first time an error happened */
        int32_t  s_first_error_ino;      /* inode involved in first error */
        int64_t  s_first_error_block;    /* block involved of first error */
        uint8_t  s_first_error_func[32];     /* function where the error happened */
        int32_t  s_first_error_line;     /* line number where error happened */
        int32_t  s_last_error_time;      /* most recent time of an error */
        int32_t  s_last_error_ino;       /* inode involved in last error */
        int32_t  s_last_error_line;      /* line number where error happened */
        int64_t  s_last_error_block;     /* block involved of last error */
        uint8_t  s_last_error_func[32];      /* function where the error happened */
        uint8_t  s_mount_opts[64];
        int32_t  s_usr_quota_inum;       /* inode for tracking user quota */
        int32_t  s_grp_quota_inum;       /* inode for tracking group quota */
        int32_t  s_overhead_clusters;    /* overhead blocks/clusters in fs */
        int32_t  s_backup_bgs[2];        /* groups with sparse_super2 SBs */
        uint8_t  s_encrypt_algos[4];     /* Encryption algorithms in use  */
        uint8_t  s_encrypt_pw_salt[16];  /* Salt used for string2key algorithm */
        int32_t  s_lpf_ino;              /* Location of the lost+found inode */
        int32_t  s_prj_quota_inum;       /* inode for tracking project quota */
        int32_t  s_checksum_seed;        /* crc32c(uuid) if csum_seed set */
        uint8_t  s_wtime_hi;
        uint8_t  s_mtime_hi;
        uint8_t  s_mkfs_time_hi;
        uint8_t  s_lastcheck_hi;
        uint8_t  s_first_error_time_hi;
        uint8_t  s_last_error_time_hi;
        uint8_t  s_pad[2];
        int16_t  s_encoding;             /* Filename charset encoding */
        int16_t  s_encoding_flags;       /* Filename charset encoding flags */
        int32_t  s_reserved[95];         /* Padding to the end of the block */
        int32_t  s_checksum;             /* crc32c(Superblock) */
        int32_t  s_bit_map_length;
};
struct block_group_descriptors{
    int32_t 	bg_block_bitmap_lo;
    int32_t 	bg_inode_bitmap_lo;
    int32_t 	bg_inode_table_lo;
    int16_t 	bg_free_blocks_count_lo;
    int16_t 	bg_free_inodes_count_lo;
    int16_t 	bg_used_dirs_count_lo;
    int16_t 	bg_flags;
    int32_t 	bg_exclude_bitmap_lo;
    int16_t 	bg_block_bitmap_csum_lo;
    int16_t 	bg_inode_bitmap_csum_lo;
    int16_t 	bg_itable_unused_lo;
    int16_t 	bg_checksum;
    int32_t 	bg_block_bitmap_hi;
    int32_t 	bg_inode_bitmap_hi;
    int32_t 	bg_inode_table_hi;
    int16_t 	bg_free_blocks_count_hi;
    int16_t 	bg_free_inodes_count_hi;
    int16_t 	bg_used_dirs_count_hi;
    int16_t 	bg_itable_unused_hi;
    int32_t 	bg_exclude_bitmap_hi;
    int16_t 	bg_block_bitmap_csum_hi;
    int16_t 	bg_inode_bitmap_csum_hi;
    uint32_t 	bg_reserved;   
};
struct inode_t {
        int16_t  i_mode;         /* File mode */
        int16_t  i_uid;          /* Low 16 bits of Owner Uid */
        int32_t  i_size_lo;      /* Size in bytes */
        int32_t  i_atime;        /* Access time */
        int32_t  i_ctime;        /* Inode Change time */
        int32_t  i_mtime;        /* Modification time */
        int32_t  i_dtime;        /* Deletion Time */
        int16_t  i_gid;          /* Low 16 bits of Group Id */
        int16_t  i_links_count;  /* Links count */
        int32_t  i_blocks_lo;    /* Blocks count */
        int32_t  i_flags;        /* File flags */
        union {
                struct {
                        int32_t  l_i_version;
                } linux1;
                struct {
                        uint32_t  h_i_translator;
                } hurd1;
                struct {
                        uint32_t  m_i_reserved1;
                } masix1;
        } osd1;                         /* OS dependent 1 */
        int32_t  i_block[EXT4_N_BLOCKS];/* Pointers to blocks */
        int32_t  i_generation;   /* File version (for NFS) */
        int32_t  i_file_acl_lo;  /* File ACL */
        int32_t  i_size_high;
        int32_t  i_obso_faddr;   /* Obsoleted fragment address */
        union {
                struct {
                        int16_t  l_i_blocks_high; /* were l_i_reserved1 */
                        int16_t  l_i_file_acl_high;
                        int16_t  l_i_uid_high;   /* these 2 fields */
                        int16_t  l_i_gid_high;   /* were reserved2[0] */
                        int16_t  l_i_checksum_lo;/* crc32c(uuid+inum+inode) LE */
                        int16_t  l_i_reserved;
                } linux2;
                struct {
                        int16_t  h_i_reserved1;  /* Obsoleted fragment number/size which are removed in ext4 */
                        uint16_t   h_i_mode_high;
                        uint16_t   h_i_uid_high;
                        uint16_t   h_i_gid_high;
                        uint32_t   h_i_author;
                } hurd2;
                struct {
                        int16_t  h_i_reserved1;  /* Obsoleted fragment number/size which are removed in ext4 */
                        int16_t  m_i_file_acl_high;
                        uint32_t   m_i_reserved2[2];
                } masix2;
        } osd2;                         /* OS dependent 2 */
        int16_t  i_extra_isize;
        int16_t  i_checksum_hi;  /* crc32c(uuid+inum+inode) BE */
        int32_t  i_ctime_extra;  /* extra Change time      (nsec << 2 | epoch) */
        int32_t  i_mtime_extra;  /* extra Modification time(nsec << 2 | epoch) */
        int32_t  i_atime_extra;  /* extra Access time      (nsec << 2 | epoch) */
        int32_t  i_crtime;       /* File Creation time */
        int32_t  i_crtime_extra; /* extra FileCreationtime (nsec << 2 | epoch) */
        int32_t  i_version_hi;   /* high 32 bits for 64-bit version */
        int32_t  i_projid;       /* Project ID */
};
struct extent_header_t {
        int16_t  eh_magic;       /* probably will support different formats */
        int16_t  eh_entries;     /* number of valid entries */
        int16_t  eh_max;         /* capacity of store in entries */
        int16_t  eh_depth;       /* has tree real underlying blocks? */ 
        int32_t  eh_generation;  /* generation of the tree */ 
};
struct dir_entry_2_t {
        int32_t  inode;                  /* Inode number */
        int16_t  rec_len;                /* Directory entry length */
        uint8_t    name_len;               /* Name length */
        uint8_t    file_type;
        char    name[EXT4_NAME_LEN];    /* File name */
};
struct extent_t {
        int32_t  ee_block;       /* first logical block extent covers */
        int16_t  ee_len;         /* number of blocks covered by extent */
        int16_t  ee_start_hi;    /* high 16 bits of physical block */ 
        int32_t  ee_start_lo;    /* low 32 bits of physical block */
};
struct extent_idx_t {
        int32_t  ei_block;       /* index covers logical blocks from 'block' */ 
        int32_t  ei_leaf_lo;     /* pointer to the physical block of the next *
                 * level. leaf or next index could be there */
        int16_t  ei_leaf_hi;     /* high 16 bits of physical block */
        uint16_t   ei_unused;
};

class sistema_de_arquivo{
    private:
        super_block_t* super_block;
        block_group_descriptors** grupo;
        int tamanho_do_bloco;
        std::string caminho_do_arquivo;
        int inode_diretorio_atual;
        int inode_root;
        std::ifstream input_file;
        char* bitmap_bloco;
        char* bitmap_inode;
        
    public:

        short grupo_do_bitmap;
        short inode_do_bitmap;

        /*
        DESCRIÇÃO:
            Realiza a destruição do sistema de arquivo, liberando a memória alocada para os grupos, super bloco,
            mapa de bits de bloco e mapa de bits de inode.

        PARAMETROS DE ENTRADA:
            Não há parâmetros de entrada

        PARÂMETROS DE SAÍDA:
            Não há parâmetros de saída
        */
        ~sistema_de_arquivo();
        /*
        DESCRIÇÃO:
            Inicializa um objeto 'sistema_de_arquivo' com base em um arquivo de imagem 'ext4'. Realiza a leitura
            do super bloco, configura o tamanho do bloco, inicializa grupos de blocos, define variáveis de caminho,
            inodes e arquivos, abre o arquivo de imagem em modo binário e realiza a leitura dos mapas de bits de bloco
            e inode.

        PARAMETROS DE ENTRADA:
            ext4_image - Caminho do arquivo de imagem ext4

        PARÂMETROS DE SAÍDA:
            Não há parâmetros de saída
        */
        sistema_de_arquivo(std::string ext4_image);
        /*
        DESCRIÇÃO:
            Imprime informações detalhadas sobre o super bloco fornecido, incluindo o nome do volume, tamanho da imagem,
            espaço livre, contagem de inodes e blocos livres, tamanho do bloco e inode, contagem de grupos de blocos e
            informações relacionadas aos grupos.

        PARAMETROS DE ENTRADA:
            block - Ponteiro para a estrutura do super bloco (super_block_t)

        PARÂMETROS DE SAÍDA:
            Não há parâmetros de saída além da exibição das informações no console
        */
        void info();
        /*
        DESCRIÇÃO:
            Obtém um inode específico com base na posição fornecida no sistema de arquivos. Realiza a leitura do inode
            na posição desejada e retorna um ponteiro para a estrutura do inode correspondente.

        PARAMETROS DE ENTRADA:
            pos - Posição do inode desejado no sistema de arquivos

        PARÂMETROS DE SAÍDA:
            Retorna um ponteiro para a estrutura do inode correspondente à posição 'pos'. Retorna NULL se a posição for
            menor ou igual a 1 ou se houver um erro ao ler o inode.
        */
        inode_t* get_inode(int pos);
        /*
        DESCRIÇÃO:
            Procura por um diretório com o nome especificado dentro do diretório atual no sistema de arquivos. 
            Realiza a leitura do inode do diretório atual, percorre os blocos de diretório, e verifica se existe 
            um diretório com o nome fornecido. Retorna o número do inode correspondente se encontrar o diretório com o nome 
            especificado, caso contrário, retorna 0.

        PARAMETROS DE ENTRADA:
            nome - Nome do diretório a ser procurado

        PARÂMETROS DE SAÍDA:
            Retorna o número do inode correspondente ao diretório com o nome fornecido dentro do diretório atual. 
            Se não encontrar o diretório ou atingir o final dos blocos de diretório no diretório atual, retorna 0.
        */
        int procurar_por_pasta(std::string nome);
        /*
        DESCRIÇÃO:
            Procura por um arquivo com o nome especificado dentro do diretório atual no sistema de arquivos. 
            Realiza a leitura do inode do diretório atual, percorre os blocos de diretório e verifica se existe 
            um arquivo com o nome fornecido. Retorna o número do inode correspondente se encontrar o arquivo com o nome 
            especificado e se for do tipo arquivo regular (file_type == 1). Caso contrário, retorna 0.

        PARAMETROS DE ENTRADA:
            nome - Nome do arquivo a ser procurado

        PARÂMETROS DE SAÍDA:
            Retorna o número do inode correspondente ao arquivo com o nome fornecido dentro do diretório atual, 
            se for do tipo arquivo regular (file_type == 1). Se não encontrar o arquivo ou atingir o final dos 
            blocos de diretório no diretório atual, retorna 0.
        */
        int procurar_por_arquivo(std::string nome);
        /*
        DESCRIÇÃO:
            Define o inode do diretório atual para o valor especificado. Atualiza o valor do inode utilizado 
            para representar o diretório atual no sistema de arquivos.

        PARAMETROS DE ENTRADA:
            inode - Valor do inode a ser atribuído ao diretório atual

        PARÂMETROS DE SAÍDA:
            Não há parâmetros de saída além da atualização do valor do inode que representa o diretório atual no sistema.
        */
        void set_inode_atual(int inode);
        /*
        DESCRIÇÃO:
            Lista o conteúdo do diretório atual no sistema de arquivos. Realiza a leitura do inode do diretório atual, 
            percorre os blocos de diretório e imprime o nome de todos os itens (arquivos e subdiretórios) presentes 
            no diretório atual.

        PARAMETROS DE ENTRADA:
            Não há parâmetros de entrada.

        PARÂMETROS DE SAÍDA:
            Não há parâmetros de saída além da impressão dos nomes dos itens presentes no diretório atual.
        */
        void list_dir();
        /*
        DESCRIÇÃO:
            Retorna o diretório onde o sistema de arquivos foi montado pela última vez. Obtém o caminho do diretório
            onde o sistema de arquivos foi montado a partir das informações armazenadas no super bloco.

        PARAMETROS DE ENTRADA:
            Não há parâmetros de entrada.

        PARÂMETROS DE SAÍDA:
            Retorna uma string representando o caminho do diretório onde o sistema de arquivos foi montado pela última vez.
        */
        std::string get_dir_mount();
        /*
        DESCRIÇÃO:
            Retorna o ponteiro para o mapa de bits de blocos do sistema de arquivos. Fornece acesso ao mapa de bits 
            de blocos armazenado na classe 'sistema_de_arquivo'.

        PARAMETROS DE ENTRADA:
            Não há parâmetros de entrada.

        PARÂMETROS DE SAÍDA:
            Retorna um ponteiro para o mapa de bits de blocos do sistema de arquivos.
        */
        char* get_bitmap_block();
        /*
        DESCRIÇÃO:
            Retorna o ponteiro para o mapa de bits de inodes do sistema de arquivos. Fornece acesso ao mapa de bits 
            de inodes armazenado na classe 'sistema_de_arquivo'.

        PARAMETROS DE ENTRADA:
            Não há parâmetros de entrada.

        PARÂMETROS DE SAÍDA:
            Retorna um ponteiro para o mapa de bits de inodes do sistema de arquivos.
        */
        char* get_bitmap_inode();
        /*
        DESCRIÇÃO:
            Retorna o descritor do grupo de blocos na posição especificada. Fornece acesso ao descritor de grupo de 
            blocos correspondente à posição 'pos' armazenado na classe 'sistema_de_arquivo'.

        PARAMETROS DE ENTRADA:
            pos - Posição do descritor do grupo de blocos desejado

        PARÂMETROS DE SAÍDA:
            Retorna o descritor do grupo de blocos na posição especificada no sistema de arquivos.
        */
        block_group_descriptors* get_group(int);
        /*
        DESCRIÇÃO:
            Retorna o ponteiro para o super bloco do sistema de arquivos. Fornece acesso ao super bloco 
            armazenado na classe 'sistema_de_arquivo'.

        PARAMETROS DE ENTRADA:
            Não há parâmetros de entrada.

        PARÂMETROS DE SAÍDA:
            Retorna um ponteiro para o super bloco do sistema de arquivos.
        */  
        super_block_t* get_super();
        /*
        DESCRIÇÃO:
            Atualiza o mapa de bits de blocos para o grupo especificado. Libera a memória previamente alocada 
            para o mapa de bits de blocos e carrega um novo mapa de bits para o grupo 'n_grupo'.

        PARAMETROS DE ENTRADA:
            n_grupo - Índice do grupo para o qual o mapa de bits de blocos será atualizado.

        PARÂMETROS DE SAÍDA:
            Não há parâmetros de saída além da atualização do mapa de bits de blocos para o grupo especificado.
        */
        void set_bitmap_grupo(int);
        /*
        DESCRIÇÃO:
            Atualiza o mapa de bits de inodes para o grupo especificado. Libera a memória previamente alocada 
            para o mapa de bits de inodes e carrega um novo mapa de bits para o grupo 'n_grupo'.

        PARAMETROS DE ENTRADA:
            n_grupo - Índice do grupo para o qual o mapa de bits de inodes será atualizado.

        PARÂMETROS DE SAÍDA:
            Não há parâmetros de saída além da atualização do mapa de bits de inodes para o grupo especificado.
        */
        void set_bitmap_inode(int);
        /*
        DESCRIÇÃO:
            Imprime informações detalhadas sobre um arquivo ou diretório no sistema de arquivos com o nome 
            especificado ('nome_arquivo'). A função busca pelo arquivo ou diretório no diretório atual, 
            verifica suas propriedades (como nome, tipo, inode, tamanho e datas de acesso, criação e modificação) 
            e exibe essas informações no console.

        PARAMETROS DE ENTRADA:
            nome_arquivo - Nome do arquivo ou diretório cujas informações serão impressas.

        PARÂMETROS DE SAÍDA:
            Não há parâmetros de saída além da exibição das informações detalhadas sobre o arquivo ou diretório 
            no console.
        */
        void print_info(std::string);
        /*
        DESCRIÇÃO:
            Lê e exibe o conteúdo de um arquivo no sistema de arquivos com o nome especificado ('nome_arquivo'). 
            A função busca pelo arquivo no diretório atual, lê seu conteúdo e o exibe no console.

        PARAMETROS DE ENTRADA:
            nome_arquivo - Nome do arquivo cujo conteúdo será lido e exibido.

        PARÂMETROS DE SAÍDA:
            Não há parâmetros de saída além da exibição do conteúdo do arquivo no console.
        */
        void ler_arquivo(std::string);
        /*
        DESCRIÇÃO:
            Exporta um arquivo do sistema de arquivos com o nome especificado ('nome_arquivo') para um caminho 
            de destino especificado ('caminho'). A função busca pelo arquivo no diretório atual, lê seu conteúdo 
            e o escreve em um novo arquivo no caminho fornecido.

        PARAMETROS DE ENTRADA:
            nome_arquivo - Nome do arquivo a ser exportado.
            caminho - Caminho de destino onde o arquivo será exportado.

        PARÂMETROS DE SAÍDA:
            Não há parâmetros de saída além da escrita do conteúdo do arquivo no caminho de destino.
        */
        void exportar_arquivo(std::string, std::string);
        /*
        DESCRIÇÃO:
            Obtém o valor de um bit específico em um mapa de bits dado uma posição 'pos'. A função calcula o índice 
            do byte onde o bit está localizado e o deslocamento dentro desse byte para recuperar o valor do bit.

        PARAMETROS DE ENTRADA:
            bitmap - Ponteiro para o mapa de bits.
            pos - Posição do bit a ser recuperado.

        PARÂMETROS DE SAÍDA:
            Retorna o valor do bit na posição especificada do mapa de bits.
        */
        bool get_bit(char*, int);
};
/*
    DESCRIÇÃO:
        Realiza a leitura do superbloco de um sistema de arquivos localizado no caminho especificado.
        Após a leitura, ajusta algumas informações do superbloco, como o tamanho do bloco e do cluster,
        o comprimento do mapa de bits de blocos e outras informações relevantes.

    PARAMETROS DE ENTRADA:
        caminho_relativo - Caminho do arquivo do sistema de arquivos

    PARÂMETROS DE SAÍDA:
        Retorna um ponteiro para a estrutura 'super_block_t' que representa o superbloco do sistema de arquivos.
        Em caso de falha na abertura do arquivo ou na leitura do superbloco, retorna nullptr.
*/
super_block_t* leitura_superblock(std::string);
/*
    DESCRIÇÃO:
        Realiza a leitura dos descritores de grupo de blocos do sistema de arquivos localizado no caminho especificado.
        Lê os descritores de 'quantidades_de_grupos' grupos de blocos a partir de um deslocamento de 'tamanho_bloco'
        bytes no arquivo.

    PARAMETROS DE ENTRADA:
        caminho_relativo - Caminho do arquivo do sistema de arquivos.
        quantidades_de_grupos - Número de grupos de blocos cujos descritores serão lidos.
        tamanho_bloco - Tamanho do bloco do sistema de arquivos (deslocamento inicial para leitura dos descritores).

    PARÂMETROS DE SAÍDA:
        Retorna um array de ponteiros para estruturas 'block_group_descriptors' representando os descritores de grupo de blocos lidos.
        Em caso de falha na abertura do arquivo ou na leitura dos descritores, retorna nullptr.
*/
block_group_descriptors** leitura_grupo_de_blocks(std::string, int, int);
/*
    DESCRIÇÃO:
        Realiza a leitura do bitmap de blocos para um grupo de blocos específico dentro do sistema de arquivos,
        utilizando as informações do descritor de grupo de blocos ('group') e do superbloco ('block').
        
    PARAMETROS DE ENTRADA:
        group - Descritor do grupo de blocos para o qual o bitmap de blocos será lido.
        block - Ponteiro para o superbloco do sistema de arquivos.
        nome_arquivo - Nome do arquivo do sistema de arquivos.

    PARÂMETROS DE SAÍDA:
        Retorna um ponteiro para um array de caracteres ('char*') representando o bitmap de blocos do grupo.
        Em caso de falha na abertura do arquivo ou na leitura do bitmap de blocos, retorna nullptr.
*/
char* leitura_do_bitmap_blocos(block_group_descriptors*, super_block_t*, std::string);
/*
    DESCRIÇÃO:
        Exibe informações detalhadas do superbloco de um sistema de arquivos.

    PARAMETROS DE ENTRADA:
        block - Ponteiro para o superbloco do sistema de arquivos.

    PARÂMETROS DE SAÍDA:
        Não há parâmetros de saída além da exibição das informações detalhadas do superbloco no console.
*/
void info(super_block_t*);
/*
    DESCRIÇÃO:
        Realiza a leitura do bitmap de inodes para um grupo de blocos específico dentro do sistema de arquivos,
        utilizando as informações do descritor de grupo de blocos ('group') e do superbloco ('block').

    PARAMETROS DE ENTRADA:
        group - Descritor do grupo de blocos para o qual o bitmap de inodes será lido.
        block - Ponteiro para o superbloco do sistema de arquivos.
        nome_arquivo - Nome do arquivo do sistema de arquivos.

    PARÂMETROS DE SAÍDA:
        Retorna um ponteiro para um array de caracteres ('char*') representando o bitmap de inodes do grupo.
        Em caso de falha na abertura do arquivo ou na leitura do bitmap de inodes, retorna nullptr.
*/
char* leitura_do_bitmap_inode(block_group_descriptors*, super_block_t*, std::string);

#endif