#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main() {
    string nomeFile;
    cout << "Inserisci il nome del file: ";
    cin >> nomeFile;

    ifstream file(nomeFile, ios::binary);
    if (!file.is_open()) {
        cerr << "Errore nell'aprire il file!" << endl;
        return 1;
    }

    char prevChar = '\0';
    int runLength = 0;
    vector<int> runCounts;  // Vettore per contare le run per ogni lunghezza
    int totalRunLength = 0; // Somma della lunghezza totale delle run
    int totalRuns = 0;      // Numero totale di run

    char currentChar;
    long position = 0; // Posizione nel file

    // Leggi il file carattere per carattere
    while (file.get(currentChar)) {
        if (currentChar == prevChar) {
            runLength++;
        } else {
            // Se una run è finita, incrementiamo il contatore per quella lunghezza
            if (runLength > 0) {
                // Assicurati che il vettore sia abbastanza grande per la lunghezza della run
                if (runLength > runCounts.size()) {
                    runCounts.resize(runLength);
                }
                runCounts[runLength - 1]++;  // Incrementa il contatore per la run di quella lunghezza
                totalRunLength += runLength; // Somma la lunghezza totale delle run
                totalRuns++;                 // Incrementa il numero totale di run
            }

            prevChar = currentChar;
            runLength = 1; // Resetta la lunghezza della run
        }

        position++;
    }

    // Controlla l'ultima run
    if (runLength > 0) {
        if (runLength > runCounts.size()) {
            runCounts.resize(runLength);
        }
        runCounts[runLength - 1]++;  // Incrementa il contatore per la run dell'ultima lunghezza
        totalRunLength += runLength; // Somma la lunghezza totale delle run
        totalRuns++;                 // Incrementa il numero totale di run
    }

    // Calcola la lunghezza media delle run (se ci sono run)
    double averageRunLength = 0.0;
    if (totalRuns > 0) {
        averageRunLength = static_cast<double>(totalRunLength) / totalRuns;
    }

    // Stampa i risultati a schermo
    for (size_t i = 0; i < runCounts.size(); i++) {
        if(runCounts[i]!=0)
            cout << "Numero di run di lunghezza " << i + 1 << ": " << runCounts[i] << endl;
    }

    // Stampa la lunghezza media delle run
    cout << "La lunghezza media delle run è: " << averageRunLength << endl;
    cout << "Il numero delle run è: " << totalRuns << endl;

    // Salva i risultati in un file di testo
    string nomeFileOutput;
    cout << "Inserisci il nome del file di output per salvare i risultati (es. output.txt): ";
    cin >> nomeFileOutput;

    ofstream outputFile(nomeFileOutput);
    if (!outputFile.is_open()) {
        cerr << "Errore nella creazione del file di output!" << endl;
        return 1;
    }

    // Scrivi i dati nel file in formato lunghezza_run,numero_run
    for (size_t i = 0; i < runCounts.size(); i++) {
        if(runCounts[i]!=0)
            outputFile << (i + 1) << "," << runCounts[i] << endl;
    }

    // Chiudi il file di output
    outputFile.close();

    cout << "I risultati sono stati salvati in " << nomeFileOutput << endl;


    file.close();
    return 0;
}
