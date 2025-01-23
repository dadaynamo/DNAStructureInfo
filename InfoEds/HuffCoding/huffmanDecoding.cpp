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
    HuffmanNode* left;  // Figlio sinistro
    HuffmanNode* right; // Figlio destro

    HuffmanNode() : byte(0), left(nullptr), right(nullptr) {}
    HuffmanNode(unsigned char b) : byte(b), left(nullptr), right(nullptr) {}
};

// Ricostruzione dell'albero di Huffman dal file
HuffmanNode* readTree(ifstream& in) {
    char bit;
    in.get(bit);

    if (bit == '1') {
        // Nodo foglia
        unsigned char byte;
        in.get(reinterpret_cast<char&>(byte));
        return new HuffmanNode(byte);
    } else {
        // Nodo interno
        HuffmanNode* node = new HuffmanNode();
        node->left = readTree(in);
        node->right = readTree(in);
        return node;
    }
}

// Decodifica dei dati compressi
void decompressFile(const string& compressedFile, const string& outputFile) {
    // Apertura del file compresso
    ifstream in(compressedFile, ios::binary);
    if (!in.is_open()) {
        cerr << "Errore nell'apertura del file compresso.\n";
        return;
    }

    // Lettura dell'albero di Huffman
    HuffmanNode* root = readTree(in);

    // Lettura del padding
    unsigned char padding;
    in.get(reinterpret_cast<char&>(padding));

    // Lettura dei dati compressi
    string encodedData;
    char byte;
    while (in.get(byte)) {
        bitset<8> bits(byte);
        encodedData += bits.to_string();
    }
    in.close();

    // Rimuove i bit di padding
    encodedData = encodedData.substr(0, encodedData.size() - padding);

    // Decodifica i dati
    ofstream out(outputFile, ios::binary);
    if (!out.is_open()) {
        cerr << "Errore nell'apertura del file di output.\n";
        return;
    }

    HuffmanNode* current = root;
    for (char bit : encodedData) {
        current = (bit == '0') ? current->left : current->right;

        // Nodo foglia: scrive il byte decodificato
        if (!current->left && !current->right) {
            out.put(static_cast<char>(current->byte));
            current = root;
        }
    }

    out.close();
    cout << "Decompressione completata. File salvato in: " << outputFile << endl;

    // Deallocazione dell'albero
    queue<HuffmanNode*> nodes;
    nodes.push(root);
    while (!nodes.empty()) {
        HuffmanNode* node = nodes.front();
        nodes.pop();
        if (node->left) nodes.push(node->left);
        if (node->right) nodes.push(node->right);
        delete node;
    }
}

// Funzione principale
int main() {
    string compressedFile, outputFile;
    cout << "Inserire il nome del file compresso: ";
    cin >> compressedFile;
    cout << "Inserire il nome del file decompresso: ";
    cin >> outputFile;

    decompressFile(compressedFile, outputFile);
    return 0;
}
