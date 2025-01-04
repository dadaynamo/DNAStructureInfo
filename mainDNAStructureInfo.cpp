#include <iostream>
#include <string>
#include <cstring> // Necessario per strcmp
#include <cstdlib>  // Per rand() e srand()
#include <ctime>    // Per time()
#include <fstream> // Libreria per la gestione dei file
#include <sstream>
#include <random>
#include <vector> //Lista dinamica
#include <unordered_map>
#include <cstdint> // Per int64_t
#include <cmath> // Necessario per le funzioni logaritmiche

using namespace std;

//MACROS -------------------------------------------------------------

//GLOBAL VARS --------------------------------------------------------

std::string type;  // C -> Comparison, I -> Individual, HI -> Header Individual, HC -> Header Comparison
char typeIn;  // E -> .eds, T -> .txt
char typeOut = 'C'; // C -> .csv, T -> .txt
std::string outputName; //file name senza estensione
std::string inOrigin; //Nome file Originale
std::string inComp; //Nome file da confrontare

int tot; //Dimensione del file originale
int countA, countC, countG, countT, count$;
//int New_alpha_size = 4; //dimensione dell'alfabeto genomico , 5 considerando i $

//FUNCTIONS ----------------------------------------------------------

//********************************FUNZIONI PROF************************************** */

//Calolo entropia con funzioni prof
//Per usarli bisogna assegnare alle var globali count e tot le frequenze di ogni carattere


/* **********************************************
    Calcolo delle frequenze di ogni simbolo
    nel file originale
    ********************************************* */
int calcFreqChar(std::string filename){ //Dovrebbe essere una buona ottimizzazione
     // Apri il file in modalità di lettura
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Errore nell'apertura del file." << endl;
        return 1;
    }
    // Leggi il file e conta la frequenza di A, C, G, T
    char ch;
    while (file.get(ch)) {
        switch (ch) {
            case 'A':
                countA++;
                break;
            case 'C':
                countC++;
                break;
            case 'G':
                countG++;
                break;
            case 'T':
                countT++;
                break;
            case '$':
                count$++;
                break;
        }
        tot++; // Incrementa il numero totale di caratteri letti
    }

    file.close(); // Chiudi il file
    return 0;
}

void updateStats(std::string filename){ //Update le statistiche del file specificato
    calcFreqChar(filename);
}
//*********************************************************************************** */

int displayVersion(){ //mostra la versione del progetto
    std::cout << "---------------------------------------------------" << std::endl;
    std::cout << "        DNAStructureInfo Program Version 2         " << std::endl;
    std::cout << "---------------------------------------------------" << std::endl;
    std::cout << "Versione: 2.0.0" << std::endl;
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
    cout << "GLOBAL ---------------------------------" << endl;
    cout << "Type " << type << endl;
    cout << "TypeIn " << typeIn << endl;
    cout << "TypeOut " << typeOut << endl;
    cout << "inOrigin " << inOrigin << endl;
    cout << "outputName " << outputName << endl;
    cout << "-----------------------------------------" << endl;

}

