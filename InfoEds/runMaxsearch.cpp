#include <iostream>
#include <fstream>
#include <string>

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
    long runStartPos = -1;  // Posizione di inizio della run
    char runChar = '\0';    // Il carattere della run trovata

    char currentChar;
    long position = 0;  // Posizione nel file

    // Leggi il file carattere per carattere
    while (file.get(currentChar)) {
        if (currentChar == prevChar) {
            runLength++;
        } else {
            // Se la run è di lunghezza 424, segnala la posizione
            if (runLength == 424) {
                cout << "Run trovata di lunghezza 424, carattere: " << runChar << endl;
                cout << "Inizia alla posizione: " << runStartPos << endl;
            }
            prevChar = currentChar;
            runChar = currentChar;  // Salva il carattere della nuova run
            runStartPos = position; // Salva la posizione iniziale della run
            runLength = 1;          // Resetta la lunghezza della run
        }

        position++;
    }

    // Controlla l'ultima run
    if (runLength == 424) {
        cout << "Run trovata di lunghezza 424, carattere: " << runChar << endl;
        cout << "Inizia alla posizione: " << runStartPos << endl;
    }

    file.close();
    return 0;
}
