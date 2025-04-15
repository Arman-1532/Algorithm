#include <iostream>
#include <queue>
#include <fstream>
#include <string>

using namespace std;

typedef struct node {
    int freq;
    char symbol;
    struct node *left, *right;
} Node;

bool operator<(const Node& x, const Node& y) {
    return x.freq > y.freq;
}

Node* createNode(int frequency, char sym, Node* left, Node* right) {
    Node* newNode = new Node();
    newNode->freq = frequency;
    newNode->symbol = sym;
    newNode->left = left;
    newNode->right = right;
    return newNode;
}

void generateHuffmanCodes(Node* root, string code, char symbols[], string codes[], int& index) {
    if (!root) return;

    if (!root->left && !root->right) {
        symbols[index] = root->symbol;
        codes[index] = code;
        index++;
        return;
    }

    generateHuffmanCodes(root->left, code + "0", symbols, codes, index);
    generateHuffmanCodes(root->right, code + "1", symbols, codes, index);
}

Node* buildHuffmanTree(priority_queue<Node>& pq) {
    while (pq.size() > 1) {
        Node temp1 = pq.top();
        pq.pop();

        Node temp2 = pq.top();
        pq.pop();

        Node* newNode = createNode(temp1.freq + temp2.freq, '\0', new Node(temp1), new Node(temp2));
        pq.push(*newNode);
    }

    return new Node(pq.top());
}

void buildFrequencyTable(const string& filename, char symbols[], int freq[], int& size) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Unable to open file!" << endl;
        return;
    }

    int frequency[256] = {0};
    char ch;

    while (file.get(ch)) {
        frequency[(unsigned char)ch]++;
    }
    file.close();

    size = 0;
    for (int i = 0; i < 256; i++) {
        if (frequency[i] > 0) {
            symbols[size] = (char)i;
            freq[size] = frequency[i];
            size++;
        }
    }
}

string encodeContent(const string& filename, char symbols[], string codes[], int size) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Unable to open file!" << endl;
        return NULL;
    }

    string encodedStr = "";
    char ch;
    while (file.get(ch)) {
        for (int i = 0; i < size; i++) {
            if (symbols[i] == ch) {
                encodedStr += codes[i];
                break;
            }
        }
    }

    file.close();
    return encodedStr;
}

void writeEncodedFile(const string& filename, const string& encodedContent) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Unable to write to file!" << endl;
        return;
    }

    file << encodedContent;
    file.close();
}

void writeHuffmanCodesToFile(const string& filename, char symbols[], string codes[], int size) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Unable to write to file!" << endl;
        return;
    }

    for (int i = 0; i < size; i++) {
        file << symbols[i] << ": " << codes[i] << "\n";
    }

    file.close();
}

string decodeContent(const string& encodedFilename, Node* root) {
    ifstream file(encodedFilename);
    if (!file.is_open()) {
        cout << "Error: Unable to open encoded file!" << endl;
        return NULL;
    }

    string encodedContent;
    getline(file, encodedContent);
    file.close();

    string decodedStr = "";
    Node* current = root;
    for (char bit : encodedContent) {
        if (bit == '0')
            current = current->left;
        else
            current = current->right;

        if (!current->left && !current->right) {  
            decodedStr += current->symbol;
            current = root;
        }
    }

    return decodedStr;
}

void writeDecodedFile(const string& filename, const string& decodedContent) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Unable to write decoded content to file!" << endl;
        return;
    }

    file << decodedContent;
    file.close();
}

int main() {
    const string inputFile = "input.txt";
    const string outputFile = "encoded_output.txt";
    const string codesFile = "huffman_codes.txt";
    const string decodedFile = "decoded_output.txt";

    char symbols[256];
    int freq[256];
    int size = 0;

    buildFrequencyTable(inputFile, symbols, freq, size);

    priority_queue<Node> pq;
    for (int i = 0; i < size; i++) {
        pq.push(*createNode(freq[i], symbols[i], nullptr, nullptr));
    }

    Node* root = buildHuffmanTree(pq);

    char codeSymbols[256];
    string codes[256];
    int codeIndex = 0;
    generateHuffmanCodes(root, "", codeSymbols, codes, codeIndex);

    string encodedContent = encodeContent(inputFile, codeSymbols, codes, codeIndex);

    writeEncodedFile(outputFile, encodedContent);
    writeHuffmanCodesToFile(codesFile, codeSymbols, codes, codeIndex);

    cout << "Huffman Codes:\n";
    for (int i = 0; i < codeIndex; i++) {
        cout << codeSymbols[i] << ": " << codes[i] << endl;
    }

    cout << "Encoded content has been written to " << outputFile << endl;
    cout << "Huffman codes have been written to " << codesFile << endl;

    string decodedContent = decodeContent(outputFile, root);
    writeDecodedFile(decodedFile, decodedContent);

    cout << "Decoded content has been written to " << decodedFile << endl;

    return 0;
}
