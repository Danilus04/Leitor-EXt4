#include "main.hpp"

//#define FILE_NAME "images_ext4/myext4image4k.img"

using namespace std;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cout << "Por favor, forneça o argumento necessário." << endl;
        return 1;
    }

    shell* console;
    console = new shell(argv[1]); // Usando o primeiro argumento aqui
    console->start_loop();
    delete console;

    return 0;
}
