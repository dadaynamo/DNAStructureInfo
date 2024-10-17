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

/*
Table Output
|------------------------------------------------------------------------------------------------|
| Filename    | Entropy     | LocalEnt    | Redundancy  | Efficiency | TassoComp   | TYPE        |
|------------------------------------------------------------------------------------------------|
| file1       | 1.78        | 1.5         | 104.4       | 0.5        | 0.1         | Original    |
|-------------|-------------|-------------|-------------|------------|-------------|-------------|
| file2       | 1.78        | 1.5         | 104.4       | 0.5        | 0.5         | Comparison  |
|-------------|-------------|-------------|-------------|------------|-------------|-------------|
| file3       | 1.78        | 1.5         | 104.4       | 0.5        | 0.5         | Comparison  |
|-------------|-------------|-------------|-------------|------------|-------------|-------------|
| file4       | 1.78        | 1.5         | 104.4       | 0.5        | 0.5         | Comparison  |
|------------------------------------------------------------------------------------------------|

*/
using namespace std;

//MACROS -------------------------------------------------------------

//GLOBAL VARS --------------------------------------------------------

char type;  // C -> Comparison, I -> Individual
char typeIn;  // E -> .eds, T -> .txt
char typeOut; // C -> .csv, T -> .txt
char profile; // G -> General, A -> Advanced
std::string outputName; //file name senza estensione
std::string inOrigin; //Nome file Originale
std::vector<std::string> inListComp; //Lista dinamica di filename da confrontare con l'originale


//FUNCTIONS ----------------------------------------------------------


int displayVersion(){ //mostra la versione del progetto
       std::cout << "---------------------------------------------------" << std::endl;
    std::cout << "                DNAStructureInfo Program                    " << std::endl;
    std::cout << "---------------------------------------------------" << std::endl;
    std::cout << "Versione: 1.0.0" << std::endl;
    std::cout << "Autore: Mattia Laszlo Daday" << std::endl;
    std::cout << "Anno: 2024/2025" << std::endl;
    std::cout << "Descrizione:  " << std::endl;
    std::cout << "DNAStructureInfo is a C++ tool that analyzes DNA sequences," << std::endl;
    std::cout << "extracting key metrics like entropy, local entropy, and compressibility rate." << std::endl;
    std::cout << "It generates a summary table to help researchers and bioinformaticians" << std::endl;
    std::cout << "better understand the complexity and structure of the DNA." << std::endl;

    std::cout << "---------------------------------------------------" << std::endl;
    return 0;
}

