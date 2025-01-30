#include <iostream>
#include <fstream>
#include <bitset>
#include <vector>
#include <map>

using namespace std;

void countRunLengths(const string &filename) {
    // Apri il file binario in modalità lettura binaria
    ifstream file(filename, ios::binary);
    
    if (!file.is_open()) {
        cerr << "Errore nell'aprire il file!" << endl;
        return;
    }

    // Posizione del file e variabili per il conteggio
    file.seekg(0, ios::end);
    size_t file_size = file.tellg(); // dimensione del file in byte
    file.seekg(0, ios::beg);

    cout << "Dimensione originale del file: " << file_size << " byte" << endl;

    bool last_bit = -1; // Stato dell'ultimo bit visto (inizializzato a -1 per forza di differire)
    int current_run_length = 0; // Lunghezza della run attuale
    map<int, int> run_length_count; // Mappa per contare le run di diverse lunghezze
    int total_runs = 0; // Variabile per il totale delle run

    char byte;
    bool in_run = false;

    // Leggi ogni byte del file
    while (file.read(&byte, 1)) {
        // Esamina ogni bit nel byte
        for (int i = 7; i >= 0; --i) {
            bool current_bit = (byte >> i) & 1; // Estrai il singolo bit (0 o 1)

            if (last_bit == current_bit) {
                // Se il bit è uguale all'ultimo, siamo dentro una run
                current_run_length++;
            } else {
                // Se cambia il bit, conta la run e iniziane una nuova
                if (in_run) {
                    run_length_count[current_run_length]++; // Conta la run di questa lunghezza
                    total_runs++; // Incrementa il totale delle run
                }
                last_bit = current_bit;
                current_run_length = 1; // Inizia una nuova run
                in_run = true;
            }
        }
    }

    // Se l'ultima sequenza è una run, conta anche questa
    if (in_run) {
        run_length_count[current_run_length]++; // Conta l'ultima run
        total_runs++; // Incrementa il totale delle run
    }

    // Stampa il numero di run per ogni lunghezza
    cout << "Numero di run per lunghezza:" << endl;
    for (const auto& entry : run_length_count) {
        cout << "Lunghezza run " << entry.first << ": " << entry.second << " run" << endl;
    }

    // Stampa il totale delle run
    cout << "Totale delle run: " << total_runs << " run" << endl;

    file.close();
}

int main() {
    // Chiedi all'utente di inserire il nome del file binario
    string filename;
    cout << "Inserisci il percorso del file binario da analizzare: ";
    cin >> filename;

    // Chiama la funzione per contare le lunghezze delle run
    countRunLengths(filename);

    return 0;
}
