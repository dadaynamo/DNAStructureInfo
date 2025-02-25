#include <iostream>
#include <string>
#include <cstring> // Necessario per strcmp
#include <cstdlib> // Per rand() e srand()
#include <ctime>   // Per time()
#include <fstream> // Libreria per la gestione dei file
#include <sstream>
#include <random>
#include <vector> //Lista dinamica
#include <unordered_map>
#include <cstdint> // Per int64_t
#include <cmath>   // Necessario per le funzioni logaritmiche
#include <algorithm>
#include <chrono>
using namespace std;

// MACROS -------------------------------------------------------------

// GLOBAL VARS --------------------------------------------------------

std::string type;       // C -> Comparison, I -> Individual, HI -> Header Individual, HC -> Header Comparison
char typeIn;            // E -> .eds, T -> .txt
char typeOut = 'C';     // C -> .csv, T -> .txt
std::string outputName; // file name senza estensione
std::string inOrigin;   // Nome file Originale
std::string inComp;     // Nome file da confrontare
std::string logName;    // Nome file di log

int tot; // Dimensione del file originale
int countA, countC, countG, countT, count$, countH, countN, countGA, countGC, countV;

vector<int> O;  // vettore occorrenze caratteri
vector<char> C; // vettore caratteri del file inOrigin

std::ofstream logFile; // Dichiarazione di una variabile globale per il file di log

// FUNCTIONS --------------------------------------------------------------------------------------------------------------------

// Funzione per ottenere il timestamp corrente
std::string getTimestamp()
{
    std::time_t now = std::time(nullptr);
    char timestamp[100];
    std::strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
    return std::string(timestamp);
}

// Funzione per scrivere nel file di log
void writeLog(const std::string &level, const std::string &message)
{
    logFile << "[" << getTimestamp() << "] " << level << " " << message << std::endl;
}

// Funzione per scrivere una separazione di sezione
void writeSectionSeparator(const std::string &sectionName)
{
    logFile << "*************************************************************" << std::endl;
    logFile << "=== SEZIONE: " << sectionName << " ===" << std::endl;
}

// Funzione per scrivere la fine di una sezione
void writeSectionEnd(const std::string &sectionName)
{
    logFile << "=== FINE SEZIONE: " << sectionName << " ===" << std::endl;
    logFile << "*************************************************************" << std::endl
            << std::endl;
}

// Funzione per calcolare il tempo trascorso tra due momenti
long long calculateDuration(const std::chrono::steady_clock::time_point &startTime)
{
    auto endTime = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    return duration;
}

// Funzione per aprire il file di log (da chiamare all'inizio)
void openLogFile(const std::string &filename)
{
    logFile.open(filename, std::ios::app); // Apertura in modalità append
    if (!logFile.is_open())
    {
        std::cerr << "Errore nell'apertura del file di log!" << std::endl;
    }
}

// Funzione per chiudere il file di log (da chiamare alla fine)
void closeLogFile()
{
    if (logFile.is_open())
    {
        logFile.close();
    }
}

/* **********************************************
    Calcolo delle frequenze di ogni simbolo
    nel file originale DA TOGLIERE
    ********************************************* */
int calcFreqChar(std::string filename)
{
    // Dovrebbe essere una buona ottimizzazione
    // Apri il file in modalità di lettura
    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "Errore nell'apertura del file." << endl;
        return 1;
    }
    // Leggi il file e conta la frequenza di A, C, G, T
    char ch;
    while (file.get(ch))
    {
        switch (ch)
        {
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
        case '#':
            countH++;
            break;
        case 'N':
            countN++;
            break;
        case '{':
            countGA++;
            break;
        case '}':
            countGC++;
            break;
        case ',':
            countV++;
            break;
        }
        tot++; // Incrementa il numero totale di caratteri letti
    }

    file.close(); // Chiudi il file
    return 0;
}

void updateStats(std::string filename)
{ // Update le statistiche del file specificato
    calcFreqChar(filename);
}
//*********************************************************************************** */