void printFile(std::string filename){
    std::ifstream file(filename + ".csv");
    if (!file) {
        std::cerr << "Errore nell'aprire il file: " << filename << ".txt\n";
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::cout << line << '\n';
    }
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

/* DA IMPLEMENTARE*/
// Funzione per calcolare l'entropia positiva
double entropPos0() { //USABILE

    cout << countA << " " << countC << " " << countG << " " << countT << " " << tot << endl;
    double entropia = 0.0;

    // Entropia positiva per ciascuna lettera (A, C, G, T)
    if (countA > 0) {
        double propA = (double)tot / countA;
        entropia += ((double)countA / tot) * (log(propA) / log(2));
    }
    if (countC > 0) {
        double propC = (double)tot / countC;
        entropia += ((double)countC / tot) * (log(propC) / log(2));
    }
    if (countG > 0) {
        double propG = (double)tot / countG;
        entropia += ((double)countG / tot) * (log(propG) / log(2));
    }
    if (countT > 0) {
        double propT = (double)tot / countT;
        entropia += ((double)countT / tot) * (log(propT) / log(2));
    }
    if (count$ > 0) {
        double prop$ = (double)tot / countT;
        entropia += ((double)count$ / tot) * (log(prop$) / log(2));
    }

    return entropia;
}


double localEntropy (std::vector<uint32_t>& codDist, int n){
    double LE;
    double sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += std::log2(codDist[i] + 1); // log base 2

       // cout << "VAL: "<< codDist[i] << " LOG: "  <<std::log2(codDist[i] + 1)<<endl;
       // cout << "SUM parziale: " <<  sum <<endl;
    }
    LE = sum/n;
    return LE;
}
void distance_encode(const std::vector<char>& t, std::vector<uint32_t>& codDist, int n) {
    std::unordered_map<char, int> posMap;

    for (int i = n - 1; i >= 0; --i) {
        char symbol = t[i];
        if (posMap.find(symbol) == posMap.end()) {
            // Simbolo visto per la prima volta
            posMap[symbol] = i;
        } else {
            // Calcola la distanza e aggiorna la posizione
            int prevPos = posMap[symbol];
            posMap[symbol] = i;
            codDist[prevPos] = prevPos - i - 1; // Distanza tra due occorrenze
        }
    }

    // Gestione simboli unici o non completati
    for (const auto& pair : posMap) {
        codDist[pair.second] = pair.second;
    }
}
double calcLE(){
    
    std::ifstream inputFile(inOrigin);
    if (!inputFile) {
        std::cerr << "Errore nell'apertura del file: " << inOrigin << std::endl;
        return 1;
    }
    // Posizionamento del cursore all'inizio del file
    inputFile.seekg(0, std::ios::beg);  // Posiziona il cursore di lettura all'inizio
    
    // Leggi il file
    std::vector<char> sequence;
    char c;
    while (inputFile.get(c)) {
        if (c == 'A' || c == 'C' || c == 'G' || c == 'T' || c == '$') {
            sequence.push_back(c);
        } else {
            std::cerr << "Carattere non valido trovato: " << c << std::endl;
            return 1;
        }
    }
    inputFile.close();

    int n = sequence.size();
    std::vector<uint32_t> codDist(n, 0);

    // Calcola il Distance Code
    distance_encode(sequence, codDist, n);
    double LE = localEntropy(codDist,n);
    return LE;
}


double tassoComp(){
  // Apertura del file originale per ottenere la sua dimensione
    std::ifstream fileOrig(inOrigin, std::ios::binary | std::ios::ate);  // Modalità binaria per evitare errori
    if (!fileOrig.is_open()) {
        std::cerr << "Impossibile aprire il file originale!" << std::endl;
        return -1.0;
    }
    std::streampos sizeOriginale = fileOrig.tellg();
    fileOrig.close();

    // Apertura del file compresso per ottenere la sua dimensione
    std::ifstream fileComp(inComp, std::ios::binary | std::ios::ate);  // Modalità binaria
    if (!fileComp.is_open()) {
        std::cerr << "Impossibile aprire il file compresso!" << std::endl;
        return -1.0;
    }
    std::streampos sizeCompresso = fileComp.tellg();
    fileComp.close();

    // Calcolo del tasso di compressione
    if (sizeCompresso == 0) {
        std::cerr << "Errore: il file compresso è vuoto." << std::endl;
        return -1.0;
    }

    return static_cast<double>(sizeOriginale) / static_cast<double>(sizeCompresso);
}

double rapportoRun(){
    double count = 0;
    double nrun=0;
    char punt = ' ';
    char c;
    double rapport;
    //prendi il primo carattere
    std::ifstream file(inOrigin); // Apri il file in modalità testo
    if (!file.is_open()) {
        std::cerr << "Errore: impossibile aprire il file " << inOrigin << std::endl;
  
    }
    
    while (file.get(c)) { // Legge un carattere alla volta
        //std::cout << c<< endl; // Stampa il carattere
           count++;
        if(punt != c){
            nrun++;
            punt=c;
        }  
        //cout << count << " " << nrun << endl;
    }
    rapport = nrun / count ;
    cout << "rapporto run: " << nrun/count << endl;
    return rapport;
}



/* ***************************************
    Calcolo Header tabella per individual e stampa nel file
    ************************************** */
void createTableI(){ //Creazione tabella finale per type individual e inserirle nel file
    if(typeOut == 'C'){ //creazione file .csv
        // Creazione di un oggetto ofstream per scrivere nel file CSV
        std::ofstream file(outputName+".csv", std::ios::app);
        // Verifica se il file è stato aperto correttamente
        if (!file.is_open()) {
            std::cerr << "Errore nell'aprire il file" << outputName << "!" << std::endl;
        }

        file << "Filename,Entropy,LocalEntropy,Tasso di Run" << std::endl;

        
        file.close();
        std::cout << "Header Individual CSV creato con successo!" << std::endl;
   
        
    }else if(typeOut == 'T'){ //creazione file .txt
        std::cout << "Da implementare!" << std::endl;
        
    }
}