int displayHelp() { //descrizione generale
      std::cout << "# DNAStructureInfo" << std::endl;
    std::cout << "DNAStructureInfo is a C++ tool that analyzes DNA sequences, extracting key metrics like entropy, local entropy, and compressibility rate." << std::endl;
    std::cout << "It generates a summary table to help researchers and bioinformaticians better understand the complexity and structure of the DNA." << std::endl;
    std::cout << std::endl;
    
    std::cout << "## Installation" << std::endl;
    std::cout << "Use make command to compile the cpp program" << std::endl;
    std::cout << std::endl;
    
    std::cout << "## Usage: " << std::endl;
    std::cout << "### With Makefile" << std::endl;
    std::cout << std::endl;
    std::cout << "make comparison" << std::endl;
    std::cout << std::endl;
    std::cout << "make individual" << std::endl;
    std::cout << std::endl;
    
    std::cout << "### Classic Execution" << std::endl;
    std::cout << std::endl;
    std::cout << "./mainDNAStructureInfo [option] [argument] | ..." << std::endl;
    std::cout << std::endl;
    
    std::cout << "Options:" << std::endl;
    std::cout << "  --help                        Show this help message and exit." << std::endl;
    std::cout << std::endl;
    std::cout << "  --type                        Specify the type of Procedure (Comparison, Individual)" << std::endl;
    std::cout << "                               Example: --type [C , I]" << std::endl;
    std::cout << std::endl;
    std::cout << "  --typeOut                      Specify the extension of the output file (.txt, .csv)." << std::endl;
    std::cout << "                               Example: --typeOut [C , T]" << std::endl;
    std::cout << std::endl;
    std::cout << "  --typeIn                      Specify the extension of the file in input (.eds, .txt)" << std::endl;
    std::cout << "                               Example: --typeIn [E, T]" << std::endl;
    std::cout << std::endl;
    std::cout << "  --profile                     Specify the style of the output table (General, Advanced)" << std::endl;
    std::cout << "                               Example: --profile [G, A]" << std::endl;
    std::cout << std::endl;
    std::cout << "  --outputName                  Specify the name of the output file without extension" << std::endl;
    std::cout << "                               Example --outputName finalout" << std::endl;
    std::cout << std::endl;
    std::cout << "  --inOrigin                    Specify in a comparison test the original file to compare" << std::endl;
    std::cout << "                               --inOrigin original" << std::endl;
    std::cout << std::endl;
    std::cout << "  --inListComp                  Specify the name list of the files to compare" << std::endl;
    std::cout << "                               --inListComp comp1 comp2 comp3" << std::endl;
    std::cout << std::endl;
    std::cout << "  --version                     Display the version of the program and exit." << std::endl;
    std::cout << std::endl;
    
    std::cout << "### Examples:" << std::endl;
    std::cout << std::endl;
    std::cout << "./mainDNAStructureInfo --type C --typeOut T --typeIn E --profile A --outputName output --inOrigin input --inListComp test1 test2 test3" << std::endl;
    std::cout << std::endl;
    std::cout << "./mainDNAStructureInfo --type I --typeOut T --typeIn E --profile A --outputName output --inOrigin input" << std::endl;
    return 0;
}

void printGlobal (){

    cout << "Type " << type << endl;
    cout << "TypeIn " << typeIn << endl;
    cout << "TypeOut " << typeOut << endl;
    cout << "profile " << profile << endl;
    cout << "inOrigin " << inOrigin << endl;
    cout << "outputName " << outputName << endl;
    cout << "inListComp ";
    for (const auto& str : inListComp) {
        std::cout << str << " ";
    }
    cout << endl;

}

double localEntropy(){
    return 1.7;
}

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

double lE(){
    return 0.0;
}
double tassoComp(){
    return 0.0;
}
double efficiency(){
    return 0.0;
}
double redundancy(){
    return 0.0;
}
void updateStats(double stats[5]){
    stats[1] =  entropy(inOrigin);
    stats[2] =  localEntropy();
    stats[3] =  redundancy();
    stats[4] =  efficiency();
    stats[5] =  tassoComp();

}

void createTableI (double stats[5]){ //Creazione tabella finale per type individual e inserirle nel file
    if(typeOut == 'C'){ //creazione file .csv
        // Creazione di un oggetto ofstream per scrivere nel file CSV
        std::ofstream file(outputName+".csv");
        // Verifica se il file è stato aperto correttamente
        if (!file.is_open()) {
            std::cerr << "Errore nell'aprire il file!" << std::endl;
        }

        // Scrivere l'intestazione (header) del CSV
        if(profile == 'G'){ //Generazione tabella riassuntiva
            file << "Filename,Entropy,LocalEntropy" << std::endl;
            file << inOrigin << "," << stats[1] << "," << stats[2] <<std::endl;

        }else if(profile == 'A'){ //Generazione tabella estesa
            file << "Filename,Entropy,LocalEntropy,Redundancy,Efficiency,TassoCompressione" << std::endl;
            file << inOrigin << "," << stats[1] << "," << stats[2] << "," << stats[3] << "," << stats[4] << "," << stats[5] <<std::endl;
        }
        
        file.close();
        std::cout << "File CSV creato con successo!" << std::endl;
   
        
    }else if(typeOut == 'T'){ //creazione file .txt
        std::cout << "Da implementare!" << std::endl;
        
    }
}

