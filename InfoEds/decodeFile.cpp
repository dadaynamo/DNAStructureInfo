#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <string>
#include <bitset>

// Mappa per decodificare i primi 3 bit in caratteri
std::unordered_map<std::string, char> binaryToChar = {
    {"000", 'A'},
    {"001", 'C'},
    {"010", 'G'},
    {"011", 'T'},
    {"100", '#'},
    {"101", '{'},
    {"110", '}'},
    {"111", ','}
};

// Legge un bit alla volta dal buffer (caricato dal file binario)
bool readBit(std::ifstream& inputFile, unsigned char& buffer, int& bitCount) {
    if (bitCount == 0) {
        // Leggi un nuovo byte dal file
        char byte;
        if (!inputFile.get(byte)) {
            return false; // Fine del file
        }
        buffer = static_cast<unsigned char>(byte);
        bitCount = 8;
    }

    // Estrai il bit più significativo
    --bitCount;
    return (buffer >> bitCount) & 1;
}

// Decodifica un numero usando Elias Gamma
int decodeEliasGamma(std::ifstream& inputFile, unsigned char& buffer, int& bitCount) {
    int zeroCount = 0;

    // Conta gli zeri iniziali
    while (true) {
        if (inputFile.eof() && bitCount == 0) {
            throw std::runtime_error("Errore: dati insufficienti per decodificare Elias Gamma.");
        }

        if (readBit(inputFile, buffer, bitCount)) {
            break;
        }
        ++zeroCount;
    }

    // Leggi il resto del numero (zeroCount bit)
    int value = 1; // Il primo 1 è implicito
    for (int i = 0; i < zeroCount; ++i) {
        if (inputFile.eof() && bitCount == 0) {
            throw std::runtime_error("Errore: dati insufficienti per completare Elias Gamma.");
        }
        value = (value << 1) | readBit(inputFile, buffer, bitCount);
    }

    //std::cout << "[DEBUG] Decodificato numero Elias Gamma: " << value << std::endl;
    return value;
}

// Decodifica il file binario in un file di testo
void decodeFile(const std::string& inputFileName, const std::string& outputFileName) {
    std::ifstream inputFile(inputFileName, std::ios::binary);
    if (!inputFile.is_open()) {
        throw std::ios_base::failure("Errore: impossibile aprire il file di input.");
    }

    std::ofstream outputFile(outputFileName, std::ios::binary);
    if (!outputFile.is_open()) {
        throw std::ios_base::failure("Errore: impossibile aprire il file di output.");
    }

    unsigned char buffer = 0; // Buffer per leggere i bit
    int bitCount = 0;         // Numero di bit rimasti nel buffer
    std::vector<char> outputBuffer; // Buffer per scrivere in blocco

    //std::cout << "[INFO] Inizio decodifica del file binario." << std::endl;

    // Leggi il file bit per bit
    while (true) {
        // Leggi i primi 3 bit per identificare il carattere
        std::string charBits;
        for (int i = 0; i < 3; ++i) {
            if (inputFile.eof() && bitCount == 0) {
               // std::cout << "[DEBUG] Fine del file raggiunta durante la lettura dei caratteri." << std::endl;
                goto end;
            }

            bool bit = readBit(inputFile, buffer, bitCount);
            charBits += (bit ? '1' : '0');
        }

        if (charBits.size() < 3) {
            //std::cout << "[DEBUG] Fine del file raggiunta con una sequenza di bit incompleta." << std::endl;
            break; // Raggiunta la fine del file senza una sequenza completa
        }

        if (binaryToChar.find(charBits) == binaryToChar.end()) {
            throw std::invalid_argument("Errore: sequenza di bit non valida: " + charBits);
        }

        char decodedChar = binaryToChar[charBits];
        //std::cout << "[DEBUG] Decodificato carattere: " << decodedChar << " (da bit: " << charBits << ")" << std::endl;

        // Decodifica la lunghezza della run (Elias Gamma)
        int runLength = 0;
        try {
            runLength = decodeEliasGamma(inputFile, buffer, bitCount);
        } catch (const std::exception& e) {
            //std::cout << "[DEBUG] Errore durante la decodifica di Elias Gamma: " << e.what() << std::endl;
            break;
        }

        // Aggiungi i caratteri decodificati nel buffer di output
        for (int i = 0; i < runLength; ++i) {
            outputBuffer.push_back(decodedChar);
        }

        // Scrivi in blocco sul file di output quando il buffer è pieno
        if (outputBuffer.size() >= 4096) {
            outputFile.write(outputBuffer.data(), outputBuffer.size());
            outputBuffer.clear();
        }

        if (inputFile.eof() && bitCount == 0) {
            break; // Fine del file
        }
    }

end:
    // Scrivi il buffer rimanente
    if (!outputBuffer.empty()) {
        outputFile.write(outputBuffer.data(), outputBuffer.size());
    }

    inputFile.close();
    outputFile.close();

    //std::cout << "[INFO] Decodifica completata. Risultato scritto nel file: " << outputFileName << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Uso: " << argv[0] << " <file_input_codificato> <file_output_decodificato>\n";
        return 1;
    }

    std::string inputFileName = argv[1];
    std::string outputFileName = argv[2];

    try {
        decodeFile(inputFileName, outputFileName);
    } catch (const std::exception& e) {
        std::cerr << "Errore: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
