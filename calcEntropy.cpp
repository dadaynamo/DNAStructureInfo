#include <iostream>
#include <string>
#include <cstring> // Necessario per strcmp
#include <cstdlib>  // Per rand() e srand()
#include <ctime>    // Per time()
#include <fstream> // Libreria per la gestione dei file
#include <random>
#include <vector> //Lista dinamica
#include <unordered_map>
#include <cstdint> // Per int64_t
#include <cmath> // Necessario per le funzioni logaritmiche
 
 using namespace std;

double entropy(std::string inputName){ //Calcolo entropia di ordine zero di una stringa 
    
    double entropy = 0.0;

    std::int64_t countA = 0, countC = 0, countG = 0, countT = 0; //contatori occorrenze
    const std::size_t bufferSize = 1024 * 1024; // 1 MB buffer
    char buffer[bufferSize];  // Buffer temporaneo per leggere il file
    
    // Aprire il file in modalità binaria
    std::ifstream file(inputName+".txt", std::ios::in | std::ios::binary);
    // Variabile per la dimensione letta
    std::int64_t dim = 0; // Variabile che tiene traccia della dimensione totale letta

    if (!file) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }
       // Leggere il file a blocchi e contare le occorrenze
    while (file.read(buffer, bufferSize) || file.gcount() > 0) {
        std::size_t bytesRead = file.gcount(); // Numero di byte letti
        dim += bytesRead; // Aggiorna la dimensione totale letta
        // Scorrere il buffer e contare le occorrenze di A, C, G, T
        for (std::size_t i = 0; i < bytesRead; ++i) {
            switch (buffer[i]) {
                case 'A': 
                    ++countA;
                    break;
                case 'C':
                    ++countC;
                    break;
                case 'G':
                    ++countG;
                    break;
                case 'T':
                    ++countT;
                    break;
            }
        }
    }

    file.close();
    double freqA = static_cast<double>(countA) / static_cast<double>(dim);
    double freqC = static_cast<double>(countC) / static_cast<double>(dim);
    double freqG = static_cast<double>(countG) / static_cast<double>(dim);
    double freqT = static_cast<double>(countT) / static_cast<double>(dim);


    //calcolo entropia
    entropy = - ((log2(freqA)*freqA) + (log2(freqC)*freqC) + (log2(freqG)*freqG) + (log2(freqT)*freqT));


    // Stampa i risultati
    std::cout << "Dim file: " << dim << std::endl;
    std::cout << "Occurrences of 'A': " << countA << std::endl;
    std::cout << "Occurrences of 'C': " << countC << std::endl;
    std::cout << "Occurrences of 'G': " << countG << std::endl;
    std::cout << "Occurrences of 'T': " << countT << std::endl;
    std::cout << "Entropy DNA': " << entropy << std::endl;
    
    return entropy;
} 


 int main(){
    double entropyfe = entropy("test/smalltest");
    cout << entropyfe << endl;;

    return 0;
}