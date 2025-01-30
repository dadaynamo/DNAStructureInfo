#include <iostream>
#include <fstream>
#include <bitset>
#include <unordered_map>
#include <cmath>

using namespace std;

// Funzione per calcolare l'entropia
double calculate_entropy(const unordered_map<string, int>& frequency_map, size_t total_symbols) {
    double entropy = 0.0;

    for (const auto& pair : frequency_map) {
        double probability = static_cast<double>(pair.second) / total_symbols;
        entropy -= probability * log2(probability);
    }

    return entropy;
}

// Funzione per leggere un file binario e contare le occorrenze dei blocchi da 4 bit e da 8 bit
void count_blocks_and_entropy(const string& file_name) {
    ifstream file(file_name, ios::binary);
    if (!file) {
        cerr << "Impossibile aprire il file!" << endl;
        return;
    }

    unordered_map<string, int> frequency_map_8bit;
    unordered_map<string, int> frequency_map_4bit;
    
    const size_t buffer_size = 1024;  // Buffer di 1024 byte
    char buffer[buffer_size];
    size_t total_8bit = 0;  // Contatore per il totale dei blocchi da 8 bit
    size_t total_4bit = 0;  // Contatore per il totale dei blocchi da 4 bit
    
    // Leggiamo il file a blocchi
    while (file.read(buffer, buffer_size)) {
        size_t bytes_read = file.gcount();  // Numero di byte effettivamente letti
        
        for (size_t i = 0; i < bytes_read; ++i) {
            char byte = buffer[i];
            bitset<8> bits(byte);
            string block_8bit = bits.to_string();
            frequency_map_8bit[block_8bit]++;  // Incrementiamo la frequenza del blocco da 8 bit
            total_8bit++;

            // Conta per i blocchi da 4 bit (due blocchi per ogni byte)
            for (int j = 0; j < 2; ++j) {
                string block_4bit = bits.to_string().substr(j * 4, 4); // Estraiamo il blocco da 4 bit
                frequency_map_4bit[block_4bit]++;  // Incrementiamo la frequenza del blocco da 4 bit
                total_4bit++;
            }
        }
    }

    file.close();

    // Calcolo e stampa delle frequenze dei blocchi da 8 bit
    cout << "Frequenze dei blocchi da 8 bit:" << endl;
    for (const auto& pair : frequency_map_8bit) {
        cout << pair.first << " | " << pair.second << endl;
    }

    // Calcolo e stampa delle frequenze dei blocchi da 4 bit
    cout << "\nFrequenze dei blocchi da 4 bit:" << endl;
    for (const auto& pair : frequency_map_4bit) {
        cout << pair.first << " | " << pair.second << endl;
    }

    // Calcolo e stampa delle entropie
    double entropy_8bit = calculate_entropy(frequency_map_8bit, total_8bit);
    double entropy_4bit = calculate_entropy(frequency_map_4bit, total_4bit);

    cout << "\nEntropia con blocchi da 8 bit: " << entropy_8bit << endl;
    cout << "Entropia con blocchi da 4 bit: " << entropy_4bit << endl;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Uso: " << argv[0] << " <nome_del_file_binario>" << endl;
        return 1;
    }

    string file_name = argv[1];
    count_blocks_and_entropy(file_name);

    return 0;
}



/*#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <cmath>
#include <bitset>

using namespace std;

// Funzione per calcolare l'entropia
double calcola_entropia(const map<int, int>& frequenze, int totale) {
    double entropia = 0.0;
    for (const auto& pair : frequenze) {
        double probabilita = (double)pair.second / totale;
        entropia -= probabilita * log2(probabilita);
    }
    return entropia;
}

// Funzione per calcolare le frequenze dei simboli a 8 bit o 4 bit
void calcola_frequenze(const string& file_path, int bit_count) {
    ifstream file(file_path, ios::binary);
    if (!file.is_open()) {
        cerr << "Impossibile aprire il file!" << endl;
        return;
    }

    map<int, int> frequenze; // Mappa per memorizzare le frequenze
    int totale_simboli = 0;

    // Calcolare le frequenze dei blocchi di bit
    char buffer;
    while (file.read(&buffer, 1)) {
        // Prendere i blocchi di bit specificati (8 bit o 4 bit)
        int valore = (unsigned char)buffer;
        int maska = (bit_count == 4) ? 0x0F : 0xFF; // Maschera per 4 bit o 8 bit

        // Analizzare il file in blocchi del numero di bit richiesti
        for (int i = 0; i < (8 / bit_count); ++i) {
            int simbolo = valore & maska; // Estrae il blocco di bit
            frequenze[simbolo]++; // Incrementa la frequenza del simbolo

            totale_simboli++;
            valore >>= bit_count; // Shift per il prossimo blocco di bit
        }
    }

    // Calcolare e stampare le frequenze
    cout << "Frequenze dei simboli con blocchi da " << bit_count << " bit:" << endl;
    for (const auto& pair : frequenze) {
        cout << bitset<8>(pair.first) << " | " << pair.second << endl;
    }

    // Calcolare l'entropia
    double entropia = calcola_entropia(frequenze, totale_simboli);
    cout << "Entropia con blocchi da " << bit_count << " bit: " << entropia << endl;

    file.close();
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Uso: " << argv[0] << " <percorso_del_file>" << endl;
        return 1;
    }

    string file_path = argv[1]; // Percorso del file da analizzare

    // Calcolare e stampare le statistiche per blocchi da 8 bit
    calcola_frequenze(file_path, 8);
    cout << endl;

    // Calcolare e stampare le statistiche per blocchi da 4 bit
    calcola_frequenze(file_path, 4);

    return 0;
}


*/










/*#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>

using namespace std;

int main(int argc, char* argv[]) {
    // Controlla se il nome del file è stato fornito come argomento
    if (argc < 2) {
        cerr << "Uso: " << argv[0] << " <nome_file_binario>" << endl;
        return 1;
    }

    string filePath = argv[1];  // Nome del file passato come argomento
    ifstream file(filePath, ios::binary);

    if (!file) {
        cerr << "Errore: impossibile aprire il file '" << filePath << "'!" << endl;
        return 1;
    }

    vector<int> frequenze(256, 0); // Array per contare le occorrenze dei byte (da 0x00 a 0xFF)
    unsigned char byte;
    long totalBytes = 0;

    // Lettura del file un byte alla volta
    while (file.read(reinterpret_cast<char*>(&byte), 1)) {
        frequenze[byte]++;
        totalBytes++;
    }
    file.close();

    // Stampa delle frequenze
    cout << "Analisi delle frequenze dei byte nel file: " << filePath << "\n";
    cout << "Totale byte letti: " << totalBytes << "\n\n";

    cout << "Byte (binario)  | Occorrenze\n";
    cout << "----------------------------\n";
    for (int i = 0; i < 256; i++) {
        cout << bitset<8>(i) << "  | " << frequenze[i] << "\n";
    }

    return 0;
}
*/