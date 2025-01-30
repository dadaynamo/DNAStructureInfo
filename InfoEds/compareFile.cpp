#include <iostream>
#include <fstream>
#include <string>
#include <iomanip> // Per std::hex e std::setw

void compare_files(const std::string& file1, const std::string& file2) {
    // Apertura dei file in modalità binaria
    std::ifstream f1(file1, std::ios::binary | std::ios::ate);
    std::ifstream f2(file2, std::ios::binary | std::ios::ate);

    // Verifica se i file sono stati aperti correttamente
    if (!f1.is_open() || !f2.is_open()) {
        std::cerr << "Errore nell'apertura di uno dei file." << std::endl;
        return;
    }

    // Confronto delle dimensioni dei file
    std::streamsize size1 = f1.tellg();
    std::streamsize size2 = f2.tellg();

    if (size1 != size2) {
        std::cout << "Le dimensioni dei file sono diverse:\n";
        std::cout << "  File 1: " << size1 << " byte\n";
        std::cout << "  File 2: " << size2 << " byte\n";
        return;
    } else {
        std::cout << "Le dimensioni dei file sono identiche: " << size1 << " byte.\n";
    }

    // Torna all'inizio dei file
    f1.seekg(0, std::ios::beg);
    f2.seekg(0, std::ios::beg);

    char ch1, ch2;
    size_t position = 0; // Posizione corrente del byte
    bool difference_found = false;

    while (f1.get(ch1) && f2.get(ch2)) {
        if (ch1 != ch2) {
            // Mostra la posizione e i valori diversi
            std::cout << "Differenza trovata alla posizione " << position << ":\n";
            std::cout << "  File 1: 0x" << std::hex << std::setw(2) << std::setfill('0') 
                      << static_cast<int>(static_cast<unsigned char>(ch1)) << "\n";
            std::cout << "  File 2: 0x" << std::hex << std::setw(2) << std::setfill('0') 
                      << static_cast<int>(static_cast<unsigned char>(ch2)) << "\n";
            difference_found = true;
            break;
        }
        ++position;
    }

    // Se nessuna differenza è stata trovata
    if (!difference_found) {
        std::cout << "I file sono identici in contenuto." << std::endl;
    }
}

int main() {
    // Inserimento dei nomi dei file
    std::string file1, file2;
    std::cout << "Inserisci il percorso del primo file: ";
    std::cin >> file1;
    std::cout << "Inserisci il percorso del secondo file: ";
    std::cin >> file2;

    // Confronto dei file
    compare_files(file1, file2);

    return 0;
}
