#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <bitset>

// Mappa per rappresentare i caratteri come numeri binari a 3 bit
std::unordered_map<char, std::string> charToBinary = {
    {'A', "000"},
    {'C', "001"},
    {'G', "010"},
    {'T', "011"},
    {'#', "100"},
    {'{', "101"},
    {'}', "110"},
    {',',"111"}
};

// Funzione per codificare un numero con Elias Gamma
std::string eliasGammaEncode(int n) {
    if (n <= 0) {
        throw std::invalid_argument("Elias Gamma encoding requires positive integers.");
    }

    // Converti il numero in binario
    std::string binary = std::bitset<32>(n).to_string();
    binary = binary.substr(binary.find('1')); // Rimuovi zeri iniziali

    // Calcola il prefisso (L-1 zeri seguiti da un 1)
    int L = binary.length();
    std::string prefix(L - 1, '0');
    // Combina prefisso e corpo
    return prefix + binary;
}



// Scrive i bit accumulati nel buffer su file
void flushBuffer(unsigned char& buffer, int& bitCount, std::ofstream& outputFile) {
    if (bitCount > 0) {
        // Aggiungi padding con zeri se il buffer non è pieno
        buffer <<= (8 - bitCount);
        outputFile.put(buffer);
        buffer = 0;
        bitCount = 0;
    }
}



// Funzione per codificare una stringa e scrivere direttamente su file binario
void encodeAndWriteToFile(const std::string& inputFileName, const std::string& outputFileName) {
    // Apri il file di input
    std::ifstream inputFile(inputFileName);
    if (!inputFile.is_open()) {
        throw std::ios_base::failure("Errore: impossibile aprire il file di input.");
    }

    // Apri il file di output in modalità binaria
    std::ofstream outputFile(outputFileName, std::ios::binary);
    if (!outputFile.is_open()) {
        throw std::ios_base::failure("Errore: impossibile aprire il file di output.");
    }

    // Variabili per la gestione del buffer
    unsigned char buffer = 0; // Buffer per accumulare i bit
    int bitCount = 0;         // Numero di bit accumulati nel buffer

    // Leggi il file di input carattere per carattere
    char currentChar;
    while (inputFile.get(currentChar)) {
        // Verifica se il carattere è valido
        if (charToBinary.find(currentChar) == charToBinary.end()) {
            throw std::invalid_argument("Errore: carattere non valido nel file di input.");
        }

        // Codifica il tipo di carattere (3 bit)
        std::string charCode = charToBinary[currentChar];

        // Conta la lunghezza della run corrente
        int runLength = 1;
        while (inputFile.peek() == currentChar) { // Guarda il prossimo carattere senza consumarlo
            inputFile.get();
            ++runLength;
        }

        // Codifica la lunghezza della run (Elias Gamma)
        std::string lengthCode = eliasGammaEncode(runLength);

        // Combina il tipo di carattere e la lunghezza codificata
        std::string encodedChunk = charCode + lengthCode;

        // Aggiungi i bit nel buffer e scrivi sul file binario
        for (char bit : encodedChunk) {
            buffer = (buffer << 1) | (bit - '0'); // Aggiungi il bit al buffer
            ++bitCount;

            // Se il buffer è pieno (8 bit), scrivilo su file
            if (bitCount == 8) {
                outputFile.put(buffer);
                buffer = 0;
                bitCount = 0;
            }
        }
    }

    // Scrivi eventuali bit rimasti nel buffer
    flushBuffer(buffer, bitCount, outputFile);

    // Chiudi i file
    inputFile.close();
    outputFile.close();
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Uso: " << argv[0] << " <file_input> <file_output>\n";
        return 1;
    }

    // Leggi i nomi dei file dai parametri
    std::string inputFileName = argv[1];
    std::string outputFileName = argv[2];

    try {
        // Codifica e scrivi direttamente su file binario
        encodeAndWriteToFile(inputFileName, outputFileName);
        std::cout << "Codifica completata. Risultato scritto nel file binario: " << outputFileName << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Errore: " << e.what() << "\n";
        return 1;
    }

    return 0;
}