//MAIN ----------------------------------------------------------------
int main(int argc, char* argv[]){

    //Verifica 0 parametri 
    if (argc == 1){
        std::cerr << "Error: Missing required parameters.\n";
        return 1;
    }

    // Verifica gli argomenti passati
    if (argc > 1 && std::string(argv[1]) == "--help"){
        displayHelp();
        return 0;
    }


    // Verifica gli argomenti passati
    if (argc > 1 && std::string(argv[1]) == "--version"){
        displayVersion();
        return 0;
    }
   

    // Analizza gli argomenti della riga di comando
    for(int i = 1; i < argc; i += 2) {
        if (strcmp(argv[i], "--type") == 0) { //Tipo Di procedura da seguire
            if (i + 1 < argc) { // Controlla se c'è un argomento successivo
                if (strcmp(argv[i + 1], "C") == 0) {
                    type = 'C'; // Comparison
                } else if (strcmp(argv[i + 1], "I") == 0) {
                    type = 'I'; // Individual
                } else{
                    std::cerr << "Errore inserimento type" << std::endl;
                    return 1;
                }
            }
        } else if (strcmp(argv[i], "--typeOut") == 0) { //Estensione file in output
            if (i + 1 < argc) {
                if (strcmp(argv[i + 1], "C") == 0) {
                    typeOut = 'C'; // CSV
                } else if (strcmp(argv[i + 1], "T") == 0) {
                    typeOut = 'T'; // TXT
                } else{
                    std::cerr << "Errore inserimento typeOut" << std::endl;
                    return 1;
                }
            }
        //} else if (strcmp(argv[i], "--typeIn") == 0) { //Estensione file in input
          //  if (i + 1 < argc) {
            //    if (strcmp(argv[i + 1], "E") == 0) {
              //      typeIn = 'E'; // EDS
                //} else if (strcmp(argv[i + 1], "T") == 0) {
                 //   typeIn = 'T'; // TXT
                //}else{
                  //  std::cerr << "Errore inserimento typeIn" << std::endl;
                    //return 1;
                //}
            //}
        } else if (strcmp(argv[i], "--profile") == 0) { //Estensione file in input
            if (i + 1 < argc) {
                if (strcmp(argv[i + 1], "G") == 0) {
                    profile = 'G'; // General
                } else if (strcmp(argv[i + 1], "A") == 0) {
                    profile = 'A'; // Advanced
                }else{
                    std::cerr << "Errore inserimento profile" << std::endl;
                    return 1;
                }
            }
        } else if (strcmp(argv[i], "--outputName") == 0) {
            if (i + 1 < argc) {
                outputName = argv[i + 1]; // Nome file output senza estensione
            }
        } else if (strcmp(argv[i], "--inOrigin") == 0) {
            if (i + 1 < argc) {
                inOrigin = argv[i + 1]; // Nome file input senza estensione
            }   
        } else if (strcmp(argv[i], "--inListComp") == 0) { //Gestione Lista di comparazione e inserimento in inListComp
            if (i + 1 < argc) {
                for(int j = i+1 ; j< argc ; j++){
                    std::string currentvalue = argv[j];
                    if(currentvalue.rfind("--", 0) == 0){
                        break;
                    }
                    inListComp.push_back(currentvalue);
                }
                
            }   
        }
    }
       

    // Verifica gli argomenti passati
    if (argc > 1 && std::string(argv[1]) == "--test"){
        printGlobal();
        return 0;
    }
    

    switch (type)
    {
    case 'C': //Inizio il comparison
        
        break;
    case 'I': //Inizio l'individual
        double stats [5]; //array per contenere le stats del file individuale
        updateStats(stats);
        createTableI(stats);
        break;
    default:
        std::cerr << "Errore inserimento type" << std::endl;
        return 1;
        break;
    }
    
    cout << "Fine prog" << endl;

    return 0;

}
