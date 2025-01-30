import matplotlib.pyplot as plt
import csv
import numpy as np

# Funzione per leggere i dati dal file
def read_run_data(filename):
    """Legge i dati da un file di input e li restituisce come un dizionario."""
    run_data = {}
    with open(filename, 'r') as file:
        reader = csv.reader(file)
        for row in reader:
            if len(row) == 2:  # Assicuriamoci che ci siano due colonne
                length, count = map(int, row)
                run_data[length] = count
    return run_data

# Chiedi i nomi dei file di input
file1 = input("Inserisci il nome del primo file (es. file1.txt): ")
file2 = input("Inserisci il nome del secondo file (es. file2.txt): ")

# Leggi i dati dai file
data1 = read_run_data(file1)
data2 = read_run_data(file2)

# Trova il range completo delle lunghezze di run
all_lengths = sorted(set(data1.keys()).union(data2.keys()))

# Prepara i dati per il grafico
counts1 = [data1.get(length, 0) for length in all_lengths]
counts2 = [data2.get(length, 0) for length in all_lengths]

# Creazione del grafico
plt.figure(figsize=(10, 6))
bar_width = 0.4

# Aggiungi le barre per i due file
plt.bar(
    [x - bar_width / 2 for x in all_lengths], counts1, width=bar_width, label=f'File 1: {file1}', align='center', alpha=0.7
)
plt.bar(
    [x + bar_width / 2 for x in all_lengths], counts2, width=bar_width, label=f'File 2: {file2}', align='center', alpha=0.7
)

# Configura l'asse delle ascisse
# plt.xticks(all_lengths)  # Assicura che tutte le lunghezze siano etichettate
plt.xlabel('Lunghezza della run')
plt.ylabel('Numero di run')
plt.yscale('log')
# plt.set_xticks(xgrid)
plt.title('Confronto delle run tra due file')
plt.legend()
plt.grid(axis='y', linestyle='--', alpha=0.7)

# Mostra o salva il grafico
plt.tight_layout()
output_image = input("Inserisci il nome del file per salvare il grafico (es. grafico.png): ")
plt.savefig(output_image)
print(f"Grafico salvato come {output_image}")
plt.show()