void insertTableI(){ //Inserimento nuova riga della tabella nel file per type comparison 

    updateStats(inOrigin);
    // Apri il file in modalità append
    std::ofstream file;
    file.open(outputName+".csv", std::ios::app);

    // Verifica se il file è stato aperto correttamente
    if (!file.is_open()) {
        std::cerr << "Errore nell'aprire il file in Append Mode." << std::endl;
    }
    
  
    file << inOrigin << "," << entropPos0() << "," << calcLE() << "," << rapportoRun() << endl;
        

    // Scrivi i dati in formato CSV
   
    // Chiudi il file
    file.close();
    std::cout << "Nuova riga aggiunta con successo!" << std::endl;
}


/* ***************************************
    Calcolo Header tabella per comparison e stampa nel file
    ************************************** */
void createTableC(){ //creazione intestazione della tabella nel file per type comparison 
  if(typeOut == 'C'){ //creazione file .csv
        // Creazione di un oggetto ofstream per scrivere nel file CSV
        std::ofstream file(outputName+".csv", std::ios::app);
        // Verifica se il file è stato aperto correttamente
        if (!file.is_open()) {
            std::cerr << "Errore nell'aprire il file!" << std::endl;
        }
        file << "Filename,Rapporto Compressione" << std::endl;
        
        
        file.close();
        std::cout << "Header Comparison CSV creato con successo!" << std::endl;
   
        
    }else if(typeOut == 'T'){ //creazione file .txt
        std::cout << "Da implementare!" << std::endl;
        
    }
}

void insertTableC(){ //Inserimento nuova riga della tabella nel file per type comparison 

    // Apri il file in modalità append
    std::ofstream file;
    file.open(outputName+".csv", std::ios::app);

    // Verifica se il file è stato aperto correttamente
    if (!file.is_open()) {
        std::cerr << "Errore nell'aprire il file in Append Mode." << std::endl;
    }
   
    file << inOrigin << "-" << inComp  << "," << tassoComp() << endl;
    
    // Chiudi il file
    file.close();
    std::cout << "Nuova riga aggiunta con successo!" << std::endl;
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
   
    // Verifica gli argomenti passati --test
    if (argc > 1 && std::string(argv[1]) == "--test"){
        printGlobal();
        return 0;
    }
    
    // Analizza gli argomenti della riga di comando
    for(int i = 1; i < argc; i += 2) {
        if (strcmp(argv[i], "--type") == 0) { //Tipo Di procedura da seguire
            if (i + 1 < argc) { // Controlla se c'è un argomento successivo
                if (strcmp(argv[i + 1], "C") == 0) {
                    type = "C"; // Comparison
                } else if (strcmp(argv[i + 1], "I") == 0) {
                    type = "I"; // Individual
                }else if (strcmp(argv[i + 1], "HI") == 0) {
                    type = "HI"; // Header Individual
                } else if (strcmp(argv[i + 1], "HC") == 0) {
                    type = "HC"; // Header Comparison
                }  else{
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
        } else if (strcmp(argv[i], "--outputName") == 0) {
            if (i + 1 < argc) {
                outputName = argv[i + 1]; // Nome file output senza estensione
            }
        } else if (strcmp(argv[i], "--inOrigin") == 0) {
            if (i + 1 < argc) {
                inOrigin = argv[i + 1]; // Nome file input senza estensione
            }   
        }else if (strcmp(argv[i], "--inComp") == 0) {
            if (i + 1 < argc) {
                inComp = argv[i + 1]; // Nome file input senza estensione
            }   
        }
    }
/*
    if(outputName == "") cout << "Non hai inserito il nome del file di output. Riprovare!!" <<endl;
    //if(inOrigin == "") cout << "Non hai inserito il nome del file di input. Riprovare!!" <<endl;
    if(typeOut == '\0') typeOut = 'C';
    if(type == "C"){
        if(inOrigin == "" || inComp == ""){
            cout << "Errore. non hai inserito i filename di input o output" << endl;
            return 1;
        }   
    }
  */  

    //printGlobal();

/*

ATTRIBUTI:
--type I C HI HC
--typeOut C T
--outputName string
--inOrigin string
--inComp string

*/



    if (type == "I") {
        insertTableI();
        std::cout << "Hai scelto H." << std::endl;
    } else if (type == "C") {
        insertTableC();
        std::cout << "Hai scelto C." << std::endl;
    } else if (type == "HI") {
        std::cout << "Creo Header per individual." << std::endl;
        createTableI();
    } else if (type == "HC") {
        std::cout << "Creo Header per comparison." << std::endl;
        createTableC();
    } else {
        std::cerr << "Errore inserimento type" << std::endl;
        return 1;
    }

    
    cout << "Fine prog" << endl;


    return 0;

}