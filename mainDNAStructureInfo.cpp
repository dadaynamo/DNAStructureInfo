#include <iostream>
#include <string>
#include <cstring> // Necessario per strcmp
#include <cstdlib>  // Per rand() e srand()
#include <ctime>    // Per time()
#include <fstream> // Libreria per la gestione dei file
#include <random>
#include <vector> //Lista dinamica

/*

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
    std::cout << "Usage:\n";
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
                } 
            }
        } else if (strcmp(argv[i], "--typeOut") == 0) { //Estensione file in output
            if (i + 1 < argc) {
                if (strcmp(argv[i + 1], "C") == 0) {
                    typeOut = 'C'; // CSV
                } else if (strcmp(argv[i + 1], "T") == 0) {
                    typeOut = 'T'; // TXT
                }
            }
        } else if (strcmp(argv[i], "--typeIn") == 0) { //Estensione file in input
            if (i + 1 < argc) {
                if (strcmp(argv[i + 1], "E") == 0) {
                    typeIn = 'E'; // EDS
                } else if (strcmp(argv[i + 1], "T") == 0) {
                    typeIn = 'T'; // TXT
                }
            }
        } else if (strcmp(argv[i], "--profile") == 0) { //Estensione file in input
            if (i + 1 < argc) {
                if (strcmp(argv[i + 1], "G") == 0) {
                    profile = 'G'; // General
                } else if (strcmp(argv[i + 1], "A") == 0) {
                    profile = 'A'; // Advanced
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
       

    printGlobal();

    return 0;

}
