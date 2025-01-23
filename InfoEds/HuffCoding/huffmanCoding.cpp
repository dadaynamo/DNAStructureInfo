#include <iostream>
#include <fstream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <bitset>
#include <string>

using namespace std;

// Nodo dell'albero di Huffman
struct HuffmanNode {
    unsigned char byte; // Byte (simbolo)
    size_t freq;        // Frequenza del simbolo
    HuffmanNode* left;  // Figlio sinistro
    HuffmanNode* right; // Figlio destro

    HuffmanNode(unsigned char b, size_t f) : byte(b), freq(f), left(nullptr), right(nullptr) {}
    HuffmanNode(HuffmanNode* l, HuffmanNode* r) : byte(0), freq(l->freq + r->freq), left(l), right(r) {}
};

// Funzione di confronto per la coda di priorità
struct Compare {
    bool operator()(HuffmanNode* a, HuffmanNode* b) {
        return a->freq > b->freq; // Frequenza minore ha priorità maggiore
    }
};

// Costruzione dell'albero di Huffman
HuffmanNode* buildHuffmanTree(const unordered_map<unsigned char, size_t>& freq) {
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> pq;

    // Creazione dei nodi foglia
    for (const auto& pair : freq) {
        pq.push(new HuffmanNode(pair.first, pair.second));
    }

    // Costruzione dell'albero
    while (pq.size() > 1) {
        HuffmanNode* left = pq.top(); pq.pop();
        HuffmanNode* right = pq.top(); pq.pop();
        pq.push(new HuffmanNode(left, right));
    }

    return pq.top();
}

// Generazione dei codici di Huffman
void generateHuffmanCodes(HuffmanNode* root, const string& code, unordered_map<unsigned char, string>& codes) {
    if (!root) return;
    if (!root->left && !root->right) { // Nodo foglia
        codes[root->byte] = code;
    }
    generateHuffmanCodes(root->left, code + "0", codes);
    generateHuffmanCodes(root->right, code + "1", codes);
}

// Scrittura dell'albero nel file compresso
void writeTree(HuffmanNode* root, ostream& out) {
    if (!root->left && !root->right) {
        out.put('1'); // Nodo foglia
        out.put(root->byte);
    } else {
        out.put('0'); // Nodo interno
        writeTree(root->left, out);
        writeTree(root->right, out);
    }
}

// Compressione del file
void compressFile(const string& inputFile, const string& outputFile) {
    // Lettura del file e conteggio delle frequenze
    ifstream in(inputFile, ios::binary);
    if (!in.is_open()) {
        cerr << "Errore nell'apertura del file di input.\n";
        return;
    }

    unordered_map<unsigned char, size_t> freq;
    vector<unsigned char> data;
    unsigned char byte;

    while (in.read(reinterpret_cast<char*>(&byte), 1)) {
        freq[byte]++;
        data.push_back(byte);
    }
    in.close();

    // Costruzione dell'albero di Huffman
    HuffmanNode* root = buildHuffmanTree(freq);

    // Generazione dei codici
    unordered_map<unsigned char, string> codes;
    generateHuffmanCodes(root, "", codes);

    // Scrittura del file compresso
    ofstream out(outputFile, ios::binary);
    if (!out.is_open()) {
        cerr << "Errore nell'apertura del file di output.\n";
        return;
    }

    // Scrittura dell'albero
    writeTree(root, out);

    // Scrittura dei dati compressi
    string encodedData;
    for (unsigned char b : data) {
        encodedData += codes[b];
    }

    // Aggiunta del padding
    size_t padding = 8 - (encodedData.size() % 8);
    for (size_t i = 0; i < padding; i++) {
        encodedData += "0";
    }
    out.put(static_cast<unsigned char>(padding)); // Scrittura del padding

    // Conversione della stringa in byte e scrittura
    for (size_t i = 0; i < encodedData.size(); i += 8) {
        bitset<8> byte(encodedData.substr(i, 8));
        out.put(static_cast<unsigned char>(byte.to_ulong()));
    }

    out.close();
    cout << "Compressione completata. File salvato in: " << outputFile << endl;
}

// Funzione per deallocare l'albero
void freeTree(HuffmanNode* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

// Funzione principale
int main() {
    string inputFile, outputFile;
    cout << "Inserire il nome del file da comprimere: ";
    cin >> inputFile;
    cout << "Inserire il nome del file compresso: ";
    cin >> outputFile;

    compressFile(inputFile, outputFile);
    return 0;
}