int displayVersion()
{ // mostra la versione del progetto
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

int displayHelp()
{ // descrizione generale
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

void printGlobal()
{
    cout << "GLOBAL ---------------------------------" << endl;
    cout << "Type " << type << endl;
    cout << "TypeIn " << typeIn << endl;
    cout << "TypeOut " << typeOut << endl;
    cout << "inOrigin " << inOrigin << endl;
    cout << "outputName " << outputName << endl;
    cout << "-----------------------------------------" << endl;
}

void fillVectOC(std::string inputName) // Calcolo delle frequenze
{
    // Apri il file in modalità di lettura
    ifstream file(inputName);
    if (!file.is_open())
    {
        cerr << "Errore nell'apertura del file." << endl;
        // return 1;
    }
    // Leggi il file e conta la frequenza di A, C, G, T
    char ch;
    while (file.get(ch))
    {
        auto it = std::find(C.begin(), C.end(), ch);
        if (it == C.end())
        {                    // Controlla se il carattere è già presente
            C.push_back(ch); // Aggiunge il carattere se non è presente
            O.push_back(1);  // Inserisce 1 nella lista delle occorrenze
        }
        else
        {
            int index = std::distance(C.begin(), it);
            O[index]++; // Incrementa il conteggio delle occorrenze
        }
        tot++;
    }
    file.close();
}
void printOC() // Stampa vettori OC
{

    cout << "********************************" << endl;
    for (size_t i = 0; i < C.size(); i++)
    {
        cout << "| " << C[i] << " : " << O[i] << endl;
    }
    cout << "********************************" << endl;
}
double newEntropy()
{
    double entropia = 0.0;

    for (size_t i = 0; i < O.size(); i++)
    {
        double propC = (double)tot / O[i];
        entropia += ((double)O[i] / tot) * (log(propC) / log(2));
    }

    return entropia;
}
/*
// Funzione per calcolare l'entropia positiva
double entropPos0()
{

    cout << "countA: " << countA << " countC: " << countC << " countG: " << countG << " CountT: " << countT << " count$: " << count$ << "count#: " << countH << " CountN:" << countN << " Count{:" << countGA << " Count}:" << countGC << " Count,:" << countV << " " << tot << endl;
    double entropia = 0.0;

    // Entropia positiva per ciascuna lettera (A, C, G, T)
    if (countA > 0)
    {
        double propA = (double)tot / countA;
        entropia += ((double)countA / tot) * (log(propA) / log(2));
    }
    if (countC > 0)
    {
        double propC = (double)tot / countC;
        entropia += ((double)countC / tot) * (log(propC) / log(2));
    }
    if (countG > 0)
    {
        double propG = (double)tot / countG;
        entropia += ((double)countG / tot) * (log(propG) / log(2));
    }
    if (countT > 0)
    {
        double propT = (double)tot / countT;
        entropia += ((double)countT / tot) * (log(propT) / log(2));
    }
    if (count$ > 0)
    {
        double prop$ = (double)tot / count$;
        entropia += ((double)count$ / tot) * (log(prop$) / log(2));
    }
    if (countH > 0)
    {
        double propH = (double)tot / countH;
        entropia += ((double)countH / tot) * (log(propH) / log(2));
    }
    if (countN > 0)
    {
        double propN = (double)tot / countN;
        entropia += ((double)countN / tot) * (log(propN) / log(2));
    }
    if (countGA > 0)
    {
        double propGA = (double)tot / countGA;
        entropia += ((double)countGA / tot) * (log(propGA) / log(2));
    }
    if (countGC > 0)
    {
        double propGC = (double)tot / countGC;
        entropia += ((double)countGC / tot) * (log(propGC) / log(2));
    }
    if (countV > 0)
    {
        double propV = (double)tot / countV;
        entropia += ((double)countV / tot) * (log(propV) / log(2));
    }

    return entropia;
}*/
/*
double lowerBoundLocalEntropy()
{
    double G = 0;
    if (countA > 0)
        G = G + log2(tot - countA + 1);
    if (countC > 0)
        G = G + log2(tot - countC + 1);
    if (countG > 0)
        G = G + log2(tot - countG + 1);
    if (countT > 0)
        G = G + log2(tot - countT + 1);
    if (count$ > 0)
        G = G + log2(tot - count$ + 1);
    if (countH > 0)
        G = G + log2(tot - countH + 1);
    if (countN > 0)
        G = G + log2(tot - countN + 1);
    if (countGA > 0)
        G = G + log2(tot - countGA + 1);
    if (countGC > 0)
        G = G + log2(tot - countGC + 1);
    if (countV > 0)
        G = G + log2(tot - countV + 1);
    G = G / tot;
    return G;
}*/

double newLowerBoundLocalEntropy()
{
    double G = 0;
    for (size_t i = 0; i < O.size(); i++)
    {
        G = G + log2(tot - O[i] + 1);
    }
    G = G / tot;
    return G;
}

double deltaDegreeBalancecalc(double entropy, double LE, double lowerLE)
{
    double degreeBalance;
    degreeBalance = (entropy - LE) / (entropy - lowerLE);
    return degreeBalance;
}
double tauDegreeBalancecalc(double entropy, double LE, double lowerLE)
{
    double degreeBalance;
    degreeBalance = (LE - lowerLE) / (entropy - lowerLE);
    return degreeBalance;
}

double localEntropy(std::vector<uint32_t> &codDist, int n)
{
    double LE;
    double sum = 0;
    for (int i = 0; i < n; ++i)
    {
        sum += std::log2(codDist[i] + 1); // log base 2

        // cout << "VAL: "<< codDist[i] << " LOG: "  <<std::log2(codDist[i] + 1)<<endl;
        // cout << "SUM parziale: " <<  sum <<endl;
    }
    LE = sum / n;
    return LE;
}
void distance_encode(const std::vector<char> &t, std::vector<uint32_t> &codDist, int n)
{
    std::unordered_map<char, int> posMap;

    for (int i = n - 1; i >= 0; --i)
    {
        char symbol = t[i];
        if (posMap.find(symbol) == posMap.end())
        {
            // Simbolo visto per la prima volta
            posMap[symbol] = i;
        }
        else
        {
            // Calcola la distanza e aggiorna la posizione
            int prevPos = posMap[symbol];
            posMap[symbol] = i;
            codDist[prevPos] = prevPos - i - 1; // Distanza tra due occorrenze
        }
    }

    // Gestione simboli unici o non completati
    for (const auto &pair : posMap)
    {
        codDist[pair.second] = pair.second;
    }
}
double calcLE()
{

    std::ifstream inputFile(inOrigin);
    if (!inputFile)
    {
        std::cerr << "Errore nell'apertura del file: " << inOrigin << std::endl;
        return 1;
    }
    // Posizionamento del cursore all'inizio del file
    inputFile.seekg(0, std::ios::beg); // Posiziona il cursore di lettura all'inizio

    // Leggi il file
    std::vector<char> sequence;
    char c;
    while (inputFile.get(c))
    {
        if (c == 'A' || c == 'C' || c == 'G' || c == 'T' || c == '$' || c == '#' || c == '{' || c == '}' || c == ',' || c == 'E' || c == 'N')
        {
            sequence.push_back(c);
        }
        else
        {
            std::cerr << "Carattere non valido trovato: " << c << std::endl;
            return 1;
        }
    }
    inputFile.close();

    int n = sequence.size();
    std::vector<uint32_t> codDist(n, 0);

    // Calcola il Distance Code
    distance_encode(sequence, codDist, n);
    double LE = localEntropy(codDist, n);
    return LE;
}

double tassoComp()
{
    // Apertura del file originale per ottenere la sua dimensione
    std::ifstream fileOrig(inOrigin, std::ios::binary | std::ios::ate); // Modalità binaria per evitare errori
    if (!fileOrig.is_open())
    {
        std::cerr << "Impossibile aprire il file originale!" << std::endl;
        return -1.0;
    }
    std::streampos sizeOriginale = fileOrig.tellg();
    fileOrig.close();

    // Apertura del file compresso per ottenere la sua dimensione
    std::ifstream fileComp(inComp, std::ios::binary | std::ios::ate); // Modalità binaria
    if (!fileComp.is_open())
    {
        std::cerr << "Impossibile aprire il file compresso!" << std::endl;
        return -1.0;
    }
    std::streampos sizeCompresso = fileComp.tellg();
    fileComp.close();

    // Calcolo del tasso di compressione
    if (sizeCompresso == 0)
    {
        std::cerr << "Errore: il file compresso è vuoto." << std::endl;
        return -1.0;
    }
    cout << "dimensione inOrigin " << sizeOriginale << ". dimensione inComp " << sizeCompresso << endl;
    cout << "tasso compressione = " << static_cast<double>(sizeOriginale) / static_cast<double>(sizeCompresso) << endl;

    return static_cast<double>(sizeOriginale) / static_cast<double>(sizeCompresso);
}

double rapportoRun()
{
    int count = 0;
    int nrun = 0;
    char punt = ' ';
    char c;
    double rapport;
    // prendi il primo carattere
    std::ifstream file(inOrigin); // Apri il file in modalità testo
    if (!file.is_open())
    {
        std::cerr << "Errore: impossibile aprire il file " << inOrigin << std::endl;
    }

    while (file.get(c))
    { // Legge un carattere alla volta
        // std::cout << c<< endl; // Stampa il carattere
        count++;
        if (punt != c)
        {
            nrun++;
            punt = c;
        }
        // cout << count << " " << nrun << endl;
    }
    rapport = static_cast<double>(nrun) / count;
    cout << "numero run " << nrun << " Dim: " << count << " , rapporto run: " << rapport << endl;
    return rapport;
}


void calcDebug()
{ // Inserimento nuova riga della tabella nel file per type comparison
    writeSectionSeparator("Calcolo entropia");
    updateStats(inOrigin);
    fillVectOC(inOrigin);
    printOC();
    double entropy = newEntropy();
    double LE = calcLE();
    double rappRun = rapportoRun();
    double lowerLE = newLowerBoundLocalEntropy();
    double delta = deltaDegreeBalancecalc(entropy, LE, lowerLE);
    double tau = tauDegreeBalancecalc(entropy, LE, lowerLE);

    // Apri il file in modalità append
    std::ofstream file;
    file.open(outputName + ".csv", std::ios::app);

    // Verifica se il file è stato aperto correttamente
    if (!file.is_open())
    {
        std::cerr << "Errore nell'aprire il file in Append Mode." << std::endl;
    }

    file << inOrigin << "," << entropy << "," << LE << "," << rappRun << "," << lowerLE << "," << delta << "," << tau << endl;
    writeLog("[INFO] Entropy: ", to_string(entropy));
    writeLog("[INFO] Local Entropy: ", to_string(LE));
    writeLog("[INFO] Lower LE: ", to_string(lowerLE));
    writeLog("[INFO] Delta: ", to_string(delta));
    

    // Scrivi i dati in formato CSV
    writeSectionEnd("Elaborazione dati");
    // Chiudi il file
    file.close();
    std::cout << "Nuova riga aggiunta con successo!" << std::endl;
}


/* ***************************************
    Calcolo Header tabella per individual e stampa nel file
    ************************************** */
void createTableI()
{ // Creazione tabella finale per type individual e inserirle nel file
    if (typeOut == 'C')
    { // creazione file .csv
        // Creazione di un oggetto ofstream per scrivere nel file CSV
        std::ofstream file(outputName + ".csv", std::ios::app);
        // Verifica se il file è stato aperto correttamente
        if (!file.is_open())
        {
            std::cerr << "Errore nell'aprire il file" << outputName << "!" << std::endl;
        }

        file << "Filename,Entropy,LocalEntropy,Tasso di Run,LowerBoundLE,Sigma,Tau" << std::endl;

        file.close();
        std::cout << "Header Individual CSV creato con successo!" << std::endl;
    }
    else if (typeOut == 'T')
    { // creazione file .txt
        std::cout << "Da implementare!" << std::endl;
    }
}

void insertTableI()
{ // Inserimento nuova riga della tabella nel file per type comparison

    updateStats(inOrigin);
    fillVectOC(inOrigin);
    printOC();
    double entropy = newEntropy();
    double LE = calcLE();
    double rappRun = rapportoRun();
    // double lowerLE = lowerBoundLocalEntropy();
    double lowerLE = newLowerBoundLocalEntropy();
    double delta = deltaDegreeBalancecalc(entropy, LE, lowerLE);
    double tau = tauDegreeBalancecalc(entropy, LE, lowerLE);

    // Apri il file in modalità append
    std::ofstream file;
    file.open(outputName + ".csv", std::ios::app);

    // Verifica se il file è stato aperto correttamente
    if (!file.is_open())
    {
        std::cerr << "Errore nell'aprire il file in Append Mode." << std::endl;
    }

    file << inOrigin << "," << entropy << "," << LE << "," << rappRun << "," << lowerLE << "," << delta << "," << tau << endl;

    // Scrivi i dati in formato CSV

    // Chiudi il file
    file.close();
    std::cout << "Nuova riga aggiunta con successo!" << std::endl;
}

/* ***************************************
    Calcolo Header tabella per comparison e stampa nel file
    ************************************** */
void createTableC()
{ // creazione intestazione della tabella nel file per type comparison
    if (typeOut == 'C')
    { // creazione file .csv
        // Creazione di un oggetto ofstream per scrivere nel file CSV
        std::ofstream file(outputName + ".csv", std::ios::app);
        // Verifica se il file è stato aperto correttamente
        if (!file.is_open())
        {
            std::cerr << "Errore nell'aprire il file!" << std::endl;
        }
        file << "Filename,Rapporto Compressione" << std::endl;

        file.close();
        std::cout << "Header Comparison CSV creato con successo!" << std::endl;
    }
    else if (typeOut == 'T')
    { // creazione file .txt
        std::cout << "Da implementare!" << std::endl;
    }
}

void insertTableC()
{ // Inserimento nuova riga della tabella nel file per type comparison

    // Apri il file in modalità append
    std::ofstream file;
    file.open(outputName + ".csv", std::ios::app);

    // Verifica se il file è stato aperto correttamente
    if (!file.is_open())
    {
        std::cerr << "Errore nell'aprire il file in Append Mode." << std::endl;
    }

    file << inOrigin << "-" << inComp << "," << tassoComp() << endl;

    // Chiudi il file
    file.close();
    std::cout << "Nuova riga aggiunta con successo!" << std::endl;
}

// MAIN ----------------------------------------------------------------
int main(int argc, char *argv[])
{

    // Verifica 0 parametri
    if (argc == 1)
    {
        std::cerr << "Error: Missing required parameters.\n";
        return 1;
    }

    // Verifica gli argomenti passati
    if (argc > 1 && std::string(argv[1]) == "--help")
    {
        displayHelp();
        return 0;
    }

    // Verifica gli argomenti passati
    if (argc > 1 && std::string(argv[1]) == "--version")
    {
        displayVersion();
        return 0;
    }

    // Verifica gli argomenti passati --test
    if (argc > 1 && std::string(argv[1]) == "--test")
    {
        printGlobal();
        return 0;
    }

    // Analizza gli argomenti della riga di comando
    for (int i = 1; i < argc; i += 2)
    {
        if (strcmp(argv[i], "--type") == 0)
        { // Tipo Di procedura da seguire
            if (i + 1 < argc)
            { // Controlla se c'è un argomento successivo
                if (strcmp(argv[i + 1], "C") == 0)
                {
                    type = "C"; // Comparison
                }
                else if (strcmp(argv[i + 1], "I") == 0)
                {
                    type = "I"; // Individual
                }
                else if (strcmp(argv[i + 1], "HI") == 0)
                {
                    type = "HI"; // Header Individual
                }
                else if (strcmp(argv[i + 1], "HC") == 0)
                {
                    type = "HC"; // Header Comparison
                }
                else if (strcmp(argv[i + 1], "D") == 0)
                {
                    type = "D"; // Individual
                }
                else
                {
                    std::cerr << "Errore inserimento type" << std::endl;
                    return 1;
                }
            }
        }
        else if (strcmp(argv[i], "--typeOut") == 0)
        { // Estensione file in output
            if (i + 1 < argc)
            {
                if (strcmp(argv[i + 1], "C") == 0)
                {
                    typeOut = 'C'; // CSV
                }
                else if (strcmp(argv[i + 1], "T") == 0)
                {
                    typeOut = 'T'; // TXT
                }
                else
                {
                    std::cerr << "Errore inserimento typeOut" << std::endl;
                    return 1;
                }
            }
        }
        else if (strcmp(argv[i], "--outputName") == 0)
        {
            if (i + 1 < argc)
            {
                outputName = argv[i + 1]; // Nome file output senza estensione
            }
        }
        else if (strcmp(argv[i], "--inOrigin") == 0)
        {
            if (i + 1 < argc)
            {
                inOrigin = argv[i + 1]; // Nome file input senza estensione
            }
        }
        else if (strcmp(argv[i], "--inComp") == 0)
        {
            if (i + 1 < argc)
            {
                inComp = argv[i + 1]; // Nome file input senza estensione
            }
        }
        else if (strcmp(argv[i], "--log") == 0)
        {
            if (i + 1 < argc)
            {
                logName = argv[i + 1]; // Nome file output senza estensione
                openLogFile(logName);  // Apri il file di log una sola volta
            }
        }
        else
        {
            // default
            openLogFile("a.log");
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

    // printGlobal();

    /*

    ATTRIBUTI:
    --type I C HI HC D
    --typeOut C T
    --outputName string
    --inOrigin string
    --inComp string
    --log string

    */
    if (type == "D")
    {
        calcDebug();
        std::cout << "Hai scelto D." << std::endl;
    }
    else if (type == "I")
    {
        insertTableI();
        std::cout << "Hai scelto H." << std::endl;
    }
    else if (type == "C")
    {
        insertTableC();
        std::cout << "Hai scelto C." << std::endl;
    }
    else if (type == "HI")
    {
        std::cout << "Creo Header per individual." << std::endl;
        createTableI();
    }
    else if (type == "HC")
    {
        std::cout << "Creo Header per comparison." << std::endl;
        createTableC();
    }
    else
    {
        std::cerr << "Errore inserimento type" << std::endl;
        return 1;
    }

    cout << "Fine prog" << endl;
    closeLogFile(); // Chiudi il file di log alla fine
    return 0;
}
